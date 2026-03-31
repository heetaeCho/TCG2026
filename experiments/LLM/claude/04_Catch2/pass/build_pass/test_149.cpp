#include <gtest/gtest.h>
#include <array>
#include <cstddef>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::array_cat;

// Test that array_cat with N=0 produces an array of size 1 containing the appended element
TEST(ArrayCatTest_149, AppendToEmptyArray_149) {
    std::array<void const*, 0> empty{};
    int dummy = 42;
    void const* rhs = &dummy;

    auto result = array_cat(std::move(empty), rhs);

    static_assert(std::is_same<decltype(result), std::array<void const*, 1>>::value,
                  "Result should be std::array<void const*, 1>");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], rhs);
}

// Test that array_cat with N=1 produces an array of size 2 with correct elements
TEST(ArrayCatTest_149, AppendToSingleElementArray_149) {
    int a = 1;
    int b = 2;
    std::array<void const*, 1> arr = { &a };
    void const* rhs = &b;

    auto result = array_cat(std::move(arr), rhs);

    static_assert(std::is_same<decltype(result), std::array<void const*, 2>>::value,
                  "Result should be std::array<void const*, 2>");
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], static_cast<void const*>(&a));
    EXPECT_EQ(result[1], static_cast<void const*>(&b));
}

// Test that array_cat with N=3 produces an array of size 4 with all elements preserved
TEST(ArrayCatTest_149, AppendToThreeElementArray_149) {
    int vals[4];
    std::array<void const*, 3> arr = { &vals[0], &vals[1], &vals[2] };
    void const* rhs = &vals[3];

    auto result = array_cat(std::move(arr), rhs);

    static_assert(std::is_same<decltype(result), std::array<void const*, 4>>::value,
                  "Result should be std::array<void const*, 4>");
    EXPECT_EQ(result.size(), 4u);
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(result[i], static_cast<void const*>(&vals[i]));
    }
    EXPECT_EQ(result[3], static_cast<void const*>(&vals[3]));
}

// Test that appending nullptr works correctly
TEST(ArrayCatTest_149, AppendNullptr_149) {
    int a = 10;
    std::array<void const*, 1> arr = { &a };

    auto result = array_cat(std::move(arr), nullptr);

    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], static_cast<void const*>(&a));
    EXPECT_EQ(result[1], nullptr);
}

// Test that all nullptrs in the input array and rhs are handled
TEST(ArrayCatTest_149, AllNullptrs_149) {
    std::array<void const*, 2> arr = { nullptr, nullptr };

    auto result = array_cat(std::move(arr), nullptr);

    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], nullptr);
    EXPECT_EQ(result[1], nullptr);
    EXPECT_EQ(result[2], nullptr);
}

// Test with a larger array (N=5) to verify scalability
TEST(ArrayCatTest_149, AppendToFiveElementArray_149) {
    int vals[6];
    std::array<void const*, 5> arr = {
        &vals[0], &vals[1], &vals[2], &vals[3], &vals[4]
    };
    void const* rhs = &vals[5];

    auto result = array_cat(std::move(arr), rhs);

    static_assert(std::is_same<decltype(result), std::array<void const*, 6>>::value,
                  "Result should be std::array<void const*, 6>");
    EXPECT_EQ(result.size(), 6u);
    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result[i], static_cast<void const*>(&vals[i]));
    }
    EXPECT_EQ(result[5], static_cast<void const*>(&vals[5]));
}

// Test that the original array elements are preserved (order matters)
TEST(ArrayCatTest_149, PreservesOrderOfElements_149) {
    int a = 1, b = 2, c = 3, d = 4;
    std::array<void const*, 3> arr = { &a, &b, &c };
    void const* rhs = &d;

    auto result = array_cat(std::move(arr), rhs);

    // Verify exact ordering
    EXPECT_EQ(result[0], static_cast<void const*>(&a));
    EXPECT_EQ(result[1], static_cast<void const*>(&b));
    EXPECT_EQ(result[2], static_cast<void const*>(&c));
    EXPECT_EQ(result[3], static_cast<void const*>(&d));
}

// Test with mixed nullptr and non-nullptr elements
TEST(ArrayCatTest_149, MixedNullAndNonNullElements_149) {
    int val = 99;
    std::array<void const*, 3> arr = { nullptr, &val, nullptr };
    void const* rhs = &val;

    auto result = array_cat(std::move(arr), rhs);

    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], nullptr);
    EXPECT_EQ(result[1], static_cast<void const*>(&val));
    EXPECT_EQ(result[2], nullptr);
    EXPECT_EQ(result[3], static_cast<void const*>(&val));
}

// Test chaining: result of one array_cat can be fed into another
TEST(ArrayCatTest_149, ChainedArrayCat_149) {
    int a = 1, b = 2, c = 3;

    std::array<void const*, 0> empty{};
    auto step1 = array_cat(std::move(empty), &a);
    auto step2 = array_cat(std::move(step1), &b);
    auto step3 = array_cat(std::move(step2), &c);

    static_assert(std::is_same<decltype(step3), std::array<void const*, 3>>::value,
                  "Result should be std::array<void const*, 3>");
    EXPECT_EQ(step3.size(), 3u);
    EXPECT_EQ(step3[0], static_cast<void const*>(&a));
    EXPECT_EQ(step3[1], static_cast<void const*>(&b));
    EXPECT_EQ(step3[2], static_cast<void const*>(&c));
}
