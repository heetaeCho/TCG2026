#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffBinaryElement inherits from TiffEntryBase which likely requires
// tag and group parameters, we need to construct it properly.
// TiffEntryBase typically takes (uint16_t tag, IfdId group) in constructor.

class TiffBinaryElementTest_254 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test default elByteOrder is invalidByteOrder
TEST_F(TiffBinaryElementTest_254, DefaultElByteOrderIsInvalid_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);
}

// Test setElByteOrder and elByteOrder getter
TEST_F(TiffBinaryElementTest_254, SetElByteOrderLittleEndian_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    element.setElByteOrder(littleEndian);
    EXPECT_EQ(element.elByteOrder(), littleEndian);
}

TEST_F(TiffBinaryElementTest_254, SetElByteOrderBigEndian_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);
}

// Test setting byte order back to invalidByteOrder
TEST_F(TiffBinaryElementTest_254, SetElByteOrderBackToInvalid_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);
    element.setElByteOrder(invalidByteOrder);
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);
}

// Test setElDef and elDef getter
TEST_F(TiffBinaryElementTest_254, SetElDefAndRetrieve_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    ArrayDef def = {0, ttUndefined, 0};
    element.setElDef(def);
    const ArrayDef* result = element.elDef();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->idx_, def.idx_);
    EXPECT_EQ(result->count_, def.count_);
}

// Test setElDef with non-zero values
TEST_F(TiffBinaryElementTest_254, SetElDefWithNonZeroValues_254) {
    TiffBinaryElement element(0x0001, IfdId::ifd0Id);
    ArrayDef def = {5, ttUnsignedShort, 3};
    element.setElDef(def);
    const ArrayDef* result = element.elDef();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->idx_, 5u);
    EXPECT_EQ(result->count_, 3u);
}

// Test elDef returns pointer to internal state (default)
TEST_F(TiffBinaryElementTest_254, DefaultElDefValues_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    const ArrayDef* result = element.elDef();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->idx_, 0u);
    EXPECT_EQ(result->count_, 0u);
}

// Test overwriting elDef
TEST_F(TiffBinaryElementTest_254, OverwriteElDef_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    ArrayDef def1 = {1, ttUnsignedByte, 2};
    element.setElDef(def1);
    const ArrayDef* result1 = element.elDef();
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->idx_, 1u);

    ArrayDef def2 = {10, ttUnsignedLong, 5};
    element.setElDef(def2);
    const ArrayDef* result2 = element.elDef();
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->idx_, 10u);
    EXPECT_EQ(result2->count_, 5u);
}

// Test changing byte order multiple times
TEST_F(TiffBinaryElementTest_254, ChangeByteOrderMultipleTimes_254) {
    TiffBinaryElement element(0x0000, IfdId::ifd0Id);
    element.setElByteOrder(littleEndian);
    EXPECT_EQ(element.elByteOrder(), littleEndian);
    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);
    element.setElByteOrder(littleEndian);
    EXPECT_EQ(element.elByteOrder(), littleEndian);
}
