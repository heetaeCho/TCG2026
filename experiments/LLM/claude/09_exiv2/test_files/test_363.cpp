#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// TiffBinaryElement requires tag and group for construction (inherits from TiffEntryBase)
// Based on typical Exiv2 patterns, TiffEntryBase takes (uint16_t tag, IfdId group)

class TiffBinaryElementTest_363 : public ::testing::Test {
protected:
    void SetUp() override {
        // TiffBinaryElement inherits from TiffEntryBase which takes tag and group
        // Using tag=0 and a default group
        element_ = std::make_unique<TiffBinaryElement>(0, IfdId::ifd0Id);
    }

    std::unique_ptr<TiffBinaryElement> element_;
};

// Test default elByteOrder is invalidByteOrder
TEST_F(TiffBinaryElementTest_363, DefaultElByteOrderIsInvalid_363) {
    EXPECT_EQ(element_->elByteOrder(), invalidByteOrder);
}

// Test setting and getting elByteOrder with littleEndian
TEST_F(TiffBinaryElementTest_363, SetElByteOrderLittleEndian_363) {
    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);
}

// Test setting and getting elByteOrder with bigEndian
TEST_F(TiffBinaryElementTest_363, SetElByteOrderBigEndian_363) {
    element_->setElByteOrder(bigEndian);
    EXPECT_EQ(element_->elByteOrder(), bigEndian);
}

// Test setting elByteOrder back to invalidByteOrder
TEST_F(TiffBinaryElementTest_363, SetElByteOrderBackToInvalid_363) {
    element_->setElByteOrder(bigEndian);
    element_->setElByteOrder(invalidByteOrder);
    EXPECT_EQ(element_->elByteOrder(), invalidByteOrder);
}

// Test default elDef values
TEST_F(TiffBinaryElementTest_363, DefaultElDefNotNull_363) {
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
}

// Test default count is 0 (from default elDef_.count_ = 0 based on {0, ttUndefined, 0})
TEST_F(TiffBinaryElementTest_363, DefaultDoCountIsZero_363) {
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->count_, 0u);
}

// Test setElDef and verify through elDef
TEST_F(TiffBinaryElementTest_363, SetElDefAndRetrieve_363) {
    ArrayDef newDef = {1, 5, 10};
    element_->setElDef(newDef);
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->idx_, 1u);
    EXPECT_EQ(def->count_, 10u);
}

// Test that setElDef updates count returned by doCount
TEST_F(TiffBinaryElementTest_363, SetElDefUpdatesCount_363) {
    ArrayDef newDef = {0, 3, 42};
    element_->setElDef(newDef);
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->count_, 42u);
}

// Test setting elDef with zero count
TEST_F(TiffBinaryElementTest_363, SetElDefWithZeroCount_363) {
    ArrayDef newDef = {0, 0, 0};
    element_->setElDef(newDef);
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->count_, 0u);
}

// Test setting elDef with large count
TEST_F(TiffBinaryElementTest_363, SetElDefWithLargeCount_363) {
    ArrayDef newDef = {0, 1, 999999};
    element_->setElDef(newDef);
    const ArrayDef* def = element_->elDef();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def->count_, 999999u);
}

// Test overwriting elDef multiple times
TEST_F(TiffBinaryElementTest_363, OverwriteElDefMultipleTimes_363) {
    ArrayDef def1 = {0, 1, 5};
    element_->setElDef(def1);
    EXPECT_EQ(element_->elDef()->count_, 5u);

    ArrayDef def2 = {1, 2, 10};
    element_->setElDef(def2);
    EXPECT_EQ(element_->elDef()->count_, 10u);

    ArrayDef def3 = {2, 3, 15};
    element_->setElDef(def3);
    EXPECT_EQ(element_->elDef()->count_, 15u);
}

// Test overwriting elByteOrder multiple times
TEST_F(TiffBinaryElementTest_363, OverwriteElByteOrderMultipleTimes_363) {
    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);

    element_->setElByteOrder(bigEndian);
    EXPECT_EQ(element_->elByteOrder(), bigEndian);

    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);
}
