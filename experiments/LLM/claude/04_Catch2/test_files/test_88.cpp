#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <array>
#include <deque>

#include "catch2/catch_tostring.hpp"

// Test with empty range
TEST(RangeToStringTest_88, EmptyRange_88) {
    std::vector<int> empty;
    std::string result = Catch::Detail::rangeToString(empty.begin(), empty.end());
    EXPECT_EQ(result, "{  }");
}

// Test with single element
TEST(RangeToStringTest_88, SingleElement_88) {
    std::vector<int> single = {42};
    std::string result = Catch::Detail::rangeToString(single.begin(), single.end());
    EXPECT_EQ(result, "{ 42 }");
}

// Test with multiple integers
TEST(RangeToStringTest_88, MultipleIntegers_88) {
    std::vector<int> vec = {1, 2, 3};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_EQ(result, "{ 1, 2, 3 }");
}

// Test with two elements
TEST(RangeToStringTest_88, TwoElements_88) {
    std::vector<int> vec = {10, 20};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_EQ(result, "{ 10, 20 }");
}

// Test with negative integers
TEST(RangeToStringTest_88, NegativeIntegers_88) {
    std::vector<int> vec = {-1, -2, -3};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_EQ(result, "{ -1, -2, -3 }");
}

// Test with strings
TEST(RangeToStringTest_88, StringElements_88) {
    std::vector<std::string> vec = {"hello", "world"};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("world"), std::string::npos);
    EXPECT_EQ(result.front(), '{');
    EXPECT_EQ(result.back(), '}');
}

// Test with list container (non-random-access iterator)
TEST(RangeToStringTest_88, ListIterator_88) {
    std::list<int> lst = {5, 10, 15};
    std::string result = Catch::Detail::rangeToString(lst.begin(), lst.end());
    EXPECT_EQ(result, "{ 5, 10, 15 }");
}

// Test with set container (ordered, bidirectional iterator)
TEST(RangeToStringTest_88, SetIterator_88) {
    std::set<int> s = {3, 1, 2};
    std::string result = Catch::Detail::rangeToString(s.begin(), s.end());
    EXPECT_EQ(result, "{ 1, 2, 3 }");
}

// Test with floating point values
TEST(RangeToStringTest_88, FloatingPointElements_88) {
    std::vector<double> vec = {1.5, 2.5};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_NE(result.find("1.5"), std::string::npos);
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

// Test with boolean values
TEST(RangeToStringTest_88, BooleanElements_88) {
    std::vector<bool> vec = {true, false, true};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test with large number of elements
TEST(RangeToStringTest_88, LargeRange_88) {
    std::vector<int> vec(100);
    for (int i = 0; i < 100; ++i) vec[i] = i;
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_EQ(result.substr(0, 2), "{ ");
    EXPECT_EQ(result.substr(result.size() - 2), " }");
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("99"), std::string::npos);
}

// Test with array iterators
TEST(RangeToStringTest_88, CArrayIterator_88) {
    int arr[] = {7, 8, 9};
    std::string result = Catch::Detail::rangeToString(std::begin(arr), std::end(arr));
    EXPECT_EQ(result, "{ 7, 8, 9 }");
}

// Test with deque
TEST(RangeToStringTest_88, DequeIterator_88) {
    std::deque<int> dq = {100, 200, 300};
    std::string result = Catch::Detail::rangeToString(dq.begin(), dq.end());
    EXPECT_EQ(result, "{ 100, 200, 300 }");
}

// Test result always starts with "{ " and ends with " }"
TEST(RangeToStringTest_88, FormatConsistency_88) {
    std::vector<int> vec = {1};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_GE(result.size(), 4u);
    EXPECT_EQ(result.substr(0, 2), "{ ");
    EXPECT_EQ(result.substr(result.size() - 2), " }");
}

// Test empty range format consistency
TEST(RangeToStringTest_88, EmptyRangeFormat_88) {
    std::vector<int> empty;
    std::string result = Catch::Detail::rangeToString(empty.begin(), empty.end());
    EXPECT_GE(result.size(), 4u);
    EXPECT_EQ(result.substr(0, 2), "{ ");
    EXPECT_EQ(result.substr(result.size() - 2), " }");
}

// Test with char elements
TEST(RangeToStringTest_88, CharElements_88) {
    std::vector<char> vec = {'a', 'b', 'c'};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.end());
    EXPECT_NE(result.find("'a'"), std::string::npos);
    EXPECT_NE(result.find("'b'"), std::string::npos);
    EXPECT_NE(result.find("'c'"), std::string::npos);
}

// Test partial range
TEST(RangeToStringTest_88, PartialRange_88) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string result = Catch::Detail::rangeToString(vec.begin() + 1, vec.begin() + 4);
    EXPECT_EQ(result, "{ 2, 3, 4 }");
}

// Test with same begin and end (empty)
TEST(RangeToStringTest_88, SameBeginEnd_88) {
    std::vector<int> vec = {1, 2, 3};
    std::string result = Catch::Detail::rangeToString(vec.begin(), vec.begin());
    EXPECT_EQ(result, "{  }");
}
