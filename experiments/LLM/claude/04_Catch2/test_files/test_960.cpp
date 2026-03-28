#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <functional>

// Include the Catch2 amalgamated header for the RangeEquals matcher
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Helper to check if a matcher matches a given range
template <typename Matcher, typename Range>
bool matcherMatches(const Matcher& matcher, const Range& range) {
    return matcher.match(range);
}

// ---- Tests for RangeEquals ----

class RangeEqualsTest_960 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Two identical vectors of ints should match
TEST_F(RangeEqualsTest_960, IdenticalIntVectorsMatch_960) {
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Two different vectors of ints should not match
TEST_F(RangeEqualsTest_960, DifferentIntVectorsDoNotMatch_960) {
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1, 2, 3, 4, 6};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Empty ranges should match
TEST_F(RangeEqualsTest_960, EmptyRangesMatch_960) {
    std::vector<int> expected = {};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Different sized ranges should not match
TEST_F(RangeEqualsTest_960, DifferentSizedRangesDoNotMatch_960) {
    std::vector<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1, 2};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Actual range longer than expected should not match
TEST_F(RangeEqualsTest_960, ActualLongerThanExpectedDoNotMatch_960) {
    std::vector<int> expected = {1, 2};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1, 2, 3};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Single element ranges that match
TEST_F(RangeEqualsTest_960, SingleElementMatchingRanges_960) {
    std::vector<int> expected = {42};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {42};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Single element ranges that do not match
TEST_F(RangeEqualsTest_960, SingleElementNonMatchingRanges_960) {
    std::vector<int> expected = {42};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {43};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Custom predicate - compare by absolute value
TEST_F(RangeEqualsTest_960, CustomPredicateAbsoluteValueComparison_960) {
    std::vector<int> expected = {1, -2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected, [](int a, int b) {
        return std::abs(a) == std::abs(b);
    });
    
    std::vector<int> actual = {-1, 2, -3};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Custom predicate that always returns true
TEST_F(RangeEqualsTest_960, CustomPredicateAlwaysTrue_960) {
    std::vector<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected, [](int, int) {
        return true;
    });
    
    std::vector<int> actual = {99, 98, 97};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Custom predicate that always returns false
TEST_F(RangeEqualsTest_960, CustomPredicateAlwaysFalse_960) {
    std::vector<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected, [](int, int) {
        return false;
    });
    
    std::vector<int> actual = {1, 2, 3};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Different container types - vector vs list
TEST_F(RangeEqualsTest_960, DifferentContainerTypesVectorVsList_960) {
    std::list<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1, 2, 3};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Different container types - vector vs array
TEST_F(RangeEqualsTest_960, DifferentContainerTypesVectorVsArray_960) {
    std::array<int, 3> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1, 2, 3};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: String vectors match
TEST_F(RangeEqualsTest_960, StringVectorsMatch_960) {
    std::vector<std::string> expected = {"hello", "world"};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<std::string> actual = {"hello", "world"};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: String vectors do not match
TEST_F(RangeEqualsTest_960, StringVectorsDoNotMatch_960) {
    std::vector<std::string> expected = {"hello", "world"};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<std::string> actual = {"hello", "earth"};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Custom predicate for case-insensitive string comparison
TEST_F(RangeEqualsTest_960, CaseInsensitiveStringComparison_960) {
    std::vector<std::string> expected = {"Hello", "World"};
    auto matcher = Catch::Matchers::RangeEquals(expected, [](const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(a[i]) != std::tolower(b[i])) return false;
        }
        return true;
    });
    
    std::vector<std::string> actual = {"hello", "world"};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Double/float vectors with default equality
TEST_F(RangeEqualsTest_960, DoubleVectorsExactMatch_960) {
    std::vector<double> expected = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<double> actual = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Double vectors with approximate comparison predicate
TEST_F(RangeEqualsTest_960, DoubleVectorsApproximateMatch_960) {
    std::vector<double> expected = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::RangeEquals(expected, [](double a, double b) {
        return std::abs(a - b) < 0.01;
    });
    
    std::vector<double> actual = {1.005, 2.005, 3.005};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Empty expected with non-empty actual should not match
TEST_F(RangeEqualsTest_960, EmptyExpectedNonEmptyActual_960) {
    std::vector<int> expected = {};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Non-empty expected with empty actual should not match
TEST_F(RangeEqualsTest_960, NonEmptyExpectedEmptyActual_960) {
    std::vector<int> expected = {1};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Same elements in different order should not match (default equality)
TEST_F(RangeEqualsTest_960, SameElementsDifferentOrderDoNotMatch_960) {
    std::vector<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {3, 2, 1};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Large identical ranges match
TEST_F(RangeEqualsTest_960, LargeIdenticalRangesMatch_960) {
    std::vector<int> expected(1000);
    std::iota(expected.begin(), expected.end(), 0);
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual(1000);
    std::iota(actual.begin(), actual.end(), 0);
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Large ranges differ at last element
TEST_F(RangeEqualsTest_960, LargeRangesDifferAtEnd_960) {
    std::vector<int> expected(1000);
    std::iota(expected.begin(), expected.end(), 0);
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual(1000);
    std::iota(actual.begin(), actual.end(), 0);
    actual.back() = -1;
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Matcher has a describe method that returns a non-empty string
TEST_F(RangeEqualsTest_960, DescribeReturnsNonEmptyString_960) {
    std::vector<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Initializer list style range
TEST_F(RangeEqualsTest_960, WorksWithInitializerListStyleVector_960) {
    auto matcher = Catch::Matchers::RangeEquals(std::vector<int>{10, 20, 30});
    
    std::vector<int> actual = {10, 20, 30};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Boolean vectors
TEST_F(RangeEqualsTest_960, BooleanVectorsMatch_960) {
    std::vector<bool> expected = {true, false, true};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<bool> actual = {true, false, true};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Boolean vectors do not match
TEST_F(RangeEqualsTest_960, BooleanVectorsDoNotMatch_960) {
    std::vector<bool> expected = {true, false, true};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<bool> actual = {true, true, true};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Custom predicate with empty ranges should match (no comparisons needed)
TEST_F(RangeEqualsTest_960, CustomPredicateEmptyRangesMatch_960) {
    std::vector<int> expected = {};
    auto matcher = Catch::Matchers::RangeEquals(expected, [](int, int) {
        return false; // Even with always-false predicate, empty ranges should match
    });
    
    std::vector<int> actual = {};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Ranges with negative numbers
TEST_F(RangeEqualsTest_960, NegativeNumbersMatch_960) {
    std::vector<int> expected = {-5, -3, -1, 0, 1, 3, 5};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {-5, -3, -1, 0, 1, 3, 5};
    EXPECT_TRUE(matcherMatches(matcher, actual));
}

// Test: Ranges differ at first element
TEST_F(RangeEqualsTest_960, RangesDifferAtFirstElement_960) {
    std::vector<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {0, 2, 3};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}

// Test: Ranges differ at middle element
TEST_F(RangeEqualsTest_960, RangesDifferAtMiddleElement_960) {
    std::vector<int> expected = {1, 2, 3};
    auto matcher = Catch::Matchers::RangeEquals(expected);
    
    std::vector<int> actual = {1, 99, 3};
    EXPECT_FALSE(matcherMatches(matcher, actual));
}
