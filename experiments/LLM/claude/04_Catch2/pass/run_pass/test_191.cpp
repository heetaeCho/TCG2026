#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <string>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::NoneTrue;
using Catch::Matchers::NoneTrueMatcher;

class NoneTrueMatcherTest_191 : public ::testing::Test {
protected:
    NoneTrueMatcher matcher = NoneTrue();
};

// Test that NoneTrue() factory function returns a NoneTrueMatcher
TEST_F(NoneTrueMatcherTest_191, FactoryReturnsNoneTrueMatcher_191) {
    auto m = NoneTrue();
    // Just verify it compiles and can be created
    (void)m;
}

// Test with empty vector - no elements means none are true
TEST_F(NoneTrueMatcherTest_191, EmptyVectorMatchesNoneTrue_191) {
    std::vector<bool> empty;
    EXPECT_TRUE(matcher.match(empty));
}

// Test with vector of all false values
TEST_F(NoneTrueMatcherTest_191, AllFalseMatchesNoneTrue_191) {
    std::vector<bool> allFalse = {false, false, false};
    EXPECT_TRUE(matcher.match(allFalse));
}

// Test with single false value
TEST_F(NoneTrueMatcherTest_191, SingleFalseMatchesNoneTrue_191) {
    std::vector<bool> singleFalse = {false};
    EXPECT_TRUE(matcher.match(singleFalse));
}

// Test with single true value - should not match
TEST_F(NoneTrueMatcherTest_191, SingleTrueDoesNotMatch_191) {
    std::vector<bool> singleTrue = {true};
    EXPECT_FALSE(matcher.match(singleTrue));
}

// Test with all true values
TEST_F(NoneTrueMatcherTest_191, AllTrueDoesNotMatch_191) {
    std::vector<bool> allTrue = {true, true, true};
    EXPECT_FALSE(matcher.match(allTrue));
}

// Test with mixed values - first element true
TEST_F(NoneTrueMatcherTest_191, FirstTrueDoesNotMatch_191) {
    std::vector<bool> mixed = {true, false, false};
    EXPECT_FALSE(matcher.match(mixed));
}

// Test with mixed values - last element true
TEST_F(NoneTrueMatcherTest_191, LastTrueDoesNotMatch_191) {
    std::vector<bool> mixed = {false, false, true};
    EXPECT_FALSE(matcher.match(mixed));
}

// Test with mixed values - middle element true
TEST_F(NoneTrueMatcherTest_191, MiddleTrueDoesNotMatch_191) {
    std::vector<bool> mixed = {false, true, false};
    EXPECT_FALSE(matcher.match(mixed));
}

// Test with std::array of all false
TEST_F(NoneTrueMatcherTest_191, ArrayAllFalseMatchesNoneTrue_191) {
    std::array<bool, 3> allFalse = {false, false, false};
    EXPECT_TRUE(matcher.match(allFalse));
}

// Test with std::array containing a true
TEST_F(NoneTrueMatcherTest_191, ArrayWithTrueDoesNotMatch_191) {
    std::array<bool, 3> withTrue = {false, true, false};
    EXPECT_FALSE(matcher.match(withTrue));
}

// Test that describe returns a non-empty description string
TEST_F(NoneTrueMatcherTest_191, DescribeReturnsNonEmptyString_191) {
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test with large vector of all false
TEST_F(NoneTrueMatcherTest_191, LargeVectorAllFalseMatches_191) {
    std::vector<bool> largeFalse(1000, false);
    EXPECT_TRUE(matcher.match(largeFalse));
}

// Test with large vector containing one true at the end
TEST_F(NoneTrueMatcherTest_191, LargeVectorOneTrueAtEndDoesNotMatch_191) {
    std::vector<bool> largeVec(1000, false);
    largeVec.back() = true;
    EXPECT_FALSE(matcher.match(largeVec));
}

// Test with large vector containing one true at the beginning
TEST_F(NoneTrueMatcherTest_191, LargeVectorOneTrueAtBeginDoesNotMatch_191) {
    std::vector<bool> largeVec(1000, false);
    largeVec.front() = true;
    EXPECT_FALSE(matcher.match(largeVec));
}

// Test with two elements both false
TEST_F(NoneTrueMatcherTest_191, TwoFalseElementsMatch_191) {
    std::vector<bool> twoFalse = {false, false};
    EXPECT_TRUE(matcher.match(twoFalse));
}

// Test with two elements one true
TEST_F(NoneTrueMatcherTest_191, TwoElementsOneTrue_191) {
    std::vector<bool> vec = {false, true};
    EXPECT_FALSE(matcher.match(vec));
}
