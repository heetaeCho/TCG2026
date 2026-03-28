#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#include "util/logging.h"

namespace leveldb {

// Test normal operation with a typical number
TEST(NumberToStringTest_458, TypicalNumber_458) {
  std::string result = NumberToString(12345);
  EXPECT_EQ(result, "12345");
}

// Test boundary: zero
TEST(NumberToStringTest_458, Zero_458) {
  std::string result = NumberToString(0);
  EXPECT_EQ(result, "0");
}

// Test boundary: one
TEST(NumberToStringTest_458, One_458) {
  std::string result = NumberToString(1);
  EXPECT_EQ(result, "1");
}

// Test boundary: maximum uint64_t value
TEST(NumberToStringTest_458, MaxUint64_458) {
  std::string result = NumberToString(UINT64_MAX);
  EXPECT_EQ(result, "18446744073709551615");
}

// Test a large number below max
TEST(NumberToStringTest_458, LargeNumber_458) {
  std::string result = NumberToString(1000000000000ULL);
  EXPECT_EQ(result, "1000000000000");
}

// Test single digit numbers
TEST(NumberToStringTest_458, SingleDigit_458) {
  EXPECT_EQ(NumberToString(9), "9");
}

// Test power of ten
TEST(NumberToStringTest_458, PowerOfTen_458) {
  EXPECT_EQ(NumberToString(100), "100");
}

// Test that result contains only numeric characters
TEST(NumberToStringTest_458, ResultIsNumericOnly_458) {
  std::string result = NumberToString(999999);
  for (char c : result) {
    EXPECT_TRUE(c >= '0' && c <= '9') << "Non-numeric character found: " << c;
  }
}

// Test that repeated calls produce consistent results
TEST(NumberToStringTest_458, ConsistentResults_458) {
  std::string r1 = NumberToString(42);
  std::string r2 = NumberToString(42);
  EXPECT_EQ(r1, r2);
}

// Test boundary: UINT32_MAX
TEST(NumberToStringTest_458, Uint32Max_458) {
  std::string result = NumberToString(UINT32_MAX);
  EXPECT_EQ(result, "4294967295");
}

// Test boundary: UINT32_MAX + 1
TEST(NumberToStringTest_458, Uint32MaxPlusOne_458) {
  std::string result = NumberToString(static_cast<uint64_t>(UINT32_MAX) + 1);
  EXPECT_EQ(result, "4294967296");
}

// Test various small numbers
TEST(NumberToStringTest_458, SmallNumbers_458) {
  EXPECT_EQ(NumberToString(2), "2");
  EXPECT_EQ(NumberToString(10), "10");
  EXPECT_EQ(NumberToString(99), "99");
}

}  // namespace leveldb
