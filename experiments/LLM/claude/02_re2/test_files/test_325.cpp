#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <memory>

namespace re2 {

// Helper to parse a regexp and return it (caller must Decref)
static Regexp* ParseRegexp(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  return re;
}

class CompilerTest_325 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test basic compilation of a simple literal pattern
TEST_F(CompilerTest_325, CompileSimpleLiteral_325) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_FALSE(prog->reversed());
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation of an empty pattern
TEST_F(CompilerTest_325, CompileEmptyPattern_325) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_FALSE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test compilation of a pattern with anchors (^)
TEST_F(CompilerTest_325, CompileAnchorStart_325) {
  Regexp* re = ParseRegexp("^hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->anchor_start());
  delete prog;
  re->Decref();
}

// Test compilation of a pattern with end anchor ($)
TEST_F(CompilerTest_325, CompileAnchorEnd_325) {
  Regexp* re = ParseRegexp("hello$");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->anchor_end());
  delete prog;
  re->Decref();
}

// Test compilation of a pattern with both anchors
TEST_F(CompilerTest_325, CompileBothAnchors_325) {
  Regexp* re = ParseRegexp("^hello$");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->anchor_start());
  EXPECT_TRUE(prog->anchor_end());
  delete prog;
  re->Decref();
}

// Test reverse compilation
TEST_F(CompilerTest_325, CompileReversed_325) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test reverse compilation with anchors - anchors should be swapped
TEST_F(CompilerTest_325, CompileReversedAnchors_325) {
  Regexp* re = ParseRegexp("^hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  // When reversed, anchor_start and anchor_end should be swapped
  // Original: anchor_start=true, anchor_end=false
  // Reversed: anchor_start=false, anchor_end=true
  EXPECT_FALSE(prog->anchor_start());
  EXPECT_TRUE(prog->anchor_end());
  delete prog;
  re->Decref();
}

// Test compilation with character class
TEST_F(CompilerTest_325, CompileCharClass_325) {
  Regexp* re = ParseRegexp("[a-z]+");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with alternation
TEST_F(CompilerTest_325, CompileAlternation_325) {
  Regexp* re = ParseRegexp("foo|bar");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with repetition
TEST_F(CompilerTest_325, CompileRepetition_325) {
  Regexp* re = ParseRegexp("a{3,5}");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with capture groups
TEST_F(CompilerTest_325, CompileCaptureGroups_325) {
  Regexp* re = ParseRegexp("(foo)(bar)");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with dot
TEST_F(CompilerTest_325, CompileDot_325) {
  Regexp* re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that compiled program has valid start indices
TEST_F(CompilerTest_325, CompileStartIndices_325) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GE(prog->start(), 0);
  EXPECT_GE(prog->start_unanchored(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with very small memory limit may still work for simple patterns
TEST_F(CompilerTest_325, CompileSmallMemoryLimit_325) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  // Very small memory but simple pattern
  Prog* prog = re->CompileToProg(1 << 10);
  // With a very small limit, it might still succeed for trivial patterns
  // or it might return null. We just test it doesn't crash.
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test compilation with complex nested pattern
TEST_F(CompilerTest_325, CompileComplexPattern_325) {
  Regexp* re = ParseRegexp("(a+|b*)(c{2,4})?d");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test unanchored pattern has different start and start_unanchored
TEST_F(CompilerTest_325, CompileUnanchoredStartDifference_325) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  // For unanchored patterns, start_unanchored should include the DotStar prefix
  // and thus differ from start
  EXPECT_NE(prog->start(), prog->start_unanchored());
  delete prog;
  re->Decref();
}

// Test anchored pattern has same start and start_unanchored
TEST_F(CompilerTest_325, CompileAnchoredStartSame_325) {
  Regexp* re = ParseRegexp("^hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  // For anchored patterns, start and start_unanchored should be the same
  // since no DotStar prefix is added
  EXPECT_EQ(prog->start(), prog->start_unanchored());
  delete prog;
  re->Decref();
}

// Test CompileSet functionality
TEST_F(CompilerTest_325, CompileSetUnanchored_325) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar|baz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_325, CompileSetAnchorBoth_325) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_325, CompileSetAnchorStart_325) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_START, 0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with Unicode pattern
TEST_F(CompilerTest_325, CompileUnicodePattern_325) {
  Regexp* re = ParseRegexp("[\\x{100}-\\x{10FFFF}]");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with question mark (optional)
TEST_F(CompilerTest_325, CompileOptionalPattern_325) {
  Regexp* re = ParseRegexp("a?b?c?");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation produces Dump output (basic sanity)
TEST_F(CompilerTest_325, CompileDumpNotEmpty_325) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
  re->Decref();
}

// Test that reversed compilation of anchored end pattern swaps to anchor_start
TEST_F(CompilerTest_325, CompileReversedEndAnchor_325) {
  Regexp* re = ParseRegexp("hello$");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  // Original: anchor_start=false, anchor_end=true
  // Reversed: anchor_start=true, anchor_end=false
  EXPECT_TRUE(prog->anchor_start());
  EXPECT_FALSE(prog->anchor_end());
  delete prog;
  re->Decref();
}

// Test compilation with non-greedy quantifiers
TEST_F(CompilerTest_325, CompileNonGreedy_325) {
  Regexp* re = ParseRegexp("a+?b*?c??");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with word boundary
TEST_F(CompilerTest_325, CompileWordBoundary_325) {
  Regexp* re = ParseRegexp("\\bhello\\b");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test bytemap_range is positive for compiled program
TEST_F(CompilerTest_325, CompileByteMapRange_325) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  delete prog;
  re->Decref();
}

// Test compilation with single character
TEST_F(CompilerTest_325, CompileSingleChar_325) {
  Regexp* re = ParseRegexp("x");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_FALSE(prog->anchor_start());
  EXPECT_FALSE(prog->anchor_end());
  EXPECT_FALSE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test that reversed compilation of both anchors swaps them
TEST_F(CompilerTest_325, CompileReversedBothAnchors_325) {
  Regexp* re = ParseRegexp("^hello$");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  // Both anchors present, swap still results in both being true
  EXPECT_TRUE(prog->anchor_start());
  EXPECT_TRUE(prog->anchor_end());
  delete prog;
  re->Decref();
}

}  // namespace re2
