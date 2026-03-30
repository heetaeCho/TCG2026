// TEST_ID: 1115
//
// Unit tests for Exiv2::DataBuf::alloc(size_t)
//
// Constraints reminder:
// - Treat implementation as black box (no private state access)
// - Test only via public interface / observable behavior

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <iterator>

#include "exiv2/types.hpp"

namespace {

class DataBufTest_1115 : public ::testing::Test {};

TEST_F(DataBufTest_1115, DefaultConstructedIsEmpty_1115) {
  Exiv2::DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), static_cast<size_t>(0));
}

TEST_F(DataBufTest_1115, AllocZeroResultsInEmptyBuffer_1115) {
  Exiv2::DataBuf buf;
  buf.alloc(0);

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), static_cast<size_t>(0));
}

TEST_F(DataBufTest_1115, AllocNonZeroUpdatesSizeAndNotEmpty_1115) {
  Exiv2::DataBuf buf;
  buf.alloc(16);

  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), static_cast<size_t>(16));

  // Observable interaction: requesting pointers for valid offsets should be possible.
  // We do not assume content or null-termination; only that the call is valid.
  EXPECT_NE(buf.data(0), nullptr);
  EXPECT_NE(buf.c_data(0), nullptr);
  EXPECT_NE(buf.c_str(0), nullptr);
}

TEST_F(DataBufTest_1115, IteratorsCoverAllocatedSize_1115) {
  Exiv2::DataBuf buf;
  buf.alloc(10);

  const auto dist = static_cast<size_t>(std::distance(buf.begin(), buf.end()));
  EXPECT_EQ(dist, buf.size());
  EXPECT_EQ(dist, static_cast<size_t>(10));
}

TEST_F(DataBufTest_1115, InBoundsReadWriteUint8WorksAfterAlloc_1115) {
  Exiv2::DataBuf buf;
  buf.alloc(1);

  buf.write_uint8(0, 0xAB);
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>(0xAB));
}

TEST_F(DataBufTest_1115, ReAllocAllowsAccessAtNewEndBoundary_1115) {
  Exiv2::DataBuf buf;

  buf.alloc(8);
  EXPECT_EQ(buf.size(), static_cast<size_t>(8));

  // In-bounds writes at boundaries of the initial allocation.
  buf.write_uint8(0, 0x12);
  buf.write_uint8(7, 0x34);
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>(0x12));
  EXPECT_EQ(buf.read_uint8(7), static_cast<uint8_t>(0x34));

  // Re-allocate bigger: only check updated size and that new boundary is usable.
  buf.alloc(16);
  EXPECT_EQ(buf.size(), static_cast<size_t>(16));
  EXPECT_FALSE(buf.empty());

  buf.write_uint8(15, 0xCD);
  EXPECT_EQ(buf.read_uint8(15), static_cast<uint8_t>(0xCD));
}

}  // namespace