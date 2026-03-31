#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <array>
#include <deque>
#include <map>

// Include Catch2 headers needed for rangeToString
#include "catch2/catch_tostring.hpp"

// Test with empty vector
TEST(RangeToStringTest_89, EmptyVector_89) {
    std::vector<int> empty;
    std::string result = Catch::rangeToString(empty);
    // An empty range should produce some valid string output (e.g., "{ }" or "{}")
    EXPECT_FALSE(result.empty());
    // Typically Catch2 formats empty ranges as "{ }"
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

// Test with single element vector
TEST(RangeToStringTest_89, SingleElementVector_89) {
    std::vector<int> v = {42};
    std::string result = Catch::rangeToString(v);
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test with multiple integer elements
TEST(RangeToStringTest_89, MultipleIntElements_89) {
    std::vector<int> v = {1, 2, 3};
    std::string result = Catch::rangeToString(v);
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

// Test with string elements
TEST(RangeToStringTest_89, StringElements_89) {
    std::vector<std::string> v = {"hello", "world"};
    std::string result = Catch::rangeToString(v);
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("world"), std::string::npos);
}

// Test with list container
TEST(RangeToStringTest_89, ListContainer_89) {
    std::list<int> l = {10, 20, 30};
    std::string result = Catch::rangeToString(l);
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
    EXPECT_NE(result.find("30"), std::string::npos);
}

// Test with set container
TEST(RangeToStringTest_89, SetContainer_89) {
    std::set<int> s = {5, 10, 15};
    std::string result = Catch::rangeToString(s);
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("15"), std::string::npos);
}

// Test with array
TEST(RangeToStringTest_89, StdArray_89) {
    std::array<int, 3> arr = {100, 200, 300};
    std::string result = Catch::rangeToString(arr);
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find("200"), std::string::npos);
    EXPECT_NE(result.find("300"), std::string::npos);
}

// Test with deque container
TEST(RangeToStringTest_89, DequeContainer_89) {
    std::deque<int> d = {7, 8, 9};
    std::string result = Catch::rangeToString(d);
    EXPECT_NE(result.find("7"), std::string::npos);
    EXPECT_NE(result.find("8"), std::string::npos);
    EXPECT_NE(result.find("9"), std::string::npos);
}

// Test with negative numbers
TEST(RangeToStringTest_89, NegativeNumbers_89) {
    std::vector<int> v = {-1, -2, -3};
    std::string result = Catch::rangeToString(v);
    EXPECT_NE(result.find("-1"), std::string::npos);
    EXPECT_NE(result.find("-2"), std::string::npos);
    EXPECT_NE(result.find("-3"), std::string::npos);
}

// Test with floating point numbers
TEST(RangeToStringTest_89, FloatingPointNumbers_89) {
    std::vector<double> v = {1.5, 2.5};
    std::string result = Catch::rangeToString(v);
    EXPECT_NE(result.find("1.5"), std::string::npos);
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

// Test with boolean values
TEST(RangeToStringTest_89, BooleanValues_89) {
    std::vector<bool> v = {true, false, true};
    std::string result = Catch::rangeToString(v);
    // Result should be a non-empty formatted string
    EXPECT_FALSE(result.empty());
}

// Test that result contains braces (typical formatting)
TEST(RangeToStringTest_89, ResultContainsBraces_89) {
    std::vector<int> v = {1, 2, 3};
    std::string result = Catch::rangeToString(v);
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

// Test with large number of elements
TEST(RangeToStringTest_89, LargeNumberOfElements_89) {
    std::vector<int> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    std::string result = Catch::rangeToString(v);
    EXPECT_FALSE(result.empty());
    // At minimum the first element should appear
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test with single char elements
TEST(RangeToStringTest_89, CharElements_89) {
    std::vector<char> v = {'a', 'b', 'c'};
    std::string result = Catch::rangeToString(v);
    EXPECT_FALSE(result.empty());
}

// Test result is consistent for same input
TEST(RangeToStringTest_89, ConsistentResults_89) {
    std::vector<int> v = {1, 2, 3};
    std::string result1 = Catch::rangeToString(v);
    std::string result2 = Catch::rangeToString(v);
    EXPECT_EQ(result1, result2);
}

// Test with zero-sized std::array
TEST(RangeToStringTest_89, EmptyStdArray_89) {
    std::array<int, 0> arr = {};
    std::string result = Catch::rangeToString(arr);
    EXPECT_FALSE(result.empty());
}
