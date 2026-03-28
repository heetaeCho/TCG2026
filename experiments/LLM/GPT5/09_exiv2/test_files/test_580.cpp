// =================================================================================================
// TEST_ID: 580
// File: test_memio_putb_580.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::byte;
using Exiv2::MemIo;
using Exiv2::Position;

class MemIoPutbTest_580 : public ::testing::Test {
 protected:
  static void EnsureOpen(MemIo& io) {
    // Treat as black-box: if open() is required, this makes tests robust.
    // If open() is a no-op, still fine.
    (void)io.open();
  }
};

TEST_F(MemIoPutbTest_580, ReturnsWrittenByteForCommonValues_580) {
  MemIo io;
  EnsureOpen(io);

  EXPECT_EQ(0x00, io.putb(static_cast<byte>(0x00)));
  EXPECT_EQ(0x7F, io.putb(static_cast<byte>(0x7F)));
  EXPECT_EQ(0xFF, io.putb(static_cast<byte>(0xFF)));
}

TEST_F(MemIoPutbTest_580, IncreasesTellAndSizeByOnePerPut_580) {
  MemIo io;
  EnsureOpen(io);

  const size_t size0 = io.size();
  const size_t tell0 = io.tell();

  (void)io.putb(static_cast<byte>(0x12));

  EXPECT_EQ(size0 + 1U, io.size());
  EXPECT_EQ(tell0 + 1U, io.tell());
}

TEST_F(MemIoPutbTest_580, MultiplePutbAppendsBytesReadableInOrderViaGetb_580) {
  MemIo io;
  EnsureOpen(io);

  const std::vector<byte> bytes = {
      static_cast<byte>(0x10), static_cast<byte>(0x20), static_cast<byte>(0x30), static_cast<byte>(0xFF)};

  for (byte b : bytes) {
    EXPECT_EQ(static_cast<int>(b), io.putb(b));
  }

  ASSERT_EQ(0, io.seek(0, Position::beg));

  for (byte expected : bytes) {
    const int got = io.getb();
    EXPECT_EQ(static_cast<int>(expected), got);
  }
}

TEST_F(MemIoPutbTest_580, StressPutbManyBytesAndVerifySizeAndReadback_580) {
  MemIo io;
  EnsureOpen(io);

  const size_t size0 = io.size();

  constexpr size_t kCount = 1024;
  std::vector<byte> bytes;
  bytes.reserve(kCount);
  for (size_t i = 0; i < kCount; ++i) {
    bytes.push_back(static_cast<byte>(i & 0xFF));
  }

  for (byte b : bytes) {
    EXPECT_EQ(static_cast<int>(b), io.putb(b));
  }

  EXPECT_EQ(size0 + kCount, io.size());
  EXPECT_EQ(size0 + kCount, io.tell());

  ASSERT_EQ(0, io.seek(static_cast<int64_t>(size0), Position::beg));

  for (byte expected : bytes) {
    const int got = io.getb();
    EXPECT_EQ(static_cast<int>(expected), got);
  }
}

TEST_F(MemIoPutbTest_580, PutbThenReadUsingReadBufferInterface_580) {
  MemIo io;
  EnsureOpen(io);

  const std::vector<byte> bytes = {static_cast<byte>(0xAB), static_cast<byte>(0xCD), static_cast<byte>(0xEF)};
  for (byte b : bytes) {
    (void)io.putb(b);
  }

  ASSERT_EQ(0, io.seek(0, Position::beg));

  std::vector<byte> out(bytes.size(), static_cast<byte>(0x00));
  const size_t n = io.read(out.data(), out.size());
  EXPECT_EQ(bytes.size(), n);
  EXPECT_EQ(bytes, out);
}

}  // namespace