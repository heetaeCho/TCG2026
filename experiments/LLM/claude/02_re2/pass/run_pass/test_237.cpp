#include "re2/re2.h"
#include <string>
#include <map>
#include <vector>
#include "gtest/gtest.h"

namespace re2 {

// Test RE2 construction and basic operations that exercise empty_string paths
class RE2EmptyStringTest_237 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RE2EmptyStringTest_237, DefaultConstructedPatternIsEmpty_237) {
    // An invalid/empty pattern scenario
    RE2 re("");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), "");
}

TEST_F(RE2EmptyStringTest_237, EmptyPatternMatchesEmptyString_237) {
    RE2 re("");
    EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST_F(RE2EmptyStringTest_237, EmptyPatternPartialMatchesAnyString_237) {
    RE2 re("");
    EXPECT_TRUE(RE2::PartialMatch("hello", re));
    EXPECT_TRUE(RE2::PartialMatch("", re));
}

TEST_F(RE2EmptyStringTest_237, InvalidPatternError_237) {
    RE2 re("(unclosed");
    EXPECT_FALSE(re.ok());
    // error() should return a non-empty error string
    EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2EmptyStringTest_237, ValidPatternNoError_237) {
    RE2 re("abc");
    EXPECT_TRUE(re.ok());
    EXPECT_TRUE(re.error().empty());
}

TEST_F(RE2EmptyStringTest_237, NamedGroupsOnPatternWithoutGroups_237) {
    RE2 re("abc");
    EXPECT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_TRUE(groups.empty());
}

TEST_F(RE2EmptyStringTest_237, CapturingGroupNamesOnPatternWithoutGroups_237) {
    RE2 re("abc");
    EXPECT_TRUE(re.ok());
    const std::map<int, std::string>& names = re.CapturingGroupNames();
    EXPECT_TRUE(names.empty());
}

TEST_F(RE2EmptyStringTest_237, NamedGroupsWithNamedCapture_237) {
    RE2 re("(?P<name>\\w+)");
    EXPECT_TRUE(re.ok());
    const std::map<std::string, int>& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 1u);
    auto it = groups.find("name");
    EXPECT_NE(it, groups.end());
    EXPECT_EQ(it->second, 1);
}

TEST_F(RE2EmptyStringTest_237, CapturingGroupNamesWithNamedCapture_237) {
    RE2 re("(?P<name>\\w+)");
    EXPECT_TRUE(re.ok());
    const std::map<int, std::string>& names = re.CapturingGroupNames();
    EXPECT_EQ(names.size(), 1u);
    auto it = names.find(1);
    EXPECT_NE(it, names.end());
    EXPECT_EQ(it->second, "name");
}

TEST_F(RE2EmptyStringTest_237, NumberOfCapturingGroups_237) {
    RE2 re("(a)(b)(c)");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2EmptyStringTest_237, EmptyPatternNumberOfCapturingGroups_237) {
    RE2 re("");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2EmptyStringTest_237, FullMatchSimplePattern_237) {
    EXPECT_TRUE(RE2::FullMatch("hello", "h.*o"));
    EXPECT_FALSE(RE2::FullMatch("hello", "^world$"));
}

TEST_F(RE2EmptyStringTest_237, PartialMatchSimplePattern_237) {
    EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
    EXPECT_FALSE(RE2::PartialMatch("hello", "xyz"));
}

TEST_F(RE2EmptyStringTest_237, PatternAccessor_237) {
    RE2 re("test_pattern");
    EXPECT_EQ(re.pattern(), "test_pattern");
}

TEST_F(RE2EmptyStringTest_237, ErrorArgForInvalidPattern_237) {
    RE2 re("[invalid");
    EXPECT_FALSE(re.ok());
    EXPECT_FALSE(re.error().empty());
    EXPECT_NE(re.error_code(), RE2::NoError);
}

}  // namespace re2
