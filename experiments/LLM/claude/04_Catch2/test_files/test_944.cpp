#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <functional>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Helper comparators
struct EqualTo {
    template<typename T>
    constexpr bool operator()(const T& a, const T& b) const {
        return a == b;
    }
};

struct LessThan {
    template<typename T>
    constexpr bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

struct AlwaysTrue {
    template<typename T>
    constexpr bool operator()(const T&, const T&) const {
        return true;
    }
};

struct AlwaysFalse {
    template<typename T>
    constexpr bool operator()(const T&, const T&) const {
        return false;
    }
};

// Test fixture
class CountSentinelTest_944 : public ::testing::Test {
protected:
};

// Normal operation: count occurrences of a value in a vector using equality
TEST_F(CountSentinelTest_944, CountMatchingElementsInVector_944) {
    std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 2, EqualTo{});
    EXPECT_EQ(result, 3);
}

// Normal operation: count with no matches
TEST_F(CountSentinelTest_944, CountNoMatchingElements_944) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 10, EqualTo{});
    EXPECT_EQ(result, 0);
}

// Boundary condition: empty range
TEST_F(CountSentinelTest_944, EmptyRange_944) {
    std::vector<int> v;
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 1, EqualTo{});
    EXPECT_EQ(result, 0);
}

// Boundary condition: single element that matches
TEST_F(CountSentinelTest_944, SingleElementMatches_944) {
    std::vector<int> v = {42};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 42, EqualTo{});
    EXPECT_EQ(result, 1);
}

// Boundary condition: single element that does not match
TEST_F(CountSentinelTest_944, SingleElementDoesNotMatch_944) {
    std::vector<int> v = {42};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 99, EqualTo{});
    EXPECT_EQ(result, 0);
}

// All elements match
TEST_F(CountSentinelTest_944, AllElementsMatch_944) {
    std::vector<int> v = {7, 7, 7, 7, 7};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 7, EqualTo{});
    EXPECT_EQ(result, 5);
}

// Comparator that always returns true
TEST_F(CountSentinelTest_944, ComparatorAlwaysTrue_944) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 0, AlwaysTrue{});
    EXPECT_EQ(result, 5);
}

// Comparator that always returns false
TEST_F(CountSentinelTest_944, ComparatorAlwaysFalse_944) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 0, AlwaysFalse{});
    EXPECT_EQ(result, 0);
}

// Using a custom comparator (less than)
TEST_F(CountSentinelTest_944, CustomComparatorLessThan_944) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    // Count elements less than 3
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 3, LessThan{});
    EXPECT_EQ(result, 2); // 1 and 2 are less than 3
}

// Using with std::list (forward iterator)
TEST_F(CountSentinelTest_944, WorksWithListIterators_944) {
    std::list<int> lst = {10, 20, 30, 20, 40};
    auto result = Catch::Detail::count_sentinel(lst.begin(), lst.end(), 20, EqualTo{});
    EXPECT_EQ(result, 2);
}

// Using with string elements
TEST_F(CountSentinelTest_944, WorksWithStrings_944) {
    std::vector<std::string> v = {"hello", "world", "hello", "foo"};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), std::string("hello"), EqualTo{});
    EXPECT_EQ(result, 2);
}

// Using with raw array pointers
TEST_F(CountSentinelTest_944, WorksWithRawPointers_944) {
    int arr[] = {5, 10, 15, 10, 20};
    auto result = Catch::Detail::count_sentinel(std::begin(arr), std::end(arr), 10, EqualTo{});
    EXPECT_EQ(result, 2);
}

// Return type is std::ptrdiff_t
TEST_F(CountSentinelTest_944, ReturnTypeIsPtrdiffT_944) {
    std::vector<int> v = {1, 2, 3};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 2, EqualTo{});
    static_assert(std::is_same<decltype(result), std::ptrdiff_t>::value, "Return type should be std::ptrdiff_t");
    EXPECT_EQ(result, 1);
}

// Large collection
TEST_F(CountSentinelTest_944, LargeCollection_944) {
    std::vector<int> v(10000, 0);
    // Set every 10th element to 1
    for (size_t i = 0; i < v.size(); i += 10) {
        v[i] = 1;
    }
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 1, EqualTo{});
    EXPECT_EQ(result, 1000);
}

// Lambda comparator
TEST_F(CountSentinelTest_944, LambdaComparator_944) {
    std::vector<int> v = {1, -2, 3, -4, 5};
    // Count elements whose absolute value equals the given value's absolute value
    auto absCmp = [](int a, int b) { return std::abs(a) == std::abs(b); };
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 4, absCmp);
    EXPECT_EQ(result, 1); // only -4
}

// Match at boundaries (first and last elements)
TEST_F(CountSentinelTest_944, MatchAtFirstAndLastElement_944) {
    std::vector<int> v = {99, 1, 2, 3, 99};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 99, EqualTo{});
    EXPECT_EQ(result, 2);
}

// Using with double values
TEST_F(CountSentinelTest_944, WorksWithDoubles_944) {
    std::vector<double> v = {1.0, 2.5, 3.0, 2.5, 4.0};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.end(), 2.5, EqualTo{});
    EXPECT_EQ(result, 2);
}

// Partial range
TEST_F(CountSentinelTest_944, PartialRange_944) {
    std::vector<int> v = {1, 2, 3, 2, 5, 2, 7};
    // Only search first 4 elements
    auto result = Catch::Detail::count_sentinel(v.begin(), v.begin() + 4, 2, EqualTo{});
    EXPECT_EQ(result, 2);
}

// Same start and sentinel (zero-length range)
TEST_F(CountSentinelTest_944, SameStartAndSentinel_944) {
    std::vector<int> v = {1, 2, 3};
    auto result = Catch::Detail::count_sentinel(v.begin(), v.begin(), 1, EqualTo{});
    EXPECT_EQ(result, 0);
}
