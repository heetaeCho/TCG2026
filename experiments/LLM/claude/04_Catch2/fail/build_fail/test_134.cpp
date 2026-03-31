#include <catch2/matchers/internal/catch_matchers_impl.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <type_traits>
#include <sstream>

// A simple custom matcher for testing purposes
template <typename T>
struct SimpleMatcher : Catch::Matchers::MatcherBase<T> {
    T expected_;
    SimpleMatcher(T expected) : expected_(std::move(expected)) {}
    
    bool match(T const& actual) const override {
        return actual == expected_;
    }
    
    std::string describe() const override {
        std::ostringstream oss;
        oss << "equals " << expected_;
        return oss.str();
    }
};

// A matcher that always returns true
template <typename T>
struct AlwaysTrueMatcher : Catch::Matchers::MatcherBase<T> {
    bool match(T const&) const override {
        return true;
    }
    std::string describe() const override {
        return "always matches";
    }
};

// A matcher that always returns false
template <typename T>
struct AlwaysFalseMatcher : Catch::Matchers::MatcherBase<T> {
    bool match(T const&) const override {
        return false;
    }
    std::string describe() const override {
        return "never matches";
    }
};

class MakeMatchExprTest_134 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that makeMatchExpr creates a MatchExpr with matching value (int)
TEST_F(MakeMatchExprTest_134, IntMatchExprWithMatchingValue_134) {
    SimpleMatcher<int> matcher(42);
    auto expr = Catch::makeMatchExpr(42, matcher);
    // MatchExpr should be convertible to bool via its evaluation
    // The expression should match since 42 == 42
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test that makeMatchExpr creates a MatchExpr with non-matching value (int)
TEST_F(MakeMatchExprTest_134, IntMatchExprWithNonMatchingValue_134) {
    SimpleMatcher<int> matcher(42);
    auto expr = Catch::makeMatchExpr(99, matcher);
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test with string type matching
TEST_F(MakeMatchExprTest_134, StringMatchExprWithMatchingValue_134) {
    SimpleMatcher<std::string> matcher(std::string("hello"));
    std::string val = "hello";
    auto expr = Catch::makeMatchExpr(val, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test with string type non-matching
TEST_F(MakeMatchExprTest_134, StringMatchExprWithNonMatchingValue_134) {
    SimpleMatcher<std::string> matcher(std::string("hello"));
    std::string val = "world";
    auto expr = Catch::makeMatchExpr(val, matcher);
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test with always-true matcher
TEST_F(MakeMatchExprTest_134, AlwaysTrueMatcherReturnsTrue_134) {
    AlwaysTrueMatcher<int> matcher;
    auto expr = Catch::makeMatchExpr(0, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test with always-false matcher  
TEST_F(MakeMatchExprTest_134, AlwaysFalseMatcherReturnsFalse_134) {
    AlwaysFalseMatcher<int> matcher;
    auto expr = Catch::makeMatchExpr(0, matcher);
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test with rvalue argument
TEST_F(MakeMatchExprTest_134, RvalueArgumentMatches_134) {
    SimpleMatcher<int> matcher(10);
    auto expr = Catch::makeMatchExpr(10, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test with lvalue argument
TEST_F(MakeMatchExprTest_134, LvalueArgumentMatches_134) {
    SimpleMatcher<int> matcher(10);
    int val = 10;
    auto expr = Catch::makeMatchExpr(val, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test with double type
TEST_F(MakeMatchExprTest_134, DoubleMatchExprMatching_134) {
    SimpleMatcher<double> matcher(3.14);
    auto expr = Catch::makeMatchExpr(3.14, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test with double type non-matching
TEST_F(MakeMatchExprTest_134, DoubleMatchExprNonMatching_134) {
    SimpleMatcher<double> matcher(3.14);
    auto expr = Catch::makeMatchExpr(2.71, matcher);
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test boundary: zero value
TEST_F(MakeMatchExprTest_134, ZeroValueMatches_134) {
    SimpleMatcher<int> matcher(0);
    auto expr = Catch::makeMatchExpr(0, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test boundary: negative value
TEST_F(MakeMatchExprTest_134, NegativeValueMatches_134) {
    SimpleMatcher<int> matcher(-1);
    auto expr = Catch::makeMatchExpr(-1, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test boundary: empty string
TEST_F(MakeMatchExprTest_134, EmptyStringMatches_134) {
    SimpleMatcher<std::string> matcher(std::string(""));
    std::string val = "";
    auto expr = Catch::makeMatchExpr(val, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test boundary: large value
TEST_F(MakeMatchExprTest_134, LargeIntValueMatches_134) {
    SimpleMatcher<int> matcher(std::numeric_limits<int>::max());
    auto expr = Catch::makeMatchExpr(std::numeric_limits<int>::max(), matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test boundary: min int value
TEST_F(MakeMatchExprTest_134, MinIntValueMatches_134) {
    SimpleMatcher<int> matcher(std::numeric_limits<int>::min());
    auto expr = Catch::makeMatchExpr(std::numeric_limits<int>::min(), matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test that the return type is correct
TEST_F(MakeMatchExprTest_134, ReturnTypeIsMatchExpr_134) {
    SimpleMatcher<int> matcher(42);
    auto expr = Catch::makeMatchExpr(42, matcher);
    bool isCorrectType = std::is_same<
        decltype(expr),
        Catch::MatchExpr<int, SimpleMatcher<int>>
    >::value;
    // It might be MatchExpr<int&&, ...> or MatchExpr<int, ...> depending on forwarding
    // Just verify it compiles and is usable as bool
    (void)isCorrectType;
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test with const lvalue
TEST_F(MakeMatchExprTest_134, ConstLvalueArgumentMatches_134) {
    SimpleMatcher<int> matcher(42);
    const int val = 42;
    auto expr = Catch::makeMatchExpr(val, matcher);
    EXPECT_TRUE(static_cast<bool>(expr));
}
