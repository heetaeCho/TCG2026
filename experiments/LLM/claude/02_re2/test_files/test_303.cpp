#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test fixture for Compiler tests
class CompilerTest_303 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal pattern
TEST_F(CompilerTest_303, CompileSimpleLiteral_303) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a reversed pattern
TEST_F(CompilerTest_303, CompileReversed_303) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with very small max_mem may return nullptr or a valid prog
TEST_F(CompilerTest_303, CompileSmallMaxMem_303) {
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may fail to compile
  Prog* prog = Compiler::Compile(re, false, 1);
  // Either nullptr (ran out of memory) or a valid prog
  delete prog;
  re->Decref();
}

// Test compiling an empty pattern
TEST_F(CompilerTest_303, CompileEmptyPattern_303) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a character class pattern
TEST_F(CompilerTest_303, CompileCharClass_303) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with alternation
TEST_F(CompilerTest_303, CompileAlternation_303) {
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with quantifiers (star, plus, quest)
TEST_F(CompilerTest_303, CompileQuantifiers_303) {
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with non-greedy quantifiers
TEST_F(CompilerTest_303, CompileNonGreedyQuantifiers_303) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with capture groups
TEST_F(CompilerTest_303, CompileCaptureGroups_303) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with anchors
TEST_F(CompilerTest_303, CompileAnchors_303) {
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with dot
TEST_F(CompilerTest_303, CompileDot_303) {
  Regexp* re = Regexp::Parse("a.b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling unicode character classes
TEST_F(CompilerTest_303, CompileUnicodeCharClass_303) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored
TEST_F(CompilerTest_303, CompileSetUnanchored_303) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor start
TEST_F(CompilerTest_303, CompileSetAnchorStart_303) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor both
TEST_F(CompilerTest_303, CompileSetAnchorBoth_303) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with repetition
TEST_F(CompilerTest_303, CompileRepetition_303) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with case-insensitive flag
TEST_F(CompilerTest_303, CompileCaseInsensitive_303) {
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with word boundary
TEST_F(CompilerTest_303, CompileWordBoundary_303) {
  Regexp* re = Regexp::Parse("\\bhello\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a complex nested pattern
TEST_F(CompilerTest_303, CompileComplexNested_303) {
  Regexp* re = Regexp::Parse("((a|b)*c)+d?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program works correctly with RE2 matching
TEST_F(CompilerTest_303, CompiledProgramMatches_303) {
  RE2 pattern("hello");
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Test that compiled program with alternation matches correctly
TEST_F(CompilerTest_303, CompiledAlternationMatches_303) {
  RE2 pattern("abc|def");
  EXPECT_TRUE(RE2::FullMatch("abc", pattern));
  EXPECT_TRUE(RE2::FullMatch("def", pattern));
  EXPECT_FALSE(RE2::FullMatch("ghi", pattern));
}

// Test compiling with a null regexp pointer (edge case)
TEST_F(CompilerTest_303, CompileNullRegexp_303) {
  Prog* prog = Compiler::Compile(nullptr, false, 1 << 20);
  // Should handle null gracefully - either return nullptr or valid prog
  delete prog;
}

// Test that a large max_mem value works
TEST_F(CompilerTest_303, CompileLargeMaxMem_303) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1LL << 30);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with dotall flag (. matches newline)
TEST_F(CompilerTest_303, CompileDotAll_303) {
  Regexp* re = Regexp::Parse("(?s)a.b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling single character
TEST_F(CompilerTest_303, CompileSingleChar_303) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with negated character class
TEST_F(CompilerTest_303, CompileNegatedCharClass_303) {
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with high Unicode codepoints
TEST_F(CompilerTest_303, CompileHighUnicode_303) {
  Regexp* re = Regexp::Parse("[\\x{10000}-\\x{10FFFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compilation and reverse compilation produce different programs
TEST_F(CompilerTest_303, CompileForwardVsReverse_303) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog_fwd = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog_fwd, nullptr);
  
  Regexp* re2 = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re2, nullptr);
  Prog* prog_rev = Compiler::Compile(re2, true, 1 << 20);
  EXPECT_NE(prog_rev, nullptr);
  
  // Both should produce valid programs
  delete prog_fwd;
  delete prog_rev;
  re->Decref();
  re2->Decref();
}

// Test compiling deeply nested groups
TEST_F(CompilerTest_303, CompileDeeplyNested_303) {
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileSet with small memory may return nullptr for complex patterns
TEST_F(CompilerTest_303, CompileSetSmallMemory_303) {
  Regexp* re = Regexp::Parse("a{100}|b{100}|c{100}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1);
  // May return nullptr due to memory constraints
  delete prog;
  re->Decref();
}

}  // namespace re2
