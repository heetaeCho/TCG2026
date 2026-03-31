#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test fixture for Compiler tests
class CompilerTest_294 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal
TEST_F(CompilerTest_294, CompileSimpleLiteral_294) {
  Regexp* re = Regexp::Parse("a", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a+ (greedy plus)
TEST_F(CompilerTest_294, CompileGreedyPlus_294) {
  Regexp* re = Regexp::Parse("a+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a+? (nongreedy plus)
TEST_F(CompilerTest_294, CompileNonGreedyPlus_294) {
  Regexp* re = Regexp::Parse("a+?", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a* (greedy star)
TEST_F(CompilerTest_294, CompileGreedyStar_294) {
  Regexp* re = Regexp::Parse("a*", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a*? (nongreedy star)
TEST_F(CompilerTest_294, CompileNonGreedyStar_294) {
  Regexp* re = Regexp::Parse("a*?", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a? (greedy quest)
TEST_F(CompilerTest_294, CompileGreedyQuest_294) {
  Regexp* re = Regexp::Parse("a?", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile produces a valid Prog for a?? (nongreedy quest)
TEST_F(CompilerTest_294, CompileNonGreedyQuest_294) {
  Regexp* re = Regexp::Parse("a??", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with concatenation
TEST_F(CompilerTest_294, CompileConcatenation_294) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with alternation
TEST_F(CompilerTest_294, CompileAlternation_294) {
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with capture group
TEST_F(CompilerTest_294, CompileCaptureGroup_294) {
  Regexp* re = Regexp::Parse("(a)", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with byte range (character class)
TEST_F(CompilerTest_294, CompileCharClass_294) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with empty width assertions
TEST_F(CompilerTest_294, CompileEmptyWidth_294) {
  Regexp* re = Regexp::Parse("^a$", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile reversed
TEST_F(CompilerTest_294, CompileReversed_294) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with very low max_mem may return nullptr
TEST_F(CompilerTest_294, CompileVeryLowMaxMem_294) {
  // A complex pattern with very low memory limit should fail
  Regexp* re = Regexp::Parse("(a+|b+|c+){100}", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1);
  // With extremely low memory, compilation may fail
  // We just check it doesn't crash; result may be nullptr
  delete prog;
  re->Decref();
}

// Test Compile with dot
TEST_F(CompilerTest_294, CompileDot_294) {
  Regexp* re = Regexp::Parse(".", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with dot star
TEST_F(CompilerTest_294, CompileDotStar_294) {
  Regexp* re = Regexp::Parse(".*", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with Unicode pattern
TEST_F(CompilerTest_294, CompileUnicode_294) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored
TEST_F(CompilerTest_294, CompileSetUnanchored_294) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor start
TEST_F(CompilerTest_294, CompileSetAnchorStart_294) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor both
TEST_F(CompilerTest_294, CompileSetAnchorBoth_294) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a+ (greedy) compiled program matches correctly via RE2
TEST_F(CompilerTest_294, GreedyPlusMatchBehavior_294) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

// Test that a+? (nongreedy) compiled program matches correctly via RE2
TEST_F(CompilerTest_294, NonGreedyPlusMatchBehavior_294) {
  RE2 re("a+?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test that greedy vs nongreedy plus produce different match lengths
TEST_F(CompilerTest_294, GreedyVsNonGreedyPlusPartialMatch_294) {
  std::string greedy_match, nongreedy_match;
  RE2::PartialMatch("aaab", "(a+)", &greedy_match);
  RE2::PartialMatch("aaab", "(a+?)", &nongreedy_match);
  EXPECT_EQ(greedy_match, "aaa");
  EXPECT_EQ(nongreedy_match, "a");
}

// Test star behavior
TEST_F(CompilerTest_294, StarMatchBehavior_294) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

// Test quest behavior
TEST_F(CompilerTest_294, QuestMatchBehavior_294) {
  RE2 re("a?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

// Test complex expression
TEST_F(CompilerTest_294, ComplexExpression_294) {
  Regexp* re = Regexp::Parse("(a+b)*c?[d-f]+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compilation of an empty regex succeeds
TEST_F(CompilerTest_294, CompileEmptyRegex_294) {
  Regexp* re = Regexp::Parse("", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST_F(CompilerTest_294, CompileWordBoundary_294) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with foldcase (case insensitive)
TEST_F(CompilerTest_294, CompileCaseInsensitive_294) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition
TEST_F(CompilerTest_294, CompileRepetition_294) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the compiled program for plus has correct instruction count > 0
TEST_F(CompilerTest_294, CompilePlusHasInstructions_294) {
  Regexp* re = Regexp::Parse("a+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test deeply nested groups
TEST_F(CompilerTest_294, CompileNestedGroups_294) {
  Regexp* re = Regexp::Parse("((((a+)+)+)+)", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test alternation of plus patterns
TEST_F(CompilerTest_294, CompileAlternationOfPlus_294) {
  Regexp* re = Regexp::Parse("a+|b+|c+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with moderate max_mem
TEST_F(CompilerTest_294, CompileModerateMaxMem_294) {
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::PerlX, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 4096);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that greedy vs nongreedy star produce different match lengths
TEST_F(CompilerTest_294, GreedyVsNonGreedyStarPartialMatch_294) {
  std::string greedy_match, nongreedy_match;
  RE2::PartialMatch("aaab", "(a*)", &greedy_match);
  RE2::PartialMatch("aaab", "(a*?)", &nongreedy_match);
  EXPECT_EQ(greedy_match, "aaa");
  EXPECT_EQ(nongreedy_match, "");
}

}  // namespace re2
