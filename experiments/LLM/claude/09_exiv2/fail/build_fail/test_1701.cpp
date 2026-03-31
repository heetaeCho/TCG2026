#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "types.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal TiffReader for testing
class TiffReaderTest_1701 : public ::testing::Test {
protected:
    void SetUp() override {
        // Minimal data buffer
        data_.resize(64, 0);
    }

    std::vector<byte> data_;
};

// Test that nextIdx returns 1 on first call for a given group
TEST_F(TiffReaderTest_1701, NextIdxReturnsOneOnFirstCall_1701) {
    TiffRwState state(invalidByteOrder, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    int idx = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx, 1);
}

// Test that nextIdx increments on subsequent calls for the same group
TEST_F(TiffReaderTest_1701, NextIdxIncrementsForSameGroup_1701) {
    TiffRwState state(invalidByteOrder, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    int idx3 = reader.nextIdx(IfdId::ifd0Id);

    EXPECT_EQ(idx1, 1);
    EXPECT_EQ(idx2, 2);
    EXPECT_EQ(idx3, 3);
}

// Test that nextIdx maintains separate counters for different groups
TEST_F(TiffReaderTest_1701, NextIdxSeparateCountersPerGroup_1701) {
    TiffRwState state(invalidByteOrder, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    int idxA1 = reader.nextIdx(IfdId::ifd0Id);
    int idxB1 = reader.nextIdx(IfdId::exifId);
    int idxA2 = reader.nextIdx(IfdId::ifd0Id);
    int idxB2 = reader.nextIdx(IfdId::exifId);

    EXPECT_EQ(idxA1, 1);
    EXPECT_EQ(idxB1, 1);
    EXPECT_EQ(idxA2, 2);
    EXPECT_EQ(idxB2, 2);
}

// Test that nextIdx works with multiple different groups independently
TEST_F(TiffReaderTest_1701, NextIdxMultipleGroupsIndependent_1701) {
    TiffRwState state(invalidByteOrder, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 1);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd1Id), 1);
    EXPECT_EQ(reader.nextIdx(IfdId::exifId), 1);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 2);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd1Id), 2);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 3);
}

// Test byteOrder returns the byte order from state
TEST_F(TiffReaderTest_1701, ByteOrderReturnsStateByteOrder_1701) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test byteOrder with big endian
TEST_F(TiffReaderTest_1701, ByteOrderReturnsBigEndian_1701) {
    TiffRwState state(bigEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test baseOffset returns the base offset from state
TEST_F(TiffReaderTest_1701, BaseOffsetReturnsStateBaseOffset_1701) {
    TiffRwState state(littleEndian, 42);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    EXPECT_EQ(reader.baseOffset(), 42u);
}

// Test baseOffset with zero offset
TEST_F(TiffReaderTest_1701, BaseOffsetZero_1701) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test circularReference with start pointer within data range
TEST_F(TiffReaderTest_1701, CircularReferenceFirstVisitReturnsFalse_1701) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    // First visit to a directory start should not be circular
    bool result = reader.circularReference(data_.data() + 10, IfdId::ifd0Id);
    EXPECT_FALSE(result);
}

// Test circularReference detects second visit to same location and group
TEST_F(TiffReaderTest_1701, CircularReferenceSecondVisitReturnsTrue_1701) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    const byte* start = data_.data() + 10;
    reader.circularReference(start, IfdId::ifd0Id);
    bool result = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test that different start pointers with same group are not circular
TEST_F(TiffReaderTest_1701, CircularReferenceDifferentStartNotCircular_1701) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    EXPECT_FALSE(reader.circularReference(data_.data() + 10, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(data_.data() + 20, IfdId::ifd0Id));
}

// Test setOrigState restores original state
TEST_F(TiffReaderTest_1701, SetOrigStateRestoresByteOrder_1701) {
    TiffRwState state(bigEndian, 100);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    // After construction, byteOrder should match original state
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 100u);

    // Call setOrigState and verify it still returns original values
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 100u);
}

// Test nextIdx with many increments
TEST_F(TiffReaderTest_1701, NextIdxManyIncrements_1701) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_.data(), data_.size(), &root, state);

    for (int i = 1; i <= 100; ++i) {
        EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), i);
    }
}
