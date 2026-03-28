#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpNumCapturesTest_356 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Regexp objects are reference counted and cleaned up via Decref
  }

  Regexp* ParseRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                                << " error: " << status.Text();
    return re;
  }
};

// Test that a simple literal pattern has no captures
TEST_F(RegexpNumCapturesTest_356, NoCapturesInLiteral_356) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(0, re->NumCaptures());
  re->Decref();
}

// Test a pattern with a single capture group
TEST_F(RegexpNumCapturesTest_356, SingleCaptureGroup_356) {
  Regexp* re = ParseRegexp("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(1, re->NumCaptures());
  re->Decref();
}

// Test a pattern with multiple capture groups
TEST_F(RegexpNumCapturesTest_356, MultipleCaptureGroups_356) {
  Regexp* re = ParseRegexp("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(3, re->NumCaptures());
  re->Decref();
}

// Test nested capture groups
TEST_F(RegexpNumCapturesTest_356, NestedCaptureGroups_356) {
  Regexp* re = ParseRegexp("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(3, re->NumCaptures());
  re->Decref();
}

// Test non-capturing groups don't count
TEST_F(RegexpNumCapturesTest_356, NonCapturingGroupsNotCounted_356) {
  Regexp* re = ParseRegexp("(?:abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(0, re->NumCaptures());
  re->Decref();
}

// Test mix of capturing and non-capturing groups
TEST_F(RegexpNumCapturesTest_356, MixedCapturingAndNonCapturing_356) {
  Regexp* re = ParseRegexp("(?:a)(b)(?:c)(d)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(2, re->NumCaptures());
  re->Decref();
}

// Test empty pattern
TEST_F(RegexpNumCapturesTest_356, EmptyPattern_356) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(0, re->NumCaptures());
  re->Decref();
}

// Test deeply nested capture groups
TEST_F(RegexpNumCapturesTest_356, DeeplyNestedCaptures_356) {
  Regexp* re = ParseRegexp("((((a))))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(4, re->NumCaptures());
  re->Decref();
}

// Test capture groups inside alternation
TEST_F(RegexpNumCapturesTest_356, CapturesInAlternation_356) {
  Regexp* re = ParseRegexp("(a)|(b)|(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(3, re->NumCaptures());
  re->Decref();
}

// Test capture groups with quantifiers
TEST_F(RegexpNumCapturesTest_356, CapturesWithQuantifiers_356) {
  Regexp* re = ParseRegexp("(a)+(b)*(c)?");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(3, re->NumCaptures());
  re->Decref();
}

// Test named capture groups count as captures
TEST_F(RegexpNumCapturesTest_356, NamedCaptureGroups_356) {
  Regexp* re = ParseRegexp("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(1, re->NumCaptures());
  re->Decref();
}

// Test multiple named capture groups
TEST_F(RegexpNumCapturesTest_356, MultipleNamedCaptureGroups_356) {
  Regexp* re = ParseRegexp("(?P<first>a)(?P<second>b)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(2, re->NumCaptures());
  re->Decref();
}

// Test pattern with character class (no captures)
TEST_F(RegexpNumCapturesTest_356, CharacterClassNoCaptures_356) {
  Regexp* re = ParseRegexp("[abc]+");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(0, re->NumCaptures());
  re->Decref();
}

// Test complex pattern with many capture groups
TEST_F(RegexpNumCapturesTest_356, ComplexPatternMultipleCaptures_356) {
  Regexp* re = ParseRegexp("(\\d+)-(\\d+)-(\\d+)T(\\d+):(\\d+):(\\d+)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(6, re->NumCaptures());
  re->Decref();
}

// Test capture group wrapping entire pattern
TEST_F(RegexpNumCapturesTest_356, CaptureWrappingEntirePattern_356) {
  Regexp* re = ParseRegexp("(abcdef)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(1, re->NumCaptures());
  re->Decref();
}

// Test single character, no captures
TEST_F(RegexpNumCapturesTest_356, SingleCharNoCaps_356) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(0, re->NumCaptures());
  re->Decref();
}

// Test dot star, no captures
TEST_F(RegexpNumCapturesTest_356, DotStarNoCaptures_356) {
  Regexp* re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(0, re->NumCaptures());
  re->Decref();
}

// Test capture inside repetition
TEST_F(RegexpNumCapturesTest_356, CaptureInsideRepetition_356) {
  Regexp* re = ParseRegexp("(a){3,5}");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(1, re->NumCaptures());
  re->Decref();
}

// Test mix of named and unnamed captures
TEST_F(RegexpNumCapturesTest_356, MixNamedAndUnnamedCaptures_356) {
  Regexp* re = ParseRegexp("(a)(?P<b>b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(3, re->NumCaptures());
  re->Decref();
}

// Test captures with escape sequences
TEST_F(RegexpNumCapturesTest_356, CapturesWithEscapeSequences_356) {
  Regexp* re = ParseRegexp("(\\w+)\\s+(\\d+)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(2, re->NumCaptures());
  re->Decref();
}

}  // namespace re2
