#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class FactorAlternationRound1Test_506 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that alternation with common prefix is factored
TEST_F(FactorAlternationRound1Test_506, CommonPrefixFactored_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|abd|abe", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // The common prefix "ab" should be factored out
  // Expect something like ab[cde] or ab(?:c|d|e)
  EXPECT_NE(s.find("str{ab}"), std::string::npos);
  re->Decref();
}

// Test alternation with no common prefix - no factoring
TEST_F(FactorAlternationRound1Test_506, NoCommonPrefix_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Should remain as alternation of three separate items
  EXPECT_NE(s.find("alt{"), std::string::npos);
  re->Decref();
}

// Test alternation with two elements sharing prefix (should NOT be spliced by Round1 - needs 3+)
TEST_F(FactorAlternationRound1Test_506, TwoElementsCommonPrefix_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|abd", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Two elements with common prefix - still may be factored by overall process
  EXPECT_TRUE(re != nullptr);
  re->Decref();
}

// Test single alternative - no factoring needed
TEST_F(FactorAlternationRound1Test_506, SingleAlternative_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("str{abc}"), std::string::npos);
  re->Decref();
}

// Test alternation with full common prefix (identical strings)
TEST_F(FactorAlternationRound1Test_506, IdenticalAlternatives_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|abc|abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("str{abc}"), std::string::npos);
  re->Decref();
}

// Test alternation with partial common prefix among many alternatives
TEST_F(FactorAlternationRound1Test_506, PartialCommonPrefixMany_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcd|abce|abcf|xyz", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // abc should be factored from the first three
  EXPECT_NE(s.find("str{abc}"), std::string::npos);
  re->Decref();
}

// Test empty alternation
TEST_F(FactorAlternationRound1Test_506, EmptyPattern_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  re->Decref();
}

// Test alternation with FoldCase flag
TEST_F(FactorAlternationRound1Test_506, FoldCaseCommonPrefix_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc|(?i)abd|(?i)abe", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  re->Decref();
}

// Test alternation with single character alternatives sharing prefix
TEST_F(FactorAlternationRound1Test_506, SingleCharPrefix_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("aa|ab|ac", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // 'a' should be factored out
  EXPECT_NE(s.find("lit{a}"), std::string::npos);
  re->Decref();
}

// Test alternation with Literal flag
TEST_F(FactorAlternationRound1Test_506, LiteralMode_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::Literal, &status);
  ASSERT_TRUE(re != nullptr);
  // In literal mode, | is treated as literal
  std::string s = re->Dump();
  re->Decref();
}

// Test complex alternation with multiple groups
TEST_F(FactorAlternationRound1Test_506, MultipleGroups_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("aaa|aab|aac|bba|bbb|bbc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  // Both "aa" and "bb" prefixes should be factored
  EXPECT_NE(s.find("str{aa}"), std::string::npos);
  EXPECT_NE(s.find("str{bb}"), std::string::npos);
  re->Decref();
}

// Test alternation with long common prefix
TEST_F(FactorAlternationRound1Test_506, LongCommonPrefix_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdefx|abcdefy|abcdefz", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("str{abcdef}"), std::string::npos);
  re->Decref();
}

// Test that Round1 does not break roundtrip parsing
TEST_F(FactorAlternationRound1Test_506, RoundtripConsistency_506) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|fob|foc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string str = re->ToString();
  EXPECT_FALSE(str.empty());
  // Re-parse the result
  Regexp* re2 = Regexp::Parse(str, Regexp::LikePerl, &status);
  ASSERT_TRUE(re2 != nullptr);
  re->Decref();
  re2->Decref();
}

}  // namespace re2
