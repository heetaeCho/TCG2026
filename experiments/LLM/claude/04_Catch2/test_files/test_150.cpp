#include <gtest/gtest.h>
#include <array>
#include <cstddef>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

namespace {

// Test fixture
class ArrayCatTest_150 : public ::testing::Test {
protected:
    int dummy1 = 42;
    int dummy2 = 84;
    int dummy3 = 126;
    double dummy4 = 3.14;
    char dummy5 = 'x';
};

// Test with N=0: concatenating a single pointer with an empty array
TEST_F(ArrayCatTest_150, CatWithEmptyArray_150) {
    void const* lhs = &dummy1;
    std::array<void const*, 0> rhs{};
    
    auto result = Catch::Matchers::Detail::array_cat<0>(lhs, std::move(rhs));
    
    static_assert(std::is_same<decltype(result), std::array<void const*, 1>>::value,
                  "Result should be std::array<void const*, 1>");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], lhs);
}

// Test with N=1: concatenating a pointer with a single-element array
TEST_F(ArrayCatTest_150, CatWithSingleElementArray_150) {
    void const* lhs = &dummy1;
    std::array<void const*, 1> rhs{{ &dummy2 }};
    
    auto result = Catch::Matchers::Detail::array_cat<1>(lhs, std::move(rhs));
    
    static_assert(std::is_same<decltype(result), std::array<void const*, 2>>::value,
                  "Result should be std::array<void const*, 2>");
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], static_cast<void const*>(&dummy1));
    EXPECT_EQ(result[1], static_cast<void const*>(&dummy2));
}

// Test with N=2: concatenating a pointer with a two-element array
TEST_F(ArrayCatTest_150, CatWithTwoElementArray_150) {
    void const* lhs = &dummy1;
    std::array<void const*, 2> rhs{{ &dummy2, &dummy3 }};
    
    auto result = Catch::Matchers::Detail::array_cat<2>(lhs, std::move(rhs));
    
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], static_cast<void const*>(&dummy1));
    EXPECT_EQ(result[1], static_cast<void const*>(&dummy2));
    EXPECT_EQ(result[2], static_cast<void const*>(&dummy3));
}

// Test with N=4: larger array
TEST_F(ArrayCatTest_150, CatWithFourElementArray_150) {
    int a = 1, b = 2, c = 3, d = 4;
    void const* lhs = &dummy1;
    std::array<void const*, 4> rhs{{ &a, &b, &c, &d }};
    
    auto result = Catch::Matchers::Detail::array_cat<4>(lhs, std::move(rhs));
    
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], static_cast<void const*>(&dummy1));
    EXPECT_EQ(result[1], static_cast<void const*>(&a));
    EXPECT_EQ(result[2], static_cast<void const*>(&b));
    EXPECT_EQ(result[3], static_cast<void const*>(&c));
    EXPECT_EQ(result[4], static_cast<void const*>(&d));
}

// Test with nullptr as lhs
TEST_F(ArrayCatTest_150, CatWithNullptrLhs_150) {
    void const* lhs = nullptr;
    std::array<void const*, 2> rhs{{ &dummy1, &dummy2 }};
    
    auto result = Catch::Matchers::Detail::array_cat<2>(lhs, std::move(rhs));
    
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], nullptr);
    EXPECT_EQ(result[1], static_cast<void const*>(&dummy1));
    EXPECT_EQ(result[2], static_cast<void const*>(&dummy2));
}

// Test with nullptr elements in rhs
TEST_F(ArrayCatTest_150, CatWithNullptrInRhs_150) {
    void const* lhs = &dummy1;
    std::array<void const*, 3> rhs{{ nullptr, &dummy2, nullptr }};
    
    auto result = Catch::Matchers::Detail::array_cat<3>(lhs, std::move(rhs));
    
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], static_cast<void const*>(&dummy1));
    EXPECT_EQ(result[1], nullptr);
    EXPECT_EQ(result[2], static_cast<void const*>(&dummy2));
    EXPECT_EQ(result[3], nullptr);
}

// Test with different pointer types (all cast to void const*)
TEST_F(ArrayCatTest_150, CatWithDifferentPointerTypes_150) {
    void const* lhs = &dummy4;  // double*
    std::array<void const*, 2> rhs{{ &dummy1, &dummy5 }};  // int*, char*
    
    auto result = Catch::Matchers::Detail::array_cat<2>(lhs, std::move(rhs));
    
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], static_cast<void const*>(&dummy4));
    EXPECT_EQ(result[1], static_cast<void const*>(&dummy1));
    EXPECT_EQ(result[2], static_cast<void const*>(&dummy5));
}

// Test that the order is preserved: lhs is always first
TEST_F(ArrayCatTest_150, OrderPreservation_150) {
    int values[5] = {10, 20, 30, 40, 50};
    void const* lhs = &values[0];
    std::array<void const*, 4> rhs{{
        &values[1], &values[2], &values[3], &values[4]
    }};
    
    auto result = Catch::Matchers::Detail::array_cat<4>(lhs, std::move(rhs));
    
    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result[i], static_cast<void const*>(&values[i]))
            << "Mismatch at index " << i;
    }
}

// Test that all nullptr array works
TEST_F(ArrayCatTest_150, AllNullptrs_150) {
    void const* lhs = nullptr;
    std::array<void const*, 3> rhs{{ nullptr, nullptr, nullptr }};
    
    auto result = Catch::Matchers::Detail::array_cat<3>(lhs, std::move(rhs));
    
    EXPECT_EQ(result.size(), 4u);
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(result[i], nullptr) << "Expected nullptr at index " << i;
    }
}

// Test result type correctness for various N values
TEST_F(ArrayCatTest_150, ResultTypeSizeCorrectness_150) {
    {
        std::array<void const*, 0> rhs{};
        auto result = Catch::Matchers::Detail::array_cat<0>(nullptr, std::move(rhs));
        EXPECT_EQ(result.size(), 1u);
    }
    {
        std::array<void const*, 1> rhs{{ nullptr }};
        auto result = Catch::Matchers::Detail::array_cat<1>(nullptr, std::move(rhs));
        EXPECT_EQ(result.size(), 2u);
    }
    {
        std::array<void const*, 5> rhs{{ nullptr, nullptr, nullptr, nullptr, nullptr }};
        auto result = Catch::Matchers::Detail::array_cat<5>(nullptr, std::move(rhs));
        EXPECT_EQ(result.size(), 6u);
    }
}

} // anonymous namespace
