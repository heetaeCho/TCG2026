#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test compilation of simple literals
TEST(CompilerTest_304, CompileSimpleLiteral_304) {
  Regexp* re = Regexp::Parse("a", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of concatenation
TEST(CompilerTest_304, CompileConcatenation_304) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of alternation
TEST(CompilerTest_304, CompileAlternation_304) {
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of star (Kleene closure)
TEST(CompilerTest_304, CompileStar_304) {
  Regexp* re = Regexp::Parse("a*", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of plus
TEST(CompilerTest_304, CompilePlus_304) {
  Regexp* re = Regexp::Parse("a+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of question mark (optional)
TEST(CompilerTest_304, CompileQuest_304) {
  Regexp* re = Regexp::Parse("a?", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with capture groups
TEST(CompilerTest_304, CompileCapture_304) {
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of character class
TEST(CompilerTest_304, CompileCharClass_304) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of dot (any character)
TEST(CompilerTest_304, CompileDot_304) {
  Regexp* re = Regexp::Parse(".", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with reversed flag
TEST(CompilerTest_304, CompileReversed_304) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with very small memory limit
TEST(CompilerTest_304, CompileSmallMemoryLimit_304) {
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit may cause compilation to fail (return nullptr)
  Prog* prog = Compiler::Compile(re, false, 1);
  // Either it compiles or it doesn't - we just check it doesn't crash
  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test compilation of empty regex
TEST(CompilerTest_304, CompileEmptyRegex_304) {
  Regexp* re = Regexp::Parse("", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of complex regex
TEST(CompilerTest_304, CompileComplexRegex_304) {
  Regexp* re = Regexp::Parse("(foo|bar)+baz[0-9]*", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of non-greedy quantifiers
TEST(CompilerTest_304, CompileNonGreedy_304) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of anchors
TEST(CompilerTest_304, CompileAnchors_304) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of Unicode character classes
TEST(CompilerTest_304, CompileUnicode_304) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST(CompilerTest_304, CompileSetUnanchored_304) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST(CompilerTest_304, CompileSetAnchorBoth_304) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST(CompilerTest_304, CompileSetAnchorStart_304) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of case-insensitive regex
TEST(CompilerTest_304, CompileCaseInsensitive_304) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of repetition with bounds
TEST(CompilerTest_304, CompileRepetitionBounded_304) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiled program size is reasonable
TEST(CompilerTest_304, CompileProgramSize_304) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation of nested groups
TEST(CompilerTest_304, CompileNestedGroups_304) {
  Regexp* re = Regexp::Parse("((a|b)(c|d))+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of word boundary
TEST(CompilerTest_304, CompileWordBoundary_304) {
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program can match correctly via RE2
TEST(CompilerTest_304, CompiledProgramMatches_304) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test compiled program for alternation matches correctly
TEST(CompilerTest_304, CompiledAlternationMatches_304) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("I have a cat", re));
  EXPECT_TRUE(RE2::PartialMatch("I have a dog", re));
  EXPECT_FALSE(RE2::PartialMatch("I have a fish", re));
}

// Test compilation with memory limit that allows compilation
TEST(CompilerTest_304, CompileWithAdequateMemory_304) {
  Regexp* re = Regexp::Parse("a+b+c+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of large character class
TEST(CompilerTest_304, CompileLargeCharClass_304) {
  Regexp* re = Regexp::Parse("[a-zA-Z0-9_\\-\\.]+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test reversed compilation produces a valid program
TEST(CompilerTest_304, CompileReversedProducesValidProgram_304) {
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation of regex with escape sequences
TEST(CompilerTest_304, CompileEscapeSequences_304) {
  Regexp* re = Regexp::Parse("\\d+\\.\\d+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that null regexp input is handled (compile should handle gracefully)
TEST(CompilerTest_304, CompileNullRegexp_304) {
  // Passing nullptr - test that it doesn't crash
  // The behavior may vary; we mainly want no crash.
  Prog* prog = Compiler::Compile(nullptr, false, 1 << 20);
  // It's acceptable to return nullptr for null input
  if (prog != nullptr) {
    delete prog;
  }
}

}  // namespace re2
