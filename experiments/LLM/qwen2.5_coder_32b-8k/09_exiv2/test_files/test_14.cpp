#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



using namespace Exiv2::Internal;



class PtrSliceStorageTest_14 : public ::testing::Test {

protected:

    using StorageType = int*;

    const size_t dataSize = 5;

    int data[5] = {0, 1, 2, 3, 4};

    PtrSliceStorage<StorageType> ptrSliceStorage;



    PtrSliceStorageTest_14() : ptrSliceStorage(data, 0, dataSize) {}

};



TEST_F(PtrSliceStorageTest_14, UnsafeAt_ReturnsCorrectElement_14) {

    EXPECT_EQ(ptrSliceStorage.unsafeAt(0), 0);

    EXPECT_EQ(ptrSliceStorage.unsafeAt(2), 2);

    EXPECT_EQ(ptrSliceStorage.unsafeAt(dataSize - 1), 4);

}



TEST_F(PtrSliceStorageTest_14, UnsafeAt_OutOfBounds_ReturnsUndefined_14) {

    // This test assumes out-of-bounds access does not cause a runtime error.

    // The actual value is undefined, so we just check that it compiles and runs.

    EXPECT_NO_THROW(ptrSliceStorage.unsafeAt(dataSize));

}



TEST_F(PtrSliceStorageTest_14, UnsafeAt_BoundaryCondition_Start_14) {

    EXPECT_EQ(ptrSliceStorage.unsafeAt(0), 0);

}



TEST_F(PtrSliceStorageTest_14, UnsafeAt_BoundaryCondition_End_14) {

    EXPECT_EQ(ptrSliceStorage.unsafeAt(dataSize - 1), 4);

}
