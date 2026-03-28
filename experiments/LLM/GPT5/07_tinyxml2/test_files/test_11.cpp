// File: ./TestProjects/tinyxml2/tests/DynArrayOperatorIndex_11.test.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

using tinyxml2::DynArray;

// TEST_ID = 11
class DynArrayOperatorIndexTest_11 : public ::testing::Test {
protected:
    using IntArr = DynArray<int, 4>;
};

TEST_F(DynArrayOperatorIndexTest_11, OperatorIndexReturnsElementReferenceAndAllowsWrite_11) {
    IntArr arr;
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);

    // Read
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    // Write via returned reference
    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);

    // Ensure it's really a reference (writing through an alias changes the array)
    int& ref = arr[2];
    ref = -7;
    EXPECT_EQ(arr[2], -7);
}

TEST_F(DynArrayOperatorIndexTest_11, OperatorIndexWorksAtValidBoundaries_11) {
    IntArr arr;
    arr.Push(111);

    ASSERT_EQ(arr.Size(), size_t{1});
    EXPECT_EQ(arr[0], 111);

    arr.Push(222);
    arr.Push(333);

    ASSERT_EQ(arr.Size(), size_t{3});
    EXPECT_EQ(arr[arr.Size() - 1], 333);

    // Mutate last element and observe via PeekTop (public API)
    arr[arr.Size() - 1] = 444;
    EXPECT_EQ(arr.PeekTop(), 444);
}

TEST_F(DynArrayOperatorIndexTest_11, OperatorIndexAddressMatchesMemPointerForFirstElementWhenNonEmpty_11) {
    IntArr arr;
    arr.Push(1);
    arr.Push(2);

    // Mem() is a public API; when non-empty, &arr[0] should refer to the first element.
    // We only compare addresses returned by public APIs (no private access).
    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);

    const int* addr0 = static_cast<const int*>(&arr[0]);
    EXPECT_EQ(addr0, mem);
}

#if !defined(NDEBUG)
// In debug builds, operator[] uses TIXMLASSERT(i < _size). Expect process termination on OOB.
TEST_F(DynArrayOperatorIndexTest_11, OperatorIndexOutOfRangeTriggersAssertionDeath_11) {
    IntArr arr;
    arr.Push(123);

    // i == _size is out-of-range
    EXPECT_DEATH(
        {
            (void)arr[1];
        },
        ".*");
}
#endif

}  // namespace
