#include <gtest/gtest.h>
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using namespace Catch;

namespace {

// Helper to create a TestCaseInfo with a given name
std::unique_ptr<TestCaseInfo> makeTestCase(const std::string& name) {
    NameAndTags nameAndTags(name, "");
    SourceLineInfo lineInfo("test_file.cpp", 1);
    return std::make_unique<TestCaseInfo>(""_catch_sr, nameAndTags, lineInfo);
}

} // anonymous namespace

class NamePatternTest_1003 : public ::testing::Test {
protected:
};

// Test exact match
TEST_F(NamePatternTest_1003, ExactMatch_1003) {
    TestSpec::NamePattern pattern("MyTest", "MyTest");
    auto tc = makeTestCase("MyTest");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test case insensitive matching
TEST_F(NamePatternTest_1003, CaseInsensitiveMatch_1003) {
    TestSpec::NamePattern pattern("mytest", "mytest");
    auto tc = makeTestCase("MyTest");
    EXPECT_TRUE(pattern.matches(*tc));
}

TEST_F(NamePatternTest_1003, CaseInsensitiveMatchUpperPattern_1003) {
    TestSpec::NamePattern pattern("MYTEST", "MYTEST");
    auto tc = makeTestCase("mytest");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test wildcard at end
TEST_F(NamePatternTest_1003, WildcardAtEnd_1003) {
    TestSpec::NamePattern pattern("My*", "My*");
    auto tc = makeTestCase("MyTest");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test wildcard at beginning
TEST_F(NamePatternTest_1003, WildcardAtBeginning_1003) {
    TestSpec::NamePattern pattern("*Test", "*Test");
    auto tc = makeTestCase("MyTest");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test wildcard at both ends
TEST_F(NamePatternTest_1003, WildcardAtBothEnds_1003) {
    TestSpec::NamePattern pattern("*Tes*", "*Tes*");
    auto tc = makeTestCase("MyTestCase");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test no match
TEST_F(NamePatternTest_1003, NoMatch_1003) {
    TestSpec::NamePattern pattern("OtherTest", "OtherTest");
    auto tc = makeTestCase("MyTest");
    EXPECT_FALSE(pattern.matches(*tc));
}

// Test wildcard no match
TEST_F(NamePatternTest_1003, WildcardNoMatch_1003) {
    TestSpec::NamePattern pattern("Foo*", "Foo*");
    auto tc = makeTestCase("BarTest");
    EXPECT_FALSE(pattern.matches(*tc));
}

// Test empty pattern with wildcard matches everything
TEST_F(NamePatternTest_1003, WildcardOnlyMatchesAll_1003) {
    TestSpec::NamePattern pattern("*", "*");
    auto tc = makeTestCase("AnyTestName");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test empty test case name
TEST_F(NamePatternTest_1003, EmptyTestCaseNameWithWildcard_1003) {
    TestSpec::NamePattern pattern("*", "*");
    auto tc = makeTestCase("");
    // Empty name gets replaced with a default name, so wildcard should still match
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test pattern with spaces
TEST_F(NamePatternTest_1003, PatternWithSpaces_1003) {
    TestSpec::NamePattern pattern("my test case", "my test case");
    auto tc = makeTestCase("My Test Case");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test partial wildcard match at end
TEST_F(NamePatternTest_1003, WildcardPartialMatchEnd_1003) {
    TestSpec::NamePattern pattern("*case", "*case");
    auto tc = makeTestCase("MyTestCase");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test wildcard with no matching suffix
TEST_F(NamePatternTest_1003, WildcardNoMatchingSuffix_1003) {
    TestSpec::NamePattern pattern("*xyz", "*xyz");
    auto tc = makeTestCase("MyTestCase");
    EXPECT_FALSE(pattern.matches(*tc));
}

// Test single character name
TEST_F(NamePatternTest_1003, SingleCharacterMatch_1003) {
    TestSpec::NamePattern pattern("a", "a");
    auto tc = makeTestCase("A");
    EXPECT_TRUE(pattern.matches(*tc));
}

// Test longer pattern than test name
TEST_F(NamePatternTest_1003, LongerPatternThanName_1003) {
    TestSpec::NamePattern pattern("VeryLongPatternName", "VeryLongPatternName");
    auto tc = makeTestCase("Short");
    EXPECT_FALSE(pattern.matches(*tc));
}
