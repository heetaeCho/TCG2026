#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for Compiler tests
class CompilerTest_599 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse a regexp and compile it
static Prog* CompileRegexp(const char* pattern, bool reversed = false,
                           int64_t max_mem = 8 << 20) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = Compiler::Compile(re, reversed, max_mem);
  re->Decref();
  return prog;
}

// Test: Compile a simple literal pattern
TEST_F(CompilerTest_599, CompileSimpleLiteral_599) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile an empty pattern
TEST_F(CompilerTest_599, CompileEmptyPattern_599) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with alternation
TEST_F(CompilerTest_599, CompileAlternation_599) {
  Prog* prog = CompileRegexp("a|b");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with repetition (star)
TEST_F(CompilerTest_599, CompileStar_599) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with repetition (plus)
TEST_F(CompilerTest_599, CompilePlus_599) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with optional (quest)
TEST_F(CompilerTest_599, CompileQuest_599) {
  Prog* prog = CompileRegexp("a?");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with character class
TEST_F(CompilerTest_599, CompileCharClass_599) {
  Prog* prog = CompileRegexp("[a-z]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with capture groups
TEST_F(CompilerTest_599, CompileCaptureGroup_599) {
  Prog* prog = CompileRegexp("(a)(b)");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with dot
TEST_F(CompilerTest_599, CompileDot_599) {
  Prog* prog = CompileRegexp(".");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with anchors
TEST_F(CompilerTest_599, CompileAnchors_599) {
  Prog* prog = CompileRegexp("^abc$");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile reversed pattern
TEST_F(CompilerTest_599, CompileReversed_599) {
  Prog* prog = CompileRegexp("abc", /*reversed=*/true);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile with very small max_mem should return nullptr for complex pattern
TEST_F(CompilerTest_599, CompileWithVerySmallMemLimit_599) {
  // A complex pattern with very small memory limit
  Prog* prog = CompileRegexp("a{1000}", /*reversed=*/false, /*max_mem=*/1);
  // With extremely small memory, compilation may fail
  // Either way, we just check it doesn't crash; result may or may not be null
  delete prog;
}

// Test: Compile a complex nested pattern
TEST_F(CompilerTest_599, CompileComplexNestedPattern_599) {
  Prog* prog = CompileRegexp("((a|b)*c)+d?");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile pattern with Unicode characters
TEST_F(CompilerTest_599, CompileUnicodePattern_599) {
  Prog* prog = CompileRegexp("[\\x{100}-\\x{10FFFF}]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile with null Regexp should return nullptr
TEST_F(CompilerTest_599, CompileNullRegexp_599) {
  Prog* prog = Compiler::Compile(nullptr, false, 8 << 20);
  EXPECT_EQ(prog, nullptr);
}

// Test: CompileSet with a simple pattern
TEST_F(CompilerTest_599, CompileSetSimple_599) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: CompileSet anchored
TEST_F(CompilerTest_599, CompileSetAnchored_599) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: CompileSet anchor start
TEST_F(CompilerTest_599, CompileSetAnchorStart_599) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: Compile pattern with nongreedy operators
TEST_F(CompilerTest_599, CompileNonGreedy_599) {
  Prog* prog = CompileRegexp("a*?b+?c??");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile a pattern with word boundary
TEST_F(CompilerTest_599, CompileWordBoundary_599) {
  Prog* prog = CompileRegexp("\\bfoo\\b");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile pattern with counted repetition
TEST_F(CompilerTest_599, CompileCountedRepetition_599) {
  Prog* prog = CompileRegexp("a{3,5}");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile pattern with escape sequences
TEST_F(CompilerTest_599, CompileEscapeSequences_599) {
  Prog* prog = CompileRegexp("\\d+\\s\\w+");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile single character
TEST_F(CompilerTest_599, CompileSingleChar_599) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile pattern with case-insensitive flag
TEST_F(CompilerTest_599, CompileCaseInsensitive_599) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: Compile large alternation
TEST_F(CompilerTest_599, CompileLargeAlternation_599) {
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "word" + std::to_string(i);
  }
  Prog* prog = CompileRegexp(pattern.c_str());
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile nested capture groups
TEST_F(CompilerTest_599, CompileNestedCaptures_599) {
  Prog* prog = CompileRegexp("((a)(b(c)))");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiled program has valid start instruction
TEST_F(CompilerTest_599, CompiledProgHasValidStart_599) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // start() should return a non-negative value
  EXPECT_GE(prog->start(), 0);
  delete prog;
}

// Test: Compiled program has instructions
TEST_F(CompilerTest_599, CompiledProgHasInstructions_599) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // size should be positive - there must be at least some instructions
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test: Compile reversed complex pattern
TEST_F(CompilerTest_599, CompileReversedComplex_599) {
  Prog* prog = CompileRegexp("(a|b)+c*", /*reversed=*/true);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Memory limit boundary - moderate limit
TEST_F(CompilerTest_599, CompileWithModerateMem_599) {
  Prog* prog = CompileRegexp("a+b+c+", /*reversed=*/false, /*max_mem=*/4096);
  // Should succeed with a reasonable memory limit for a simple pattern
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: CompileSet with null regexp
TEST_F(CompilerTest_599, CompileSetNullRegexp_599) {
  Prog* prog = Compiler::CompileSet(nullptr, RE2::UNANCHORED, 8 << 20);
  EXPECT_EQ(prog, nullptr);
}

}  // namespace re2
