#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/compile.h"

#include <memory>
#include <string>

namespace re2 {

class CompilerTest_313 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse a regexp string into a Regexp*
Regexp* ParseRegexp(const std::string& pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

// Test that Compile returns a non-null Prog for a simple literal pattern
TEST_F(CompilerTest_313, CompileSimpleLiteral_313) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile returns a non-null Prog for a character class
TEST_F(CompilerTest_313, CompileCharClass_313) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile works with reversed flag
TEST_F(CompilerTest_313, CompileReversed_313) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles alternation
TEST_F(CompilerTest_313, CompileAlternation_313) {
  Regexp* re = ParseRegexp("foo|bar|baz");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (star)
TEST_F(CompilerTest_313, CompileStar_313) {
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (plus)
TEST_F(CompilerTest_313, CompilePlus_313) {
  Regexp* re = ParseRegexp("a+");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles optional (quest)
TEST_F(CompilerTest_313, CompileQuest_313) {
  Regexp* re = ParseRegexp("a?");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles capture groups
TEST_F(CompilerTest_313, CompileCapture_313) {
  Regexp* re = ParseRegexp("(abc)(def)");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles empty pattern
TEST_F(CompilerTest_313, CompileEmptyPattern_313) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles dot (any char)
TEST_F(CompilerTest_313, CompileDot_313) {
  Regexp* re = ParseRegexp(".");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles anchors
TEST_F(CompilerTest_313, CompileAnchors_313) {
  Regexp* re = ParseRegexp("^abc$");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles Unicode ranges
TEST_F(CompilerTest_313, CompileUnicodeRange_313) {
  Regexp* re = ParseRegexp("[\\x{0100}-\\x{ffff}]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with very small max_mem may return null for complex patterns
TEST_F(CompilerTest_313, CompileSmallMaxMem_313) {
  Regexp* re = ParseRegexp("a{100}b{100}c{100}");
  ASSERT_NE(re, nullptr);
  // Very small memory limit
  Prog* prog = Compiler::Compile(re, false, 1);
  // May return null due to memory limit
  // We just check it doesn't crash; result may be null or non-null
  delete prog;
  re->Decref();
}

// Test that Compile handles nongreedy repetitions
TEST_F(CompilerTest_313, CompileNonGreedy_313) {
  Regexp* re = ParseRegexp("a*?b+?c??");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED anchor
TEST_F(CompilerTest_313, CompileSetUnanchored_313) {
  Regexp* re = ParseRegexp("foo|bar");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_313, CompileSetAnchorBoth_313) {
  Regexp* re = ParseRegexp("foo|bar");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_313, CompileSetAnchorStart_313) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles complex nested pattern
TEST_F(CompilerTest_313, CompileComplexNested_313) {
  Regexp* re = ParseRegexp("((a|b)*c(d+|e?))+");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Latin1 encoding
TEST_F(CompilerTest_313, CompileLatin1_313) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::Latin1);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", flags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with case-insensitive flag (foldcase)
TEST_F(CompilerTest_313, CompileFoldCase_313) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", flags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program produces correct matching via RE2
TEST_F(CompilerTest_313, CompiledProgMatchesCorrectly_313) {
  RE2 pattern("^(foo|bar)baz$");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("foobaz", pattern));
  EXPECT_TRUE(RE2::FullMatch("barbaz", pattern));
  EXPECT_FALSE(RE2::FullMatch("quxbaz", pattern));
}

// Test that compiled program handles Unicode correctly
TEST_F(CompilerTest_313, CompiledProgUnicodeMatch_313) {
  RE2 pattern("\\p{L}+");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", pattern));
  EXPECT_TRUE(RE2::PartialMatch("héllo", pattern));
  EXPECT_FALSE(RE2::PartialMatch("12345", pattern));
}

// Test Compile with wide Unicode range (covers Add_80_10ffff path)
TEST_F(CompilerTest_313, CompileWideUnicodeRange_313) {
  Regexp* re = ParseRegexp("[^\\x00-\\x7f]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile handles single rune
TEST_F(CompilerTest_313, CompileSingleRune_313) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that the compiled program's size is reasonable
TEST_F(CompilerTest_313, CompiledProgramSize_313) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test Compile with dotstar-like pattern
TEST_F(CompilerTest_313, CompileDotStar_313) {
  Regexp* re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with bounded repetition
TEST_F(CompilerTest_313, CompileBoundedRepetition_313) {
  Regexp* re = ParseRegexp("a{3,5}");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with small max_mem
TEST_F(CompilerTest_313, CompileSetSmallMaxMem_313) {
  Regexp* re = ParseRegexp("a{1000}");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1);
  // May fail due to memory limit
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST_F(CompilerTest_313, CompileWordBoundary_313) {
  Regexp* re = ParseRegexp("\\bword\\b");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test full Unicode range character class
TEST_F(CompilerTest_313, CompileFullUnicodeCharClass_313) {
  Regexp* re = ParseRegexp("[\\x{0}-\\x{10ffff}]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Latin1 encoding and foldcase
TEST_F(CompilerTest_313, CompileLatin1FoldCase_313) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::Latin1 | Regexp::FoldCase);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[A-Z]", flags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
