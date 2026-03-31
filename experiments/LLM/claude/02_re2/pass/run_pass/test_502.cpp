#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

namespace re2 {

// Test fixture for ParseState tests
class ParseStateTest_502 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test DoLeftParenNoCapture through Parse interface
// The (?:...) syntax triggers DoLeftParenNoCapture internally
TEST_F(ParseStateTest_502, DoLeftParenNoCaptureBasic_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // Non-capturing group should not increase capture count
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureNested_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:(?:a)(?:b))", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureWithCapture_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:(a)(?:b))", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // Only the (a) should count as a capture
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureWithAlternation_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b|c)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureEmpty_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureRepeated_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)+", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureWithStar_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)*", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureWithQuestion_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)?", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureMultipleNonCapturing_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)(?:b)(?:c)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureComplex_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a(b)c)(?:(d)e)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // Two capturing groups inside non-capturing groups
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureDeeplyNested_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:(?:(?:(?:a))))", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureToString_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // The ToString should produce a valid regex string
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureWithFlags_502) {
  RegexpStatus status;
  // (?i:abc) is a non-capturing group with flag modification
  Regexp* re = Regexp::Parse("(?i:abc)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, CaptureVsNonCaptureCounting_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(?:b)(c)(?:d)(e)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // Only (a), (c), (e) are captures
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureWithRepetition_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc){2,5}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(ParseStateTest_502, DoLeftParenNoCaptureSimplify_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test PushLiteral through Parse
TEST_F(ParseStateTest_502, PushLiteralBasic_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test DoLeftParen through Parse
TEST_F(ParseStateTest_502, DoLeftParenCapture_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test named capture groups
TEST_F(ParseStateTest_502, DoLeftParenNamedCapture_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->count("name"), 1);
  delete named;
  re->Decref();
}

// Test DoVerticalBar through Parse
TEST_F(ParseStateTest_502, DoVerticalBar_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushDot through Parse
TEST_F(ParseStateTest_502, PushDot_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushCaret through Parse
TEST_F(ParseStateTest_502, PushCaret_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushDollar through Parse
TEST_F(ParseStateTest_502, PushDollar_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc$", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test complex pattern combining non-capturing and other features
TEST_F(ParseStateTest_502, ComplexPatternWithNonCapture_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^(?:foo|bar)+(?:baz)*$", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test error case: unmatched right paren
TEST_F(ParseStateTest_502, UnmatchedRightParen_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc))", Regexp::PerlX, &status);
  EXPECT_EQ(re, nullptr);
}

// Test error case: unmatched left paren
TEST_F(ParseStateTest_502, UnmatchedLeftParen_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc", Regexp::PerlX, &status);
  EXPECT_EQ(re, nullptr);
}

// Test POSIX flags with non-capturing groups
TEST_F(ParseStateTest_502, DoLeftParenNoCapturePOSIX_502) {
  RegexpStatus status;
  // POSIX doesn't support (?:...) but PerlX does
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::PerlX | Regexp::OneLine, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test word boundary inside non-capturing group
TEST_F(ParseStateTest_502, WordBoundaryInNonCapture_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:\\bfoo\\b)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test character class inside non-capturing group
TEST_F(ParseStateTest_502, CharClassInNonCapture_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:[a-z]+)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test empty string parse
TEST_F(ParseStateTest_502, EmptyStringParse_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test non-greedy inside non-capturing group
TEST_F(ParseStateTest_502, NonGreedyInNonCapture_502) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a+?b*?)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

}  // namespace re2
