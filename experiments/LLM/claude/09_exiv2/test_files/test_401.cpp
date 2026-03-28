#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"
#include "exiv2/tags.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffDataEntry inherits from TiffDataEntryBase which needs tag, group, and tiffType
// We need to find a way to construct it and access doSizeData through the public interface

class TiffDataEntryTest_401 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that doSizeData returns 0 when no value is set (pValue() is null)
TEST_F(TiffDataEntryTest_401, SizeDataReturnsZeroWhenNoValueSet_401) {
    // Construct a TiffDataEntry with some tag, group, tiffType
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, ttUnsignedLong, 0x0117, IfdId::ifd0Id);
    
    // pValue() should be null initially, so sizeData() should return 0
    // doSizeData is called through the TiffComponent interface
    EXPECT_EQ(entry.sizeData(), 0u);
}

// Test that doSizeData returns pValue()->sizeDataArea() when value is set but has no data area
TEST_F(TiffDataEntryTest_401, SizeDataReturnsZeroWhenValueHasNoDataArea_401) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, ttUnsignedLong, 0x0117, IfdId::ifd0Id);
    
    // Create a value and set it
    auto value = Value::create(unsignedLong);
    // Read some data into the value
    value->read("100");
    
    entry.setValue(std::move(value));
    
    // Value exists but has no data area set, so sizeDataArea() should return 0
    EXPECT_EQ(entry.sizeData(), 0u);
}

// Test that doSizeData returns correct size when value has a data area
TEST_F(TiffDataEntryTest_401, SizeDataReturnsCorrectSizeWhenValueHasDataArea_401) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, ttUnsignedLong, 0x0117, IfdId::ifd0Id);
    
    auto value = Value::create(unsignedLong);
    value->read("100");
    
    // Set a data area on the value
    byte dataArea[128];
    std::memset(dataArea, 0, sizeof(dataArea));
    value->setDataArea(dataArea, sizeof(dataArea));
    
    entry.setValue(std::move(value));
    
    // Now sizeDataArea should return 128
    EXPECT_EQ(entry.sizeData(), 128u);
}

// Test with a different sized data area
TEST_F(TiffDataEntryTest_401, SizeDataReturnsCorrectSizeForSmallDataArea_401) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, ttUnsignedLong, 0x0117, IfdId::ifd0Id);
    
    auto value = Value::create(unsignedLong);
    value->read("50");
    
    byte dataArea[1];
    dataArea[0] = 0xFF;
    value->setDataArea(dataArea, 1);
    
    entry.setValue(std::move(value));
    
    EXPECT_EQ(entry.sizeData(), 1u);
}

// Test with empty data area (size 0)
TEST_F(TiffDataEntryTest_401, SizeDataReturnsZeroForEmptyDataArea_401) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, ttUnsignedLong, 0x0117, IfdId::ifd0Id);
    
    auto value = Value::create(unsignedLong);
    value->read("0");
    
    // Setting data area with size 0
    byte dummy = 0;
    value->setDataArea(&dummy, 0);
    
    entry.setValue(std::move(value));
    
    EXPECT_EQ(entry.sizeData(), 0u);
}

// Test replacing value - ensure new value's data area size is returned
TEST_F(TiffDataEntryTest_401, SizeDataUpdatesWhenValueIsReplaced_401) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, ttUnsignedLong, 0x0117, IfdId::ifd0Id);
    
    // First value with data area
    auto value1 = Value::create(unsignedLong);
    value1->read("100");
    byte dataArea1[64];
    std::memset(dataArea1, 0, sizeof(dataArea1));
    value1->setDataArea(dataArea1, sizeof(dataArea1));
    entry.setValue(std::move(value1));
    
    EXPECT_EQ(entry.sizeData(), 64u);
    
    // Replace with a new value with different data area size
    auto value2 = Value::create(unsignedLong);
    value2->read("200");
    byte dataArea2[256];
    std::memset(dataArea2, 0, sizeof(dataArea2));
    value2->setDataArea(dataArea2, sizeof(dataArea2));
    entry.setValue(std::move(value2));
    
    EXPECT_EQ(entry.sizeData(), 256u);
}

// Test with large data area
TEST_F(TiffDataEntryTest_401, SizeDataReturnsCorrectSizeForLargeDataArea_401) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, ttUnsignedLong, 0x0117, IfdId::ifd0Id);
    
    auto value = Value::create(unsignedLong);
    value->read("1000");
    
    const size_t largeSize = 65536;
    std::vector<byte> dataArea(largeSize, 0);
    value->setDataArea(dataArea.data(), largeSize);
    
    entry.setValue(std::move(value));
    
    EXPECT_EQ(entry.sizeData(), largeSize);
}
