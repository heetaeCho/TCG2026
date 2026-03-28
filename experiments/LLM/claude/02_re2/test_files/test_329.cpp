#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/stringpiece.h"

namespace re2 {

class CompilerTest_329 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Compile returns a non-null Prog for a simple literal regex
TEST_F(CompilerTest_329, CompileSimpleLiteral_329) {
  Regexp* re = Regexp::Parse("hello", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with reversed flag returns a valid Prog
TEST_F(CompilerTest_329, CompileReversed_329) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles dot (any character)
TEST_F(CompilerTest_329, CompileDot_329) {
  Regexp* re = Regexp::Parse(".", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles alternation
TEST_F(CompilerTest_329, CompileAlternation_329) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (star)
TEST_F(CompilerTest_329, CompileStar_329) {
  Regexp* re = Regexp::Parse("a*", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (plus)
TEST_F(CompilerTest_329, CompilePlus_329) {
  Regexp* re = Regexp::Parse("a+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (quest)
TEST_F(CompilerTest_329, CompileQuest_329) {
  Regexp* re = Regexp::Parse("a?", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles capture groups
TEST_F(CompilerTest_329, CompileCapture_329) {
  Regexp* re = Regexp::Parse("(abc)(def)", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles character classes
TEST_F(CompilerTest_329, CompileCharClass_329) {
  Regexp* re = Regexp::Parse("[a-z0-9]", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles empty regex
TEST_F(CompilerTest_329, CompileEmpty_329) {
  Regexp* re = Regexp::Parse("", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with very small max_mem might return null or limited prog
TEST_F(CompilerTest_329, CompileVerySmallMaxMem_329) {
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may fail to compile
  Prog* prog = Compiler::Compile(re, false, 1);
  // Whether it returns null or not depends on implementation,
  // but it should not crash
  delete prog;
  re->Decref();
}

// Test that CompileSet returns a valid Prog for UNANCHORED
TEST_F(CompilerTest_329, CompileSetUnanchored_329) {
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileSet returns a valid Prog for ANCHOR_START
TEST_F(CompilerTest_329, CompileSetAnchorStart_329) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileSet returns a valid Prog for ANCHOR_BOTH
TEST_F(CompilerTest_329, CompileSetAnchorBoth_329) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with a complex nested regex
TEST_F(CompilerTest_329, CompileComplexNested_329) {
  Regexp* re = Regexp::Parse("((a|b)*c)+d?", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles Unicode character classes
TEST_F(CompilerTest_329, CompileUnicode_329) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles anchors
TEST_F(CompilerTest_329, CompileAnchors_329) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles word boundary
TEST_F(CompilerTest_329, CompileWordBoundary_329) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles non-greedy quantifiers
TEST_F(CompilerTest_329, CompileNonGreedy_329) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles case-insensitive flag
TEST_F(CompilerTest_329, CompileCaseInsensitive_329) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program size reflects complexity
TEST_F(CompilerTest_329, CompileProgramSize_329) {
  Regexp* re1 = Regexp::Parse("a", Regexp::PerlX, nullptr);
  ASSERT_NE(re1, nullptr);
  Prog* prog1 = Compiler::Compile(re1, false, 1 << 20);
  ASSERT_NE(prog1, nullptr);

  Regexp* re2 = Regexp::Parse("abcdefghijklmnop", Regexp::PerlX, nullptr);
  ASSERT_NE(re2, nullptr);
  Prog* prog2 = Compiler::Compile(re2, false, 1 << 20);
  ASSERT_NE(prog2, nullptr);

  // A longer literal should generally produce a larger program
  EXPECT_GE(prog2->size(), prog1->size());

  delete prog1;
  delete prog2;
  re1->Decref();
  re2->Decref();
}

// Test Compile with counted repetition
TEST_F(CompilerTest_329, CompileCountedRepetition_329) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with small max_mem
TEST_F(CompilerTest_329, CompileSetSmallMaxMem_329) {
  Regexp* re = Regexp::Parse("a{1000}|b{1000}", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1);
  // Should not crash; may return null
  delete prog;
  re->Decref();
}

// Test Compile with DotAll flag (s flag - dot matches newline)
TEST_F(CompilerTest_329, CompileDotAll_329) {
  Regexp* re = Regexp::Parse("(?s)a.b", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Verify the compiled program from Compile is functional through RE2
TEST_F(CompilerTest_329, CompiledProgramFunctional_329) {
  // Use RE2 to verify the overall compile path works correctly
  RE2 re("(\\d+)-(\\w+)");
  ASSERT_TRUE(re.ok());

  std::string digits, word;
  EXPECT_TRUE(RE2::FullMatch("123-hello", re, &digits, &word));
  EXPECT_EQ(digits, "123");
  EXPECT_EQ(word, "hello");
}

// Test that compilation doesn't crash on a single byte range regex
TEST_F(CompilerTest_329, CompileSingleByteRange_329) {
  Regexp* re = Regexp::Parse("[\\x00-\\xff]", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles nested groups
TEST_F(CompilerTest_329, CompileNestedGroups_329) {
  Regexp* re = Regexp::Parse("((((a))))", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles a large alternation
TEST_F(CompilerTest_329, CompileLargeAlternation_329) {
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "word" + std::to_string(i);
  }
  Regexp* re = Regexp::Parse(pattern, Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
