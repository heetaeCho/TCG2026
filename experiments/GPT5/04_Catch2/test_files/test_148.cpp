// File: array_cat_tests_148.cpp

#include <gtest/gtest.h>
#include <array>
#include <tuple>
#include <type_traits>

// Include the header under test (path from the prompt)
#include "catch2/matchers/catch_matchers_templated.hpp"

namespace CM = Catch::Matchers::Detail;

// Compile-time checks: result type size is N+M
static_assert(
    std::tuple_size<decltype(CM::array_cat(std::array<void const*, 1>{}, std::array<void const*, 2>{}))>::value == 3,
    "array_cat should produce array of size N+M");
static_assert(
    std::tuple_size<decltype(CM::array_cat(std::array<void const*, 0>{}, std::array<void const*, 0>{}))>::value == 0,
    "array_cat should handle zero-sized arrays");

// No fixture needed, but keeping consistent suite naming with TEST_ID
using ArrayCatTest_148 = ::testing::Test;

TEST(ArrayCatTest_148, ConcatenatesBothNonEmpty_148) {
    static int a = 1, b = 2, c = 3, d = 4;
    std::array<void const*, 2> lhs{ &a, &b };
    std::array<void const*, 2> rhs{ &c, &d };

    auto result = CM::array_cat(std::move(lhs), std::move(rhs));

    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], &a);
    EXPECT_EQ(result[1], &b);
    EXPECT_EQ(result[2], &c);
    EXPECT_EQ(result[3], &d);
}

TEST(ArrayCatTest_148, LeftEmptyRightNonEmpty_148) {
    static int x = 42, y = 43;
    std::array<void const*, 0> lhs{};
    std::array<void const*, 2> rhs{ &x, &y };

    auto result = CM::array_cat(std::move(lhs), std::move(rhs));

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], &x);
    EXPECT_EQ(result[1], &y);
}

TEST(ArrayCatTest_148, LeftNonEmptyRightEmpty_148) {
    static int x = 11, y = 22;
    std::array<void const*, 2> lhs{ &x, &y };
    std::array<void const*, 0> rhs{};

    auto result = CM::array_cat(std::move(lhs), std::move(rhs));

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], &x);
    EXPECT_EQ(result[1], &y);
}

TEST(ArrayCatTest_148, BothEmpty_148) {
    std::array<void const*, 0> lhs{};
    std::array<void const*, 0> rhs{};

    auto result = CM::array_cat(std::move(lhs), std::move(rhs));

    EXPECT_EQ(result.size(), 0u);
    // No element access — zero-sized container.
}

TEST(ArrayCatTest_148, PreservesNullptrElementsAndOrder_148) {
    static int a = 7;
    void const* pnull = nullptr;

    std::array<void const*, 3> lhs{ pnull, &a, pnull };
    std::array<void const*, 1> rhs{ pnull };

    auto result = CM::array_cat(std::move(lhs), std::move(rhs));

    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], nullptr);
    EXPECT_EQ(result[1], &a);
    EXPECT_EQ(result[2], nullptr);
    EXPECT_EQ(result[3], nullptr);
}

TEST(ArrayCatTest_148, WorksWithPointersFromDifferentTypes_148) {
    static int i = 1;
    static double d = 2.0;
    static char c = 'z';

    std::array<void const*, 1> lhs{ static_cast<void const*>(&i) };
    std::array<void const*, 2> rhs{ static_cast<void const*>(&d), static_cast<void const*>(&c) };

    auto result = CM::array_cat(std::move(lhs), std::move(rhs));

    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], &i);
    EXPECT_EQ(result[1], &d);
    EXPECT_EQ(result[2], &c);
}
