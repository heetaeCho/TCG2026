#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include "re2/re2.h"

// We need to include or declare the function under test.
// Since it's in the re2_python namespace and uses pybind11's py::bytes,
// we cannot directly test RE2NamedCapturingGroupsShim without pybind11.
// Instead, we test the underlying RE2 methods that the shim relies on:
// - NumberOfCapturingGroups()
// - NamedCapturingGroups()
// These are the public interfaces exercised by the shim function.

class RE2NamedCapturingGroupsTest_55 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Pattern with no capturing groups returns empty named groups map
TEST_F(RE2NamedCapturingGroupsTest_55, NoCapturingGroups_55) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_TRUE(named.empty());
}

// Test: Pattern with unnamed capturing groups returns empty named groups map
TEST_F(RE2NamedCapturingGroupsTest_55, UnnamedCapturingGroups_55) {
  RE2 re("(hello)(world)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_TRUE(named.empty());
}

// Test: Pattern with one named capturing group
TEST_F(RE2NamedCapturingGroupsTest_55, SingleNamedCapturingGroup_55) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 1);
  auto it = named.find("name");
  ASSERT_NE(it, named.end());
  EXPECT_EQ(it->second, 1);
}

// Test: Pattern with multiple named capturing groups
TEST_F(RE2NamedCapturingGroupsTest_55, MultipleNamedCapturingGroups_55) {
  RE2 re("(?P<first>\\w+)\\s+(?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 2);

  auto it1 = named.find("first");
  ASSERT_NE(it1, named.end());
  EXPECT_EQ(it1->second, 1);

  auto it2 = named.find("second");
  ASSERT_NE(it2, named.end());
  EXPECT_EQ(it2->second, 2);
}

// Test: Mix of named and unnamed capturing groups
TEST_F(RE2NamedCapturingGroupsTest_55, MixedNamedAndUnnamedGroups_55) {
  RE2 re("(\\d+)(?P<word>\\w+)(\\d+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 1);
  auto it = named.find("word");
  ASSERT_NE(it, named.end());
  EXPECT_EQ(it->second, 2);
}

// Test: Named group index is correct when unnamed groups precede it
TEST_F(RE2NamedCapturingGroupsTest_55, NamedGroupIndexAfterUnnamed_55) {
  RE2 re("(a)(b)(?P<third>c)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 1);
  auto it = named.find("third");
  ASSERT_NE(it, named.end());
  EXPECT_EQ(it->second, 3);
}

// Test: Pattern with non-capturing groups should not affect named groups
TEST_F(RE2NamedCapturingGroupsTest_55, NonCapturingGroupsIgnored_55) {
  RE2 re("(?:hello)(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 1);
  auto it = named.find("name");
  ASSERT_NE(it, named.end());
  EXPECT_EQ(it->second, 1);
}

// Test: Empty pattern
TEST_F(RE2NamedCapturingGroupsTest_55, EmptyPattern_55) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_TRUE(named.empty());
}

// Test: Complex pattern with many named groups - ordering in map
TEST_F(RE2NamedCapturingGroupsTest_55, MultipleNamedGroupsOrdering_55) {
  RE2 re("(?P<year>\\d{4})-(?P<month>\\d{2})-(?P<day>\\d{2})");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 3);

  auto it_year = named.find("year");
  ASSERT_NE(it_year, named.end());
  EXPECT_EQ(it_year->second, 1);

  auto it_month = named.find("month");
  ASSERT_NE(it_month, named.end());
  EXPECT_EQ(it_month->second, 2);

  auto it_day = named.find("day");
  ASSERT_NE(it_day, named.end());
  EXPECT_EQ(it_day->second, 3);
}

// Test: CapturingGroupNames returns the reverse mapping
TEST_F(RE2NamedCapturingGroupsTest_55, CapturingGroupNamesReverseMapping_55) {
  RE2 re("(?P<alpha>a)(?P<beta>b)");
  ASSERT_TRUE(re.ok());
  const auto& group_names = re.CapturingGroupNames();
  EXPECT_EQ(group_names.size(), 2);

  auto it1 = group_names.find(1);
  ASSERT_NE(it1, group_names.end());
  EXPECT_EQ(it1->second, "alpha");

  auto it2 = group_names.find(2);
  ASSERT_NE(it2, group_names.end());
  EXPECT_EQ(it2->second, "beta");
}

// Test: Calling NamedCapturingGroups multiple times returns consistent results
TEST_F(RE2NamedCapturingGroupsTest_55, ConsistentResults_55) {
  RE2 re("(?P<foo>bar)");
  ASSERT_TRUE(re.ok());

  const auto& named1 = re.NamedCapturingGroups();
  const auto& named2 = re.NamedCapturingGroups();

  EXPECT_EQ(named1.size(), named2.size());
  EXPECT_EQ(&named1, &named2);  // Should return same reference
}

// Test: Invalid pattern - ok() returns false
TEST_F(RE2NamedCapturingGroupsTest_55, InvalidPattern_55) {
  RE2 re("(?P<name");  // malformed
  EXPECT_FALSE(re.ok());
}

// Test: Pattern with nested named groups (RE2 doesn't support duplicate names
// in the same way, but nested groups are valid)
TEST_F(RE2NamedCapturingGroupsTest_55, NestedGroups_55) {
  RE2 re("(?P<outer>(?P<inner>\\w+)\\d+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 2);

  auto it_outer = named.find("outer");
  ASSERT_NE(it_outer, named.end());
  EXPECT_EQ(it_outer->second, 1);

  auto it_inner = named.find("inner");
  ASSERT_NE(it_inner, named.end());
  EXPECT_EQ(it_inner->second, 2);
}

// Test: NumberOfCapturingGroups matches the total groups (named + unnamed)
TEST_F(RE2NamedCapturingGroupsTest_55, NumberOfCapturingGroupsTotal_55) {
  RE2 re("(a)(?P<b>b)(c)(?P<d>d)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 4);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 2);  // only named groups
}

// Test: Pattern with alternation and named groups
TEST_F(RE2NamedCapturingGroupsTest_55, AlternationWithNamedGroups_55) {
  RE2 re("(?P<choice>cat|dog)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 1);
  auto it = named.find("choice");
  ASSERT_NE(it, named.end());
  EXPECT_EQ(it->second, 1);
}

// Test: Pattern consisting only of literal text
TEST_F(RE2NamedCapturingGroupsTest_55, LiteralPattern_55) {
  RE2 re("just some text 123");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
  const auto& named = re.NamedCapturingGroups();
  EXPECT_TRUE(named.empty());
}
