#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// We need to include the actual header
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// A simple generic matcher for testing purposes
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename Arg>
    bool match(Arg&&) const {
        return true;
    }
    std::string describe() const override {
        return "always true";
    }
};

struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename Arg>
    bool match(Arg&&) const {
        return false;
    }
    std::string describe() const override {
        return "always false";
    }
};

struct EqualsMatcher : Catch::Matchers::MatcherGenericBase {
    int value;
    explicit EqualsMatcher(int v) : value(v) {}
    
    template<typename Arg>
    bool match(Arg&& arg) const {
        return arg == value;
    }
    std::string describe() const override {
        return "equals " + std::to_string(value);
    }
};

struct StringContainsMatcher : Catch::Matchers::MatcherGenericBase {
    std::string substring;
    explicit StringContainsMatcher(std::string s) : substring(std::move(s)) {}
    
    template<typename Arg>
    bool match(Arg&& arg) const {
        return std::string(arg).find(substring) != std::string::npos;
    }
    std::string describe() const override {
        return "contains \"" + substring + "\"";
    }
};

// Test fixture
class MatchNotOfGenericTest_166 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that negating an always-true matcher returns false
TEST_F(MatchNotOfGenericTest_166, NegateAlwaysTrueReturnsFalse_166) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    EXPECT_FALSE(notMatcher.match(42));
    EXPECT_FALSE(notMatcher.match(0));
    EXPECT_FALSE(notMatcher.match(-1));
}

// Test that negating an always-false matcher returns true
TEST_F(MatchNotOfGenericTest_166, NegateAlwaysFalseReturnsTrue_166) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    
    EXPECT_TRUE(notMatcher.match(42));
    EXPECT_TRUE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(-1));
}

// Test negation of equality matcher - matching value
TEST_F(MatchNotOfGenericTest_166, NegateEqualsMatcherWithMatchingValue_166) {
    EqualsMatcher equalsFive(5);
    auto notMatcher = !equalsFive;
    
    // 5 matches EqualsMatcher(5), so negation should be false
    EXPECT_FALSE(notMatcher.match(5));
}

// Test negation of equality matcher - non-matching value
TEST_F(MatchNotOfGenericTest_166, NegateEqualsMatcherWithNonMatchingValue_166) {
    EqualsMatcher equalsFive(5);
    auto notMatcher = !equalsFive;
    
    // 3 does not match EqualsMatcher(5), so negation should be true
    EXPECT_TRUE(notMatcher.match(3));
    EXPECT_TRUE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(-5));
}

// Test negation with string type argument
TEST_F(MatchNotOfGenericTest_166, NegateStringMatcherContainsSubstring_166) {
    StringContainsMatcher containsHello("hello");
    auto notMatcher = !containsHello;
    
    EXPECT_FALSE(notMatcher.match(std::string("hello world")));
    EXPECT_TRUE(notMatcher.match(std::string("goodbye world")));
}

// Test that describe works on negated matcher
TEST_F(MatchNotOfGenericTest_166, DescribeReturnsNonEmptyString_166) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    std::string description = notMatcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test describe contains negation indication
TEST_F(MatchNotOfGenericTest_166, DescribeContainsNot_166) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    
    std::string description = notMatcher.describe();
    // The description should contain "not" to indicate negation
    EXPECT_NE(description.find("not"), std::string::npos);
}

// Test with boundary value - zero
TEST_F(MatchNotOfGenericTest_166, BoundaryValueZero_166) {
    EqualsMatcher equalsZero(0);
    auto notMatcher = !equalsZero;
    
    EXPECT_FALSE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(1));
    EXPECT_TRUE(notMatcher.match(-1));
}

// Test with rvalue argument
TEST_F(MatchNotOfGenericTest_166, MatchWithRvalue_166) {
    EqualsMatcher equalsTen(10);
    auto notMatcher = !equalsTen;
    
    EXPECT_FALSE(notMatcher.match(10));
    EXPECT_TRUE(notMatcher.match(11));
}

// Test with lvalue argument
TEST_F(MatchNotOfGenericTest_166, MatchWithLvalue_166) {
    EqualsMatcher equalsTen(10);
    auto notMatcher = !equalsTen;
    
    int val = 10;
    EXPECT_FALSE(notMatcher.match(val));
    
    val = 20;
    EXPECT_TRUE(notMatcher.match(val));
}

// Test with const lvalue argument
TEST_F(MatchNotOfGenericTest_166, MatchWithConstLvalue_166) {
    EqualsMatcher equalsTen(10);
    auto notMatcher = !equalsTen;
    
    const int val = 10;
    EXPECT_FALSE(notMatcher.match(val));
    
    const int val2 = 20;
    EXPECT_TRUE(notMatcher.match(val2));
}

// Test double negation
TEST_F(MatchNotOfGenericTest_166, DoubleNegation_166) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    auto doubleNotMatcher = !notMatcher;
    
    // Double negation should restore original behavior
    EXPECT_TRUE(doubleNotMatcher.match(42));
}

// Test double negation with always false
TEST_F(MatchNotOfGenericTest_166, DoubleNegationAlwaysFalse_166) {
    AlwaysFalseMatcher falseMatcher;
    auto notMatcher = !falseMatcher;
    auto doubleNotMatcher = !notMatcher;
    
    // Double negation should restore original behavior (false)
    EXPECT_FALSE(doubleNotMatcher.match(42));
}

// Test negation with empty string
TEST_F(MatchNotOfGenericTest_166, NegateStringMatcherEmptyString_166) {
    StringContainsMatcher containsHello("hello");
    auto notMatcher = !containsHello;
    
    // Empty string does not contain "hello", so negation should be true
    EXPECT_TRUE(notMatcher.match(std::string("")));
}

// Test negation with exact match substring
TEST_F(MatchNotOfGenericTest_166, NegateStringMatcherExactMatch_166) {
    StringContainsMatcher containsHello("hello");
    auto notMatcher = !containsHello;
    
    // Exact match - contains "hello", so negation should be false
    EXPECT_FALSE(notMatcher.match(std::string("hello")));
}

// Test that MatchNotOfGeneric is move constructible
TEST_F(MatchNotOfGenericTest_166, MoveConstructible_166) {
    AlwaysTrueMatcher trueMatcher;
    auto notMatcher = !trueMatcher;
    auto movedMatcher = std::move(notMatcher);
    
    EXPECT_FALSE(movedMatcher.match(42));
}
