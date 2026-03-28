#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Minimal test fixture for TiffReader
class TiffReaderTest_1702 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create minimal valid TIFF data
        // A minimal IFD with 0 entries
        memset(tiffData_, 0, sizeof(tiffData_));
    }

    byte tiffData_[256];
};

// Test: TiffReader construction with valid parameters
TEST_F(TiffReaderTest_1702, ConstructWithValidData_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    EXPECT_NO_THROW({
        TiffReader reader(data, sizeof(data), &root, state);
    });
}

// Test: byteOrder returns the correct byte order from state
TEST_F(TiffReaderTest_1702, ByteOrderReturnsCorrectOrder_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState stateLittle(littleEndian, 0);
    
    TiffReader readerLittle(data, sizeof(data), &root, stateLittle);
    EXPECT_EQ(littleEndian, readerLittle.byteOrder());
}

// Test: byteOrder returns big endian when constructed with big endian
TEST_F(TiffReaderTest_1702, ByteOrderReturnsBigEndian_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState stateBig(bigEndian, 0);
    
    TiffReader readerBig(data, sizeof(data), &root, stateBig);
    EXPECT_EQ(bigEndian, readerBig.byteOrder());
}

// Test: baseOffset returns the correct base offset from state
TEST_F(TiffReaderTest_1702, BaseOffsetReturnsCorrectValue_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(0u, reader.baseOffset());
}

// Test: baseOffset with non-zero offset
TEST_F(TiffReaderTest_1702, BaseOffsetNonZero_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 8);
    
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(8u, reader.baseOffset());
}

// Test: nextIdx returns incrementing values for same group
TEST_F(TiffReaderTest_1702, NextIdxIncrementsForSameGroup_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    
    EXPECT_LT(idx1, idx2);
}

// Test: nextIdx returns different sequences for different groups
TEST_F(TiffReaderTest_1702, NextIdxDifferentGroups_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    int idx1_group1 = reader.nextIdx(IfdId::ifd0Id);
    int idx1_group2 = reader.nextIdx(IfdId::ifd1Id);
    
    // Both should be valid indices (first call for each group)
    EXPECT_GE(idx1_group1, 0);
    EXPECT_GE(idx1_group2, 0);
}

// Test: circularReference detects circular references
TEST_F(TiffReaderTest_1702, CircularReferenceDetection_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    // First reference should not be circular
    bool first = reader.circularReference(data, IfdId::ifd0Id);
    EXPECT_FALSE(first);
    
    // Same start+group again should be circular
    bool second = reader.circularReference(data, IfdId::ifd0Id);
    EXPECT_TRUE(second);
}

// Test: circularReference with different addresses is not circular
TEST_F(TiffReaderTest_1702, CircularReferenceDifferentAddresses_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    bool first = reader.circularReference(data, IfdId::ifd0Id);
    EXPECT_FALSE(first);
    
    bool second = reader.circularReference(data + 10, IfdId::ifd0Id);
    EXPECT_FALSE(second);
}

// Test: circularReference with different groups is not circular
TEST_F(TiffReaderTest_1702, CircularReferenceDifferentGroups_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    bool first = reader.circularReference(data, IfdId::ifd0Id);
    EXPECT_FALSE(first);
    
    bool second = reader.circularReference(data, IfdId::ifd1Id);
    EXPECT_FALSE(second);
}

// Test: postProcess with empty post list does not throw
TEST_F(TiffReaderTest_1702, PostProcessEmptyListNoThrow_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    EXPECT_NO_THROW(reader.postProcess());
}

// Test: setOrigState restores original state
TEST_F(TiffReaderTest_1702, SetOrigStateRestoresState_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    // After setOrigState, byteOrder should match original
    reader.setOrigState();
    EXPECT_EQ(littleEndian, reader.byteOrder());
    EXPECT_EQ(0u, reader.baseOffset());
}

// Test: setMnState with nullptr (default makernote state)
TEST_F(TiffReaderTest_1702, SetMnStateWithNullptr_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 4);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    // Setting mnState with nullptr should set to default mnState (which is same as origState at construction)
    EXPECT_NO_THROW(reader.setMnState(nullptr));
}

// Test: setMnState with valid state pointer
TEST_F(TiffReaderTest_1702, SetMnStateWithValidState_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(littleEndian, 0);
    TiffRwState mnState(bigEndian, 8);
    
    TiffReader reader(data, sizeof(data), &root, origState);
    
    reader.setMnState(&mnState);
    // After setMnState, byte order and base offset should reflect the makernote state
    EXPECT_EQ(bigEndian, reader.byteOrder());
    EXPECT_EQ(8u, reader.baseOffset());
}

// Test: After setMnState and setOrigState, original state is restored
TEST_F(TiffReaderTest_1702, SetMnStateThenRestoreOrigState_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(littleEndian, 0);
    TiffRwState mnState(bigEndian, 16);
    
    TiffReader reader(data, sizeof(data), &root, origState);
    
    reader.setMnState(&mnState);
    EXPECT_EQ(bigEndian, reader.byteOrder());
    
    reader.setOrigState();
    EXPECT_EQ(littleEndian, reader.byteOrder());
    EXPECT_EQ(0u, reader.baseOffset());
}

// Test: Construction with zero size
TEST_F(TiffReaderTest_1702, ConstructWithZeroSize_1702) {
    byte data[1] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    EXPECT_NO_THROW({
        TiffReader reader(data, 0, &root, state);
    });
}

// Test: Multiple postProcess calls do not crash
TEST_F(TiffReaderTest_1702, MultiplePostProcessCalls_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    EXPECT_NO_THROW(reader.postProcess());
    EXPECT_NO_THROW(reader.postProcess());
    EXPECT_NO_THROW(reader.postProcess());
}

// Test: nextIdx starts from a consistent initial value
TEST_F(TiffReaderTest_1702, NextIdxInitialValue_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    int idx = reader.nextIdx(IfdId::ifd0Id);
    
    // The first index should be a non-negative value
    EXPECT_GE(idx, 0);
}

// Test: Visiting a TiffEntry
TEST_F(TiffReaderTest_1702, VisitTiffEntry_1702) {
    // Set up minimal TIFF entry data
    // Tag (2 bytes) + Type (2 bytes) + Count (4 bytes) + Value/Offset (4 bytes) = 12 bytes minimum
    byte data[128];
    memset(data, 0, sizeof(data));
    
    // Write a minimal IFD entry in little-endian
    // Tag = 0x0100 (ImageWidth)
    data[0] = 0x00; data[1] = 0x01;
    // Type = 3 (SHORT)
    data[2] = 0x03; data[3] = 0x00;
    // Count = 1
    data[4] = 0x01; data[5] = 0x00; data[6] = 0x00; data[7] = 0x00;
    // Value = 640
    data[8] = 0x80; data[9] = 0x02; data[10] = 0x00; data[11] = 0x00;
    
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    entry.setStart(data);
    
    // Should not throw
    EXPECT_NO_THROW(reader.visitEntry(&entry));
}

// Test: Verify byte order preservation across operations
TEST_F(TiffReaderTest_1702, ByteOrderPreservation_1702) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 42);
    
    TiffReader reader(data, sizeof(data), &root, state);
    
    EXPECT_EQ(bigEndian, reader.byteOrder());
    EXPECT_EQ(42u, reader.baseOffset());
    
    // After postProcess (with empty list), state should be restored
    reader.postProcess();
    EXPECT_EQ(bigEndian, reader.byteOrder());
    EXPECT_EQ(42u, reader.baseOffset());
}
