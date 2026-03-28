#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>

// Since we're testing AllMatchMatcher which is a template class that wraps a matcher,
// we need to create a simple matcher to use with it.

// Minimal matcher that checks if a value satisfies a predicate
template <typename Predicate>
class SimpleMatcher {
    Predicate m_pred;
    std::string m_description;
public:
    SimpleMatcher(Predicate pred, std::string desc = "simple matcher")
        : m_pred(pred), m_description(std::move(desc)) {}
    
    template <typename T>
    bool match(T&& val) const {
        return m_pred(std::forward<T>(val));
    }
    
    std::string describe() const { return m_description; }
};

// Reconstruct a minimal AllMatchMatcher for testing purposes
// based on the provided interface
template <typename Matcher>
class AllMatchMatcher {
    Matcher m_matcher;
public:
    AllMatchMatcher(Matcher matcher) : m_matcher(std::move(matcher)) {}
    
    template <typename RangeLike>
    bool match(RangeLike&& rng) const {
        for (auto&& elem : rng) {
            if (!m_matcher.match(elem)) {
                return false;
            }
        }
        return true;
    }
};

// Helper to create AllMatchMatcher easily
template <typename Matcher>
AllMatchMatcher<Matcher> makeAllMatchMatcher(Matcher m) {
    return AllMatchMatcher<Matcher>(std::move(m));
}

// Test fixture
class AllMatchMatcherTest_177 : public ::testing::Test {
protected:
    // Matcher: all elements are positive
    SimpleMatcher<std::function<bool(int)>> isPositive{
        [](int v) { return v > 0; }, "is positive"
    };
    
    // Matcher: all elements are even
    SimpleMatcher<std::function<bool(int)>> isEven{
        [](int v) { return v % 2 == 0; }, "is even"
    };
    
    // Matcher: string is non-empty
    SimpleMatcher<std::function<bool(const std::string&)>> isNonEmpty{
        [](const std::string& s) { return !s.empty(); }, "is non-empty"
    };
};

// Normal operation: all elements match
TEST_F(AllMatchMatcherTest_177, AllElementsMatch_ReturnsTrue_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Normal operation: not all elements match
TEST_F(AllMatchMatcherTest_177, NotAllElementsMatch_ReturnsFalse_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {1, 2, -3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Boundary: empty range should return true (vacuous truth)
TEST_F(AllMatchMatcherTest_177, EmptyRange_ReturnsTrue_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {};
    EXPECT_TRUE(matcher.match(v));
}

// Boundary: single element that matches
TEST_F(AllMatchMatcherTest_177, SingleElementMatches_ReturnsTrue_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// Boundary: single element that doesn't match
TEST_F(AllMatchMatcherTest_177, SingleElementDoesNotMatch_ReturnsFalse_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {-1};
    EXPECT_FALSE(matcher.match(v));
}

// First element fails
TEST_F(AllMatchMatcherTest_177, FirstElementFails_ReturnsFalse_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {-1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(v));
}

// Last element fails
TEST_F(AllMatchMatcherTest_177, LastElementFails_ReturnsFalse_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {1, 2, 3, -4};
    EXPECT_FALSE(matcher.match(v));
}

// All elements fail
TEST_F(AllMatchMatcherTest_177, AllElementsFail_ReturnsFalse_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {-1, -2, -3};
    EXPECT_FALSE(matcher.match(v));
}

// Works with different container types: list
TEST_F(AllMatchMatcherTest_177, WorksWithList_177) {
    auto matcher = makeAllMatchMatcher(isEven);
    std::list<int> l = {2, 4, 6, 8};
    EXPECT_TRUE(matcher.match(l));
}

// Works with different container types: array
TEST_F(AllMatchMatcherTest_177, WorksWithArray_177) {
    auto matcher = makeAllMatchMatcher(isEven);
    std::array<int, 4> a = {2, 4, 6, 8};
    EXPECT_TRUE(matcher.match(a));
}

// Works with array that has non-matching element
TEST_F(AllMatchMatcherTest_177, WorksWithArrayNonMatching_177) {
    auto matcher = makeAllMatchMatcher(isEven);
    std::array<int, 4> a = {2, 4, 5, 8};
    EXPECT_FALSE(matcher.match(a));
}

// Works with strings
TEST_F(AllMatchMatcherTest_177, WorksWithStringContainer_177) {
    auto matcher = makeAllMatchMatcher(isNonEmpty);
    std::vector<std::string> v = {"hello", "world", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

// String container with empty string fails
TEST_F(AllMatchMatcherTest_177, StringContainerWithEmptyStringFails_177) {
    auto matcher = makeAllMatchMatcher(isNonEmpty);
    std::vector<std::string> v = {"hello", "", "foo"};
    EXPECT_FALSE(matcher.match(v));
}

// Works with C-style array via initializer_list
TEST_F(AllMatchMatcherTest_177, WorksWithInitializerList_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    EXPECT_TRUE(matcher.match(std::initializer_list<int>{1, 2, 3}));
}

// Even matcher with all odd fails
TEST_F(AllMatchMatcherTest_177, EvenMatcherWithAllOdd_ReturnsFalse_177) {
    auto matcher = makeAllMatchMatcher(isEven);
    std::vector<int> v = {1, 3, 5, 7};
    EXPECT_FALSE(matcher.match(v));
}

// Even matcher with mixed values
TEST_F(AllMatchMatcherTest_177, EvenMatcherWithMixed_ReturnsFalse_177) {
    auto matcher = makeAllMatchMatcher(isEven);
    std::vector<int> v = {2, 4, 5, 8};
    EXPECT_FALSE(matcher.match(v));
}

// Large range all matching
TEST_F(AllMatchMatcherTest_177, LargeRangeAllMatch_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v(10000, 1);
    EXPECT_TRUE(matcher.match(v));
}

// Large range with single non-matching at end
TEST_F(AllMatchMatcherTest_177, LargeRangeWithSingleFailAtEnd_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v(10000, 1);
    v.back() = -1;
    EXPECT_FALSE(matcher.match(v));
}

// Large range with single non-matching at beginning
TEST_F(AllMatchMatcherTest_177, LargeRangeWithSingleFailAtBeginning_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v(10000, 1);
    v.front() = -1;
    EXPECT_FALSE(matcher.match(v));
}

// Verify short-circuit behavior by counting calls
TEST_F(AllMatchMatcherTest_177, ShortCircuitsOnFirstFailure_177) {
    int callCount = 0;
    SimpleMatcher<std::function<bool(int)>> countingMatcher{
        [&callCount](int v) { callCount++; return v > 0; },
        "counting positive"
    };
    auto matcher = makeAllMatchMatcher(countingMatcher);
    std::vector<int> v = {1, 2, -3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
    // Should stop at the third element
    EXPECT_EQ(callCount, 3);
}

// Verify all elements checked when all match
TEST_F(AllMatchMatcherTest_177, ChecksAllElementsWhenAllMatch_177) {
    int callCount = 0;
    SimpleMatcher<std::function<bool(int)>> countingMatcher{
        [&callCount](int v) { callCount++; return v > 0; },
        "counting positive"
    };
    auto matcher = makeAllMatchMatcher(countingMatcher);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
    EXPECT_EQ(callCount, 5);
}

// Test with const reference range
TEST_F(AllMatchMatcherTest_177, WorksWithConstRange_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    const std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Zero values with isPositive (boundary: zero is not positive)
TEST_F(AllMatchMatcherTest_177, ZeroIsNotPositive_177) {
    auto matcher = makeAllMatchMatcher(isPositive);
    std::vector<int> v = {1, 0, 3};
    EXPECT_FALSE(matcher.match(v));
}
