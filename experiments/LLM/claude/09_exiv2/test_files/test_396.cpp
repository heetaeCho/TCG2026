#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffBinaryElement
class TiffBinaryElementTest_396 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a TiffBinaryElement with some default tag, group, and tiffType
        element_ = std::make_unique<TiffBinaryElement>(0x0001, IfdId::ifd0Id, ttUndefined);
    }

    void TearDown() override {
        element_.reset();
    }

    std::unique_ptr<TiffBinaryElement> element_;
};

// Test that doSize returns 0 when no value is set (pValue() is null)
TEST_F(TiffBinaryElementTest_396, DoSizeReturnsZeroWhenNoValue_396) {
    // When no value has been set, pValue() should be null
    EXPECT_EQ(element_->pValue(), nullptr);
    // The size accessible through the public interface should reflect doSize() returning 0
    // We can't call doSize directly (protected), but we can check pValue is null
    // which based on the implementation means doSize returns 0
    ASSERT_EQ(element_->pValue(), nullptr);
}

// Test that after setting a value, pValue() is not null
TEST_F(TiffBinaryElementTest_396, SetValueMakesPValueNonNull_396) {
    auto value = Value::create(unsignedByte);
    ASSERT_NE(value, nullptr);
    
    // Read a single byte value
    const byte data[] = {0x42};
    value->read(data, 1, littleEndian);
    
    element_->setValue(std::move(value));
    
    EXPECT_NE(element_->pValue(), nullptr);
}

// Test that pValue()->size() returns correct size after setting a value
TEST_F(TiffBinaryElementTest_396, ValueSizeAfterSetValue_396) {
    auto value = Value::create(unsignedByte);
    ASSERT_NE(value, nullptr);
    
    const byte data[] = {0x01, 0x02, 0x03};
    value->read(data, 3, littleEndian);
    
    element_->setValue(std::move(value));
    
    ASSERT_NE(element_->pValue(), nullptr);
    EXPECT_EQ(element_->pValue()->size(), 3u);
}

// Test that pValue()->size() returns 1 for single byte value
TEST_F(TiffBinaryElementTest_396, ValueSizeSingleByte_396) {
    auto value = Value::create(unsignedByte);
    ASSERT_NE(value, nullptr);
    
    const byte data[] = {0xFF};
    value->read(data, 1, littleEndian);
    
    element_->setValue(std::move(value));
    
    ASSERT_NE(element_->pValue(), nullptr);
    EXPECT_EQ(element_->pValue()->size(), 1u);
}

// Test setElDef and elDef
TEST_F(TiffBinaryElementTest_396, SetAndGetElDef_396) {
    ArrayDef def = {0, ttUnsignedShort, 2};
    element_->setElDef(def);
    
    const ArrayDef* retrieved = element_->elDef();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->tiffType_, ttUnsignedShort);
    EXPECT_EQ(retrieved->count_, 2u);
}

// Test setElByteOrder and elByteOrder
TEST_F(TiffBinaryElementTest_396, SetAndGetElByteOrder_396) {
    element_->setElByteOrder(bigEndian);
    EXPECT_EQ(element_->elByteOrder(), bigEndian);
}

// Test default elByteOrder is invalidByteOrder
TEST_F(TiffBinaryElementTest_396, DefaultElByteOrderIsInvalid_396) {
    EXPECT_EQ(element_->elByteOrder(), invalidByteOrder);
}

// Test setElByteOrder with littleEndian
TEST_F(TiffBinaryElementTest_396, SetElByteOrderLittleEndian_396) {
    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);
}

// Test tiffType returns the type set in constructor
TEST_F(TiffBinaryElementTest_396, TiffTypeFromConstructor_396) {
    EXPECT_EQ(element_->tiffType(), ttUndefined);
}

// Test construction with different tiffType
TEST_F(TiffBinaryElementTest_396, ConstructWithDifferentTiffType_396) {
    TiffBinaryElement elem(0x0002, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(elem.tiffType(), ttUnsignedShort);
}

// Test pData returns null when no data is set
TEST_F(TiffBinaryElementTest_396, PDataNullInitially_396) {
    EXPECT_EQ(element_->pData(), nullptr);
}

// Test offset default value
TEST_F(TiffBinaryElementTest_396, DefaultOffset_396) {
    EXPECT_EQ(element_->offset(), 0u);
}

// Test setOffset and offset
TEST_F(TiffBinaryElementTest_396, SetAndGetOffset_396) {
    element_->setOffset(12345);
    EXPECT_EQ(element_->offset(), 12345u);
}

// Test setValue replaces existing value
TEST_F(TiffBinaryElementTest_396, SetValueReplacesExistingValue_396) {
    auto value1 = Value::create(unsignedByte);
    const byte data1[] = {0x01};
    value1->read(data1, 1, littleEndian);
    element_->setValue(std::move(value1));
    
    ASSERT_NE(element_->pValue(), nullptr);
    EXPECT_EQ(element_->pValue()->size(), 1u);
    
    auto value2 = Value::create(unsignedByte);
    const byte data2[] = {0x02, 0x03};
    value2->read(data2, 2, littleEndian);
    element_->setValue(std::move(value2));
    
    ASSERT_NE(element_->pValue(), nullptr);
    EXPECT_EQ(element_->pValue()->size(), 2u);
}

// Test setData with shared buffer
TEST_F(TiffBinaryElementTest_396, SetDataWithSharedBuffer_396) {
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    
    element_->setData(buf->data(), 10, buf);
    
    EXPECT_NE(element_->pData(), nullptr);
    EXPECT_EQ(element_->pData()[0], 0xAB);
}

// Test setData with DataBuf shared_ptr
TEST_F(TiffBinaryElementTest_396, SetDataWithDataBufPtr_396) {
    auto buf = std::make_shared<DataBuf>(5);
    std::memset(buf->data(), 0xCD, 5);
    
    element_->setData(buf);
    
    EXPECT_NE(element_->pData(), nullptr);
}

// Test idx default value
TEST_F(TiffBinaryElementTest_396, DefaultIdx_396) {
    EXPECT_EQ(element_->idx(), 0);
}

// Test updateValue with a value
TEST_F(TiffBinaryElementTest_396, UpdateValue_396) {
    auto value = Value::create(unsignedByte);
    const byte data[] = {0x10, 0x20};
    value->read(data, 2, littleEndian);
    
    element_->updateValue(std::move(value), littleEndian);
    
    ASSERT_NE(element_->pValue(), nullptr);
}

// Test multiple elByteOrder changes
TEST_F(TiffBinaryElementTest_396, MultipleElByteOrderChanges_396) {
    element_->setElByteOrder(littleEndian);
    EXPECT_EQ(element_->elByteOrder(), littleEndian);
    
    element_->setElByteOrder(bigEndian);
    EXPECT_EQ(element_->elByteOrder(), bigEndian);
    
    element_->setElByteOrder(invalidByteOrder);
    EXPECT_EQ(element_->elByteOrder(), invalidByteOrder);
}

// Test with empty value (size 0 after read with 0 bytes)
TEST_F(TiffBinaryElementTest_396, EmptyValueSize_396) {
    auto value = Value::create(unsignedByte);
    // Don't read any data into the value
    element_->setValue(std::move(value));
    
    ASSERT_NE(element_->pValue(), nullptr);
    EXPECT_EQ(element_->pValue()->size(), 0u);
}

// Test construction with tag 0
TEST_F(TiffBinaryElementTest_396, ConstructWithTagZero_396) {
    TiffBinaryElement elem(0x0000, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(elem.tiffType(), ttUndefined);
    EXPECT_EQ(elem.pValue(), nullptr);
    EXPECT_EQ(elem.pData(), nullptr);
}

// Test that setElDef can be called multiple times
TEST_F(TiffBinaryElementTest_396, SetElDefMultipleTimes_396) {
    ArrayDef def1 = {0, ttUnsignedByte, 1};
    element_->setElDef(def1);
    
    const ArrayDef* retrieved1 = element_->elDef();
    ASSERT_NE(retrieved1, nullptr);
    EXPECT_EQ(retrieved1->tiffType_, ttUnsignedByte);
    
    ArrayDef def2 = {1, ttUnsignedLong, 4};
    element_->setElDef(def2);
    
    const ArrayDef* retrieved2 = element_->elDef();
    ASSERT_NE(retrieved2, nullptr);
    EXPECT_EQ(retrieved2->tiffType_, ttUnsignedLong);
}
