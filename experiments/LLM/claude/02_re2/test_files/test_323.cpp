#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <string>

namespace re2 {

// We test the IsAnchorEnd behavior indirectly through the public interface,
// since IsAnchorEnd is a static function used internally during compilation.
// The observable effect of IsAnchorEnd is that when compiling a regex that
// ends with $, the compiled program may have anchor-end behavior.
// We use CompileToProg and CompileToReverseProg, as well as Parse/ToString/Dump
// to observe behavior.

class IsAnchorEndTest_323 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: A simple pattern ending with \z (EndText) should be recognized as anchor-end.
// We verify this through compilation behavior.
TEST_F(IsAnchorEndTest_323, SimpleEndTextAnchor_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  // The program should compile successfully for a pattern with end anchor
  delete prog;
  re->Decref();
}

// Test: Pattern without end anchor
TEST_F(IsAnchorEndTest_323, NoEndAnchor_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Concat ending with EndText (e.g., "abc$" in single-line mode uses \z)
TEST_F(IsAnchorEndTest_323, ConcatEndingWithEndText_323) {
  RegexpStatus status;
  // Using (?s) for single-line, \z is end of text
  Regexp* re = Regexp::Parse("abc\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Capture group ending with EndText
TEST_F(IsAnchorEndTest_323, CaptureEndingWithEndText_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc\\z)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Nested captures ending with EndText
TEST_F(IsAnchorEndTest_323, NestedCaptureEndingWithEndText_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((abc\\z))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Deeply nested captures (depth >= 4 should stop recursion)
TEST_F(IsAnchorEndTest_323, DeeplyNestedCaptureEndText_323) {
  RegexpStatus status;
  // 5 levels of nesting - should exceed depth limit of 4
  Regexp* re = Regexp::Parse("(((((abc\\z)))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Concat with capture ending in EndText
TEST_F(IsAnchorEndTest_323, ConcatWithCaptureEndText_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc(def\\z)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: EndLine ($ in multiline mode) is NOT EndText
TEST_F(IsAnchorEndTest_323, EndLineIsNotEndText_323) {
  RegexpStatus status;
  // $ in OneLine mode maps to EndText, but in multiline it's EndLine
  Regexp* re = Regexp::Parse("abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Pattern with only EndText
TEST_F(IsAnchorEndTest_323, OnlyEndText_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Alternation is not handled by IsAnchorEnd (should not crash)
TEST_F(IsAnchorEndTest_323, AlternationNotHandled_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc|def)\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Complex pattern with EndText at end of concat
TEST_F(IsAnchorEndTest_323, ComplexConcatEndText_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a.b[cd]e\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with end anchor
TEST_F(IsAnchorEndTest_323, ReverseProgWithEndAnchor_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Star/Plus/Quest are not handled by IsAnchorEnd (default case)
TEST_F(IsAnchorEndTest_323, StarNotHandled_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Empty pattern compiles successfully
TEST_F(IsAnchorEndTest_323, EmptyPattern_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Concat with single sub ending in EndText
TEST_F(IsAnchorEndTest_323, SingleSubConcat_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Multiple captures nested with concat ending in EndText
TEST_F(IsAnchorEndTest_323, MultipleCapturesConcat_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c\\z)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Both begin and end anchors
TEST_F(IsAnchorEndTest_323, BothAnchors_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\Aabc\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: EndText inside capture inside concat
TEST_F(IsAnchorEndTest_323, EndTextInsideCaptureInsideConcat_323) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello(world(\\z))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Exactly at depth boundary (depth 3 captures + EndText)
TEST_F(IsAnchorEndTest_323, DepthBoundaryThreeCapturesEndText_323) {
  RegexpStatus status;
  // 3 nested captures + EndText = depth goes 0->1->2->3 which is < 4, should work
  Regexp* re = Regexp::Parse("(((\\z)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

// Test: Exactly at depth 4 captures (should hit depth >= 4 and return false)
TEST_F(IsAnchorEndTest_323, DepthFourCapturesEndText_323) {
  RegexpStatus status;
  // 4 nested captures: depth goes 0->1->2->3->4 which is >= 4
  Regexp* re = Regexp::Parse("((((\\z))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  delete prog;
  re->Decref();
}

}  // namespace re2
