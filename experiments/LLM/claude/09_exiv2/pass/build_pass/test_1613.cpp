#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for SonyMakerNote
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1613 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tests for printSony2FpAmbientTemperature
// =============================================================================

// Test: When value count != 1, should output "(<value>)"
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_ValueCountNotOne_1613) {
  ExifData exifData;
  // Create a value with 2 elements
  auto value = Value::create(signedShort);
  value->read("25 30");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  // Should contain parentheses since count != 1
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When metadata is nullptr, should output "(<value>)"
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_NullMetadata_1613) {
  auto value = Value::create(signedShort);
  value->read("25");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When Exif.Sony2Fp.0x0002 exists and equals 255, should output temperature with °C
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_ValidWithKey255_1613) {
  ExifData exifData;

  // Add Exif.Sony2Fp.0x0002 with value 255
  auto keyValue = Value::create(unsignedByte);
  keyValue->read("255");
  exifData.add(ExifKey("Exif.Sony2Fp.0x0002"), keyValue.get());

  auto value = Value::create(signedShort);
  value->read("25");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  // Should contain the value and °C
  EXPECT_NE(result.find("25"), std::string::npos);
  EXPECT_NE(result.find("°C"), std::string::npos);
}

// Test: When Exif.Sony2Fp.0x0002 exists but does NOT equal 255, should output "n/a"
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_KeyNotEqualTo255_1613) {
  ExifData exifData;

  // Add Exif.Sony2Fp.0x0002 with value != 255
  auto keyValue = Value::create(unsignedByte);
  keyValue->read("100");
  exifData.add(ExifKey("Exif.Sony2Fp.0x0002"), keyValue.get());

  auto value = Value::create(signedShort);
  value->read("25");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: When Exif.Sony2Fp.0x0002 does not exist in metadata, should output "n/a"
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_KeyNotFound_1613) {
  ExifData exifData;
  // Don't add the key

  auto value = Value::create(signedShort);
  value->read("25");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Negative temperature value with valid key=255
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_NegativeTemperature_1613) {
  ExifData exifData;

  auto keyValue = Value::create(unsignedByte);
  keyValue->read("255");
  exifData.add(ExifKey("Exif.Sony2Fp.0x0002"), keyValue.get());

  auto value = Value::create(signedShort);
  value->read("-10");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("-10"), std::string::npos);
  EXPECT_NE(result.find("°C"), std::string::npos);
}

// Test: Zero temperature value with valid key=255
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_ZeroTemperature_1613) {
  ExifData exifData;

  auto keyValue = Value::create(unsignedByte);
  keyValue->read("255");
  exifData.add(ExifKey("Exif.Sony2Fp.0x0002"), keyValue.get());

  auto value = Value::create(signedShort);
  value->read("0");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("0"), std::string::npos);
  EXPECT_NE(result.find("°C"), std::string::npos);
}

// Test: Value count is zero (empty value)
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_EmptyValue_1613) {
  ExifData exifData;

  auto value = Value::create(signedShort);
  // Don't read any data, count should be 0

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  // count != 1, so should get parenthesized output
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Both conditions fail - null metadata AND count != 1
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_NullMetadataAndMultipleValues_1613) {
  auto value = Value::create(signedShort);
  value->read("10 20");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Key value is 0 (boundary: not 255)
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_KeyValueZero_1613) {
  ExifData exifData;

  auto keyValue = Value::create(unsignedByte);
  keyValue->read("0");
  exifData.add(ExifKey("Exif.Sony2Fp.0x0002"), keyValue.get());

  auto value = Value::create(signedShort);
  value->read("25");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Key value is 254 (boundary: just below 255)
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_KeyValue254_1613) {
  ExifData exifData;

  auto keyValue = Value::create(unsignedByte);
  keyValue->read("254");
  exifData.add(ExifKey("Exif.Sony2Fp.0x0002"), keyValue.get());

  auto value = Value::create(signedShort);
  value->read("30");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_ReturnsOstream_1613) {
  ExifData exifData;
  auto value = Value::create(signedShort);
  value->read("25");

  std::ostream& ret = SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference with null metadata
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_ReturnsOstreamNullMeta_1613) {
  auto value = Value::create(signedShort);
  value->read("25");

  std::ostream& ret = SonyMakerNote::printSony2FpAmbientTemperature(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: Large temperature value
TEST_F(SonyMakerNoteTest_1613, AmbientTemperature_LargeTemperature_1613) {
  ExifData exifData;

  auto keyValue = Value::create(unsignedByte);
  keyValue->read("255");
  exifData.add(ExifKey("Exif.Sony2Fp.0x0002"), keyValue.get());

  auto value = Value::create(signedShort);
  value->read("32767");

  SonyMakerNote::printSony2FpAmbientTemperature(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("32767"), std::string::npos);
  EXPECT_NE(result.find("°C"), std::string::npos);
}
