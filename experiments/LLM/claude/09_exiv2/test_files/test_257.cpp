#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

// We need to include necessary headers for Exiv2 types
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffBinaryElement inherits from TiffEntryBase, we need to understand
// construction requirements. Based on the interface, we test public methods.

class TiffBinaryElementTest_257 : public ::testing::Test {
protected:
    // TiffEntryBase typically requires a tag and group for construction
    // We'll create TiffBinaryElement objects in each test as needed
};

TEST_F(TiffBinaryElementTest_257, DefaultElByteOrderIsInvalid_257) {
    // A newly constructed TiffBinaryElement should have invalidByteOrder as default
    // Based on the known default: ByteOrder elByteOrder_ = invalidByteOrder
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

TEST_F(TiffBinaryElementTest_257, SetElByteOrderToLittleEndian_257) {
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
}

TEST_F(TiffBinaryElementTest_257, SetElByteOrderToBigEndian_257) {
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
}

TEST_F(TiffBinaryElementTest_257, SetElByteOrderToInvalidByteOrder_257) {
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    // First set to a valid order, then reset to invalid
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
    elem.setElByteOrder(invalidByteOrder);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

TEST_F(TiffBinaryElementTest_257, SetElByteOrderMultipleTimes_257) {
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
}

TEST_F(TiffBinaryElementTest_257, DefaultElDefValues_257) {
    // Default elDef_ should be {0, ttUndefined, 0}
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUndefined);
    EXPECT_EQ(def->count_, 0u);
}

TEST_F(TiffBinaryElementTest_257, SetElDefUpdatesElDef_257) {
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    ArrayDef newDef = {5, ttUnsignedShort, 3};
    elem.setElDef(newDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 5u);
    EXPECT_EQ(def->tiffType_, ttUnsignedShort);
    EXPECT_EQ(def->count_, 3u);
}

TEST_F(TiffBinaryElementTest_257, SetElDefMultipleTimes_257) {
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    
    ArrayDef def1 = {1, ttUnsignedByte, 1};
    elem.setElDef(def1);
    const ArrayDef* result1 = elem.elDef();
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->idx_, 1u);
    EXPECT_EQ(result1->tiffType_, ttUnsignedByte);
    EXPECT_EQ(result1->count_, 1u);
    
    ArrayDef def2 = {10, ttSignedLong, 4};
    elem.setElDef(def2);
    const ArrayDef* result2 = elem.elDef();
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->idx_, 10u);
    EXPECT_EQ(result2->tiffType_, ttSignedLong);
    EXPECT_EQ(result2->count_, 4u);
}

TEST_F(TiffBinaryElementTest_257, ConstructionWithDifferentTagAndGroup_257) {
    TiffBinaryElement elem1(0x0001, IfdId::ifd0Id);
    TiffBinaryElement elem2(0x0100, IfdId::exifId);
    
    // Both should have default byte order
    EXPECT_EQ(elem1.elByteOrder(), invalidByteOrder);
    EXPECT_EQ(elem2.elByteOrder(), invalidByteOrder);
}

TEST_F(TiffBinaryElementTest_257, ElDefReturnsSamePointerAfterSet_257) {
    TiffBinaryElement elem(0, IfdId::ifd0Id);
    ArrayDef newDef = {2, ttUnsignedLong, 1};
    elem.setElDef(newDef);
    
    const ArrayDef* ptr1 = elem.elDef();
    const ArrayDef* ptr2 = elem.elDef();
    // Both calls should return the same pointer (to internal member)
    EXPECT_EQ(ptr1, ptr2);
}
