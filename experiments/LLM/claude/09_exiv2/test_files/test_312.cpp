#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for ArrayDef tests
class ArrayDefTest_312 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that size() returns a non-negative value for basic inputs
TEST_F(ArrayDefTest_312, SizeReturnsNonNegativeForBasicInputs_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    def.tiffType_ = unsignedByte;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    EXPECT_GT(result, 0u);
}

// Test that size() scales with count_
TEST_F(ArrayDefTest_312, SizeScalesWithCount_312) {
    ArrayDef def1;
    def1.idx_ = 0;
    def1.count_ = 1;
    def1.tiffType_ = unsignedShort;
    
    ArrayDef def2;
    def2.idx_ = 0;
    def2.count_ = 2;
    def2.tiffType_ = unsignedShort;
    
    size_t size1 = def1.size(0, IfdId::ifd0Id);
    size_t size2 = def2.size(0, IfdId::ifd0Id);
    
    EXPECT_EQ(size2, 2 * size1);
}

// Test that size() returns 0 when count_ is 0
TEST_F(ArrayDefTest_312, SizeReturnsZeroWhenCountIsZero_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 0;
    def.tiffType_ = unsignedShort;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    EXPECT_EQ(result, 0u);
}

// Test size() with unsignedByte type (size should be 1 * count)
TEST_F(ArrayDefTest_312, SizeWithUnsignedByteType_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 5;
    def.tiffType_ = unsignedByte;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    // unsignedByte has typeSize of 1, so result should be 5 * 1 = 5
    EXPECT_EQ(result, 5u);
}

// Test size() with unsignedShort type (size should be 2 * count)
TEST_F(ArrayDefTest_312, SizeWithUnsignedShortType_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 3;
    def.tiffType_ = unsignedShort;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    // unsignedShort has typeSize of 2, so result should be 3 * 2 = 6
    EXPECT_EQ(result, 6u);
}

// Test size() with unsignedLong type (size should be 4 * count)
TEST_F(ArrayDefTest_312, SizeWithUnsignedLongType_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 2;
    def.tiffType_ = unsignedLong;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    // unsignedLong has typeSize of 4, so result should be 2 * 4 = 8
    EXPECT_EQ(result, 8u);
}

// Test size() with unsignedRational type (size should be 8 * count)
TEST_F(ArrayDefTest_312, SizeWithUnsignedRationalType_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    def.tiffType_ = unsignedRational;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    // unsignedRational has typeSize of 8, so result should be 1 * 8 = 8
    EXPECT_EQ(result, 8u);
}

// Test size() with signedShort type
TEST_F(ArrayDefTest_312, SizeWithSignedShortType_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 4;
    def.tiffType_ = signedShort;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    // signedShort has typeSize of 2, so result should be 4 * 2 = 8
    EXPECT_EQ(result, 8u);
}

// Test size() with large count
TEST_F(ArrayDefTest_312, SizeWithLargeCount_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1000;
    def.tiffType_ = unsignedByte;
    
    size_t result = def.size(0, IfdId::ifd0Id);
    EXPECT_EQ(result, 1000u);
}

// Test operator== returns true when idx matches
TEST_F(ArrayDefTest_312, OperatorEqualReturnsTrueWhenIdxMatches_312) {
    ArrayDef def;
    def.idx_ = 5;
    def.count_ = 1;
    def.tiffType_ = unsignedByte;
    
    EXPECT_TRUE(def == 5u);
}

// Test operator== returns false when idx does not match
TEST_F(ArrayDefTest_312, OperatorEqualReturnsFalseWhenIdxDoesNotMatch_312) {
    ArrayDef def;
    def.idx_ = 5;
    def.count_ = 1;
    def.tiffType_ = unsignedByte;
    
    EXPECT_FALSE(def == 3u);
}

// Test operator== with zero idx
TEST_F(ArrayDefTest_312, OperatorEqualWithZeroIdx_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    def.tiffType_ = unsignedByte;
    
    EXPECT_TRUE(def == 0u);
    EXPECT_FALSE(def == 1u);
}

// Test size() with different IfdId groups to verify it handles group parameter
TEST_F(ArrayDefTest_312, SizeWithDifferentGroups_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 2;
    def.tiffType_ = unsignedShort;
    
    size_t result1 = def.size(0, IfdId::ifd0Id);
    size_t result2 = def.size(0, IfdId::ifd1Id);
    
    // For standard types, the size should be the same regardless of group
    // Both should be 2 * 2 = 4
    EXPECT_EQ(result1, 4u);
    EXPECT_EQ(result2, 4u);
}

// Test size() with different tags
TEST_F(ArrayDefTest_312, SizeWithDifferentTags_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    def.tiffType_ = unsignedLong;
    
    size_t result1 = def.size(0x0100, IfdId::ifd0Id);
    size_t result2 = def.size(0x0200, IfdId::ifd0Id);
    
    // For standard types, size should be consistent
    EXPECT_EQ(result1, 4u);
    EXPECT_EQ(result2, 4u);
}

// Test size with count_ = 1 for various types to confirm type size calculation
TEST_F(ArrayDefTest_312, SizeWithCountOneConfirmsTypeSize_312) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    
    def.tiffType_ = unsignedByte;
    EXPECT_EQ(def.size(0, IfdId::ifd0Id), TypeInfo::typeSize(unsignedByte));
    
    def.tiffType_ = unsignedShort;
    EXPECT_EQ(def.size(0, IfdId::ifd0Id), TypeInfo::typeSize(unsignedShort));
    
    def.tiffType_ = unsignedLong;
    EXPECT_EQ(def.size(0, IfdId::ifd0Id), TypeInfo::typeSize(unsignedLong));
}
