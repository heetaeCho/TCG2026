#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class CompilerTest_309 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic compilation of a simple literal pattern
TEST_F(CompilerTest_309, CompileSimpleLiteral_309) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of a pattern with character classes that triggers AddSuffixRecursive
TEST_F(CompilerTest_309, CompileCharacterClass_309) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of unicode character classes that trigger UTF-8 byte range suffix merging
TEST_F(CompilerTest_309, CompileUnicodeClass_309) {
  Regexp* re = Regexp::Parse("[\\x{100}-\\x{10FFFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with reversed flag
TEST_F(CompilerTest_309, CompileReversed_309) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with very small max_mem to trigger allocation failures
TEST_F(CompilerTest_309, CompileSmallMaxMem_309) {
  Regexp* re = Regexp::Parse("[\\x{0}-\\x{10FFFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit may cause compilation to fail gracefully
  Prog* prog = Compiler::Compile(re, false, 64);
  // May or may not succeed depending on how small is too small
  delete prog;
  re->Decref();
}

// Test compilation of overlapping byte ranges that exercise suffix merging
TEST_F(CompilerTest_309, CompileOverlappingRanges_309) {
  Regexp* re = Regexp::Parse("[\\x{80}-\\x{FF}\\x{100}-\\x{1FF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of dot-star pattern
TEST_F(CompilerTest_309, CompileDotStar_309) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored
TEST_F(CompilerTest_309, CompileSetUnanchored_309) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchored start
TEST_F(CompilerTest_309, CompileSetAnchorStart_309) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchored both
TEST_F(CompilerTest_309, CompileSetAnchorBoth_309) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of pattern with multi-byte UTF-8 characters that share suffixes
TEST_F(CompilerTest_309, CompileSharedUTF8Suffixes_309) {
  Regexp* re = Regexp::Parse("[\\x{400}-\\x{4FF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of complex alternation with shared byte range suffixes
TEST_F(CompilerTest_309, CompileComplexAlternation_309) {
  Regexp* re = Regexp::Parse("[\\x{1000}-\\x{1FFF}\\x{2000}-\\x{2FFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of CJK unified ideographs range (3-byte UTF-8)
TEST_F(CompilerTest_309, CompileCJKRange_309) {
  Regexp* re = Regexp::Parse("[\\x{4E00}-\\x{9FFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with foldcase
TEST_F(CompilerTest_309, CompileWithFoldcase_309) {
  Regexp* re = Regexp::Parse("(?i)[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of 4-byte UTF-8 range (supplementary planes)
TEST_F(CompilerTest_309, Compile4ByteUTF8Range_309) {
  Regexp* re = Regexp::Parse("[\\x{10000}-\\x{10FFFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of empty pattern
TEST_F(CompilerTest_309, CompileEmptyPattern_309) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program works correctly via RE2 for matching
TEST_F(CompilerTest_309, CompiledProgramMatchesCorrectly_309) {
  RE2 pattern("[\\x{80}-\\x{7FF}]+");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("\xC2\x80", pattern));  // U+0080
  EXPECT_FALSE(RE2::FullMatch("a", pattern));  // ASCII
}

// Test matching with shared suffix byte ranges
TEST_F(CompilerTest_309, SharedSuffixMatching_309) {
  RE2 pattern("[\\x{400}-\\x{4FF}]");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("\xD0\x80", pattern));  // U+0400
  EXPECT_TRUE(RE2::FullMatch("\xD3\xBF", pattern));  // U+04FF
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

// Test compilation of alternation of multi-byte unicode literals
TEST_F(CompilerTest_309, CompileUnicodeAlternation_309) {
  Regexp* re = Regexp::Parse("\\x{1234}|\\x{1235}|\\x{1236}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with Latin1 encoding
TEST_F(CompilerTest_309, CompileLatin1_309) {
  Regexp* re = Regexp::Parse("[\\x{00}-\\x{FF}]", Regexp::Latin1 | Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that NULL regexp is handled
TEST_F(CompilerTest_309, CompileNullRegexp_309) {
  Prog* prog = Compiler::Compile(nullptr, false, 1 << 20);
  EXPECT_EQ(prog, nullptr);
}

// Test compilation of pattern with captures
TEST_F(CompilerTest_309, CompileWithCaptures_309) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of quantifiers
TEST_F(CompilerTest_309, CompileQuantifiers_309) {
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the program from compilation can distinguish matches
TEST_F(CompilerTest_309, ProgramDistinguishesMatches_309) {
  RE2 pattern("[\\x{80}-\\x{FF}]");
  ASSERT_TRUE(pattern.ok());
  // U+0080 is \xC2\x80 in UTF-8
  EXPECT_TRUE(RE2::FullMatch("\xC2\x80", pattern));
  // U+00FF is \xC3\xBF in UTF-8
  EXPECT_TRUE(RE2::FullMatch("\xC3\xBF", pattern));
  // U+007F is \x7F in UTF-8 (single byte, out of range)
  EXPECT_FALSE(RE2::FullMatch("\x7F", pattern));
}

}  // namespace re2
