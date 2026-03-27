#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"  // Assuming the full class definitions are available

namespace Exiv2 {
namespace Internal {

class ConstSliceBaseTest_5 : public ::testing::Test {
protected:
    // Sample data setup for the tests
    std::vector<int> sample_data = {1, 2, 3, 4, 5};

    // Constructor for creating ConstSliceBase
    ConstSliceBase<int, std::vector<int>> slice;
    
    ConstSliceBaseTest_5() 
        : slice(sample_data, 0, 5) {}  // Initializes slice with the whole sample_data
};

// Normal Operation Test Case
TEST_F(ConstSliceBaseTest_5, CendReturnsCorrectIterator_5) {
    auto it = slice.cend();
    ASSERT_EQ(*it, 5);  // Assuming 'cend' points past the last element
}

// Boundary Test Case: Checking the `at` method for valid indices
TEST_F(ConstSliceBaseTest_5, AtReturnsCorrectElement_5) {
    ASSERT_EQ(slice.at(0), 1);  // First element should be 1
    ASSERT_EQ(slice.at(4), 5);  // Last element should be 5
}

// Boundary Test Case: Verifying `at` method out-of-bounds access throws exception
TEST_F(ConstSliceBaseTest_5, AtThrowsOnOutOfBoundsAccess_5) {
    EXPECT_THROW(slice.at(5), std::out_of_range);  // Access beyond the range should throw
}

// Exceptional Test Case: Testing `subSlice` for valid ranges
TEST_F(ConstSliceBaseTest_5, SubSliceReturnsCorrectSlice_5) {
    auto sub = slice.subSlice(1, 4);
    ASSERT_EQ(sub.size(), 3);
    ASSERT_EQ(sub.at(0), 2);  // Should contain elements from index 1 to 3 (2, 3, 4)
}

// Exceptional Test Case: Testing subSlice for invalid range
TEST_F(ConstSliceBaseTest_5, SubSliceThrowsOnInvalidRange_5) {
    EXPECT_THROW(slice.subSlice(4, 6), std::out_of_range);  // Invalid range should throw
}

// Verifying that the size method returns the correct range size
TEST_F(ConstSliceBaseTest_5, SizeReturnsCorrectRangeSize_5) {
    ASSERT_EQ(slice.size(), 5);  // Size of the slice should be 5 (from index 0 to 4)
}

}  // namespace Internal
}  // namespace Exiv2