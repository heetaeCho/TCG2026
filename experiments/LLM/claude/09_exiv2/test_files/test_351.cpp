#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffDataEntry
class TiffDataEntryTest_351 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
  void TearDown() override {
  }
};

// Test that TiffDataEntry can be constructed with valid tag and group
TEST_F(TiffDataEntryTest_351, Construction_351) {
  // TiffDataEntryBase constructor takes tag, group, and a size tag/group
  // TiffDataEntry inherits from TiffDataEntryBase
  EXPECT_NO_THROW({
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  });
}

// Test setStrips with nullptr pSize
TEST_F(TiffDataEntryTest_351, SetStripsNullSize_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  // Setting strips with null pSize - should handle gracefully
  EXPECT_NO_THROW({
    entry.setStrips(nullptr, data, sizeof(data), 0);
  });
}

// Test setStrips with valid data
TEST_F(TiffDataEntryTest_351, SetStripsWithData_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  
  // Create a Value to represent strip sizes
  auto sizeValue = Value::create(unsignedLong);
  sizeValue->read("4");
  
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_NO_THROW({
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);
  });
}

// Test setStrips with zero size data
TEST_F(TiffDataEntryTest_351, SetStripsZeroSizeData_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  
  auto sizeValue = Value::create(unsignedLong);
  sizeValue->read("0");
  
  EXPECT_NO_THROW({
    entry.setStrips(sizeValue.get(), nullptr, 0, 0);
  });
}

// Test setStrips with non-zero base offset
TEST_F(TiffDataEntryTest_351, SetStripsWithBaseOffset_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  
  auto sizeValue = Value::create(unsignedLong);
  sizeValue->read("4");
  
  const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
  EXPECT_NO_THROW({
    entry.setStrips(sizeValue.get(), data, sizeof(data), 4);
  });
}

// Test setStrips with multiple strip sizes
TEST_F(TiffDataEntryTest_351, SetStripsMultipleSizes_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  
  auto sizeValue = Value::create(unsignedLong);
  sizeValue->read("2 2");
  
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_NO_THROW({
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);
  });
}

// Test that a second TiffDataEntry can be constructed with different tag
TEST_F(TiffDataEntryTest_351, ConstructionDifferentTag_351) {
  EXPECT_NO_THROW({
    TiffDataEntry entry(0x0201, IfdId::ifd0Id);
  });
}

// Test setStrips with null data pointer but non-zero size
TEST_F(TiffDataEntryTest_351, SetStripsNullDataNonZeroSize_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  
  auto sizeValue = Value::create(unsignedLong);
  sizeValue->read("4");
  
  // Passing null data with non-zero size - boundary condition
  EXPECT_NO_THROW({
    entry.setStrips(sizeValue.get(), nullptr, 4, 0);
  });
}

// Test setStrips called multiple times (overwrite behavior)
TEST_F(TiffDataEntryTest_351, SetStripsCalledTwice_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  
  auto sizeValue1 = Value::create(unsignedLong);
  sizeValue1->read("2");
  const byte data1[] = {0x01, 0x02};
  
  entry.setStrips(sizeValue1.get(), data1, sizeof(data1), 0);
  
  auto sizeValue2 = Value::create(unsignedLong);
  sizeValue2->read("4");
  const byte data2[] = {0x03, 0x04, 0x05, 0x06};
  
  EXPECT_NO_THROW({
    entry.setStrips(sizeValue2.get(), data2, sizeof(data2), 0);
  });
}

// Test large base offset
TEST_F(TiffDataEntryTest_351, SetStripsLargeBaseOffset_351) {
  TiffDataEntry entry(0x0111, IfdId::ifd0Id);
  
  auto sizeValue = Value::create(unsignedLong);
  sizeValue->read("1");
  
  const byte data[] = {0xFF};
  EXPECT_NO_THROW({
    entry.setStrips(sizeValue.get(), data, sizeof(data), 1000000);
  });
}
