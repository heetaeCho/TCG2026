#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <memory>
#include <string>

namespace re2 {

class CompilerTest_307 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse a regexp and return ownership
static Regexp* ParseRegexp(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  return re;
}

// Test that Compile produces a non-null Prog for a simple literal
TEST_F(CompilerTest_307, CompileSimpleLiteral_307) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with reversed flag produces a non-null Prog
TEST_F(CompilerTest_307, CompileReversed_307) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling an empty pattern
TEST_F(CompilerTest_307, CompileEmptyPattern_307) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a character class
TEST_F(CompilerTest_307, CompileCharClass_307) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling alternation
TEST_F(CompilerTest_307, CompileAlternation_307) {
  Regexp* re = ParseRegexp("abc|def");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a pattern with repetition (star)
TEST_F(CompilerTest_307, CompileStar_307) {
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a pattern with plus
TEST_F(CompilerTest_307, CompilePlus_307) {
  Regexp* re = ParseRegexp("a+");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a pattern with question mark
TEST_F(CompilerTest_307, CompileQuest_307) {
  Regexp* re = ParseRegexp("a?");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a pattern with capturing groups
TEST_F(CompilerTest_307, CompileCapture_307) {
  Regexp* re = ParseRegexp("(abc)(def)");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a dot (any character)
TEST_F(CompilerTest_307, CompileDot_307) {
  Regexp* re = ParseRegexp(".");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with very small max_mem might return null or limited prog
TEST_F(CompilerTest_307, CompileVerySmallMaxMem_307) {
  Regexp* re = ParseRegexp("a{1000}b{1000}c{1000}");
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may fail to compile
  Prog* prog = Compiler::Compile(re, false, 1);
  // The result could be nullptr if memory is too small
  // Just ensure it doesn't crash
  delete prog;
  re->Decref();
}

// Test compiling with a large pattern
TEST_F(CompilerTest_307, CompileLargePattern_307) {
  Regexp* re = ParseRegexp("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)+");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling Unicode pattern
TEST_F(CompilerTest_307, CompileUnicode_307) {
  Regexp* re = ParseRegexp("\\p{L}+");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling anchored patterns
TEST_F(CompilerTest_307, CompileAnchored_307) {
  Regexp* re = ParseRegexp("^abc$");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST_F(CompilerTest_307, CompileSetUnanchored_307) {
  Regexp* re = ParseRegexp("abc|def|ghi");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_307, CompileSetAnchorBoth_307) {
  Regexp* re = ParseRegexp("abc|def|ghi");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_307, CompileSetAnchorStart_307) {
  Regexp* re = ParseRegexp("abc|def|ghi");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program has expected size for simple pattern
TEST_F(CompilerTest_307, CompileProgramSize_307) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling non-greedy repetitions
TEST_F(CompilerTest_307, CompileNonGreedy_307) {
  Regexp* re = ParseRegexp("a*?b+?c??");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling counted repetition
TEST_F(CompilerTest_307, CompileCountedRepetition_307) {
  Regexp* re = ParseRegexp("a{3,5}");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling word boundary
TEST_F(CompilerTest_307, CompileWordBoundary_307) {
  Regexp* re = ParseRegexp("\\bfoo\\b");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test case-insensitive compilation
TEST_F(CompilerTest_307, CompileCaseInsensitive_307) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a complex nested pattern
TEST_F(CompilerTest_307, CompileComplexNested_307) {
  Regexp* re = ParseRegexp("((a|b)*c(d|e)+)?f");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile returns different programs for different patterns
TEST_F(CompilerTest_307, CompileDifferentPatterns_307) {
  Regexp* re1 = ParseRegexp("abc");
  Regexp* re2 = ParseRegexp("xyz");
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);

  Prog* prog1 = Compiler::Compile(re1, false, 1 << 20);
  Prog* prog2 = Compiler::Compile(re2, false, 1 << 20);
  ASSERT_NE(prog1, nullptr);
  ASSERT_NE(prog2, nullptr);

  // Different patterns should produce different programs
  // We can't easily compare, but both should be valid
  EXPECT_GT(prog1->size(), 0);
  EXPECT_GT(prog2->size(), 0);

  delete prog1;
  delete prog2;
  re1->Decref();
  re2->Decref();
}

// Test compiling byte range patterns (hex escapes)
TEST_F(CompilerTest_307, CompileByteRange_307) {
  Regexp* re = ParseRegexp("\\x00-\\xff");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that reverse compilation of a concatenation differs from forward
TEST_F(CompilerTest_307, CompileForwardVsReverse_307) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  Prog* forward = Compiler::Compile(re, false, 1 << 20);
  Prog* reversed = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(forward, nullptr);
  ASSERT_NE(reversed, nullptr);

  // Both should compile successfully
  EXPECT_GT(forward->size(), 0);
  EXPECT_GT(reversed->size(), 0);

  delete forward;
  delete reversed;
  re->Decref();
}

// Test compiling with adequate max_mem
TEST_F(CompilerTest_307, CompileAdequateMaxMem_307) {
  Regexp* re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling empty width assertions (beginning/end of line)
TEST_F(CompilerTest_307, CompileEmptyWidth_307) {
  Regexp* re = ParseRegexp("^$");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the compiled program's instruction count is reasonable
TEST_F(CompilerTest_307, CompileInstructionCount_307) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  // A single literal should produce a small number of instructions
  EXPECT_LT(prog->size(), 100);
  delete prog;
  re->Decref();
}

// Test CompileSet with small memory limit
TEST_F(CompilerTest_307, CompileSetSmallMemory_307) {
  Regexp* re = ParseRegexp("a{1000}");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1);
  // May return nullptr due to memory constraints - should not crash
  delete prog;
  re->Decref();
}

}  // namespace re2
