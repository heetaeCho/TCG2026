// util/logging_test.cc
#include "leveldb/slice.h"
#include "util/logging.cc"  // or declare bool ConsumeDecimalNumber(Slice*, uint64_t*) and link the TU
#include <gtest/gtest.h>
#include <string>
#include <cstdint>

namespace leveldb {

class ConsumeDecimalNumberTest_460 : public ::testing::Test {};

// Normal operation: parses a simple all-digit string and consumes all digits.
TEST_F(ConsumeDecimalNumberTest_460, ParsesSimpleNumber_460) {
  std::string s = "12345";
  Slice in(s);
  uint64_t val = 0;

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(val, 12345u);
  EXPECT_TRUE(in.empty());                   // consumed all digits
  EXPECT_EQ(in.ToString(), "");              // observable remainder
}

// Normal operation: stops at first non-digit and advances input by digits consumed.
TEST_F(ConsumeDecimalNumberTest_460, ParsesWithTrailingNonDigits_460) {
  std::string s = "987abc";
  Slice in(s);
  uint64_t val = 0;

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(val, 987u);
  EXPECT_EQ(in.ToString(), "abc");           // remainder is observable through Slice
}

// Boundary: empty input → returns false, does not advance; val set to 0 (observable).
TEST_F(ConsumeDecimalNumberTest_460, EmptyInputReturnsFalse_460) {
  std::string s = "";
  Slice in(s);
  uint64_t val = 123;                        // sentinel

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_FALSE(ok);
  EXPECT_EQ(val, 0u);                        // observable per function contract
  EXPECT_TRUE(in.empty());                   // no advancement possible
}

// Boundary: leading zeros are allowed; consumes all consecutive digits.
TEST_F(ConsumeDecimalNumberTest_460, LeadingZeros_460) {
  std::string s = "00042";
  Slice in(s);
  uint64_t val = 0;

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(val, 42u);
  EXPECT_TRUE(in.empty());                   // all digits consumed
}

// Boundary: maximum uint64 value parses successfully and consumes all digits.
TEST_F(ConsumeDecimalNumberTest_460, MaxUint64Succeeds_460) {
  // 2^64 - 1
  std::string s = "18446744073709551615";
  Slice in(s);
  uint64_t val = 0;

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(val, std::numeric_limits<uint64_t>::max());
  EXPECT_TRUE(in.empty());
}

// Exceptional: value just above uint64 max should fail; input and val remain observably unchanged.
TEST_F(ConsumeDecimalNumberTest_460, OverflowReturnsFalseAndNoConsumption_460) {
  std::string s = "18446744073709551616";    // max + 1
  Slice in(s);
  const char* original_data = in.data();
  size_t original_size = in.size();
  uint64_t val = 999u;                       // sentinel

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_FALSE(ok);
  EXPECT_EQ(val, 999u);                      // not modified on failure path
  EXPECT_EQ(in.data(), original_data);       // no advancement
  EXPECT_EQ(in.size(), original_size);
  EXPECT_EQ(in.ToString(), s);               // remainder unchanged
}

// Exceptional: first char non-digit → returns false; no consumption; val set to 0.
TEST_F(ConsumeDecimalNumberTest_460, NonDigitFirstChar_460) {
  std::string s = "abc123";
  Slice in(s);
  uint64_t val = 1234;

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_FALSE(ok);
  EXPECT_EQ(val, 0u);
  EXPECT_EQ(in.ToString(), "abc123");        // unchanged
}

// Normal operation: parses zero and stops before non-digit (e.g., 'x'); advances by one.
TEST_F(ConsumeDecimalNumberTest_460, StopsBeforeNonDigitAndAdvances_460) {
  std::string s = "0x10";
  Slice in(s);
  uint64_t val = 111;

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(val, 0u);
  EXPECT_EQ(in.ToString(), "x10");           // consumed only '0'
}

// Boundary: large but valid (max-1) parses and consumes all digits.
TEST_F(ConsumeDecimalNumberTest_460, MaxMinusOneParses_460) {
  std::string s = "18446744073709551614";    // max - 1
  Slice in(s);
  uint64_t val = 0;

  bool ok = ConsumeDecimalNumber(&in, &val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(val, std::numeric_limits<uint64_t>::max() - 1);
  EXPECT_TRUE(in.empty());
}

} // namespace leveldb
