#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the necessary Catch2 headers
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// We need to work with the TestSpec class through its public interface only.
// Since TestSpec has a friend class TestSpecParser, we may need it to populate filters.
#include "catch2/internal/catch_test_spec_parser.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

namespace {

// Helper to create a TestSpec from a string pattern using the TestSpecParser
Catch::TestSpec parseTestSpec(const std::string& spec) {
    Catch::TestSpec result;
    Catch::TestSpecParser parser(Catch::ITagAliasRegistry::get());
    parser.parse(spec).testSpec();
    return parser.parse(spec).testSpec();
}

// A mock config for use in matchesByFilter
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(std::ostream&, stream, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(unsigned int, rngSeed, (), (const, override));
    MOCK_METHOD(Catch::UseColour, useColour, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(std::vector<Catch::ReporterSpec> const&, getProcessedReporterSpecs, (), (const, override));
    MOCK_METHOD(Catch::TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, showHelp, (), (const, override));
};

} // anonymous namespace

// Test that a default-constructed TestSpec has no filters
TEST(TestSpecTest_1007, DefaultConstructedHasNoFilters_1007) {
    Catch::TestSpec spec;
    EXPECT_FALSE(spec.hasFilters());
}

// Test that a default-constructed TestSpec returns empty invalid specs
TEST(TestSpecTest_1007, DefaultConstructedHasNoInvalidSpecs_1007) {
    Catch::TestSpec spec;
    const auto& invalidSpecs = spec.getInvalidSpecs();
    EXPECT_TRUE(invalidSpecs.empty());
}

// Test that parsing a valid test name pattern results in filters being present
TEST(TestSpecTest_1007, ParsedSpecHasFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("SomeTestName");
    EXPECT_TRUE(spec.hasFilters());
}

// Test that parsing an empty string results in no filters
TEST(TestSpecTest_1007, EmptyStringHasNoFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("");
    EXPECT_FALSE(spec.hasFilters());
}

// Test that parsing a wildcard pattern results in filters
TEST(TestSpecTest_1007, WildcardPatternHasFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("*");
    EXPECT_TRUE(spec.hasFilters());
}

// Test that parsing a tag pattern results in filters
TEST(TestSpecTest_1007, TagPatternHasFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("[tag1]");
    EXPECT_TRUE(spec.hasFilters());
}

// Test that parsing multiple comma-separated patterns results in filters
TEST(TestSpecTest_1007, MultipleFiltersHasFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("test1,test2");
    EXPECT_TRUE(spec.hasFilters());
}

// Test that matchesByFilter with empty test cases returns empty matches
TEST(TestSpecTest_1007, MatchesByFilterWithEmptyTestCasesReturnsEmpty_1007) {
    Catch::TestSpec spec = parseTestSpec("*");
    std::vector<Catch::TestCaseHandle> testCases;
    MockConfig config;

    auto matches = spec.matchesByFilter(testCases, config);
    // With no test cases provided, each filter should match nothing
    // but there should be as many match entries as there are filters
    for (const auto& match : matches) {
        EXPECT_TRUE(match.tests.empty());
    }
}

// Test copy semantics - copied TestSpec should have same filter state
TEST(TestSpecTest_1007, CopyConstructorPreservesFilters_1007) {
    Catch::TestSpec spec1 = parseTestSpec("SomeTest");
    Catch::TestSpec spec2 = spec1;
    EXPECT_EQ(spec1.hasFilters(), spec2.hasFilters());
}

// Test move semantics
TEST(TestSpecTest_1007, MoveConstructorTransfersFilters_1007) {
    Catch::TestSpec spec1 = parseTestSpec("SomeTest");
    EXPECT_TRUE(spec1.hasFilters());
    Catch::TestSpec spec2 = std::move(spec1);
    EXPECT_TRUE(spec2.hasFilters());
}

// Test that assignment works properly
TEST(TestSpecTest_1007, AssignmentOperatorWorks_1007) {
    Catch::TestSpec spec1 = parseTestSpec("Test1");
    Catch::TestSpec spec2;
    EXPECT_FALSE(spec2.hasFilters());
    spec2 = spec1;
    EXPECT_TRUE(spec2.hasFilters());
}

// Test that a negated filter pattern is still considered a filter
TEST(TestSpecTest_1007, NegatedFilterHasFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("~[hide]");
    EXPECT_TRUE(spec.hasFilters());
}

// Test that an exclusion pattern with name results in filters
TEST(TestSpecTest_1007, ExclusionPatternHasFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("~SomeTest");
    EXPECT_TRUE(spec.hasFilters());
}

// Test getInvalidSpecs on a valid spec returns empty
TEST(TestSpecTest_1007, ValidSpecHasNoInvalidSpecs_1007) {
    Catch::TestSpec spec = parseTestSpec("ValidTestName");
    const auto& invalidSpecs = spec.getInvalidSpecs();
    EXPECT_TRUE(invalidSpecs.empty());
}

// Test that a spec with only whitespace has no filters
TEST(TestSpecTest_1007, WhitespaceOnlyHasNoFilters_1007) {
    Catch::TestSpec spec = parseTestSpec("   ");
    EXPECT_FALSE(spec.hasFilters());
}
