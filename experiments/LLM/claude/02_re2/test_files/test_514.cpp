#include <string>
#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

class MaybeParseRepetitionTest_514 : public ::testing::Test {
 protected:
  // Helper: try to parse a regex and check if it's valid
  bool IsValidRegex(const std::string& pattern) {
    RE2 re(pattern);
    return re.ok();
  }

  // Helper: check if a regex matches a given string
  bool Matches(const std::string& pattern, const std::string& text) {
    RE2 re(pattern);
    if (!re.ok()) return false;
    return RE2::FullMatch(text, re);
  }
};

// Test exact repetition {n}
TEST_F(MaybeParseRepetitionTest_514, ExactRepetition_514) {
  EXPECT_TRUE(Matches("a{3}", "aaa"));
  EXPECT_FALSE(Matches("a{3}", "aa"));
  EXPECT_FALSE(Matches("a{3}", "aaaa"));
}

// Test range repetition {n,m}
TEST_F(MaybeParseRepetitionTest_514, RangeRepetition_514) {
  EXPECT_TRUE(Matches("a{2,4}", "aa"));
  EXPECT_TRUE(Matches("a{2,4}", "aaa"));
  EXPECT_TRUE(Matches("a{2,4}", "aaaa"));
  EXPECT_FALSE(Matches("a{2,4}", "a"));
  EXPECT_FALSE(Matches("a{2,4}", "aaaaa"));
}

// Test open-ended repetition {n,}
TEST_F(MaybeParseRepetitionTest_514, OpenEndedRepetition_514) {
  EXPECT_TRUE(Matches("a{2,}", "aa"));
  EXPECT_TRUE(Matches("a{2,}", "aaaa"));
  EXPECT_TRUE(Matches("a{2,}", "aaaaaaaaaa"));
  EXPECT_FALSE(Matches("a{2,}", "a"));
}

// Test {0} repetition
TEST_F(MaybeParseRepetitionTest_514, ZeroRepetition_514) {
  EXPECT_TRUE(Matches("a{0}", ""));
  EXPECT_FALSE(Matches("a{0}", "a"));
}

// Test {0,0} repetition
TEST_F(MaybeParseRepetitionTest_514, ZeroToZeroRepetition_514) {
  EXPECT_TRUE(Matches("a{0,0}", ""));
  EXPECT_FALSE(Matches("a{0,0}", "a"));
}

// Test {1} repetition (equivalent to just 'a')
TEST_F(MaybeParseRepetitionTest_514, SingleRepetition_514) {
  EXPECT_TRUE(Matches("a{1}", "a"));
  EXPECT_FALSE(Matches("a{1}", ""));
  EXPECT_FALSE(Matches("a{1}", "aa"));
}

// Test {0,1} repetition (equivalent to 'a?')
TEST_F(MaybeParseRepetitionTest_514, ZeroOrOneRepetition_514) {
  EXPECT_TRUE(Matches("a{0,1}", ""));
  EXPECT_TRUE(Matches("a{0,1}", "a"));
  EXPECT_FALSE(Matches("a{0,1}", "aa"));
}

// Test invalid repetition: no closing brace - treated as literal
TEST_F(MaybeParseRepetitionTest_514, MissingClosingBrace_514) {
  // In RE2, an incomplete repetition like {3 without } is treated as literal
  EXPECT_TRUE(IsValidRegex("a{3"));
}

// Test empty braces {} - should be treated as literal or invalid
TEST_F(MaybeParseRepetitionTest_514, EmptyBraces_514) {
  // RE2 should handle this gracefully
  EXPECT_TRUE(IsValidRegex("a{}"));
}

// Test invalid range where lo > hi
TEST_F(MaybeParseRepetitionTest_514, InvalidRange_LoGreaterThanHi_514) {
  // {4,2} is an invalid repetition range
  EXPECT_FALSE(IsValidRegex("a{4,2}"));
}

// Test repetition with large numbers
TEST_F(MaybeParseRepetitionTest_514, LargeRepetitionCount_514) {
  // RE2 has a limit on repetition count (1000 by default)
  EXPECT_FALSE(IsValidRegex("a{1001}"));
}

// Test {n,m} where n equals m
TEST_F(MaybeParseRepetitionTest_514, RangeWithEqualBounds_514) {
  EXPECT_TRUE(Matches("a{3,3}", "aaa"));
  EXPECT_FALSE(Matches("a{3,3}", "aa"));
  EXPECT_FALSE(Matches("a{3,3}", "aaaa"));
}

// Test that bare { without number is treated as literal
TEST_F(MaybeParseRepetitionTest_514, BareOpenBrace_514) {
  EXPECT_TRUE(IsValidRegex("a{"));
}

// Test {,n} - missing lo
TEST_F(MaybeParseRepetitionTest_514, MissingLo_514) {
  // {,3} has no lo integer, so MaybeParseRepetition returns false
  // and it's treated as a literal
  EXPECT_TRUE(IsValidRegex("a{,3}"));
}

// Test repetition with comma but no hi, no closing brace
TEST_F(MaybeParseRepetitionTest_514, CommaNoHiNoBrace_514) {
  EXPECT_TRUE(IsValidRegex("a{3,"));
}

// Test {0,} repetition (equivalent to 'a*')
TEST_F(MaybeParseRepetitionTest_514, ZeroOrMoreRepetition_514) {
  EXPECT_TRUE(Matches("a{0,}", ""));
  EXPECT_TRUE(Matches("a{0,}", "a"));
  EXPECT_TRUE(Matches("a{0,}", "aaaa"));
}

// Test {1,} repetition (equivalent to 'a+')
TEST_F(MaybeParseRepetitionTest_514, OneOrMoreRepetition_514) {
  EXPECT_TRUE(Matches("a{1,}", "a"));
  EXPECT_TRUE(Matches("a{1,}", "aaaa"));
  EXPECT_FALSE(Matches("a{1,}", ""));
}

// Test with complex patterns involving repetition
TEST_F(MaybeParseRepetitionTest_514, ComplexPatternWithRepetition_514) {
  EXPECT_TRUE(Matches("(ab){2}", "abab"));
  EXPECT_FALSE(Matches("(ab){2}", "ab"));
  EXPECT_TRUE(Matches("[abc]{2,3}", "ab"));
  EXPECT_TRUE(Matches("[abc]{2,3}", "abc"));
}

// Test nested repetitions (if allowed)
TEST_F(MaybeParseRepetitionTest_514, NestedRepetition_514) {
  // RE2 may not allow nested repetitions
  // (a{2}){3} should be valid
  EXPECT_TRUE(Matches("(a{2}){3}", "aaaaaa"));
  EXPECT_FALSE(Matches("(a{2}){3}", "aaaaa"));
}

}  // namespace re2
