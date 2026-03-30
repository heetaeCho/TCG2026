#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace Exiv2 { namespace Internal {



class PtrSliceStorageTest_15 : public ::testing::Test {

protected:

    using storage_type = int*;

    const size_t begin = 0;

    const size_t end = 10;

    std::vector<int> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    PtrSliceStorage<storage_type> slice;



    PtrSliceStorageTest_15() : slice(data.data(), begin, end) {}

};



TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAt_ReturnsCorrectPointer_15) {

    EXPECT_EQ(slice.unsafeGetIteratorAt(0), &data[0]);

    EXPECT_EQ(slice.unsafeGetIteratorAt(9), &data[9]);

}



TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAt_BoundaryCondition_Start_15) {

    EXPECT_EQ(slice.unsafeGetIteratorAt(0), data.data());

}



TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAt_BoundaryCondition_End_15) {

    EXPECT_EQ(slice.unsafeGetIteratorAt(end - 1), &data[end - 1]);

}



TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAt_OutOfBounds_DoesNotThrow_15) {

    EXPECT_NO_THROW(slice.unsafeGetIteratorAt(end));

    EXPECT_NO_THROW(slice.unsafeGetIteratorAt(static_cast<size_t>(-1)));

}



}} // namespace Exiv2::Internal
