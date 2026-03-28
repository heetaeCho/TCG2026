#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/value.hpp"
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_945 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When exifData is nullptr, print0x000c should output the value directly
TEST_F(CanonMakerNoteTest_945, Print0x000c_NullExifData_OutputsValueDirectly_945) {
  auto value = Value::create(unsignedLong);
  value->read("1234567");
  
  CanonMakerNote::print0x000c(os, *value, nullptr);
  
  // When exifData is null, it should just output the value as-is
  EXPECT_EQ(os.str(), value->toString());
}

// Test: When exifData exists but does not contain Exif.Canon.ModelID key
TEST_F(CanonMakerNoteTest_945, Print0x000c_NoModelIDKey_OutputsValueDirectly_945) {
  ExifData exifData;
  auto value = Value::create(unsignedLong);
  value->read("1234567");
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  EXPECT_EQ(os.str(), value->toString());
}

// Test: When exifData has ModelID but with wrong value (not 0x01140000)
TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDNotMatching_OutputsValueDirectly_945) {
  ExifData exifData;
  // Add a ModelID that doesn't match 0x01140000
  exifData["Exif.Canon.ModelID"] = static_cast<uint32_t>(0x00000001);
  
  auto value = Value::create(unsignedLong);
  value->read("1234567");
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  EXPECT_EQ(os.str(), value->toString());
}

// Test: When exifData has ModelID == 0x01140000, should format the value specially
TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMatches_FormatsSpecially_945) {
  ExifData exifData;
  // Set ModelID to 0x01140000
  exifData["Exif.Canon.ModelID"] = static_cast<uint32_t>(0x01140000);
  
  // Create a value: let's use 0x00010002 = 65538
  // upper 16 bits: 0x0001, lower 16 bits: 0x0002
  // Expected output: "000100002" (4 hex digits + 5 decimal digits)
  auto value = Value::create(unsignedLong);
  value->read("65538");  // 0x00010002
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  std::string result = os.str();
  // upper 16 bits = 1 -> "0001", lower 16 bits = 2 -> "00002"
  EXPECT_EQ(result, "000100002");
}

// Test: ModelID matches with a larger value
TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMatches_LargerValue_945) {
  ExifData exifData;
  exifData["Exif.Canon.ModelID"] = static_cast<uint32_t>(0x01140000);
  
  // Value: 0x01230456 = 19137622
  // upper 16 bits: 0x0123 -> "0123"
  // lower 16 bits: 0x0456 = 1110 -> "01110"
  uint32_t testVal = 0x01230456;
  auto value = Value::create(unsignedLong);
  value->read(std::to_string(testVal));
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  std::string result = os.str();
  EXPECT_EQ(result, "012301110");
}

// Test: ModelID matches with value = 0
TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMatches_ZeroValue_945) {
  ExifData exifData;
  exifData["Exif.Canon.ModelID"] = static_cast<uint32_t>(0x01140000);
  
  auto value = Value::create(unsignedLong);
  value->read("0");
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  std::string result = os.str();
  // upper 16 bits: 0 -> "0000", lower 16 bits: 0 -> "00000"
  EXPECT_EQ(result, "000000000");
}

// Test: ModelID matches with max 16-bit values in both halves
TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMatches_MaxValue_945) {
  ExifData exifData;
  exifData["Exif.Canon.ModelID"] = static_cast<uint32_t>(0x01140000);
  
  // 0xFFFFFFFF = 4294967295
  // upper 16 bits: 0xFFFF -> "ffff"
  // lower 16 bits: 0xFFFF = 65535 -> "65535"
  auto value = Value::create(unsignedLong);
  value->read("4294967295");
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  std::string result = os.str();
  EXPECT_EQ(result, "ffff65535");
}

// Test: Return value is a reference to the same ostream
TEST_F(CanonMakerNoteTest_945, Print0x000c_ReturnsSameOstream_945) {
  auto value = Value::create(unsignedLong);
  value->read("42");
  
  std::ostream& retVal = CanonMakerNote::print0x000c(os, *value, nullptr);
  
  EXPECT_EQ(&retVal, &os);
}

// Test: Return value is same ostream when ModelID matches
TEST_F(CanonMakerNoteTest_945, Print0x000c_ReturnsSameOstream_WhenModelIDMatches_945) {
  ExifData exifData;
  exifData["Exif.Canon.ModelID"] = static_cast<uint32_t>(0x01140000);
  
  auto value = Value::create(unsignedLong);
  value->read("100");
  
  std::ostream& retVal = CanonMakerNote::print0x000c(os, *value, &exifData);
  
  EXPECT_EQ(&retVal, &os);
}

// Test: ModelID key exists but with multiple count values (count != 1)
TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMultipleValues_OutputsValueDirectly_945) {
  ExifData exifData;
  // Add ModelID with multiple values by using a short array type
  auto modelIdValue = Value::create(unsignedLong);
  modelIdValue->read("18087936 123");  // two values, count should be 2
  exifData.add(ExifKey("Exif.Canon.ModelID"), modelIdValue.get());
  
  auto value = Value::create(unsignedLong);
  value->read("1234567");
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  // Since count != 1, should fall through to plain output
  EXPECT_EQ(os.str(), value->toString());
}

// Test: Specific formatted output with known hex/decimal pattern
TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMatches_SpecificPattern_945) {
  ExifData exifData;
  exifData["Exif.Canon.ModelID"] = static_cast<uint32_t>(0x01140000);
  
  // Value: 0x00AB1234 = 11211316
  // upper 16: 0x00AB -> "00ab"
  // lower 16: 0x1234 = 4660 -> "04660"
  uint32_t testVal = 0x00AB1234;
  auto value = Value::create(unsignedLong);
  value->read(std::to_string(testVal));
  
  CanonMakerNote::print0x000c(os, *value, &exifData);
  
  std::string result = os.str();
  EXPECT_EQ(result, "00ab04660");
}
