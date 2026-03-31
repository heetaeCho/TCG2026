#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffBinaryElementTest_349 : public ::testing::Test {
protected:
    void SetUp() override {
        // TiffBinaryElement inherits from TiffEntryBase which requires tag and group
        // Using tag 0x0001 and ifdIdNotSet as a basic construction
    }
};

// Test that default elByteOrder is invalidByteOrder
TEST_F(TiffBinaryElementTest_349, DefaultElByteOrderIsInvalid_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

// Test setting and getting elByteOrder to littleEndian
TEST_F(TiffBinaryElementTest_349, SetElByteOrderLittleEndian_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
}

// Test setting and getting elByteOrder to bigEndian
TEST_F(TiffBinaryElementTest_349, SetElByteOrderBigEndian_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
}

// Test setting elByteOrder back to invalidByteOrder
TEST_F(TiffBinaryElementTest_349, SetElByteOrderBackToInvalid_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
    elem.setElByteOrder(invalidByteOrder);
    EXPECT_EQ(elem.elByteOrder(), invalidByteOrder);
}

// Test that default elDef returns a pointer to default ArrayDef
TEST_F(TiffBinaryElementTest_349, DefaultElDefNotNull_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    const ArrayDef* def = elem.elDef();
    EXPECT_NE(def, nullptr);
}

// Test that default elDef has expected default values
TEST_F(TiffBinaryElementTest_349, DefaultElDefValues_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUndefined);
    EXPECT_EQ(def->count_, 0u);
}

// Test setting elDef and retrieving it
TEST_F(TiffBinaryElementTest_349, SetElDefAndRetrieve_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    ArrayDef customDef = {5, ttUnsignedShort, 3};
    elem.setElDef(customDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 5u);
    EXPECT_EQ(def->tiffType_, ttUnsignedShort);
    EXPECT_EQ(def->count_, 3u);
}

// Test setting elDef with zero count
TEST_F(TiffBinaryElementTest_349, SetElDefZeroCount_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    ArrayDef zeroDef = {0, ttUnsignedByte, 0};
    elem.setElDef(zeroDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUnsignedByte);
    EXPECT_EQ(def->count_, 0u);
}

// Test overwriting elDef
TEST_F(TiffBinaryElementTest_349, OverwriteElDef_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    ArrayDef def1 = {1, ttUnsignedByte, 1};
    elem.setElDef(def1);
    ArrayDef def2 = {10, ttUnsignedLong, 4};
    elem.setElDef(def2);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 10u);
    EXPECT_EQ(def->tiffType_, ttUnsignedLong);
    EXPECT_EQ(def->count_, 4u);
}

// Test multiple byte order changes
TEST_F(TiffBinaryElementTest_349, MultipleByteOrderChanges_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
    elem.setElByteOrder(bigEndian);
    EXPECT_EQ(elem.elByteOrder(), bigEndian);
    elem.setElByteOrder(littleEndian);
    EXPECT_EQ(elem.elByteOrder(), littleEndian);
}

// Test construction with different tag values
TEST_F(TiffBinaryElementTest_349, ConstructWithDifferentTags_349) {
    TiffBinaryElement elem1(0x0000, IfdId::ifdIdNotSet);
    TiffBinaryElement elem2(0xFFFF, IfdId::ifdIdNotSet);
    // Both should have default byte order
    EXPECT_EQ(elem1.elByteOrder(), invalidByteOrder);
    EXPECT_EQ(elem2.elByteOrder(), invalidByteOrder);
}

// Test setElDef with large index value
TEST_F(TiffBinaryElementTest_349, SetElDefLargeIndex_349) {
    TiffBinaryElement elem(0x0001, IfdId::ifdIdNotSet);
    ArrayDef largeDef = {65535, ttSignedLong, 100};
    elem.setElDef(largeDef);
    const ArrayDef* def = elem.elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 65535u);
    EXPECT_EQ(def->count_, 100u);
}
