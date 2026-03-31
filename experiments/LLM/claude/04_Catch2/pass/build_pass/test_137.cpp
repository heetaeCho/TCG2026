#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the header under test
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// A simple concrete matcher for testing purposes
template <typename T>
class EqualsMatcher : public MatcherBase<T> {
    T m_expected;
public:
    explicit EqualsMatcher(T expected) : m_expected(std::move(expected)) {}
    
    bool match(T const& arg) const override {
        return arg == m_expected;
    }
    
    std::string describe() const override {
        return "equals expected value";
    }
};

// A matcher that always returns true
template <typename T>
class AlwaysTrueMatcher : public MatcherBase<T> {
public:
    bool match(T const&) const override {
        return true;
    }
    
    std::string describe() const override {
        return "always true";
    }
};

// A matcher that always returns false
template <typename T>
class AlwaysFalseMatcher : public MatcherBase<T> {
public:
    bool match(T const&) const override {
        return false;
    }
    
    std::string describe() const override {
        return "always false";
    }
};

class MatchAllOfTest_137 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that combining two matchers via && produces a MatchAllOf that matches when both match
TEST_F(MatchAllOfTest_137, CombineTwoTrueMatchersMatchesTrue_137) {
    AlwaysTrueMatcher<int> m1;
    AlwaysTrueMatcher<int> m2;
    
    auto combined = std::move(Detail::MatchAllOf<int>() && m1) && m2;
    // Actually, let's use the friend operator&& properly
    // MatchAllOf is created by combining matchers
    
    EXPECT_TRUE(combined.match(42));
}

// Test that MatchAllOf with one true and one false matcher returns false
TEST_F(MatchAllOfTest_137, CombineTrueAndFalseMatchersReturnsFalse_137) {
    AlwaysTrueMatcher<int> trueM;
    AlwaysFalseMatcher<int> falseM;
    
    auto combined = std::move(Detail::MatchAllOf<int>() && trueM) && falseM;
    
    EXPECT_FALSE(combined.match(42));
}

// Test that MatchAllOf with two false matchers returns false
TEST_F(MatchAllOfTest_137, CombineTwoFalseMatchersReturnsFalse_137) {
    AlwaysFalseMatcher<int> m1;
    AlwaysFalseMatcher<int> m2;
    
    auto combined = std::move(Detail::MatchAllOf<int>() && m1) && m2;
    
    EXPECT_FALSE(combined.match(42));
}

// Test chaining three matchers all true
TEST_F(MatchAllOfTest_137, ChainThreeTrueMatchersReturnsTrue_137) {
    AlwaysTrueMatcher<int> m1;
    AlwaysTrueMatcher<int> m2;
    AlwaysTrueMatcher<int> m3;
    
    auto combined = std::move(std::move(Detail::MatchAllOf<int>() && m1) && m2) && m3;
    
    EXPECT_TRUE(combined.match(100));
}

// Test chaining three matchers where last is false
TEST_F(MatchAllOfTest_137, ChainThreeMatchersLastFalseReturnsFalse_137) {
    AlwaysTrueMatcher<int> m1;
    AlwaysTrueMatcher<int> m2;
    AlwaysFalseMatcher<int> m3;
    
    auto combined = std::move(std::move(Detail::MatchAllOf<int>() && m1) && m2) && m3;
    
    EXPECT_FALSE(combined.match(100));
}

// Test with a single matcher added
TEST_F(MatchAllOfTest_137, SingleTrueMatcherReturnsTrue_137) {
    AlwaysTrueMatcher<int> m1;
    
    auto combined = Detail::MatchAllOf<int>() && m1;
    
    EXPECT_TRUE(combined.match(0));
}

// Test with a single false matcher
TEST_F(MatchAllOfTest_137, SingleFalseMatcherReturnsFalse_137) {
    AlwaysFalseMatcher<int> m1;
    
    auto combined = Detail::MatchAllOf<int>() && m1;
    
    EXPECT_FALSE(combined.match(0));
}

// Test that describe returns a non-empty string
TEST_F(MatchAllOfTest_137, DescribeReturnsNonEmptyString_137) {
    AlwaysTrueMatcher<int> m1;
    AlwaysTrueMatcher<int> m2;
    
    auto combined = std::move(Detail::MatchAllOf<int>() && m1) && m2;
    
    std::string desc = combined.describe();
    EXPECT_FALSE(desc.empty());
}

// Test with string type matchers
TEST_F(MatchAllOfTest_137, WorksWithStringType_137) {
    EqualsMatcher<std::string> m1("hello");
    AlwaysTrueMatcher<std::string> m2;
    
    auto combined = std::move(Detail::MatchAllOf<std::string>() && m1) && m2;
    
    EXPECT_TRUE(combined.match(std::string("hello")));
    EXPECT_FALSE(combined.match(std::string("world")));
}

// Test with string type where both matchers check equality to same value
TEST_F(MatchAllOfTest_137, BothEqualsMatchersSameValue_137) {
    EqualsMatcher<std::string> m1("test");
    EqualsMatcher<std::string> m2("test");
    
    auto combined = std::move(Detail::MatchAllOf<std::string>() && m1) && m2;
    
    EXPECT_TRUE(combined.match(std::string("test")));
}

// Test with string type where matchers check different values - should fail
TEST_F(MatchAllOfTest_137, BothEqualsMatchersDifferentValues_137) {
    EqualsMatcher<std::string> m1("abc");
    EqualsMatcher<std::string> m2("xyz");
    
    auto combined = std::move(Detail::MatchAllOf<std::string>() && m1) && m2;
    
    // Can't match both "abc" and "xyz" at the same time
    EXPECT_FALSE(combined.match(std::string("abc")));
    EXPECT_FALSE(combined.match(std::string("xyz")));
}

// Test with integer equals matchers
TEST_F(MatchAllOfTest_137, IntegerEqualsMatchers_137) {
    EqualsMatcher<int> m1(42);
    AlwaysTrueMatcher<int> m2;
    
    auto combined = std::move(Detail::MatchAllOf<int>() && m1) && m2;
    
    EXPECT_TRUE(combined.match(42));
    EXPECT_FALSE(combined.match(43));
}

// Test boundary: chaining many matchers
TEST_F(MatchAllOfTest_137, ChainManyTrueMatchers_137) {
    AlwaysTrueMatcher<int> m1, m2, m3, m4, m5;
    
    auto combined = std::move(
        std::move(
            std::move(
                std::move(Detail::MatchAllOf<int>() && m1) && m2
            ) && m3
        ) && m4
    ) && m5;
    
    EXPECT_TRUE(combined.match(999));
}

// Test boundary: chaining many matchers with one false in the middle
TEST_F(MatchAllOfTest_137, ChainManyMatchersOneFalseInMiddle_137) {
    AlwaysTrueMatcher<int> m1, m2, m4, m5;
    AlwaysFalseMatcher<int> m3;
    
    auto combined = std::move(
        std::move(
            std::move(
                std::move(Detail::MatchAllOf<int>() && m1) && m2
            ) && m3
        ) && m4
    ) && m5;
    
    EXPECT_FALSE(combined.match(999));
}

// Test that move semantics work properly (object still usable after move construction)
TEST_F(MatchAllOfTest_137, MoveConstructionWorks_137) {
    AlwaysTrueMatcher<int> m1;
    
    auto temp = Detail::MatchAllOf<int>() && m1;
    auto moved = std::move(temp);
    
    EXPECT_TRUE(moved.match(5));
}
