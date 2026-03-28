#include <gtest/gtest.h>
#include <vector>
#include <array>
#include "exiv2/slice.hpp"  // Include the header file for the function

// Test Fixture for Slice
template <typename Container>
class SliceTest : public ::testing::Test {
public:
    std::vector<int> vec;
};

using TestTypes = ::testing::Types<std::vector<int>, std::array<int, 5>>;
TYPED_TEST_SUITE(SliceTest, TestTypes);

// Normal operation: Test makeSliceUntil with a valid container and end index
TYPED_TEST(SliceTest, MakeSliceUntil_NormalOperation) {
    this->vec = {1, 2, 3, 4, 5, 6};

    // Create a slice from the container until index 4
    auto slice = Exiv2::makeSliceUntil(this->vec, 4);

    // Verify the slice contains the correct range of elements
    ASSERT_EQ(slice.size(), 4);
    EXPECT_EQ(slice[0], 1);
    EXPECT_EQ(slice[1], 2);
    EXPECT_EQ(slice[2], 3);
    EXPECT_EQ(slice[3], 4);
}

// Boundary condition: Test makeSliceUntil with an end index equal to the container size
TYPED_TEST(SliceTest, MakeSliceUntil_EndIndexEqualToSize) {
    this->vec = {1, 2, 3, 4, 5};

    // Create a slice that includes the entire container
    auto slice = Exiv2::makeSliceUntil(this->vec, this->vec.size());

    // Verify the slice matches the entire container
    ASSERT_EQ(slice.size(), this->vec.size());
    for (size_t i = 0; i < this->vec.size(); ++i) {
        EXPECT_EQ(slice[i], this->vec[i]);
    }
}

// Boundary condition: Test makeSliceUntil with end index of 0
TYPED_TEST(SliceTest, MakeSliceUntil_EndIndexZero) {
    this->vec = {1, 2, 3, 4, 5};

    // Create a slice with an end index of 0
    auto slice = Exiv2::makeSliceUntil(this->vec, 0);

    // Verify the slice is empty
    ASSERT_EQ(slice.size(), 0);
}

// Exceptional case: Test makeSliceUntil with an invalid end index (greater than container size)
TYPED_TEST(SliceTest, MakeSliceUntil_InvalidEndIndex) {
    this->vec = {1, 2, 3};

    // Create a slice with an end index greater than the container size
    auto slice = Exiv2::makeSliceUntil(this->vec, 5);

    // Verify that the slice includes all elements in the container
    ASSERT_EQ(slice.size(), this->vec.size());
    EXPECT_EQ(slice[0], 1);
    EXPECT_EQ(slice[1], 2);
    EXPECT_EQ(slice[2], 3);
}

// Exceptional case: Test makeSliceUntil with an empty container
TYPED_TEST(SliceTest, MakeSliceUntil_EmptyContainer) {
    this->vec = {};

    // Create a slice from the empty container
    auto slice = Exiv2::makeSliceUntil(this->vec, 0);

    // Verify the slice is also empty
    ASSERT_EQ(slice.size(), 0);
}