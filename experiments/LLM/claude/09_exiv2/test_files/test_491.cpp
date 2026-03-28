#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteFlashGroupAControlDataTest_491 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: Single unsignedByte value with lower nibble 0 => "Off"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue0_ReturnsOff_491) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Off");
}

// Test: Single unsignedByte value with lower nibble 1 => "TTL"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue1_ReturnsTTL_491) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "TTL");
}

// Test: Single unsignedByte value with lower nibble 2 => "iTTL"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue2_ReturnsiTTL_491) {
  auto value = Value::create(unsignedByte);
  value->read("2");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "iTTL");
}

// Test: Single unsignedByte value with lower nibble 3 => "Auto Aperture"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue3_ReturnsAutoAperture_491) {
  auto value = Value::create(unsignedByte);
  value->read("3");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Auto Aperture");
}

// Test: Single unsignedByte value with lower nibble 4 => "Automatic"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue4_ReturnsAutomatic_491) {
  auto value = Value::create(unsignedByte);
  value->read("4");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Automatic");
}

// Test: Single unsignedByte value with lower nibble 5 => "GN (distance priority)"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue5_ReturnsGN_491) {
  auto value = Value::create(unsignedByte);
  value->read("5");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "GN (distance priority)");
}

// Test: Single unsignedByte value with lower nibble 6 => "Manual"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue6_ReturnsManual_491) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Manual");
}

// Test: Single unsignedByte value with lower nibble 7 => "Repeating Flash"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, SingleUnsignedByteValue7_ReturnsRepeatingFlash_491) {
  auto value = Value::create(unsignedByte);
  value->read("7");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Repeating Flash");
}

// Test: Value with upper nibble set, only lower nibble should be used (0x12 => lower nibble 2 => "iTTL")
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, UpperNibbleMaskedOut_491) {
  auto value = Value::create(unsignedByte);
  // 0x12 = 18, lower nibble = 2 => "iTTL"
  value->read("18");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "iTTL");
}

// Test: Value with upper nibble 0xF0, lower nibble 6 => 0xF6 = 246, lower nibble = 6 => "Manual"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, HighUpperNibbleMaskedOut_491) {
  auto value = Value::create(unsignedByte);
  // 0xF6 = 246, lower nibble = 6 => "Manual"
  value->read("246");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Manual");
}

// Test: Wrong type (unsignedShort instead of unsignedByte) => should output raw value in parentheses
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, WrongType_ReturnsRawValueInParens_491) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Multiple values (count != 1) => should output raw value in parentheses
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, MultipleValues_ReturnsRawValueInParens_491) {
  auto value = Value::create(unsignedByte);
  value->read("1 2");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Lower nibble value that is out of range (e.g., 0x0F = 15) for nikonFlashControlMode table
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, OutOfRangeLowerNibble_491) {
  auto value = Value::create(unsignedByte);
  // 0x0F = 15, lower nibble = 15, which is not in the table (0-7)
  value->read("15");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  std::string result = os.str();
  // Should output something (likely the raw number or "(15)")
  EXPECT_FALSE(result.empty());
}

// Test: Lower nibble 8 => not in table, should produce some output
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, LowerNibble8NotInTable_491) {
  auto value = Value::create(unsignedByte);
  value->read("8");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value 0 with valid type => "Off"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, ZeroValue_ReturnsOff_491) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Off");
}

// Test: Value 0x30 = 48, lower nibble = 0 => "Off"
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, Value48LowerNibble0_ReturnsOff_491) {
  auto value = Value::create(unsignedByte);
  value->read("48");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Off");
}

// Test: Returns the same ostream reference
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, ReturnsSameOstreamReference_491) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  std::ostream& returned = Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test: Returns the same ostream reference on error path
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, ReturnsSameOstreamReferenceOnError_491) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  std::ostream& returned = Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test: With non-null ExifData pointer
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, WithExifData_491) {
  ExifData exifData;
  auto value = Value::create(unsignedByte);
  value->read("2");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, &exifData);
  EXPECT_EQ(os.str(), "iTTL");
}

// Test: Value 0xFF = 255, lower nibble = 0x0F = 15
TEST_F(Nikon3MakerNoteFlashGroupAControlDataTest_491, Value255LowerNibble15_491) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
