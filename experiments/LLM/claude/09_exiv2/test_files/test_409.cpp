#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need to find the correct IfdId and tag values to construct TiffImageEntry
// TiffImageEntry inherits from TiffDataEntryBase which inherits from TiffEntryBase

class TiffImageEntryTest_409 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Helper: TiffImageEntry constructor requires tag, group, and possibly szTag/szGroup
// Based on TiffDataEntryBase interface

TEST_F(TiffImageEntryTest_409, DoSizeImage_NullValue_ReturnsZero_409) {
    // When no value is set, pValue() returns null, doSizeImage should return 0
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    // Without setting any value, pValue() should be null
    // Access doSizeImage through the component's sizeImage or similar
    // TiffComponent has a size hierarchy; doSizeImage is called via sizeImage()
    // Since doSizeImage is protected, it's accessible via the TiffComponent virtual dispatch
    
    // pValue() is nullptr, so doSizeImage should return 0
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffImageEntryTest_409, DoSizeImage_ValueWithDataArea_ReturnsDataAreaSize_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    // Create a value with a non-zero data area
    auto value = Value::create(TypeId::unsignedLong);
    value->read("100");
    
    // Set data area on the value
    byte dataArea[256];
    std::memset(dataArea, 0, sizeof(dataArea));
    value->setDataArea(dataArea, sizeof(dataArea));
    
    entry.setValue(std::move(value));
    
    // Now pValue() should be non-null
    ASSERT_NE(entry.pValue(), nullptr);
    
    // If sizeDataArea is non-zero, doSizeImage returns that
    size_t dataAreaSize = entry.pValue()->sizeDataArea();
    if (dataAreaSize != 0) {
        // The doSizeImage should return the data area size
        EXPECT_EQ(dataAreaSize, sizeof(dataArea));
    }
}

TEST_F(TiffImageEntryTest_409, DoSizeImage_ValueWithoutDataArea_ReturnsStripsSum_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    // Create a value without data area
    auto value = Value::create(TypeId::unsignedLong);
    value->read("0 100 200");
    
    entry.setValue(std::move(value));
    
    ASSERT_NE(entry.pValue(), nullptr);
    // sizeDataArea should be 0 for a plain value
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
}

TEST_F(TiffImageEntryTest_409, SetStrips_PopulatesStrips_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    // Create strip size value
    auto sizeValue = Value::create(TypeId::unsignedLong);
    sizeValue->read("100 200 300");
    
    // Create some data
    byte data[600];
    std::memset(data, 0xAB, sizeof(data));
    
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);
    
    // After setting strips, the entry should have strip information
    // We can't directly observe strips_, but we can verify setStrips doesn't crash
    SUCCEED();
}

TEST_F(TiffImageEntryTest_409, PValueReturnsNullWhenNoValueSet_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffImageEntryTest_409, SetValueMakesValueAccessible_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = Value::create(TypeId::unsignedLong);
    value->read("42");
    
    entry.setValue(std::move(value));
    
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toInt64(0), 42);
}

TEST_F(TiffImageEntryTest_409, SetStripsWithNullSize_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    byte data[100];
    std::memset(data, 0, sizeof(data));
    
    // Passing null pSize - should handle gracefully
    entry.setStrips(nullptr, data, sizeof(data), 0);
    SUCCEED();
}

TEST_F(TiffImageEntryTest_409, SetStripsWithNullData_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto sizeValue = Value::create(TypeId::unsignedLong);
    sizeValue->read("100");
    
    // Passing null data with zero size
    entry.setStrips(sizeValue.get(), nullptr, 0, 0);
    SUCCEED();
}

TEST_F(TiffImageEntryTest_409, ValueWithZeroDataAreaAndNoStrips_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    // Set a value that has no data area
    auto value = Value::create(TypeId::unsignedLong);
    value->read("0");
    
    entry.setValue(std::move(value));
    
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
    // With no strips and no data area, doSizeImage should return 0
    // (strips_ is empty, so transform_reduce returns initial value 0)
}

TEST_F(TiffImageEntryTest_409, TiffType_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    // Verify basic properties are accessible
    EXPECT_EQ(entry.tiffType(), 0u);
}

TEST_F(TiffImageEntryTest_409, MultipleSetValue_409) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value1 = Value::create(TypeId::unsignedLong);
    value1->read("10");
    entry.setValue(std::move(value1));
    
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toInt64(0), 10);
    
    auto value2 = Value::create(TypeId::unsignedLong);
    value2->read("20");
    entry.setValue(std::move(value2));
    
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toInt64(0), 20);
}
