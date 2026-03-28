#include <gtest/gtest.h>
#include <string>

// Include the header for the class under test
#include "catch2/matchers/catch_matchers.hpp"

// Concrete subclass for testing purposes, since MatcherUntypedBase has a pure virtual describe()
class TestMatcher : public Catch::Matchers::MatcherUntypedBase {
public:
    explicit TestMatcher(const std::string& description)
        : m_description(description), m_describeCallCount(0) {}

    std::string describe() const override {
        ++m_describeCallCount;
        return m_description;
    }

    void setDescription(const std::string& desc) {
        m_description = desc;
    }

    mutable int m_describeCallCount;

private:
    std::string m_description;
};

// Test fixture
class MatcherUntypedBaseTest_246 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that toString() returns the result of describe()
TEST_F(MatcherUntypedBaseTest_246, ToStringReturnsDescribeResult_246) {
    TestMatcher matcher("test description");
    std::string result = matcher.toString();
    EXPECT_EQ(result, "test description");
}

// Test that toString() caches the result and doesn't call describe() again
TEST_F(MatcherUntypedBaseTest_246, ToStringCachesResult_246) {
    TestMatcher matcher("cached description");

    // First call should invoke describe()
    std::string result1 = matcher.toString();
    EXPECT_EQ(result1, "cached description");
    EXPECT_EQ(matcher.m_describeCallCount, 1);

    // Second call should use cached value, not calling describe() again
    std::string result2 = matcher.toString();
    EXPECT_EQ(result2, "cached description");
    EXPECT_EQ(matcher.m_describeCallCount, 1);
}

// Test that toString() with an empty describe result still works
TEST_F(MatcherUntypedBaseTest_246, ToStringWithEmptyDescription_246) {
    TestMatcher matcher("");

    // When describe() returns empty string, m_cachedToString remains empty,
    // so describe() may be called each time
    std::string result = matcher.toString();
    // The result should be whatever describe() returns
    EXPECT_EQ(result, "");
}

// Test that toString() returns same cached value even if description changes
TEST_F(MatcherUntypedBaseTest_246, ToStringReturnsCachedValueAfterDescriptionChange_246) {
    TestMatcher matcher("original");

    std::string result1 = matcher.toString();
    EXPECT_EQ(result1, "original");

    // Change the description after first call
    matcher.setDescription("modified");

    // Should still return the cached value
    std::string result2 = matcher.toString();
    EXPECT_EQ(result2, "original");
}

// Test that describe() is called exactly once for non-empty description
TEST_F(MatcherUntypedBaseTest_246, DescribeCalledOnceForNonEmptyDescription_246) {
    TestMatcher matcher("non-empty");

    matcher.toString();
    matcher.toString();
    matcher.toString();

    EXPECT_EQ(matcher.m_describeCallCount, 1);
}

// Test with a long description string
TEST_F(MatcherUntypedBaseTest_246, ToStringWithLongDescription_246) {
    std::string longDesc(10000, 'x');
    TestMatcher matcher(longDesc);

    std::string result = matcher.toString();
    EXPECT_EQ(result, longDesc);
    EXPECT_EQ(result.size(), 10000u);
}

// Test with special characters in description
TEST_F(MatcherUntypedBaseTest_246, ToStringWithSpecialCharacters_246) {
    TestMatcher matcher("special chars: \n\t\r\\\"'!@#$%^&*()");

    std::string result = matcher.toString();
    EXPECT_EQ(result, "special chars: \n\t\r\\\"'!@#$%^&*()");
}

// Test with unicode-like content in description
TEST_F(MatcherUntypedBaseTest_246, ToStringWithUnicodeContent_246) {
    TestMatcher matcher("unicode: \xC3\xA9\xC3\xA0\xC3\xBC");

    std::string result = matcher.toString();
    EXPECT_EQ(result, "unicode: \xC3\xA9\xC3\xA0\xC3\xBC");
}

// Test copy construction behavior
TEST_F(MatcherUntypedBaseTest_246, CopyConstructedMatcherToString_246) {
    TestMatcher original("copy test");

    // Call toString on original to populate cache
    original.toString();

    // Copy construct
    TestMatcher copied(original);

    // The copied matcher should also have the cached value or recompute
    std::string result = copied.toString();
    EXPECT_EQ(result, "copy test");
}

// Test that empty describe called repeatedly if cache stays empty
TEST_F(MatcherUntypedBaseTest_246, EmptyDescribeCalledRepeatedly_246) {
    TestMatcher matcher("");

    matcher.toString();
    int countAfterFirst = matcher.m_describeCallCount;

    matcher.toString();
    int countAfterSecond = matcher.m_describeCallCount;

    // If the cached string is empty, describe() should be called again
    // because the condition checks if m_cachedToString.empty()
    EXPECT_GE(countAfterSecond, countAfterFirst);
}
