#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;

// A concrete Pattern implementation for testing
class MockPattern : public TestSpec::Pattern {
public:
    explicit MockPattern(bool matchResult, const std::string& name = "mock")
        : TestSpec::Pattern(name), m_matchResult(matchResult) {}

    bool matches(TestCaseInfo const& /*testCase*/) const override {
        return m_matchResult;
    }

private:
    bool m_matchResult;
    void serializeTo(std::ostream& out) const override {
        out << "MockPattern";
    }
};

// Helper to create a TestCaseInfo with specific properties
static TestCaseInfo makeTestCaseInfo(const std::string& name, const std::string& tags = "") {
    return TestCaseInfo(
        ""_catch_sr,
        NameAndTags(name, tags),
        SourceLineInfo("test_file.cpp", 1)
    );
}

class TestSpecFilterTest_1005 : public ::testing::Test {
protected:
    TestSpec::Filter filter;
};

// Test: Empty filter with non-hidden test case should return true
TEST_F(TestSpecFilterTest_1005, EmptyFilterMatchesNonHiddenTestCase_1005) {
    auto tc = makeTestCaseInfo("VisibleTest");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Empty filter with hidden test case (tagged [.]) should return false
TEST_F(TestSpecFilterTest_1005, EmptyFilterDoesNotMatchHiddenTestCase_1005) {
    auto tc = makeTestCaseInfo("HiddenTest", "[.]");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Single required pattern that matches should return true
TEST_F(TestSpecFilterTest_1005, SingleRequiredPatternMatches_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Single required pattern that does not match should return false
TEST_F(TestSpecFilterTest_1005, SingleRequiredPatternDoesNotMatch_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Required pattern with hidden test case - should still match if pattern matches
// Because when there are required patterns, should_use is set to true regardless of hidden status
TEST_F(TestSpecFilterTest_1005, RequiredPatternMatchesHiddenTestCase_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("HiddenTest", "[.]");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Required pattern that doesn't match hidden test case
TEST_F(TestSpecFilterTest_1005, RequiredPatternDoesNotMatchHiddenTestCase_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("HiddenTest", "[.]");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Single forbidden pattern that matches should return false
TEST_F(TestSpecFilterTest_1005, SingleForbiddenPatternMatchesReturnsFalse_1005) {
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Single forbidden pattern that does not match should return true for non-hidden
TEST_F(TestSpecFilterTest_1005, SingleForbiddenPatternDoesNotMatchReturnsTrue_1005) {
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Forbidden pattern with hidden test case - no required patterns, so should_use = false
TEST_F(TestSpecFilterTest_1005, ForbiddenPatternOnlyWithHiddenTestCase_1005) {
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("HiddenTest", "[.]");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Multiple required patterns - all match
TEST_F(TestSpecFilterTest_1005, MultipleRequiredPatternsAllMatch_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Multiple required patterns - first doesn't match
TEST_F(TestSpecFilterTest_1005, MultipleRequiredPatternsFirstFails_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(false));
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Multiple required patterns - second doesn't match
TEST_F(TestSpecFilterTest_1005, MultipleRequiredPatternsSecondFails_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_required.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Multiple forbidden patterns - first matches (should fail)
TEST_F(TestSpecFilterTest_1005, MultipleForbiddenPatternsFirstMatches_1005) {
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Multiple forbidden patterns - second matches (should fail)
TEST_F(TestSpecFilterTest_1005, MultipleForbiddenPatternsSecondMatches_1005) {
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Multiple forbidden patterns - none match
TEST_F(TestSpecFilterTest_1005, MultipleForbiddenPatternsNoneMatch_1005) {
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Required matches but forbidden also matches - forbidden takes precedence
TEST_F(TestSpecFilterTest_1005, RequiredMatchesForbiddenAlsoMatches_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Required matches, forbidden does not match
TEST_F(TestSpecFilterTest_1005, RequiredMatchesForbiddenDoesNot_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Required does not match, forbidden does not match - should return false (required blocks)
TEST_F(TestSpecFilterTest_1005, RequiredDoesNotMatchForbiddenDoesNot_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(false));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("SomeTest");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: Hidden test with required matching and forbidden not matching
TEST_F(TestSpecFilterTest_1005, HiddenTestRequiredMatchForbiddenNoMatch_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(false));
    auto tc = makeTestCaseInfo("HiddenTest", "[.]");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Hidden test with required matching and forbidden matching
TEST_F(TestSpecFilterTest_1005, HiddenTestRequiredAndForbiddenBothMatch_1005) {
    filter.m_required.push_back(Detail::make_unique<MockPattern>(true));
    filter.m_forbidden.push_back(Detail::make_unique<MockPattern>(true));
    auto tc = makeTestCaseInfo("HiddenTest", "[.]");
    EXPECT_FALSE(filter.matches(tc));
}

// Test: No patterns, non-hidden test with tags
TEST_F(TestSpecFilterTest_1005, EmptyFilterNonHiddenWithTags_1005) {
    auto tc = makeTestCaseInfo("TaggedTest", "[some_tag]");
    EXPECT_TRUE(filter.matches(tc));
}

// Test: Test tagged with [!hide] which is another way to be hidden
TEST_F(TestSpecFilterTest_1005, EmptyFilterWithInternalHiddenTag_1005) {
    auto tc = makeTestCaseInfo("HiddenTest2", "[.hidden]");
    // Tags starting with . are hidden
    EXPECT_FALSE(filter.matches(tc));
}
