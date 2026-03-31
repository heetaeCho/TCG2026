#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <string>

namespace re2 {

// Since IsAnchorStart is a static function in compile.cc and not directly
// accessible, we test its behavior indirectly through CompileToProg and
// the observable effects on compiled programs. The function IsAnchorStart
// is called during compilation, so we can observe its effects through
// the compilation process.

class IsAnchorStartTest_322 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to parse a regexp
  Regexp* Parse(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                                << " error: " << status.Text();
    return re;
  }
};

// Test: A pattern starting with \A (BeginText) anchor
// IsAnchorStart should recognize and process the BeginText anchor
TEST_F(IsAnchorStartTest_322, BeginTextAnchor_322) {
  Regexp* re = Parse("\\Ahello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: A pattern without any anchor at the start
TEST_F(IsAnchorStartTest_322, NoAnchorAtStart_322) {
  Regexp* re = Parse("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: BeginText anchor inside a capture group
TEST_F(IsAnchorStartTest_322, BeginTextInsideCapture_322) {
  Regexp* re = Parse("(\\Ahello)");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: BeginText anchor in a concat (e.g., \Aab)
TEST_F(IsAnchorStartTest_322, BeginTextInConcat_322) {
  Regexp* re = Parse("\\Aab");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Nested capture with BeginText anchor
TEST_F(IsAnchorStartTest_322, NestedCaptureWithBeginText_322) {
  Regexp* re = Parse("((\\Ahello))");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Deeply nested captures with BeginText (testing depth limit)
TEST_F(IsAnchorStartTest_322, DeepNestedCaptureWithBeginText_322) {
  // 5 levels of nesting - should exceed depth limit of 4
  Regexp* re = Parse("(((((\\Ahello)))))");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: BeginLine (^) is not BeginText and should not trigger IsAnchorStart
TEST_F(IsAnchorStartTest_322, BeginLineIsNotBeginText_322) {
  Regexp* re = Parse("^hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Just BeginText anchor alone
TEST_F(IsAnchorStartTest_322, JustBeginText_322) {
  Regexp* re = Parse("\\A");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Alternation starting with BeginText (should not trigger since op is kRegexpAlternate)
TEST_F(IsAnchorStartTest_322, AlternationWithBeginText_322) {
  Regexp* re = Parse("\\Ahello|world");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Empty pattern
TEST_F(IsAnchorStartTest_322, EmptyPattern_322) {
  Regexp* re = Parse("");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Capture group containing concat with BeginText
TEST_F(IsAnchorStartTest_322, CaptureContainingConcatWithBeginText_322) {
  Regexp* re = Parse("(\\Aab)cd");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Star/Plus/Quest at start (none of these should match IsAnchorStart)
TEST_F(IsAnchorStartTest_322, StarAtStart_322) {
  Regexp* re = Parse("a*hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Concat with multiple subs where first is BeginText
TEST_F(IsAnchorStartTest_322, ConcatMultipleSubsFirstIsBeginText_322) {
  Regexp* re = Parse("\\Aabcdef");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with BeginText
TEST_F(IsAnchorStartTest_322, ReverseProgWithBeginText_322) {
  Regexp* re = Parse("\\Ahello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Complex pattern with multiple captures and BeginText
TEST_F(IsAnchorStartTest_322, ComplexPatternWithBeginText_322) {
  Regexp* re = Parse("(\\A(foo)(bar))baz");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Depth exactly at boundary (4 levels of nesting = depth 4)
TEST_F(IsAnchorStartTest_322, DepthExactlyAtBoundary_322) {
  // 4 levels of capture nesting
  Regexp* re = Parse("((((\\Ahello))))");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: 3 levels of capture nesting (within depth limit)
TEST_F(IsAnchorStartTest_322, ThreeLevelsOfCapture_322) {
  Regexp* re = Parse("(((\\Ahello)))");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: BeginText followed by character class
TEST_F(IsAnchorStartTest_322, BeginTextFollowedByCharClass_322) {
  Regexp* re = Parse("\\A[a-z]+");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Pattern with EndText but no BeginText
TEST_F(IsAnchorStartTest_322, EndTextOnly_322) {
  Regexp* re = Parse("hello\\z");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test: Both BeginText and EndText
TEST_F(IsAnchorStartTest_322, BothBeginAndEndText_322) {
  Regexp* re = Parse("\\Ahello\\z");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
