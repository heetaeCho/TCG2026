#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/compile.cc"
#include <memory>
#include <string>

namespace re2 {

class CompilerTest_308 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Compile returns a non-null Prog for a simple regex
TEST_F(CompilerTest_308, CompileSimpleRegex_308) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with reversed flag
TEST_F(CompilerTest_308, CompileReversed_308) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with very small max_mem to trigger failure/limits
TEST_F(CompilerTest_308, CompileSmallMaxMem_308) {
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may return nullptr or a truncated program
  Prog* prog = Compiler::Compile(re, false, 1);
  // With extremely tight memory, compilation may fail
  // We just check it doesn't crash
  delete prog;
  re->Decref();
}

// Test Compile with empty pattern
TEST_F(CompilerTest_308, CompileEmptyPattern_308) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with character class
TEST_F(CompilerTest_308, CompileCharClass_308) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with alternation
TEST_F(CompilerTest_308, CompileAlternation_308) {
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition operators
TEST_F(CompilerTest_308, CompileRepetition_308) {
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with captures
TEST_F(CompilerTest_308, CompileCaptures_308) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Unicode
TEST_F(CompilerTest_308, CompileUnicode_308) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with dot
TEST_F(CompilerTest_308, CompileDot_308) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with anchors
TEST_F(CompilerTest_308, CompileAnchors_308) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED anchor
TEST_F(CompilerTest_308, CompileSetUnanchored_308) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_308, CompileSetAnchorStart_308) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_308, CompileSetAnchorBoth_308) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with complex nested expression
TEST_F(CompilerTest_308, CompileComplexNested_308) {
  Regexp* re = Regexp::Parse("((a|b)*c)+d?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with counted repetition
TEST_F(CompilerTest_308, CompileCountedRepetition_308) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with non-greedy operators
TEST_F(CompilerTest_308, CompileNonGreedy_308) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST_F(CompilerTest_308, CompileWordBoundary_308) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Latin1 encoding
TEST_F(CompilerTest_308, CompileLatin1_308) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::Latin1, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile produces a program that can match (integration-style verification)
TEST_F(CompilerTest_308, CompiledProgramMatches_308) {
  RE2 pattern("hello");
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Test Compile with single character
TEST_F(CompilerTest_308, CompileSingleChar_308) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with case-insensitive flag
TEST_F(CompilerTest_308, CompileCaseInsensitive_308) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile returns valid program size
TEST_F(CompilerTest_308, CompileProgramSize_308) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test memory limit enforcement with large regex
TEST_F(CompilerTest_308, CompileMemoryLimitEnforcement_308) {
  // Create a regex that would require significant memory
  std::string big_pattern;
  for (int i = 0; i < 100; i++) {
    big_pattern += "(a|b|c|d|e|f|g|h|i|j)";
  }
  Regexp* re = Regexp::Parse(big_pattern, Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Use a small memory limit
  Prog* prog = Compiler::Compile(re, false, 256);
  // May or may not return nullptr depending on actual memory usage
  // Just ensure no crash
  delete prog;
  re->Decref();
}

// Test Compile with escape sequences
TEST_F(CompilerTest_308, CompileEscapeSequences_308) {
  Regexp* re = Regexp::Parse("\\d+\\.\\d+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with empty alternation-like pattern
TEST_F(CompilerTest_308, CompileSetAlternation_308) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with deeply nested groups
TEST_F(CompilerTest_308, CompileDeeplyNested_308) {
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that multiple compiles work independently
TEST_F(CompilerTest_308, MultipleCompiles_308) {
  Regexp* re1 = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  Regexp* re2 = Regexp::Parse("def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);

  Prog* prog1 = Compiler::Compile(re1, false, 1 << 20);
  Prog* prog2 = Compiler::Compile(re2, false, 1 << 20);

  EXPECT_NE(prog1, nullptr);
  EXPECT_NE(prog2, nullptr);

  delete prog1;
  delete prog2;
  re1->Decref();
  re2->Decref();
}

// Test Compile with large character class ranges
TEST_F(CompilerTest_308, CompileLargeCharClass_308) {
  Regexp* re = Regexp::Parse("[\\x00-\\xff]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with UTF8 range patterns
TEST_F(CompilerTest_308, CompileUTF8Range_308) {
  Regexp* re = Regexp::Parse("[\\x{100}-\\x{10FFFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program from Compile has correct start
TEST_F(CompilerTest_308, CompileProgramHasStart_308) {
  Regexp* re = Regexp::Parse("test", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GE(prog->start(), 0);
  delete prog;
  re->Decref();
}

}  // namespace re2
