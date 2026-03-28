#include <gtest/gtest.h>
#include <stdexcept>
#include "exiv2/slice.hpp"

namespace Exiv2 {
namespace Internal {

// Mock SliceBase class for testing (We don't need full implementation for this test)
class SliceBaseMock : public SliceBase {
public:
    SliceBaseMock(size_t begin, size_t end) : SliceBase(begin, end) {}

    size_t size() const noexcept override {
        return end_ - begin_;
    }
};

} // namespace Internal
} // namespace Exiv2

// Unit tests for the SliceBase class

TEST_F(SliceBaseTest_1, RangeCheck_ValidIndex_1) {
    // Test for normal operation when index is within bounds
    Exiv2::Internal::SliceBaseMock slice(0, 10);

    EXPECT_NO_THROW(slice.rangeCheck(5)); // index within the valid range
}

TEST_F(SliceBaseTest_2, RangeCheck_OutOfBounds_2) {
    // Test for an exception when the index is out of bounds
    Exiv2::Internal::SliceBaseMock slice(0, 10);

    EXPECT_THROW(slice.rangeCheck(10), std::out_of_range); // index equal to size, should throw
    EXPECT_THROW(slice.rangeCheck(11), std::out_of_range); // index greater than size, should throw
}

TEST_F(SliceBaseTest_3, RangeCheck_BoundaryConditions_3) {
    // Test for boundary conditions at the edges of the slice
    Exiv2::Internal::SliceBaseMock slice(0, 5);

    EXPECT_NO_THROW(slice.rangeCheck(0)); // minimum valid index
    EXPECT_NO_THROW(slice.rangeCheck(4)); // maximum valid index
    EXPECT_THROW(slice.rangeCheck(5), std::out_of_range); // out-of-bounds index
}

TEST_F(SliceBaseTest_4, Size_ReturnsCorrectSize_4) {
    // Test for checking the size of the slice
    Exiv2::Internal::SliceBaseMock slice(0, 5);

    EXPECT_EQ(slice.size(), 5); // Size should be 5
}

TEST_F(SliceBaseTest_5, RangeCheck_EmptySlice_5) {
    // Test for an empty slice
    Exiv2::Internal::SliceBaseMock slice(0, 0);

    EXPECT_THROW(slice.rangeCheck(0), std::out_of_range); // Should throw exception as the slice is empty
}

TEST_F(SliceBaseTest_6, RangeCheck_LargeSlice_6) {
    // Test for a very large slice range
    Exiv2::Internal::SliceBaseMock slice(0, 1000000);

    EXPECT_NO_THROW(slice.rangeCheck(999999)); // Should not throw for valid index
    EXPECT_THROW(slice.rangeCheck(1000000), std::out_of_range); // Should throw for out-of-bounds index
}