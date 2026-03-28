// File: test_types_databuf_resize_1116.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/types.hpp"

namespace {

using Exiv2::DataBuf;

class DataBufResizeTest_1116 : public ::testing::Test {};

// Normal operation: default-constructed then resized to a non-zero size.
TEST_F(DataBufResizeTest_1116, ResizeFromDefaultToNonZero_1116) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  EXPECT_NO_THROW(buf.resize(8u));
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 8u);
}

// Boundary: resize to zero should result in empty buffer.
TEST_F(DataBufResizeTest_1116, ResizeToZeroMakesEmpty_1116) {
  DataBuf buf(10u);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 10u);

  EXPECT_NO_THROW(buf.resize(0u));
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// Boundary: resize to same size should keep size stable (observable behavior).
TEST_F(DataBufResizeTest_1116, ResizeToSameSizeKeepsSize_1116) {
  DataBuf buf(5u);
  ASSERT_EQ(buf.size(), 5u);

  EXPECT_NO_THROW(buf.resize(5u));
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_FALSE(buf.empty());
}

// Normal: growing then shrinking updates size accordingly.
TEST_F(DataBufResizeTest_1116, ResizeGrowThenShrinkUpdatesSize_1116) {
  DataBuf buf(3u);
  EXPECT_EQ(buf.size(), 3u);

  EXPECT_NO_THROW(buf.resize(12u));
  EXPECT_EQ(buf.size(), 12u);

  EXPECT_NO_THROW(buf.resize(4u));
  EXPECT_EQ(buf.size(), 4u);
}

// Normal: constructed from raw data; resize should still reflect requested size.
TEST_F(DataBufResizeTest_1116, ResizeAfterConstructFromDataUpdatesSize_1116) {
  const std::vector<Exiv2::byte> src = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(src.data(), src.size());
  EXPECT_EQ(buf.size(), src.size());
  EXPECT_FALSE(buf.empty());

  EXPECT_NO_THROW(buf.resize(7u));
  EXPECT_EQ(buf.size(), 7u);

  EXPECT_NO_THROW(buf.resize(2u));
  EXPECT_EQ(buf.size(), 2u);
}

// Boundary-ish: multiple sequential resizes should always match the last requested size.
TEST_F(DataBufResizeTest_1116, SequentialResizesTrackLastRequestedSize_1116) {
  DataBuf buf;
  EXPECT_EQ(buf.size(), 0u);

  const std::vector<size_t> sizes = {1u, 0u, 16u, 16u, 3u, 0u, 9u};
  for (size_t s : sizes) {
    EXPECT_NO_THROW(buf.resize(s));
    EXPECT_EQ(buf.size(), s);
    EXPECT_EQ(buf.empty(), s == 0u);
  }
}

}  // namespace