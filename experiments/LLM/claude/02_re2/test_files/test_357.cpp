#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <map>
#include <string>

namespace re2 {

class NamedCapturesWalkerTest_357 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a regex with no named captures returns no named groups
TEST_F(NamedCapturesWalkerTest_357, NoNamedCaptures_357) {
    RE2 re("(\\d+)-(\\d+)");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_TRUE(groups.empty());
}

// Test that a regex with one named capture returns correct mapping
TEST_F(NamedCapturesWalkerTest_357, SingleNamedCapture_357) {
    RE2 re("(?P<year>\\d{4})");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 1u);
    auto it = groups.find("year");
    ASSERT_NE(it, groups.end());
    EXPECT_EQ(it->second, 1);
}

// Test that a regex with multiple named captures returns correct mappings
TEST_F(NamedCapturesWalkerTest_357, MultipleNamedCaptures_357) {
    RE2 re("(?P<year>\\d{4})-(?P<month>\\d{2})-(?P<day>\\d{2})");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 3u);
    
    auto it_year = groups.find("year");
    ASSERT_NE(it_year, groups.end());
    EXPECT_EQ(it_year->second, 1);
    
    auto it_month = groups.find("month");
    ASSERT_NE(it_month, groups.end());
    EXPECT_EQ(it_month->second, 2);
    
    auto it_day = groups.find("day");
    ASSERT_NE(it_day, groups.end());
    EXPECT_EQ(it_day->second, 3);
}

// Test mix of named and unnamed captures
TEST_F(NamedCapturesWalkerTest_357, MixedNamedAndUnnamedCaptures_357) {
    RE2 re("(\\w+)(?P<num>\\d+)(\\w+)");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 1u);
    auto it = groups.find("num");
    ASSERT_NE(it, groups.end());
    EXPECT_EQ(it->second, 2);
}

// Test empty regex pattern
TEST_F(NamedCapturesWalkerTest_357, EmptyPattern_357) {
    RE2 re("");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_TRUE(groups.empty());
}

// Test simple pattern without any captures
TEST_F(NamedCapturesWalkerTest_357, NoCapturesAtAll_357) {
    RE2 re("abc");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_TRUE(groups.empty());
}

// Test nested named captures
TEST_F(NamedCapturesWalkerTest_357, NestedNamedCaptures_357) {
    RE2 re("(?P<outer>(?P<inner>\\d+)\\w+)");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 2u);
    
    auto it_outer = groups.find("outer");
    ASSERT_NE(it_outer, groups.end());
    EXPECT_EQ(it_outer->second, 1);
    
    auto it_inner = groups.find("inner");
    ASSERT_NE(it_inner, groups.end());
    EXPECT_EQ(it_inner->second, 2);
}

// Test named capture with alternation
TEST_F(NamedCapturesWalkerTest_357, NamedCaptureWithAlternation_357) {
    RE2 re("(?P<val>abc|def)");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 1u);
    auto it = groups.find("val");
    ASSERT_NE(it, groups.end());
    EXPECT_EQ(it->second, 1);
}

// Test that querying named captures multiple times returns consistent results
TEST_F(NamedCapturesWalkerTest_357, ConsistentResults_357) {
    RE2 re("(?P<name>\\w+)");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups1 = re.NamedCapturingGroups();
    const std::map<std::string, int>& groups2 = re.NamedCapturingGroups();
    EXPECT_EQ(groups1, groups2);
}

// Test named capture index ordering with multiple groups
TEST_F(NamedCapturesWalkerTest_357, CaptureIndexOrdering_357) {
    RE2 re("(?P<a>x)(?P<b>y)(?P<c>z)");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 3u);
    EXPECT_EQ(groups.at("a"), 1);
    EXPECT_EQ(groups.at("b"), 2);
    EXPECT_EQ(groups.at("c"), 3);
}

// Test named capture with quantifiers
TEST_F(NamedCapturesWalkerTest_357, NamedCaptureWithQuantifier_357) {
    RE2 re("(?P<digits>\\d+)+");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 1u);
    auto it = groups.find("digits");
    ASSERT_NE(it, groups.end());
    EXPECT_EQ(it->second, 1);
}

// Test looking up a non-existent named capture
TEST_F(NamedCapturesWalkerTest_357, NonExistentNameLookup_357) {
    RE2 re("(?P<exists>\\d+)");
    ASSERT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.find("nonexistent"), groups.end());
}

}  // namespace re2
