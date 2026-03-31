#include <gtest/gtest.h>
#include "exiv2/slice.hpp"

// Since SliceBase is a protected/internal struct, we need to create a concrete
// derived class to test through the public interface. We'll use the actual
// Slice classes provided by the header if available, or create a minimal
// testable wrapper.

// Minimal test helper that derives from SliceBase to expose its public interface
namespace {

struct TestableSliceBase : public Exiv2::Internal::SliceBase {
    TestableSliceBase(size_t begin, size_t end) : SliceBase(begin, end) {}
    
    // Expose rangeCheck for testing since it's protected
    void testRangeCheck(size_t index) const {
        rangeCheck(index);
    }
};

}  // namespace

class SliceBaseTest_1 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that size() returns the correct value for a normal range
TEST_F(SliceBaseTest_1, SizeReturnsCorrectValue_1) {
    TestableSliceBase slice(0, 10);
    EXPECT_EQ(slice.size(), 10u);
}

// Test that size() returns 0 for an empty slice (begin == end)
TEST_F(SliceBaseTest_1, SizeReturnsZeroForEmptySlice_1) {
    TestableSliceBase slice(5, 5);
    EXPECT_EQ(slice.size(), 0u);
}

// Test that size() returns 1 for a single-element slice
TEST_F(SliceBaseTest_1, SizeReturnsOneForSingleElementSlice_1) {
    TestableSliceBase slice(3, 4);
    EXPECT_EQ(slice.size(), 1u);
}

// Test that size() works correctly for a large range
TEST_F(SliceBaseTest_1, SizeWorksForLargeRange_1) {
    TestableSliceBase slice(0, 1000000);
    EXPECT_EQ(slice.size(), 1000000u);
}

// Test that size() works when begin is non-zero
TEST_F(SliceBaseTest_1, SizeCorrectWithNonZeroBegin_1) {
    TestableSliceBase slice(100, 200);
    EXPECT_EQ(slice.size(), 100u);
}

// Test that size() is noexcept
TEST_F(SliceBaseTest_1, SizeIsNoexcept_1) {
    TestableSliceBase slice(0, 10);
    EXPECT_TRUE(noexcept(slice.size()));
}

// Test that constructor throws when begin > end
TEST_F(SliceBaseTest_1, ConstructorThrowsWhenBeginGreaterThanEnd_1) {
    EXPECT_THROW(TestableSliceBase(10, 5), std::out_of_range);
}

// Test that rangeCheck throws for an out-of-range index
TEST_F(SliceBaseTest_1, RangeCheckThrowsForOutOfRangeIndex_1) {
    TestableSliceBase slice(0, 10);
    EXPECT_THROW(slice.testRangeCheck(10), std::out_of_range);
}

// Test that rangeCheck throws for an index way out of range
TEST_F(SliceBaseTest_1, RangeCheckThrowsForFarOutOfRangeIndex_1) {
    TestableSliceBase slice(0, 10);
    EXPECT_THROW(slice.testRangeCheck(100), std::out_of_range);
}

// Test that rangeCheck does not throw for valid index 0
TEST_F(SliceBaseTest_1, RangeCheckDoesNotThrowForValidIndexZero_1) {
    TestableSliceBase slice(0, 10);
    EXPECT_NO_THROW(slice.testRangeCheck(0));
}

// Test that rangeCheck does not throw for valid index at upper boundary
TEST_F(SliceBaseTest_1, RangeCheckDoesNotThrowForLastValidIndex_1) {
    TestableSliceBase slice(0, 10);
    EXPECT_NO_THROW(slice.testRangeCheck(9));
}

// Test that rangeCheck throws for any index on an empty slice
TEST_F(SliceBaseTest_1, RangeCheckThrowsForEmptySlice_1) {
    TestableSliceBase slice(5, 5);
    EXPECT_THROW(slice.testRangeCheck(0), std::out_of_range);
}

// Test that rangeCheck does not throw for a middle index
TEST_F(SliceBaseTest_1, RangeCheckDoesNotThrowForMiddleIndex_1) {
    TestableSliceBase slice(0, 100);
    EXPECT_NO_THROW(slice.testRangeCheck(50));
}

// Test size with adjacent begin/end values
TEST_F(SliceBaseTest_1, SizeWithAdjacentValues_1) {
    TestableSliceBase slice(99, 100);
    EXPECT_EQ(slice.size(), 1u);
}

// Test construction with begin = 0 and end = 0
TEST_F(SliceBaseTest_1, ConstructionWithZeroRange_1) {
    TestableSliceBase slice(0, 0);
    EXPECT_EQ(slice.size(), 0u);
}
