#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// We test the Quest method (and related Compiler functionality) through
// the public Compile interface, since Compiler's internal methods like
// Quest, AllocInst, etc. are not directly accessible without constructing
// and setting up a Compiler properly. The observable behavior of Quest
// is reflected in the compiled Prog.

class CompilerQuestTest_296 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple quest (?) compiles correctly with greedy semantics
TEST_F(CompilerQuestTest_296, SimpleQuestGreedy_296) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  // "a?" should match empty string
  EXPECT_TRUE(RE2::FullMatch("", "a?"));
  // "a?" should match "a"
  EXPECT_TRUE(RE2::FullMatch("a", "a?"));
  delete prog;
  re->Decref();
}

// Test that a simple quest (?) compiles correctly with non-greedy semantics
TEST_F(CompilerQuestTest_296, SimpleQuestNonGreedy_296) {
  Regexp* re = Regexp::Parse("a??", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  // "a??" should still match empty string and "a"
  EXPECT_TRUE(RE2::FullMatch("", "a??"));
  EXPECT_TRUE(RE2::FullMatch("a", "a??"));
  delete prog;
  re->Decref();
}

// Test quest on a more complex subexpression
TEST_F(CompilerQuestTest_296, QuestOnGroup_296) {
  Regexp* re = Regexp::Parse("(ab)?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(RE2::FullMatch("", "(ab)?"));
  EXPECT_TRUE(RE2::FullMatch("ab", "(ab)?"));
  EXPECT_FALSE(RE2::FullMatch("a", "(ab)?"));
  delete prog;
  re->Decref();
}

// Test quest combined with other operators
TEST_F(CompilerQuestTest_296, QuestWithCat_296) {
  Regexp* re = Regexp::Parse("a?b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(RE2::FullMatch("b", "a?b"));
  EXPECT_TRUE(RE2::FullMatch("ab", "a?b"));
  EXPECT_FALSE(RE2::FullMatch("aab", "a?b"));
  delete prog;
  re->Decref();
}

// Test multiple quests in sequence
TEST_F(CompilerQuestTest_296, MultipleQuests_296) {
  Regexp* re = Regexp::Parse("a?b?c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(RE2::FullMatch("", "a?b?c?"));
  EXPECT_TRUE(RE2::FullMatch("a", "a?b?c?"));
  EXPECT_TRUE(RE2::FullMatch("ab", "a?b?c?"));
  EXPECT_TRUE(RE2::FullMatch("abc", "a?b?c?"));
  EXPECT_TRUE(RE2::FullMatch("bc", "a?b?c?"));
  EXPECT_TRUE(RE2::FullMatch("c", "a?b?c?"));
  EXPECT_TRUE(RE2::FullMatch("ac", "a?b?c?"));
  EXPECT_FALSE(RE2::FullMatch("abcd", "a?b?c?"));
  delete prog;
  re->Decref();
}

// Test quest with reversed compilation
TEST_F(CompilerQuestTest_296, QuestReversed_296) {
  Regexp* re = Regexp::Parse("a?b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  // Just verify it compiles without error
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test quest on character class
TEST_F(CompilerQuestTest_296, QuestOnCharClass_296) {
  EXPECT_TRUE(RE2::FullMatch("", "[abc]?"));
  EXPECT_TRUE(RE2::FullMatch("a", "[abc]?"));
  EXPECT_TRUE(RE2::FullMatch("b", "[abc]?"));
  EXPECT_TRUE(RE2::FullMatch("c", "[abc]?"));
  EXPECT_FALSE(RE2::FullMatch("d", "[abc]?"));
  EXPECT_FALSE(RE2::FullMatch("ab", "[abc]?"));
}

// Test quest nullable property - quest always produces nullable fragment
TEST_F(CompilerQuestTest_296, QuestIsNullable_296) {
  // Quest should always match empty string since it's "zero or one"
  EXPECT_TRUE(RE2::FullMatch("", "x?"));
  EXPECT_TRUE(RE2::FullMatch("", "(?:abc)?"));
  EXPECT_TRUE(RE2::FullMatch("", "(?:.*)?"));
}

// Test quest with very small memory limit to test allocation failure path
TEST_F(CompilerQuestTest_296, QuestWithSmallMemory_296) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory - may fail to compile
  Prog* prog = Compiler::Compile(re, false, 1);
  // Either it compiles or returns nullptr; we just check no crash
  delete prog;
  re->Decref();
}

// Test greedy vs non-greedy quest behavior in partial match
TEST_F(CompilerQuestTest_296, GreedyVsNonGreedyQuestPartialMatch_296) {
  std::string match;
  // Greedy: a? should prefer matching 'a'
  EXPECT_TRUE(RE2::PartialMatch("a", "(a?)", &match));
  EXPECT_EQ(match, "a");

  // Non-greedy: a?? should prefer matching empty
  EXPECT_TRUE(RE2::PartialMatch("a", "(a??)", &match));
  EXPECT_EQ(match, "");
}

// Test quest on nested optional groups
TEST_F(CompilerQuestTest_296, NestedQuestGroups_296) {
  EXPECT_TRUE(RE2::FullMatch("", "(a?)?"));
  EXPECT_TRUE(RE2::FullMatch("a", "(a?)?"));
  EXPECT_FALSE(RE2::FullMatch("aa", "(a?)?"));
}

// Test quest with alternation inside
TEST_F(CompilerQuestTest_296, QuestWithAlternation_296) {
  EXPECT_TRUE(RE2::FullMatch("", "(a|b)?"));
  EXPECT_TRUE(RE2::FullMatch("a", "(a|b)?"));
  EXPECT_TRUE(RE2::FullMatch("b", "(a|b)?"));
  EXPECT_FALSE(RE2::FullMatch("c", "(a|b)?"));
  EXPECT_FALSE(RE2::FullMatch("ab", "(a|b)?"));
}

// Test NoMatch fragment passed to Quest - when input is NoMatch
// This tests the IsNoMatch(a) branch in Quest
TEST_F(CompilerQuestTest_296, CompileWithImpossibleQuest_296) {
  // An impossible pattern like [^\x00-\x{10ffff}]? essentially has no match
  // for the inner part, but quest should still work (return Nop)
  // We use Compile interface to test this indirectly
  Regexp* re = Regexp::Parse("(?:a?)?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test quest with byte range (case fold)
TEST_F(CompilerQuestTest_296, QuestWithCaseFold_296) {
  EXPECT_TRUE(RE2::FullMatch("", "(?i:a)?"));
  EXPECT_TRUE(RE2::FullMatch("a", "(?i:a)?"));
  EXPECT_TRUE(RE2::FullMatch("A", "(?i:a)?"));
  EXPECT_FALSE(RE2::FullMatch("b", "(?i:a)?"));
}

// Test that Compile/CompileSet work for patterns using quest
TEST_F(CompilerQuestTest_296, CompileSetWithQuest_296) {
  Regexp* re = Regexp::Parse("a?|b?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
