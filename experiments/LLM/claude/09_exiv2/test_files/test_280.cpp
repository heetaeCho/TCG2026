#include <gtest/gtest.h>
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

// Test fixture for TiffRwState
class TiffRwStateTest_280 : public ::testing::Test {
protected:
    // Setup and teardown can be added if needed
};

// Test: Default construction with zero base offset
TEST_F(TiffRwStateTest_280, BaseOffsetZero_280) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(state.baseOffset(), 0u);
}

// Test: Construction with a non-zero base offset
TEST_F(TiffRwStateTest_280, BaseOffsetNonZero_280) {
    TiffRwState state(littleEndian, 42);
    EXPECT_EQ(state.baseOffset(), 42u);
}

// Test: Construction with a large base offset
TEST_F(TiffRwStateTest_280, BaseOffsetLargeValue_280) {
    size_t largeOffset = 1000000;
    TiffRwState state(bigEndian, largeOffset);
    EXPECT_EQ(state.baseOffset(), largeOffset);
}

// Test: Construction with maximum size_t value (boundary)
TEST_F(TiffRwStateTest_280, BaseOffsetMaxSizeT_280) {
    size_t maxOffset = std::numeric_limits<size_t>::max();
    TiffRwState state(littleEndian, maxOffset);
    EXPECT_EQ(state.baseOffset(), maxOffset);
}

// Test: ByteOrder is preserved with little endian
TEST_F(TiffRwStateTest_280, ByteOrderLittleEndian_280) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(state.byteOrder(), littleEndian);
}

// Test: ByteOrder is preserved with big endian
TEST_F(TiffRwStateTest_280, ByteOrderBigEndian_280) {
    TiffRwState state(bigEndian, 0);
    EXPECT_EQ(state.byteOrder(), bigEndian);
}

// Test: Both byte order and base offset are correctly stored
TEST_F(TiffRwStateTest_280, ByteOrderAndBaseOffset_280) {
    TiffRwState state(bigEndian, 512);
    EXPECT_EQ(state.byteOrder(), bigEndian);
    EXPECT_EQ(state.baseOffset(), 512u);
}

// Test: Different instances have independent state
TEST_F(TiffRwStateTest_280, IndependentInstances_280) {
    TiffRwState state1(littleEndian, 100);
    TiffRwState state2(bigEndian, 200);
    
    EXPECT_EQ(state1.baseOffset(), 100u);
    EXPECT_EQ(state2.baseOffset(), 200u);
    EXPECT_EQ(state1.byteOrder(), littleEndian);
    EXPECT_EQ(state2.byteOrder(), bigEndian);
}

// Test: Base offset of 1 (boundary just above zero)
TEST_F(TiffRwStateTest_280, BaseOffsetOne_280) {
    TiffRwState state(littleEndian, 1);
    EXPECT_EQ(state.baseOffset(), 1u);
}

// Test: Typical TIFF-like offset value
TEST_F(TiffRwStateTest_280, TypicalTiffOffset_280) {
    // A common TIFF header offset is 8
    TiffRwState state(littleEndian, 8);
    EXPECT_EQ(state.baseOffset(), 8u);
    EXPECT_EQ(state.byteOrder(), littleEndian);
}

} // namespace Internal
} // namespace Exiv2
