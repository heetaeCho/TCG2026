#include <gtest/gtest.h>
#include <array>
#include <cstddef>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::array_cat;

// Test: Concatenating two empty arrays yields an empty array
TEST(ArrayCatTest_148, BothEmpty_148) {
    std::array<void const*, 0> lhs{};
    std::array<void const*, 0> rhs{};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    static_assert(std::is_same<decltype(result), std::array<void const*, 0>>::value, "");
    EXPECT_EQ(result.size(), 0u);
}

// Test: Concatenating a non-empty array with an empty array
TEST(ArrayCatTest_148, LeftNonEmptyRightEmpty_148) {
    int a = 1, b = 2, c = 3;
    std::array<void const*, 3> lhs = {&a, &b, &c};
    std::array<void const*, 0> rhs{};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], &a);
    EXPECT_EQ(result[1], &b);
    EXPECT_EQ(result[2], &c);
}

// Test: Concatenating an empty array with a non-empty array
TEST(ArrayCatTest_148, LeftEmptyRightNonEmpty_148) {
    int x = 10, y = 20;
    std::array<void const*, 0> lhs{};
    std::array<void const*, 2> rhs = {&x, &y};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], &x);
    EXPECT_EQ(result[1], &y);
}

// Test: Concatenating two non-empty arrays preserves order
TEST(ArrayCatTest_148, BothNonEmpty_148) {
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    std::array<void const*, 2> lhs = {&a, &b};
    std::array<void const*, 3> rhs = {&c, &d, &e};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], &a);
    EXPECT_EQ(result[1], &b);
    EXPECT_EQ(result[2], &c);
    EXPECT_EQ(result[3], &d);
    EXPECT_EQ(result[4], &e);
}

// Test: Single element arrays
TEST(ArrayCatTest_148, SingleElementArrays_148) {
    int a = 42, b = 99;
    std::array<void const*, 1> lhs = {&a};
    std::array<void const*, 1> rhs = {&b};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], &a);
    EXPECT_EQ(result[1], &b);
}

// Test: Nullptr elements are preserved correctly
TEST(ArrayCatTest_148, NullptrElements_148) {
    std::array<void const*, 2> lhs = {nullptr, nullptr};
    std::array<void const*, 1> rhs = {nullptr};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], nullptr);
    EXPECT_EQ(result[1], nullptr);
    EXPECT_EQ(result[2], nullptr);
}

// Test: Mixed nullptr and valid pointers
TEST(ArrayCatTest_148, MixedNullAndValid_148) {
    int val = 7;
    std::array<void const*, 2> lhs = {nullptr, &val};
    std::array<void const*, 2> rhs = {&val, nullptr};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], nullptr);
    EXPECT_EQ(result[1], &val);
    EXPECT_EQ(result[2], &val);
    EXPECT_EQ(result[3], nullptr);
}

// Test: Result type is correct for asymmetric sizes
TEST(ArrayCatTest_148, ResultTypeCorrectSize_148) {
    int a = 1;
    std::array<void const*, 1> lhs = {&a};
    std::array<void const*, 4> rhs = {&a, &a, &a, &a};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    static_assert(std::is_same<decltype(result), std::array<void const*, 5>>::value, "Result should be array of size N+M");
    ASSERT_EQ(result.size(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result[i], &a);
    }
}

// Test: Larger arrays to verify correctness at a bigger scale
TEST(ArrayCatTest_148, LargerArrays_148) {
    int vals[10];
    std::array<void const*, 5> lhs;
    std::array<void const*, 5> rhs;
    for (int i = 0; i < 5; ++i) {
        lhs[i] = &vals[i];
        rhs[i] = &vals[i + 5];
    }
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 10u);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(result[i], &vals[i]);
    }
}

// Test: Duplicate pointers are preserved
TEST(ArrayCatTest_148, DuplicatePointers_148) {
    int val = 42;
    std::array<void const*, 3> lhs = {&val, &val, &val};
    std::array<void const*, 2> rhs = {&val, &val};
    auto result = array_cat(std::move(lhs), std::move(rhs));
    ASSERT_EQ(result.size(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result[i], &val);
    }
}
