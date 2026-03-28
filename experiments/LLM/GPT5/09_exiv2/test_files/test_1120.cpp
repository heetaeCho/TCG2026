// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::DataBuf::read_uint16
// File: test_types_databuf_read_uint16_1120.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "exiv2/types.hpp"

namespace {

class DataBufReadUint16Test_1120 : public ::testing::Test {};

TEST_F(DataBufReadUint16Test_1120, ReadsValueWrittenLittleEndian_1120) {
  Exiv2::DataBuf buf(2);
  const uint16_t v = 0x1234;

  buf.write_uint16(0, v, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint16(0, Exiv2::littleEndian), v);
}

TEST_F(DataBufReadUint16Test_1120, ReadsValueWrittenBigEndian_1120) {
  Exiv2::DataBuf buf(2);
  const uint16_t v = 0xBEEF;

  buf.write_uint16(0, v, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint16(0, Exiv2::bigEndian), v);
}

TEST_F(DataBufReadUint16Test_1120, ReadsAtNonZeroOffsetWithinBounds_1120) {
  Exiv2::DataBuf buf(4);

  const uint16_t v0 = 0x0102;
  const uint16_t v1 = 0xA1B2;

  buf.write_uint16(0, v0, Exiv2::littleEndian);
  buf.write_uint16(2, v1, Exiv2::littleEndian);

  EXPECT_EQ(buf.read_uint16(0, Exiv2::littleEndian), v0);
  EXPECT_EQ(buf.read_uint16(2, Exiv2::littleEndian), v1);
}

TEST_F(DataBufReadUint16Test_1120, BoundaryOffsetAtSizeMinus2IsAllowed_1120) {
  Exiv2::DataBuf buf(6);
  const uint16_t v = 0x0F0E;

  // Last valid offset for a uint16 read is size-2.
  const std::size_t lastValidOffset = buf.size() - 2;
  buf.write_uint16(lastValidOffset, v, Exiv2::bigEndian);

  EXPECT_EQ(buf.read_uint16(lastValidOffset, Exiv2::bigEndian), v);
}

TEST_F(DataBufReadUint16Test_1120, ThrowsOutOfRangeWhenBufferIsEmpty_1120) {
  Exiv2::DataBuf buf; // default constructed, expected to be empty
  EXPECT_THROW((void)buf.read_uint16(0, Exiv2::littleEndian), std::out_of_range);
}

TEST_F(DataBufReadUint16Test_1120, ThrowsOutOfRangeWhenBufferHasOnlyOneByte_1120) {
  Exiv2::DataBuf buf(1);
  EXPECT_THROW((void)buf.read_uint16(0, Exiv2::littleEndian), std::out_of_range);
}

TEST_F(DataBufReadUint16Test_1120, ThrowsOutOfRangeWhenOffsetIsSizeMinus1_1120) {
  Exiv2::DataBuf buf(2);
  // For size==2, only offset 0 is valid; offset 1 must throw.
  EXPECT_THROW((void)buf.read_uint16(1, Exiv2::littleEndian), std::out_of_range);
}

TEST_F(DataBufReadUint16Test_1120, ThrowsOutOfRangeWhenOffsetExceedsSizeMinus2_1120) {
  Exiv2::DataBuf buf(5);
  // Valid offsets are 0..3 (size-2). Offset 4 must throw.
  EXPECT_THROW((void)buf.read_uint16(4, Exiv2::bigEndian), std::out_of_range);
}

TEST_F(DataBufReadUint16Test_1120, ThrowsOutOfRangeForVeryLargeOffset_1120) {
  Exiv2::DataBuf buf(10);
  const std::size_t hugeOffset = static_cast<std::size_t>(-1); // SIZE_MAX
  EXPECT_THROW((void)buf.read_uint16(hugeOffset, Exiv2::littleEndian), std::out_of_range);
}

}  // namespace