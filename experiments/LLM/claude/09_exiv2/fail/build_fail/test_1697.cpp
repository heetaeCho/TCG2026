#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "exiv2/exiv2.hpp"

#include <cstring>
#include <vector>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffReaderTest_1697 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal valid TIFF IFD entry in a byte buffer
    // Format: tag(2) + type(2) + count(4) + value/offset(4) = 12 bytes per entry
    std::vector<byte> createMinimalTiffData(ByteOrder byteOrder) {
        std::vector<byte> data(64, 0);
        return data;
    }
};

// Test TiffReader construction with valid parameters
TEST_F(TiffReaderTest_1697, ConstructWithValidData_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    ASSERT_NO_THROW(TiffReader reader(data.data(), data.size(), &root, state));
}

// Test byteOrder returns the correct byte order set during construction
TEST_F(TiffReaderTest_1697, ByteOrderReturnsCorrectOrder_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::littleEndian);
}

// Test byteOrder with big endian
TEST_F(TiffReaderTest_1697, ByteOrderBigEndian_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::bigEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);
}

// Test baseOffset returns the correct offset set during construction
TEST_F(TiffReaderTest_1697, BaseOffsetReturnsCorrectValue_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test baseOffset with non-zero offset
TEST_F(TiffReaderTest_1697, BaseOffsetNonZero_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 8);

    TiffReader reader(data.data(), data.size(), &root, state);
    EXPECT_EQ(reader.baseOffset(), 8u);
}

// Test setOrigState restores original state
TEST_F(TiffReaderTest_1697, SetOrigStateRestoresByteOrder_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, origState);

    // Change to makernote state
    TiffRwState mnState(ByteOrder::bigEndian, 10);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);

    // Restore original
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), ByteOrder::littleEndian);
}

// Test setMnState changes the byte order
TEST_F(TiffReaderTest_1697, SetMnStateChangesByteOrder_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, origState);

    TiffRwState mnState(ByteOrder::bigEndian, 16);
    reader.setMnState(&mnState);

    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);
    EXPECT_EQ(reader.baseOffset(), 16u);
}

// Test circularReference with start pointer within data range
TEST_F(TiffReaderTest_1697, CircularReferenceFirstVisitReturnsFalse_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    // First visit to a location should not be circular
    bool result = reader.circularReference(data.data() + 10, IfdId::ifd0Id);
    EXPECT_FALSE(result);
}

// Test circularReference detects second visit to same location/group
TEST_F(TiffReaderTest_1697, CircularReferenceSecondVisitReturnsTrue_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    const byte* start = data.data() + 10;
    reader.circularReference(start, IfdId::ifd0Id);
    bool result = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test nextIdx returns sequential indices for the same group
TEST_F(TiffReaderTest_1697, NextIdxReturnsSequentialIndices_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx2, idx1 + 1);
}

// Test nextIdx returns independent indices for different groups
TEST_F(TiffReaderTest_1697, NextIdxIndependentForDifferentGroups_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    int idx1_group0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1_group1 = reader.nextIdx(IfdId::ifd1Id);
    // Both should start from the same initial value (independent counters)
    EXPECT_EQ(idx1_group0, idx1_group1);
}

// Test construction with zero size data
TEST_F(TiffReaderTest_1697, ConstructWithZeroSize_1697) {
    byte dummy = 0;
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    ASSERT_NO_THROW(TiffReader reader(&dummy, 0, &root, state));
}

// Test visitDataEntry with a TiffDataEntry object (basic invocation)
TEST_F(TiffReaderTest_1697, VisitDataEntryDoesNotCrashOnEmptyData_1697) {
    // Create a buffer large enough for a TIFF entry (at least 12 bytes for one IFD entry)
    std::vector<byte> data(256, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    // Create a TiffDataEntry - the tag and group are required
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);  // StripOffsets tag

    // visitDataEntry should not crash even with zeroed data
    ASSERT_NO_THROW(reader.visitDataEntry(&entry));
}

// Test visitEntry with a TiffEntry object
TEST_F(TiffReaderTest_1697, VisitEntryDoesNotCrashOnEmptyData_1697) {
    std::vector<byte> data(256, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    TiffEntry entry(0x010e, IfdId::ifd0Id);  // ImageDescription tag
    ASSERT_NO_THROW(reader.visitEntry(&entry));
}

// Test postProcess can be called without prior processing
TEST_F(TiffReaderTest_1697, PostProcessNoOpWhenNothingRead_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);
    ASSERT_NO_THROW(reader.postProcess());
}

// Test circularReference with start pointer outside data range
TEST_F(TiffReaderTest_1697, CircularReferenceOutOfRangePointer_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    // Pointer beyond the data buffer
    const byte* outOfRange = data.data() + data.size() + 100;
    // This should likely be detected as invalid and treated as circular or ignored
    bool result = reader.circularReference(outOfRange, IfdId::ifd0Id);
    // We just verify it doesn't crash; the actual return is implementation-defined
    (void)result;
}

// Test multiple nextIdx calls return incrementing values
TEST_F(TiffReaderTest_1697, NextIdxMultipleCalls_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);

    EXPECT_EQ(idx1, idx0 + 1);
    EXPECT_EQ(idx2, idx0 + 2);
}

// Test setMnState with nullptr - should handle gracefully or use original state
TEST_F(TiffReaderTest_1697, SetMnStateWithNullptr_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, origState);

    // This tests whether nullptr is handled; behavior is implementation-defined
    // but should not crash
    ASSERT_NO_THROW(reader.setMnState(nullptr));
}

// Test switching between makernote state and original state multiple times
TEST_F(TiffReaderTest_1697, StateToggleMultipleTimes_1697) {
    std::vector<byte> data(128, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, origState);

    TiffRwState mnState(ByteOrder::bigEndian, 20);

    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);

    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), ByteOrder::littleEndian);

    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);

    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), ByteOrder::littleEndian);
}

// Test visitDirectory with a TiffDirectory object and zeroed buffer
TEST_F(TiffReaderTest_1697, VisitDirectoryWithZeroedData_1697) {
    std::vector<byte> data(256, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);

    TiffReader reader(data.data(), data.size(), &root, state);

    TiffDirectory dir(0, IfdId::ifd0Id);
    // With zeroed data, directory entry count is 0, should complete without issue
    ASSERT_NO_THROW(reader.visitDirectory(&dir));
}
