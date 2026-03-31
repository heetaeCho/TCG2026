#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"

namespace re2 {

// Test DFA behavior through the public RE2 interface, since DFA::State
// is an internal implementation detail not directly constructable.
// We verify DFA correctness through RE2 matching operations.

class DFATest_437 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test normal matching using DFA path
TEST_F(DFATest_437, SimpleMatch_437) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

TEST_F(DFATest_437, PartialMatch_437) {
  RE2 re("ello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

TEST_F(DFATest_437, EmptyPattern_437) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

TEST_F(DFATest_437, EmptyString_437) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST_F(DFATest_437, ComplexPattern_437) {
  RE2 re("(a|b)+c*d");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abd", re));
  EXPECT_TRUE(RE2::FullMatch("aaccd", re));
  EXPECT_TRUE(RE2::FullMatch("bbbd", re));
  EXPECT_FALSE(RE2::FullMatch("cd", re));
}

TEST_F(DFATest_437, CharacterClass_437) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
  EXPECT_FALSE(RE2::FullMatch("hello123", re));
}

TEST_F(DFATest_437, RepetitionBoundary_437) {
  RE2 re("a{3,5}");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

TEST_F(DFATest_437, LongInput_437) {
  RE2 re("a*b");
  ASSERT_TRUE(re.ok());
  std::string input(10000, 'a');
  input += 'b';
  EXPECT_TRUE(RE2::FullMatch(input, re));
}

TEST_F(DFATest_437, NoMatch_437) {
  RE2 re("xyz");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::PartialMatch("abc", re));
}

TEST_F(DFATest_437, DotStar_437) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("anything goes here!", re));
}

TEST_F(DFATest_437, AnchoredMatch_437) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

TEST_F(DFATest_437, AlternationMatch_437) {
  RE2 re("cat|dog|bird");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_TRUE(RE2::FullMatch("bird", re));
  EXPECT_FALSE(RE2::FullMatch("fish", re));
}

}  // namespace re2
