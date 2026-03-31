#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashMasterDataFl6Test_489 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When metadata pointer is null, output should be "(value)"
TEST_F(PrintFlashMasterDataFl6Test_489, NullMetadata_489) {
  auto value = Value::create(unsignedByte);
  value->read("0");

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, nullptr);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value count is not 1 (e.g., 0 values)
TEST_F(PrintFlashMasterDataFl6Test_489, ValueCountZero_489) {
  auto value = Value::create(unsignedByte);
  // Don't read any value, so count should be 0
  ExifData metadata;

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value type is not unsignedByte
TEST_F(PrintFlashMasterDataFl6Test_489, WrongValueType_489) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  ExifData metadata;

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value count is more than 1
TEST_F(PrintFlashMasterDataFl6Test_489, ValueCountMoreThanOne_489) {
  auto value = Value::create(unsignedByte);
  value->read("10 20");
  ExifData metadata;

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When ExternalFlashData1 key is not found in metadata
TEST_F(PrintFlashMasterDataFl6Test_489, ExternalFlashData1NotFound_489) {
  auto value = Value::create(unsignedByte);
  value->read("42");
  ExifData metadata;
  // Don't add Exif.NikonFl6.ExternalFlashData1

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When ExternalFlashData1 is present but has wrong type
TEST_F(PrintFlashMasterDataFl6Test_489, ExternalFlashData1WrongType_489) {
  auto value = Value::create(unsignedByte);
  value->read("42");
  ExifData metadata;

  // Add ExternalFlashData1 with wrong type (unsignedShort instead of unsignedByte)
  auto flashData = Value::create(unsignedShort);
  flashData->read("5");
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When ExternalFlashData1 is present with correct type but mode & 0x0F == 0 -> "n/a"
TEST_F(PrintFlashMasterDataFl6Test_489, ModeZeroReturnsNA_489) {
  auto value = Value::create(unsignedByte);
  value->read("42");
  ExifData metadata;

  // ExternalFlashData1 with value 0x00 (mode & 0x0F == 0)
  auto flashData = Value::create(unsignedByte);
  flashData->read("0");
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  // Should contain "n/a" or its translation
  EXPECT_FALSE(result.empty());
  // When mode is 0, it should return "n/a" (or localized equivalent)
  // We check it does NOT contain "(" which would indicate fallback
  EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: When ExternalFlashData1 mode & 0x0F == 0 with value 0x10 (upper nibble set)
TEST_F(PrintFlashMasterDataFl6Test_489, ModeZeroWithUpperNibble_489) {
  auto value = Value::create(unsignedByte);
  value->read("42");
  ExifData metadata;

  // 0x10 & 0x0F == 0
  auto flashData = Value::create(unsignedByte);
  flashData->read("16");  // 0x10
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: When ExternalFlashData1 has non-zero mode, flash compensation should be printed
TEST_F(PrintFlashMasterDataFl6Test_489, NonZeroModePrintsCompensation_489) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData metadata;

  // ExternalFlashData1 with value 1 (mode & 0x0F == 1)
  auto flashData = Value::create(unsignedByte);
  flashData->read("1");
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // Should not be the fallback "(value)" pattern since conditions are met
  // and should not be "n/a" since mode != 0
}

// Test: When ExternalFlashData1 has mode 0x0F (all lower bits set)
TEST_F(PrintFlashMasterDataFl6Test_489, ModeFPrintsCompensation_489) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  ExifData metadata;

  // ExternalFlashData1 with value 0xFF (mode & 0x0F == 0x0F)
  auto flashData = Value::create(unsignedByte);
  flashData->read("255");  // 0xFF
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Return value is the same ostream reference
TEST_F(PrintFlashMasterDataFl6Test_489, ReturnsOstreamReference_489) {
  auto value = Value::create(unsignedByte);
  value->read("42");

  std::ostream& returned = Nikon3MakerNote::printFlashMasterDataFl6(os, *value, nullptr);

  EXPECT_EQ(&returned, &os);
}

// Test: Return value is the same ostream when mode is zero
TEST_F(PrintFlashMasterDataFl6Test_489, ReturnsOstreamReferenceNACase_489) {
  auto value = Value::create(unsignedByte);
  value->read("42");
  ExifData metadata;

  auto flashData = Value::create(unsignedByte);
  flashData->read("0");
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  std::ostream& returned = Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  EXPECT_EQ(&returned, &os);
}

// Test: ExternalFlashData1 has count > 1
TEST_F(PrintFlashMasterDataFl6Test_489, ExternalFlashData1MultipleValues_489) {
  auto value = Value::create(unsignedByte);
  value->read("42");
  ExifData metadata;

  auto flashData = Value::create(unsignedByte);
  flashData->read("1 2");  // count == 2
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  // Should fall through to "(value)" since count != 1
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Different non-zero mode values (mode = 2)
TEST_F(PrintFlashMasterDataFl6Test_489, ModeTwo_489) {
  auto value = Value::create(unsignedByte);
  value->read("12");
  ExifData metadata;

  auto flashData = Value::create(unsignedByte);
  flashData->read("2");  // mode & 0x0F == 2
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value of 0 with non-zero mode should produce compensation output
TEST_F(PrintFlashMasterDataFl6Test_489, ZeroValueWithNonZeroMode_489) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData metadata;

  auto flashData = Value::create(unsignedByte);
  flashData->read("3");  // mode & 0x0F == 3
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // Should not be "(0)" - it should be a proper flash compensation value
}

// Test: Max byte value (255) for the flash compensation value
TEST_F(PrintFlashMasterDataFl6Test_489, MaxByteValue_489) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  ExifData metadata;

  auto flashData = Value::create(unsignedByte);
  flashData->read("1");
  metadata.add(ExifKey("Exif.NikonFl6.ExternalFlashData1"), flashData.get());

  Nikon3MakerNote::printFlashMasterDataFl6(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
