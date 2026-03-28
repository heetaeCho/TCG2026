#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashGroupBDataFl7Test_496 : public ::testing::Test {
protected:
  std::ostringstream os;
};

// Test: When metadata is null, output should be "(value)"
TEST_F(PrintFlashGroupBDataFl7Test_496, NullMetadataReturnsParenthesizedValue_496) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, nullptr);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value count != 1, output should be parenthesized
TEST_F(PrintFlashGroupBDataFl7Test_496, ValueCountNotOneReturnsParenthesized_496) {
  // Create a value with multiple elements
  auto value = Value::create(unsignedByte);
  value->read("42 43");

  ExifData metadata;

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value type is not unsignedByte, output should be parenthesized
TEST_F(PrintFlashGroupBDataFl7Test_496, ValueTypeNotUnsignedByteReturnsParenthesized_496) {
  auto value = Value::create(unsignedShort);
  value->read("42");

  ExifData metadata;

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When FlashGroupBCControlData key is not found in metadata, output should be parenthesized
TEST_F(PrintFlashGroupBDataFl7Test_496, ControlDataNotFoundReturnsParenthesized_496) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  // Don't add the FlashGroupBCControlData key

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When FlashGroupBCControlData exists but has wrong type
TEST_F(PrintFlashGroupBDataFl7Test_496, ControlDataWrongTypeReturnsParenthesized_496) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  // Add with wrong type (unsignedShort instead of unsignedByte)
  auto controlValue = Value::create(unsignedShort);
  controlValue->read("16");
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When mode (upper nibble) is 0, output should be "n/a"
TEST_F(PrintFlashGroupBDataFl7Test_496, ModeZeroReturnsNA_496) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  // Control data with upper nibble = 0 (e.g., value 0x00 to 0x0F)
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("0");  // 0 >> 4 == 0
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos);
}

// Test: When mode (upper nibble) is 0 with low nibble set, still "n/a"
TEST_F(PrintFlashGroupBDataFl7Test_496, ModeLowNibbleOnlyReturnsNA_496) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("15");  // 0x0F >> 4 == 0
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos);
}

// Test: When mode (upper nibble) is non-zero, should call printFlashCompensationValue
TEST_F(PrintFlashGroupBDataFl7Test_496, ModeNonZeroReturnsFlashCompensation_496) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  ExifData metadata;
  // Control data with upper nibble = 1 (e.g., value 0x10 = 16)
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("16");  // 16 >> 4 == 1, non-zero mode
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  // Should not be parenthesized or n/a since mode is non-zero
  EXPECT_TRUE(result.find("(") == std::string::npos);
  // The result should not be empty
  EXPECT_FALSE(result.empty());
}

// Test: When mode is 2 (upper nibble = 2), should produce flash compensation output
TEST_F(PrintFlashGroupBDataFl7Test_496, ModeUpperNibble2ReturnsFlashCompensation_496) {
  auto value = Value::create(unsignedByte);
  value->read("6");

  ExifData metadata;
  // Control data = 0x20 = 32, so mode = 32 >> 4 = 2
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("32");
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // Should not be n/a
  EXPECT_TRUE(result.find("n/a") == std::string::npos && result.find("N/A") == std::string::npos);
}

// Test: When mode is 3 (upper nibble = 3), should produce flash compensation output (manual scale)
TEST_F(PrintFlashGroupBDataFl7Test_496, ModeUpperNibble3ReturnsFlashCompensation_496) {
  auto value = Value::create(unsignedByte);
  value->read("12");

  ExifData metadata;
  // Control data = 0x30 = 48, so mode = 48 >> 4 = 3
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("48");
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Return value is the same ostream reference
TEST_F(PrintFlashGroupBDataFl7Test_496, ReturnsSameOstream_496) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  std::ostream& ret = Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, nullptr);

  EXPECT_EQ(&ret, &os);
}

// Test: ControlData with count != 1 returns parenthesized value
TEST_F(PrintFlashGroupBDataFl7Test_496, ControlDataCountNotOneReturnsParenthesized_496) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("16 32");  // count = 2
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value with 0 and mode non-zero
TEST_F(PrintFlashGroupBDataFl7Test_496, ValueZeroWithNonZeroMode_496) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("16");  // mode = 1
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  // Should produce some flash compensation value (not parenthesized, not n/a)
  EXPECT_FALSE(result.empty());
  EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test: Value 255 (max unsigned byte) with non-zero mode
TEST_F(PrintFlashGroupBDataFl7Test_496, MaxByteValueWithNonZeroMode_496) {
  auto value = Value::create(unsignedByte);
  value->read("255");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("240");  // mode = 240 >> 4 = 15
  metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
