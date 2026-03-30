// =================================================================================================
// TEST_ID: 1141
// File: test_types_getLong_1141.cpp
//
// Unit tests for Exiv2::getLong(const byte* buf, ByteOrder byteOrder)
//
// Constraints honored:
//  - Treat implementation as a black box: tests assert only observable outputs from the public API.
//  - No private state access.
//  - Cover normal, boundary, and error-ish/exceptional (observable) cases.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "exiv2/types.hpp"  // Exiv2::ByteOrder, Exiv2::getLong, Exiv2::byte (as provided by Exiv2)

namespace {

class GetLongTest_1141 : public ::testing::Test {};

TEST_F(GetLongTest_1141, LittleEndian_CombinesBytesInLittleEndianOrder_1141) {
  const Exiv2::byte buf[4] = {0x78, 0x56, 0x34, 0x12};
  const int32_t v = Exiv2::getLong(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, static_cast<int32_t>(0x12345678));
}

TEST_F(GetLongTest_1141, BigEndian_CombinesBytesInBigEndianOrder_1141) {
  const Exiv2::byte buf[4] = {0x12, 0x34, 0x56, 0x78};
  const int32_t v = Exiv2::getLong(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, static_cast<int32_t>(0x12345678));
}

TEST_F(GetLongTest_1141, AllZeroBytes_ReturnsZeroForBothEndianness_1141) {
  const Exiv2::byte buf[4] = {0x00, 0x00, 0x00, 0x00};

  EXPECT_EQ(Exiv2::getLong(buf, Exiv2::littleEndian), 0);
  EXPECT_EQ(Exiv2::getLong(buf, Exiv2::bigEndian), 0);
}

TEST_F(GetLongTest_1141, AllFFBytes_ReturnsMinusOneForBothEndianness_1141) {
  const Exiv2::byte buf[4] = {0xFF, 0xFF, 0xFF, 0xFF};

  EXPECT_EQ(Exiv2::getLong(buf, Exiv2::littleEndian), static_cast<int32_t>(-1));
  EXPECT_EQ(Exiv2::getLong(buf, Exiv2::bigEndian), static_cast<int32_t>(-1));
}

TEST_F(GetLongTest_1141, HighestBitSet_BecomesNegativeInResult_1141) {
  // Value 0x80000000 as bytes in both endianness layouts.
  const Exiv2::byte le[4] = {0x00, 0x00, 0x00, 0x80};
  const Exiv2::byte be[4] = {0x80, 0x00, 0x00, 0x00};

  const int32_t vle = Exiv2::getLong(le, Exiv2::littleEndian);
  const int32_t vbe = Exiv2::getLong(be, Exiv2::bigEndian);

  EXPECT_EQ(vle, static_cast<int32_t>(0x80000000u));
  EXPECT_EQ(vbe, static_cast<int32_t>(0x80000000u));
  EXPECT_LT(vle, 0);
  EXPECT_LT(vbe, 0);
}

TEST_F(GetLongTest_1141, MaxSignedInt_ReturnsInt32Max_1141) {
  // 0x7FFFFFFF
  const Exiv2::byte le[4] = {0xFF, 0xFF, 0xFF, 0x7F};
  const Exiv2::byte be[4] = {0x7F, 0xFF, 0xFF, 0xFF};

  EXPECT_EQ(Exiv2::getLong(le, Exiv2::littleEndian), std::numeric_limits<int32_t>::max());
  EXPECT_EQ(Exiv2::getLong(be, Exiv2::bigEndian), std::numeric_limits<int32_t>::max());
}

TEST_F(GetLongTest_1141, MinSignedInt_ReturnsInt32Min_1141) {
  // 0x80000000
  const Exiv2::byte le[4] = {0x00, 0x00, 0x00, 0x80};
  const Exiv2::byte be[4] = {0x80, 0x00, 0x00, 0x00};

  EXPECT_EQ(Exiv2::getLong(le, Exiv2::littleEndian), std::numeric_limits<int32_t>::min());
  EXPECT_EQ(Exiv2::getLong(be, Exiv2::bigEndian), std::numeric_limits<int32_t>::min());
}

TEST_F(GetLongTest_1141, DifferentBuffersProduceDifferentResults_1141) {
  const Exiv2::byte a[4] = {0x01, 0x00, 0x00, 0x00};
  const Exiv2::byte b[4] = {0x02, 0x00, 0x00, 0x00};

  EXPECT_EQ(Exiv2::getLong(a, Exiv2::littleEndian), 1);
  EXPECT_EQ(Exiv2::getLong(b, Exiv2::littleEndian), 2);
  EXPECT_NE(Exiv2::getLong(a, Exiv2::littleEndian), Exiv2::getLong(b, Exiv2::littleEndian));
}

TEST_F(GetLongTest_1141, InvalidByteOrder_TreatedAsNonLittleEndianBranch_1141) {
  // Observable behavior: only special-cased byteOrder is littleEndian; others follow the "else" path.
  // Use a pattern where LE and BE interpretations differ.
  const Exiv2::byte buf[4] = {0x01, 0x02, 0x03, 0x04};

  const int32_t expected_big = Exiv2::getLong(buf, Exiv2::bigEndian);
  const int32_t expected_little = Exiv2::getLong(buf, Exiv2::littleEndian);
  ASSERT_NE(expected_big, expected_little);

  EXPECT_EQ(Exiv2::getLong(buf, Exiv2::invalidByteOrder), expected_big);
}

}  // namespace