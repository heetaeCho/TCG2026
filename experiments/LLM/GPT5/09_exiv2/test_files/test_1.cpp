#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"  // Adjust the path if needed.

namespace Exiv2 { namespace Internal {

class SliceBaseTest_1 : public ::testing::Test {
protected:
    // You can set up any necessary resources here
    SliceBaseTest_1() {}

    // Teardown resources after tests, if needed
    ~SliceBaseTest_1() override {}
};

// Test case for size function (normal operation)
TEST_F(SliceBaseTest_1, Size_NormalOperation_1) {
    SliceBase slice(10, 20);
    EXPECT_EQ(slice.size(), 10);
}

// Test case for boundary condition when size is zero
TEST_F(SliceBaseTest_1, Size_ZeroRange_2) {
    SliceBase slice(10, 10);
    EXPECT_EQ(slice.size(), 0);
}

// Test case for boundary condition with a large range
TEST_F(SliceBaseTest_1, Size_LargeRange_3) {
    SliceBase slice(0, 1000000);
    EXPECT_EQ(slice.size(), 1000000);
}

// Test case for rangeCheck when index is within the range
TEST_F(SliceBaseTest_1, RangeCheck_ValidIndex_4) {
    SliceBase slice(10, 20);
    // We assume rangeCheck is a private function, so we cannot test directly,
    // but we'll simulate by invoking size() which implicitly uses rangeCheck.
    EXPECT_NO_THROW(slice.rangeCheck(15));  // Assume rangeCheck will not throw for a valid index
}

// Test case for exceptional condition when index is out of bounds
TEST_F(SliceBaseTest_1, RangeCheck_OutOfBounds_5) {
    SliceBase slice(10, 20);
    // We assume rangeCheck throws if index is out of bounds
    EXPECT_THROW(slice.rangeCheck(25), std::out_of_range);
}

} }  // namespace Exiv2::Internal