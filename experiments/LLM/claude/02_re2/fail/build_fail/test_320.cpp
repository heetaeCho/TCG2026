#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/compile.h"

// We test the Compiler primarily through its static public interface:
// Compile and CompileSet, which are the main entry points.
// We also test via RE2, which internally uses Compiler::Compile.

namespace re2 {

// Test fixture that provides helper methods for creating and testing compiled programs
class CompilerTest_320 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to compile a pattern and return a Prog*
  Prog* CompilePattern(const char* pattern, bool reversed = false, int64_t max_mem = 1 << 20) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = Compiler::Compile(re, reversed, max_mem);
    re->Decref();
    return prog;
  }
};

// Test that a simple literal pattern compiles successfully
TEST_F(CompilerTest_320, SimpleLiteralCompiles_320) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test that an empty pattern compiles successfully
TEST_F(CompilerTest_320, EmptyPatternCompiles_320) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test that a single ASCII character literal compiles
TEST_F(CompilerTest_320, SingleASCIICharCompiles_320) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test that a UTF-8 multibyte character compiles
TEST_F(CompilerTest_320, UTF8MultibyteLiteralCompiles_320) {
  // Chinese character (3-byte UTF-8)
  Prog* prog = CompilePattern("中");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test that a 4-byte UTF-8 character compiles
TEST_F(CompilerTest_320, FourByteUTF8LiteralCompiles_320) {
  // Emoji (4-byte UTF-8)
  Prog* prog = CompilePattern("😀");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation with foldcase (case-insensitive)
TEST_F(CompilerTest_320, CaseInsensitiveCompiles_320) {
  Prog* prog = CompilePattern("(?i)hello");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test reversed compilation
TEST_F(CompilerTest_320, ReversedCompilation_320) {
  Prog* prog = CompilePattern("abc", true);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test alternation compiles
TEST_F(CompilerTest_320, AlternationCompiles_320) {
  Prog* prog = CompilePattern("a|b|c");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test repetition compiles
TEST_F(CompilerTest_320, RepetitionCompiles_320) {
  Prog* prog = CompilePattern("a*b+c?");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test character class compiles
TEST_F(CompilerTest_320, CharClassCompiles_320) {
  Prog* prog = CompilePattern("[a-zA-Z0-9]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test dot (any character) compiles
TEST_F(CompilerTest_320, DotCompiles_320) {
  Prog* prog = CompilePattern("a.b");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test anchored pattern compiles
TEST_F(CompilerTest_320, AnchoredPatternCompiles_320) {
  Prog* prog = CompilePattern("^abc$");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test capture groups compile
TEST_F(CompilerTest_320, CaptureGroupCompiles_320) {
  Prog* prog = CompilePattern("(a)(b)(c)");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test nested groups compile
TEST_F(CompilerTest_320, NestedGroupsCompile_320) {
  Prog* prog = CompilePattern("((a)(b))");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test with very low max_mem - pattern may fail to compile or produce limited program
TEST_F(CompilerTest_320, VeryLowMaxMem_320) {
  // With extremely low memory, complex patterns should fail
  Prog* prog = CompilePattern("a{1000}", false, 100);
  // May or may not compile depending on implementation
  // Just ensure no crash
  delete prog;
}

// Test CompileSet with unanchored
TEST_F(CompilerTest_320, CompileSetUnanchored_320) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test CompileSet with anchor start
TEST_F(CompilerTest_320, CompileSetAnchorStart_320) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test CompileSet with anchor both
TEST_F(CompilerTest_320, CompileSetAnchorBoth_320) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test that compiled program actually matches correctly (via RE2)
TEST_F(CompilerTest_320, CompiledProgramMatchesASCII_320) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test case insensitive matching through compiled program
TEST_F(CompilerTest_320, CompiledProgramMatchesCaseInsensitive_320) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

// Test UTF-8 matching through compiled program
TEST_F(CompilerTest_320, CompiledProgramMatchesUTF8_320) {
  RE2 re("中文");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("中文", re));
  EXPECT_FALSE(RE2::FullMatch("英文", re));
}

// Test Latin1 encoding compilation
TEST_F(CompilerTest_320, Latin1EncodingCompiles_320) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("abc", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
}

// Test Latin1 encoding with high byte values
TEST_F(CompilerTest_320, Latin1HighByteMatches_320) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("\xe9", opts);  // é in Latin-1
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\xe9", re));
}

// Test boundary: Runeself boundary (128)
TEST_F(CompilerTest_320, RuneselfBoundaryBelow_320) {
  // ASCII char just below Runeself (127 = DEL)
  Prog* prog = CompilePattern("\\x7f");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test boundary: Runeself boundary (128)
TEST_F(CompilerTest_320, RuneselfBoundaryAt_320) {
  // First multibyte character (U+0080)
  Prog* prog = CompilePattern("\\x{80}");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test boundary: Runemax
TEST_F(CompilerTest_320, RunemaxBoundary_320) {
  // U+10FFFF - maximum valid Unicode code point
  Prog* prog = CompilePattern("\\x{10ffff}");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test 2-byte UTF-8 character
TEST_F(CompilerTest_320, TwoByteUTF8Literal_320) {
  // U+00E9 (é) is 2 bytes in UTF-8
  RE2 re("é");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("é", re));
}

// Test 3-byte UTF-8 character
TEST_F(CompilerTest_320, ThreeByteUTF8Literal_320) {
  // U+4E2D (中) is 3 bytes in UTF-8
  RE2 re("中");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("中", re));
}

// Test complex regex with multiple features
TEST_F(CompilerTest_320, ComplexRegexCompiles_320) {
  Prog* prog = CompilePattern("^(foo|bar){2,5}[a-z]+\\.txt$");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test non-greedy quantifiers compile
TEST_F(CompilerTest_320, NonGreedyQuantifiersCompile_320) {
  Prog* prog = CompilePattern("a*?b+?c??");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test empty width assertions compile
TEST_F(CompilerTest_320, EmptyWidthAssertionsCompile_320) {
  Prog* prog = CompilePattern("\\ba\\b");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test that Compile returns nullptr for null regexp (safety check)
TEST_F(CompilerTest_320, CompileNullRegexp_320) {
  Prog* prog = Compiler::Compile(nullptr, false, 1 << 20);
  // Depending on implementation, this may return nullptr or crash
  // We accept nullptr as correct behavior
  EXPECT_EQ(prog, nullptr);
}

// Test character range compilation
TEST_F(CompilerTest_320, CharacterRangeUTF8Compiles_320) {
  Prog* prog = CompilePattern("[\\x{100}-\\x{1ff}]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test wide Unicode range
TEST_F(CompilerTest_320, WideUnicodeRangeCompiles_320) {
  Prog* prog = CompilePattern("[\\x{10000}-\\x{10ffff}]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test multiple concatenated UTF-8 literals
TEST_F(CompilerTest_320, MultipleConcatenatedUTF8Literals_320) {
  RE2 re("中文字符串");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("中文字符串", re));
  EXPECT_FALSE(RE2::FullMatch("中文", re));
}

// Test case-insensitive with ASCII boundary
TEST_F(CompilerTest_320, CaseInsensitiveASCIIBoundary_320) {
  RE2 re("(?i)[a-z]");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("A", re));
  EXPECT_TRUE(RE2::FullMatch("z", re));
  EXPECT_TRUE(RE2::FullMatch("Z", re));
  EXPECT_FALSE(RE2::FullMatch("1", re));
}

// Test that program size is reasonable for simple patterns
TEST_F(CompilerTest_320, ProgramSizeReasonable_320) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test with sufficient max_mem for moderate pattern
TEST_F(CompilerTest_320, SufficientMaxMemForModeratePattern_320) {
  Prog* prog = CompilePattern("[a-z]{1,10}", false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test reversed compilation with UTF-8
TEST_F(CompilerTest_320, ReversedUTF8Compilation_320) {
  Prog* prog = CompilePattern("中文", true);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

}  // namespace re2
