// File: re2_capturing_group_names_test_251.cc

#include <gtest/gtest.h>
#include <re2/re2.h>

#include <map>
#include <string>
#include <vector>
#include <algorithm>

using re2::RE2;

namespace {

// Utility to turn the returned map into a sorted vector of (index, name)
// to make assertions order-independent and readable.
static std::vector<std::pair<int, std::string>> ToSortedVec(
    const std::map<int, std::string>& m) {
  std::vector<std::pair<int, std::string>> v(m.begin(), m.end());
  std::sort(v.begin(), v.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });
  return v;
}

}  // namespace

// No named capturing groups -> empty map.
TEST(RE2CapturingGroupNamesTest_251, NoNamedGroups_ReturnsEmpty_251) {
  RE2 re("ab(c)d");  // only an unnamed group
  const auto& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
  EXPECT_EQ(ToSortedVec(names).size(), 0u);
}

// Single named capturing group -> {1: "name"}.
TEST(RE2CapturingGroupNamesTest_251, SingleNamedGroup_ReturnsIndex1Name_251) {
  RE2 re("(?P<foo>a)");  // one named group "foo"
  const auto& names = re.CapturingGroupNames();

  ASSERT_EQ(names.size(), 1u);
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "foo");
}

// Multiple named capturing groups -> correct index-to-name mapping.
TEST(RE2CapturingGroupNamesTest_251, MultipleNamedGroups_CorrectMapping_251) {
  RE2 re("(?P<x>[0-9]+)-(?P<y>[A-Za-z]+)");
  const auto& names = re.CapturingGroupNames();

  std::vector<std::pair<int, std::string>> expected = {
      {1, "x"},
      {2, "y"},
  };
  EXPECT_EQ(ToSortedVec(names), expected);
}

// Unnamed groups should not appear in the name map; only named ones do.
TEST(RE2CapturingGroupNamesTest_251, UnnamedGroupsAreExcluded_251) {
  RE2 re("(.)(?P<name>.)");  // group 1 unnamed, group 2 named
  const auto& names = re.CapturingGroupNames();

  // Only group 2 should be present with the correct name.
  ASSERT_EQ(names.size(), 1u);
  EXPECT_EQ(names.count(1), 0u);
  auto it = names.find(2);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "name");
}

// The method returns a const reference; subsequent calls should return
// the same reference (observable via address) and same content.
TEST(RE2CapturingGroupNamesTest_251, CachedResult_ReferenceStableAcrossCalls_251) {
  RE2 re("(?P<n>\\d+)");
  const auto* first_addr = &re.CapturingGroupNames();
  const auto* second_addr = &re.CapturingGroupNames();
  EXPECT_EQ(first_addr, second_addr) << "Reference from repeated calls should be stable";

  // And content remains consistent.
  const auto& names = re.CapturingGroupNames();
  ASSERT_EQ(names.size(), 1u);
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "n");
}

// Different RE2 instances with different patterns should yield independent maps.
TEST(RE2CapturingGroupNamesTest_251, DifferentPatterns_IndependentMaps_251) {
  RE2 re1("(?P<a>a)(?P<b>b)");
  RE2 re2("(?P<x>x)");

  const auto& names1 = re1.CapturingGroupNames();
  const auto& names2 = re2.CapturingGroupNames();

  std::vector<std::pair<int, std::string>> expected1 = {
      {1, "a"},
      {2, "b"},
  };
  std::vector<std::pair<int, std::string>> expected2 = {
      {1, "x"},
  };

  EXPECT_EQ(ToSortedVec(names1), expected1);
  EXPECT_EQ(ToSortedVec(names2), expected2);
}

