#include "gtest/gtest.h"
#include "re2/re2.h"
#include <map>
#include <string>
#include <vector>

namespace re2 {

// Test fixture for NamedCapturingGroups tests
class NamedCapturingGroupsTest_250 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a pattern with no named groups returns an empty map
TEST_F(NamedCapturingGroupsTest_250, NoNamedGroups_250) {
  RE2 re("(a)(b)(c)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test that a pattern with a single named group returns the correct mapping
TEST_F(NamedCapturingGroupsTest_250, SingleNamedGroup_250) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 1u);
  auto it = groups.find("name");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 1);
}

// Test that a pattern with multiple named groups returns correct mappings
TEST_F(NamedCapturingGroupsTest_250, MultipleNamedGroups_250) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+) (?P<third>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 3u);

  auto it1 = groups.find("first");
  ASSERT_NE(it1, groups.end());
  EXPECT_EQ(it1->second, 1);

  auto it2 = groups.find("second");
  ASSERT_NE(it2, groups.end());
  EXPECT_EQ(it2->second, 2);

  auto it3 = groups.find("third");
  ASSERT_NE(it3, groups.end());
  EXPECT_EQ(it3->second, 3);
}

// Test mixed named and unnamed groups
TEST_F(NamedCapturingGroupsTest_250, MixedNamedAndUnnamedGroups_250) {
  RE2 re("(a)(?P<name>b)(c)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 1u);
  auto it = groups.find("name");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 2);
}

// Test that a simple literal pattern with no groups returns an empty map
TEST_F(NamedCapturingGroupsTest_250, LiteralPatternNoGroups_250) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test an empty pattern
TEST_F(NamedCapturingGroupsTest_250, EmptyPattern_250) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test that calling NamedCapturingGroups multiple times returns same result (idempotent via call_once)
TEST_F(NamedCapturingGroupsTest_250, CalledMultipleTimes_250) {
  RE2 re("(?P<alpha>\\d+)-(?P<beta>\\d+)");
  ASSERT_TRUE(re.ok());

  const std::map<std::string, int>& groups1 = re.NamedCapturingGroups();
  const std::map<std::string, int>& groups2 = re.NamedCapturingGroups();

  // Should return the same reference
  EXPECT_EQ(&groups1, &groups2);
  EXPECT_EQ(groups1.size(), 2u);
}

// Test named group with nested groups
TEST_F(NamedCapturingGroupsTest_250, NestedNamedGroups_250) {
  RE2 re("(?P<outer>(?P<inner>\\w+))");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2u);

  auto outer = groups.find("outer");
  ASSERT_NE(outer, groups.end());
  EXPECT_EQ(outer->second, 1);

  auto inner = groups.find("inner");
  ASSERT_NE(inner, groups.end());
  EXPECT_EQ(inner->second, 2);
}

// Test that named group indices are correct with alternation
TEST_F(NamedCapturingGroupsTest_250, NamedGroupsWithAlternation_250) {
  RE2 re("(?P<a>foo)|(?P<b>bar)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2u);

  auto a = groups.find("a");
  ASSERT_NE(a, groups.end());
  EXPECT_EQ(a->second, 1);

  auto b = groups.find("b");
  ASSERT_NE(b, groups.end());
  EXPECT_EQ(b->second, 2);
}

// Test invalid pattern - NamedCapturingGroups should still return a valid (empty) map
TEST_F(NamedCapturingGroupsTest_250, InvalidPattern_250) {
  RE2 re("(?P<name");  // Invalid regex
  // The regex may or may not be ok, but we should be able to call NamedCapturingGroups safely
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  // For an invalid pattern, expect empty map
  EXPECT_TRUE(groups.empty());
}

// Test named group with special characters in the group content
TEST_F(NamedCapturingGroupsTest_250, NamedGroupSpecialContent_250) {
  RE2 re("(?P<ip>\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 1u);
  auto it = groups.find("ip");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 1);
}

// Test looking up a non-existent group name returns end()
TEST_F(NamedCapturingGroupsTest_250, NonExistentGroupName_250) {
  RE2 re("(?P<existing>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.find("nonexistent"), groups.end());
}

// Test with only non-capturing groups
TEST_F(NamedCapturingGroupsTest_250, NonCapturingGroups_250) {
  RE2 re("(?:a)(?:b)(?:c)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Additional test: verify CapturingGroupNames is consistent with NamedCapturingGroups
TEST_F(NamedCapturingGroupsTest_250, ConsistentWithCapturingGroupNames_250) {
  RE2 re("(?P<year>\\d{4})-(?P<month>\\d{2})-(?P<day>\\d{2})");
  ASSERT_TRUE(re.ok());

  const std::map<std::string, int>& named = re.NamedCapturingGroups();
  const std::map<int, std::string>& names = re.CapturingGroupNames();

  // Each entry in NamedCapturingGroups should have a corresponding entry in CapturingGroupNames
  for (const auto& pair : named) {
    auto it = names.find(pair.second);
    ASSERT_NE(it, names.end());
    EXPECT_EQ(it->second, pair.first);
  }
}

// Test NumberOfCapturingGroups alongside NamedCapturingGroups
TEST_F(NamedCapturingGroupsTest_250, NumberOfCapturingGroupsRelation_250) {
  RE2 re("(a)(?P<b>b)(c)(?P<d>d)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 4);
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  // Only 2 named groups out of 4 total
  EXPECT_EQ(groups.size(), 2u);
}

// Test with a complex pattern
TEST_F(NamedCapturingGroupsTest_250, ComplexPattern_250) {
  RE2 re("(?P<protocol>https?)://(?P<host>[^/]+)(?P<path>/[^ ]*)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 3u);

  EXPECT_EQ(groups.at("protocol"), 1);
  EXPECT_EQ(groups.at("host"), 2);
  EXPECT_EQ(groups.at("path"), 3);
}

}  // namespace re2
