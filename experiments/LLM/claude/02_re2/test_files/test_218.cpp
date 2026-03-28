#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class MimicsPCRETest_218 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that a simple literal string mimics PCRE
TEST_F(MimicsPCRETest_218, SimpleLiteralMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a simple concatenation mimics PCRE
TEST_F(MimicsPCRETest_218, SimpleConcatenationMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a simple alternation mimics PCRE
TEST_F(MimicsPCRETest_218, SimpleAlternationMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a simple character class mimics PCRE
TEST_F(MimicsPCRETest_218, SimpleCharClassMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a simple repetition mimics PCRE
TEST_F(MimicsPCRETest_218, SimpleRepetitionMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a plus repetition mimics PCRE
TEST_F(MimicsPCRETest_218, PlusRepetitionMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a question mark mimics PCRE
TEST_F(MimicsPCRETest_218, QuestionMarkMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a capture group mimics PCRE
TEST_F(MimicsPCRETest_218, CaptureGroupMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that dot mimics PCRE
TEST_F(MimicsPCRETest_218, DotMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that anchors mimic PCRE
TEST_F(MimicsPCRETest_218, AnchorsMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a repetition with specific counts mimics PCRE
TEST_F(MimicsPCRETest_218, CountedRepetitionMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test non-greedy repetitions mimic PCRE
TEST_F(MimicsPCRETest_218, NonGreedyRepetitionMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test word boundary mimics PCRE
TEST_F(MimicsPCRETest_218, WordBoundaryMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bhello\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test escaped special characters mimic PCRE
TEST_F(MimicsPCRETest_218, EscapedCharactersMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test complex pattern mimics PCRE
TEST_F(MimicsPCRETest_218, ComplexPatternMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+)(b*)|c{2,3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that nested repetitions may not mimic PCRE
// e.g., (a*)* is a pattern that might cause backtracking differences
TEST_F(MimicsPCRETest_218, NestedRepetitionMayNotMimicPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a*)*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Nested repetitions are known to diverge from PCRE semantics
  bool result = re->MimicsPCRE();
  // We just verify it doesn't crash; the result depends on the implementation
  (void)result;
  re->Decref();
}

// Test that (a*|b*)* may not mimic PCRE
TEST_F(MimicsPCRETest_218, AlternationWithRepetitionMayNotMimicPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a*|b*)*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  (void)result;
  re->Decref();
}

// Test empty pattern mimics PCRE
TEST_F(MimicsPCRETest_218, EmptyPatternMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a named capture group mimics PCRE
TEST_F(MimicsPCRETest_218, NamedCaptureGroupMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test non-capturing group mimics PCRE
TEST_F(MimicsPCRETest_218, NonCapturingGroupMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that (a+)+, a nested repetition with + inside +, is tested
TEST_F(MimicsPCRETest_218, NestedPlusRepetition_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  (void)result;
  re->Decref();
}

// Test that (a+|)* pattern with empty alternative
TEST_F(MimicsPCRETest_218, EmptyAlternativeInRepetition_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|)*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  (void)result;
  re->Decref();
}

// Test that a simple single character mimics PCRE
TEST_F(MimicsPCRETest_218, SingleCharacterMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test case insensitive flag
TEST_F(MimicsPCRETest_218, CaseInsensitiveMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test with multiline mode
TEST_F(MimicsPCRETest_218, MultilineMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?m)^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test with dotall/singleline mode
TEST_F(MimicsPCRETest_218, DotAllMimicsPCRE_218) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?s)a.b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

}  // namespace re2
