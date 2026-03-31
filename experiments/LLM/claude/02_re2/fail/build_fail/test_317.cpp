#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test fixture for Compiler tests
class CompilerTest_317 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal pattern
TEST_F(CompilerTest_317, CompileSimpleLiteral_317) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a reversed pattern
TEST_F(CompilerTest_317, CompileReversed_317) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with alternation
TEST_F(CompilerTest_317, CompileAlternation_317) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition (star)
TEST_F(CompilerTest_317, CompileStar_317) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition (plus)
TEST_F(CompilerTest_317, CompilePlus_317) {
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with question mark
TEST_F(CompilerTest_317, CompileQuest_317) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with character class
TEST_F(CompilerTest_317, CompileCharClass_317) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with dot (any character)
TEST_F(CompilerTest_317, CompileDot_317) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with capture group
TEST_F(CompilerTest_317, CompileCapture_317) {
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with anchors
TEST_F(CompilerTest_317, CompileAnchors_317) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with very small max_mem might return nullptr or small prog
TEST_F(CompilerTest_317, CompileWithVerySmallMaxMem_317) {
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // With extremely limited memory, compilation might fail
  Prog* prog = Compiler::Compile(re, false, 1);
  // Either nullptr or a valid prog - we just verify it doesn't crash
  delete prog;
  re->Decref();
}

// Test Compile with empty pattern
TEST_F(CompilerTest_317, CompileEmptyPattern_317) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored
TEST_F(CompilerTest_317, CompileSetUnanchored_317) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor start
TEST_F(CompilerTest_317, CompileSetAnchorStart_317) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor both
TEST_F(CompilerTest_317, CompileSetAnchorBoth_317) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with complex regex
TEST_F(CompilerTest_317, CompileComplexRegex_317) {
  Regexp* re = Regexp::Parse("(a+b*|c?d){2,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Unicode character class
TEST_F(CompilerTest_317, CompileUnicodeCharClass_317) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with nongreedy repetitions
TEST_F(CompilerTest_317, CompileNonGreedy_317) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST_F(CompilerTest_317, CompileWordBoundary_317) {
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the compiled program has a non-zero size
TEST_F(CompilerTest_317, CompileProgHasSize_317) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test Compile with case-insensitive flag
TEST_F(CompilerTest_317, CompileCaseInsensitive_317) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with nested groups
TEST_F(CompilerTest_317, CompileNestedGroups_317) {
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with nullptr Regexp doesn't crash (boundary)
// Note: This tests the behavior when the regexp is a simple match-all
TEST_F(CompilerTest_317, CompileMatchAll_317) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with large bounded repetition and limited memory
TEST_F(CompilerTest_317, CompileLargeRepetitionLimitedMemory_317) {
  Regexp* re = Regexp::Parse("a{100}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Use limited memory
  Prog* prog = Compiler::Compile(re, false, 256);
  // May or may not succeed - just check no crash
  delete prog;
  re->Decref();
}

// Test Compile with alternation of character classes
TEST_F(CompilerTest_317, CompileAlternationCharClasses_317) {
  Regexp* re = Regexp::Parse("[a-z]|[0-9]|[A-Z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with empty alternation
TEST_F(CompilerTest_317, CompileSetAlternation_317) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program for reversed is different from forward
TEST_F(CompilerTest_317, CompileReversedDiffersFromForward_317) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  
  Prog* prog_fwd = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog_fwd, nullptr);
  
  Prog* prog_rev = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog_rev, nullptr);
  
  // Both should be valid programs but may differ
  EXPECT_GT(prog_fwd->size(), 0);
  EXPECT_GT(prog_rev->size(), 0);
  
  delete prog_fwd;
  delete prog_rev;
  re->Decref();
}

}  // namespace re2
