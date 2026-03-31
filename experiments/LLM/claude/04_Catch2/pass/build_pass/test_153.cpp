#include <gtest/gtest.h>
#include <array>
#include <utility>
#include <cstddef>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

class MatchAnyOfTest_153 : public ::testing::Test {
protected:
    // Helper to call the function under test
    template<std::size_t N, typename Arg>
    bool callMatchAnyOf(Arg&& arg, const std::array<void const*, N>& arr) {
        return Catch::Matchers::Detail::match_any_of<N>(
            std::forward<Arg>(arg), arr, std::index_sequence<>{});
    }
};

// Test that match_any_of with empty index_sequence returns false for empty array
TEST_F(MatchAnyOfTest_153, EmptyArrayReturnsFalse_153) {
    std::array<void const*, 0> arr{};
    int value = 42;
    bool result = Catch::Matchers::Detail::match_any_of<0>(value, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test that match_any_of with empty index_sequence returns false for non-empty array
TEST_F(MatchAnyOfTest_153, NonEmptyArrayEmptySequenceReturnsFalse_153) {
    int dummy = 10;
    std::array<void const*, 1> arr{ {static_cast<void const*>(&dummy)} };
    int value = 42;
    bool result = Catch::Matchers::Detail::match_any_of<1>(value, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test with a larger array but still empty index_sequence
TEST_F(MatchAnyOfTest_153, LargerArrayEmptySequenceReturnsFalse_153) {
    int d1 = 1, d2 = 2, d3 = 3;
    std::array<void const*, 3> arr{ {
        static_cast<void const*>(&d1),
        static_cast<void const*>(&d2),
        static_cast<void const*>(&d3)
    } };
    int value = 100;
    bool result = Catch::Matchers::Detail::match_any_of<3>(value, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test with lvalue reference argument
TEST_F(MatchAnyOfTest_153, LvalueArgReturnsFalse_153) {
    std::array<void const*, 0> arr{};
    std::string value = "test";
    bool result = Catch::Matchers::Detail::match_any_of<0>(value, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test with rvalue reference argument
TEST_F(MatchAnyOfTest_153, RvalueArgReturnsFalse_153) {
    std::array<void const*, 0> arr{};
    bool result = Catch::Matchers::Detail::match_any_of<0>(42, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test with const lvalue argument
TEST_F(MatchAnyOfTest_153, ConstLvalueArgReturnsFalse_153) {
    std::array<void const*, 0> arr{};
    const double value = 3.14;
    bool result = Catch::Matchers::Detail::match_any_of<0>(value, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test with nullptr entries in array still returns false with empty sequence
TEST_F(MatchAnyOfTest_153, NullptrEntriesEmptySequenceReturnsFalse_153) {
    std::array<void const*, 2> arr{ {nullptr, nullptr} };
    int value = 0;
    bool result = Catch::Matchers::Detail::match_any_of<2>(value, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test with different argument types - pointer type
TEST_F(MatchAnyOfTest_153, PointerArgReturnsFalse_153) {
    std::array<void const*, 0> arr{};
    int x = 5;
    int* value = &x;
    bool result = Catch::Matchers::Detail::match_any_of<0>(value, arr, std::index_sequence<>{});
    EXPECT_FALSE(result);
}

// Test return type is bool
TEST_F(MatchAnyOfTest_153, ReturnTypeIsBool_153) {
    std::array<void const*, 0> arr{};
    int value = 0;
    auto result = Catch::Matchers::Detail::match_any_of<0>(value, arr, std::index_sequence<>{});
    static_assert(std::is_same<decltype(result), bool>::value, "Return type must be bool");
    EXPECT_FALSE(result);
}
