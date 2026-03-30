// =================================================================================================
// TEST_ID: 1119
// Unit tests for Exiv2::DataBuf::write_uint8 (black-box via public interface)
// File under test (partial): ./TestProjects/exiv2/src/types.cpp
// Dependency header: exiv2/types.hpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "exiv2/types.hpp"

namespace {

class DataBufWriteUInt8Test_1119 : public ::testing::Test {};

TEST_F(DataBufWriteUInt8Test_1119, WriteAtZeroOffsetUpdatesReadBack_1119) {
  Exiv2::DataBuf buf(4);

  buf.write_uint8(0, static_cast<uint8_t>(0x12));

  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>(0x12));
}

TEST_F(DataBufWriteUInt8Test_1119, WriteAtLastValidOffsetUpdatesReadBack_1119) {
  Exiv2::DataBuf buf(4);
  const std::size_t last = buf.size() - 1;

  buf.write_uint8(last, static_cast<uint8_t>(0xAB));

  EXPECT_EQ(buf.read_uint8(last), static_cast<uint8_t>(0xAB));
}

TEST_F(DataBufWriteUInt8Test_1119, OverwriteSameOffsetKeepsLatestValue_1119) {
  Exiv2::DataBuf buf(2);

  buf.write_uint8(1, static_cast<uint8_t>(0x01));
  buf.write_uint8(1, static_cast<uint8_t>(0xFE));

  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>(0xFE));
}

TEST_F(DataBufWriteUInt8Test_1119, WritesDoNotAffectOtherOffsets_1119) {
  Exiv2::DataBuf buf(3);

  buf.write_uint8(0, static_cast<uint8_t>(0x10));
  buf.write_uint8(2, static_cast<uint8_t>(0x20));

  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>(0x10));
  EXPECT_EQ(buf.read_uint8(2), static_cast<uint8_t>(0x20));

  // Middle byte should remain whatever default state is; we only assert it is NOT forced to either
  // of the written values by the other writes.
  EXPECT_NE(buf.read_uint8(1), static_cast<uint8_t>(0x10));
  EXPECT_NE(buf.read_uint8(1), static_cast<uint8_t>(0x20));
}

TEST_F(DataBufWriteUInt8Test_1119, WriteOnEmptyBufferAtOffsetZeroThrowsOutOfRange_1119) {
  Exiv2::DataBuf buf;  // default constructed, should be empty

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  EXPECT_THROW(buf.write_uint8(0, static_cast<uint8_t>(0x00)), std::out_of_range);
}

TEST_F(DataBufWriteUInt8Test_1119, WriteAtOffsetEqualToSizeThrowsOutOfRange_1119) {
  Exiv2::DataBuf buf(5);
  const std::size_t off = buf.size();  // one past last valid index

  EXPECT_THROW(buf.write_uint8(off, static_cast<uint8_t>(0x7F)), std::out_of_range);
}

TEST_F(DataBufWriteUInt8Test_1119, WriteAtOffsetGreaterThanSizeThrowsOutOfRange_1119) {
  Exiv2::DataBuf buf(1);

  EXPECT_THROW(buf.write_uint8(buf.size() + 10u, static_cast<uint8_t>(0x7F)), std::out_of_range);
}

TEST_F(DataBufWriteUInt8Test_1119, BoundaryWriteThenOutOfRangeWritePreservesPreviousData_1119) {
  Exiv2::DataBuf buf(2);

  buf.write_uint8(0, static_cast<uint8_t>(0xAA));
  buf.write_uint8(1, static_cast<uint8_t>(0xBB));

  EXPECT_THROW(buf.write_uint8(2, static_cast<uint8_t>(0xCC)), std::out_of_range);

  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>(0xAA));
  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>(0xBB));
}

}  // namespace