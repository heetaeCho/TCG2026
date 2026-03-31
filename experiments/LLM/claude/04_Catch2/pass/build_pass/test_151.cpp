#include <gtest/gtest.h>
#include <array>
#include <utility>
#include <string>
#include <cstddef>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

using namespace Catch::Matchers::Detail;

class MatchAllOfTest_151 : public ::testing::Test {
protected:
};

// Test that match_all_of with empty index_sequence and empty array returns true
TEST_F(MatchAllOfTest_151, EmptyArrayEmptySequenceReturnsTrue_151) {
    std::array<void const*, 0> arr{};
    int arg = 42;
    bool result = match_all_of<0>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with a non-empty array but empty index_sequence still returns true
TEST_F(MatchAllOfTest_151, NonEmptyArrayEmptySequenceReturnsTrue_151) {
    int dummy = 10;
    std::array<void const*, 1> arr{ {&dummy} };
    int arg = 42;
    bool result = match_all_of<1>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with larger array but empty index_sequence returns true
TEST_F(MatchAllOfTest_151, LargerArrayEmptySequenceReturnsTrue_151) {
    int d1 = 1, d2 = 2, d3 = 3;
    std::array<void const*, 3> arr{ {&d1, &d2, &d3} };
    double arg = 3.14;
    bool result = match_all_of<3>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with string argument type
TEST_F(MatchAllOfTest_151, StringArgEmptySequenceReturnsTrue_151) {
    std::array<void const*, 0> arr{};
    std::string arg = "hello";
    bool result = match_all_of<0>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with rvalue argument
TEST_F(MatchAllOfTest_151, RvalueArgEmptySequenceReturnsTrue_151) {
    std::array<void const*, 0> arr{};
    bool result = match_all_of<0>(42, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with const lvalue argument
TEST_F(MatchAllOfTest_151, ConstLvalueArgEmptySequenceReturnsTrue_151) {
    std::array<void const*, 0> arr{};
    const int arg = 100;
    bool result = match_all_of<0>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with nullptr entries in array but empty index_sequence
TEST_F(MatchAllOfTest_151, NullptrEntriesEmptySequenceReturnsTrue_151) {
    std::array<void const*, 2> arr{ {nullptr, nullptr} };
    int arg = 0;
    bool result = match_all_of<2>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with const reference to array
TEST_F(MatchAllOfTest_151, ConstRefArrayEmptySequenceReturnsTrue_151) {
    std::array<void const*, 0> arr{};
    const auto& constArr = arr;
    float arg = 1.0f;
    bool result = match_all_of<0>(arg, constArr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with pointer argument type
TEST_F(MatchAllOfTest_151, PointerArgEmptySequenceReturnsTrue_151) {
    std::array<void const*, 0> arr{};
    int val = 5;
    int* arg = &val;
    bool result = match_all_of<0>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// Test with large N array but empty sequence
TEST_F(MatchAllOfTest_151, LargeNArrayEmptySequenceReturnsTrue_151) {
    std::array<void const*, 10> arr{};
    int arg = 0;
    bool result = match_all_of<10>(arg, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}
