#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2::Internal;
using namespace Exiv2;

// TiffBinaryElement requires a tag and group for construction via TiffEntryBase
// We need to figure out the constructor signature from TiffEntryBase

class TiffBinaryElementTest_295 : public ::testing::Test {
protected:
    void SetUp() override {
        // TiffEntryBase typically takes a tag and group
        // Using tag=0x0001, group=1 as reasonable defaults
    }
};

TEST_F(TiffBinaryElementTest_295, DefaultElByteOrder_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

TEST_F(TiffBinaryElementTest_295, SetElByteOrderLittleEndian_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
}

TEST_F(TiffBinaryElementTest_295, SetElByteOrderBigEndian_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
}

TEST_F(TiffBinaryElementTest_295, SetElByteOrderInvalid_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    elem.setElByteOrder(invalidByteOrder);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

TEST_F(TiffBinaryElementTest_295, SetElByteOrderOverwrite_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
}

TEST_F(TiffBinaryElementTest_295, DefaultElDef_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUndefined);
    EXPECT_EQ(def->count_, 0u);
}

TEST_F(TiffBinaryElementTest_295, SetElDef_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    ArrayDef newDef = {5, ttUnsignedShort, 3};
    elem.setElDef(newDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 5u);
    EXPECT_EQ(def->tiffType_, ttUnsignedShort);
    EXPECT_EQ(def->count_, 3u);
}

TEST_F(TiffBinaryElementTest_295, SetElDefMultipleTimes_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    ArrayDef def1 = {1, ttUnsignedByte, 10};
    elem.setElDef(def1);
    const ArrayDef* result1 = elem.elDef();
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->idx_, 1u);

    ArrayDef def2 = {42, ttSignedLong, 7};
    elem.setElDef(def2);
    const ArrayDef* result2 = elem.elDef();
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->idx_, 42u);
    EXPECT_EQ(result2->tiffType_, ttSignedLong);
    EXPECT_EQ(result2->count_, 7u);
}

TEST_F(TiffBinaryElementTest_295, SetElDefZeroValues_295) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    ArrayDef zeroDef = {0, ttUndefined, 0};
    elem.setElDef(zeroDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUndefined);
    EXPECT_EQ(def->count_, 0u);
}
