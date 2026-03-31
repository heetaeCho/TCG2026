#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <set>

// Include the Catch2 amalgamated header for the generators
#define CATCH_CONFIG_MAIN
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

class FromRangeTest_941 : public ::testing::Test {
protected:
};

// Normal operation: from_range with a vector of ints
TEST_F(FromRangeTest_941, VectorOfInts_ReturnsElementsInOrder_941) {
    std::vector<int> v = {10, 20, 30};
    auto gen = from_range(v.begin(), v.end());

    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_FALSE(gen.next());
}

// Normal operation: from_range with a single element
TEST_F(FromRangeTest_941, SingleElement_941) {
    std::vector<int> v = {42};
    auto gen = from_range(v.begin(), v.end());

    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());
}

// Boundary: from_range with empty range should throw or handle gracefully
TEST_F(FromRangeTest_941, EmptyRange_ThrowsOnConstruction_941) {
    std::vector<int> v;
    EXPECT_THROW(from_range(v.begin(), v.end()), Catch::GeneratorException);
}

// Normal operation: from_range with strings
TEST_F(FromRangeTest_941, VectorOfStrings_941) {
    std::vector<std::string> v = {"hello", "world"};
    auto gen = from_range(v.begin(), v.end());

    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

// Normal operation: from_range with a list (bidirectional iterator)
TEST_F(FromRangeTest_941, ListIterator_941) {
    std::list<int> lst = {1, 2, 3, 4};
    auto gen = from_range(lst.begin(), lst.end());

    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_FALSE(gen.next());
}

// Normal operation: from_range with a set (ordered elements)
TEST_F(FromRangeTest_941, SetIterator_941) {
    std::set<int> s = {3, 1, 2};
    auto gen = from_range(s.begin(), s.end());

    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

// Normal operation: from_range with array pointers (raw iterators)
TEST_F(FromRangeTest_941, RawPointerIterators_941) {
    int arr[] = {100, 200, 300};
    auto gen = from_range(std::begin(arr), std::end(arr));

    EXPECT_EQ(gen.get(), 100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 300);
    EXPECT_FALSE(gen.next());
}

// Normal operation: from_range with const iterators
TEST_F(FromRangeTest_941, ConstIterators_941) {
    const std::vector<double> v = {1.5, 2.5, 3.5};
    auto gen = from_range(v.cbegin(), v.cend());

    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.5);
    EXPECT_FALSE(gen.next());
}

// Boundary: large range
TEST_F(FromRangeTest_941, LargeRange_941) {
    std::vector<int> v(1000);
    for (int i = 0; i < 1000; ++i) v[i] = i;
    auto gen = from_range(v.begin(), v.end());

    for (int i = 0; i < 999; ++i) {
        EXPECT_EQ(gen.get(), i);
        EXPECT_TRUE(gen.next());
    }
    EXPECT_EQ(gen.get(), 999);
    EXPECT_FALSE(gen.next());
}

// Normal operation: get() returns same value when called multiple times without next()
TEST_F(FromRangeTest_941, GetWithoutNextReturnsSameValue_941) {
    std::vector<int> v = {5, 10};
    auto gen = from_range(v.begin(), v.end());

    EXPECT_EQ(gen.get(), 5);
    EXPECT_EQ(gen.get(), 5);
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 10);
    EXPECT_EQ(gen.get(), 10);
}

// Normal operation: from_range with std::array
TEST_F(FromRangeTest_941, StdArrayIterator_941) {
    std::array<int, 3> arr = {7, 8, 9};
    auto gen = from_range(arr.begin(), arr.end());

    EXPECT_EQ(gen.get(), 7);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 8);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);
    EXPECT_FALSE(gen.next());
}

// Boundary: two elements
TEST_F(FromRangeTest_941, TwoElements_941) {
    std::vector<int> v = {1, 2};
    auto gen = from_range(v.begin(), v.end());

    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_FALSE(gen.next());
}

// Type deduction: ResultType should be value_type without const
TEST_F(FromRangeTest_941, TypeDeductionFromConstVector_941) {
    const std::vector<int> v = {11, 22};
    auto gen = from_range(v.begin(), v.end());

    static_assert(std::is_same_v<decltype(gen.get()), int const&> ||
                  std::is_same_v<decltype(gen.get()), int&> ||
                  std::is_same_v<decltype(gen.get()), int>,
                  "ResultType should be deduced correctly");
    EXPECT_EQ(gen.get(), 11);
}
