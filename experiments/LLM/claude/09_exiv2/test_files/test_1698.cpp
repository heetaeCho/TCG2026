#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Minimal valid TIFF data buffer for testing
// TIFF header: byte order (II = little endian), magic number 42, offset to first IFD
static const byte minimalTiffLE[] = {
    0x49, 0x49,             // Byte order: little-endian
    0x2A, 0x00,             // Magic number: 42
    0x08, 0x00, 0x00, 0x00, // Offset to first IFD: 8
    // IFD with 0 entries
    0x00, 0x00,             // Number of directory entries: 0
    0x00, 0x00, 0x00, 0x00  // Next IFD offset: 0
};

static const byte minimalTiffBE[] = {
    0x4D, 0x4D,             // Byte order: big-endian
    0x00, 0x2A,             // Magic number: 42
    0x00, 0x00, 0x00, 0x08, // Offset to first IFD: 8
    // IFD with 0 entries
    0x00, 0x00,             // Number of directory entries: 0
    0x00, 0x00, 0x00, 0x00  // Next IFD offset: 0
};

class TiffReaderTest_1698 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffReader can be constructed with little-endian state
TEST_F(TiffReaderTest_1698, ConstructWithLittleEndian_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    EXPECT_NO_THROW({
        TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    });
}

// Test that TiffReader can be constructed with big-endian state
TEST_F(TiffReaderTest_1698, ConstructWithBigEndian_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    
    EXPECT_NO_THROW({
        TiffReader reader(minimalTiffBE, sizeof(minimalTiffBE), &root, state);
    });
}

// Test byteOrder returns the correct byte order (little endian)
TEST_F(TiffReaderTest_1698, ByteOrderLittleEndian_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test byteOrder returns the correct byte order (big endian)
TEST_F(TiffReaderTest_1698, ByteOrderBigEndian_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    TiffReader reader(minimalTiffBE, sizeof(minimalTiffBE), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test baseOffset returns the configured base offset
TEST_F(TiffReaderTest_1698, BaseOffsetZero_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test baseOffset with non-zero offset
TEST_F(TiffReaderTest_1698, BaseOffsetNonZero_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 4);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    EXPECT_EQ(reader.baseOffset(), 4u);
}

// Test setOrigState restores original state
TEST_F(TiffReaderTest_1698, SetOrigStateRestoresByteOrder_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    // After setting original state, byte order should remain as originally configured
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test setMnState changes state
TEST_F(TiffReaderTest_1698, SetMnStateChangesState_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    TiffRwState mnState(bigEndian, 8);
    reader.setMnState(&mnState);
    
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 8u);
}

// Test setOrigState after setMnState
TEST_F(TiffReaderTest_1698, SetOrigStateAfterMnState_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    TiffRwState mnState(bigEndian, 8);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test circularReference returns false for first visit
TEST_F(TiffReaderTest_1698, CircularReferenceFirstVisitReturnsFalse_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    // First visit to a given start/group should not be circular
    bool result = reader.circularReference(minimalTiffLE + 8, IfdId::ifd0Id);
    EXPECT_FALSE(result);
}

// Test circularReference returns true for second visit to same location
TEST_F(TiffReaderTest_1698, CircularReferenceSecondVisitReturnsTrue_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    const byte* start = minimalTiffLE + 8;
    reader.circularReference(start, IfdId::ifd0Id);
    bool result = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test nextIdx returns sequential indices for the same group
TEST_F(TiffReaderTest_1698, NextIdxReturnsSequentialIndices_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    
    EXPECT_EQ(idx1, idx0 + 1);
}

// Test nextIdx for different groups are independent
TEST_F(TiffReaderTest_1698, NextIdxDifferentGroupsIndependent_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    int idx0_group0 = reader.nextIdx(IfdId::ifd0Id);
    int idx0_group1 = reader.nextIdx(IfdId::exifId);
    
    // Both should be the first index for their respective groups
    EXPECT_EQ(idx0_group0, idx0_group1);
}

// Test visitImageEntry with a TiffImageEntry object - basic call shouldn't crash
TEST_F(TiffReaderTest_1698, VisitImageEntryBasicCall_1698) {
    // Create a TIFF data buffer with a valid IFD entry for StripOffsets
    // Tag 273 (0x0111) = StripOffsets, Type 3 (SHORT), Count 1, Value offset
    byte tiffData[128] = {0};
    // Little-endian header
    tiffData[0] = 0x49; tiffData[1] = 0x49; // II
    tiffData[2] = 0x2A; tiffData[3] = 0x00; // 42
    tiffData[4] = 0x08; tiffData[5] = 0x00; tiffData[6] = 0x00; tiffData[7] = 0x00; // offset 8
    // IFD: 1 entry
    tiffData[8] = 0x01; tiffData[9] = 0x00;
    // Entry: tag=0x0111 (StripOffsets), type=3 (SHORT), count=1, value=0
    tiffData[10] = 0x11; tiffData[11] = 0x01; // tag
    tiffData[12] = 0x03; tiffData[13] = 0x00; // type SHORT
    tiffData[14] = 0x01; tiffData[15] = 0x00; tiffData[16] = 0x00; tiffData[17] = 0x00; // count
    tiffData[18] = 0x00; tiffData[19] = 0x00; tiffData[20] = 0x00; tiffData[21] = 0x00; // value
    // Next IFD offset: 0
    tiffData[22] = 0x00; tiffData[23] = 0x00; tiffData[24] = 0x00; tiffData[25] = 0x00;
    
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(tiffData, sizeof(tiffData), &root, state);
    
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    // This should not crash - it calls readDataEntryBase internally
    EXPECT_NO_THROW(reader.visitImageEntry(&entry));
}

// Test visitEntry with a TiffEntry object
TEST_F(TiffReaderTest_1698, VisitEntryBasicCall_1698) {
    byte tiffData[128] = {0};
    tiffData[0] = 0x49; tiffData[1] = 0x49;
    tiffData[2] = 0x2A; tiffData[3] = 0x00;
    tiffData[4] = 0x08; tiffData[5] = 0x00; tiffData[6] = 0x00; tiffData[7] = 0x00;
    tiffData[8] = 0x00; tiffData[9] = 0x00;
    tiffData[10] = 0x00; tiffData[11] = 0x00; tiffData[12] = 0x00; tiffData[13] = 0x00;
    
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(tiffData, sizeof(tiffData), &root, state);
    
    TiffEntry entry(0x010E, IfdId::ifd0Id); // ImageDescription
    
    EXPECT_NO_THROW(reader.visitEntry(&entry));
}

// Test postProcess doesn't crash on empty data
TEST_F(TiffReaderTest_1698, PostProcessNoEntries_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    EXPECT_NO_THROW(reader.postProcess());
}

// Test with zero-size data
TEST_F(TiffReaderTest_1698, ConstructWithZeroSize_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    byte emptyData = 0;
    
    EXPECT_NO_THROW({
        TiffReader reader(&emptyData, 0, &root, state);
    });
}

// Test visitDirectory with minimal valid directory
TEST_F(TiffReaderTest_1698, VisitDirectoryMinimal_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    TiffDirectory dir(0, IfdId::ifd0Id);
    
    // This may detect circular reference or handle gracefully
    EXPECT_NO_THROW(reader.visitDirectory(&dir));
}

// Test multiple calls to nextIdx
TEST_F(TiffReaderTest_1698, NextIdxMultipleCalls_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    
    EXPECT_EQ(idx1, idx0 + 1);
    EXPECT_EQ(idx2, idx1 + 1);
}

// Test circularReference with different groups at same location
TEST_F(TiffReaderTest_1698, CircularReferenceDifferentGroups_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    const byte* start = minimalTiffLE + 8;
    bool result1 = reader.circularReference(start, IfdId::ifd0Id);
    // Different group at same location - implementation specific behavior
    bool result2 = reader.circularReference(start, IfdId::exifId);
    
    EXPECT_FALSE(result1);
    // Second call with different group may or may not be circular depending on implementation
    // We just verify it doesn't crash
}

// Test setMnState with nullptr - boundary condition
TEST_F(TiffReaderTest_1698, SetMnStateWithNullptr_1698) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(minimalTiffLE, sizeof(minimalTiffLE), &root, state);
    
    // Passing nullptr may or may not be valid; test that behavior is defined
    // This tests boundary behavior
    reader.setMnState(nullptr);
    // After null state, original state should be recoverable
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}
