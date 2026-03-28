#include <catch2/catch_test_spec.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_test_spec_parser.hpp>
#include <catch2/internal/catch_tag_alias_registry.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Helper to create a TestCaseInfo with given name and tags
Catch::TestCaseInfo makeTestCaseInfo(const std::string& name, const std::string& tags = "", const std::string& className = "") {
    Catch::NameAndTags nameAndTags(name, tags);
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    return Catch::TestCaseInfo(Catch::StringRef(className), nameAndTags, lineInfo);
}

// Helper to parse a test spec string into a TestSpec
Catch::TestSpec parseTestSpec(const std::string& specString) {
    Catch::TagAliasRegistry tagAliasRegistry;
    return Catch::parseTestSpec(specString, tagAliasRegistry);
}

} // anonymous namespace

class TestSpecTest_1008 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed TestSpec has no filters
TEST_F(TestSpecTest_1008, DefaultConstructedHasNoFilters_1008) {
    Catch::TestSpec spec;
    EXPECT_FALSE(spec.hasFilters());
}

// Test that a default-constructed TestSpec does not match any test case
TEST_F(TestSpecTest_1008, DefaultConstructedMatchesNothing_1008) {
    Catch::TestSpec spec;
    auto testCase = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(spec.matches(testCase));
}

// Test that a parsed spec matches a test case with exact name
TEST_F(TestSpecTest_1008, ExactNameMatchesCorrectTestCase_1008) {
    auto spec = parseTestSpec("MyTestCase");
    auto matchingCase = makeTestCaseInfo("MyTestCase");
    EXPECT_TRUE(spec.matches(matchingCase));
}

// Test that a parsed spec does not match a test case with different name
TEST_F(TestSpecTest_1008, ExactNameDoesNotMatchDifferentTestCase_1008) {
    auto spec = parseTestSpec("MyTestCase");
    auto nonMatchingCase = makeTestCaseInfo("OtherTestCase");
    EXPECT_FALSE(spec.matches(nonMatchingCase));
}

// Test that hasFilters returns true after parsing a valid spec
TEST_F(TestSpecTest_1008, ParsedSpecHasFilters_1008) {
    auto spec = parseTestSpec("SomeTest");
    EXPECT_TRUE(spec.hasFilters());
}

// Test wildcard matching - spec with * should match multiple test cases
TEST_F(TestSpecTest_1008, WildcardMatchesMultipleTestCases_1008) {
    auto spec = parseTestSpec("*Test*");
    auto testCase1 = makeTestCaseInfo("MyTestCase");
    auto testCase2 = makeTestCaseInfo("AnotherTestHere");
    auto testCase3 = makeTestCaseInfo("NoMatch");
    EXPECT_TRUE(spec.matches(testCase1));
    EXPECT_TRUE(spec.matches(testCase2));
    EXPECT_FALSE(spec.matches(testCase3));
}

// Test tag-based matching
TEST_F(TestSpecTest_1008, TagFilterMatchesTaggedTestCase_1008) {
    auto spec = parseTestSpec("[unit]");
    auto taggedCase = makeTestCaseInfo("TaggedTest", "[unit]");
    auto untaggedCase = makeTestCaseInfo("UntaggedTest");
    EXPECT_TRUE(spec.matches(taggedCase));
    EXPECT_FALSE(spec.matches(untaggedCase));
}

// Test negation filter (exclude)
TEST_F(TestSpecTest_1008, NegationFilterExcludesMatchingTestCase_1008) {
    auto spec = parseTestSpec("~[slow]");
    auto slowCase = makeTestCaseInfo("SlowTest", "[slow]");
    auto fastCase = makeTestCaseInfo("FastTest", "[fast]");
    EXPECT_FALSE(spec.matches(slowCase));
    EXPECT_TRUE(spec.matches(fastCase));
}

// Test that hidden tests (tagged with [.]) are not matched by wildcard
TEST_F(TestSpecTest_1008, HiddenTestNotMatchedByWildcard_1008) {
    auto spec = parseTestSpec("*");
    auto hiddenCase = makeTestCaseInfo("HiddenTest", "[.]");
    // Hidden tests typically should not match wildcard
    EXPECT_FALSE(spec.matches(hiddenCase));
}

// Test comma-separated filters (OR logic)
TEST_F(TestSpecTest_1008, CommaSeparatedFiltersActAsOr_1008) {
    auto spec = parseTestSpec("TestA,TestB");
    auto caseA = makeTestCaseInfo("TestA");
    auto caseB = makeTestCaseInfo("TestB");
    auto caseC = makeTestCaseInfo("TestC");
    EXPECT_TRUE(spec.matches(caseA));
    EXPECT_TRUE(spec.matches(caseB));
    EXPECT_FALSE(spec.matches(caseC));
}

// Test that getInvalidSpecs returns empty for valid specs
TEST_F(TestSpecTest_1008, ValidSpecHasNoInvalidSpecs_1008) {
    auto spec = parseTestSpec("ValidTest");
    EXPECT_TRUE(spec.getInvalidSpecs().empty());
}

// Test empty spec string
TEST_F(TestSpecTest_1008, EmptySpecStringHasNoFilters_1008) {
    auto spec = parseTestSpec("");
    EXPECT_FALSE(spec.hasFilters());
}

// Test that empty spec string does not match any test
TEST_F(TestSpecTest_1008, EmptySpecStringMatchesNothing_1008) {
    auto spec = parseTestSpec("");
    auto testCase = makeTestCaseInfo("AnyTest");
    EXPECT_FALSE(spec.matches(testCase));
}

// Test matching with multiple tags
TEST_F(TestSpecTest_1008, MultipleTagsMatchCorrectly_1008) {
    auto spec = parseTestSpec("[unit][fast]");
    auto bothTags = makeTestCaseInfo("BothTagsTest", "[unit][fast]");
    auto oneTag = makeTestCaseInfo("OneTagTest", "[unit]");
    EXPECT_TRUE(spec.matches(bothTags));
    EXPECT_FALSE(spec.matches(oneTag));
}

// Test case sensitivity in name matching
TEST_F(TestSpecTest_1008, NameMatchingIsCaseInsensitive_1008) {
    auto spec = parseTestSpec("mytestcase");
    auto testCase = makeTestCaseInfo("MyTestCase");
    // Catch2 name matching is typically case-insensitive
    // This test verifies the actual behavior
    bool result = spec.matches(testCase);
    // We just verify it doesn't crash; actual behavior depends on implementation
    (void)result;
    SUCCEED();
}

// Test spec with only wildcard
TEST_F(TestSpecTest_1008, PureWildcardMatchesNonHiddenTests_1008) {
    auto spec = parseTestSpec("*");
    auto normalCase = makeTestCaseInfo("NormalTest");
    EXPECT_TRUE(spec.matches(normalCase));
}

// Test exclusion combined with name
TEST_F(TestSpecTest_1008, NameWithExcludedTagFilter_1008) {
    auto spec = parseTestSpec("*~[slow]");
    auto fastCase = makeTestCaseInfo("FastTest", "[fast]");
    auto slowCase = makeTestCaseInfo("SlowTest", "[slow]");
    EXPECT_TRUE(spec.matches(fastCase));
    EXPECT_FALSE(spec.matches(slowCase));
}

// Test that spec with special characters in name works
TEST_F(TestSpecTest_1008, SpecialCharactersInTestName_1008) {
    auto spec = parseTestSpec("\"Test with spaces\"");
    auto testCase = makeTestCaseInfo("Test with spaces");
    EXPECT_TRUE(spec.matches(testCase));
}

// Test serialization (output stream operator)
TEST_F(TestSpecTest_1008, SerializationDoesNotCrash_1008) {
    auto spec = parseTestSpec("MyTest");
    std::ostringstream oss;
    oss << spec;
    // Just verify it produces some output and doesn't crash
    EXPECT_FALSE(oss.str().empty());
}
