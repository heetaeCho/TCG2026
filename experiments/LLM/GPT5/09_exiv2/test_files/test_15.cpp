#include <gtest/gtest.h>
#include "exiv2/slice.hpp" // Assuming the header is available

namespace Exiv2 { namespace Internal {

// Unit test for the `unsafeGetIteratorAt` function in PtrSliceStorage
TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtValidIndex_15) {
    // Setup
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Action
    int* result = storage.unsafeGetIteratorAt(2);

    // Assertion
    EXPECT_EQ(*result, 3) << "The iterator at index 2 should point to the value 3.";
}

TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtBoundaryIndex_15) {
    // Setup
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Action & Assertions for valid boundary index
    int* result_start = storage.unsafeGetIteratorAt(0);
    int* result_end = storage.unsafeGetIteratorAt(4);

    // Validate the boundary elements
    EXPECT_EQ(*result_start, 1) << "The iterator at index 0 should point to the value 1.";
    EXPECT_EQ(*result_end, 5) << "The iterator at index 4 should point to the value 5.";
}

TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtInvalidIndex_15) {
    // Setup
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Action
    // Checking invalid index
    EXPECT_THROW(storage.unsafeGetIteratorAt(5), std::out_of_range) << "Accessing index 5 should throw an out_of_range exception.";
}

TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtNegativeIndex_15) {
    // Setup
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Action
    // Checking invalid negative index
    EXPECT_THROW(storage.unsafeGetIteratorAt(-1), std::out_of_range) << "Negative index access should throw an out_of_range exception.";
}

} } // namespace Exiv2::Internal