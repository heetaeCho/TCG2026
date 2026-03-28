// ============================================================================
// TEST_ID: 1477
// File: test_panasonic_mn_header_write_1477.cpp
// Target: ./TestProjects/exiv2/src/makernote_int.cpp (Exiv2::Internal::PanasonicMnHeader)
// ============================================================================

#include <gtest/gtest.h>

#include "basicio.hpp"
#include "makernote_int.hpp"

// Some Exiv2 trees expose IoWrapper via a dedicated header; include if available.
// If your build already pulls it transitively, this include is harmless.
// (If your project doesn't have this header, you can remove this line.)
#include "iowrapper.hpp"

namespace {

using Exiv2::ByteOrder;

class PanasonicMnHeaderTest_1477 : public ::testing::Test {
 protected:
  // Helper: copy MemIo contents into a std::vector<byte> without relying on internal state.
  static std::vector<Exiv2::byte> ReadAll(Exiv2::BasicIo& io) {
    const long originalPos = io.tell();
    io.seek(0, Exiv2::BasicIo::beg);

    std::vector<Exiv2::byte> out(static_cast<size_t>(io.size()));
    if (!out.empty()) {
      const long r = io.read(out.data(), static_cast<long>(out.size()));
      out.resize(static_cast<size_t>(std::max<long>(0, r)));
    }

    io.seek(originalPos, Exiv2::BasicIo::beg);
    return out;
  }
};

TEST_F(PanasonicMnHeaderTest_1477, WriteReturnsBytesWrittenAndProducesSameIncreaseInTargetIo_1477) {
  Exiv2::MemIo mem;
  Exiv2::Internal::IoWrapper wrapper(mem);
  Exiv2::Internal::PanasonicMnHeader header;

  const size_t before = static_cast<size_t>(mem.size());
  const size_t written = header.write(wrapper, ByteOrder::littleEndian);
  const size_t after = static_cast<size_t>(mem.size());

  EXPECT_GT(written, 0u);
  EXPECT_EQ(after - before, written);
}

TEST_F(PanasonicMnHeaderTest_1477, WriteAppendsOnRepeatedCalls_1477) {
  Exiv2::MemIo mem;
  Exiv2::Internal::IoWrapper wrapper(mem);
  Exiv2::Internal::PanasonicMnHeader header;

  const size_t w1 = header.write(wrapper, ByteOrder::littleEndian);
  const size_t s1 = static_cast<size_t>(mem.size());

  const size_t w2 = header.write(wrapper, ByteOrder::littleEndian);
  const size_t s2 = static_cast<size_t>(mem.size());

  EXPECT_GT(w1, 0u);
  EXPECT_GT(w2, 0u);
  EXPECT_EQ(s1, w1);
  EXPECT_EQ(s2, w1 + w2);
}

TEST_F(PanasonicMnHeaderTest_1477, WriteIgnoresByteOrderForLengthAndOutputBytes_1477) {
  Exiv2::Internal::PanasonicMnHeader header;

  Exiv2::MemIo memLE;
  Exiv2::Internal::IoWrapper wrapperLE(memLE);
  const size_t wLE = header.write(wrapperLE, ByteOrder::littleEndian);
  const auto bytesLE = ReadAll(memLE);

  Exiv2::MemIo memBE;
  Exiv2::Internal::IoWrapper wrapperBE(memBE);
  const size_t wBE = header.write(wrapperBE, ByteOrder::bigEndian);
  const auto bytesBE = ReadAll(memBE);

  EXPECT_GT(wLE, 0u);
  EXPECT_EQ(wBE, wLE);
  EXPECT_EQ(bytesBE.size(), bytesLE.size());
  EXPECT_EQ(bytesBE, bytesLE);
}

TEST_F(PanasonicMnHeaderTest_1477, WriteToAlreadyNonEmptyIoOnlyAppendsHeaderBytes_1477) {
  Exiv2::MemIo mem;
  // Pre-fill with a sentinel payload through the public BasicIo interface.
  const Exiv2::byte prefix[] = {0xAA, 0xBB, 0xCC, 0xDD};
  ASSERT_EQ(mem.write(prefix, static_cast<long>(sizeof(prefix))), static_cast<long>(sizeof(prefix)));

  Exiv2::Internal::IoWrapper wrapper(mem);
  Exiv2::Internal::PanasonicMnHeader header;

  const auto beforeBytes = ReadAll(mem);
  ASSERT_EQ(beforeBytes.size(), sizeof(prefix));

  const size_t written = header.write(wrapper, ByteOrder::littleEndian);

  const auto afterBytes = ReadAll(mem);
  EXPECT_EQ(afterBytes.size(), sizeof(prefix) + written);

  // Verify prefix preserved (append-only observable effect).
  ASSERT_GE(afterBytes.size(), sizeof(prefix));
  for (size_t i = 0; i < sizeof(prefix); ++i) {
    EXPECT_EQ(afterBytes[i], prefix[i]);
  }
}

}  // namespace