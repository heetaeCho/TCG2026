#include <string>
#include <cstdint>
#include <limits>

#include "gtest/gtest.h"
#include "util/coding.h"

namespace leveldb {

// Helper to decode a varint64 from a string for verification
// Using the existing GetVarint64 or decoding logic from coding.h
// We rely on the public decoding functions available in the interface.

class PutVarint64Test_443 : public ::testing::Test {
 protected:
  std::string dst_;
};

TEST_F(PutVarint64Test_443, ZeroValue_443) {
  PutVarint64(&dst_, 0);
  EXPECT_FALSE(dst_.empty());
  // Zero should encode in 1 byte (varint encoding)
  EXPECT_EQ(dst_.size(), 1u);
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, 0u);
}

TEST_F(PutVarint64Test_443, SmallValue_443) {
  PutVarint64(&dst_, 1);
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, 1u);
}

TEST_F(PutVarint64Test_443, MaxSingleByteValue_443) {
  // 127 is the max value that fits in a single varint byte
  PutVarint64(&dst_, 127);
  EXPECT_EQ(dst_.size(), 1u);
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, 127u);
}

TEST_F(PutVarint64Test_443, TwoByteValue_443) {
  // 128 requires 2 bytes in varint encoding
  PutVarint64(&dst_, 128);
  EXPECT_EQ(dst_.size(), 2u);
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, 128u);
}

TEST_F(PutVarint64Test_443, LargeValue_443) {
  uint64_t val = 123456789012345ULL;
  PutVarint64(&dst_, val);
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, val);
}

TEST_F(PutVarint64Test_443, MaxUint64Value_443) {
  uint64_t val = std::numeric_limits<uint64_t>::max();
  PutVarint64(&dst_, val);
  // Max uint64 should encode in 10 bytes
  EXPECT_EQ(dst_.size(), 10u);
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, val);
}

TEST_F(PutVarint64Test_443, AppendsToExistingString_443) {
  dst_ = "prefix";
  size_t original_size = dst_.size();
  PutVarint64(&dst_, 42);
  EXPECT_GT(dst_.size(), original_size);
  EXPECT_EQ(dst_.substr(0, original_size), "prefix");
  
  // Decode the varint from after the prefix
  Slice input(dst_.data() + original_size, dst_.size() - original_size);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, 42u);
}

TEST_F(PutVarint64Test_443, MultipleAppends_443) {
  PutVarint64(&dst_, 100);
  PutVarint64(&dst_, 200);
  PutVarint64(&dst_, 300);
  
  Slice input(dst_);
  uint64_t v1, v2, v3;
  EXPECT_TRUE(GetVarint64(&input, &v1));
  EXPECT_TRUE(GetVarint64(&input, &v2));
  EXPECT_TRUE(GetVarint64(&input, &v3));
  EXPECT_EQ(v1, 100u);
  EXPECT_EQ(v2, 200u);
  EXPECT_EQ(v3, 300u);
}

TEST_F(PutVarint64Test_443, PowersOfTwo_443) {
  for (int i = 0; i < 64; i++) {
    dst_.clear();
    uint64_t val = static_cast<uint64_t>(1) << i;
    PutVarint64(&dst_, val);
    
    Slice input(dst_);
    uint64_t result;
    EXPECT_TRUE(GetVarint64(&input, &result));
    EXPECT_EQ(result, val) << "Failed for power of two: 2^" << i;
  }
}

TEST_F(PutVarint64Test_443, VarintEncodingSize_443) {
  // Test that encoding sizes match expected varint sizes
  // 1 byte: 0-127
  // 2 bytes: 128 - 16383
  // etc.
  
  dst_.clear();
  PutVarint64(&dst_, 0);
  EXPECT_EQ(dst_.size(), 1u);
  
  dst_.clear();
  PutVarint64(&dst_, 127);
  EXPECT_EQ(dst_.size(), 1u);
  
  dst_.clear();
  PutVarint64(&dst_, 128);
  EXPECT_EQ(dst_.size(), 2u);
  
  dst_.clear();
  PutVarint64(&dst_, 16383);
  EXPECT_EQ(dst_.size(), 2u);
  
  dst_.clear();
  PutVarint64(&dst_, 16384);
  EXPECT_EQ(dst_.size(), 3u);
}

TEST_F(PutVarint64Test_443, BoundaryValues_443) {
  // Test values at byte boundaries of varint encoding
  std::vector<std::pair<uint64_t, size_t>> test_cases = {
      {0, 1},
      {(1ULL << 7) - 1, 1},
      {(1ULL << 7), 2},
      {(1ULL << 14) - 1, 2},
      {(1ULL << 14), 3},
      {(1ULL << 21) - 1, 3},
      {(1ULL << 21), 4},
      {(1ULL << 28) - 1, 4},
      {(1ULL << 28), 5},
      {(1ULL << 35) - 1, 5},
      {(1ULL << 35), 6},
      {(1ULL << 42) - 1, 6},
      {(1ULL << 42), 7},
      {(1ULL << 49) - 1, 7},
      {(1ULL << 49), 8},
      {(1ULL << 56) - 1, 8},
      {(1ULL << 56), 9},
      {(1ULL << 63) - 1, 9},
      {(1ULL << 63), 10},
      {std::numeric_limits<uint64_t>::max(), 10},
  };
  
  for (const auto& tc : test_cases) {
    dst_.clear();
    PutVarint64(&dst_, tc.first);
    EXPECT_EQ(dst_.size(), tc.second) 
        << "Value: " << tc.first << " expected size: " << tc.second;
    
    Slice input(dst_);
    uint64_t result;
    EXPECT_TRUE(GetVarint64(&input, &result));
    EXPECT_EQ(result, tc.first);
  }
}

TEST_F(PutVarint64Test_443, EmptyStringAppend_443) {
  EXPECT_TRUE(dst_.empty());
  PutVarint64(&dst_, 42);
  EXPECT_FALSE(dst_.empty());
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, 42u);
}

TEST_F(PutVarint64Test_443, Uint32MaxValue_443) {
  uint64_t val = std::numeric_limits<uint32_t>::max();
  PutVarint64(&dst_, val);
  
  Slice input(dst_);
  uint64_t result;
  EXPECT_TRUE(GetVarint64(&input, &result));
  EXPECT_EQ(result, val);
}

}  // namespace leveldb
