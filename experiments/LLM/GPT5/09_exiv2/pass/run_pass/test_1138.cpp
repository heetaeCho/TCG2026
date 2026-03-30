// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1138
//
// Unit tests for Exiv2::getULongLong (./TestProjects/exiv2/src/types.cpp)
//
// Constraints note:
// - Treat implementation as a black box: tests validate observable outputs only.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "exiv2/types.hpp"

namespace {

// Keep fixture name aligned with TEST_ID requirement.
class GetULongLongTest_1138 : public ::testing::Test {};

TEST_F(GetULongLongTest_1138, LittleEndian_ZeroBufferReturnsZero_1138) {
  const Exiv2::byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, 0ULL);
}

TEST_F(GetULongLongTest_1138, BigEndian_ZeroBufferReturnsZero_1138) {
  const Exiv2::byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, 0ULL);
}

TEST_F(GetULongLongTest_1138, LittleEndian_KnownPatternAssemblesCorrectly_1138) {
  // For little-endian, buf[0] is least significant byte.
  const Exiv2::byte buf[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, 0xEFCDAB8967452301ULL);
}

TEST_F(GetULongLongTest_1138, BigEndian_KnownPatternAssemblesCorrectly_1138) {
  // For big-endian, buf[0] is most significant byte.
  const Exiv2::byte buf[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, 0x0123456789ABCDEFULL);
}

TEST_F(GetULongLongTest_1138, DifferentByteOrdersProduceDifferentValuesForNonSymmetricBuffer_1138) {
  const Exiv2::byte buf[8] = {0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  const uint64_t le = Exiv2::getULongLong(buf, Exiv2::littleEndian);
  const uint64_t be = Exiv2::getULongLong(buf, Exiv2::bigEndian);

  EXPECT_NE(le, be);
  EXPECT_EQ(le, 0x0000000000000010ULL);
  EXPECT_EQ(be, 0x1000000000000000ULL);
}

TEST_F(GetULongLongTest_1138, LittleEndian_AllFFReturnsMax_1138) {
  const Exiv2::byte buf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, std::numeric_limits<uint64_t>::max());
}

TEST_F(GetULongLongTest_1138, BigEndian_AllFFReturnsMax_1138) {
  const Exiv2::byte buf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, std::numeric_limits<uint64_t>::max());
}

TEST_F(GetULongLongTest_1138, BigEndian_SingleLowBitInLastByte_1138) {
  // Boundary-ish: exercise least significant bit in big-endian (buf[7]).
  const Exiv2::byte buf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::bigEndian);
  EXPECT_EQ(v, 0x0000000000000001ULL);
}

TEST_F(GetULongLongTest_1138, LittleEndian_SingleHighBitInLastByte_1138) {
  // Boundary-ish: exercise most significant bit position in little-endian (buf[7] contributes to top byte).
  const Exiv2::byte buf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
  const uint64_t v = Exiv2::getULongLong(buf, Exiv2::littleEndian);
  EXPECT_EQ(v, 0x8000000000000000ULL);
}

TEST_F(GetULongLongTest_1138, InvalidByteOrder_TreatedAsBigEndianObservableMapping_1138) {
  // Exceptional/error case (observable): invalidByteOrder takes the non-littleEndian path.
  // We only assert the observable output relationship for the provided enum values.
  const Exiv2::byte buf[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED, 0xFA, 0xCE};

  const uint64_t invalid = Exiv2::getULongLong(buf, Exiv2::invalidByteOrder);
  const uint64_t big = Exiv2::getULongLong(buf, Exiv2::bigEndian);

  EXPECT_EQ(invalid, big);
  EXPECT_EQ(big, 0xDEADBEEFFEEDFACEULL);
}

}  // namespace