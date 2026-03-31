#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

// We need to include necessary headers for the types used
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffBinaryElement inherits from TiffEntryBase, we need to understand
// how to construct it. TiffEntryBase typically takes a tag and group.
// We'll test the public interface: elDef(), elByteOrder(), setElDef(), setElByteOrder()

class TiffBinaryElementTest_256 : public ::testing::Test {
protected:
    void SetUp() override {
        // TiffEntryBase constructor typically takes (tag, group)
        // We create a TiffBinaryElement with some tag and group
    }
};

// Test that default elDef returns a valid pointer with default values
TEST_F(TiffBinaryElementTest_256, DefaultElDef_256) {
    // TiffBinaryElement constructor needs tag and group from TiffEntryBase
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    // Default values based on the known initialization: {0, ttUndefined, 0}
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUndefined);
    EXPECT_EQ(def->count_, 0u);
}

// Test that default elByteOrder returns invalidByteOrder
TEST_F(TiffBinaryElementTest_256, DefaultElByteOrder_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

// Test setElDef changes the elDef
TEST_F(TiffBinaryElementTest_256, SetElDefChangesValue_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    ArrayDef newDef = {5, ttUnsignedShort, 3};
    elem.setElDef(newDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 5u);
    EXPECT_EQ(def->tiffType_, ttUnsignedShort);
    EXPECT_EQ(def->count_, 3u);
}

// Test setElByteOrder changes the byte order to big endian
TEST_F(TiffBinaryElementTest_256, SetElByteOrderBigEndian_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
}

// Test setElByteOrder changes the byte order to little endian
TEST_F(TiffBinaryElementTest_256, SetElByteOrderLittleEndian_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
}

// Test setElByteOrder can be set back to invalidByteOrder
TEST_F(TiffBinaryElementTest_256, SetElByteOrderInvalid_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
    elem.setElByteOrder(invalidByteOrder);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

// Test setElDef multiple times to ensure it updates correctly
TEST_F(TiffBinaryElementTest_256, SetElDefMultipleTimes_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    
    ArrayDef def1 = {1, ttUnsignedByte, 1};
    elem.setElDef(def1);
    const ArrayDef* result1 = elem.elDef();
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->idx_, 1u);
    EXPECT_EQ(result1->tiffType_, ttUnsignedByte);
    EXPECT_EQ(result1->count_, 1u);

    ArrayDef def2 = {10, ttUnsignedLong, 42};
    elem.setElDef(def2);
    const ArrayDef* result2 = elem.elDef();
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->idx_, 10u);
    EXPECT_EQ(result2->tiffType_, ttUnsignedLong);
    EXPECT_EQ(result2->count_, 42u);
}

// Test elDef with zero count boundary
TEST_F(TiffBinaryElementTest_256, SetElDefZeroCount_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    ArrayDef zeroDef = {0, ttUnsignedByte, 0};
    elem.setElDef(zeroDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->count_, 0u);
}

// Test with different tag values
TEST_F(TiffBinaryElementTest_256, DifferentTagValues_256) {
    TiffBinaryElement elem1(0x0000, IfdId::ifd0Id);
    TiffBinaryElement elem2(0xFFFF, IfdId::ifd0Id);
    
    // Both should have default elDef and elByteOrder
    EXPECT_EQ(elem1.elByteOrder(), invalidByteOrder);
    EXPECT_EQ(elem2.elByteOrder(), invalidByteOrder);
    
    const ArrayDef* def1 = elem1.elDef();
    const ArrayDef* def2 = elem2.elDef();
    ASSERT_NE(def1, nullptr);
    ASSERT_NE(def2, nullptr);
}

// Test that setting elDef on one element does not affect another
TEST_F(TiffBinaryElementTest_256, IndependentElements_256) {
    TiffBinaryElement elem1(0x0001, IfdId::ifd0Id);
    TiffBinaryElement elem2(0x0002, IfdId::ifd0Id);
    
    ArrayDef newDef = {7, ttSignedShort, 2};
    elem1.setElDef(newDef);
    elem1.setElByteOrder(bigEndian);
    
    // elem2 should still have defaults
    EXPECT_EQ(elem2.elByteOrder(), invalidByteOrder);
    const ArrayDef* def2 = elem2.elDef();
    ASSERT_NE(def2, nullptr);
    EXPECT_EQ(def2->idx_, 0u);
    EXPECT_EQ(def2->tiffType_, ttUndefined);
    EXPECT_EQ(def2->count_, 0u);
}

// Test large ArrayDef values
TEST_F(TiffBinaryElementTest_256, LargeArrayDefValues_256) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    ArrayDef largeDef = {65535, ttUnsignedLong, 100000};
    elem.setElDef(largeDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 65535u);
    EXPECT_EQ(def->count_, 100000u);
}
