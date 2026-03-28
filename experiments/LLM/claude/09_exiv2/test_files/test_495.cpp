#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashGroupBDataFl6Test_495 : public ::testing::Test {
protected:
  std::ostringstream os;
};

// Test: null metadata pointer should produce fallback output "(value)"
TEST_F(PrintFlashGroupBDataFl6Test_495, NullMetadata_495) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, nullptr);

  std::string result = os.str();
  EXPECT_EQ(result, "(42)");
}

// Test: value with count != 1 should produce fallback output
TEST_F(PrintFlashGroupBDataFl6Test_495, ValueCountNotOne_495) {
  auto value = Value::create(unsignedByte);
  value->read("10 20");  // count = 2

  ExifData metadata;
  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_EQ(result, "(10 20)");
}

// Test: value with wrong type (not unsignedByte) should produce fallback output
TEST_F(PrintFlashGroupBDataFl6Test_495, ValueWrongType_495) {
  auto value = Value::create(unsignedShort);
  value->read("42");

  ExifData metadata;
  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_EQ(result, "(42)");
}

// Test: metadata does not contain the required key - fallback
TEST_F(PrintFlashGroupBDataFl6Test_495, MetadataMissingKey_495) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  // Don't add the required key
  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_EQ(result, "(42)");
}

// Test: metadata has the key but with wrong type
TEST_F(PrintFlashGroupBDataFl6Test_495, MetadataKeyWrongType_495) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  auto controlValue = Value::create(unsignedShort);
  controlValue->read("16");
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_EQ(result, "(42)");
}

// Test: metadata key has count != 1
TEST_F(PrintFlashGroupBDataFl6Test_495, MetadataKeyCountNotOne_495) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("16 32");  // count = 2
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_EQ(result, "(42)");
}

// Test: mode is 0 (top nibble of control data is 0) -> should print "n/a"
TEST_F(PrintFlashGroupBDataFl6Test_495, ModeZero_PrintsNA_495) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  // Value 0x0F: top nibble = 0, so mode = 0
  controlValue->read("15");  // 0x0F -> mode = 0x0F >> 4 = 0
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  // mode = 0 means "n/a"
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: mode is 0 when control data is 0
TEST_F(PrintFlashGroupBDataFl6Test_495, ControlDataZero_PrintsNA_495) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("0");  // mode = 0 >> 4 = 0
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: mode is non-zero (top nibble of control data is non-zero) -> calls printFlashCompensationValue
TEST_F(PrintFlashGroupBDataFl6Test_495, ModeNonZero_PrintsCompensation_495) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  // Value 16 = 0x10: top nibble = 1, so mode = 1 (non-zero)
  controlValue->read("16");
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  // Should not be "(0)" or "n/a" - should produce some compensation value
  EXPECT_NE(result, "(0)");
  EXPECT_EQ(result.find("n/a"), std::string::npos);
  // The result should be non-empty (some flash compensation output)
  EXPECT_FALSE(result.empty());
}

// Test: mode non-zero with a different control value (mode=3 -> 0x30 = 48)
TEST_F(PrintFlashGroupBDataFl6Test_495, ModeThree_PrintsCompensation_495) {
  auto value = Value::create(unsignedByte);
  value->read("6");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  // Value 48 = 0x30: top nibble = 3, so mode = 3
  controlValue->read("48");
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_NE(result, "(6)");
  EXPECT_EQ(result.find("n/a"), std::string::npos);
  EXPECT_FALSE(result.empty());
}

// Test: returns reference to the same ostream
TEST_F(PrintFlashGroupBDataFl6Test_495, ReturnsOstreamReference_495) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  std::ostream& returned = Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test: valid inputs with mode = 0 also returns ostream reference
TEST_F(PrintFlashGroupBDataFl6Test_495, NAReturnsOstreamReference_495) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("0");
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  std::ostream& returned = Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);
  EXPECT_EQ(&returned, &os);
}

// Test: boundary - control data value 255 (0xFF -> mode = 15)
TEST_F(PrintFlashGroupBDataFl6Test_495, ControlDataMax255_495) {
  auto value = Value::create(unsignedByte);
  value->read("128");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  // 255 = 0xFF, mode = 0xFF >> 4 = 15
  controlValue->read("255");
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  // mode is non-zero, so should not print n/a or fallback
  EXPECT_EQ(result.find("n/a"), std::string::npos);
  EXPECT_FALSE(result.empty());
}

// Test: boundary - value is 255 (max unsigned byte)
TEST_F(PrintFlashGroupBDataFl6Test_495, ValueMax255WithNonZeroMode_495) {
  auto value = Value::create(unsignedByte);
  value->read("255");

  ExifData metadata;
  auto controlValue = Value::create(unsignedByte);
  controlValue->read("32");  // mode = 2
  metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());

  Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.find("n/a"), std::string::npos);
}
