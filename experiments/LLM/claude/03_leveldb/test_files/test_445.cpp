#include "gtest/gtest.h"
#include "util/coding.h"

namespace leveldb {

// Test VarintLength for value 0 — minimum possible value
TEST(VarintLengthTest_445, ZeroValue_445) {
  EXPECT_EQ(1, VarintLength(0));
}

// Test VarintLength for value 1
TEST(VarintLengthTest_445, OneValue_445) {
  EXPECT_EQ(1, VarintLength(1));
}

// Test VarintLength for maximum value that fits in 1 byte (7 bits): 127
TEST(VarintLengthTest_445, MaxOneByteValue_445) {
  EXPECT_EQ(1, VarintLength(127));
}

// Test VarintLength for minimum value that requires 2 bytes: 128
TEST(VarintLengthTest_445, MinTwoByteValue_445) {
  EXPECT_EQ(2, VarintLength(128));
}

// Test VarintLength for maximum value that fits in 2 bytes (14 bits): 16383
TEST(VarintLengthTest_445, MaxTwoByteValue_445) {
  EXPECT_EQ(2, VarintLength((1 << 14) - 1));
}

// Test VarintLength for minimum value that requires 3 bytes: 16384
TEST(VarintLengthTest_445, MinThreeByteValue_445) {
  EXPECT_EQ(3, VarintLength(1 << 14));
}

// Test VarintLength for maximum value that fits in 3 bytes (21 bits): 2097151
TEST(VarintLengthTest_445, MaxThreeByteValue_445) {
  EXPECT_EQ(3, VarintLength((1 << 21) - 1));
}

// Test VarintLength for minimum value that requires 4 bytes: 2097152
TEST(VarintLengthTest_445, MinFourByteValue_445) {
  EXPECT_EQ(4, VarintLength(1 << 21));
}

// Test VarintLength for maximum value that fits in 4 bytes (28 bits): 268435455
TEST(VarintLengthTest_445, MaxFourByteValue_445) {
  EXPECT_EQ(4, VarintLength((1 << 28) - 1));
}

// Test VarintLength for minimum value that requires 5 bytes: 268435456
TEST(VarintLengthTest_445, MinFiveByteValue_445) {
  EXPECT_EQ(5, VarintLength(1 << 28));
}

// Test VarintLength for maximum value that fits in 5 bytes (35 bits)
TEST(VarintLengthTest_445, MaxFiveByteValue_445) {
  EXPECT_EQ(5, VarintLength((1ULL << 35) - 1));
}

// Test VarintLength for minimum value that requires 6 bytes
TEST(VarintLengthTest_445, MinSixByteValue_445) {
  EXPECT_EQ(6, VarintLength(1ULL << 35));
}

// Test VarintLength for maximum value that fits in 6 bytes (42 bits)
TEST(VarintLengthTest_445, MaxSixByteValue_445) {
  EXPECT_EQ(6, VarintLength((1ULL << 42) - 1));
}

// Test VarintLength for minimum value that requires 7 bytes
TEST(VarintLengthTest_445, MinSevenByteValue_445) {
  EXPECT_EQ(7, VarintLength(1ULL << 42));
}

// Test VarintLength for maximum value that fits in 7 bytes (49 bits)
TEST(VarintLengthTest_445, MaxSevenByteValue_445) {
  EXPECT_EQ(7, VarintLength((1ULL << 49) - 1));
}

// Test VarintLength for minimum value that requires 8 bytes
TEST(VarintLengthTest_445, MinEightByteValue_445) {
  EXPECT_EQ(8, VarintLength(1ULL << 49));
}

// Test VarintLength for maximum value that fits in 8 bytes (56 bits)
TEST(VarintLengthTest_445, MaxEightByteValue_445) {
  EXPECT_EQ(8, VarintLength((1ULL << 56) - 1));
}

// Test VarintLength for minimum value that requires 9 bytes
TEST(VarintLengthTest_445, MinNineByteValue_445) {
  EXPECT_EQ(9, VarintLength(1ULL << 56));
}

// Test VarintLength for maximum value that fits in 9 bytes (63 bits)
TEST(VarintLengthTest_445, MaxNineByteValue_445) {
  EXPECT_EQ(9, VarintLength((1ULL << 63) - 1));
}

// Test VarintLength for minimum value that requires 10 bytes (2^63)
TEST(VarintLengthTest_445, MinTenByteValue_445) {
  EXPECT_EQ(10, VarintLength(1ULL << 63));
}

// Test VarintLength for UINT64_MAX — maximum possible uint64_t value
TEST(VarintLengthTest_445, MaxUint64Value_445) {
  EXPECT_EQ(10, VarintLength(UINT64_MAX));
}

// Test VarintLength for some power of two values
TEST(VarintLengthTest_445, PowersOfTwo_445) {
  EXPECT_EQ(1, VarintLength(1));
  EXPECT_EQ(1, VarintLength(2));
  EXPECT_EQ(1, VarintLength(64));
  EXPECT_EQ(2, VarintLength(256));
  EXPECT_EQ(3, VarintLength(1 << 16));
  EXPECT_EQ(5, VarintLength(1ULL << 32));
}

// Test VarintLength for some typical small values
TEST(VarintLengthTest_445, TypicalSmallValues_445) {
  EXPECT_EQ(1, VarintLength(10));
  EXPECT_EQ(1, VarintLength(50));
  EXPECT_EQ(1, VarintLength(100));
  EXPECT_EQ(2, VarintLength(200));
  EXPECT_EQ(2, VarintLength(1000));
}

}  // namespace leveldb
