#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the Catch2 matchers header
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need to create some simple matchers for testing purposes
// These are concrete matchers that implement the MatcherGenericBase interface

namespace {

// A simple matcher that checks if an int is greater than a threshold
struct GreaterThanMatcher : Catch::Matchers::MatcherGenericBase {
    int threshold;
    explicit GreaterThanMatcher(int t) : threshold(t) {}
    
    bool match(int const& val) const {
        return val > threshold;
    }
    
    std::string describe() const override {
        return "is greater than " + std::to_string(threshold);
    }
};

// A simple matcher that checks if an int is less than a threshold
struct LessThanMatcher : Catch::Matchers::MatcherGenericBase {
    int threshold;
    explicit LessThanMatcher(int t) : threshold(t) {}
    
    bool match(int const& val) const {
        return val < threshold;
    }
    
    std::string describe() const override {
        return "is less than " + std::to_string(threshold);
    }
};

// A matcher that checks if value is even
struct IsEvenMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int const& val) const {
        return val % 2 == 0;
    }
    
    std::string describe() const override {
        return "is even";
    }
};

// A matcher that checks if value is positive
struct IsPositiveMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int const& val) const {
        return val > 0;
    }
    
    std::string describe() const override {
        return "is positive";
    }
};

// A string contains matcher
struct StringContainsMatcher : Catch::Matchers::MatcherGenericBase {
    std::string substring;
    explicit StringContainsMatcher(std::string s) : substring(std::move(s)) {}
    
    bool match(std::string const& val) const {
        return val.find(substring) != std::string::npos;
    }
    
    std::string describe() const override {
        return "contains \"" + substring + "\"";
    }
};

// A string starts with matcher
struct StringStartsWithMatcher : Catch::Matchers::MatcherGenericBase {
    std::string prefix;
    explicit StringStartsWithMatcher(std::string s) : prefix(std::move(s)) {}
    
    bool match(std::string const& val) const {
        return val.substr(0, prefix.size()) == prefix;
    }
    
    std::string describe() const override {
        return "starts with \"" + prefix + "\"";
    }
};

} // anonymous namespace

class MatchAllOfGenericTest_159 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that combining two matchers with && produces a combined matcher that matches when both match
TEST_F(MatchAllOfGenericTest_159, TwoMatchersBothMatch_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt10 = LessThanMatcher(10);
    
    auto combined = std::move(gt5) && lt10;
    
    // 7 is greater than 5 AND less than 10
    EXPECT_TRUE(combined.match(7));
}

// Test that combined matcher fails when first matcher fails
TEST_F(MatchAllOfGenericTest_159, TwoMatchersFirstFails_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt10 = LessThanMatcher(10);
    
    auto combined = std::move(gt5) && lt10;
    
    // 3 is NOT greater than 5
    EXPECT_FALSE(combined.match(3));
}

// Test that combined matcher fails when second matcher fails
TEST_F(MatchAllOfGenericTest_159, TwoMatchersSecondFails_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt10 = LessThanMatcher(10);
    
    auto combined = std::move(gt5) && lt10;
    
    // 15 is greater than 5 but NOT less than 10
    EXPECT_FALSE(combined.match(15));
}

// Test that combined matcher fails when both matchers fail
TEST_F(MatchAllOfGenericTest_159, TwoMatchersBothFail_159) {
    auto gt10 = GreaterThanMatcher(10);
    auto lt5 = LessThanMatcher(5);
    
    auto combined = std::move(gt10) && lt5;
    
    // 7 is NOT greater than 10 AND NOT less than 5
    EXPECT_FALSE(combined.match(7));
}

// Test chaining three matchers together
TEST_F(MatchAllOfGenericTest_159, ThreeMatchersAllMatch_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt100 = LessThanMatcher(100);
    auto isEven = IsEvenMatcher();
    
    auto combined = std::move(gt5) && lt100;
    auto combined3 = std::move(combined) && isEven;
    
    // 8 is greater than 5, less than 100, and even
    EXPECT_TRUE(combined3.match(8));
}

// Test chaining three matchers where third fails
TEST_F(MatchAllOfGenericTest_159, ThreeMatchersThirdFails_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt100 = LessThanMatcher(100);
    auto isEven = IsEvenMatcher();
    
    auto combined = std::move(gt5) && lt100;
    auto combined3 = std::move(combined) && isEven;
    
    // 7 is greater than 5, less than 100, but NOT even
    EXPECT_FALSE(combined3.match(7));
}

// Test that describe returns a non-empty string for combined matchers
TEST_F(MatchAllOfGenericTest_159, DescribeReturnsNonEmpty_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt10 = LessThanMatcher(10);
    
    auto combined = std::move(gt5) && lt10;
    
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test with string matchers
TEST_F(MatchAllOfGenericTest_159, StringMatchersCombined_159) {
    auto contains_hello = StringContainsMatcher("hello");
    auto starts_with_say = StringStartsWithMatcher("say");
    
    auto combined = std::move(contains_hello) && starts_with_say;
    
    EXPECT_TRUE(combined.match(std::string("say hello world")));
}

// Test with string matchers where one fails
TEST_F(MatchAllOfGenericTest_159, StringMatchersCombinedOneFails_159) {
    auto contains_hello = StringContainsMatcher("hello");
    auto starts_with_say = StringStartsWithMatcher("say");
    
    auto combined = std::move(contains_hello) && starts_with_say;
    
    // Contains "hello" but doesn't start with "say"
    EXPECT_FALSE(combined.match(std::string("just hello")));
}

// Test boundary: value exactly at threshold for GreaterThan
TEST_F(MatchAllOfGenericTest_159, BoundaryExactThreshold_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt10 = LessThanMatcher(10);
    
    auto combined = std::move(gt5) && lt10;
    
    // 5 is NOT greater than 5 (strict)
    EXPECT_FALSE(combined.match(5));
}

// Test boundary: value exactly at upper threshold
TEST_F(MatchAllOfGenericTest_159, BoundaryExactUpperThreshold_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt10 = LessThanMatcher(10);
    
    auto combined = std::move(gt5) && lt10;
    
    // 10 is greater than 5 but NOT less than 10
    EXPECT_FALSE(combined.match(10));
}

// Test four matchers chained together
TEST_F(MatchAllOfGenericTest_159, FourMatchersAllMatch_159) {
    auto gt0 = GreaterThanMatcher(0);
    auto lt100 = LessThanMatcher(100);
    auto isEven = IsEvenMatcher();
    auto isPositive = IsPositiveMatcher();
    
    auto c1 = std::move(gt0) && lt100;
    auto c2 = std::move(c1) && isEven;
    auto c3 = std::move(c2) && isPositive;
    
    // 42 is > 0, < 100, even, and positive
    EXPECT_TRUE(c3.match(42));
}

// Test four matchers where one fails
TEST_F(MatchAllOfGenericTest_159, FourMatchersOneFails_159) {
    auto gt0 = GreaterThanMatcher(0);
    auto lt100 = LessThanMatcher(100);
    auto isEven = IsEvenMatcher();
    auto isPositive = IsPositiveMatcher();
    
    auto c1 = std::move(gt0) && lt100;
    auto c2 = std::move(c1) && isEven;
    auto c3 = std::move(c2) && isPositive;
    
    // 43 is > 0, < 100, positive, but NOT even
    EXPECT_FALSE(c3.match(43));
}

// Test describe with three matchers includes meaningful information
TEST_F(MatchAllOfGenericTest_159, DescribeThreeMatchers_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt100 = LessThanMatcher(100);
    auto isEven = IsEvenMatcher();
    
    auto combined = std::move(gt5) && lt100;
    auto combined3 = std::move(combined) && isEven;
    
    std::string description = combined3.describe();
    EXPECT_FALSE(description.empty());
}

// Test that the result type is correct (MatchAllOfGeneric with accumulated types)
TEST_F(MatchAllOfGenericTest_159, ResultTypeIsMatchAllOfGeneric_159) {
    auto gt5 = GreaterThanMatcher(5);
    auto lt10 = LessThanMatcher(10);
    
    auto combined = std::move(gt5) && lt10;
    
    // Verify it's still a matcher by calling match
    bool result = combined.match(7);
    EXPECT_TRUE(result);
}

// Test with negative numbers
TEST_F(MatchAllOfGenericTest_159, NegativeNumbers_159) {
    auto gt_neg10 = GreaterThanMatcher(-10);
    auto lt_neg1 = LessThanMatcher(-1);
    
    auto combined = std::move(gt_neg10) && lt_neg1;
    
    // -5 is greater than -10 AND less than -1
    EXPECT_TRUE(combined.match(-5));
}

// Test with negative numbers failing
TEST_F(MatchAllOfGenericTest_159, NegativeNumbersFailing_159) {
    auto gt_neg10 = GreaterThanMatcher(-10);
    auto lt_neg1 = LessThanMatcher(-1);
    
    auto combined = std::move(gt_neg10) && lt_neg1;
    
    // 0 is greater than -10 but NOT less than -1
    EXPECT_FALSE(combined.match(0));
}

// Test with zero as boundary
TEST_F(MatchAllOfGenericTest_159, ZeroBoundary_159) {
    auto gt0 = GreaterThanMatcher(0);
    auto isEven = IsEvenMatcher();
    
    auto combined = std::move(gt0) && isEven;
    
    // 0 is NOT greater than 0
    EXPECT_FALSE(combined.match(0));
    
    // Recreate since moved
    auto gt0_2 = GreaterThanMatcher(0);
    auto isEven2 = IsEvenMatcher();
    auto combined2 = std::move(gt0_2) && isEven2;
    
    // 2 is greater than 0 AND even
    EXPECT_TRUE(combined2.match(2));
}

// Test matching with large values
TEST_F(MatchAllOfGenericTest_159, LargeValues_159) {
    auto gt_million = GreaterThanMatcher(1000000);
    auto lt_billion = LessThanMatcher(1000000000);
    
    auto combined = std::move(gt_million) && lt_billion;
    
    EXPECT_TRUE(combined.match(500000000));
    EXPECT_FALSE(combined.match(500000));
}
