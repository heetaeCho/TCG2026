#include <gtest/gtest.h>

// Include necessary headers from exiv2
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffBinaryElement inherits from TiffEntryBase, we need to understand
// its construction. Based on the interface, we test the public methods available.

class TiffBinaryElementTest_255 : public ::testing::Test {
protected:
    void SetUp() override {
        // TiffEntryBase typically takes a tag and group in constructor
        // We create a TiffBinaryElement with some tag/group
        element_ = std::make_unique<TiffBinaryElement>(0x0001, IfdId::ifd0Id);
    }

    void TearDown() override {
        element_.reset();
    }

    std::unique_ptr<TiffBinaryElement> element_;
};

// Test that the default byte order is invalidByteOrder
TEST_F(TiffBinaryElementTest_255, DefaultByteOrderIsInvalid_255) {
    EXPECT_EQ(element_->elByteOrder(), invalidByteOrder);
}

// Test setting byte order to little endian
TEST_F(TiffBinaryElementTest_255, SetElByteOrderLittleEndian_255) {
    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);
}

// Test setting byte order to big endian
TEST_F(TiffBinaryElementTest_255, SetElByteOrderBigEndian_255) {
    element_->setElByteOrder(bigEndian);
    EXPECT_EQ(element_->elByteOrder(), bigEndian);
}

// Test setting byte order back to invalidByteOrder
TEST_F(TiffBinaryElementTest_255, SetElByteOrderBackToInvalid_255) {
    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);
    element_->setElByteOrder(invalidByteOrder);
    EXPECT_EQ(element_->elByteOrder(), invalidByteOrder);
}

// Test overwriting byte order
TEST_F(TiffBinaryElementTest_255, OverwriteByteOrder_255) {
    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);
    element_->setElByteOrder(bigEndian);
    EXPECT_EQ(element_->elByteOrder(), bigEndian);
}

// Test default elDef returns pointer to default ArrayDef
TEST_F(TiffBinaryElementTest_255, DefaultElDefNotNull_255) {
    const ArrayDef* def = element_->elDef();
    // Default elDef_ is {0, ttUndefined, 0}, so pointer should be valid
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUndefined);
    EXPECT_EQ(def->count_, 0u);
}

// Test setting elDef
TEST_F(TiffBinaryElementTest_255, SetElDef_255) {
    ArrayDef newDef = {5, ttUnsignedShort, 3};
    element_->setElDef(newDef);
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 5u);
    EXPECT_EQ(def->tiffType_, ttUnsignedShort);
    EXPECT_EQ(def->count_, 3u);
}

// Test setting elDef multiple times
TEST_F(TiffBinaryElementTest_255, SetElDefMultipleTimes_255) {
    ArrayDef def1 = {1, ttUnsignedByte, 1};
    element_->setElDef(def1);
    const ArrayDef* result1 = element_->elDef();
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->idx_, 1u);

    ArrayDef def2 = {10, ttSignedLong, 4};
    element_->setElDef(def2);
    const ArrayDef* result2 = element_->elDef();
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->idx_, 10u);
    EXPECT_EQ(result2->tiffType_, ttSignedLong);
    EXPECT_EQ(result2->count_, 4u);
}

// Test setting elDef with zero values
TEST_F(TiffBinaryElementTest_255, SetElDefZeroValues_255) {
    ArrayDef zeroDef = {0, ttUndefined, 0};
    element_->setElDef(zeroDef);
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 0u);
    EXPECT_EQ(def->tiffType_, ttUndefined);
    EXPECT_EQ(def->count_, 0u);
}

// Test that setting byte order does not affect elDef
TEST_F(TiffBinaryElementTest_255, ByteOrderDoesNotAffectElDef_255) {
    ArrayDef newDef = {7, ttUnsignedLong, 2};
    element_->setElDef(newDef);
    element_->setElByteOrder(bigEndian);

    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 7u);
    EXPECT_EQ(def->tiffType_, ttUnsignedLong);
    EXPECT_EQ(def->count_, 2u);
    EXPECT_EQ(element_->elByteOrder(), bigEndian);
}

// Test that setting elDef does not affect byte order
TEST_F(TiffBinaryElementTest_255, ElDefDoesNotAffectByteOrder_255) {
    element_->setElByteOrder(littleEndian);
    ArrayDef newDef = {3, ttUnsignedShort, 1};
    element_->setElDef(newDef);

    EXPECT_EQ(element_->elByteOrder(), littleEndian);
}
