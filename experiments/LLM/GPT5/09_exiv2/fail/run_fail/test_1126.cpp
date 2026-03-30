// =================================================================================================
// TEST_ID: 1126
// File: test_databuf_cmpbytes_1126.cpp
// Unit tests for Exiv2::DataBuf::cmpBytes (black-box; observable behavior only)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "exiv2/types.hpp"

namespace {

class DataBufCmpBytesTest_1126 : public ::testing::Test {};

TEST_F(DataBufCmpBytesTest_1126, ReturnsZeroWhenBytesMatch_1126) {
  const uint8_t src[] = {0x10, 0x20, 0x30, 0x40, 0x50};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  const uint8_t needle[] = {0x30, 0x40};
  const int r = dbuf.cmpBytes(/*offset=*/2, needle, sizeof(needle));

  EXPECT_EQ(r, 0);
}

TEST_F(DataBufCmpBytesTest_1126, ReturnsNonZeroWhenBytesDiffer_1126) {
  const uint8_t src[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  const uint8_t needle[] = {0x03, 0x05};  // differs at second byte
  const int r = dbuf.cmpBytes(/*offset=*/2, needle, sizeof(needle));

  EXPECT_NE(r, 0);
}

TEST_F(DataBufCmpBytesTest_1126, ComparesCorrectRegionUsingOffset_1126) {
  // Same needle appears at two different locations; ensure offset selects region.
  const uint8_t src[] = {0xAA, 0xBB, 0x01, 0x02, 0xCC, 0x01, 0x02, 0xDD};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  const uint8_t needle[] = {0x01, 0x02};

  EXPECT_EQ(dbuf.cmpBytes(/*offset=*/2, needle, sizeof(needle)), 0);
  EXPECT_EQ(dbuf.cmpBytes(/*offset=*/5, needle, sizeof(needle)), 0);

  const uint8_t other[] = {0xBB, 0x01};
  EXPECT_EQ(dbuf.cmpBytes(/*offset=*/1, other, sizeof(other)), 0);
}

TEST_F(DataBufCmpBytesTest_1126, AllowsComparisonExactlyAtEndBoundary_1126) {
  const uint8_t src[] = {0xDE, 0xAD, 0xBE, 0xEF};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  // offset == size - bufsize is the last valid start position.
  const uint8_t needle[] = {0xBE, 0xEF};
  EXPECT_EQ(dbuf.cmpBytes(/*offset=*/2, needle, sizeof(needle)), 0);
}

TEST_F(DataBufCmpBytesTest_1126, ThrowsOutOfRangeWhenBufsizeExceedsDataSize_1126) {
  const uint8_t src[] = {0x11, 0x22, 0x33};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  const uint8_t needle[] = {0x11, 0x22, 0x33, 0x44};

  EXPECT_THROW((void)dbuf.cmpBytes(/*offset=*/0, needle, sizeof(needle)), std::out_of_range);
}

TEST_F(DataBufCmpBytesTest_1126, ThrowsOutOfRangeWhenOffsetWouldOverflowRange_1126) {
  const uint8_t src[] = {0x01, 0x02, 0x03};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  const uint8_t needle[] = {0x03};  // bufsize=1

  // offset == size is beyond last byte -> invalid (would make offset > size - bufsize).
  EXPECT_THROW((void)dbuf.cmpBytes(/*offset=*/3, needle, sizeof(needle)), std::out_of_range);

  // Another overflow case: offset too large for bufsize 2.
  const uint8_t needle2[] = {0x02, 0x03};
  EXPECT_THROW((void)dbuf.cmpBytes(/*offset=*/2, needle2, sizeof(needle2)), std::out_of_range);
}

TEST_F(DataBufCmpBytesTest_1126, ZeroLengthComparisonAtStartReturnsZero_1126) {
  const uint8_t src[] = {0xAA, 0xBB};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  // For memcmp with size 0, result is 0. Provide a non-null pointer.
  const uint8_t dummy = 0x00;
  EXPECT_EQ(dbuf.cmpBytes(/*offset=*/0, &dummy, /*bufsize=*/0), 0);
}

TEST_F(DataBufCmpBytesTest_1126, ZeroLengthComparisonAtEndBoundaryReturnsZero_1126) {
  const uint8_t src[] = {0xAA, 0xBB};
  Exiv2::DataBuf dbuf(src, sizeof(src));

  // With bufsize==0, offset == size should be accepted (no bytes accessed).
  const uint8_t dummy = 0x00;
  EXPECT_EQ(dbuf.cmpBytes(/*offset=*/dbuf.size(), &dummy, /*bufsize=*/0), 0);
}

TEST_F(DataBufCmpBytesTest_1126, EmptyDataBufZeroLengthAtZeroReturnsZero_1126) {
  Exiv2::DataBuf dbuf;  // default-constructed; expected empty buffer.

  const uint8_t dummy = 0x00;
  EXPECT_EQ(dbuf.cmpBytes(/*offset=*/0, &dummy, /*bufsize=*/0), 0);
}

TEST_F(DataBufCmpBytesTest_1126, EmptyDataBufNonZeroLengthThrowsOutOfRange_1126) {
  Exiv2::DataBuf dbuf;  // empty

  const uint8_t needle[] = {0x00};
  EXPECT_THROW((void)dbuf.cmpBytes(/*offset=*/0, needle, sizeof(needle)), std::out_of_range);
}

}  // namespace