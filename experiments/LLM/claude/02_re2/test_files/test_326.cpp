#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test that a simple regex compiles successfully and produces a valid Prog
TEST(CompilerTest_326, CompileSimpleLiteral_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that compiling an empty regex works
TEST(CompilerTest_326, CompileEmptyRegex_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling a character class
TEST(CompilerTest_326, CompileCharClass_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling alternation
TEST(CompilerTest_326, CompileAlternation_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar|baz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling repetition operators
TEST(CompilerTest_326, CompileRepetition_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b+c?d{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling with capture groups
TEST(CompilerTest_326, CompileCaptureGroups_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling dot-star pattern
TEST(CompilerTest_326, CompileDotStar_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling anchored regex
TEST(CompilerTest_326, CompileAnchored_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling a reverse program
TEST(CompilerTest_326, CompileReverseProg_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that forward compile is not reversed
TEST(CompilerTest_326, ForwardProgNotReversed_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_FALSE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test compiling with a limited max_mem
TEST(CompilerTest_326, CompileWithLimitedMemory_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);  // 1MB
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  // dfa_mem should be set based on max_mem
  EXPECT_GT(prog->dfa_mem(), 0);
  delete prog;
  re->Decref();
}

// Test compiling with zero max_mem (should use default 1<<20)
TEST(CompilerTest_326, CompileWithZeroMaxMem_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_EQ(prog->dfa_mem(), 1 << 20);
  delete prog;
  re->Decref();
}

// Test compiling a complex regex with Unicode
TEST(CompilerTest_326, CompileUnicodeRegex_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling regex with prefix (for prefix accel)
TEST(CompilerTest_326, CompileWithPrefix_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling a regex that is very large may fail with limited memory
TEST(CompilerTest_326, CompileLargeRegexLimitedMem_326) {
  RegexpStatus status;
  // Build a large alternation
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "abcdefghij";
    pattern += std::to_string(i);
  }
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may still succeed but dfa_mem will be small
  Prog* prog = re->CompileToProg(1 << 10);
  // Even with tiny memory limit, compilation may succeed
  // but if it does, the prog should be valid
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test that bytemap_range is positive for non-trivial regex
TEST(CompilerTest_326, ByteMapRangePositive_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST(CompilerTest_326, CompileSetUnanchored_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST(CompilerTest_326, CompileSetAnchorBoth_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST(CompilerTest_326, CompileSetAnchorStart_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_START, 0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that compiled program can dump without crashing
TEST(CompilerTest_326, ProgDump_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab+c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
  re->Decref();
}

// Test compiling with case-insensitive flag
TEST(CompilerTest_326, CompileFoldCase_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling nongreedy quantifiers
TEST(CompilerTest_326, CompileNonGreedy_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling word boundary
TEST(CompilerTest_326, CompileWordBoundary_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bhello\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that start and start_unanchored are valid
TEST(CompilerTest_326, ProgStartValues_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GE(prog->start(), 0);
  EXPECT_LT(prog->start(), prog->size());
  EXPECT_GE(prog->start_unanchored(), 0);
  EXPECT_LT(prog->start_unanchored(), prog->size());
  delete prog;
  re->Decref();
}

// Test with very large memory limit
TEST(CompilerTest_326, CompileWithLargeMaxMem_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1LL << 30);  // 1GB
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->dfa_mem(), 0);
  delete prog;
  re->Decref();
}

// Test compiling nested groups
TEST(CompilerTest_326, CompileNestedGroups_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that can_prefix_accel works for a prefix pattern
TEST(CompilerTest_326, PrefixAccelForLiteralPrefix_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz.*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  // Just check it doesn't crash; the value depends on the pattern
  (void)prog->can_prefix_accel();
  delete prog;
  re->Decref();
}

// Test compiling a single dot
TEST(CompilerTest_326, CompileSingleDot_326) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

}  // namespace re2
