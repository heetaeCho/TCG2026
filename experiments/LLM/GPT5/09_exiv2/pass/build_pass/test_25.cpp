#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"  // Include the header for the class under test

namespace Exiv2 {

class SliceTest_25 : public ::testing::Test {
protected:
    // SetUp() can be used if necessary for shared resources across tests
    void SetUp() override {
    }

    // TearDown() can be used for cleanup after tests
    void TearDown() override {
    }
};

// Test case for verifying normal operation of makeSliceUntil
TEST_F(SliceTest_25, MakeSliceUntil_NormalOperation_25) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t end = 3;
    
    auto slice = makeSliceUntil(arr, end);

    // Verify that the slice's size is correct, the end pointer is as expected
    EXPECT_EQ(slice.size(), end);
    EXPECT_EQ(slice.begin(), arr);
    EXPECT_EQ(slice.end(), arr + end);
}

// Test case for boundary condition where the slice ends at 0
TEST_F(SliceTest_25, MakeSliceUntil_ZeroLength_25) {
    int arr[] = {1, 2, 3};
    size_t end = 0;

    auto slice = makeSliceUntil(arr, end);

    // Verify that slice has size 0
    EXPECT_EQ(slice.size(), 0);
    EXPECT_EQ(slice.begin(), arr);
    EXPECT_EQ(slice.end(), arr); // Since the size is 0, begin == end
}

// Test case for boundary condition where slice includes all elements
TEST_F(SliceTest_25, MakeSliceUntil_AllElements_25) {
    int arr[] = {1, 2, 3};
    size_t end = 3;

    auto slice = makeSliceUntil(arr, end);

    // Verify that slice includes all elements
    EXPECT_EQ(slice.size(), 3);
    EXPECT_EQ(slice.begin(), arr);
    EXPECT_EQ(slice.end(), arr + end);
}

// Test case for exceptional condition where end exceeds array bounds
TEST_F(SliceTest_25, MakeSliceUntil_OutOfBounds_25) {
    int arr[] = {1, 2, 3};
    size_t end = 10; // Out of bounds

    auto slice = makeSliceUntil(arr, end);

    // Verify that the size is still constrained by the array size
    EXPECT_EQ(slice.size(), 3);
    EXPECT_EQ(slice.end(), arr + 3);  // end should be constrained to the size of the array
}

} // namespace Exiv2

// Add more test cases for additional edge cases or specific behavior if needed