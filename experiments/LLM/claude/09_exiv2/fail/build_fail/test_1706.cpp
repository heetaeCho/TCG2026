#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffReader tests
class TiffReaderTest_1706 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }
};

// Test TiffRwState construction and accessors
TEST_F(TiffReaderTest_1706, TiffRwState_ByteOrder_1706) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(state.byteOrder(), littleEndian);
}

TEST_F(TiffReaderTest_1706, TiffRwState_BaseOffset_1706) {
    TiffRwState state(bigEndian, 42);
    EXPECT_EQ(state.baseOffset(), 42u);
}

TEST_F(TiffReaderTest_1706, TiffRwState_BigEndianByteOrder_1706) {
    TiffRwState state(bigEndian, 100);
    EXPECT_EQ(state.byteOrder(), bigEndian);
    EXPECT_EQ(state.baseOffset(), 100u);
}

TEST_F(TiffReaderTest_1706, TiffRwState_ZeroBaseOffset_1706) {
    TiffRwState state(littleEndian, 0);
    EXPECT_EQ(state.baseOffset(), 0u);
}

// Test TiffVisitor GoEvent mechanism
TEST_F(TiffReaderTest_1706, TiffVisitor_SetGo_DefaultTrue_1706) {
    // Create a minimal data buffer and TiffReader
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    // By default, go events should be true
    EXPECT_TRUE(reader.go(geTraverse));
    EXPECT_TRUE(reader.go(geKnownMakernote));
}

TEST_F(TiffReaderTest_1706, TiffVisitor_SetGo_DisableTraverse_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    reader.setGo(geTraverse, false);
    EXPECT_FALSE(reader.go(geTraverse));
    EXPECT_TRUE(reader.go(geKnownMakernote));
}

TEST_F(TiffReaderTest_1706, TiffVisitor_SetGo_DisableKnownMakernote_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    reader.setGo(geKnownMakernote, false);
    EXPECT_TRUE(reader.go(geTraverse));
    EXPECT_FALSE(reader.go(geKnownMakernote));
}

TEST_F(TiffReaderTest_1706, TiffVisitor_SetGo_ReEnable_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    reader.setGo(geKnownMakernote, false);
    EXPECT_FALSE(reader.go(geKnownMakernote));

    reader.setGo(geKnownMakernote, true);
    EXPECT_TRUE(reader.go(geKnownMakernote));
}

// Test TiffReader construction and basic accessors
TEST_F(TiffReaderTest_1706, TiffReader_ByteOrder_LittleEndian_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

TEST_F(TiffReaderTest_1706, TiffReader_ByteOrder_BigEndian_1706) {
    byte data[64] = {0};
    TiffRwState state(bigEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

TEST_F(TiffReaderTest_1706, TiffReader_BaseOffset_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 10);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    EXPECT_EQ(reader.baseOffset(), 10u);
}

TEST_F(TiffReaderTest_1706, TiffReader_SetOrigState_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 10);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    // After setting mnState, byteOrder may change; setOrigState should restore
    TiffRwState mnState(bigEndian, 20);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 20u);

    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 10u);
}

TEST_F(TiffReaderTest_1706, TiffReader_SetMnState_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    TiffRwState mnState(bigEndian, 50);
    reader.setMnState(&mnState);

    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 50u);
}

// Test visitIfdMakernote with a null header (no valid makernote header)
TEST_F(TiffReaderTest_1706, VisitIfdMakernote_FailedReadHeader_DisablesGoKnownMakernote_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    // Create a TiffIfdMakernote with nullptr header - readHeader should fail
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setStart(data);

    reader.visitIfdMakernote(&makernote);

    // After a failed readHeader, geKnownMakernote should be set to false
    EXPECT_FALSE(reader.go(geKnownMakernote));
}

// Test that visitIfdMakernote sets image byte order on the object
TEST_F(TiffReaderTest_1706, VisitIfdMakernote_SetsImageByteOrder_1706) {
    byte data[64] = {0};
    TiffRwState state(bigEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setStart(data);

    reader.visitIfdMakernote(&makernote);

    // Even if readHeader fails, setImageByteOrder should have been called
    // We can't directly check imageByteOrder_ but the function should not crash
    EXPECT_FALSE(reader.go(geKnownMakernote));
}

// Test circularReference
TEST_F(TiffReaderTest_1706, CircularReference_FirstVisit_ReturnsFalse_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    // First visit to an address/group should not be circular
    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
}

TEST_F(TiffReaderTest_1706, CircularReference_SecondVisit_ReturnsTrue_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    // First visit
    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
    // Second visit to same address/group should be circular
    EXPECT_TRUE(reader.circularReference(data, IfdId::ifd0Id));
}

TEST_F(TiffReaderTest_1706, CircularReference_DifferentGroups_NotCircular_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(data, IfdId::exifId));
}

TEST_F(TiffReaderTest_1706, CircularReference_DifferentAddresses_NotCircular_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(data + 10, IfdId::ifd0Id));
}

// Test nextIdx
TEST_F(TiffReaderTest_1706, NextIdx_IncrementsForSameGroup_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_LT(idx1, idx2);
}

TEST_F(TiffReaderTest_1706, NextIdx_DifferentGroupsIndependent_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    int idx1_group1 = reader.nextIdx(IfdId::ifd0Id);
    int idx1_group2 = reader.nextIdx(IfdId::exifId);

    // Both should be the first index for their respective group
    EXPECT_EQ(idx1_group1, idx1_group2);
}

// Test with minimal size data buffer
TEST_F(TiffReaderTest_1706, TiffReader_MinimalBuffer_1706) {
    byte data[1] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test TiffIfdMakernote basic properties
TEST_F(TiffReaderTest_1706, TiffIfdMakernote_TagAndGroup_1706) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.tag(), 0x927c);
    EXPECT_EQ(makernote.group(), IfdId::exifId);
}

TEST_F(TiffReaderTest_1706, TiffIfdMakernote_ReadHeaderNullHeader_ReturnsFalse_1706) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[64] = {0};

    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test multiple setMnState / setOrigState transitions
TEST_F(TiffReaderTest_1706, TiffReader_MultipleStateTransitions_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    TiffRwState mnState1(bigEndian, 100);
    reader.setMnState(&mnState1);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 100u);

    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);

    TiffRwState mnState2(bigEndian, 200);
    reader.setMnState(&mnState2);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
    EXPECT_EQ(reader.baseOffset(), 200u);

    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test that visitIfdMakernote with start at beginning of data calculates mnOffset as 0
TEST_F(TiffReaderTest_1706, VisitIfdMakernote_FailedHeader_DoesNotCrash_1706) {
    byte data[256] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setStart(data + 10);

    // Should not crash, should just disable geKnownMakernote
    reader.visitIfdMakernote(&makernote);
    EXPECT_FALSE(reader.go(geKnownMakernote));
}

// Test that geTraverse remains unaffected by visitIfdMakernote failure
TEST_F(TiffReaderTest_1706, VisitIfdMakernote_FailedHeader_TraverseUnaffected_1706) {
    byte data[64] = {0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffReader reader(data, sizeof(data), &root, state);

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setStart(data);

    reader.visitIfdMakernote(&makernote);

    // geTraverse should still be true
    EXPECT_TRUE(reader.go(geTraverse));
    // geKnownMakernote should be false
    EXPECT_FALSE(reader.go(geKnownMakernote));
}
