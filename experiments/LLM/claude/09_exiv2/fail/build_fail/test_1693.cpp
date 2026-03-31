#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffReaderTest_1693 : public ::testing::Test {
protected:
    void SetUp() override {
        // Minimal valid TIFF-like data buffer
        data_.resize(256, 0);
    }

    std::vector<byte> data_;
};

// Test that TiffReader returns the correct byte order when constructed with littleEndian
TEST_F(TiffReaderTest_1693, ByteOrderLittleEndian_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test that TiffReader returns the correct byte order when constructed with bigEndian
TEST_F(TiffReaderTest_1693, ByteOrderBigEndian_1693) {
    TiffRwState state(bigEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test that TiffReader returns the correct base offset
TEST_F(TiffReaderTest_1693, BaseOffsetZero_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test that TiffReader returns a non-zero base offset
TEST_F(TiffReaderTest_1693, BaseOffsetNonZero_1693) {
    TiffRwState state(littleEndian, 42);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.baseOffset(), 42u);
}

// Test that circularReference returns false for a new start/group combination
TEST_F(TiffReaderTest_1693, CircularReferenceFirstCall_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    // First call with a given start and group should not be circular
    bool result = reader.circularReference(data_.data() + 10, IfdId::ifd0Id);
    EXPECT_FALSE(result);
}

// Test that circularReference returns true when called twice with the same start/group
TEST_F(TiffReaderTest_1693, CircularReferenceDetected_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    const byte* start = data_.data() + 10;
    reader.circularReference(start, IfdId::ifd0Id);
    bool result = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test that nextIdx returns incrementing indices for the same group
TEST_F(TiffReaderTest_1693, NextIdxIncrementing_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx1, idx0 + 1);
}

// Test that nextIdx for different groups are independent
TEST_F(TiffReaderTest_1693, NextIdxDifferentGroups_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    int idx0_g1 = reader.nextIdx(IfdId::ifd0Id);
    int idx0_g2 = reader.nextIdx(IfdId::ifd1Id);
    // Both should start at the same initial value
    EXPECT_EQ(idx0_g1, idx0_g2);
}

// Test setOrigState restores original byte order after setMnState changes it
TEST_F(TiffReaderTest_1693, SetOrigStateRestoresByteOrder_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    
    TiffRwState mnState(bigEndian, 100);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 100u);
    
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test setMnState changes byte order and base offset
TEST_F(TiffReaderTest_1693, SetMnStateChangesState_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    TiffRwState mnState(bigEndian, 50);
    reader.setMnState(&mnState);
    
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 50u);
}

// Test construction with zero-size data
TEST_F(TiffReaderTest_1693, ConstructWithZeroSize_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    byte dummy = 0;
    TiffReader reader(&dummy, 0, &root, state);
    
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test construction with large base offset
TEST_F(TiffReaderTest_1693, LargeBaseOffset_1693) {
    size_t largeOffset = 1000000;
    TiffRwState state(bigEndian, largeOffset);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.baseOffset(), largeOffset);
}

// Test postProcess does not crash on a reader with no entries
TEST_F(TiffReaderTest_1693, PostProcessNoEntries_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    // Should not throw or crash
    EXPECT_NO_THROW(reader.postProcess());
}

// Test circularReference with different groups at same start is not circular
TEST_F(TiffReaderTest_1693, CircularReferenceDifferentGroups_1693) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    const byte* start = data_.data() + 20;
    bool result1 = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_FALSE(result1);
    
    // Same start address but different group should not be circular
    bool result2 = reader.circularReference(start, IfdId::ifd1Id);
    EXPECT_FALSE(result2);
}

// Test TiffRwState byteOrder and baseOffset accessors
TEST(TiffRwStateTest_1693, Accessors_1693) {
    TiffRwState state(bigEndian, 123);
    EXPECT_EQ(state.byteOrder(), bigEndian);
    EXPECT_EQ(state.baseOffset(), 123u);
}

TEST(TiffRwStateTest_1693, LittleEndianZeroOffset_1693) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(state.byteOrder(), littleEndian);
    EXPECT_EQ(state.baseOffset(), 0u);
}
