// File: ./TestProjects/tinyxml2/test_dynarray_clear_5.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"  // DynArray is declared here.

namespace {

template <typename T, size_t N>
using DynArray = tinyxml2::DynArray<T, N>;

class DynArrayClearTest_5 : public ::testing::Test {
protected:
    DynArray<int, 2> arr_int_;
    DynArray<std::string, 2> arr_str_;
};

TEST_F(DynArrayClearTest_5, ClearOnEmptyKeepsEmpty_5) {
    EXPECT_TRUE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.Size(), 0u);

    arr_int_.Clear();

    EXPECT_TRUE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.Size(), 0u);
}

TEST_F(DynArrayClearTest_5, ClearEmptiesArrayAfterPush_5) {
    arr_int_.Push(10);
    arr_int_.Push(20);

    ASSERT_FALSE(arr_int_.Empty());
    ASSERT_EQ(arr_int_.Size(), 2u);
    EXPECT_EQ(arr_int_.PeekTop(), 20);

    arr_int_.Clear();

    EXPECT_TRUE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.Size(), 0u);
}

TEST_F(DynArrayClearTest_5, ClearIsIdempotent_5) {
    arr_int_.Push(1);
    arr_int_.Push(2);

    arr_int_.Clear();
    EXPECT_TRUE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.Size(), 0u);

    // Calling Clear repeatedly should keep it empty (and not crash).
    arr_int_.Clear();
    arr_int_.Clear();
    EXPECT_TRUE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.Size(), 0u);
}

TEST_F(DynArrayClearTest_5, ClearAfterPushArrEmpties_5) {
    int* p = arr_int_.PushArr(3);
    ASSERT_NE(p, nullptr);

    // Fill the returned array slots (observable through Size()).
    p[0] = 7;
    p[1] = 8;
    p[2] = 9;

    ASSERT_EQ(arr_int_.Size(), 3u);
    ASSERT_FALSE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.PeekTop(), 9);

    arr_int_.Clear();

    EXPECT_TRUE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.Size(), 0u);
}

TEST_F(DynArrayClearTest_5, ClearAllowsReuseAfterClear_5) {
    arr_int_.Push(100);
    arr_int_.Push(200);
    ASSERT_EQ(arr_int_.Size(), 2u);

    arr_int_.Clear();
    ASSERT_TRUE(arr_int_.Empty());
    ASSERT_EQ(arr_int_.Size(), 0u);

    // Reuse after Clear should work through the public interface.
    arr_int_.Push(42);
    EXPECT_FALSE(arr_int_.Empty());
    EXPECT_EQ(arr_int_.Size(), 1u);
    EXPECT_EQ(arr_int_.PeekTop(), 42);
    EXPECT_EQ(arr_int_[0], 42);
}

TEST_F(DynArrayClearTest_5, ClearWorksWithNonTrivialType_5) {
    arr_str_.Push(std::string("a"));
    arr_str_.Push(std::string("b"));

    ASSERT_FALSE(arr_str_.Empty());
    ASSERT_EQ(arr_str_.Size(), 2u);
    EXPECT_EQ(arr_str_.PeekTop(), "b");

    arr_str_.Clear();

    EXPECT_TRUE(arr_str_.Empty());
    EXPECT_EQ(arr_str_.Size(), 0u);

    // Reuse with non-trivial type.
    arr_str_.Push(std::string("again"));
    EXPECT_EQ(arr_str_.Size(), 1u);
    EXPECT_EQ(arr_str_.PeekTop(), "again");
}

}  // namespace
