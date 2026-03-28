#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <map>

// Test that a simple pattern compiles successfully
TEST(RE2Test_238, SimplePatternCompiles_238) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

// Test that named groups are accessible
TEST(RE2Test_238, NamedGroupsExist_238) {
  RE2 re("(?P<name>\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 1);
  EXPECT_NE(groups.find("name"), groups.end());
  EXPECT_EQ(groups.at("name"), 1);
}

// Test that a pattern with no named groups returns an empty map
TEST(RE2Test_238, NoNamedGroupsReturnsEmptyMap_238) {
  RE2 re("(\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test that an invalid pattern reports not ok
TEST(RE2Test_238, InvalidPatternNotOk_238) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
}

// Test that an invalid pattern returns empty named groups
TEST(RE2Test_238, InvalidPatternEmptyNamedGroups_238) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test that an invalid pattern returns empty group names
TEST(RE2Test_238, InvalidPatternEmptyGroupNames_238) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  const std::map<int, std::string>& groups = re.CapturingGroupNames();
  EXPECT_TRUE(groups.empty());
}

// Test multiple named groups
TEST(RE2Test_238, MultipleNamedGroups_238) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("first"), 1);
  EXPECT_EQ(groups.at("second"), 2);
}

// Test CapturingGroupNames (int -> string mapping)
TEST(RE2Test_238, CapturingGroupNamesMapping_238) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<int, std::string>& group_names = re.CapturingGroupNames();
  EXPECT_EQ(group_names.size(), 2);
  EXPECT_EQ(group_names.at(1), "first");
  EXPECT_EQ(group_names.at(2), "second");
}

// Test empty pattern
TEST(RE2Test_238, EmptyPattern_238) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test pattern with no capturing groups at all
TEST(RE2Test_238, NoCaptureGroups_238) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test FullMatch with named groups
TEST(RE2Test_238, FullMatchWithNamedGroups_238) {
  RE2 re("(?P<word>\\w+)");
  EXPECT_TRUE(re.ok());
  std::string word;
  EXPECT_TRUE(RE2::FullMatch("hello", re, &word));
  EXPECT_EQ(word, "hello");
}

// Test that NumberOfCapturingGroups includes both named and unnamed
TEST(RE2Test_238, NumberOfCapturingGroupsMixed_238) {
  RE2 re("(\\d+) (?P<name>\\w+)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
  const std::map<std::string, int>& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 1);
  EXPECT_EQ(named.at("name"), 2);
}

// Test pattern() returns the original pattern string
TEST(RE2Test_238, PatternReturnsOriginal_238) {
  RE2 re("(?P<grp>abc)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "(?P<grp>abc)");
}

// Test error message is empty for valid pattern
TEST(RE2Test_238, NoErrorForValidPattern_238) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(re.error().empty());
}

// Test error message is non-empty for invalid pattern
TEST(RE2Test_238, ErrorForInvalidPattern_238) {
  RE2 re("[");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}
