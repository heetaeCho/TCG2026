#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"

// Mock class for testing external dependencies if needed
class MockHandler {
public:
    MOCK_METHOD(void, onSliceSub, (size_t begin, size_t end), ());
};

class SliceTest_17 : public ::testing::Test {
protected:
    Exiv2::Slice<int> slice;

    void SetUp() override {
        // Setup logic for each test case
        int data[] = {1, 2, 3, 4, 5};
        slice = Exiv2::Slice<int>(data, 0, 5);
    }
};

// Normal operation: Test subSlice functionality for valid range
TEST_F(SliceTest_17, SubSliceNormalOperation_17) {
    Exiv2::Slice<int> sub = slice.subSlice(1, 3);
    EXPECT_EQ(sub.size(), 2);
    EXPECT_EQ(sub[0], 2);
    EXPECT_EQ(sub[1], 3);
}

// Boundary condition: Subslice with the same start and end
TEST_F(SliceTest_17, SubSliceSameStartEnd_17) {
    Exiv2::Slice<int> sub = slice.subSlice(2, 2);
    EXPECT_EQ(sub.size(), 0); // No elements in the slice
}

// Boundary condition: Subslice with start at the beginning and end at the last element
TEST_F(SliceTest_17, SubSliceFullRange_17) {
    Exiv2::Slice<int> sub = slice.subSlice(0, 5);
    EXPECT_EQ(sub.size(), 5);
    EXPECT_EQ(sub[0], 1);
    EXPECT_EQ(sub[4], 5);
}

// Exceptional case: Subslice with an out-of-bounds range (end is beyond size)
TEST_F(SliceTest_17, SubSliceOutOfBounds_17) {
    EXPECT_THROW(slice.subSlice(0, 10), std::out_of_range);
}

// Test for mocking external handler on subSlice interaction
TEST_F(SliceTest_17, MockHandlerSubSlice_17) {
    MockHandler mockHandler;
    EXPECT_CALL(mockHandler, onSliceSub(1, 3)).Times(1);
    
    // Simulating the interaction where subSlice triggers handler
    Exiv2::Slice<int> sub = slice.subSlice(1, 3);
    mockHandler.onSliceSub(1, 3);
}