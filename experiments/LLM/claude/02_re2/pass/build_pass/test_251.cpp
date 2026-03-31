#include "gtest/gtest.h"
#include "re2/re2.h"
#include <map>
#include <string>

namespace re2 {

// Test: CapturingGroupNames returns empty map for pattern with no capturing groups
TEST(RE2CapturingGroupNamesTest_251, NoCapturingGroups_251) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

// Test: CapturingGroupNames returns empty map for pattern with unnamed capturing groups
TEST(RE2CapturingGroupNamesTest_251, UnnamedCapturingGroups_251) {
  RE2 re("(hello)(world)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  // Unnamed groups should not appear in the map
  EXPECT_TRUE(names.empty());
}

// Test: CapturingGroupNames returns correct names for named capturing groups
TEST(RE2CapturingGroupNamesTest_251, SingleNamedCapturingGroup_251) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 1u);
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "name");
}

// Test: CapturingGroupNames returns correct names for multiple named capturing groups
TEST(RE2CapturingGroupNamesTest_251, MultipleNamedCapturingGroups_251) {
  RE2 re("(?P<first>\\w+)\\s(?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2u);
  auto it1 = names.find(1);
  ASSERT_NE(it1, names.end());
  EXPECT_EQ(it1->second, "first");
  auto it2 = names.find(2);
  ASSERT_NE(it2, names.end());
  EXPECT_EQ(it2->second, "second");
}

// Test: CapturingGroupNames with mix of named and unnamed groups
TEST(RE2CapturingGroupNamesTest_251, MixedNamedAndUnnamedGroups_251) {
  RE2 re("(\\d+)(?P<word>\\w+)(\\d+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  // Only named group should be in the map
  EXPECT_EQ(names.size(), 1u);
  auto it = names.find(2);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "word");
  // Unnamed groups should not be present
  EXPECT_EQ(names.find(1), names.end());
  EXPECT_EQ(names.find(3), names.end());
}

// Test: CapturingGroupNames called multiple times returns the same result (idempotent)
TEST(RE2CapturingGroupNamesTest_251, CalledMultipleTimes_251) {
  RE2 re("(?P<foo>bar)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names1 = re.CapturingGroupNames();
  const std::map<int, std::string>& names2 = re.CapturingGroupNames();
  EXPECT_EQ(&names1, &names2);  // Should return the same reference
  EXPECT_EQ(names1.size(), 1u);
  EXPECT_EQ(names1.at(1), "foo");
}

// Test: CapturingGroupNames for empty pattern
TEST(RE2CapturingGroupNamesTest_251, EmptyPattern_251) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

// Test: CapturingGroupNames for pattern with non-capturing groups only
TEST(RE2CapturingGroupNamesTest_251, NonCapturingGroups_251) {
  RE2 re("(?:hello)(?:world)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

// Test: CapturingGroupNames with nested named groups
TEST(RE2CapturingGroupNamesTest_251, NestedNamedGroups_251) {
  RE2 re("(?P<outer>(?P<inner>\\w+))");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2u);
  auto it1 = names.find(1);
  ASSERT_NE(it1, names.end());
  EXPECT_EQ(it1->second, "outer");
  auto it2 = names.find(2);
  ASSERT_NE(it2, names.end());
  EXPECT_EQ(it2->second, "inner");
}

// Test: CapturingGroupNames for complex pattern with alternation and named groups
TEST(RE2CapturingGroupNamesTest_251, AlternationWithNamedGroups_251) {
  RE2 re("(?P<a>foo)|(?P<b>bar)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2u);
  EXPECT_EQ(names.at(1), "a");
  EXPECT_EQ(names.at(2), "b");
}

// Test: CapturingGroupNames consistency with NumberOfCapturingGroups
TEST(RE2CapturingGroupNamesTest_251, ConsistencyWithNumberOfCapturingGroups_251) {
  RE2 re("(?P<x>\\d+)(\\w+)(?P<y>\\s+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  // Only named groups should be in the map (groups 1 and 3)
  EXPECT_EQ(names.size(), 2u);
  EXPECT_EQ(names.at(1), "x");
  EXPECT_EQ(names.at(3), "y");
}

// Test: CapturingGroupNames consistency with NamedCapturingGroups
TEST(RE2CapturingGroupNamesTest_251, ConsistencyWithNamedCapturingGroups_251) {
  RE2 re("(?P<alpha>\\w+)\\s(?P<beta>\\d+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();
  
  // They should be inverses of each other
  for (const auto& pair : group_names) {
    auto it = named_groups.find(pair.second);
    ASSERT_NE(it, named_groups.end());
    EXPECT_EQ(it->second, pair.first);
  }
  for (const auto& pair : named_groups) {
    auto it = group_names.find(pair.second);
    ASSERT_NE(it, group_names.end());
    EXPECT_EQ(it->second, pair.first);
  }
}

// Test: CapturingGroupNames for a simple literal pattern (no groups at all)
TEST(RE2CapturingGroupNamesTest_251, SimpleLiteralPattern_251) {
  RE2 re("abc123");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

// Test: CapturingGroupNames with a single character class pattern
TEST(RE2CapturingGroupNamesTest_251, CharacterClassPattern_251) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

// Test: CapturingGroupNames with many named groups
TEST(RE2CapturingGroupNamesTest_251, ManyNamedGroups_251) {
  RE2 re("(?P<g1>a)(?P<g2>b)(?P<g3>c)(?P<g4>d)(?P<g5>e)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 5u);
  EXPECT_EQ(names.at(1), "g1");
  EXPECT_EQ(names.at(2), "g2");
  EXPECT_EQ(names.at(3), "g3");
  EXPECT_EQ(names.at(4), "g4");
  EXPECT_EQ(names.at(5), "g5");
}

}  // namespace re2
