#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



using namespace Exiv2::Internal;



// Test fixture for PtrSliceStorage tests

class PtrSliceStorageTest_2148 : public ::testing::Test {

protected:

    // Define a sample pointer type and size_t for testing

    using storage_type = int*;

};



// Test normal operation with valid non-null pointer

TEST_F(PtrSliceStorageTest_2148, ConstructorWithNonNullPointer_2148) {

    int sampleData = 42;

    EXPECT_NO_THROW(PtrSliceStorage(&sampleData, 0, 1));

}



// Test boundary condition with zero-size range (begin == end)

TEST_F(PtrSliceStorageTest_2148, ConstructorWithZeroSizeRange_2148) {

    int sampleData = 42;

    EXPECT_NO_THROW(PtrSliceStorage(&sampleData, 0, 0));

}



// Test exceptional case with null pointer

TEST_F(PtrSliceStorageTest_2148, ConstructorWithNullPointer_2148) {

    EXPECT_THROW(PtrSliceStorage(nullptr, 0, 1), std::invalid_argument);

}
