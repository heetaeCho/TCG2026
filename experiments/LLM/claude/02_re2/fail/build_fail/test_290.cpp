#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test through the public static interface: Compiler::Compile and Compiler::CompileSet
// Since Compiler is mostly used internally, we test it through these static methods
// and through RE2 which exercises the compiler.

class CompilerTest_290 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal
TEST_F(CompilerTest_290, CompileSimpleLiteral_290) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a character class
TEST_F(CompilerTest_290, CompileCharacterClass_290) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with reversed flag
TEST_F(CompilerTest_290, CompileReversed_290) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with alternation
TEST_F(CompilerTest_290, CompileAlternation_290) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition (star)
TEST_F(CompilerTest_290, CompileStar_290) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition (plus)
TEST_F(CompilerTest_290, CompilePlus_290) {
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition (quest)
TEST_F(CompilerTest_290, CompileQuest_290) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with capture groups
TEST_F(CompilerTest_290, CompileCaptureGroup_290) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with empty regex
TEST_F(CompilerTest_290, CompileEmptyRegex_290) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with dot
TEST_F(CompilerTest_290, CompileDot_290) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with anchors
TEST_F(CompilerTest_290, CompileAnchors_290) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with very small max_mem might return nullptr for complex regex
TEST_F(CompilerTest_290, CompileWithVerySmallMaxMem_290) {
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small max_mem - may or may not return nullptr depending on complexity
  Prog* prog = Compiler::Compile(re, false, 1);
  // If it returns nullptr, that's expected for insufficient memory
  // If it returns non-null, that's also fine
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST_F(CompilerTest_290, CompileSetUnanchored_290) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_290, CompileSetAnchorStart_290) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_290, CompileSetAnchorBoth_290) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Unicode character class
TEST_F(CompilerTest_290, CompileUnicodeClass_290) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with non-greedy repetition
TEST_F(CompilerTest_290, CompileNonGreedy_290) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with complex nested groups
TEST_F(CompilerTest_290, CompileNestedGroups_290) {
  Regexp* re = Regexp::Parse("((a|b)*c)+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST_F(CompilerTest_290, CompileWordBoundary_290) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with counted repetition
TEST_F(CompilerTest_290, CompileCountedRepetition_290) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program can actually match (integration-like test)
TEST_F(CompilerTest_290, CompiledProgramMatchesCorrectly_290) {
  RE2 pattern("hello");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Test that compiled program handles alternation matching
TEST_F(CompilerTest_290, CompiledAlternationMatches_290) {
  RE2 pattern("cat|dog|bird");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::PartialMatch("I have a cat", pattern));
  EXPECT_TRUE(RE2::PartialMatch("I have a dog", pattern));
  EXPECT_TRUE(RE2::PartialMatch("I have a bird", pattern));
  EXPECT_FALSE(RE2::PartialMatch("I have a fish", pattern));
}

// Test compile with case-insensitive flag
TEST_F(CompilerTest_290, CompileCaseInsensitive_290) {
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with dot-star pattern (commonly used in DFA)
TEST_F(CompilerTest_290, CompileDotStar_290) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiling a moderately complex regex doesn't crash
TEST_F(CompilerTest_290, CompileModeratelyComplex_290) {
  Regexp* re = Regexp::Parse(
      "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$",
      Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with high unicode ranges
TEST_F(CompilerTest_290, CompileHighUnicode_290) {
  Regexp* re = Regexp::Parse("[\\x{10000}-\\x{10FFFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the program size is non-zero for a non-trivial regex
TEST_F(CompilerTest_290, CompiledProgramHasInstructions_290) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test Compile with Latin1 encoding
TEST_F(CompilerTest_290, CompileLatin1_290) {
  Regexp* re = Regexp::Parse("[\\x80-\\xff]",
                              Regexp::LikePerl | Regexp::Latin1, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
