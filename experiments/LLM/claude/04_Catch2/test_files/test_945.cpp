#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <forward_list>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Test fixture
class SentinelDistanceTest_945 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: distance of a non-empty vector
TEST_F(SentinelDistanceTest_945, VectorNonEmpty_945) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto dist = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(dist, 5);
}

// Boundary: empty container should return 0
TEST_F(SentinelDistanceTest_945, EmptyContainer_945) {
    std::vector<int> v;
    auto dist = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(dist, 0);
}

// Normal operation: single element container
TEST_F(SentinelDistanceTest_945, SingleElement_945) {
    std::vector<int> v = {42};
    auto dist = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(dist, 1);
}

// Normal operation: works with list (bidirectional iterator)
TEST_F(SentinelDistanceTest_945, ListContainer_945) {
    std::list<int> lst = {10, 20, 30};
    auto dist = Catch::Detail::sentinel_distance(lst.begin(), lst.end());
    EXPECT_EQ(dist, 3);
}

// Normal operation: works with forward_list (forward iterator)
TEST_F(SentinelDistanceTest_945, ForwardListContainer_945) {
    std::forward_list<int> flst = {1, 2, 3, 4};
    auto dist = Catch::Detail::sentinel_distance(flst.begin(), flst.end());
    EXPECT_EQ(dist, 4);
}

// Normal operation: works with string
TEST_F(SentinelDistanceTest_945, StringIterators_945) {
    std::string s = "hello";
    auto dist = Catch::Detail::sentinel_distance(s.begin(), s.end());
    EXPECT_EQ(dist, 5);
}

// Boundary: empty string
TEST_F(SentinelDistanceTest_945, EmptyString_945) {
    std::string s;
    auto dist = Catch::Detail::sentinel_distance(s.begin(), s.end());
    EXPECT_EQ(dist, 0);
}

// Normal operation: partial range
TEST_F(SentinelDistanceTest_945, PartialRange_945) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin();
    ++it; // points to 2
    auto dist = Catch::Detail::sentinel_distance(it, v.end());
    EXPECT_EQ(dist, 4);
}

// Normal operation: iterator equals sentinel (same position, non-empty container)
TEST_F(SentinelDistanceTest_945, IteratorEqualsSentinel_945) {
    std::vector<int> v = {1, 2, 3};
    auto dist = Catch::Detail::sentinel_distance(v.end(), v.end());
    EXPECT_EQ(dist, 0);
}

// Normal operation: works with const iterators
TEST_F(SentinelDistanceTest_945, ConstIterators_945) {
    const std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    auto dist = Catch::Detail::sentinel_distance(v.cbegin(), v.cend());
    EXPECT_EQ(dist, 7);
}

// Normal operation: large container
TEST_F(SentinelDistanceTest_945, LargeContainer_945) {
    std::vector<int> v(10000, 0);
    auto dist = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(dist, 10000);
}

// Normal operation: works with array pointers (pointers are forward iterators)
TEST_F(SentinelDistanceTest_945, RawPointers_945) {
    int arr[] = {1, 2, 3, 4, 5};
    int* begin = arr;
    int* end = arr + 5;
    auto dist = Catch::Detail::sentinel_distance(begin, end);
    EXPECT_EQ(dist, 5);
}

// Boundary: raw pointer to single element
TEST_F(SentinelDistanceTest_945, RawPointerSingleElement_945) {
    int val = 99;
    int* begin = &val;
    int* end = &val + 1;
    auto dist = Catch::Detail::sentinel_distance(begin, end);
    EXPECT_EQ(dist, 1);
}

// Boundary: raw pointer empty range
TEST_F(SentinelDistanceTest_945, RawPointerEmptyRange_945) {
    int arr[] = {1};
    int* p = arr;
    auto dist = Catch::Detail::sentinel_distance(p, p);
    EXPECT_EQ(dist, 0);
}

// Normal: return type is std::ptrdiff_t
TEST_F(SentinelDistanceTest_945, ReturnTypeIsPtrdiffT_945) {
    std::vector<int> v = {1, 2, 3};
    auto dist = Catch::Detail::sentinel_distance(v.begin(), v.end());
    static_assert(std::is_same<decltype(dist), std::ptrdiff_t>::value,
                  "Return type should be std::ptrdiff_t");
    EXPECT_EQ(dist, 3);
}

// Normal operation: two elements
TEST_F(SentinelDistanceTest_945, TwoElements_945) {
    std::vector<double> v = {1.0, 2.0};
    auto dist = Catch::Detail::sentinel_distance(v.begin(), v.end());
    EXPECT_EQ(dist, 2);
}

// Normal operation: forward_list empty
TEST_F(SentinelDistanceTest_945, EmptyForwardList_945) {
    std::forward_list<int> flst;
    auto dist = Catch::Detail::sentinel_distance(flst.begin(), flst.end());
    EXPECT_EQ(dist, 0);
}
