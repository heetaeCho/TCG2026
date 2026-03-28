#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal valid TIFF IFD entry in a byte buffer
// TIFF IFD entry format (12 bytes):
//   2 bytes: tag
//   2 bytes: type
//   4 bytes: count
//   4 bytes: value/offset
static std::vector<byte> createMinimalTiffEntry(uint16_t tag, uint16_t type, uint32_t count, uint32_t valueOffset, ByteOrder byteOrder) {
    std::vector<byte> data(12, 0);
    if (byteOrder == littleEndian) {
        data[0] = static_cast<byte>(tag & 0xFF);
        data[1] = static_cast<byte>((tag >> 8) & 0xFF);
        data[2] = static_cast<byte>(type & 0xFF);
        data[3] = static_cast<byte>((type >> 8) & 0xFF);
        data[4] = static_cast<byte>(count & 0xFF);
        data[5] = static_cast<byte>((count >> 8) & 0xFF);
        data[6] = static_cast<byte>((count >> 16) & 0xFF);
        data[7] = static_cast<byte>((count >> 24) & 0xFF);
        data[8] = static_cast<byte>(valueOffset & 0xFF);
        data[9] = static_cast<byte>((valueOffset >> 8) & 0xFF);
        data[10] = static_cast<byte>((valueOffset >> 16) & 0xFF);
        data[11] = static_cast<byte>((valueOffset >> 24) & 0xFF);
    } else {
        data[0] = static_cast<byte>((tag >> 8) & 0xFF);
        data[1] = static_cast<byte>(tag & 0xFF);
        data[2] = static_cast<byte>((type >> 8) & 0xFF);
        data[3] = static_cast<byte>(type & 0xFF);
        data[4] = static_cast<byte>((count >> 24) & 0xFF);
        data[5] = static_cast<byte>((count >> 16) & 0xFF);
        data[6] = static_cast<byte>((count >> 8) & 0xFF);
        data[7] = static_cast<byte>(count & 0xFF);
        data[8] = static_cast<byte>((valueOffset >> 24) & 0xFF);
        data[9] = static_cast<byte>((valueOffset >> 16) & 0xFF);
        data[10] = static_cast<byte>((valueOffset >> 8) & 0xFF);
        data[11] = static_cast<byte>(valueOffset & 0xFF);
    }
    return data;
}

// Minimal TIFF header + IFD for testing
static std::vector<byte> createMinimalTiffBuffer(ByteOrder bo) {
    std::vector<byte> buf;
    // TIFF header (8 bytes)
    if (bo == littleEndian) {
        buf.push_back('I'); buf.push_back('I');
    } else {
        buf.push_back('M'); buf.push_back('M');
    }
    // Magic number 42
    if (bo == littleEndian) {
        buf.push_back(42); buf.push_back(0);
    } else {
        buf.push_back(0); buf.push_back(42);
    }
    // Offset to first IFD (8)
    if (bo == littleEndian) {
        buf.push_back(8); buf.push_back(0); buf.push_back(0); buf.push_back(0);
    } else {
        buf.push_back(0); buf.push_back(0); buf.push_back(0); buf.push_back(8);
    }
    // IFD with 0 entries
    buf.push_back(0); buf.push_back(0);
    // Next IFD offset = 0
    buf.push_back(0); buf.push_back(0); buf.push_back(0); buf.push_back(0);
    
    return buf;
}

class TiffReaderTest_1696 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: TiffReader construction with little-endian byte order
TEST_F(TiffReaderTest_1696, ConstructWithLittleEndian_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    ASSERT_NO_THROW({
        TiffReader reader(data.data(), data.size(), &root, state);
    });
}

// Test: TiffReader construction with big-endian byte order
TEST_F(TiffReaderTest_1696, ConstructWithBigEndian_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(bigEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    
    ASSERT_NO_THROW({
        TiffReader reader(data.data(), data.size(), &root, state);
    });
}

// Test: byteOrder returns the correct byte order
TEST_F(TiffReaderTest_1696, ByteOrderReturnsCorrectOrder_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test: byteOrder returns big endian when constructed with big endian
TEST_F(TiffReaderTest_1696, ByteOrderReturnsBigEndian_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(bigEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test: baseOffset returns the correct base offset
TEST_F(TiffReaderTest_1696, BaseOffsetReturnsCorrectValue_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test: baseOffset with non-zero offset
TEST_F(TiffReaderTest_1696, BaseOffsetWithNonZeroOffset_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 8);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.baseOffset(), 8u);
}

// Test: setOrigState restores original state (byte order should remain the same)
TEST_F(TiffReaderTest_1696, SetOrigStateRestoresState_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    // Change state via setMnState
    TiffRwState mnState(bigEndian, 4);
    reader.setMnState(&mnState);
    // Now byte order might have changed
    
    // Restore original
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test: setMnState changes the state
TEST_F(TiffReaderTest_1696, SetMnStateChangesState_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    
    TiffRwState mnState(bigEndian, 10);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 10u);
}

// Test: circularReference detects no circular reference on first visit
TEST_F(TiffReaderTest_1696, CircularReferenceNoCircularOnFirstVisit_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    const byte* start = data.data() + 8;
    bool isCircular = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_FALSE(isCircular);
}

// Test: circularReference detects circular reference on second visit to same start/group
TEST_F(TiffReaderTest_1696, CircularReferenceDetectsRepeat_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    const byte* start = data.data() + 8;
    reader.circularReference(start, IfdId::ifd0Id);
    bool isCircular = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_TRUE(isCircular);
}

// Test: nextIdx returns incrementing indices for a given group
TEST_F(TiffReaderTest_1696, NextIdxIncrementsForSameGroup_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx1, idx0 + 1);
}

// Test: nextIdx returns independent indices for different groups
TEST_F(TiffReaderTest_1696, NextIdxIndependentForDifferentGroups_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    int idx0_group0 = reader.nextIdx(IfdId::ifd0Id);
    int idx0_group1 = reader.nextIdx(IfdId::ifd1Id);
    // Both should start from the same initial index
    EXPECT_EQ(idx0_group0, idx0_group1);
}

// Test: visitEntry with a TiffEntry object (null pointer should be handled or not crash)
TEST_F(TiffReaderTest_1696, VisitEntryWithNullptr_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    // Passing nullptr - this may or may not crash depending on implementation
    // We test that a valid TiffEntry can be visited
    // Create a TiffEntry with a tag within the data range
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    // The entry doesn't have data set, so visitEntry should handle gracefully
    // This tests that calling visitEntry doesn't crash with an uninitialized entry
    ASSERT_NO_THROW(reader.visitEntry(&entry));
}

// Test: Construction with zero-size data
TEST_F(TiffReaderTest_1696, ConstructWithZeroSizeData_1696) {
    byte dummy = 0;
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    ASSERT_NO_THROW({
        TiffReader reader(&dummy, 0, &root, state);
    });
}

// Test: postProcess can be called without crash
TEST_F(TiffReaderTest_1696, PostProcessNoThrow_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    ASSERT_NO_THROW(reader.postProcess());
}

// Test: circularReference with different groups at same start is not circular
TEST_F(TiffReaderTest_1696, CircularReferenceDifferentGroupsSameStart_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    const byte* start = data.data() + 8;
    bool isCircular1 = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_FALSE(isCircular1);
    
    // Different group, same start - should not be circular
    bool isCircular2 = reader.circularReference(start, IfdId::ifd1Id);
    EXPECT_FALSE(isCircular2);
}

// Test: Multiple nextIdx calls return sequential values
TEST_F(TiffReaderTest_1696, NextIdxSequentialValues_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    
    EXPECT_EQ(idx1, idx0 + 1);
    EXPECT_EQ(idx2, idx0 + 2);
}

// Test: setMnState with nullptr (boundary case)
TEST_F(TiffReaderTest_1696, SetMnStateWithNullptr_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    // Setting MnState with nullptr - depending on implementation this might
    // use internal mnState_ or crash. Testing behavior.
    ASSERT_NO_THROW(reader.setMnState(nullptr));
}

// Test: Verify setOrigState after setMnState restores baseOffset
TEST_F(TiffReaderTest_1696, SetOrigStateRestoresBaseOffset_1696) {
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 42);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.baseOffset(), 42u);
    
    TiffRwState mnState(bigEndian, 100);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.baseOffset(), 100u);
    
    reader.setOrigState();
    EXPECT_EQ(reader.baseOffset(), 42u);
}

// Test: visitDirectory with a TiffDirectory object
TEST_F(TiffReaderTest_1696, VisitDirectoryNoThrow_1696) {
    // Create a buffer with a valid IFD structure
    std::vector<byte> data = createMinimalTiffBuffer(littleEndian);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data.data(), data.size(), &root, state);
    
    TiffDirectory dir(0, IfdId::ifd0Id);
    // Visiting a directory that has no start set may handle gracefully
    ASSERT_NO_THROW(reader.visitDirectory(&dir));
}
