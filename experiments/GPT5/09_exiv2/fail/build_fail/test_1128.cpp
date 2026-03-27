// ============================================================================
// TEST_ID: 1128
// File: test_databuf_c_data_1128.cpp
// Target: Exiv2::DataBuf::c_data(size_t offset) const
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "exiv2/types.hpp"

namespace {

// A small helper to build deterministic data.
static std::vector<Exiv2::byte> MakeBytes(std::initializer_list<uint8_t> xs) {
  std::vector<Exiv2::byte> out;
  out.reserve(xs.size());
  for (auto v : xs) out.push_back(static_cast<Exiv2::byte>(v));
  return out;
}

class DataBufCDataTest_1128 : public ::testing::Test {};

TEST_F(DataBufCDataTest_1128, DefaultConstructedIsEmptyAndReturnsNullAtZero_1128) {
  const Exiv2::DataBuf buf;  // default ctor
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  // Observable behavior: empty => nullptr
  EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST_F(DataBufCDataTest_1128, EmptyExplicitSizeZeroReturnsNullAtZero_1128) {
  const Exiv2::DataBuf buf(static_cast<size_t>(0));
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST_F(DataBufCDataTest_1128, NonEmptyOffsetZeroReturnsNonNullPointer_1128) {
  const Exiv2::DataBuf buf(static_cast<size_t>(3));
  ASSERT_FALSE(buf.empty());
  ASSERT_EQ(buf.size(), 3u);

  const Exiv2::byte* p = buf.c_data(0);
  EXPECT_NE(p, nullptr);
}

TEST_F(DataBufCDataTest_1128, NonEmptyOffsetSizeReturnsNullPointer_1128) {
  const Exiv2::DataBuf buf(static_cast<size_t>(3));
  ASSERT_EQ(buf.size(), 3u);

  // Observable behavior: offset == size => nullptr
  EXPECT_EQ(buf.c_data(buf.size()), nullptr);
}

TEST_F(DataBufCDataTest_1128, OffsetWithinRangeReturnsPointerAndMatchesDataOffset_1128) {
  // Use constructor from raw bytes to make contents deterministic.
  const auto bytes = MakeBytes({0x10, 0x20, 0x30, 0x40});
  const Exiv2::DataBuf buf(bytes.data(), bytes.size());
  ASSERT_EQ(buf.size(), bytes.size());

  // data(0) should point to the first byte; c_data(2) should be data(0)+2.
  Exiv2::byte* d0 = buf.data(0);
  ASSERT_NE(d0, nullptr);

  const Exiv2::byte* c2 = buf.c_data(2);
  ASSERT_NE(c2, nullptr);

  // Pointer arithmetic is observable via public API.
  EXPECT_EQ(c2, d0 + 2);

  // Also verify the dereferenced value matches known input (still observable).
  EXPECT_EQ(static_cast<uint8_t>(*c2), 0x30);
}

TEST_F(DataBufCDataTest_1128, OffsetGreaterThanSizeThrowsOutOfRange_1128) {
  const Exiv2::DataBuf buf(static_cast<size_t>(3));
  ASSERT_EQ(buf.size(), 3u);

  EXPECT_THROW((void)buf.c_data(buf.size() + 1), std::out_of_range);
}

TEST_F(DataBufCDataTest_1128, BoundaryOffsetSizeMinusOneReturnsNonNullWhenSizeNonZero_1128) {
  const Exiv2::DataBuf buf(static_cast<size_t>(1));
  ASSERT_EQ(buf.size(), 1u);

  const Exiv2::byte* p = buf.c_data(0);  // size-1
  EXPECT_NE(p, nullptr);
}

TEST_F(DataBufCDataTest_1128, AfterResizeToZeroCDataAtZeroReturnsNull_1128) {
  Exiv2::DataBuf buf(static_cast<size_t>(5));
  ASSERT_FALSE(buf.empty());

  buf.resize(0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST_F(DataBufCDataTest_1128, AfterResetCDataAtZeroReturnsNull_1128) {
  Exiv2::DataBuf buf(static_cast<size_t>(2));
  ASSERT_FALSE(buf.empty());

  buf.reset();
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST_F(DataBufCDataTest_1128, AllocThenCDataReflectsNewSizeBoundaries_1128) {
  Exiv2::DataBuf buf;  // empty
  ASSERT_TRUE(buf.empty());

  buf.alloc(4);
  ASSERT_EQ(buf.size(), 4u);
  ASSERT_FALSE(buf.empty());

  EXPECT_NE(buf.c_data(0), nullptr);
  EXPECT_EQ(buf.c_data(4), nullptr);
  EXPECT_THROW((void)buf.c_data(5), std::out_of_range);
}

}  // namespace