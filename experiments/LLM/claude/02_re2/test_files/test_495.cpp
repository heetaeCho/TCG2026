#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test through the public Regexp::Parse interface since ParseState is not directly
// accessible (it's a private nested class). We can observe PushRepeatOp behavior
// through parsing regex patterns that invoke it.

class PushRepeatOpTest_495 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test: Repeat operator on empty stack (no argument) should fail
TEST_F(PushRepeatOpTest_495, StarWithNoArgument_495) {
  // "*" alone should fail with kRegexpRepeatArgument
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

TEST_F(PushRepeatOpTest_495, PlusWithNoArgument_495) {
  // "+" alone should fail with kRegexpRepeatArgument
  Regexp* re = Regexp::Parse("+", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

TEST_F(PushRepeatOpTest_495, QuestWithNoArgument_495) {
  // "?" alone should fail with kRegexpRepeatArgument
  Regexp* re = Regexp::Parse("?", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

// Test: Normal star operation on a literal
TEST_F(PushRepeatOpTest_495, StarOnLiteral_495) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Normal plus operation on a literal
TEST_F(PushRepeatOpTest_495, PlusOnLiteral_495) {
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test: Normal quest operation on a literal
TEST_F(PushRepeatOpTest_495, QuestOnLiteral_495) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test: Non-greedy star (a*?)
TEST_F(PushRepeatOpTest_495, NonGreedyStar_495) {
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  // NonGreedy flag should be set
  EXPECT_TRUE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test: Non-greedy plus (a+?)
TEST_F(PushRepeatOpTest_495, NonGreedyPlus_495) {
  Regexp* re = Regexp::Parse("a+?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  EXPECT_TRUE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test: Non-greedy quest (a??)
TEST_F(PushRepeatOpTest_495, NonGreedyQuest_495) {
  Regexp* re = Regexp::Parse("a??", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpQuest);
  EXPECT_TRUE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test: Double star (a**) - same op and flags should be idempotent (returns true, collapsed to star)
TEST_F(PushRepeatOpTest_495, DoubleStarCollapse_495) {
  Regexp* re = Regexp::Parse("a**", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Plus followed by star (a+*) - different repeat ops should collapse to star
TEST_F(PushRepeatOpTest_495, PlusThenStarCollapse_495) {
  Regexp* re = Regexp::Parse("a+*", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Quest followed by star (a?*) - should collapse to star
TEST_F(PushRepeatOpTest_495, QuestThenStarCollapse_495) {
  Regexp* re = Regexp::Parse("a?*", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Star followed by plus (a*+) - should collapse to star
TEST_F(PushRepeatOpTest_495, StarThenPlusCollapse_495) {
  Regexp* re = Regexp::Parse("a*+", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Star followed by quest (a*?) - nongreedy star
TEST_F(PushRepeatOpTest_495, StarThenQuestNonGreedy_495) {
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_TRUE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test: Repeat operator after opening paren marker should fail
TEST_F(PushRepeatOpTest_495, StarAfterOpenParen_495) {
  Regexp* re = Regexp::Parse("(*)", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

// Test: Repeat operator after alternation marker should fail
TEST_F(PushRepeatOpTest_495, StarAfterPipe_495) {
  Regexp* re = Regexp::Parse("a|*", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

// Test: Complex pattern with repeat ops on groups
TEST_F(PushRepeatOpTest_495, StarOnGroup_495) {
  Regexp* re = Regexp::Parse("(ab)*", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Plus on group
TEST_F(PushRepeatOpTest_495, PlusOnGroup_495) {
  Regexp* re = Regexp::Parse("(ab)+", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test: Quest on group
TEST_F(PushRepeatOpTest_495, QuestOnGroup_495) {
  Regexp* re = Regexp::Parse("(ab)?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test: Star on character class
TEST_F(PushRepeatOpTest_495, StarOnCharClass_495) {
  Regexp* re = Regexp::Parse("[abc]*", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Plus on dot
TEST_F(PushRepeatOpTest_495, PlusOnDot_495) {
  Regexp* re = Regexp::Parse(".+", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test: Pattern with repeat at beginning of alternation fails
TEST_F(PushRepeatOpTest_495, PlusAfterPipe_495) {
  Regexp* re = Regexp::Parse("a|+", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

// Test: Quest after pipe fails
TEST_F(PushRepeatOpTest_495, QuestAfterPipe_495) {
  Regexp* re = Regexp::Parse("a|?", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

// Test: NonGreedy mode (default nongreedy flag)
TEST_F(PushRepeatOpTest_495, DefaultNonGreedyMode_495) {
  // With NonGreedy flag set in parse flags, greedy ops become nongreedy
  // and adding ? makes them greedy
  Regexp* re = Regexp::Parse("a*",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::NonGreedy),
      &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  // With NonGreedy base flag, the star should be nongreedy
  EXPECT_TRUE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test: With NonGreedy flag, adding ? toggles back to greedy
TEST_F(PushRepeatOpTest_495, NonGreedyFlagWithQuestionMarkToggles_495) {
  Regexp* re = Regexp::Parse("a*?",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::NonGreedy),
      &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  // NonGreedy XOR NonGreedy = no NonGreedy (greedy)
  EXPECT_FALSE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test: Multiple repeat combinations - quest then plus collapses to star
TEST_F(PushRepeatOpTest_495, QuestThenPlusCollapse_495) {
  Regexp* re = Regexp::Parse("a?+", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Plus then quest - different ops different greediness wraps
TEST_F(PushRepeatOpTest_495, PlusThenQuestCollapse_495) {
  Regexp* re = Regexp::Parse("a+?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  EXPECT_TRUE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test: Repeat after start of string should fail
TEST_F(PushRepeatOpTest_495, RepeatAtStart_495) {
  Regexp* re = Regexp::Parse("+b", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
}

}  // namespace re2
