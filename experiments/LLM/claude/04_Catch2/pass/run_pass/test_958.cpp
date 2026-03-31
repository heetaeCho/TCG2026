#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <functional>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Helper to create an UnorderedRangeEqualsMatcher with default equality
template <typename Range>
auto makeUnorderedMatcher(Range&& range) {
    return UnorderedRangeEqualsMatcher<std::decay_t<Range>, std::equal_to<>>(
        std::forward<Range>(range), std::equal_to<>{});
}

// Helper to create an UnorderedRangeEqualsMatcher with custom predicate
template <typename Range, typename Pred>
auto makeUnorderedMatcherWithPred(Range&& range, Pred&& pred) {
    return UnorderedRangeEqualsMatcher<std::decay_t<Range>, std::decay_t<Pred>>(
        std::forward<Range>(range), std::forward<Pred>(pred));
}

// Test: Both ranges are empty - should match
TEST(UnorderedRangeEqualsMatcherTest_958, BothEmptyRangesMatch_958) {
    std::vector<int> desired = {};
    std::vector<int> target = {};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Identical ranges in same order
TEST(UnorderedRangeEqualsMatcherTest_958, IdenticalRangesSameOrder_958) {
    std::vector<int> desired = {1, 2, 3, 4, 5};
    std::vector<int> target = {1, 2, 3, 4, 5};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Same elements in different order (permutation)
TEST(UnorderedRangeEqualsMatcherTest_958, SameElementsDifferentOrder_958) {
    std::vector<int> desired = {1, 2, 3, 4, 5};
    std::vector<int> target = {5, 3, 1, 4, 2};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Different sizes - target is shorter
TEST(UnorderedRangeEqualsMatcherTest_958, DifferentSizesTargetShorter_958) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> target = {1, 2};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Different sizes - target is longer
TEST(UnorderedRangeEqualsMatcherTest_958, DifferentSizesTargetLonger_958) {
    std::vector<int> desired = {1, 2};
    std::vector<int> target = {1, 2, 3};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Same size but different elements
TEST(UnorderedRangeEqualsMatcherTest_958, SameSizeDifferentElements_958) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> target = {4, 5, 6};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Single element match
TEST(UnorderedRangeEqualsMatcherTest_958, SingleElementMatch_958) {
    std::vector<int> desired = {42};
    std::vector<int> target = {42};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Single element no match
TEST(UnorderedRangeEqualsMatcherTest_958, SingleElementNoMatch_958) {
    std::vector<int> desired = {42};
    std::vector<int> target = {99};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Duplicate elements - same duplicates
TEST(UnorderedRangeEqualsMatcherTest_958, DuplicateElementsSameCounts_958) {
    std::vector<int> desired = {1, 1, 2, 3, 3};
    std::vector<int> target = {3, 1, 3, 2, 1};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Duplicate elements - different counts
TEST(UnorderedRangeEqualsMatcherTest_958, DuplicateElementsDifferentCounts_958) {
    std::vector<int> desired = {1, 1, 2, 3};
    std::vector<int> target = {1, 2, 3, 3};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Empty desired, non-empty target
TEST(UnorderedRangeEqualsMatcherTest_958, EmptyDesiredNonEmptyTarget_958) {
    std::vector<int> desired = {};
    std::vector<int> target = {1};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Non-empty desired, empty target
TEST(UnorderedRangeEqualsMatcherTest_958, NonEmptyDesiredEmptyTarget_958) {
    std::vector<int> desired = {1};
    std::vector<int> target = {};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Works with different container types (list vs vector)
TEST(UnorderedRangeEqualsMatcherTest_958, DifferentContainerTypes_958) {
    std::vector<int> desired = {3, 1, 2};
    std::list<int> target = {2, 3, 1};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Works with std::array
TEST(UnorderedRangeEqualsMatcherTest_958, WorksWithStdArray_958) {
    std::array<int, 3> desired = {1, 2, 3};
    std::array<int, 3> target = {3, 2, 1};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Works with strings
TEST(UnorderedRangeEqualsMatcherTest_958, WorksWithStrings_958) {
    std::vector<std::string> desired = {"hello", "world", "foo"};
    std::vector<std::string> target = {"foo", "hello", "world"};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Custom predicate - case insensitive string comparison
TEST(UnorderedRangeEqualsMatcherTest_958, CustomPredicateCaseInsensitive_958) {
    auto caseInsensitiveEqual = [](const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(a[i]) != std::tolower(b[i])) return false;
        }
        return true;
    };
    
    std::vector<std::string> desired = {"Hello", "World"};
    std::vector<std::string> target = {"world", "hello"};
    auto matcher = makeUnorderedMatcherWithPred(desired, caseInsensitiveEqual);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Custom predicate that does not match
TEST(UnorderedRangeEqualsMatcherTest_958, CustomPredicateNoMatch_958) {
    auto alwaysFalse = [](int, int) { return false; };
    
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> target = {1, 2, 3};
    auto matcher = makeUnorderedMatcherWithPred(desired, alwaysFalse);
    EXPECT_FALSE(matcher.match(target));
}

// Test: All same elements
TEST(UnorderedRangeEqualsMatcherTest_958, AllSameElements_958) {
    std::vector<int> desired = {5, 5, 5, 5};
    std::vector<int> target = {5, 5, 5, 5};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: All same elements but different count
TEST(UnorderedRangeEqualsMatcherTest_958, AllSameElementsDifferentCount_958) {
    std::vector<int> desired = {5, 5, 5};
    std::vector<int> target = {5, 5, 5, 5};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: Large range permutation
TEST(UnorderedRangeEqualsMatcherTest_958, LargeRangePermutation_958) {
    std::vector<int> desired;
    std::vector<int> target;
    for (int i = 0; i < 100; ++i) {
        desired.push_back(i);
        target.push_back(99 - i);
    }
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Partial overlap - same size but some elements differ
TEST(UnorderedRangeEqualsMatcherTest_958, PartialOverlap_958) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> target = {1, 2, 4};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_FALSE(matcher.match(target));
}

// Test: describe returns non-empty string
TEST(UnorderedRangeEqualsMatcherTest_958, DescribeReturnsNonEmpty_958) {
    std::vector<int> desired = {1, 2, 3};
    auto matcher = makeUnorderedMatcher(desired);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Negative numbers
TEST(UnorderedRangeEqualsMatcherTest_958, NegativeNumbers_958) {
    std::vector<int> desired = {-3, -1, -2};
    std::vector<int> target = {-1, -2, -3};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Mixed positive and negative
TEST(UnorderedRangeEqualsMatcherTest_958, MixedPositiveNegative_958) {
    std::vector<int> desired = {-1, 0, 1};
    std::vector<int> target = {1, -1, 0};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Floating point values
TEST(UnorderedRangeEqualsMatcherTest_958, FloatingPointValues_958) {
    std::vector<double> desired = {1.1, 2.2, 3.3};
    std::vector<double> target = {3.3, 1.1, 2.2};
    auto matcher = makeUnorderedMatcher(desired);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Custom predicate with modular equality
TEST(UnorderedRangeEqualsMatcherTest_958, CustomPredicateModularEquality_958) {
    auto modEqual = [](int a, int b) { return (a % 10) == (b % 10); };
    
    std::vector<int> desired = {1, 12, 23};
    std::vector<int> target = {33, 11, 2};
    auto matcher = makeUnorderedMatcherWithPred(desired, modEqual);
    EXPECT_TRUE(matcher.match(target));
}
