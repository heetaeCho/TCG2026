#include <gtest/gtest.h>
#include <map>
#include <string>
#include "re2/re2.h"

namespace {

// Test that a pattern with no named groups returns an empty group names map
TEST(RE2GroupNames_239, NoNamedGroupsReturnsEmptyMap_239) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  EXPECT_TRUE(group_names.empty());
}

// Test that a pattern with no named groups returns empty named groups map
TEST(RE2GroupNames_239, NoNamedCapturingGroupsReturnsEmptyMap_239) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();
  EXPECT_TRUE(named_groups.empty());
}

// Test that a pattern with named groups returns correct group names
TEST(RE2GroupNames_239, NamedGroupReturnsCorrectMap_239) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  EXPECT_EQ(group_names.size(), 2);
  auto it1 = group_names.find(1);
  ASSERT_NE(it1, group_names.end());
  EXPECT_EQ(it1->second, "first");
  auto it2 = group_names.find(2);
  ASSERT_NE(it2, group_names.end());
  EXPECT_EQ(it2->second, "second");
}

// Test that named capturing groups returns correct name-to-index mapping
TEST(RE2GroupNames_239, NamedCapturingGroupsReturnsCorrectMap_239) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();
  EXPECT_EQ(named_groups.size(), 2);
  auto it1 = named_groups.find("first");
  ASSERT_NE(it1, named_groups.end());
  EXPECT_EQ(it1->second, 1);
  auto it2 = named_groups.find("second");
  ASSERT_NE(it2, named_groups.end());
  EXPECT_EQ(it2->second, 2);
}

// Test with unnamed capturing groups - no named group names expected
TEST(RE2GroupNames_239, UnnamedGroupsReturnEmptyGroupNames_239) {
  RE2 re("(\\w+) (\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  EXPECT_TRUE(group_names.empty());
  const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();
  EXPECT_TRUE(named_groups.empty());
}

// Test with mixed named and unnamed groups
TEST(RE2GroupNames_239, MixedNamedAndUnnamedGroups_239) {
  RE2 re("(\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  EXPECT_EQ(group_names.size(), 1);
  auto it = group_names.find(2);
  ASSERT_NE(it, group_names.end());
  EXPECT_EQ(it->second, "second");
}

// Test with invalid pattern - should still be safe to query
TEST(RE2GroupNames_239, InvalidPatternReturnsEmptyGroupNames_239) {
  RE2 re("(?P<bad");
  EXPECT_FALSE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  EXPECT_TRUE(group_names.empty());
  const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();
  EXPECT_TRUE(named_groups.empty());
}

// Test single named group
TEST(RE2GroupNames_239, SingleNamedGroup_239) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  EXPECT_EQ(group_names.size(), 1);
  EXPECT_EQ(group_names.at(1), "name");
}

}  // namespace
