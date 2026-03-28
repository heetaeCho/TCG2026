// TEST_ID 1118
// Unit tests for Exiv2::DataBuf::read_uint8(size_t) based on provided interface.
// Constraints respected: black-box testing, only observable behavior via public API.

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <vector>

// Exiv2 public header
#include "exiv2/types.hpp"

namespace {

// Use a dedicated fixture name that includes the TEST_ID.
class DataBufReadUint8Test_1118 : public ::testing::Test {};

TEST_F(DataBufReadUint8Test_1118, ReadUint8FromNonEmptyBuffer_ReturnsExpectedValue_1118) {
  const Exiv2::byte src[] = {0x00, 0x7f, 0x80, 0xff};
  Exiv2::DataBuf buf(src, sizeof(src));

  EXPECT_EQ(buf.read_uint8(0), 0x00u);
  EXPECT_EQ(buf.read_uint8(1), 0x7fu);
  EXPECT_EQ(buf.read_uint8(2), 0x80u);
  EXPECT_EQ(buf.read_uint8(3), 0xffu);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8AtLastValidOffset_ReturnsExpectedValue_1118) {
  const Exiv2::byte src[] = {0x12, 0x34, 0x56};
  Exiv2::DataBuf buf(src, sizeof(src));

  ASSERT_EQ(buf.size(), sizeof(src));
  EXPECT_EQ(buf.read_uint8(buf.size() - 1), 0x56u);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8FromEmptyBuffer_ThrowsOutOfRange_1118) {
  Exiv2::DataBuf buf;  // default-constructed; expected to be empty per interface (size()/empty()).

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  EXPECT_THROW((void)buf.read_uint8(0), std::out_of_range);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8AtSizeOffset_ThrowsOutOfRange_1118) {
  const Exiv2::byte src[] = {0xaa, 0xbb};
  Exiv2::DataBuf buf(src, sizeof(src));

  ASSERT_EQ(buf.size(), sizeof(src));

  // Boundary: offset == size() is out of range.
  EXPECT_THROW((void)buf.read_uint8(buf.size()), std::out_of_range);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8WithVeryLargeOffset_ThrowsOutOfRange_1118) {
  const Exiv2::byte src[] = {0x01};
  Exiv2::DataBuf buf(src, sizeof(src));

  // Extreme boundary: huge offset should be out of range.
  EXPECT_THROW((void)buf.read_uint8(std::numeric_limits<size_t>::max()), std::out_of_range);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8AfterReset_ThrowsOutOfRange_1118) {
  const Exiv2::byte src[] = {0xde, 0xad, 0xbe, 0xef};
  Exiv2::DataBuf buf(src, sizeof(src));

  ASSERT_FALSE(buf.empty());
  ASSERT_GT(buf.size(), 0u);

  buf.reset();

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  EXPECT_THROW((void)buf.read_uint8(0), std::out_of_range);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8AfterResizeSmaller_OutOfRangeForTruncatedOffset_1118) {
  const Exiv2::byte src[] = {0x10, 0x20, 0x30, 0x40};
  Exiv2::DataBuf buf(src, sizeof(src));

  ASSERT_EQ(buf.size(), 4u);
  EXPECT_EQ(buf.read_uint8(3), 0x40u);  // last valid before resize

  buf.resize(2);

  ASSERT_EQ(buf.size(), 2u);
  EXPECT_EQ(buf.read_uint8(0), 0x10u);
  EXPECT_EQ(buf.read_uint8(1), 0x20u);

  // Now previously-valid offset should be out of range.
  EXPECT_THROW((void)buf.read_uint8(2), std::out_of_range);
  EXPECT_THROW((void)buf.read_uint8(3), std::out_of_range);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8AfterAllocAndWrite_CanReadBackWrittenValue_1118) {
  Exiv2::DataBuf buf;
  buf.alloc(3);

  ASSERT_EQ(buf.size(), 3u);

  buf.write_uint8(0, 0x9au);
  buf.write_uint8(1, 0xbbu);
  buf.write_uint8(2, 0xccu);

  EXPECT_EQ(buf.read_uint8(0), 0x9au);
  EXPECT_EQ(buf.read_uint8(1), 0xbbu);
  EXPECT_EQ(buf.read_uint8(2), 0xccu);
}

TEST_F(DataBufReadUint8Test_1118, ReadUint8DoesNotMutateBuffer_ReadSameOffsetTwiceSameValue_1118) {
  const Exiv2::byte src[] = {0x5a, 0xa5};
  Exiv2::DataBuf buf(src, sizeof(src));

  const auto v1 = buf.read_uint8(1);
  const auto v2 = buf.read_uint8(1);

  EXPECT_EQ(v1, 0xa5u);
  EXPECT_EQ(v2, 0xa5u);
}

}  // namespace