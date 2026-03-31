#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// We need a minimal ArrayCfg and ArrayDef to construct TiffBinaryArray
// These are needed to create test objects

namespace {

// Helper to create a TiffBinaryArray for testing
// We need valid ArrayCfg to construct one
static const ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,   // group
    invalidByteOrder, // byteOrder
    ttUndefined,      // elTiffType
    notEncrypted,     // cryptFct
    false,            // hasSize
    false,            // hasFillers
    false             // concat
};

static const ArrayDef testArrayDef[] = {
    {0, ttUndefined, 1}
};

class TiffFinderTest_1639 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that visitBinaryArray with matching tag and group sets the result
TEST_F(TiffFinderTest_1639, VisitBinaryArrayMatchingTagAndGroup_1639) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(tag, group);
    TiffBinaryArray binaryArray(tag, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray);
    
    // If tag and group match, result should point to the object
    EXPECT_EQ(finder.result(), &binaryArray);
}

// Test that visitBinaryArray with non-matching tag does not set result
TEST_F(TiffFinderTest_1639, VisitBinaryArrayNonMatchingTag_1639) {
    uint16_t searchTag = 0x0001;
    uint16_t objectTag = 0x0002;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(searchTag, group);
    TiffBinaryArray binaryArray(objectTag, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray);
    
    // Tag doesn't match, result should be nullptr
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that visitBinaryArray with non-matching group does not set result
TEST_F(TiffFinderTest_1639, VisitBinaryArrayNonMatchingGroup_1639) {
    uint16_t tag = 0x0001;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId objectGroup = IfdId::ifd1Id;
    
    TiffFinder finder(tag, searchGroup);
    TiffBinaryArray binaryArray(tag, objectGroup, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray);
    
    // Group doesn't match, result should be nullptr
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that result is initially nullptr
TEST_F(TiffFinderTest_1639, InitialResultIsNull_1639) {
    TiffFinder finder(0x0001, IfdId::ifd0Id);
    
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that init resets the finder state
TEST_F(TiffFinderTest_1639, InitResetsState_1639) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(tag, group);
    TiffBinaryArray binaryArray(tag, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray);
    EXPECT_EQ(finder.result(), &binaryArray);
    
    // Re-init with different tag/group, result should be reset
    finder.init(0x0002, IfdId::ifd1Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that init allows finding a new object
TEST_F(TiffFinderTest_1639, InitAllowsFindingNewObject_1639) {
    uint16_t tag1 = 0x0001;
    uint16_t tag2 = 0x0002;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(tag1, group);
    TiffBinaryArray binaryArray1(tag1, group, testArrayCfg, testArrayDef, 1);
    TiffBinaryArray binaryArray2(tag2, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray1);
    EXPECT_EQ(finder.result(), &binaryArray1);
    
    finder.init(tag2, group);
    finder.visitBinaryArray(&binaryArray2);
    EXPECT_EQ(finder.result(), &binaryArray2);
}

// Test visiting multiple binary arrays, only matching one is found
TEST_F(TiffFinderTest_1639, VisitMultipleBinaryArraysOnlyMatchIsFound_1639) {
    uint16_t searchTag = 0x0003;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(searchTag, group);
    
    TiffBinaryArray binaryArray1(0x0001, group, testArrayCfg, testArrayDef, 1);
    TiffBinaryArray binaryArray2(0x0002, group, testArrayCfg, testArrayDef, 1);
    TiffBinaryArray binaryArray3(searchTag, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray1);
    EXPECT_EQ(finder.result(), nullptr);
    
    finder.visitBinaryArray(&binaryArray2);
    EXPECT_EQ(finder.result(), nullptr);
    
    finder.visitBinaryArray(&binaryArray3);
    EXPECT_EQ(finder.result(), &binaryArray3);
}

// Test with both tag and group not matching
TEST_F(TiffFinderTest_1639, VisitBinaryArrayBothNonMatching_1639) {
    TiffFinder finder(0x0001, IfdId::ifd0Id);
    TiffBinaryArray binaryArray(0x0002, IfdId::ifd1Id, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray);
    
    EXPECT_EQ(finder.result(), nullptr);
}

// Test with tag 0 boundary
TEST_F(TiffFinderTest_1639, VisitBinaryArrayTagZero_1639) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(tag, group);
    TiffBinaryArray binaryArray(tag, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray);
    
    EXPECT_EQ(finder.result(), &binaryArray);
}

// Test with max tag boundary
TEST_F(TiffFinderTest_1639, VisitBinaryArrayMaxTag_1639) {
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(tag, group);
    TiffBinaryArray binaryArray(tag, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&binaryArray);
    
    EXPECT_EQ(finder.result(), &binaryArray);
}

// Test that once a match is found, visiting a non-matching object doesn't clear the result
TEST_F(TiffFinderTest_1639, MatchPersistsAfterNonMatch_1639) {
    uint16_t searchTag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    
    TiffFinder finder(searchTag, group);
    TiffBinaryArray matchingArray(searchTag, group, testArrayCfg, testArrayDef, 1);
    TiffBinaryArray nonMatchingArray(0x0002, group, testArrayCfg, testArrayDef, 1);
    
    finder.visitBinaryArray(&matchingArray);
    EXPECT_EQ(finder.result(), &matchingArray);
    
    // Visiting a non-matching object should not clear the previously found result
    finder.visitBinaryArray(&nonMatchingArray);
    EXPECT_EQ(finder.result(), &matchingArray);
}

} // namespace
