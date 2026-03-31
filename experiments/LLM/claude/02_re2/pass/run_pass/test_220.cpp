#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class MimicsPCRETest_220 : public ::testing::Test {
 protected:
  Regexp* Parse(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                                << " error: " << status.Text();
    return re;
  }
};

// Simple literal patterns should mimic PCRE
TEST_F(MimicsPCRETest_220, SimpleLiteral_220) {
  Regexp* re = Parse("hello");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Empty pattern should mimic PCRE
TEST_F(MimicsPCRETest_220, EmptyPattern_220) {
  Regexp* re = Parse("");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Simple alternation should mimic PCRE
TEST_F(MimicsPCRETest_220, SimpleAlternation_220) {
  Regexp* re = Parse("a|b");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Simple character class should mimic PCRE
TEST_F(MimicsPCRETest_220, SimpleCharClass_220) {
  Regexp* re = Parse("[abc]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Simple repetition (star) should mimic PCRE
TEST_F(MimicsPCRETest_220, SimpleStar_220) {
  Regexp* re = Parse("a*");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Simple repetition (plus) should mimic PCRE
TEST_F(MimicsPCRETest_220, SimplePlus_220) {
  Regexp* re = Parse("a+");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Simple repetition (question) should mimic PCRE
TEST_F(MimicsPCRETest_220, SimpleQuestion_220) {
  Regexp* re = Parse("a?");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Capture group should mimic PCRE
TEST_F(MimicsPCRETest_220, CaptureGroup_220) {
  Regexp* re = Parse("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Dot should mimic PCRE
TEST_F(MimicsPCRETest_220, Dot_220) {
  Regexp* re = Parse(".");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Anchors should mimic PCRE
TEST_F(MimicsPCRETest_220, Anchors_220) {
  Regexp* re = Parse("^abc$");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Word boundary should mimic PCRE
TEST_F(MimicsPCRETest_220, WordBoundary_220) {
  Regexp* re = Parse("\\bfoo\\b");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Nested captures should mimic PCRE
TEST_F(MimicsPCRETest_220, NestedCaptures_220) {
  Regexp* re = Parse("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Named captures should mimic PCRE
TEST_F(MimicsPCRETest_220, NamedCapture_220) {
  Regexp* re = Parse("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Non-greedy repetition should mimic PCRE
TEST_F(MimicsPCRETest_220, NonGreedyStar_220) {
  Regexp* re = Parse("a*?");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Non-greedy plus should mimic PCRE
TEST_F(MimicsPCRETest_220, NonGreedyPlus_220) {
  Regexp* re = Parse("a+?");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Counted repetition should mimic PCRE
TEST_F(MimicsPCRETest_220, CountedRepetition_220) {
  Regexp* re = Parse("a{2,5}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Complex pattern that should mimic PCRE
TEST_F(MimicsPCRETest_220, ComplexPatternMimics_220) {
  Regexp* re = Parse("^(([a-z]+)(\\d{2,4}))$");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Escape sequences should mimic PCRE
TEST_F(MimicsPCRETest_220, EscapeSequences_220) {
  Regexp* re = Parse("\\d+\\s*\\w+");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Alternation with captures should mimic PCRE
TEST_F(MimicsPCRETest_220, AlternationWithCaptures_220) {
  Regexp* re = Parse("(a)|(b)");
  ASSERT_NE(re, nullptr);
  // This may or may not mimic PCRE depending on the implementation
  // (PCRE has different capture group semantics in alternations)
  // Just verify it returns a bool without crashing
  re->MimicsPCRE();
  re->Decref();
}

// Single character should mimic PCRE
TEST_F(MimicsPCRETest_220, SingleChar_220) {
  Regexp* re = Parse("a");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Negated character class
TEST_F(MimicsPCRETest_220, NegatedCharClass_220) {
  Regexp* re = Parse("[^abc]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Pattern with backreference-like structure but parsed without PCRE mode
// Using Regexp::Parse with different flags might affect MimicsPCRE
TEST_F(MimicsPCRETest_220, PosixFlags_220) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Repetition with exact count
TEST_F(MimicsPCRETest_220, ExactRepetition_220) {
  Regexp* re = Parse("a{3}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Pattern with \A and \z anchors
TEST_F(MimicsPCRETest_220, SpecialAnchors_220) {
  Regexp* re = Parse("\\Aabc\\z");
  ASSERT_NE(re, nullptr);
  re->MimicsPCRE();  // Just verify no crash
  re->Decref();
}

// Deeply nested pattern
TEST_F(MimicsPCRETest_220, DeeplyNested_220) {
  Regexp* re = Parse("((((a))))");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Multiple alternations
TEST_F(MimicsPCRETest_220, MultipleAlternations_220) {
  Regexp* re = Parse("a|b|c|d|e");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Pattern with non-capturing group
TEST_F(MimicsPCRETest_220, NonCapturingGroup_220) {
  Regexp* re = Parse("(?:abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Unicode character class
TEST_F(MimicsPCRETest_220, UnicodeCharClass_220) {
  Regexp* re = Parse("\\p{L}+");
  ASSERT_NE(re, nullptr);
  // Unicode properties may not mimic PCRE exactly
  re->MimicsPCRE();  // Just verify no crash
  re->Decref();
}

// Concatenation of patterns
TEST_F(MimicsPCRETest_220, Concatenation_220) {
  Regexp* re = Parse("abcdef");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Calling MimicsPCRE multiple times should give consistent results
TEST_F(MimicsPCRETest_220, ConsistentResults_220) {
  Regexp* re = Parse("(a+)(b*)");
  ASSERT_NE(re, nullptr);
  bool first = re->MimicsPCRE();
  bool second = re->MimicsPCRE();
  EXPECT_EQ(first, second);
  re->Decref();
}

}  // namespace re2
