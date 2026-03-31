#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <catch2/catch_test_spec.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_test_spec_parser.hpp>
#include <catch2/catch_tag_alias_autoregistrar.hpp>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch;

// Test fixture for TestSpec tests
class TestSpecTest_1010 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed TestSpec has no filters
TEST_F(TestSpecTest_1010, DefaultConstructedHasNoFilters_1010) {
    TestSpec spec;
    EXPECT_FALSE(spec.hasFilters());
}

// Test that a default-constructed TestSpec has no invalid specs
TEST_F(TestSpecTest_1010, DefaultConstructedHasNoInvalidSpecs_1010) {
    TestSpec spec;
    const auto& invalidSpecs = spec.getInvalidSpecs();
    EXPECT_TRUE(invalidSpecs.empty());
}

// Test that getInvalidSpecs returns a reference to a vector of strings
TEST_F(TestSpecTest_1010, GetInvalidSpecsReturnsVectorReference_1010) {
    TestSpec spec;
    const auto& invalidSpecs1 = spec.getInvalidSpecs();
    const auto& invalidSpecs2 = spec.getInvalidSpecs();
    // Both calls should return reference to the same object
    EXPECT_EQ(&invalidSpecs1, &invalidSpecs2);
}

// Test that a TestSpec with no filters does not match any test case
TEST_F(TestSpecTest_1010, NoFiltersDoesNotMatch_1010) {
    TestSpec spec;
    // Create a minimal TestCaseInfo - we need to check that an empty spec doesn't match
    // Since hasFilters is false, matches should return false
    // We create a TestCaseInfo using its constructor
    auto testInfo = makeTestCaseInfo(
        "",
        {"test case", "[tag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    EXPECT_FALSE(spec.matches(*testInfo));
}

// Test parsing a valid test spec creates filters
TEST_F(TestSpecTest_1010, ParsedSpecHasFilters_1010) {
    TestSpec spec;
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("some test");
    spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

// Test parsing a valid test spec results in no invalid specs
TEST_F(TestSpecTest_1010, ValidParsedSpecHasNoInvalidSpecs_1010) {
    TestSpec spec;
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("some test");
    spec = parser.testSpec();
    EXPECT_TRUE(spec.getInvalidSpecs().empty());
}

// Test that a parsed spec can match a test case with matching name
TEST_F(TestSpecTest_1010, ParsedSpecMatchesMatchingTestCase_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("my test case");
    TestSpec spec = parser.testSpec();

    auto testInfo = makeTestCaseInfo(
        "",
        {"my test case", "[tag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    EXPECT_TRUE(spec.matches(*testInfo));
}

// Test that a parsed spec does not match a non-matching test case
TEST_F(TestSpecTest_1010, ParsedSpecDoesNotMatchNonMatchingTestCase_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("my test case");
    TestSpec spec = parser.testSpec();

    auto testInfo = makeTestCaseInfo(
        "",
        {"different test case", "[tag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    EXPECT_FALSE(spec.matches(*testInfo));
}

// Test wildcard matching
TEST_F(TestSpecTest_1010, WildcardMatchesMultipleTestCases_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("*test*");
    TestSpec spec = parser.testSpec();

    auto testInfo1 = makeTestCaseInfo(
        "",
        {"my test case", "[tag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    auto testInfo2 = makeTestCaseInfo(
        "",
        {"another test here", "[other]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );

    EXPECT_TRUE(spec.matches(*testInfo1));
    EXPECT_TRUE(spec.matches(*testInfo2));
}

// Test tag-based filter
TEST_F(TestSpecTest_1010, TagFilterMatchesTaggedTestCase_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("[mytag]");
    TestSpec spec = parser.testSpec();

    auto testInfo = makeTestCaseInfo(
        "",
        {"some test", "[mytag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    EXPECT_TRUE(spec.matches(*testInfo));
}

// Test tag-based filter does not match untagged test case
TEST_F(TestSpecTest_1010, TagFilterDoesNotMatchUntaggedTestCase_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("[mytag]");
    TestSpec spec = parser.testSpec();

    auto testInfo = makeTestCaseInfo(
        "",
        {"some test", "[othertag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    EXPECT_FALSE(spec.matches(*testInfo));
}

// Test negation filter
TEST_F(TestSpecTest_1010, NegationFilterExcludesMatchingTestCase_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("~[skip]");
    TestSpec spec = parser.testSpec();

    auto testInfoSkip = makeTestCaseInfo(
        "",
        {"skipped test", "[skip]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    auto testInfoNormal = makeTestCaseInfo(
        "",
        {"normal test", "[normal]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );

    EXPECT_FALSE(spec.matches(*testInfoSkip));
    EXPECT_TRUE(spec.matches(*testInfoNormal));
}

// Test empty spec string
TEST_F(TestSpecTest_1010, EmptyStringProducesNoFilters_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("");
    TestSpec spec = parser.testSpec();
    EXPECT_FALSE(spec.hasFilters());
}

// Test that hasFilters returns consistent results
TEST_F(TestSpecTest_1010, HasFiltersConsistentOnMultipleCalls_1010) {
    TestSpec spec;
    EXPECT_FALSE(spec.hasFilters());
    EXPECT_FALSE(spec.hasFilters());

    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("test");
    spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
    EXPECT_TRUE(spec.hasFilters());
}

// Test copy semantics of TestSpec
TEST_F(TestSpecTest_1010, CopyConstructedSpecPreservesFilters_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("my test");
    TestSpec spec1 = parser.testSpec();
    TestSpec spec2 = spec1;

    EXPECT_EQ(spec1.hasFilters(), spec2.hasFilters());
    EXPECT_EQ(spec1.getInvalidSpecs().size(), spec2.getInvalidSpecs().size());
}

// Test assignment semantics of TestSpec
TEST_F(TestSpecTest_1010, AssignedSpecPreservesFilters_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("my test");
    TestSpec spec1 = parser.testSpec();
    TestSpec spec2;
    spec2 = spec1;

    EXPECT_EQ(spec1.hasFilters(), spec2.hasFilters());
}

// Test that getInvalidSpecs size is zero for valid specs
TEST_F(TestSpecTest_1010, ValidSpecHasZeroInvalidSpecs_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("valid test name");
    TestSpec spec = parser.testSpec();
    EXPECT_EQ(spec.getInvalidSpecs().size(), 0u);
}

// Test multiple comma-separated filters
TEST_F(TestSpecTest_1010, MultipleFiltersWithComma_1010) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("test1,test2");
    TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());

    auto testInfo1 = makeTestCaseInfo(
        "",
        {"test1", ""},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    auto testInfo2 = makeTestCaseInfo(
        "",
        {"test2", ""},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );

    EXPECT_TRUE(spec.matches(*testInfo1));
    EXPECT_TRUE(spec.matches(*testInfo2));
}
