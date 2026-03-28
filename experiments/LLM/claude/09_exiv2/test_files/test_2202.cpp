#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// ============================================================================
// TiffRwState Tests
// ============================================================================

class TiffRwStateTest_2202 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TiffRwStateTest_2202, ConstructWithLittleEndianAndZeroOffset_2202) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(state.byteOrder(), littleEndian);
    EXPECT_EQ(state.baseOffset(), 0u);
}

TEST_F(TiffRwStateTest_2202, ConstructWithBigEndianAndNonZeroOffset_2202) {
    TiffRwState state(bigEndian, 100);
    EXPECT_EQ(state.byteOrder(), bigEndian);
    EXPECT_EQ(state.baseOffset(), 100u);
}

TEST_F(TiffRwStateTest_2202, ConstructWithLargeBaseOffset_2202) {
    size_t largeOffset = 1024 * 1024;
    TiffRwState state(littleEndian, largeOffset);
    EXPECT_EQ(state.byteOrder(), littleEndian);
    EXPECT_EQ(state.baseOffset(), largeOffset);
}

// ============================================================================
// TiffReader Tests
// ============================================================================

class TiffReaderTest_2202 : public ::testing::Test {
protected:
    void SetUp() override {
        // Minimal valid data buffer
        data_.resize(256, 0);
    }
    void TearDown() override {}

    std::vector<byte> data_;
};

TEST_F(TiffReaderTest_2202, ConstructorInitializesCorrectly_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

TEST_F(TiffReaderTest_2202, ByteOrderReturnsBigEndian_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

TEST_F(TiffReaderTest_2202, BaseOffsetReturnsCorrectValue_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 42);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    EXPECT_EQ(reader.baseOffset(), 42u);
}

TEST_F(TiffReaderTest_2202, SetOrigStateRestoresOriginalState_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(littleEndian, 10);
    
    TiffReader reader(data_.data(), data_.size(), &root, origState);
    
    // Change state via setMnState
    TiffRwState mnState(bigEndian, 20);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 20u);
    
    // Restore original state
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 10u);
}

TEST_F(TiffReaderTest_2202, SetMnStateChangesState_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, origState);
    
    TiffRwState mnState(bigEndian, 50);
    reader.setMnState(&mnState);
    
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 50u);
}

TEST_F(TiffReaderTest_2202, CircularReferenceReturnsFalseForFirstVisit_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    const byte* start = data_.data() + 10;
    bool isCircular = reader.circularReference(start, IfdId::ifd0Id);
    
    EXPECT_FALSE(isCircular);
}

TEST_F(TiffReaderTest_2202, CircularReferenceReturnsTrueForDuplicate_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    const byte* start = data_.data() + 10;
    // First call should register it
    reader.circularReference(start, IfdId::ifd0Id);
    // Second call with same start and group should detect circular reference
    bool isCircular = reader.circularReference(start, IfdId::ifd0Id);
    
    EXPECT_TRUE(isCircular);
}

TEST_F(TiffReaderTest_2202, CircularReferenceReturnsFalseForDifferentGroups_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    const byte* start = data_.data() + 10;
    reader.circularReference(start, IfdId::ifd0Id);
    // Different group should not be circular
    bool isCircular = reader.circularReference(start, IfdId::ifd1Id);
    
    EXPECT_FALSE(isCircular);
}

TEST_F(TiffReaderTest_2202, NextIdxReturnsIncrementingValues_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    
    EXPECT_EQ(idx1, idx0 + 1);
}

TEST_F(TiffReaderTest_2202, NextIdxReturnsDifferentSequencesForDifferentGroups_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    int idx0_group0 = reader.nextIdx(IfdId::ifd0Id);
    int idx0_group1 = reader.nextIdx(IfdId::ifd1Id);
    
    // Both should start from the same initial value (independently)
    EXPECT_EQ(idx0_group0, idx0_group1);
}

TEST_F(TiffReaderTest_2202, ConstructWithZeroSizeData_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    byte dummyByte = 0;
    TiffReader reader(&dummyByte, 0, &root, state);
    
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

TEST_F(TiffReaderTest_2202, PostProcessDoesNotCrash_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    // postProcess should not crash when there's nothing to post-process
    EXPECT_NO_THROW(reader.postProcess());
}

// ============================================================================
// TiffVisitor Go/SetGo Tests
// ============================================================================

class TiffVisitorGoTest_2202 : public ::testing::Test {
protected:
    // We need a concrete TiffVisitor subclass to test go/setGo
    // TiffReader serves as a concrete instance
    void SetUp() override {
        data_.resize(256, 0);
    }
    std::vector<byte> data_;
};

TEST_F(TiffVisitorGoTest_2202, GoDefaultsToTrue_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    // By default, go events should be true
    EXPECT_TRUE(reader.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(reader.go(TiffVisitor::geKnownMakernote));
}

TEST_F(TiffVisitorGoTest_2202, SetGoToFalse_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    reader.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(reader.go(TiffVisitor::geTraverse));
}

TEST_F(TiffVisitorGoTest_2202, SetGoToTrueAfterFalse_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    reader.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(reader.go(TiffVisitor::geTraverse));
    
    reader.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(reader.go(TiffVisitor::geTraverse));
}

TEST_F(TiffVisitorGoTest_2202, SetGoIndependentForDifferentEvents_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    reader.setGo(TiffVisitor::geTraverse, false);
    
    // geKnownMakernote should still be true
    EXPECT_FALSE(reader.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(reader.go(TiffVisitor::geKnownMakernote));
}

// ============================================================================
// TiffReader with various byte orders
// ============================================================================

TEST_F(TiffReaderTest_2202, SetMnStateAndRestoreMultipleTimes_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState origState(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, origState);
    
    // First change
    TiffRwState mnState1(bigEndian, 100);
    reader.setMnState(&mnState1);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 100u);
    
    // Restore
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
    
    // Second change
    TiffRwState mnState2(bigEndian, 200);
    reader.setMnState(&mnState2);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 200u);
    
    // Restore again
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

TEST_F(TiffReaderTest_2202, NextIdxStartsFromZero_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    int firstIdx = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_GE(firstIdx, 0);
}

TEST_F(TiffReaderTest_2202, MultipleNextIdxCallsAreSequential_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    
    EXPECT_EQ(idx1, idx0 + 1);
    EXPECT_EQ(idx2, idx1 + 1);
}

TEST_F(TiffReaderTest_2202, ConstructWithLargeDataSize_2202) {
    std::vector<byte> largeData(1024 * 1024, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 512);
    
    TiffReader reader(largeData.data(), largeData.size(), &root, state);
    
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 512u);
}

TEST_F(TiffReaderTest_2202, CircularReferenceWithDifferentStartsSameGroup_2202) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    
    TiffReader reader(data_.data(), data_.size(), &root, state);
    
    const byte* start1 = data_.data() + 10;
    const byte* start2 = data_.data() + 20;
    
    EXPECT_FALSE(reader.circularReference(start1, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(start2, IfdId::ifd0Id));
    
    // Re-visiting same start should be circular
    EXPECT_TRUE(reader.circularReference(start1, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start2, IfdId::ifd0Id));
}
