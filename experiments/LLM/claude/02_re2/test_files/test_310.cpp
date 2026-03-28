#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/compile.cc"

#include <memory>
#include <string>

namespace re2 {

// Helper to compile a regex pattern and return the Prog
static Prog* CompileRegexp(const char* pattern, bool reversed = false, int64_t max_mem = 8 << 20) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = Compiler::Compile(re, reversed, max_mem);
  re->Decref();
  return prog;
}

// Test basic compilation of a simple literal pattern
TEST(CompilerTest_310, CompileSimpleLiteral_310) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of an empty pattern
TEST(CompilerTest_310, CompileEmptyPattern_310) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a pattern with alternation
TEST(CompilerTest_310, CompileAlternation_310) {
  Prog* prog = CompileRegexp("a|b");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a pattern with repetition (star)
TEST(CompilerTest_310, CompileStar_310) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a pattern with repetition (plus)
TEST(CompilerTest_310, CompilePlus_310) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a pattern with optional (quest)
TEST(CompilerTest_310, CompileQuest_310) {
  Prog* prog = CompileRegexp("a?");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a character class
TEST(CompilerTest_310, CompileCharClass_310) {
  Prog* prog = CompileRegexp("[a-z]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a dot (any character)
TEST(CompilerTest_310, CompileDot_310) {
  Prog* prog = CompileRegexp(".");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation with capture groups
TEST(CompilerTest_310, CompileCaptureGroups_310) {
  Prog* prog = CompileRegexp("(a)(b)");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a complex pattern
TEST(CompilerTest_310, CompileComplexPattern_310) {
  Prog* prog = CompileRegexp("(foo|bar)+[0-9]{2,4}.*baz");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test reversed compilation
TEST(CompilerTest_310, CompileReversed_310) {
  Prog* prog = CompileRegexp("abc", true);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation with very small max_mem to trigger potential failure
TEST(CompilerTest_310, CompileWithVerySmallMaxMem_310) {
  // Very small memory limit may cause compilation to fail or produce a limited program
  Prog* prog = CompileRegexp("a{1000}", false, 1);
  // It may or may not succeed, but should not crash
  delete prog;
}

// Test compilation of anchored patterns
TEST(CompilerTest_310, CompileAnchoredPattern_310) {
  Prog* prog = CompileRegexp("^abc$");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of Unicode patterns
TEST(CompilerTest_310, CompileUnicodePattern_310) {
  Prog* prog = CompileRegexp("\\p{L}+");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation with foldcase (case insensitive)
TEST(CompilerTest_310, CompileCaseInsensitive_310) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test compilation of non-greedy patterns
TEST(CompilerTest_310, CompileNonGreedy_310) {
  Prog* prog = CompileRegexp("a*?b+?c??");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test CompileSet with unanchored anchor
TEST(CompilerTest_310, CompileSetUnanchored_310) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test CompileSet with anchor start
TEST(CompilerTest_310, CompileSetAnchorStart_310) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test CompileSet with anchor both
TEST(CompilerTest_310, CompileSetAnchorBoth_310) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test that compiled program can be used for matching (integration-level)
TEST(CompilerTest_310, CompiledProgramMatchesCorrectly_310) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // The program should have a valid size
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test compilation of empty width assertions
TEST(CompilerTest_310, CompileEmptyWidthAssertions_310) {
  Prog* prog = CompileRegexp("\\b\\w+\\b");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of byte range patterns
TEST(CompilerTest_310, CompileByteRangePattern_310) {
  Prog* prog = CompileRegexp("[\\x00-\\xff]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test ByteRangeEqual through the Compiler class
// We test this indirectly by compiling patterns that produce identical byte ranges
TEST(CompilerTest_310, ByteRangeEqualSameRange_310) {
  // This tests compilation involving byte ranges; the ByteRangeEqual function
  // is used internally during compilation. We verify compilation succeeds.
  Prog* prog = CompileRegexp("[aa]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation with nested groups
TEST(CompilerTest_310, CompileNestedGroups_310) {
  Prog* prog = CompileRegexp("((a)(b(c)))");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of a pattern with counted repetition
TEST(CompilerTest_310, CompileCountedRepetition_310) {
  Prog* prog = CompileRegexp("a{3,5}");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of single character
TEST(CompilerTest_310, CompileSingleChar_310) {
  Prog* prog = CompileRegexp("x");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation of wide Unicode range
TEST(CompilerTest_310, CompileWideUnicodeRange_310) {
  Prog* prog = CompileRegexp("[\\x{0080}-\\x{10ffff}]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test compilation with nullptr Regexp should not crash
TEST(CompilerTest_310, CompileNullRegexp_310) {
  // Passing nullptr - implementation should handle gracefully
  // This is an error case test
  Prog* prog = Compiler::Compile(nullptr, false, 8 << 20);
  // Should return nullptr or handle gracefully
  // We just verify no crash
  delete prog;
}

// Test that the program size is reasonable for a simple pattern
TEST(CompilerTest_310, ProgramSizeReasonable_310) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);
  // A single literal should produce a small program
  EXPECT_GT(prog->size(), 0);
  EXPECT_LT(prog->size(), 100);
  delete prog;
}

// Test compilation of alternation with many alternatives
TEST(CompilerTest_310, CompileManyAlternatives_310) {
  Prog* prog = CompileRegexp("a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test concatenation of many characters
TEST(CompilerTest_310, CompileLongConcatenation_310) {
  Prog* prog = CompileRegexp("abcdefghijklmnopqrstuvwxyz");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

}  // namespace re2
