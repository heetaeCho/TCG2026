#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class RegexpRepeatTest_345 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any regexp objects created during tests
  }
};

// Test that Repeat creates a regexp with the correct op
TEST_F(RegexpRepeatTest_345, RepeatReturnsRegexpWithCorrectOp_345) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  re->Decref();
}

// Test that Repeat stores min correctly
TEST_F(RegexpRepeatTest_345, RepeatStoresMinCorrectly_345) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 7);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  re->Decref();
}

// Test that Repeat stores max correctly
TEST_F(RegexpRepeatTest_345, RepeatStoresMaxCorrectly_345) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, 10);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->max(), 10);
  re->Decref();
}

// Test that Repeat has exactly one sub-expression
TEST_F(RegexpRepeatTest_345, RepeatHasOneSub_345) {
  Regexp* sub = Regexp::NewLiteral('d', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

// Test that Repeat stores the sub-expression correctly
TEST_F(RegexpRepeatTest_345, RepeatStoresSubCorrectly_345) {
  Regexp* sub = Regexp::NewLiteral('e', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 4);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->sub()[0], sub);
  re->Decref();
}

// Test Repeat with min == 0 and max == 0
TEST_F(RegexpRepeatTest_345, RepeatZeroMinZeroMax_345) {
  Regexp* sub = Regexp::NewLiteral('f', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), 0);
  re->Decref();
}

// Test Repeat with min == max (exact repetition)
TEST_F(RegexpRepeatTest_345, RepeatExactRepetition_345) {
  Regexp* sub = Regexp::NewLiteral('g', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 5, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 5);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with max == -1 (unbounded repetition)
TEST_F(RegexpRepeatTest_345, RepeatUnboundedMax_345) {
  Regexp* sub = Regexp::NewLiteral('h', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test Repeat with large min and max values
TEST_F(RegexpRepeatTest_345, RepeatLargeValues_345) {
  Regexp* sub = Regexp::NewLiteral('i', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1000, 2000);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1000);
  EXPECT_EQ(re->max(), 2000);
  re->Decref();
}

// Test Repeat with parse flags preserved
TEST_F(RegexpRepeatTest_345, RepeatPreservesParseFlags_345) {
  Regexp* sub = Regexp::NewLiteral('j', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::FoldCase, 1, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags() & Regexp::FoldCase, Regexp::FoldCase);
  re->Decref();
}

// Test Repeat with min == 0 and unbounded max
TEST_F(RegexpRepeatTest_345, RepeatZeroMinUnboundedMax_345) {
  Regexp* sub = Regexp::NewLiteral('k', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test that Repeat produces correct Dump output
TEST_F(RegexpRepeatTest_345, RepeatDumpOutput_345) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // Dump should contain information about the repeat
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test that Repeat reference count starts at 1
TEST_F(RegexpRepeatTest_345, RepeatRefCountIsOne_345) {
  Regexp* sub = Regexp::NewLiteral('l', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, 2);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test Repeat via Parse for a{2,5} pattern
TEST_F(RegexpRepeatTest_345, ParseRepeatPattern_345) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

// Test Repeat via Parse for exact count a{3}
TEST_F(RegexpRepeatTest_345, ParseExactRepeatPattern_345) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Repeat via Parse for unbounded a{2,}
TEST_F(RegexpRepeatTest_345, ParseUnboundedRepeatPattern_345) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test ToString round-trip for repeat
TEST_F(RegexpRepeatTest_345, RepeatToStringRoundTrip_345) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  // Parse the string back and verify
  Regexp* re2 = Regexp::Parse(s, Regexp::NoParseFlags, &status);
  ASSERT_NE(re2, nullptr);
  EXPECT_EQ(re2->op(), kRegexpRepeat);
  EXPECT_EQ(re2->min(), 2);
  EXPECT_EQ(re2->max(), 5);
  re->Decref();
  re2->Decref();
}

// Test that Repeat with NonGreedy flag works
TEST_F(RegexpRepeatTest_345, RepeatNonGreedy_345) {
  Regexp* sub = Regexp::NewLiteral('m', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NonGreedy, 1, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), 5);
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);
  re->Decref();
}

}  // namespace re2
