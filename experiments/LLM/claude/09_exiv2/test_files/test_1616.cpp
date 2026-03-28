#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for SonyMakerNote
// Based on the provided code structure
namespace Exiv2 {
namespace Internal {
class SonyMakerNote;
}
}

// We need access to the function under test
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1616 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When value count != 1, output should be "(value)"
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_ValueCountNotOne_1616) {
  // Create a value with count != 1 (e.g., 2 values)
  auto value = Value::create(unsignedShort);
  value->read("25 30");
  
  ExifData metadata;
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  // Should contain parentheses since count != 1
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When metadata is nullptr, output should be "(value)"
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_NullMetadata_1616) {
  auto value = Value::create(unsignedShort);
  value->read("25");
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When 0x0004 key exists, count==1, value != 0 and < 100, should print temperature with °C
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_ValidTemperature_1616) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  ExifData metadata;
  // Add Exif.SonyMisc1.0x0004 with a valid value (non-zero, < 100)
  auto miscValue = Value::create(unsignedShort);
  miscValue->read("50");
  metadata.add(ExifKey("Exif.SonyMisc1.0x0004"), miscValue.get());
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  // Should contain "42" and "°C"
  EXPECT_TRUE(result.find("42") != std::string::npos);
  EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test: When 0x0004 key exists but value == 0, should print n/a
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MiscValueZero_1616) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  ExifData metadata;
  auto miscValue = Value::create(unsignedShort);
  miscValue->read("0");
  metadata.add(ExifKey("Exif.SonyMisc1.0x0004"), miscValue.get());
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("a") != std::string::npos);
}

// Test: When 0x0004 key exists but value >= 100, should print n/a
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MiscValueGE100_1616) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  ExifData metadata;
  auto miscValue = Value::create(unsignedShort);
  miscValue->read("100");
  metadata.add(ExifKey("Exif.SonyMisc1.0x0004"), miscValue.get());
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  // Should NOT contain "°C" since value is >= 100
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("a") != std::string::npos);
}

// Test: When 0x0004 key does not exist in metadata, should print n/a
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MiscKeyNotFound_1616) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  ExifData metadata;
  // Don't add the 0x0004 key
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("a") != std::string::npos);
}

// Test: Boundary - 0x0004 value == 99 (just under 100), should print temperature
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MiscValue99_1616) {
  auto value = Value::create(unsignedShort);
  value->read("35");
  
  ExifData metadata;
  auto miscValue = Value::create(unsignedShort);
  miscValue->read("99");
  metadata.add(ExifKey("Exif.SonyMisc1.0x0004"), miscValue.get());
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("35") != std::string::npos);
  EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test: Boundary - 0x0004 value == 1 (minimum valid), should print temperature
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MiscValue1_1616) {
  auto value = Value::create(unsignedShort);
  value->read("20");
  
  ExifData metadata;
  auto miscValue = Value::create(unsignedShort);
  miscValue->read("1");
  metadata.add(ExifKey("Exif.SonyMisc1.0x0004"), miscValue.get());
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("20") != std::string::npos);
  EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test: Value count == 0, should output "(value)"
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_ValueCountZero_1616) {
  auto value = Value::create(unsignedShort);
  // Empty value - count should be 0
  
  ExifData metadata;
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Large 0x0004 value (e.g., 200), should print n/a
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MiscValueLarge_1616) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  ExifData metadata;
  auto miscValue = Value::create(unsignedShort);
  miscValue->read("200");
  metadata.add(ExifKey("Exif.SonyMisc1.0x0004"), miscValue.get());
  
  SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  std::string result = os.str();
  // Should be n/a since 200 >= 100
  EXPECT_TRUE(result.find("C") == std::string::npos || result.find("n/a") != std::string::npos);
}

// Test: Return value is reference to same ostream
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_ReturnsOstream_1616) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  ExifData metadata;
  auto miscValue = Value::create(unsignedShort);
  miscValue->read("50");
  metadata.add(ExifKey("Exif.SonyMisc1.0x0004"), miscValue.get());
  
  std::ostream& result = SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, &metadata);
  
  EXPECT_EQ(&result, &os);
}

// Test: Return value is reference to same ostream when null metadata
TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_ReturnsOstreamOnNull_1616) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  std::ostream& result = SonyMakerNote::printSonyMisc1CameraTemperature(os, *value, nullptr);
  
  EXPECT_EQ(&result, &os);
}
