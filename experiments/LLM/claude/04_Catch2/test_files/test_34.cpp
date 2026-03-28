#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_spec_parser.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_tag_alias_registry.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

namespace {

class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
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
};

Catch::TestSpec parseTestSpec(const std::string& specString) {
    Catch::TagAliasRegistry tagAliasRegistry;
    return Catch::TestSpecParser(tagAliasRegistry)
        .parse(specString)
        .testSpec();
}

class TestSpecTest_34 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default constructed TestSpec has no filters
TEST_F(TestSpecTest_34, DefaultConstructedHasNoFilters_34) {
    Catch::TestSpec spec;
    EXPECT_FALSE(spec.hasFilters());
}

// Test: Default constructed TestSpec has no invalid specs
TEST_F(TestSpecTest_34, DefaultConstructedHasNoInvalidSpecs_34) {
    Catch::TestSpec spec;
    EXPECT_TRUE(spec.getInvalidSpecs().empty());
}

// Test: Parsing a valid test name creates filters
TEST_F(TestSpecTest_34, ParsedSpecHasFilters_34) {
    auto spec = parseTestSpec("SomeTestName");
    EXPECT_TRUE(spec.hasFilters());
}

// Test: Parsing an empty string results in no filters
TEST_F(TestSpecTest_34, EmptyStringHasNoFilters_34) {
    auto spec = parseTestSpec("");
    EXPECT_FALSE(spec.hasFilters());
}

// Test: Stream output operator does not crash on empty spec
TEST_F(TestSpecTest_34, StreamOutputEmptySpec_34) {
    Catch::TestSpec spec;
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << spec);
}

// Test: Stream output operator produces output for non-empty spec
TEST_F(TestSpecTest_34, StreamOutputNonEmptySpec_34) {
    auto spec = parseTestSpec("MyTest");
    std::ostringstream oss;
    oss << spec;
    // The output should contain something related to the filter
    EXPECT_FALSE(oss.str().empty());
}

// Test: matches returns false for default spec (no filters) - per Catch2 semantics
TEST_F(TestSpecTest_34, DefaultSpecMatchesNothing_34) {
    Catch::TestSpec spec;
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestName", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_FALSE(spec.matches(*testCaseInfo));
}

// Test: Spec with a name pattern matches a matching test case
TEST_F(TestSpecTest_34, SpecMatchesMatchingTestCase_34) {
    auto spec = parseTestSpec("TestName");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestName", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testCaseInfo));
}

// Test: Spec with a name pattern does not match a non-matching test case
TEST_F(TestSpecTest_34, SpecDoesNotMatchNonMatchingTestCase_34) {
    auto spec = parseTestSpec("SomeOtherTest");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestName", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_FALSE(spec.matches(*testCaseInfo));
}

// Test: Tag-based spec matches test case with that tag
TEST_F(TestSpecTest_34, TagSpecMatchesTaggedTestCase_34) {
    auto spec = parseTestSpec("[tag1]");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestName", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testCaseInfo));
}

// Test: Tag-based spec does not match test case without that tag
TEST_F(TestSpecTest_34, TagSpecDoesNotMatchUntaggedTestCase_34) {
    auto spec = parseTestSpec("[tag2]");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestName", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_FALSE(spec.matches(*testCaseInfo));
}

// Test: Wildcard spec matches any test case
TEST_F(TestSpecTest_34, WildcardMatchesAnyTestCase_34) {
    auto spec = parseTestSpec("*");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"AnyTestName", "[anytag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testCaseInfo));
}

// Test: Partial wildcard match
TEST_F(TestSpecTest_34, PartialWildcardMatch_34) {
    auto spec = parseTestSpec("Test*");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestSomething", "[tag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testCaseInfo));
}

// Test: Partial wildcard does not match non-matching prefix
TEST_F(TestSpecTest_34, PartialWildcardNoMatchDifferentPrefix_34) {
    auto spec = parseTestSpec("Foo*");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestSomething", "[tag]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_FALSE(spec.matches(*testCaseInfo));
}

// Test: Negation spec excludes matching test
TEST_F(TestSpecTest_34, NegationExcludesMatchingTest_34) {
    auto spec = parseTestSpec("~TestName");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestName", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_FALSE(spec.matches(*testCaseInfo));
}

// Test: Negation spec includes non-matching test
TEST_F(TestSpecTest_34, NegationIncludesNonMatchingTest_34) {
    auto spec = parseTestSpec("~TestName");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"OtherTest", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testCaseInfo));
}

// Test: getInvalidSpecs returns empty for valid spec
TEST_F(TestSpecTest_34, ValidSpecHasNoInvalidSpecs_34) {
    auto spec = parseTestSpec("ValidName");
    EXPECT_TRUE(spec.getInvalidSpecs().empty());
}

// Test: Comma-separated specs (multiple filters)
TEST_F(TestSpecTest_34, MultipleFiltersWithComma_34) {
    auto spec = parseTestSpec("TestA,TestB");
    EXPECT_TRUE(spec.hasFilters());
    
    auto testCaseInfoA = Catch::makeTestCaseInfo(
        "test",
        {"TestA", ""},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    auto testCaseInfoB = Catch::makeTestCaseInfo(
        "test",
        {"TestB", ""},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    auto testCaseInfoC = Catch::makeTestCaseInfo(
        "test",
        {"TestC", ""},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testCaseInfoA));
    EXPECT_TRUE(spec.matches(*testCaseInfoB));
    EXPECT_FALSE(spec.matches(*testCaseInfoC));
}

// Test: Case sensitivity in matching
TEST_F(TestSpecTest_34, MatchingIsCaseInsensitive_34) {
    auto spec = parseTestSpec("testname");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"TestName", ""},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    // Catch2 test spec matching is case-insensitive
    EXPECT_TRUE(spec.matches(*testCaseInfo));
}

// Test: Quoted test name with special characters
TEST_F(TestSpecTest_34, QuotedTestNameExactMatch_34) {
    auto spec = parseTestSpec("\"Test Name With Spaces\"");
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test",
        {"Test Name With Spaces", ""},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testCaseInfo));
}

// Test: Stream operator on a spec with filters
TEST_F(TestSpecTest_34, StreamOperatorWithFilters_34) {
    auto spec = parseTestSpec("[tag1]");
    std::ostringstream oss;
    oss << spec;
    std::string output = oss.str();
    // Should produce some representation
    EXPECT_FALSE(output.empty());
}

// Test: Multiple tags combined in a single filter (AND logic)
TEST_F(TestSpecTest_34, MultipleTags_34) {
    auto spec = parseTestSpec("[tag1][tag2]");
    
    auto testWithBothTags = Catch::makeTestCaseInfo(
        "test",
        {"Test", "[tag1][tag2]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    auto testWithOneTag = Catch::makeTestCaseInfo(
        "test",
        {"Test", "[tag1]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*testWithBothTags));
    EXPECT_FALSE(spec.matches(*testWithOneTag));
}

// Test: Hidden tag test case (prefixed with .)
TEST_F(TestSpecTest_34, HiddenTagNotMatchedByWildcard_34) {
    auto spec = parseTestSpec("*");
    
    auto hiddenTest = Catch::makeTestCaseInfo(
        "test",
        {"HiddenTest", "[.hidden]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    // Catch2 wildcard typically doesn't match hidden tests
    EXPECT_FALSE(spec.matches(*hiddenTest));
}

// Test: Explicitly matching hidden tag
TEST_F(TestSpecTest_34, ExplicitHiddenTagMatch_34) {
    auto spec = parseTestSpec("[.hidden]");
    
    auto hiddenTest = Catch::makeTestCaseInfo(
        "test",
        {"HiddenTest", "[.hidden]"},
        {__FILE__, static_cast<std::size_t>(__LINE__)}
    );
    
    EXPECT_TRUE(spec.matches(*hiddenTest));
}

} // anonymous namespace
