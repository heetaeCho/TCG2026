#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test through the public static Compile interface since Compiler's constructor
// and most methods are not easily accessible directly.

class CompilerTest_306 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test basic compilation of a simple literal pattern
TEST_F(CompilerTest_306, CompileSimpleLiteral_306) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of a reversed pattern
TEST_F(CompilerTest_306, CompileReversed_306) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with a character class
TEST_F(CompilerTest_306, CompileCharacterClass_306) {
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with alternation
TEST_F(CompilerTest_306, CompileAlternation_306) {
  Regexp* re = Regexp::Parse("foo|bar|baz", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with repetition
TEST_F(CompilerTest_306, CompileRepetition_306) {
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with capture groups
TEST_F(CompilerTest_306, CompileCaptureGroups_306) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with dot (any character)
TEST_F(CompilerTest_306, CompileDot_306) {
  Regexp* re = Regexp::Parse("a.b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with anchors
TEST_F(CompilerTest_306, CompileAnchors_306) {
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with very small max_mem — may fail or produce limited program
TEST_F(CompilerTest_306, CompileWithVerySmallMaxMem_306) {
  Regexp* re = Regexp::Parse("a{100,200}b{100,200}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit — compilation might return nullptr
  Prog* prog = Compiler::Compile(re, false, 1);
  // Whether it succeeds or fails, just check it doesn't crash
  delete prog;
  re->Decref();
}

// Test compilation with empty pattern
TEST_F(CompilerTest_306, CompileEmptyPattern_306) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST_F(CompilerTest_306, CompileSetUnanchored_306) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_306, CompileSetAnchorBoth_306) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_306, CompileSetAnchorStart_306) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with Unicode/UTF-8 patterns
TEST_F(CompilerTest_306, CompileUnicodePattern_306) {
  Regexp* re = Regexp::Parse("\\p{Greek}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of non-greedy repetitions
TEST_F(CompilerTest_306, CompileNonGreedy_306) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with case-insensitive flag
TEST_F(CompilerTest_306, CompileCaseInsensitive_306) {
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with complex nested pattern
TEST_F(CompilerTest_306, CompileComplexNested_306) {
  Regexp* re = Regexp::Parse("((a|b)*c(d|e)+)?f", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CachedRuneByteSuffix returns the same result for the same inputs
// This is tested indirectly through compiling patterns that reuse byte ranges.
TEST_F(CompilerTest_306, CachingConsistencyViaCompile_306) {
  // Compile a pattern with repeated character classes that should hit the cache
  Regexp* re = Regexp::Parse("[a-z][a-z][a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with large bounded repetition
TEST_F(CompilerTest_306, CompileLargeBoundedRepetition_306) {
  Regexp* re = Regexp::Parse("a{1,50}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with word boundary
TEST_F(CompilerTest_306, CompileWordBoundary_306) {
  Regexp* re = Regexp::Parse("\\bhello\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the compiled program for a simple pattern actually works for matching
TEST_F(CompilerTest_306, CompiledProgramMatchesFunctionally_306) {
  RE2 pattern("hello");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Test that compilation handles null regexp gracefully (if nullptr not expected, at least test non-null)
TEST_F(CompilerTest_306, CompileWithLargeMemLimit_306) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1LL << 30);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with very small memory
TEST_F(CompilerTest_306, CompileSetSmallMemory_306) {
  Regexp* re = Regexp::Parse("a{100,200}b{100,200}c{100,200}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1);
  // May return nullptr due to memory constraint
  delete prog;
  re->Decref();
}

// Test compilation with Latin1 encoding
TEST_F(CompilerTest_306, CompileLatin1_306) {
  Regexp* re = Regexp::Parse("[\\x00-\\xff]+", Regexp::Latin1 | Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a single character pattern compiles and produces a valid program
TEST_F(CompilerTest_306, CompileSingleChar_306) {
  Regexp* re = Regexp::Parse("x", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

}  // namespace re2
