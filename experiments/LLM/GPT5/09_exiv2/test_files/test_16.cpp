#include <gtest/gtest.h>
#include "exiv2/slice.hpp"

namespace Exiv2 {

    // Test fixture for Slice class
    class SliceTest : public ::testing::Test {
    protected:
        // Common setup code for tests if needed
        void SetUp() override {
            // Example setup, if required
        }

        // Common teardown code for tests if needed
        void TearDown() override {
            // Example teardown, if required
        }
    };

    // Normal operation test cases
    TEST_F(SliceTest, SubSliceNormalOperation_16) {
        // Assuming the implementation of Slice is correct, we test normal behavior
        
        const int arr[] = {1, 2, 3, 4, 5, 6};
        Slice<const int> slice(arr, 0, 6);
        
        // We expect the subSlice to return a new Slice containing elements 2, 3, 4
        Slice<const int> subSlice = slice.subSlice(1, 4);
        
        EXPECT_EQ(subSlice.begin(), arr + 1);  // check the beginning of the subSlice
        EXPECT_EQ(subSlice.end(), arr + 4);    // check the end of the subSlice
    }

    TEST_F(SliceTest, SubSliceEmptyRange_17) {
        // Testing subSlice with an empty range
        
        const int arr[] = {1, 2, 3, 4, 5, 6};
        Slice<const int> slice(arr, 0, 6);
        
        // Sub-slice from index 2 to 2 should result in an empty Slice
        Slice<const int> subSlice = slice.subSlice(2, 2);
        
        EXPECT_EQ(subSlice.size(), 0);  // check that the size is 0
    }

    TEST_F(SliceTest, SubSliceOutOfBoundsStart_18) {
        // Testing subSlice with start index out of bounds
        
        const int arr[] = {1, 2, 3, 4, 5, 6};
        Slice<const int> slice(arr, 0, 6);
        
        // Sub-slice with start index greater than the end of the slice should be handled
        EXPECT_THROW(slice.subSlice(7, 8), std::out_of_range);  // assuming it throws std::out_of_range
    }

    TEST_F(SliceTest, SubSliceOutOfBoundsEnd_19) {
        // Testing subSlice with end index out of bounds
        
        const int arr[] = {1, 2, 3, 4, 5, 6};
        Slice<const int> slice(arr, 0, 6);
        
        // Sub-slice with end index greater than the slice range should be handled
        Slice<const int> subSlice = slice.subSlice(4, 10);
        
        EXPECT_EQ(subSlice.end(), arr + 6);  // end should not exceed the original slice
    }

    // Exceptional case - verify the behavior when invalid arguments are provided
    TEST_F(SliceTest, SubSliceStartGreaterThanEnd_20) {
        const int arr[] = {1, 2, 3, 4, 5, 6};
        Slice<const int> slice(arr, 0, 6);

        // start index is greater than end index, which should be invalid
        EXPECT_THROW(slice.subSlice(4, 2), std::invalid_argument);  // assuming it throws std::invalid_argument
    }

    // Boundary tests
    TEST_F(SliceTest, SubSliceFullRange_21) {
        const int arr[] = {1, 2, 3, 4, 5, 6};
        Slice<const int> slice(arr, 0, 6);

        // Sub-slice with the full range should return the same slice
        Slice<const int> subSlice = slice.subSlice(0, 6);

        EXPECT_EQ(subSlice.begin(), arr);  // it should start at the beginning of the original slice
        EXPECT_EQ(subSlice.end(), arr + 6);  // it should end at the end of the original slice
    }

    TEST_F(SliceTest, SubSliceSingleElement_22) {
        const int arr[] = {1, 2, 3, 4, 5, 6};
        Slice<const int> slice(arr, 0, 6);

        // Sub-slice with a single element should return a slice of size 1
        Slice<const int> subSlice = slice.subSlice(2, 3);
        
        EXPECT_EQ(subSlice.size(), 1);  // Size should be 1
        EXPECT_EQ(*subSlice.begin(), 3);  // The element should be 3
    }

}  // namespace Exiv2