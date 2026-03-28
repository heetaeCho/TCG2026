#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp" // Assuming the file path is correct.

namespace Exiv2 {

    // Test class for Slice functionality
    class SliceTest_18 : public ::testing::Test {
    protected:
        // Placeholder for any setup or teardown if needed.
        void SetUp() override {
            // Setup can be done here if necessary.
        }

        void TearDown() override {
            // Clean-up can be done here if necessary.
        }
    };

    // Test normal behavior of subSlice with const T*
    TEST_F(SliceTest_18, SubSliceWithConstPointer_18) {
        // Create a Slice for const T* with some example data
        const int data[] = {1, 2, 3, 4, 5};
        const size_t begin = 1;
        const size_t end = 4;

        // Create the Slice instance
        Slice<const int*> slice(data, 0, 5);

        // Call subSlice and check the result
        Slice<const int*> result = slice.subSlice(begin, end);
        
        // Assertions on the subSlice behavior (check the returned subSlice values)
        ASSERT_EQ(result.begin(), data + begin);
        ASSERT_EQ(result.end(), data + end);
        ASSERT_EQ(result.size(), end - begin);
    }

    // Test normal behavior of subSlice with mutable T*
    TEST_F(SliceTest_18, SubSliceWithMutablePointer_18) {
        // Create a Slice for mutable T* with some example data
        int data[] = {10, 20, 30, 40, 50};
        const size_t begin = 1;
        const size_t end = 4;

        // Create the Slice instance
        Slice<int*> slice(data, 0, 5);

        // Call subSlice and check the result
        Slice<int*> result = slice.subSlice(begin, end);
        
        // Assertions on the subSlice behavior (check the returned subSlice values)
        ASSERT_EQ(result.begin(), data + begin);
        ASSERT_EQ(result.end(), data + end);
        ASSERT_EQ(result.size(), end - begin);
    }

    // Test exceptional case: out-of-bounds subSlice with const T*
    TEST_F(SliceTest_18, SubSliceOutOfBoundsConst_18) {
        const int data[] = {1, 2, 3, 4, 5};
        const size_t begin = 4;
        const size_t end = 6;

        Slice<const int*> slice(data, 0, 5);

        // This test expects that accessing out of bounds will throw an exception
        EXPECT_THROW(slice.subSlice(begin, end), std::out_of_range);
    }

    // Test exceptional case: out-of-bounds subSlice with mutable T*
    TEST_F(SliceTest_18, SubSliceOutOfBoundsMutable_18) {
        int data[] = {10, 20, 30, 40, 50};
        const size_t begin = 4;
        const size_t end = 6;

        Slice<int*> slice(data, 0, 5);

        // This test expects that accessing out of bounds will throw an exception
        EXPECT_THROW(slice.subSlice(begin, end), std::out_of_range);
    }

    // Test subSlice with edge case where begin == end
    TEST_F(SliceTest_18, SubSliceBeginEqualsEnd_18) {
        const int data[] = {5, 10, 15, 20, 25};
        const size_t begin = 2;
        const size_t end = 2;

        Slice<const int*> slice(data, 0, 5);
        Slice<const int*> result = slice.subSlice(begin, end);

        // Verify the result is an empty slice
        ASSERT_EQ(result.size(), 0);
    }

    // Test subSlice with single element range
    TEST_F(SliceTest_18, SubSliceSingleElement_18) {
        const int data[] = {100, 200, 300, 400, 500};
        const size_t begin = 2;
        const size_t end = 3;

        Slice<const int*> slice(data, 0, 5);
        Slice<const int*> result = slice.subSlice(begin, end);

        // Verify the result has only one element
        ASSERT_EQ(result.size(), 1);
        ASSERT_EQ(*result.begin(), 300);
    }
}