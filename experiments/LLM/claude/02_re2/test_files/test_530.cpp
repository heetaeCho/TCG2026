#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ParseCCRangeTest_530 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = new RegexpStatus();
  }

  void TearDown() override {
    delete status_;
  }

  RegexpStatus* status_;
};

// Test parsing a single character (no range)
TEST_F(ParseCCRangeTest_530, SingleCharacter_530) {
  RegexpStatus parse_status;
  absl::string_view whole_regexp("a]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("a]");
  RuneRange rr;
  absl::string_view whole_class("[a]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'a');
  EXPECT_EQ(rr.hi, 'a');
  EXPECT_TRUE(range_status.ok());
}

// Test parsing a valid range like a-z
TEST_F(ParseCCRangeTest_530, ValidRange_530) {
  absl::string_view whole_regexp("a-z]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("a-z]");
  RuneRange rr;
  absl::string_view whole_class("[a-z]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'a');
  EXPECT_EQ(rr.hi, 'z');
  EXPECT_TRUE(range_status.ok());
}

// Test parsing an inverted range (hi < lo) should fail
TEST_F(ParseCCRangeTest_530, InvertedRangeError_530) {
  absl::string_view whole_regexp("z-a]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("z-a]");
  RuneRange rr;
  absl::string_view whole_class("[z-a]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_FALSE(result);
  EXPECT_EQ(range_status.code(), kRegexpBadCharRange);
}

// Test dash followed by ] is not a range (dash is literal at end)
TEST_F(ParseCCRangeTest_530, DashBeforeCloseBracket_530) {
  absl::string_view whole_regexp("a-]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("a-]");
  RuneRange rr;
  absl::string_view whole_class("[a-]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'a');
  EXPECT_EQ(rr.hi, 'a');
  EXPECT_TRUE(range_status.ok());
}

// Test a range with identical endpoints (e.g., a-a)
TEST_F(ParseCCRangeTest_530, SameEndpointsRange_530) {
  absl::string_view whole_regexp("a-a]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("a-a]");
  RuneRange rr;
  absl::string_view whole_class("[a-a]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'a');
  EXPECT_EQ(rr.hi, 'a');
  EXPECT_TRUE(range_status.ok());
}

// Test range with digits
TEST_F(ParseCCRangeTest_530, DigitRange_530) {
  absl::string_view whole_regexp("0-9]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("0-9]");
  RuneRange rr;
  absl::string_view whole_class("[0-9]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, '0');
  EXPECT_EQ(rr.hi, '9');
  EXPECT_TRUE(range_status.ok());
}

// Test single character at string boundary
TEST_F(ParseCCRangeTest_530, SingleCharOnly_530) {
  absl::string_view whole_regexp("x");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("x");
  RuneRange rr;
  absl::string_view whole_class("[x]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'x');
  EXPECT_EQ(rr.hi, 'x');
}

// Test range with uppercase letters
TEST_F(ParseCCRangeTest_530, UppercaseRange_530) {
  absl::string_view whole_regexp("A-Z]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("A-Z]");
  RuneRange rr;
  absl::string_view whole_class("[A-Z]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'A');
  EXPECT_EQ(rr.hi, 'Z');
  EXPECT_TRUE(range_status.ok());
}

// Test that error_arg is set on bad range
TEST_F(ParseCCRangeTest_530, BadRangeErrorArg_530) {
  absl::string_view whole_regexp("z-a]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("z-a]");
  RuneRange rr;
  absl::string_view whole_class("[z-a]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_FALSE(result);
  EXPECT_EQ(range_status.code(), kRegexpBadCharRange);
  // error_arg should contain the problematic range text
  EXPECT_FALSE(range_status.error_arg().empty());
}

// Test adjacent characters range (e.g., a-b)
TEST_F(ParseCCRangeTest_530, AdjacentCharRange_530) {
  absl::string_view whole_regexp("a-b]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("a-b]");
  RuneRange rr;
  absl::string_view whole_class("[a-b]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'a');
  EXPECT_EQ(rr.hi, 'b');
  EXPECT_TRUE(range_status.ok());
}

// Test with escape character in range
TEST_F(ParseCCRangeTest_530, EscapeCharInRange_530) {
  absl::string_view whole_regexp("\\n-\\r]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("\\n-\\r]");
  RuneRange rr;
  absl::string_view whole_class("[\\n-\\r]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, '\n');
  EXPECT_EQ(rr.hi, '\r');
}

// Test short string with only dash and close bracket
TEST_F(ParseCCRangeTest_530, DashAndCloseBracketOnly_530) {
  absl::string_view whole_regexp("-]");
  Regexp::ParseState ps(Regexp::PerlX, whole_regexp, status_);

  absl::string_view s("-]");
  RuneRange rr;
  absl::string_view whole_class("[-]");
  RegexpStatus range_status;

  bool result = ps.ParseCCRange(&s, &rr, whole_class, &range_status);
  // '-' should be treated as a literal character, hi = lo = '-'
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, '-');
  EXPECT_EQ(rr.hi, '-');
}

}  // namespace re2
