#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_spec_parser.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Helper to create a TestSpec from a string expression
static Catch::TestSpec parseTestSpec(const std::string& specString) {
    Catch::TestSpecParser parser(Catch::ITagAliasRegistry::get());
    parser.parse(specString);
    return parser.testSpec();
}

// Helper to create TestCaseInfo for testing
static Catch::TestCaseInfo makeTestCaseInfo(const std::string& name,
                                             const std::string& className = "",
                                             const std::string& tags = "") {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    // Parse tags from the string
    std::vector<Catch::Tag> parsedTags;
    // Simple tag extraction
    std::string remaining = tags;
    while (!remaining.empty()) {
        auto open = remaining.find('[');
        auto close = remaining.find(']');
        if (open != std::string::npos && close != std::string::npos && close > open) {
            std::string tagStr = remaining.substr(open, close - open + 1);
            remaining = remaining.substr(close + 1);
            // We need to use the Catch mechanisms to properly create tags
        } else {
            break;
        }
    }
    
    return Catch::TestCaseInfo(className, {tags, lineInfo}, name, lineInfo);
}

class FilterTest_33 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FilterTest_33, EmptySpecMatchesNothing_33) {
    Catch::TestSpec spec = parseTestSpec("");
    // An empty spec should have no filters
    EXPECT_TRUE(spec.getFilters().empty());
}

TEST_F(FilterTest_33, SimpleNameMatchesCorrectTestCase_33) {
    Catch::TestSpec spec = parseTestSpec("MyTest");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("MyTest");
    // The filter should match a test case with the exact name
    EXPECT_TRUE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, SimpleNameDoesNotMatchDifferentTestCase_33) {
    Catch::TestSpec spec = parseTestSpec("MyTest");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("OtherTest");
    EXPECT_FALSE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, WildcardMatchesMultipleTests_33) {
    Catch::TestSpec spec = parseTestSpec("*Test*");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tc1 = makeTestCaseInfo("MyTestCase");
    auto tc2 = makeTestCaseInfo("AnotherTestHere");
    auto tc3 = makeTestCaseInfo("NoMatch");

    EXPECT_TRUE(filters[0].matches(tc1));
    EXPECT_TRUE(filters[0].matches(tc2));
    EXPECT_FALSE(filters[0].matches(tc3));
}

TEST_F(FilterTest_33, ExcludePatternDoesNotMatch_33) {
    Catch::TestSpec spec = parseTestSpec("~MyTest");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("MyTest");
    EXPECT_FALSE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, ExcludePatternMatchesOtherTests_33) {
    Catch::TestSpec spec = parseTestSpec("~MyTest");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("OtherTest");
    EXPECT_TRUE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, SerializeToOutputsNonEmpty_33) {
    Catch::TestSpec spec = parseTestSpec("MyTest");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    std::ostringstream oss;
    oss << filters[0];
    std::string output = oss.str();
    // The serialized output should not be empty for a non-empty filter
    EXPECT_FALSE(output.empty());
}

TEST_F(FilterTest_33, SerializeToOperatorStreamOutput_33) {
    Catch::TestSpec spec = parseTestSpec("SomeName");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    std::ostringstream oss;
    oss << filters[0];
    std::string result = oss.str();
    // The output should contain some representation related to the filter
    EXPECT_GT(result.size(), 0u);
}

TEST_F(FilterTest_33, TagFilterMatchesTaggedTest_33) {
    Catch::TestSpec spec = parseTestSpec("[fast]");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("AnyTest", "", "[fast]");
    EXPECT_TRUE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, TagFilterDoesNotMatchUntaggedTest_33) {
    Catch::TestSpec spec = parseTestSpec("[fast]");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("AnyTest", "", "[slow]");
    EXPECT_FALSE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, ExcludeTagFilterRejectsMatchingTag_33) {
    Catch::TestSpec spec = parseTestSpec("~[slow]");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("AnyTest", "", "[slow]");
    EXPECT_FALSE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, ExcludeTagFilterAcceptsNonMatchingTag_33) {
    Catch::TestSpec spec = parseTestSpec("~[slow]");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcInfo = makeTestCaseInfo("AnyTest", "", "[fast]");
    EXPECT_TRUE(filters[0].matches(tcInfo));
}

TEST_F(FilterTest_33, WildcardOnlyMatchesAll_33) {
    Catch::TestSpec spec = parseTestSpec("*");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tc1 = makeTestCaseInfo("Anything");
    auto tc2 = makeTestCaseInfo("Something Else");
    EXPECT_TRUE(filters[0].matches(tc1));
    EXPECT_TRUE(filters[0].matches(tc2));
}

TEST_F(FilterTest_33, MultipleFiltersCommaCreatesMultipleFilters_33) {
    Catch::TestSpec spec = parseTestSpec("TestA,TestB");
    auto filters = spec.getFilters();
    // Comma should create separate filters
    EXPECT_GE(filters.size(), 2u);
}

TEST_F(FilterTest_33, CombinedNameAndExcludeTag_33) {
    Catch::TestSpec spec = parseTestSpec("MyTest ~[slow]");
    auto filters = spec.getFilters();
    ASSERT_FALSE(filters.empty());

    auto tcMatch = makeTestCaseInfo("MyTest", "", "[fast]");
    auto tcNoMatch = makeTestCaseInfo("MyTest", "", "[slow]");

    EXPECT_TRUE(filters[0].matches(tcMatch));
    EXPECT_FALSE(filters[0].matches(tcNoMatch));
}
