// =================================================================================================
// TEST_ID: 1145
// File: test_us2Data_1145.cpp
// Unit tests for Exiv2::us2Data (./TestProjects/exiv2/src/types.cpp)
//
// Constraints followed:
// - Treat implementation as black box (test only observable effects).
// - Verify outputs via buffer content + returned size.
// - Include normal, boundary, and error/exception-observable cases.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

#include "exiv2/types.hpp"

namespace {

// Match Exiv2's byte type expectation used by us2Data signature.
// If Exiv2 defines Exiv2::byte differently in your build, adjust this alias accordingly.
using byte = unsigned char;

class Us2DataTest_1145 : public ::testing::Test {};

TEST_F(Us2DataTest_1145, ReturnsTwoBytesForLittleEndian_1145) {
  byte buf[4] = {0xAA, 0xAA, 0xAA, 0xAA};

  const uint16_t value = 0x1234;
  const size_t written = Exiv2::us2Data(buf, value, Exiv2::littleEndian);

  EXPECT_EQ(2u, written);
  EXPECT_EQ(0x34u, static_cast<unsigned>(buf[0]));
  EXPECT_EQ(0x12u, static_cast<unsigned>(buf[1]));
  // Ensure no overwrite past the documented 2 bytes.
  EXPECT_EQ(0xAAu, static_cast<unsigned>(buf[2]));
  EXPECT_EQ(0xAAu, static_cast<unsigned>(buf[3]));
}

TEST_F(Us2DataTest_1145, ReturnsTwoBytesForBigEndian_1145) {
  byte buf[4] = {0xAA, 0xAA, 0xAA, 0xAA};

  const uint16_t value = 0x1234;
  const size_t written = Exiv2::us2Data(buf, value, Exiv2::bigEndian);

  EXPECT_EQ(2u, written);
  EXPECT_EQ(0x12u, static_cast<unsigned>(buf[0]));
  EXPECT_EQ(0x34u, static_cast<unsigned>(buf[1]));
  EXPECT_EQ(0xAAu, static_cast<unsigned>(buf[2]));
  EXPECT_EQ(0xAAu, static_cast<unsigned>(buf[3]));
}

TEST_F(Us2DataTest_1145, BoundaryZeroValueLittleEndian_1145) {
  byte buf[3] = {0xCC, 0xCC, 0xCC};

  const uint16_t value = 0x0000;
  const size_t written = Exiv2::us2Data(buf, value, Exiv2::littleEndian);

  EXPECT_EQ(2u, written);
  EXPECT_EQ(0x00u, static_cast<unsigned>(buf[0]));
  EXPECT_EQ(0x00u, static_cast<unsigned>(buf[1]));
  EXPECT_EQ(0xCCu, static_cast<unsigned>(buf[2]));
}

TEST_F(Us2DataTest_1145, BoundaryMaxValueBigEndian_1145) {
  byte buf[3] = {0xCC, 0xCC, 0xCC};

  const uint16_t value = 0xFFFF;
  const size_t written = Exiv2::us2Data(buf, value, Exiv2::bigEndian);

  EXPECT_EQ(2u, written);
  EXPECT_EQ(0xFFu, static_cast<unsigned>(buf[0]));
  EXPECT_EQ(0xFFu, static_cast<unsigned>(buf[1]));
  EXPECT_EQ(0xCCu, static_cast<unsigned>(buf[2]));
}

TEST_F(Us2DataTest_1145, WritesOnlyFirstTwoBytesWhenBufferHasMoreSpace_1145) {
  byte buf[8];
  std::memset(buf, 0x5Au, sizeof(buf));

  const uint16_t value = 0x00A5;
  const size_t written = Exiv2::us2Data(buf, value, Exiv2::littleEndian);

  EXPECT_EQ(2u, written);
  EXPECT_EQ(0xA5u, static_cast<unsigned>(buf[0]));
  EXPECT_EQ(0x00u, static_cast<unsigned>(buf[1]));
  for (size_t i = 2; i < sizeof(buf); ++i) {
    EXPECT_EQ(0x5Au, static_cast<unsigned>(buf[i]));
  }
}

TEST_F(Us2DataTest_1145, InvalidByteOrderFallsBackToNonLittleEndianBranchObservableAsBigEndian_1145) {
  byte buf[4] = {0x11, 0x22, 0x33, 0x44};

  const uint16_t value = 0xABCD;
  // Use an invalid/unknown enum value through cast; behavior is observable via output bytes.
  const auto invalid = static_cast<Exiv2::ByteOrder>(Exiv2::invalidByteOrder);

  const size_t written = Exiv2::us2Data(buf, value, invalid);

  EXPECT_EQ(2u, written);
  // Observable behavior: for non-littleEndian, bytes appear in big-endian order.
  EXPECT_EQ(0xABu, static_cast<unsigned>(buf[0]));
  EXPECT_EQ(0xCDu, static_cast<unsigned>(buf[1]));
  EXPECT_EQ(0x33u, static_cast<unsigned>(buf[2]));
  EXPECT_EQ(0x44u, static_cast<unsigned>(buf[3]));
}

}  // namespace