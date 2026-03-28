// =================================================================================================
// TEST_ID: 1137
// File: test_types_getULong_1137.cpp
// Unit tests for Exiv2::getULong (types.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>

#include "exiv2/types.hpp"

namespace {

// Fixture just to keep naming consistent with your suite style.
class GetULongTest_1137 : public ::testing::Test {};

TEST_F(GetULongTest_1137, LittleEndianReadsBytesInLittleEndianOrder_1137) {
  const Exiv2::byte buf[4] = {0x01, 0x02, 0x03, 0x04};

  const uint32_t v = Exiv2::getULong(buf, Exiv2::littleEndian);

  // Little endian: buf[0] is least-significant byte.
  EXPECT_EQ(v, 0x04030201u);
}

TEST_F(GetULongTest_1137, BigEndianReadsBytesInBigEndianOrder_1137) {
  const Exiv2::byte buf[4] = {0x01, 0x02, 0x03, 0x04};

  const uint32_t v = Exiv2::getULong(buf, Exiv2::bigEndian);

  // Big endian: buf[0] is most-significant byte.
  EXPECT_EQ(v, 0x01020304u);
}

TEST_F(GetULongTest_1137, LittleEndianAllZerosReturnsZero_1137) {
  const Exiv2::byte buf[4] = {0x00, 0x00, 0x00, 0x00};

  EXPECT_EQ(Exiv2::getULong(buf, Exiv2::littleEndian), 0u);
}

TEST_F(GetULongTest_1137, BigEndianAllZerosReturnsZero_1137) {
  const Exiv2::byte buf[4] = {0x00, 0x00, 0x00, 0x00};

  EXPECT_EQ(Exiv2::getULong(buf, Exiv2::bigEndian), 0u);
}

TEST_F(GetULongTest_1137, LittleEndianAllOnesReturnsMaxUInt32_1137) {
  const Exiv2::byte buf[4] = {0xFF, 0xFF, 0xFF, 0xFF};

  EXPECT_EQ(Exiv2::getULong(buf, Exiv2::littleEndian), 0xFFFFFFFFu);
}

TEST_F(GetULongTest_1137, BigEndianAllOnesReturnsMaxUInt32_1137) {
  const Exiv2::byte buf[4] = {0xFF, 0xFF, 0xFF, 0xFF};

  EXPECT_EQ(Exiv2::getULong(buf, Exiv2::bigEndian), 0xFFFFFFFFu);
}

TEST_F(GetULongTest_1137, LittleEndianHandlesHighBitWithoutSignExtension_1137) {
  // Boundary: highest bit set via most-significant byte of the resulting value.
  const Exiv2::byte buf[4] = {0x00, 0x00, 0x00, 0x80};

  const uint32_t v = Exiv2::getULong(buf, Exiv2::littleEndian);

  EXPECT_EQ(v, 0x80000000u);
}

TEST_F(GetULongTest_1137, BigEndianHandlesHighBitWithoutSignExtension_1137) {
  const Exiv2::byte buf[4] = {0x80, 0x00, 0x00, 0x00};

  const uint32_t v = Exiv2::getULong(buf, Exiv2::bigEndian);

  EXPECT_EQ(v, 0x80000000u);
}

TEST_F(GetULongTest_1137, DifferentByteOrdersProduceDifferentValuesForNonPalindromicBytes_1137) {
  // Not symmetric: expected to differ between endianness.
  const Exiv2::byte buf[4] = {0x10, 0x20, 0x30, 0x40};

  const uint32_t le = Exiv2::getULong(buf, Exiv2::littleEndian);
  const uint32_t be = Exiv2::getULong(buf, Exiv2::bigEndian);

  EXPECT_NE(le, be);
  EXPECT_EQ(le, 0x40302010u);
  EXPECT_EQ(be, 0x10203040u);
}

// "Exceptional" / error-adjacent case (observable): invalidByteOrder is part of the public enum.
// The implementation (black box) appears to treat any non-littleEndian as big-endian.
// We only assert what is observable for this input via the interface.
TEST_F(GetULongTest_1137, InvalidByteOrderBehavesConsistentlyWithNonLittleEndianPath_1137) {
  const Exiv2::byte buf[4] = {0xDE, 0xAD, 0xBE, 0xEF};

  const uint32_t invalid = Exiv2::getULong(buf, Exiv2::invalidByteOrder);
  const uint32_t big = Exiv2::getULong(buf, Exiv2::bigEndian);

  // Observable behavior: invalidByteOrder yields same result as bigEndian for this buffer.
  EXPECT_EQ(invalid, big);
  EXPECT_EQ(invalid, 0xDEADBEEFu);
}

}  // namespace