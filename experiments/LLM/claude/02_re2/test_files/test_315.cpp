#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test through the public static interface Compiler::Compile and Compiler::CompileSet,
// since the Compiler class internals (Add_80_10ffff, etc.) are not directly accessible
// without constructing internal state. We verify behavior through regex matching.

class CompilerTest_315 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple literal pattern compiles and matches correctly
TEST_F(CompilerTest_315, CompileLiteral_315) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a reversed compile works
TEST_F(CompilerTest_315, CompileReversed_315) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a dot-star pattern (exercises Add_80_10ffff in UTF-8 mode)
TEST_F(CompilerTest_315, CompileDotStar_315) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a character class that spans the full Unicode range
TEST_F(CompilerTest_315, CompileFullUnicodeRange_315) {
  // [^\x00-\x7f] should trigger multi-byte UTF-8 ranges including 0x80-0x10FFFF
  Regexp* re = Regexp::Parse("[^\\x00-\\x7f]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a character class that spans 0x80-0x10FFFF reversed
TEST_F(CompilerTest_315, CompileFullUnicodeRangeReversed_315) {
  Regexp* re = Regexp::Parse("[^\\x00-\\x7f]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test dot pattern (matches any character except newline)
TEST_F(CompilerTest_315, CompileDot_315) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test dot pattern with DotNL flag (matches all characters including newline)
TEST_F(CompilerTest_315, CompileDotNL_315) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::DotNL);
  Regexp* re = Regexp::Parse(".", flags, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compile with very limited memory should still produce a prog (or fail gracefully)
TEST_F(CompilerTest_315, CompileWithLimitedMemory_315) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Even very small max_mem should handle a simple pattern
  Prog* prog = Compiler::Compile(re, false, 256);
  // May or may not succeed with very limited memory, but should not crash
  delete prog;
  re->Decref();
}

// Test compile with zero memory returns nullptr
TEST_F(CompilerTest_315, CompileWithZeroMemory_315) {
  Regexp* re = Regexp::Parse("a.*b.*c.*d", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 0);
  // With 0 memory, compilation should fail
  EXPECT_EQ(prog, nullptr);
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST_F(CompilerTest_315, CompileSetUnanchored_315) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_315, CompileSetAnchorBoth_315) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_315, CompileSetAnchorStart_315) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a multi-byte UTF-8 character class compiles correctly
TEST_F(CompilerTest_315, CompileMultiByteCharClass_315) {
  // Chinese character range
  Regexp* re = Regexp::Parse("[\\x{4e00}-\\x{9fff}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a 4-byte UTF-8 character class compiles correctly
TEST_F(CompilerTest_315, CompileFourByteCharClass_315) {
  // Emoji range (supplementary plane)
  Regexp* re = Regexp::Parse("[\\x{10000}-\\x{10ffff}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a 4-byte UTF-8 character class compiles correctly in reversed mode
TEST_F(CompilerTest_315, CompileFourByteCharClassReversed_315) {
  Regexp* re = Regexp::Parse("[\\x{10000}-\\x{10ffff}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of Latin1 ranges
TEST_F(CompilerTest_315, CompileLatin1Range_315) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::Latin1);
  Regexp* re = Regexp::Parse("[a-z]", flags, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of case-folded patterns
TEST_F(CompilerTest_315, CompileFoldCase_315) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  Regexp* re = Regexp::Parse("abc", flags, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of complex patterns with quantifiers
TEST_F(CompilerTest_315, CompileComplexPattern_315) {
  Regexp* re = Regexp::Parse("(a+b*c?){2,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of alternations
TEST_F(CompilerTest_315, CompileAlternation_315) {
  Regexp* re = Regexp::Parse("a|b|c|d|e", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of empty pattern
TEST_F(CompilerTest_315, CompileEmptyPattern_315) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of anchored patterns
TEST_F(CompilerTest_315, CompileAnchoredPattern_315) {
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of capture groups
TEST_F(CompilerTest_315, CompileCaptureGroups_315) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of non-greedy quantifiers
TEST_F(CompilerTest_315, CompileNonGreedyQuantifiers_315) {
  Regexp* re = Regexp::Parse("a+?b*?c??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled prog matches expected strings for a pattern involving
// multi-byte UTF8 (which uses Add_80_10ffff internally)
TEST_F(CompilerTest_315, MatchMultiByteUTF8_315) {
  RE2 pattern(".");
  ASSERT_TRUE(pattern.ok());
  
  // ASCII character
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  
  // 2-byte UTF-8 (e.g., é = U+00E9)
  EXPECT_TRUE(RE2::FullMatch("\xC3\xA9", pattern));
  
  // 3-byte UTF-8 (e.g., 中 = U+4E2D)
  EXPECT_TRUE(RE2::FullMatch("\xE4\xB8\xAD", pattern));
  
  // 4-byte UTF-8 (e.g., 𐍈 = U+10348)
  EXPECT_TRUE(RE2::FullMatch("\xF0\x90\x8D\x88", pattern));
}

// Test matching with negated character class (triggers Add_80_10ffff)
TEST_F(CompilerTest_315, MatchNegatedCharClass_315) {
  RE2 pattern("[^a]");
  ASSERT_TRUE(pattern.ok());
  
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("b", pattern));
  // Multi-byte character should match [^a]
  EXPECT_TRUE(RE2::FullMatch("\xC3\xA9", pattern));
}

// Test that a pattern with wide unicode range works end-to-end
TEST_F(CompilerTest_315, FullMatchWideUnicodeRange_315) {
  RE2 pattern("[\\x{80}-\\x{10ffff}]");
  ASSERT_TRUE(pattern.ok());
  
  // ASCII should not match
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
  
  // 2-byte UTF-8 should match
  EXPECT_TRUE(RE2::FullMatch("\xC2\x80", pattern));
  
  // 4-byte UTF-8 max should match  
  EXPECT_TRUE(RE2::FullMatch("\xF4\x8F\xBF\xBF", pattern));
}

}  // namespace re2
