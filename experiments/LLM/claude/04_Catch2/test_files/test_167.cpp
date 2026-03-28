#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <type_traits>

// We need to include the actual header for the class under test
#include "catch2/matchers/catch_matchers_templated.hpp"

// Since we're testing Catch2's internal matchers, we need to create a simple
// mock matcher that satisfies the interface expected by MatchNotOfGeneric.

namespace {

// A simple matcher that matches when value equals the stored value
template <typename T>
class SimpleMatcher : public Catch::Matchers::MatcherGenericBase {
    T m_value;
    bool m_matchResult;
public:
    explicit SimpleMatcher(T value, bool matchResult = true)
        : m_value(std::move(value)), m_matchResult(matchResult) {}

    template <typename Arg>
    bool match(Arg&& arg) const {
        return m_matchResult;
    }

    std::string describe() const override {
        return "SimpleMatcher";
    }
};

// A matcher that always returns true
class AlwaysTrueMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename Arg>
    bool match(Arg&&) const {
        return true;
    }

    std::string describe() const override {
        return "always true";
    }
};

// A matcher that always returns false
class AlwaysFalseMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename Arg>
    bool match(Arg&&) const {
        return false;
    }

    std::string describe() const override {
        return "always false";
    }
};

// A matcher with a complex description
class ComplexDescriptionMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename Arg>
    bool match(Arg&&) const {
        return true;
    }

    std::string describe() const override {
        return "matches (value > 5 and value < 10)";
    }
};

} // anonymous namespace

class MatchNotOfGenericTest_167 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that MatchNotOfGeneric negates a matcher that returns true
TEST_F(MatchNotOfGenericTest_167, NegatesTrueMatcherToFalse_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    // The negation of a true-matching matcher should return false
    EXPECT_FALSE(notMatcher.match(42));
    EXPECT_FALSE(notMatcher.match(std::string("hello")));
    EXPECT_FALSE(notMatcher.match(0));
}

// Test that MatchNotOfGeneric negates a matcher that returns false
TEST_F(MatchNotOfGenericTest_167, NegatesFalseMatcherToTrue_167) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    
    // The negation of a false-matching matcher should return true
    EXPECT_TRUE(notMatcher.match(42));
    EXPECT_TRUE(notMatcher.match(std::string("hello")));
    EXPECT_TRUE(notMatcher.match(0));
}

// Test that describe() prepends "not " to the inner matcher's description
TEST_F(MatchNotOfGenericTest_167, DescribePrependsNot_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    std::string description = notMatcher.describe();
    // The description should start with "not "
    EXPECT_THAT(description, ::testing::StartsWith("not "));
}

// Test that describe includes the inner matcher's description
TEST_F(MatchNotOfGenericTest_167, DescribeIncludesInnerDescription_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    std::string description = notMatcher.describe();
    // Should contain the inner matcher's description
    EXPECT_THAT(description, ::testing::HasSubstr("always true"));
}

// Test describe with a complex description matcher
TEST_F(MatchNotOfGenericTest_167, DescribeWithComplexInnerDescription_167) {
    ComplexDescriptionMatcher complexMatcher;
    auto notMatcher = !complexMatcher;
    
    std::string description = notMatcher.describe();
    EXPECT_THAT(description, ::testing::HasSubstr("matches (value > 5 and value < 10)"));
    EXPECT_THAT(description, ::testing::StartsWith("not "));
}

// Test that MatchNotOfGeneric works with different argument types
TEST_F(MatchNotOfGenericTest_167, WorksWithDifferentArgTypes_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    // Test with int
    EXPECT_FALSE(notMatcher.match(42));
    
    // Test with string
    EXPECT_FALSE(notMatcher.match(std::string("test")));
    
    // Test with double
    EXPECT_FALSE(notMatcher.match(3.14));
    
    // Test with bool
    EXPECT_FALSE(notMatcher.match(true));
}

// Test that MatchNotOfGeneric can be move-constructed
TEST_F(MatchNotOfGenericTest_167, IsMoveConstructible_167) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    auto movedMatcher = std::move(notMatcher);
    
    // The moved-to matcher should still work correctly
    EXPECT_TRUE(movedMatcher.match(42));
}

// Test double negation (not not)
TEST_F(MatchNotOfGenericTest_167, DoubleNegation_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    auto doubleNotMatcher = !notMatcher;
    
    // Double negation should return to original behavior
    EXPECT_TRUE(doubleNotMatcher.match(42));
}

// Test double negation with false matcher
TEST_F(MatchNotOfGenericTest_167, DoubleNegationFalse_167) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    auto doubleNotMatcher = !notMatcher;
    
    // Double negation of false should still be false
    EXPECT_FALSE(doubleNotMatcher.match(42));
}

// Test with AlwaysFalseMatcher describe
TEST_F(MatchNotOfGenericTest_167, DescribeWithFalseMatcher_167) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    
    std::string description = notMatcher.describe();
    EXPECT_THAT(description, ::testing::StartsWith("not "));
    EXPECT_THAT(description, ::testing::HasSubstr("always false"));
}

// Test that match works with const references
TEST_F(MatchNotOfGenericTest_167, MatchWithConstRef_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    const int value = 42;
    EXPECT_FALSE(notMatcher.match(value));
}

// Test that match works with rvalue references
TEST_F(MatchNotOfGenericTest_167, MatchWithRvalueRef_167) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    
    EXPECT_TRUE(notMatcher.match(std::string("temporary")));
}

// Test with empty string as argument
TEST_F(MatchNotOfGenericTest_167, MatchWithEmptyString_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    EXPECT_FALSE(notMatcher.match(std::string("")));
}

// Test boundary: zero value
TEST_F(MatchNotOfGenericTest_167, MatchWithZero_167) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    
    EXPECT_TRUE(notMatcher.match(0));
}

// Test boundary: negative value
TEST_F(MatchNotOfGenericTest_167, MatchWithNegativeValue_167) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    
    EXPECT_TRUE(notMatcher.match(-1));
}

// Test boundary: max int
TEST_F(MatchNotOfGenericTest_167, MatchWithMaxInt_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    EXPECT_FALSE(notMatcher.match(std::numeric_limits<int>::max()));
}

// Test boundary: min int
TEST_F(MatchNotOfGenericTest_167, MatchWithMinInt_167) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    EXPECT_FALSE(notMatcher.match(std::numeric_limits<int>::min()));
}
