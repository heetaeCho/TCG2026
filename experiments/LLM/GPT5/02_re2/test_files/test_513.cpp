// File: parse_integer_test_513.cc

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// Include the implementation directly so we can access the internal-static symbol
// under test without re-implementing it.
#include "re2/parse.cc"

using re2::ParseInteger;

class ParseIntegerTest_513 : public ::testing::Test {};

TEST_F(ParseIntegerTest_513, ParsesSimpleNumber_513) {
  absl::string_view s = "98765";
  int n = -1;

  bool ok = ParseInteger(&s, &n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 98765);
  EXPECT_TRUE(s.empty());  // all digits consumed
}

TEST_F(ParseIntegerTest_513, ParsesSingleZero_513) {
  absl::string_view s = "0";
  int n = 123;  // sentinel

  bool ok = ParseInteger(&s, &n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 0);
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseIntegerTest_513, StopsAtFirstNonDigit_513) {
  absl::string_view s = "123abc";
  int n = -1;

  bool ok = ParseInteger(&s, &n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 123);
  EXPECT_EQ(s, "abc");  // remainder left unconsumed
}

TEST_F(ParseIntegerTest_513, RejectsEmptyString_NoConsumption_513) {
  absl::string_view s = "";
  int n = 42;  // sentinel

  bool ok = ParseInteger(&s, &n);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n, 42);      // not assigned on failure
  EXPECT_TRUE(s.empty());  // unchanged
}

TEST_F(ParseIntegerTest_513, RejectsNonDigitStart_NoConsumption_513) {
  absl::string_view s = "-12";
  int n = 7;  // sentinel

  bool ok = ParseInteger(&s, &n);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n, 7);        // unchanged on failure
  EXPECT_EQ(s, "-12");    // no consumption
}

TEST_F(ParseIntegerTest_513, RejectsLeadingZeroForMultiDigit_NoConsumption_513) {
  absl::string_view s = "01";
  int n = 99;  // sentinel

  bool ok = ParseInteger(&s, &n);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n, 99);     // unchanged on failure
  EXPECT_EQ(s, "01");   // unchanged
}

TEST_F(ParseIntegerTest_513, AcceptsNineDigitsBoundary_513) {
  // 9 digits total
  absl::string_view s = "100000000";
  int n = -1;

  bool ok = ParseInteger(&s, &n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 100000000);
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseIntegerTest_513, FailsWhenWouldExceedDigitLimit_LeavesRemainder_513) {
  // 10 digits: after consuming 9 digits, the next iteration detects n >= 100000000 and fails.
  absl::string_view s = "1000000000";
  int n = 12345;  // sentinel

  bool ok = ParseInteger(&s, &n);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n, 12345);       // not updated on failure
  EXPECT_EQ(s, "0");         // only the final digit remains unconsumed
}
