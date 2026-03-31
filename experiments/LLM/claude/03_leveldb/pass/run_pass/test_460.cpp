#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include "util/logging.h"
#include <cstdint>
#include <limits>
#include <string>

namespace leveldb {

// Test normal operation: simple single digit
TEST(ConsumeDecimalNumberTest_460, SingleDigit_460) {
  Slice input("5");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(5u, val);
  EXPECT_EQ(0u, input.size());
}

// Test normal operation: multi-digit number
TEST(ConsumeDecimalNumberTest_460, MultiDigitNumber_460) {
  Slice input("12345");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(12345u, val);
  EXPECT_EQ(0u, input.size());
}

// Test normal operation: zero
TEST(ConsumeDecimalNumberTest_460, Zero_460) {
  Slice input("0");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(0u, val);
  EXPECT_EQ(0u, input.size());
}

// Test normal operation: number followed by non-digit characters
TEST(ConsumeDecimalNumberTest_460, NumberFollowedByNonDigit_460) {
  Slice input("123abc");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(123u, val);
  EXPECT_EQ(3u, input.size());
  EXPECT_EQ("abc", input.ToString());
}

// Test normal operation: number followed by space
TEST(ConsumeDecimalNumberTest_460, NumberFollowedBySpace_460) {
  Slice input("42 rest");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(42u, val);
  EXPECT_EQ(" rest", input.ToString());
}

// Test boundary: empty input
TEST(ConsumeDecimalNumberTest_460, EmptyInput_460) {
  Slice input("");
  uint64_t val = 123;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(0u, val);
  EXPECT_EQ(0u, input.size());
}

// Test boundary: input starts with non-digit
TEST(ConsumeDecimalNumberTest_460, StartsWithNonDigit_460) {
  Slice input("abc123");
  uint64_t val = 123;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(0u, val);
  EXPECT_EQ(6u, input.size());
}

// Test boundary: max uint64 value
TEST(ConsumeDecimalNumberTest_460, MaxUint64_460) {
  std::string maxStr = std::to_string(std::numeric_limits<uint64_t>::max());
  Slice input(maxStr);
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(std::numeric_limits<uint64_t>::max(), val);
  EXPECT_EQ(0u, input.size());
}

// Test error: overflow - number larger than max uint64
TEST(ConsumeDecimalNumberTest_460, OverflowBeyondMaxUint64_460) {
  // max uint64 is 18446744073709551615, so 18446744073709551616 overflows
  std::string overflowStr = "18446744073709551616";
  Slice input(overflowStr);
  uint64_t val = 0;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
}

// Test error: overflow - much larger number
TEST(ConsumeDecimalNumberTest_460, OverflowMuchLarger_460) {
  std::string overflowStr = "99999999999999999999";
  Slice input(overflowStr);
  uint64_t val = 0;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
}

// Test error: overflow with extra digits
TEST(ConsumeDecimalNumberTest_460, OverflowExtraDigits_460) {
  // 21 digits is definitely overflow
  std::string overflowStr = "184467440737095516150";
  Slice input(overflowStr);
  uint64_t val = 0;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
}

// Test: leading zeros
TEST(ConsumeDecimalNumberTest_460, LeadingZeros_460) {
  Slice input("00123");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(123u, val);
  EXPECT_EQ(0u, input.size());
}

// Test: single zero followed by digits
TEST(ConsumeDecimalNumberTest_460, ZeroFollowedByDigits_460) {
  Slice input("0123");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(123u, val);
  EXPECT_EQ(0u, input.size());
}

// Test: input is just whitespace
TEST(ConsumeDecimalNumberTest_460, WhitespaceOnly_460) {
  Slice input("   ");
  uint64_t val = 42;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(0u, val);
}

// Test: negative sign is not consumed
TEST(ConsumeDecimalNumberTest_460, NegativeSign_460) {
  Slice input("-123");
  uint64_t val = 42;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(0u, val);
  EXPECT_EQ(4u, input.size());
}

// Test: plus sign is not consumed
TEST(ConsumeDecimalNumberTest_460, PlusSign_460) {
  Slice input("+123");
  uint64_t val = 42;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(0u, val);
  EXPECT_EQ(4u, input.size());
}

// Test: slice is properly advanced (remove_prefix called correctly)
TEST(ConsumeDecimalNumberTest_460, SliceAdvancedCorrectly_460) {
  Slice input("999xyz");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(999u, val);
  EXPECT_EQ(3u, input.size());
  EXPECT_EQ('x', input[0]);
  EXPECT_EQ('y', input[1]);
  EXPECT_EQ('z', input[2]);
}

// Test: all digits 0-9
TEST(ConsumeDecimalNumberTest_460, AllDigits_460) {
  Slice input("1234567890");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(1234567890u, val);
  EXPECT_EQ(0u, input.size());
}

// Test: max uint64 minus 1
TEST(ConsumeDecimalNumberTest_460, MaxUint64MinusOne_460) {
  uint64_t maxMinus1 = std::numeric_limits<uint64_t>::max() - 1;
  std::string str = std::to_string(maxMinus1);
  Slice input(str);
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(maxMinus1, val);
}

// Test: single character '0'
TEST(ConsumeDecimalNumberTest_460, SingleZero_460) {
  Slice input("0");
  uint64_t val = 42;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(0u, val);
  EXPECT_EQ(0u, input.size());
}

// Test: single character '9'
TEST(ConsumeDecimalNumberTest_460, SingleNine_460) {
  Slice input("9");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(9u, val);
  EXPECT_EQ(0u, input.size());
}

// Test: binary data that looks like digits but with embedded null
TEST(ConsumeDecimalNumberTest_460, EmbeddedNull_460) {
  std::string str("12");
  str.push_back('\0');
  str.append("34");
  Slice input(str.data(), str.size());
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(12u, val);
  // Remaining should be "\034"
  EXPECT_EQ(3u, input.size());
}

// Test: decimal point is not consumed
TEST(ConsumeDecimalNumberTest_460, DecimalPoint_460) {
  Slice input("123.456");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(123u, val);
  EXPECT_EQ(".456", input.ToString());
}

// Test: overflow at boundary - value == kMaxUint64/10 and last digit exceeds
TEST(ConsumeDecimalNumberTest_460, OverflowLastDigitExceeds_460) {
  // kMaxUint64 = 18446744073709551615
  // kMaxUint64 / 10 = 1844674407370955161
  // kLastDigitOfMaxUint64 = '5'
  // So 18446744073709551616 should overflow (last digit 6 > 5)
  Slice input("18446744073709551616");
  uint64_t val = 0;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
}

// Test: value just at boundary - kMaxUint64/10 * 10 + last digit = max
TEST(ConsumeDecimalNumberTest_460, ExactMaxUint64Boundary_460) {
  // 18446744073709551615 is exactly max
  Slice input("18446744073709551615");
  uint64_t val = 0;
  ASSERT_TRUE(ConsumeDecimalNumber(&input, &val));
  EXPECT_EQ(std::numeric_limits<uint64_t>::max(), val);
}

// Test: overflow where value > kMaxUint64 / 10 (not equal, greater)
TEST(ConsumeDecimalNumberTest_460, OverflowValueExceedsTenth_460) {
  // 18446744073709551620 -> when processing '2', value would be 1844674407370955162 > kMaxUint64/10
  Slice input("18446744073709551620");
  uint64_t val = 0;
  ASSERT_FALSE(ConsumeDecimalNumber(&input, &val));
}

}  // namespace leveldb
