// ============================================================================
// TEST_ID: 1117
// File: test_types_databuf_reset_1117.cpp
// Unit tests for Exiv2::DataBuf::reset()
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

// Exiv2 headers
#include "exiv2/types.hpp"

namespace {

// A small helper to create deterministic content.
static std::vector<Exiv2::byte> MakePattern(size_t n) {
  std::vector<Exiv2::byte> v;
  v.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    v.push_back(static_cast<Exiv2::byte>(i & 0xFF));
  }
  return v;
}

class DataBufResetTest_1117 : public ::testing::Test {};

}  // namespace

// Normal operation: reset clears a non-empty buffer.
TEST_F(DataBufResetTest_1117, ResetClearsNonEmptyBuffer_1117) {
  const auto pattern = MakePattern(8);

  Exiv2::DataBuf buf(pattern.data(), pattern.size());
  ASSERT_FALSE(buf.empty());
  ASSERT_EQ(buf.size(), pattern.size());

  buf.reset();

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(buf.begin(), buf.end());
}

// Boundary: reset on a default-constructed (already empty) buffer.
TEST_F(DataBufResetTest_1117, ResetOnDefaultConstructedEmptyBufferKeepsEmpty_1117) {
  Exiv2::DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(buf.begin(), buf.end());

  buf.reset();

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(buf.begin(), buf.end());
}

// Boundary: reset on a zero-sized constructed buffer (explicit size ctor).
TEST_F(DataBufResetTest_1117, ResetOnZeroSizedConstructedBufferKeepsEmpty_1117) {
  Exiv2::DataBuf buf(static_cast<size_t>(0));
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);

  buf.reset();

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(buf.begin(), buf.end());
}

// Boundary: reset on a larger buffer.
TEST_F(DataBufResetTest_1117, ResetClearsLargeBuffer_1117) {
  const size_t kSize = 4096;
  const auto pattern = MakePattern(kSize);

  Exiv2::DataBuf buf(pattern.data(), pattern.size());
  ASSERT_FALSE(buf.empty());
  ASSERT_EQ(buf.size(), kSize);

  buf.reset();

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(buf.begin(), buf.end());
}

// Exceptional/error cases: not observable via interface for reset().
// Verify: reset() is idempotent (calling multiple times is safe/consistent).
TEST_F(DataBufResetTest_1117, ResetIsIdempotent_1117) {
  const auto pattern = MakePattern(16);

  Exiv2::DataBuf buf(pattern.data(), pattern.size());
  ASSERT_FALSE(buf.empty());
  ASSERT_EQ(buf.size(), pattern.size());

  buf.reset();
  ASSERT_TRUE(buf.empty());
  ASSERT_EQ(buf.size(), 0u);

  // Call again; should remain empty and stable.
  buf.reset();

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(buf.begin(), buf.end());
}

// Normal operation: after reset, buffer can be resized/used again.
TEST_F(DataBufResetTest_1117, ResetThenResizeAllowsReuse_1117) {
  const auto pattern = MakePattern(10);

  Exiv2::DataBuf buf(pattern.data(), pattern.size());
  ASSERT_EQ(buf.size(), pattern.size());

  buf.reset();
  ASSERT_TRUE(buf.empty());
  ASSERT_EQ(buf.size(), 0u);

  // Reuse via public API (resize). We only check observable size/emptiness.
  buf.resize(5);

  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_NE(buf.begin(), buf.end());
}