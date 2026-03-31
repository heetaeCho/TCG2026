#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to set the camera model in ExifData
static void setModel(ExifData& exifData, const std::string& model) {
  exifData["Exif.Image.Model"] = model;
}

class SonyMakerNoteAFPointsUsedTest_1597 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: Null metadata returns value in parentheses
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, NullMetadataReturnsParenthesizedValue_1597) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Wrong type (not unsignedByte) returns value in parentheses
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, WrongTypeReturnsParenthesizedValue_1597) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Wrong type with null metadata returns parenthesized value
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, WrongTypeNullMetadataReturnsParenthesizedValue_1597) {
  auto value = Value::create(unsignedShort);
  value->read("42");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Model not found in metadata returns parenthesized value
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, NoModelInMetadataReturnsParenthesizedValue_1597) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  // Don't set any model
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Non-ILCA/DSC model uses Set1 (e.g., SLT-A77 model)
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, NonILCANonDSCModelUsesSet1_1597) {
  // Create a value with bit 0 set (Center)
  auto value = Value::create(unsignedByte);
  // Byte value 1 = bit 0 set = "Center"
  std::vector<byte> buf = {0x01};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
}

// Test: ILCA-68 model uses Set2
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, ILCA68UsesSet2_1597) {
  auto value = Value::create(unsignedByte);
  // Byte value 1 = bit 0 set = "A5" in Set2
  std::vector<byte> buf = {0x01};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "ILCA-68");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("A5") != std::string::npos);
}

// Test: ILCA-77M2 model uses Set2
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, ILCA77M2UsesSet2_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0x01};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "ILCA-77M2");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("A5") != std::string::npos);
}

// Test: ILCA- model that is not ILCA-68 or ILCA-77M2 returns n/a
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, OtherILCAModelReturnsNA_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0x01};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "ILCA-99M2");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos);
}

// Test: DSC- model returns n/a
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, DSCModelReturnsNA_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0x01};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "DSC-RX100");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos);
}

// Test: Non-ILCA/DSC model with no bits set
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, NoBitsSetNonILCA_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0x00};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  // With no bits set, we should get some output (possibly "(none)" or empty list)
  EXPECT_FALSE(result.empty());
}

// Test: Non-ILCA/DSC model with multiple bits set
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, MultipleBitsSetNonILCA_1597) {
  auto value = Value::create(unsignedByte);
  // 0x03 = bits 0 and 1 set = "Center" and "Top"
  std::vector<byte> buf = {0x03};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
  EXPECT_TRUE(result.find("Top") != std::string::npos);
}

// Test: ILCA-68 with no bits set
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, NoBitsSetILCA68_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0x00};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "ILCA-68");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: ILCA-68 with multiple bits set
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, MultipleBitsSetILCA68_1597) {
  auto value = Value::create(unsignedByte);
  // 0x03 = bits 0 and 1 set = "A5" and "A6"
  std::vector<byte> buf = {0x03};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "ILCA-68");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("A5") != std::string::npos);
  EXPECT_TRUE(result.find("A6") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, ReturnsOstreamReference_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0x01};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostringstream os;
  std::ostream& ret = SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  EXPECT_EQ(&ret, &os);
}

// Test: Return value is same ostream when null metadata
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, ReturnsOstreamReferenceNullMetadata_1597) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  std::ostream& ret = SonyMakerNote::printAFPointsUsed(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: signedByte type (not unsignedByte) returns parenthesized value
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, SignedByteTypeReturnsParenthesized_1597) {
  auto value = Value::create(signedByte);
  value->read("1");
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: ILCA-77M2 variant with suffix
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, ILCA77M2WithSuffixUsesSet2_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0x02};  // bit 1 = "A6"
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "ILCA-77M2 Some Suffix");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("A6") != std::string::npos);
}

// Test: Non-ILCA/DSC model with multiple bytes
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, MultipleByteValueNonILCA_1597) {
  auto value = Value::create(unsignedByte);
  // Two bytes: 0x01, 0x01 - bit 0 from first byte and bit 8 from second byte
  std::vector<byte> buf = {0x01, 0x01};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
  EXPECT_TRUE(result.find("Upper-left") != std::string::npos);
}

// Test: ILCA- prefix that is not 68 or 77M2 returns n/a
TEST_F(SonyMakerNoteAFPointsUsedTest_1597, ILCAGenericReturnsNA_1597) {
  auto value = Value::create(unsignedByte);
  std::vector<byte> buf = {0xFF};
  value->read(buf.data(), buf.size(), littleEndian);
  ExifData exifData;
  setModel(exifData, "ILCA-100");
  std::ostringstream os;
  SonyMakerNote::printAFPointsUsed(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos);
}
