// File: test_olympus_mn_header_1440.cpp
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

// Internal headers (path may vary by your build; adjust include if needed)
#include <exiv2/makernote_int.hpp>

namespace {

class OlympusMnHeaderTest_1440 : public ::testing::Test {
protected:
  Exiv2::Internal::OlympusMnHeader header_{};
};

TEST_F(OlympusMnHeaderTest_1440, WriteReturnsNumberOfBytesAppended_1440) {
  Exiv2::MemIo memIo;
  Exiv2::Internal::IoWrapper ioWrapper;
  ioWrapper.setTarget(&memIo);

  const auto before = memIo.size();
  const size_t written = header_.write(ioWrapper, Exiv2::littleEndian);
  const auto after = memIo.size();

  EXPECT_EQ(after, before + written);
  EXPECT_GT(written, 0u);
}

TEST_F(OlympusMnHeaderTest_1440, WriteAppendsOnRepeatedCalls_1440) {
  Exiv2::MemIo memIo;
  Exiv2::Internal::IoWrapper ioWrapper;
  ioWrapper.setTarget(&memIo);

  const size_t w1 = header_.write(ioWrapper, Exiv2::littleEndian);
  const auto size1 = memIo.size();

  const size_t w2 = header_.write(ioWrapper, Exiv2::littleEndian);
  const auto size2 = memIo.size();

  EXPECT_EQ(size1, w1);
  EXPECT_EQ(size2, w1 + w2);
  EXPECT_EQ(w1, w2);
}

TEST_F(OlympusMnHeaderTest_1440, WriteSizeIsIndependentOfByteOrder_1440) {
  Exiv2::MemIo memIoLE;
  Exiv2::Internal::IoWrapper ioWrapperLE;
  ioWrapperLE.setTarget(&memIoLE);

  Exiv2::MemIo memIoBE;
  Exiv2::Internal::IoWrapper ioWrapperBE;
  ioWrapperBE.setTarget(&memIoBE);

  const size_t wLE = header_.write(ioWrapperLE, Exiv2::littleEndian);
  const size_t wBE = header_.write(ioWrapperBE, Exiv2::bigEndian);

  EXPECT_EQ(wLE, wBE);
  EXPECT_EQ(memIoLE.size(), memIoBE.size());
}

TEST_F(OlympusMnHeaderTest_1440, WriteFromNonEmptyBufferStillAppends_1440) {
  Exiv2::MemIo memIo;
  Exiv2::Internal::IoWrapper ioWrapper;
  ioWrapper.setTarget(&memIo);

  // Pre-fill with some bytes using public BasicIo interface
  const Exiv2::byte seed[] = {0x01, 0x02, 0x03, 0x04};
  ASSERT_EQ(static_cast<long>(sizeof(seed)), memIo.write(seed, static_cast<long>(sizeof(seed))));

  const auto before = memIo.size();
  const size_t written = header_.write(ioWrapper, Exiv2::littleEndian);
  const auto after = memIo.size();

  EXPECT_EQ(after, before + written);
  EXPECT_GE(before, sizeof(seed));
}

}  // namespace