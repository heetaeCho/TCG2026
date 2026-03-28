// File: util/coding_putfixed32_test.cc

#include <gtest/gtest.h>
#include <string>
#include <cstdint>

// LevelDB headers
#include "util/coding.h"   // Declares EncodeFixed32/DecodeFixed32/PutFixed32

namespace leveldb {

namespace {

// Helper to decode a uint32_t from a specific offset in std::string using the
// public decoding function (no internal re-implementation).
static uint32_t DecodeAt(const std::string& s, size_t offset) {
  // The interface of DecodeFixed32 reads from const char*.
  return DecodeFixed32(s.data() + offset);
}

// 1) Normal operation: appending to an empty string grows by 4 and decodes back.
TEST(PutFixed32Test_438, AppendsToEmptyAndDecodes_438) {
  std::string dst;
  const uint32_t v = 0x01020304u;

  ASSERT_EQ(dst.size(), 0u);
  PutFixed32(&dst, v);

  EXPECT_EQ(dst.size(), sizeof(uint32_t));
  EXPECT_EQ(DecodeAt(dst, 0), v);
}

// 2) Boundary condition: existing prefix remains intact after append.
TEST(PutFixed32Test_438, PreservesExistingPrefix_438) {
  std::string dst = "abc";  // arbitrary existing content
  const size_t before_size = dst.size();
  const uint32_t v = 1234567890u;

  PutFixed32(&dst, v);

  // Prefix unchanged
  EXPECT_EQ(dst.substr(0, before_size), std::string("abc"));
  // Size increased by exactly 4
  EXPECT_EQ(dst.size(), before_size + sizeof(uint32_t));
  // Appended value decodes correctly at the correct offset
  EXPECT_EQ(DecodeAt(dst, before_size), v);
}

// 3) Multiple appends: verify order and cumulative size increases.
TEST(PutFixed32Test_438, MultipleAppendsMaintainOrder_438) {
  std::string dst;
  const uint32_t v1 = 0u;
  const uint32_t v2 = 0xFFFFFFFFu;
  const uint32_t v3 = 42u;

  PutFixed32(&dst, v1);
  PutFixed32(&dst, v2);
  PutFixed32(&dst, v3);

  ASSERT_EQ(dst.size(), 3 * sizeof(uint32_t));
  EXPECT_EQ(DecodeAt(dst, 0 * sizeof(uint32_t)), v1);
  EXPECT_EQ(DecodeAt(dst, 1 * sizeof(uint32_t)), v2);
  EXPECT_EQ(DecodeAt(dst, 2 * sizeof(uint32_t)), v3);
}

// 4) Boundary values: 0 and UINT32_MAX encode/decode round-trip.
TEST(PutFixed32Test_438, EncodesBoundaryValues_438) {
  std::string dst;

  const uint32_t v_min = 0u;
  const uint32_t v_max = std::numeric_limits<uint32_t>::max();

  PutFixed32(&dst, v_min);
  PutFixed32(&dst, v_max);

  ASSERT_EQ(dst.size(), 2 * sizeof(uint32_t));
  EXPECT_EQ(DecodeAt(dst, 0), v_min);
  EXPECT_EQ(DecodeAt(dst, sizeof(uint32_t)), v_max);
}

// 5) Size accounting: appending N times grows by 4*N regardless of prior content.
TEST(PutFixed32Test_438, SizeGrowsByFourPerAppend_438) {
  std::string dst = "prefix";
  const size_t base = dst.size();

  // Append five arbitrary values
  PutFixed32(&dst, 11u);
  PutFixed32(&dst, 22u);
  PutFixed32(&dst, 33u);
  PutFixed32(&dst, 44u);
  PutFixed32(&dst, 55u);

  EXPECT_EQ(dst.substr(0, base), std::string("prefix"));
  EXPECT_EQ(dst.size(), base + 5 * sizeof(uint32_t));

  // Spot-check a couple of positions to ensure data landed where expected
  EXPECT_EQ(DecodeAt(dst, base + 0 * sizeof(uint32_t)), 11u);
  EXPECT_EQ(DecodeAt(dst, base + 4 * sizeof(uint32_t)), 55u);
}

}  // namespace
}  // namespace leveldb
