// File: ./TestProjects/tinyxml2/tests/test_dynarray_peektop_12.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

namespace {

using tinyxml2::DynArray;

class DynArrayPeekTopTest_12 : public ::testing::Test {};

TEST_F(DynArrayPeekTopTest_12, PeekTopReturnsLastPushedValue_12) {
    DynArray<int, 4> arr;

    arr.Push(10);
    EXPECT_EQ(arr.PeekTop(), 10);

    arr.Push(20);
    EXPECT_EQ(arr.PeekTop(), 20);

    arr.Push(30);
    EXPECT_EQ(arr.PeekTop(), 30);
}

TEST_F(DynArrayPeekTopTest_12, PeekTopWorksThroughConstReference_12) {
    DynArray<int, 4> arr;
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);

    const DynArray<int, 4>& carr = arr;
    EXPECT_EQ(carr.PeekTop(), 3);
}

TEST_F(DynArrayPeekTopTest_12, PeekTopReferenceMatchesMemBackElement_12) {
    DynArray<int, 8> arr;
    arr.Push(7);
    arr.Push(9);
    arr.Push(11);

    const DynArray<int, 8>& carr = arr;

    ASSERT_NE(carr.Mem(), nullptr);
    ASSERT_GT(carr.Size(), 0u);

    const int* expected_addr = carr.Mem() + (carr.Size() - 1);
    const int* peek_addr = &carr.PeekTop();

    EXPECT_EQ(peek_addr, expected_addr);
    EXPECT_EQ(carr.PeekTop(), *expected_addr);
}

TEST_F(DynArrayPeekTopTest_12, PeekTopAfterPopReflectsNewTop_12) {
    DynArray<int, 4> arr;
    arr.Push(100);
    arr.Push(200);
    arr.Push(300);

    EXPECT_EQ(arr.PeekTop(), 300);

    const int popped = arr.Pop();
    EXPECT_EQ(popped, 300);
    ASSERT_GT(arr.Size(), 0u);
    EXPECT_EQ(arr.PeekTop(), 200);
}

TEST_F(DynArrayPeekTopTest_12, PeekTopAfterPushArrReflectsLastWrittenElement_12) {
    DynArray<int, 2> arr;

    int* block = arr.PushArr(5);
    ASSERT_NE(block, nullptr);
    // Write values through returned pointer (observable behavior via PeekTop/Size/Mem).
    for (int i = 0; i < 5; ++i) {
        block[i] = 1000 + i;
    }

    ASSERT_EQ(arr.Size(), 5u);
    EXPECT_EQ(arr.PeekTop(), 1004);
}

#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST
// PeekTop() uses TIXMLASSERT(_size > 0). In many builds this behaves like an assert,
// which typically aborts only when assertions are enabled.
#if !defined(NDEBUG) && !defined(TINYXML2_NO_ASSERT)
TEST_F(DynArrayPeekTopTest_12, PeekTopOnEmptyTriggersAssertion_12) {
    DynArray<int, 4> arr;
    ASSERT_TRUE(arr.Empty());

    EXPECT_DEATH(
        {
            (void)arr.PeekTop();
        },
        ""
    );
}
#endif  // !NDEBUG && !TINYXML2_NO_ASSERT
#endif  // death tests

}  // namespace
