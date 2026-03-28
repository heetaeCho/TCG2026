#include <gtest/gtest.h>
#include "tiffvisitor_int.hpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffRwState
class TiffRwStateTest_279 : public ::testing::Test {
protected:
    // Nothing special needed for setup/teardown
};

// Test that byteOrder() returns the byte order set during construction (Little Endian)
TEST_F(TiffRwStateTest_279, ByteOrderReturnsLittleEndian_279) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(littleEndian, state.byteOrder());
}

// Test that byteOrder() returns the byte order set during construction (Big Endian)
TEST_F(TiffRwStateTest_279, ByteOrderReturnsBigEndian_279) {
    TiffRwState state(bigEndian, 0);
    EXPECT_EQ(bigEndian, state.byteOrder());
}

// Test that baseOffset() returns the base offset set during construction (zero)
TEST_F(TiffRwStateTest_279, BaseOffsetReturnsZero_279) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(0u, state.baseOffset());
}

// Test that baseOffset() returns a non-zero base offset
TEST_F(TiffRwStateTest_279, BaseOffsetReturnsNonZeroValue_279) {
    TiffRwState state(bigEndian, 1024);
    EXPECT_EQ(1024u, state.baseOffset());
}

// Test with a large base offset value
TEST_F(TiffRwStateTest_279, BaseOffsetReturnsLargeValue_279) {
    size_t largeOffset = 0xFFFFFFFF;
    TiffRwState state(littleEndian, largeOffset);
    EXPECT_EQ(largeOffset, state.baseOffset());
}

// Test that both byteOrder and baseOffset are correctly stored together
TEST_F(TiffRwStateTest_279, ByOrderAndBaseOffsetConsistent_279) {
    TiffRwState state1(littleEndian, 42);
    EXPECT_EQ(littleEndian, state1.byteOrder());
    EXPECT_EQ(42u, state1.baseOffset());

    TiffRwState state2(bigEndian, 100);
    EXPECT_EQ(bigEndian, state2.byteOrder());
    EXPECT_EQ(100u, state2.baseOffset());
}

// Test with boundary base offset value of 1
TEST_F(TiffRwStateTest_279, BaseOffsetBoundaryOne_279) {
    TiffRwState state(bigEndian, 1);
    EXPECT_EQ(1u, state.baseOffset());
    EXPECT_EQ(bigEndian, state.byteOrder());
}

// Test with max size_t value for base offset
TEST_F(TiffRwStateTest_279, BaseOffsetMaxSizeT_279) {
    size_t maxOffset = std::numeric_limits<size_t>::max();
    TiffRwState state(littleEndian, maxOffset);
    EXPECT_EQ(maxOffset, state.baseOffset());
    EXPECT_EQ(littleEndian, state.byteOrder());
}

// Test that two independently constructed states with same params return same values
TEST_F(TiffRwStateTest_279, TwoStatesWithSameParamsAreEqual_279) {
    TiffRwState state1(bigEndian, 512);
    TiffRwState state2(bigEndian, 512);
    EXPECT_EQ(state1.byteOrder(), state2.byteOrder());
    EXPECT_EQ(state1.baseOffset(), state2.baseOffset());
}

// Test that two independently constructed states with different params return different values
TEST_F(TiffRwStateTest_279, TwoStatesWithDifferentParamsDiffer_279) {
    TiffRwState state1(littleEndian, 0);
    TiffRwState state2(bigEndian, 256);
    EXPECT_NE(state1.byteOrder(), state2.byteOrder());
    EXPECT_NE(state1.baseOffset(), state2.baseOffset());
}

}  // namespace
