#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

#include "exiv2/metadatum.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;

// Since Metadatum is abstract, we need a concrete subclass to test.
// Exifdatum is a concrete subclass available in the codebase.

class MetadatumTest_110 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that print() returns a string representation (uses write() internally)
TEST_F(MetadatumTest_110, PrintReturnsStringFromWrite_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "TestCamera";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  std::string result = it->print(&exifData);
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result, "TestCamera");
}

// Test print with nullptr ExifData
TEST_F(MetadatumTest_110, PrintWithNullMetadata_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "TestValue";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  // Should not crash with nullptr
  std::string result = it->print(nullptr);
  EXPECT_FALSE(result.empty());
}

// Test key() returns the correct key string
TEST_F(MetadatumTest_110, KeyReturnsCorrectString_110) {
  ExifData exifData;
  exifData["Exif.Image.Model"] = "TestModel";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Model"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_EQ(it->key(), "Exif.Image.Model");
}

// Test familyName returns "Exif" for Exif metadata
TEST_F(MetadatumTest_110, FamilyNameReturnsExif_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  std::string familyName = it->familyName();
  EXPECT_EQ(familyName, "Exif");
}

// Test groupName returns correct group
TEST_F(MetadatumTest_110, GroupNameReturnsCorrectGroup_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_EQ(it->groupName(), "Image");
}

// Test tagName returns correct tag name
TEST_F(MetadatumTest_110, TagNameReturnsCorrectName_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_EQ(it->tagName(), "Make");
}

// Test toString returns the value as string
TEST_F(MetadatumTest_110, ToStringReturnsValue_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "HelloWorld";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_EQ(it->toString(), "HelloWorld");
}

// Test count() returns appropriate count
TEST_F(MetadatumTest_110, CountReturnsCorrectValue_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_GT(it->count(), 0u);
}

// Test size() returns non-zero for set value
TEST_F(MetadatumTest_110, SizeReturnsNonZero_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "TestData";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_GT(it->size(), 0u);
}

// Test tag() returns the correct tag number
TEST_F(MetadatumTest_110, TagReturnsCorrectTagNumber_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  // Make tag is 0x010f
  EXPECT_EQ(it->tag(), 0x010f);
}

// Test typeId returns asciiString for string value
TEST_F(MetadatumTest_110, TypeIdForStringValue_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_EQ(it->typeId(), asciiString);
}

// Test typeName returns a non-null string
TEST_F(MetadatumTest_110, TypeNameReturnsNonNull_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_NE(it->typeName(), nullptr);
}

// Test getValue returns a valid unique_ptr
TEST_F(MetadatumTest_110, GetValueReturnsValidPointer_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "TestValue";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  auto val = it->getValue();
  EXPECT_NE(val, nullptr);
  EXPECT_EQ(val->toString(), "TestValue");
}

// Test value() returns a reference to the value
TEST_F(MetadatumTest_110, ValueReturnsReference_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "RefTest";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  const Value& val = it->value();
  EXPECT_EQ(val.toString(), "RefTest");
}

// Test toInt64 for numeric data
TEST_F(MetadatumTest_110, ToInt64ForNumericData_110) {
  ExifData exifData;
  exifData["Exif.Image.ImageWidth"] = uint32_t(1920);
  
  auto it = exifData.findKey(ExifKey("Exif.Image.ImageWidth"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_EQ(it->toInt64(0), 1920);
}

// Test toUint32 for numeric data
TEST_F(MetadatumTest_110, ToUint32ForNumericData_110) {
  ExifData exifData;
  exifData["Exif.Image.ImageWidth"] = uint32_t(1024);
  
  auto it = exifData.findKey(ExifKey("Exif.Image.ImageWidth"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_EQ(it->toUint32(0), 1024u);
}

// Test toFloat for numeric data
TEST_F(MetadatumTest_110, ToFloatForNumericData_110) {
  ExifData exifData;
  exifData["Exif.Image.ImageWidth"] = uint32_t(800);
  
  auto it = exifData.findKey(ExifKey("Exif.Image.ImageWidth"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_FLOAT_EQ(it->toFloat(0), 800.0f);
}

// Test write() outputs to stream correctly
TEST_F(MetadatumTest_110, WriteOutputsToStream_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "StreamTest";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  std::ostringstream os;
  it->write(os, &exifData);
  EXPECT_FALSE(os.str().empty());
  EXPECT_EQ(os.str(), "StreamTest");
}

// Test print() consistency with write()
TEST_F(MetadatumTest_110, PrintConsistentWithWrite_110) {
  ExifData exifData;
  exifData["Exif.Image.Model"] = "ConsistencyTest";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Model"));
  ASSERT_NE(it, exifData.end());
  
  std::ostringstream os;
  it->write(os, &exifData);
  std::string writeResult = os.str();
  
  std::string printResult = it->print(&exifData);
  
  EXPECT_EQ(printResult, writeResult);
}

// Test setValue with string
TEST_F(MetadatumTest_110, SetValueWithString_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Initial";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  it->setValue("Updated");
  EXPECT_EQ(it->toString(), "Updated");
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(MetadatumTest_110, TagLabelReturnsNonEmpty_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  std::string label = it->tagLabel();
  EXPECT_FALSE(label.empty());
}

// Test empty string value
TEST_F(MetadatumTest_110, EmptyStringValue_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  std::string result = it->toString();
  // Even empty string may have null terminator considerations
  // Just verify it doesn't crash
  std::string printResult = it->print(&exifData);
}

// Test typeSize returns appropriate size for the type
TEST_F(MetadatumTest_110, TypeSizeReturnsAppropriateValue_110) {
  ExifData exifData;
  exifData["Exif.Image.ImageWidth"] = uint32_t(100);
  
  auto it = exifData.findKey(ExifKey("Exif.Image.ImageWidth"));
  ASSERT_NE(it, exifData.end());
  
  EXPECT_GT(it->typeSize(), 0u);
}

// Test toString with index parameter
TEST_F(MetadatumTest_110, ToStringWithIndex_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "IndexTest";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  std::string result = it->toString(0);
  EXPECT_FALSE(result.empty());
}

// Test copy to buffer
TEST_F(MetadatumTest_110, CopyToBuffer_110) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "CopyTest";
  
  auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData.end());
  
  size_t dataSize = it->size();
  ASSERT_GT(dataSize, 0u);
  
  std::vector<byte> buf(dataSize + 10, 0);
  size_t copied = it->copy(buf.data(), littleEndian);
  EXPECT_GT(copied, 0u);
}
