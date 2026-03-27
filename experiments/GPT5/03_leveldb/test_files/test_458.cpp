// File: logging_number_to_string_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <string>

// Forward declaration (treating implementation as a black box).
namespace leveldb {
std::string NumberToString(uint64_t num);
}

namespace {

// Helper to check that a string consists only of ASCII digits.
bool IsAllDigits(const std::string& s) {
  for (char c : s) {
    if (c < '0' || c > '9') return false;
  }
  return true;
}

// [Normal operation] Zero should be rendered as "0".
TEST(NumberToStringTest_458, HandlesZero_458) {
  std::string r = leveldb::NumberToString(0);
  EXPECT_EQ("0", r);
  EXPECT_TRUE(IsAllDigits(r));
}

// [Normal operation] Single-digit numbers are rendered without leading zeros.
TEST(NumberToStringTest_458, HandlesSingleDigit_458) {
  EXPECT_EQ("7", leveldb::NumberToString(7));
  EXPECT_EQ("9", leveldb::NumberToString(9));
}

// [Normal operation] Typical multi-digit numbers are rendered correctly.
TEST(NumberToStringTest_458, HandlesMultipleDigits_458) {
  EXPECT_EQ("10", leveldb::NumberToString(10));
  EXPECT_EQ("42", leveldb::NumberToString(42));
  EXPECT_EQ("12345", leveldb::NumberToString(12345));
}

// [Boundary] Large 64-bit values are rendered correctly.
TEST(NumberToStringTest_458, HandlesLargeValues_458) {
  // A representative large number within uint64_t.
  uint64_t v = 1234567890123456789ULL;
  std::string r = leveldb::NumberToString(v);
  EXPECT_EQ(std::string("1234567890123456789"), r);
  EXPECT_TRUE(IsAllDigits(r));
  // For non-zero values the first digit should not be '0' (no leading zeros).
  EXPECT_NE('0', r.front());
}

// [Boundary] Maximum uint64_t value.
TEST(NumberToStringTest_458, HandlesUint64Max_458) {
  uint64_t vmax = UINT64_MAX; // 18446744073709551615
  std::string r = leveldb::NumberToString(vmax);
  EXPECT_EQ(std::string("18446744073709551615"), r);
  EXPECT_TRUE(IsAllDigits(r));
  EXPECT_NE('0', r.front());
}

// [Regression/interaction] Multiple independent calls should not interfere.
TEST(NumberToStringTest_458, MultipleCallsAreIndependent_458) {
  std::string a = leveldb::NumberToString(1);
  std::string b = leveldb::NumberToString(1000);
  std::string c = leveldb::NumberToString(0);

  EXPECT_EQ("1", a);
  EXPECT_EQ("1000", b);
  EXPECT_EQ("0", c);

  // Ensure previous results remain intact after subsequent calls.
  EXPECT_EQ("1", a);
  EXPECT_EQ("1000", b);
  EXPECT_EQ("0", c);
}

}  // namespace
