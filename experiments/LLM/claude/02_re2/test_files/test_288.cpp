#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Since Compiler is mostly used through its static methods Compile and CompileSet,
// and internal methods operate on private types (Frag), we test through the public
// static interface and observable behavior via Prog and RE2.

class CompilerTest_288 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal regexp
TEST_F(CompilerTest_288, CompileSimpleLiteral_288) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with reversed flag produces a valid Prog
TEST_F(CompilerTest_288, CompileReversed_288) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of an alternation
TEST_F(CompilerTest_288, CompileAlternation_288) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of repetition operators
TEST_F(CompilerTest_288, CompileRepetition_288) {
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of character classes
TEST_F(CompilerTest_288, CompileCharacterClass_288) {
  Regexp* re = Regexp::Parse("[a-z0-9]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of capture groups
TEST_F(CompilerTest_288, CompileCaptureGroups_288) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of dot (any character)
TEST_F(CompilerTest_288, CompileDot_288) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of empty string regexp
TEST_F(CompilerTest_288, CompileEmptyString_288) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with very small max_mem might fail or produce limited prog
TEST_F(CompilerTest_288, CompileSmallMaxMem_288) {
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may return nullptr
  Prog* prog = Compiler::Compile(re, false, 1);
  // Whether it returns nullptr or not depends on implementation,
  // but it shouldn't crash
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED anchor
TEST_F(CompilerTest_288, CompileSetUnanchored_288) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_288, CompileSetAnchorStart_288) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_288, CompileSetAnchorBoth_288) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of Unicode patterns
TEST_F(CompilerTest_288, CompileUnicode_288) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of anchored patterns
TEST_F(CompilerTest_288, CompileAnchored_288) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of non-greedy operators
TEST_F(CompilerTest_288, CompileNonGreedy_288) {
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of case-insensitive pattern
TEST_F(CompilerTest_288, CompileCaseInsensitive_288) {
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of nested groups
TEST_F(CompilerTest_288, CompileNestedGroups_288) {
  Regexp* re = Regexp::Parse("((a|b)(c|d))*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program can be used for matching (integration-level)
TEST_F(CompilerTest_288, CompiledProgramCanMatch_288) {
  RE2 pattern("hello");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Test compilation of a complex pattern
TEST_F(CompilerTest_288, CompileComplexPattern_288) {
  Regexp* re = Regexp::Parse(
      "([a-zA-Z0-9_.+-]+)@([a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,}",
      Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of word boundary
TEST_F(CompilerTest_288, CompileWordBoundary_288) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that large repetition with moderate memory works
TEST_F(CompilerTest_288, CompileLargeRepetition_288) {
  Regexp* re = Regexp::Parse("a{100}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with alternation (typical set usage)
TEST_F(CompilerTest_288, CompileSetAlternation_288) {
  Regexp* re = Regexp::Parse("foo|bar|baz", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation preserves prog size is reasonable
TEST_F(CompilerTest_288, CompileProgSizeReasonable_288) {
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that compilation of Latin1 patterns works
TEST_F(CompilerTest_288, CompileLatin1_288) {
  Regexp* re = Regexp::Parse("[\\x00-\\xff]", Regexp::Latin1, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
