#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the header under test
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// A simple concrete matcher for testing purposes
template <typename T>
class AlwaysTrueMatcher : public MatcherBase<T> {
public:
    bool match(T const&) const override { return true; }
    std::string describe() const override { return "always true"; }
};

template <typename T>
class AlwaysFalseMatcher : public MatcherBase<T> {
public:
    bool match(T const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

template <typename T>
class EqualsMatcher : public MatcherBase<T> {
    T m_expected;
public:
    explicit EqualsMatcher(T expected) : m_expected(std::move(expected)) {}
    bool match(T const& arg) const override { return arg == m_expected; }
    std::string describe() const override { return "equals " + std::to_string(m_expected); }
};

// Specialization for string
template <>
class EqualsMatcher<std::string> : public MatcherBase<std::string> {
    std::string m_expected;
public:
    explicit EqualsMatcher(std::string expected) : m_expected(std::move(expected)) {}
    bool match(std::string const& arg) const override { return arg == m_expected; }
    std::string describe() const override { return "equals \"" + m_expected + "\""; }
};

// Test fixture
class MatchAllOfOperatorAndTest_138 : public ::testing::Test {
protected:
    AlwaysTrueMatcher<int> trueMatcher1;
    AlwaysTrueMatcher<int> trueMatcher2;
    AlwaysTrueMatcher<int> trueMatcher3;
    AlwaysFalseMatcher<int> falseMatcher1;
    AlwaysFalseMatcher<int> falseMatcher2;
};

// Test: operator&& with lhs MatcherBase and rhs MatchAllOf prepends the lhs matcher
TEST_F(MatchAllOfOperatorAndTest_138, LhsMatcherBaseAndRhsMatchAllOf_PrependsMatcher_138) {
    // Create MatchAllOf with trueMatcher2 using trueMatcher1 && trueMatcher2
    auto combined = trueMatcher1 && trueMatcher2;
    // Now use operator&&(MatcherBase const&, MatchAllOf&&) by combining with trueMatcher3
    // trueMatcher3 && (trueMatcher1 && trueMatcher2) should work via the friend function
    // But actually the first && creates a MatchAllOf, and then we can chain
    // Let's test: lhs (MatcherBase) && rhs (MatchAllOf&&)
    auto result = trueMatcher3 && std::move(combined);
    
    // All are true matchers, so matching any int should return true
    EXPECT_TRUE(result.match(42));
}

TEST_F(MatchAllOfOperatorAndTest_138, AllTrueMatchersMatch_138) {
    auto combined = trueMatcher1 && trueMatcher2;
    auto result = trueMatcher3 && std::move(combined);
    
    EXPECT_TRUE(result.match(0));
    EXPECT_TRUE(result.match(-1));
    EXPECT_TRUE(result.match(100));
}

TEST_F(MatchAllOfOperatorAndTest_138, OneFalseMatcherCausesNoMatch_138) {
    auto combined = trueMatcher1 && falseMatcher1;
    // This creates a MatchAllOf with trueMatcher1 and falseMatcher1
    // One is false, so match should fail
    EXPECT_FALSE(combined.match(42));
}

TEST_F(MatchAllOfOperatorAndTest_138, PrependFalseMatcherCausesNoMatch_138) {
    auto combined = trueMatcher1 && trueMatcher2;
    auto result = falseMatcher1 && std::move(combined);
    
    EXPECT_FALSE(result.match(42));
}

TEST_F(MatchAllOfOperatorAndTest_138, AllFalseMatchersNoMatch_138) {
    auto combined = falseMatcher1 && falseMatcher2;
    EXPECT_FALSE(combined.match(42));
}

TEST_F(MatchAllOfOperatorAndTest_138, DescribeReturnsNonEmptyString_138) {
    auto combined = trueMatcher1 && trueMatcher2;
    auto result = trueMatcher3 && std::move(combined);
    
    std::string description = result.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(MatchAllOfOperatorAndTest_138, DescribeContainsSubMatchers_138) {
    auto combined = trueMatcher1 && falseMatcher1;
    std::string description = combined.describe();
    
    // The description should contain information about sub-matchers
    EXPECT_FALSE(description.empty());
    // Should contain "always true" and "always false" in some form
    EXPECT_NE(description.find("always true"), std::string::npos);
    EXPECT_NE(description.find("always false"), std::string::npos);
}

TEST_F(MatchAllOfOperatorAndTest_138, PrependedMatcherAppearsInDescription_138) {
    auto combined = trueMatcher1 && trueMatcher2;
    auto result = falseMatcher1 && std::move(combined);
    
    std::string description = result.describe();
    // Should contain "always false" since we prepended a false matcher
    EXPECT_NE(description.find("always false"), std::string::npos);
    EXPECT_NE(description.find("always true"), std::string::npos);
}

// Test with different types (string)
TEST(MatchAllOfStringTest_138, StringMatchersCanBeCombined_138) {
    AlwaysTrueMatcher<std::string> strTrue1;
    AlwaysTrueMatcher<std::string> strTrue2;
    
    auto combined = strTrue1 && strTrue2;
    EXPECT_TRUE(combined.match("hello"));
}

TEST(MatchAllOfStringTest_138, StringMatcherPrependWorks_138) {
    AlwaysTrueMatcher<std::string> strTrue1;
    AlwaysTrueMatcher<std::string> strTrue2;
    AlwaysFalseMatcher<std::string> strFalse;
    
    auto combined = strTrue1 && strTrue2;
    auto result = strFalse && std::move(combined);
    
    EXPECT_FALSE(result.match("hello"));
}

// Test chaining multiple prepends
TEST_F(MatchAllOfOperatorAndTest_138, MultipleChainingWorks_138) {
    // trueMatcher1 && trueMatcher2 creates MatchAllOf
    // then trueMatcher3 && MatchAllOf prepends trueMatcher3
    auto step1 = trueMatcher1 && trueMatcher2;
    auto step2 = trueMatcher3 && std::move(step1);
    
    // All true, should match
    EXPECT_TRUE(step2.match(99));
}

TEST_F(MatchAllOfOperatorAndTest_138, ChainingWithFalseAtBeginning_138) {
    auto step1 = trueMatcher1 && trueMatcher2;
    auto step2 = falseMatcher1 && std::move(step1);
    
    // False matcher prepended, should not match
    EXPECT_FALSE(step2.match(99));
}

// Test boundary: matching with value 0
TEST_F(MatchAllOfOperatorAndTest_138, MatchWithZero_138) {
    auto combined = trueMatcher1 && trueMatcher2;
    auto result = trueMatcher3 && std::move(combined);
    EXPECT_TRUE(result.match(0));
}

// Test boundary: matching with negative value
TEST_F(MatchAllOfOperatorAndTest_138, MatchWithNegativeValue_138) {
    auto combined = trueMatcher1 && trueMatcher2;
    auto result = trueMatcher3 && std::move(combined);
    EXPECT_TRUE(result.match(-999));
}

// Test with specific value matchers
TEST(MatchAllOfEqualsTest_138, TwoEqualsMatchersBothSatisfied_138) {
    EqualsMatcher<int> eq5(5);
    AlwaysTrueMatcher<int> trueM;
    
    auto combined = eq5 && trueM;
    EXPECT_TRUE(combined.match(5));
    EXPECT_FALSE(combined.match(6));
}

TEST(MatchAllOfEqualsTest_138, PrependEqualsMatcherSatisfied_138) {
    AlwaysTrueMatcher<int> trueM1;
    AlwaysTrueMatcher<int> trueM2;
    EqualsMatcher<int> eq5(5);
    
    auto combined = trueM1 && trueM2;
    auto result = eq5 && std::move(combined);
    
    EXPECT_TRUE(result.match(5));
    EXPECT_FALSE(result.match(3));
}

TEST(MatchAllOfEqualsTest_138, PrependEqualsMatcherNotSatisfied_138) {
    AlwaysTrueMatcher<int> trueM1;
    AlwaysTrueMatcher<int> trueM2;
    EqualsMatcher<int> eq5(5);
    
    auto combined = trueM1 && trueM2;
    auto result = eq5 && std::move(combined);
    
    EXPECT_FALSE(result.match(10));
}
