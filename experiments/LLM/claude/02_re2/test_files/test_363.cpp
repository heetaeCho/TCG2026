#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <map>
#include <string>

// We test CaptureNamesWalker indirectly through Regexp's public API
// since CaptureNamesWalker is used internally to extract capture names.

namespace re2 {

// Test that capture names can be extracted from a regex with named groups
TEST(CaptureNamesWalkerTest_363, NamedCaptureGroupsExtracted_363) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_EQ(groups.size(), 2u);

  auto it = groups.find(1);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "first");

  it = groups.find(2);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "second");
}

// Test with no named capture groups - map should be empty
TEST(CaptureNamesWalkerTest_363, NoNamedCaptureGroups_363) {
  RE2 re("(\\w+) (\\w+)");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_TRUE(groups.empty());
}

// Test with a single named capture group
TEST(CaptureNamesWalkerTest_363, SingleNamedCaptureGroup_363) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_EQ(groups.size(), 1u);

  auto it = groups.find(1);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "name");
}

// Test with mixed named and unnamed capture groups
TEST(CaptureNamesWalkerTest_363, MixedNamedAndUnnamedGroups_363) {
  RE2 re("(\\d+) (?P<word>\\w+) (\\d+)");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  // Only named groups should appear in the map
  EXPECT_EQ(groups.size(), 1u);

  auto it = groups.find(2);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "word");

  // Unnamed groups should not be in the map
  EXPECT_EQ(groups.find(1), groups.end());
  EXPECT_EQ(groups.find(3), groups.end());
}

// Test with nested named capture groups
TEST(CaptureNamesWalkerTest_363, NestedNamedCaptureGroups_363) {
  RE2 re("(?P<outer>(?P<inner>\\w+))");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_EQ(groups.size(), 2u);

  auto it = groups.find(1);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "outer");

  it = groups.find(2);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "inner");
}

// Test with empty pattern - no capture groups
TEST(CaptureNamesWalkerTest_363, EmptyPattern_363) {
  RE2 re("");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_TRUE(groups.empty());
}

// Test with alternation containing named groups
TEST(CaptureNamesWalkerTest_363, AlternationWithNamedGroups_363) {
  RE2 re("(?P<a>\\d+)|(?P<b>\\w+)");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_EQ(groups.size(), 2u);

  auto it = groups.find(1);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "a");

  it = groups.find(2);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "b");
}

// Test with many named capture groups
TEST(CaptureNamesWalkerTest_363, ManyNamedCaptureGroups_363) {
  RE2 re("(?P<g1>a)(?P<g2>b)(?P<g3>c)(?P<g4>d)(?P<g5>e)");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_EQ(groups.size(), 5u);

  for (int i = 1; i <= 5; i++) {
    auto it = groups.find(i);
    ASSERT_NE(it, groups.end());
    EXPECT_EQ(it->second, "g" + std::to_string(i));
  }
}

// Test pattern with non-capturing groups mixed in
TEST(CaptureNamesWalkerTest_363, NonCapturingGroupsIgnored_363) {
  RE2 re("(?:abc)(?P<named>\\w+)(?:def)");
  ASSERT_TRUE(re.ok());

  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_EQ(groups.size(), 1u);

  auto it = groups.find(1);
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, "named");
}

}  // namespace re2
