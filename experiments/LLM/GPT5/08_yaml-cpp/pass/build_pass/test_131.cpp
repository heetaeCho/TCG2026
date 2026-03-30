// File: ./TestProjects/yaml-cpp/test/block_entry_tests_131.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"  // YAML::Exp::BlockEntry()

namespace {

class BlockEntryTest_131 : public ::testing::Test {
 protected:
  const YAML::RegEx& ex = YAML::Exp::BlockEntry();
};

TEST_F(BlockEntryTest_131, ReturnsSameInstanceEveryCall_131) {
  const YAML::RegEx* p1 = &YAML::Exp::BlockEntry();
  const YAML::RegEx* p2 = &YAML::Exp::BlockEntry();
  EXPECT_EQ(p1, p2);
}

TEST_F(BlockEntryTest_131, MatchesDashOnly_131) {
  EXPECT_TRUE(ex.Matches(std::string("-")));
}

TEST_F(BlockEntryTest_131, DoesNotMatchEmptyString_131) {
  EXPECT_FALSE(ex.Matches(std::string("")));
}

TEST_F(BlockEntryTest_131, DoesNotMatchNonDashStart_131) {
  EXPECT_FALSE(ex.Matches(std::string("x")));
  EXPECT_FALSE(ex.Matches(std::string("+")));
  EXPECT_FALSE(ex.Matches(std::string(" ")));
}

TEST_F(BlockEntryTest_131, DoesNotMatchExtraNonBlankAfterDash_131) {
  // The pattern begins with '-', and any optional follow-up is not expected to be '-'.
  // "--" should therefore not be a full match.
  EXPECT_FALSE(ex.Matches(std::string("--")));
}

TEST_F(BlockEntryTest_131, AcceptsDashFollowedByCommonBlankOrBreak_131) {
  // BlockEntry() is defined as: '-' + (BlankOrBreak() | empty)
  // Verify it can consume common blank/break characters when present.
  EXPECT_TRUE(ex.Matches(std::string("- ")));
  EXPECT_TRUE(ex.Matches(std::string("-\n")));
  EXPECT_TRUE(ex.Matches(std::string("-\r\n")));
  EXPECT_TRUE(ex.Matches(std::string("-\t")));
}

}  // namespace
