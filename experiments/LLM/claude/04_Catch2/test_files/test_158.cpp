#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include <string>
#include <type_traits>

// Simple custom matchers for testing purposes
struct IsPositiveMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&& val) const {
        return val > 0;
    }
    std::string describe() const override {
        return "is positive";
    }
};

struct IsEvenMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&& val) const {
        return static_cast<int>(val) % 2 == 0;
    }
    std::string describe() const override {
        return "is even";
    }
};

struct IsLessThan100Matcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&& val) const {
        return val < 100;
    }
    std::string describe() const override {
        return "is less than 100";
    }
};

struct IsGreaterThan10Matcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&& val) const {
        return val > 10;
    }
    std::string describe() const override {
        return "is greater than 10";
    }
};

struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&&) const {
        return true;
    }
    std::string describe() const override {
        return "always true";
    }
};

struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&&) const {
        return false;
    }
    std::string describe() const override {
        return "always false";
    }
};

class MatchAllOfGenericTest_158 : public ::testing::Test {
protected:
};

// Test that combining two single-matcher MatchAllOfGeneric objects works for matching case
TEST_F(MatchAllOfGenericTest_158, CombineTwoMatchersAllMatch_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    // 4 is positive and even
    EXPECT_TRUE(combined.match(4));
}

// Test that combined matcher fails when first matcher fails
TEST_F(MatchAllOfGenericTest_158, CombineTwoMatchersFirstFails_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    // -2 is not positive but is even
    EXPECT_FALSE(combined.match(-2));
}

// Test that combined matcher fails when second matcher fails
TEST_F(MatchAllOfGenericTest_158, CombineTwoMatchersSecondFails_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    // 3 is positive but not even
    EXPECT_FALSE(combined.match(3));
}

// Test that combined matcher fails when both matchers fail
TEST_F(MatchAllOfGenericTest_158, CombineTwoMatchersBothFail_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    // -3 is not positive and not even
    EXPECT_FALSE(combined.match(-3));
}

// Test combining already-combined matchers (MatchAllOfGeneric && MatchAllOfGeneric)
TEST_F(MatchAllOfGenericTest_158, CombineMultipleMatchersViaChaining_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{} && IsLessThan100Matcher{};
    // 42 satisfies all three
    EXPECT_TRUE(combined.match(42));
    // 102 is positive and even but not < 100
    EXPECT_FALSE(combined.match(102));
}

// Test combining four matchers
TEST_F(MatchAllOfGenericTest_158, CombineFourMatchersAllPass_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{} && IsLessThan100Matcher{} && IsGreaterThan10Matcher{};
    // 42: positive, even, <100, >10
    EXPECT_TRUE(combined.match(42));
}

// Test combining four matchers where one fails
TEST_F(MatchAllOfGenericTest_158, CombineFourMatchersOneFails_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{} && IsLessThan100Matcher{} && IsGreaterThan10Matcher{};
    // 4: positive, even, <100, but NOT >10
    EXPECT_FALSE(combined.match(4));
}

// Test that describe() returns a non-empty string for combined matchers
TEST_F(MatchAllOfGenericTest_158, DescribeReturnNonEmpty_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test describe contains sub-matcher descriptions
TEST_F(MatchAllOfGenericTest_158, DescribeContainsSubMatcherDescriptions_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    std::string description = combined.describe();
    EXPECT_NE(description.find("is positive"), std::string::npos);
    EXPECT_NE(description.find("is even"), std::string::npos);
}

// Test with AlwaysTrue and AlwaysFalse
TEST_F(MatchAllOfGenericTest_158, AlwaysTrueAndAlwaysFalse_158) {
    auto combined = AlwaysTrueMatcher{} && AlwaysFalseMatcher{};
    EXPECT_FALSE(combined.match(42));
}

// Test with two AlwaysTrue matchers
TEST_F(MatchAllOfGenericTest_158, TwoAlwaysTrueMatchers_158) {
    auto combined = AlwaysTrueMatcher{} && AlwaysTrueMatcher{};
    EXPECT_TRUE(combined.match(42));
}

// Test with two AlwaysFalse matchers
TEST_F(MatchAllOfGenericTest_158, TwoAlwaysFalseMatchers_158) {
    auto combined = AlwaysFalseMatcher{} && AlwaysFalseMatcher{};
    EXPECT_FALSE(combined.match(42));
}

// Test that combined matcher works with different argument types
TEST_F(MatchAllOfGenericTest_158, MatchWithDoubleType_158) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{};
    EXPECT_TRUE(combined.match(50.5));
    EXPECT_FALSE(combined.match(-1.0));
    EXPECT_FALSE(combined.match(200.0));
}

// Test boundary: zero value
TEST_F(MatchAllOfGenericTest_158, BoundaryZeroValue_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    // 0 is not positive (> 0 fails), but is even
    EXPECT_FALSE(combined.match(0));
}

// Test boundary: value exactly at boundary of IsLessThan100
TEST_F(MatchAllOfGenericTest_158, BoundaryExactly100_158) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{};
    // 100 is positive but not < 100
    EXPECT_FALSE(combined.match(100));
    // 99 is positive and < 100
    EXPECT_TRUE(combined.match(99));
}

// Test chaining describe for three matchers
TEST_F(MatchAllOfGenericTest_158, DescribeThreeMatchers_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{} && IsLessThan100Matcher{};
    std::string description = combined.describe();
    EXPECT_NE(description.find("is positive"), std::string::npos);
    EXPECT_NE(description.find("is even"), std::string::npos);
    EXPECT_NE(description.find("is less than 100"), std::string::npos);
}

// Test that move semantics work (combined matcher is usable after move construction)
TEST_F(MatchAllOfGenericTest_158, MoveConstructedMatcherWorks_158) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    auto moved = std::move(combined);
    EXPECT_TRUE(moved.match(4));
    EXPECT_FALSE(moved.match(-1));
}
