#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffReader tests
class TiffReaderTest_1694 : public ::testing::Test {
protected:
    void SetUp() override {
        // Minimal valid TIFF-like data buffer
        // We need at least some bytes for the reader to work with
        memset(data_, 0, sizeof(data_));
    }

    byte data_[256];
};

// Test fixture for TiffRwState tests
class TiffRwStateTest_1694 : public ::testing::Test {
protected:
};

// ==================== TiffRwState Tests ====================

TEST_F(TiffRwStateTest_1694, ConstructorSetsBaseOffset_1694) {
    TiffRwState state(littleEndian, 42);
    EXPECT_EQ(state.baseOffset(), 42u);
}

TEST_F(TiffRwStateTest_1694, ConstructorSetsByteOrder_1694) {
    TiffRwState state(bigEndian, 0);
    EXPECT_EQ(state.byteOrder(), bigEndian);
}

TEST_F(TiffRwStateTest_1694, BaseOffsetZero_1694) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(state.baseOffset(), 0u);
}

TEST_F(TiffRwStateTest_1694, BaseOffsetLargeValue_1694) {
    TiffRwState state(littleEndian, 1000000);
    EXPECT_EQ(state.baseOffset(), 1000000u);
}

TEST_F(TiffRwStateTest_1694, LittleEndianByteOrder_1694) {
    TiffRwState state(littleEndian, 10);
    EXPECT_EQ(state.byteOrder(), littleEndian);
}

TEST_F(TiffRwStateTest_1694, BigEndianByteOrder_1694) {
    TiffRwState state(bigEndian, 10);
    EXPECT_EQ(state.byteOrder(), bigEndian);
}

// ==================== TiffReader Tests ====================

TEST_F(TiffReaderTest_1694, BaseOffsetReturnsInitialValue_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

TEST_F(TiffReaderTest_1694, BaseOffsetWithNonZeroOffset_1694) {
    TiffRwState state(littleEndian, 16);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);
    EXPECT_EQ(reader.baseOffset(), 16u);
}

TEST_F(TiffReaderTest_1694, ByteOrderReturnsLittleEndian_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

TEST_F(TiffReaderTest_1694, ByteOrderReturnsBigEndian_1694) {
    TiffRwState state(bigEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

TEST_F(TiffReaderTest_1694, SetOrigStateRestoresState_1694) {
    TiffRwState origState(littleEndian, 100);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, origState);

    // Change state via setMnState
    TiffRwState mnState(bigEndian, 200);
    reader.setMnState(&mnState);

    // Verify state changed
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 200u);

    // Restore original state
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 100u);
}

TEST_F(TiffReaderTest_1694, SetMnStateChangesState_1694) {
    TiffRwState origState(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, origState);

    TiffRwState mnState(bigEndian, 50);
    reader.setMnState(&mnState);

    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 50u);
}

TEST_F(TiffReaderTest_1694, CircularReferenceFirstCallReturnsFalse_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);

    // First reference to a start/group should not be circular
    EXPECT_FALSE(reader.circularReference(data_, IfdId::ifd0Id));
}

TEST_F(TiffReaderTest_1694, CircularReferenceSecondCallReturnsTrue_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);

    // First call should not detect circular reference
    EXPECT_FALSE(reader.circularReference(data_, IfdId::ifd0Id));
    // Second call with same start and group should detect circular reference
    EXPECT_TRUE(reader.circularReference(data_, IfdId::ifd0Id));
}

TEST_F(TiffReaderTest_1694, CircularReferenceDifferentGroupsNotCircular_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);

    EXPECT_FALSE(reader.circularReference(data_, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(data_ + 10, IfdId::ifd1Id));
}

TEST_F(TiffReaderTest_1694, NextIdxReturnsIncrementingValues_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);

    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx1, idx0 + 1);
}

TEST_F(TiffReaderTest_1694, NextIdxDifferentGroupsIndependent_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);

    int idx0_group0 = reader.nextIdx(IfdId::ifd0Id);
    int idx0_group1 = reader.nextIdx(IfdId::ifd1Id);
    // Both should start at the same initial index value
    EXPECT_EQ(idx0_group0, idx0_group1);
}

TEST_F(TiffReaderTest_1694, NextIdxStartsAtZero_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);

    int idx = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx, 0);
}

TEST_F(TiffReaderTest_1694, BaseOffsetLargeOffset_1694) {
    TiffRwState state(littleEndian, 0xFFFF);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);
    EXPECT_EQ(reader.baseOffset(), 0xFFFFu);
}

TEST_F(TiffReaderTest_1694, PostProcessDoesNotCrash_1694) {
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, state);

    // postProcess should not crash even with no entries processed
    EXPECT_NO_THROW(reader.postProcess());
}

TEST_F(TiffReaderTest_1694, MinimalDataSize_1694) {
    byte minData[1] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(minData, 1, &root, state);
    EXPECT_EQ(reader.baseOffset(), 0u);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

TEST_F(TiffReaderTest_1694, SetMnStateThenSetOrigStateRestoresCompletely_1694) {
    TiffRwState origState(bigEndian, 77);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, origState);

    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 77u);

    TiffRwState mnState(littleEndian, 999);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 999u);

    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 77u);
}

TEST_F(TiffReaderTest_1694, MultipleSetMnStateCalls_1694) {
    TiffRwState origState(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data_, sizeof(data_), &root, origState);

    TiffRwState mnState1(bigEndian, 10);
    reader.setMnState(&mnState1);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 10u);

    TiffRwState mnState2(littleEndian, 20);
    reader.setMnState(&mnState2);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 20u);

    // setOrigState should still restore the original
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}
