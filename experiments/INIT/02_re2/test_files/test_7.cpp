// File: re2_fullmatch_test_7.cc
#include <string>
#include "gtest/gtest.h"
#include "re2/re2.h"

using re2::RE2;

class RE2FullMatchTest_7 : public ::testing::Test {};

// ----- Normal operation -----

TEST_F(RE2FullMatchTest_7, SimpleLiteralSuccess_7) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2FullMatchTest_7, SimpleLiteralFailure_7) {
  RE2 re("hello");
  EXPECT_FALSE(RE2::FullMatch("hello!", re));  // extra char prevents full match
}

TEST_F(RE2FullMatchTest_7, DotStarMatchesAll_7) {
  RE2 re(".*");
  EXPECT_TRUE(RE2::FullMatch("anything at all", re));
}

// ----- Captures into user-provided variables -----

TEST_F(RE2FullMatchTest_7, CapturesSingleString_7) {
  RE2 re("(\\w+)");
  std::string out;
  ASSERT_TRUE(RE2::FullMatch("token", re, &out));
  EXPECT_EQ(out, "token");
}

TEST_F(RE2FullMatchTest_7, CapturesMultipleTypes_7) {
  RE2 re("([A-Za-z]+)-(\\d+)");
  std::string name;
  int number = -1;
  ASSERT_TRUE(RE2::FullMatch("item-42", re, &name, &number));
  EXPECT_EQ(name, "item");
  EXPECT_EQ(number, 42);
}

// Verify CRadix parsing behaves as an observable interface feature.
// (No assumption about internal parsing beyond documented behavior that CRadix parses in any supported radix.)
TEST_F(RE2FullMatchTest_7, CapturesIntegerWithCRadix_7) {
  RE2 re("(0x[0-9A-Fa-f]+)");
  int value = 0;
  ASSERT_TRUE(RE2::FullMatch("0x2A", re, RE2::CRadix(&value)));
  EXPECT_EQ(value, 42);
}

// ----- Boundary conditions -----

TEST_F(RE2FullMatchTest_7, EmptyPatternOnEmptyText_7) {
  RE2 re("");                // empty regex
  EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST_F(RE2FullMatchTest_7, EmptyPatternOnNonEmptyText_7) {
  RE2 re("");                // empty regex should not fully match non-empty text
  EXPECT_FALSE(RE2::FullMatch("x", re));
}

TEST_F(RE2FullMatchTest_7, AnchorsRequireFullCoverage_7) {
  RE2 re("abc");
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("abc\n", re));   // extra character prevents full match
}

// ----- Exceptional / error cases (observable via the interface) -----

TEST_F(RE2FullMatchTest_7, InvalidPatternCausesOkFalseAndMatchFalse_7) {
  RE2 re("(");                       // clearly invalid
  EXPECT_FALSE(re.ok());             // observable through ok()
  EXPECT_FALSE(RE2::FullMatch("x", re));  // matching with invalid re should fail
}

// On failure, captures should remain unchanged (observable side-effect behavior).
TEST_F(RE2FullMatchTest_7, FailedMatchDoesNotModifyStringCapture_7) {
  RE2 re("(\\d+)");
  std::string cap = "unchanged";
  EXPECT_FALSE(RE2::FullMatch("no-digits-here", re, &cap));
  EXPECT_EQ(cap, "unchanged");
}

TEST_F(RE2FullMatchTest_7, FailedMatchDoesNotModifyNumericCapture_7) {
  RE2 re("(\\d+)");
  int n = 123;  // sentinel
  EXPECT_FALSE(RE2::FullMatch("abc", re, &n));
  EXPECT_EQ(n, 123);
}

// ----- Construction forms for the RE2 object (interface-only) -----

TEST_F(RE2FullMatchTest_7, WorksWithRE2ConstructedFromStdString_7) {
  std::string pat = "a{3}";
  RE2 re(pat);
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

TEST_F(RE2FullMatchTest_7, WorksWithRE2ConstructedFromCString_7) {
  const char* pat = "colou?r";  // optional 'u'
  RE2 re(pat);
  EXPECT_TRUE(RE2::FullMatch("color", re));
  EXPECT_TRUE(RE2::FullMatch("colour", re));
  EXPECT_FALSE(RE2::FullMatch("colouur", re));
}

// ----- Multiple capture groups and exact coverage -----

TEST_F(RE2FullMatchTest_7, MultipleCapturesAndExactEnd_7) {
  RE2 re("([A-Z]{2})(\\d{3})");
  std::string prefix;
  int code = -1;
  ASSERT_TRUE(RE2::FullMatch("AB123", re, &prefix, &code));
  EXPECT_EQ(prefix, "AB");
  EXPECT_EQ(code, 123);

  // Trailing characters -> not a full match
  EXPECT_FALSE(RE2::FullMatch("AB123X", re, &prefix, &code));
}
