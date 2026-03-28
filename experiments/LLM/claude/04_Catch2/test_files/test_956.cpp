#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <functional>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Helper: default equality predicate
auto default_eq = [](const auto& a, const auto& b) { return a == b; };

// ============================================================
// Test Fixture
// ============================================================
class RangeEqualsMatcherTest_956 : public ::testing::Test {
protected:
    // Nothing special needed
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, BothEmptyRangesMatch_956) {
    std::vector<int> target{};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, IdenticalSingleElementRangesMatch_956) {
    std::vector<int> target{42};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{42};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, IdenticalMultipleElementRangesMatch_956) {
    std::vector<int> target{1, 2, 3, 4, 5};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, DifferentElementsDoNotMatch_956) {
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{1, 2, 4};
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, DifferentFirstElementDoesNotMatch_956) {
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{0, 2, 3};
    EXPECT_FALSE(matcher.match(input));
}

// ============================================================
// Boundary / Size mismatch tests
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, InputLongerThanTargetDoesNotMatch_956) {
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, InputShorterThanTargetDoesNotMatch_956) {
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{1, 2};
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, EmptyInputNonEmptyTargetDoesNotMatch_956) {
    std::vector<int> target{1};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{};
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, NonEmptyInputEmptyTargetDoesNotMatch_956) {
    std::vector<int> target{};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{1};
    EXPECT_FALSE(matcher.match(input));
}

// ============================================================
// Custom predicate tests
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, CustomPredicateMatchesWhenConditionHolds_956) {
    // Predicate: both have the same parity
    auto same_parity = [](int a, int b) { return (a % 2) == (b % 2); };
    std::vector<int> target{2, 3, 4};
    RangeEqualsMatcher<std::vector<int>, decltype(same_parity)> matcher(target, same_parity);
    std::vector<int> input{8, 7, 10};  // even, odd, even
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, CustomPredicateFailsWhenConditionDoesNotHold_956) {
    auto same_parity = [](int a, int b) { return (a % 2) == (b % 2); };
    std::vector<int> target{2, 3, 4};
    RangeEqualsMatcher<std::vector<int>, decltype(same_parity)> matcher(target, same_parity);
    std::vector<int> input{8, 6, 10};  // even, even, even — second pair fails
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, AlwaysTruePredicateMatchesSameSizeRanges_956) {
    auto always_true = [](int, int) { return true; };
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(always_true)> matcher(target, always_true);
    std::vector<int> input{99, 100, 101};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, AlwaysTruePredicateDoesNotMatchDifferentSizes_956) {
    auto always_true = [](int, int) { return true; };
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(always_true)> matcher(target, always_true);
    std::vector<int> input{99, 100};
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, AlwaysFalsePredicateDoesNotMatchNonEmpty_956) {
    auto always_false = [](int, int) { return false; };
    std::vector<int> target{1};
    RangeEqualsMatcher<std::vector<int>, decltype(always_false)> matcher(target, always_false);
    std::vector<int> input{1};
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, AlwaysFalsePredicateMatchesBothEmpty_956) {
    auto always_false = [](int, int) { return false; };
    std::vector<int> target{};
    RangeEqualsMatcher<std::vector<int>, decltype(always_false)> matcher(target, always_false);
    std::vector<int> input{};
    EXPECT_TRUE(matcher.match(input));
}

// ============================================================
// Different container type tests
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, ListAndVectorMatch_956) {
    std::list<int> target{10, 20, 30};
    RangeEqualsMatcher<std::list<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{10, 20, 30};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, ArrayAndVectorMatch_956) {
    std::array<int, 3> target{10, 20, 30};
    RangeEqualsMatcher<std::array<int, 3>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{10, 20, 30};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, StringRangeMatch_956) {
    std::vector<std::string> target{"hello", "world"};
    auto str_eq = [](const std::string& a, const std::string& b) { return a == b; };
    RangeEqualsMatcher<std::vector<std::string>, decltype(str_eq)> matcher(target, str_eq);
    std::vector<std::string> input{"hello", "world"};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, StringRangeDoNotMatch_956) {
    std::vector<std::string> target{"hello", "world"};
    auto str_eq = [](const std::string& a, const std::string& b) { return a == b; };
    RangeEqualsMatcher<std::vector<std::string>, decltype(str_eq)> matcher(target, str_eq);
    std::vector<std::string> input{"hello", "earth"};
    EXPECT_FALSE(matcher.match(input));
}

// ============================================================
// Order sensitivity tests
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, DifferentOrderDoesNotMatch_956) {
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{3, 2, 1};
    EXPECT_FALSE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, ReverseOrderDoesNotMatch_956) {
    std::vector<int> target{1, 2};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{2, 1};
    EXPECT_FALSE(matcher.match(input));
}

// ============================================================
// Predicate call verification
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, PredicateCalledForEachPairUntilMismatch_956) {
    int call_count = 0;
    auto counting_eq = [&call_count](int a, int b) {
        ++call_count;
        return a == b;
    };
    std::vector<int> target{1, 2, 3, 4, 5};
    RangeEqualsMatcher<std::vector<int>, decltype(counting_eq)> matcher(target, counting_eq);
    std::vector<int> input{1, 2, 99, 4, 5};
    EXPECT_FALSE(matcher.match(input));
    // Predicate should have been called at least up to the mismatch (3 calls)
    EXPECT_GE(call_count, 3);
    // And should not have been called for all elements since it short-circuits
    EXPECT_LE(call_count, 3);
}

TEST_F(RangeEqualsMatcherTest_956, PredicateCalledForAllPairsOnFullMatch_956) {
    int call_count = 0;
    auto counting_eq = [&call_count](int a, int b) {
        ++call_count;
        return a == b;
    };
    std::vector<int> target{1, 2, 3};
    RangeEqualsMatcher<std::vector<int>, decltype(counting_eq)> matcher(target, counting_eq);
    std::vector<int> input{1, 2, 3};
    EXPECT_TRUE(matcher.match(input));
    EXPECT_EQ(call_count, 3);
}

// ============================================================
// Large range test
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, LargeIdenticalRangesMatch_956) {
    std::vector<int> target(10000);
    std::iota(target.begin(), target.end(), 0);
    std::vector<int> input(target);
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, LargeRangesDifferAtEnd_956) {
    std::vector<int> target(10000);
    std::iota(target.begin(), target.end(), 0);
    std::vector<int> input(target);
    input.back() = -1;
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    EXPECT_FALSE(matcher.match(input));
}

// ============================================================
// Duplicate elements tests
// ============================================================

TEST_F(RangeEqualsMatcherTest_956, DuplicateElementsMatch_956) {
    std::vector<int> target{5, 5, 5, 5};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{5, 5, 5, 5};
    EXPECT_TRUE(matcher.match(input));
}

TEST_F(RangeEqualsMatcherTest_956, DuplicateElementsDifferentCountDoNotMatch_956) {
    std::vector<int> target{5, 5, 5};
    RangeEqualsMatcher<std::vector<int>, decltype(default_eq)> matcher(target, default_eq);
    std::vector<int> input{5, 5, 5, 5};
    EXPECT_FALSE(matcher.match(input));
}
