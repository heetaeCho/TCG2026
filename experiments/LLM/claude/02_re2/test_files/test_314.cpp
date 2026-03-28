#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/compile.h"

namespace re2 {

// Test through RE2 and Compile interface since Compiler internals are not directly accessible
class CompilerTest_314 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal pattern
TEST_F(CompilerTest_314, CompileLiteralPattern_314) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with reversed flag
TEST_F(CompilerTest_314, CompileReversed_314) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with a character class (which exercises rune ranges)
TEST_F(CompilerTest_314, CompileCharClass_314) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Latin1 encoding (exercises AddRuneRangeLatin1 path)
TEST_F(CompilerTest_314, CompileLatin1Range_314) {
  Regexp* re = Regexp::Parse("[\\x00-\\xff]", Regexp::Latin1, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with dot-star pattern
TEST_F(CompilerTest_314, CompileDotStar_314) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with alternation
TEST_F(CompilerTest_314, CompileAlternation_314) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition operators
TEST_F(CompilerTest_314, CompileRepetition_314) {
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with very small max_mem that may cause failure
TEST_F(CompilerTest_314, CompileSmallMaxMem_314) {
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit
  Prog* prog = Compiler::Compile(re, false, 1);
  // May return nullptr if memory is too small
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST_F(CompilerTest_314, CompileSetUnanchored_314) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_314, CompileSetAnchorBoth_314) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with capture groups
TEST_F(CompilerTest_314, CompileCaptureGroups_314) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Unicode ranges (exercises AddRuneRangeUTF8)
TEST_F(CompilerTest_314, CompileUnicodeRange_314) {
  Regexp* re = Regexp::Parse("[\\x{100}-\\x{10ffff}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with empty pattern
TEST_F(CompilerTest_314, CompileEmptyPattern_314) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with non-greedy repetition
TEST_F(CompilerTest_314, CompileNonGreedy_314) {
  Regexp* re = Regexp::Parse("a+?b*?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with empty width assertions
TEST_F(CompilerTest_314, CompileEmptyWidthAssertions_314) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST_F(CompilerTest_314, CompileWordBoundary_314) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the compiled program actually matches correctly via RE2
TEST_F(CompilerTest_314, CompiledProgramMatchesCorrectly_314) {
  RE2 pattern("hello");
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Test Latin1 mode matching
TEST_F(CompilerTest_314, Latin1ModeMatching_314) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 pattern("[a-z]+", opts);
  EXPECT_TRUE(RE2::FullMatch("abc", pattern));
  EXPECT_FALSE(RE2::FullMatch("123", pattern));
}

// Test Compile with complex nested pattern
TEST_F(CompilerTest_314, CompileComplexNested_314) {
  Regexp* re = Regexp::Parse("((a|b)*c)+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_314, CompileSetAnchorStart_314) {
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that single byte Latin1 range compiles correctly
TEST_F(CompilerTest_314, CompileSingleByteLatin1_314) {
  Regexp* re = Regexp::Parse("[\\x80-\\xff]", Regexp::Latin1, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Verify case folding works through compilation
TEST_F(CompilerTest_314, CompileCaseFolding_314) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 pattern("Hello", opts);
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_TRUE(RE2::FullMatch("HELLO", pattern));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", pattern));
}

}  // namespace re2
