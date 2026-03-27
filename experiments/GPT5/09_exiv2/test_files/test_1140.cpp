// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 1140
//
// Unit tests for Exiv2::getShort(const Exiv2::byte* buf, Exiv2::ByteOrder byteOrder)
//
// Constraints notes:
// - Treat as black box: we only validate observable return values for given inputs.
// - No private/internal state access (none applicable here).
// - Boundary + error-ish inputs (null buffer) are exercised only where behavior is observable
//   without invoking undefined behavior (so we avoid passing nullptr).

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "exiv2/types.hpp"

namespace {

class GetShortTest_1140 : public ::testing::Test {};

TEST_F(GetShortTest_1140, LittleEndian_InterpretsTwoBytes_1140) {
  const Exiv2::byte buf[] = {0x34, 0x12};  // little-endian => 0x1234
  const int16_t v = Exiv2::getShort(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, static_cast<int16_t>(0x1234));
}

TEST_F(GetShortTest_1140, BigEndian_InterpretsTwoBytes_1140) {
  const Exiv2::byte buf[] = {0x12, 0x34};  // big-endian => 0x1234
  const int16_t v = Exiv2::getShort(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, static_cast<int16_t>(0x1234));
}

TEST_F(GetShortTest_1140, LittleEndian_ZeroValue_1140) {
  const Exiv2::byte buf[] = {0x00, 0x00};
  EXPECT_EQ(Exiv2::getShort(buf, Exiv2::littleEndian), static_cast<int16_t>(0));
}

TEST_F(GetShortTest_1140, BigEndian_ZeroValue_1140) {
  const Exiv2::byte buf[] = {0x00, 0x00};
  EXPECT_EQ(Exiv2::getShort(buf, Exiv2::bigEndian), static_cast<int16_t>(0));
}

TEST_F(GetShortTest_1140, LittleEndian_MaxPositiveInt16_1140) {
  // 0x7FFF => 32767
  const Exiv2::byte buf[] = {0xFF, 0x7F};
  const int16_t v = Exiv2::getShort(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, std::numeric_limits<int16_t>::max());
}

TEST_F(GetShortTest_1140, BigEndian_MaxPositiveInt16_1140) {
  // 0x7FFF => 32767
  const Exiv2::byte buf[] = {0x7F, 0xFF};
  const int16_t v = Exiv2::getShort(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, std::numeric_limits<int16_t>::max());
}

TEST_F(GetShortTest_1140, LittleEndian_MinInt16_TwoComplement_1140) {
  // 0x8000 => -32768 for int16_t
  const Exiv2::byte buf[] = {0x00, 0x80};
  const int16_t v = Exiv2::getShort(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, std::numeric_limits<int16_t>::min());
}

TEST_F(GetShortTest_1140, BigEndian_MinInt16_TwoComplement_1140) {
  // 0x8000 => -32768 for int16_t
  const Exiv2::byte buf[] = {0x80, 0x00};
  const int16_t v = Exiv2::getShort(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, std::numeric_limits<int16_t>::min());
}

TEST_F(GetShortTest_1140, LittleEndian_0xFFFF_YieldsMinusOne_1140) {
  const Exiv2::byte buf[] = {0xFF, 0xFF};
  const int16_t v = Exiv2::getShort(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, static_cast<int16_t>(-1));
}

TEST_F(GetShortTest_1140, BigEndian_0xFFFF_YieldsMinusOne_1140) {
  const Exiv2::byte buf[] = {0xFF, 0xFF};
  const int16_t v = Exiv2::getShort(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, static_cast<int16_t>(-1));
}

TEST_F(GetShortTest_1140, InvalidByteOrder_TreatedAsBigEndian_1140) {
  // Observable behavior: for "invalidByteOrder" (and any non-littleEndian value),
  // function returns big-endian interpretation per current implementation.
  const Exiv2::byte buf[] = {0x12, 0x34};  // big-endian => 0x1234
  const int16_t v = Exiv2::getShort(buf, Exiv2::invalidByteOrder);
  EXPECT_EQ(v, static_cast<int16_t>(0x1234));
}

TEST_F(GetShortTest_1140, UnknownByteOrderValue_TreatedAsBigEndian_1140) {
  const Exiv2::byte buf[] = {0x01, 0x02};  // big-endian => 0x0102
  const int16_t v = Exiv2::getShort(buf, static_cast<Exiv2::ByteOrder>(99));
  EXPECT_EQ(v, static_cast<int16_t>(0x0102));
}

}  // namespace