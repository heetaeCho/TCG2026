#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <string>
#include <memory>

namespace re2 {

// Test fixture for Compiler tests via the public static interface
class CompilerTest_298 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal pattern
TEST_F(CompilerTest_298, CompileSimpleLiteral_298) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile works with reversed flag
TEST_F(CompilerTest_298, CompileReversed_298) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of an alternation pattern
TEST_F(CompilerTest_298, CompileAlternation_298) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of a repetition pattern (star)
TEST_F(CompilerTest_298, CompileStar_298) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of a plus repetition
TEST_F(CompilerTest_298, CompilePlus_298) {
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of a question mark (optional)
TEST_F(CompilerTest_298, CompileQuest_298) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of a capture group
TEST_F(CompilerTest_298, CompileCapture_298) {
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of character class
TEST_F(CompilerTest_298, CompileCharacterClass_298) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of empty width assertions
TEST_F(CompilerTest_298, CompileEmptyWidth_298) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with very small max_mem - should still return a prog or nullptr
TEST_F(CompilerTest_298, CompileSmallMaxMem_298) {
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may fail gracefully
  Prog* prog = Compiler::Compile(re, false, 64);
  // It either returns nullptr or a valid prog
  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test compilation of a dot pattern
TEST_F(CompilerTest_298, CompileDot_298) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of non-greedy repetition
TEST_F(CompilerTest_298, CompileNonGreedy_298) {
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of concatenation
TEST_F(CompilerTest_298, CompileConcatenation_298) {
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of complex pattern
TEST_F(CompilerTest_298, CompileComplexPattern_298) {
  Regexp* re = Regexp::Parse("(a+|b*c)?[d-f]{2,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored anchor
TEST_F(CompilerTest_298, CompileSetUnanchored_298) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor start
TEST_F(CompilerTest_298, CompileSetAnchorStart_298) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor both
TEST_F(CompilerTest_298, CompileSetAnchorBoth_298) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of Unicode pattern
TEST_F(CompilerTest_298, CompileUnicode_298) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of word boundary
TEST_F(CompilerTest_298, CompileWordBoundary_298) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of nested groups
TEST_F(CompilerTest_298, CompileNestedGroups_298) {
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program size is reasonable
TEST_F(CompilerTest_298, CompileProgramSize_298) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with case-insensitive flag
TEST_F(CompilerTest_298, CompileCaseInsensitive_298) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of empty pattern
TEST_F(CompilerTest_298, CompileEmptyPattern_298) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of repeated alternation that might stress memory
TEST_F(CompilerTest_298, CompileLargeAlternation_298) {
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "word" + std::to_string(i);
  }
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiling and then using the program for matching works end-to-end
TEST_F(CompilerTest_298, CompileAndMatchEndToEnd_298) {
  RE2 pattern("hello (world)");
  ASSERT_TRUE(pattern.ok());
  std::string match;
  EXPECT_TRUE(RE2::PartialMatch("say hello world!", pattern, &match));
  EXPECT_EQ(match, "world");
}

// Test compilation of repeated quantifier
TEST_F(CompilerTest_298, CompileCountedRepetition_298) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of dotstar (any pattern)
TEST_F(CompilerTest_298, CompileDotStar_298) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Verify that two separate compilations of the same pattern produce programs
TEST_F(CompilerTest_298, CompileSamePatternTwice_298) {
  Regexp* re1 = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  Regexp* re2 = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);
  Prog* prog1 = Compiler::Compile(re1, false, 1 << 20);
  Prog* prog2 = Compiler::Compile(re2, false, 1 << 20);
  ASSERT_NE(prog1, nullptr);
  ASSERT_NE(prog2, nullptr);
  delete prog1;
  delete prog2;
  re1->Decref();
  re2->Decref();
}

// Test compilation with POSIX flags
TEST_F(CompilerTest_298, CompilePOSIX_298) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of backreference-free pattern with many captures
TEST_F(CompilerTest_298, CompileMultipleCaptures_298) {
  Regexp* re = Regexp::Parse("(a)(b)(c)(d)(e)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
