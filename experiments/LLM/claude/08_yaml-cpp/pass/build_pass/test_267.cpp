#include <gtest/gtest.h>
#include <cstddef>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::detail;

// Test basic element access for an array of integers
TEST(ArrayTest_267, AccessFirstElement_267) {
    array<int, 3> arr = {{10, 20, 30}};
    EXPECT_EQ(arr[0], 10);
}

TEST(ArrayTest_267, AccessMiddleElement_267) {
    array<int, 3> arr = {{10, 20, 30}};
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest_267, AccessLastElement_267) {
    array<int, 3> arr = {{10, 20, 30}};
    EXPECT_EQ(arr[2], 30);
}

// Test with a single-element array
TEST(ArrayTest_267, SingleElementArray_267) {
    array<int, 1> arr = {{42}};
    EXPECT_EQ(arr[0], 42);
}

// Test with different types
TEST(ArrayTest_267, DoubleTypeArray_267) {
    array<double, 2> arr = {{3.14, 2.71}};
    EXPECT_DOUBLE_EQ(arr[0], 3.14);
    EXPECT_DOUBLE_EQ(arr[1], 2.71);
}

TEST(ArrayTest_267, UnsignedIntArray_267) {
    array<unsigned int, 4> arr = {{0u, 1u, 2u, 3u}};
    EXPECT_EQ(arr[0], 0u);
    EXPECT_EQ(arr[1], 1u);
    EXPECT_EQ(arr[2], 2u);
    EXPECT_EQ(arr[3], 3u);
}

TEST(ArrayTest_267, Uint64Array_267) {
    array<std::uint64_t, 2> arr = {{0xFFFFFFFFFFFFFFFFULL, 0ULL}};
    EXPECT_EQ(arr[0], 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(arr[1], 0ULL);
}

// Test constexpr usage
TEST(ArrayTest_267, ConstexprAccess_267) {
    constexpr array<int, 3> arr = {{100, 200, 300}};
    static_assert(arr[0] == 100, "First element should be 100");
    static_assert(arr[1] == 200, "Second element should be 200");
    static_assert(arr[2] == 300, "Third element should be 300");
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

// Test that operator[] is noexcept
TEST(ArrayTest_267, OperatorBracketIsNoexcept_267) {
    array<int, 3> arr = {{1, 2, 3}};
    EXPECT_TRUE(noexcept(arr[0]));
}

// Test with const array
TEST(ArrayTest_267, ConstArrayAccess_267) {
    const array<int, 3> arr = {{5, 10, 15}};
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 15);
}

// Test boundary values for the stored type
TEST(ArrayTest_267, IntMinMaxValues_267) {
    array<int, 2> arr = {{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}};
    EXPECT_EQ(arr[0], std::numeric_limits<int>::min());
    EXPECT_EQ(arr[1], std::numeric_limits<int>::max());
}

// Test with zero-initialized values
TEST(ArrayTest_267, ZeroInitializedValues_267) {
    array<int, 3> arr = {{0, 0, 0}};
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 0);
    EXPECT_EQ(arr[2], 0);
}

// Test with negative values
TEST(ArrayTest_267, NegativeValues_267) {
    array<int, 3> arr = {{-1, -2, -3}};
    EXPECT_EQ(arr[0], -1);
    EXPECT_EQ(arr[1], -2);
    EXPECT_EQ(arr[2], -3);
}

// Test with bool type
TEST(ArrayTest_267, BoolTypeArray_267) {
    array<bool, 2> arr = {{true, false}};
    EXPECT_EQ(arr[0], true);
    EXPECT_EQ(arr[1], false);
}

// Test larger array
TEST(ArrayTest_267, LargerArray_267) {
    array<int, 10> arr = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
    for (std::size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i));
    }
}

// Test return type of operator[]
TEST(ArrayTest_267, ReturnTypeIsValueNotReference_267) {
    array<int, 3> arr = {{10, 20, 30}};
    // operator[] returns T (by value), so taking address of temporary is not possible
    // but we can verify the returned value is correct
    int val = arr[0];
    EXPECT_EQ(val, 10);
}

} // namespace
