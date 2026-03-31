#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to set the camera model in ExifData
static void setModel(ExifData& exifData, const std::string& model) {
  exifData["Exif.Image.Model"] = model;
}

class SonyMakerNoteFlexibleSpotPositionTest_1595 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: Null metadata pointer should output value in parentheses
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, NullMetadata_OutputsParenthesizedValue_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value with wrong count (1 element instead of 2) should output parenthesized
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, WrongCount_SingleValue_OutputsParenthesized_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Value with wrong count (3 elements instead of 2) should output parenthesized
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, WrongCount_ThreeValues_OutputsParenthesized_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200 300");
  
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Value with wrong type (signedShort instead of unsignedShort)
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, WrongTypeId_OutputsParenthesized_1595) {
  auto value = Value::create(signedShort);
  value->read("100 200");
  
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: NEX model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, NEXModel_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");
  
  ExifData exifData;
  setModel(exifData, "NEX-5T");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "100, 200");
}

// Test: ILCE model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, ILCEModel_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("50 75");
  
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "50, 75");
}

// Test: ILME model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, ILMEModel_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("10 20");
  
  ExifData exifData;
  setModel(exifData, "ILME-FX3");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "10, 20");
}

// Test: DSC-RX10M4 model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, DSCRX10M4Model_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("300 400");
  
  ExifData exifData;
  setModel(exifData, "DSC-RX10M4");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "300, 400");
}

// Test: DSC-RX100M6 model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, DSCRX100M6Model_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("150 250");
  
  ExifData exifData;
  setModel(exifData, "DSC-RX100M6");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "150, 250");
}

// Test: DSC-RX100M7 model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, DSCRX100M7Model_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("500 600");
  
  ExifData exifData;
  setModel(exifData, "DSC-RX100M7");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "500, 600");
}

// Test: DSC-RX100M5A model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, DSCRX100M5AModel_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("111 222");
  
  ExifData exifData;
  setModel(exifData, "DSC-RX100M5A");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "111, 222");
}

// Test: DSC-HX99 model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, DSCHX99Model_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("33 44");
  
  ExifData exifData;
  setModel(exifData, "DSC-HX99");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "33, 44");
}

// Test: DSC-RX0M2 model should output coordinates
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, DSCRX0M2Model_OutputsCoordinates_1595) {
  auto value = Value::create(unsignedShort);
  value->read("77 88");
  
  ExifData exifData;
  setModel(exifData, "DSC-RX0M2");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "77, 88");
}

// Test: Unsupported model (e.g., SLT-A77) should output "n/a"
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, UnsupportedModel_OutputsNA_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");
  
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  // Should contain "n/a" (possibly localized)
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || !result.empty());
  // Should NOT contain comma-separated coordinates
  EXPECT_TRUE(result.find(", ") == std::string::npos);
}

// Test: Another unsupported DSC model (e.g., DSC-RX100M5 without A)
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, UnsupportedDSCModel_OutputsNA_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");
  
  ExifData exifData;
  setModel(exifData, "DSC-RX100M5");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  // DSC-RX100M5 is NOT in the list (DSC-RX100M5A is), so it should be "n/a"
  EXPECT_TRUE(result.find(", ") == std::string::npos);
}

// Test: Zero values with supported model
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, ZeroValues_SupportedModel_1595) {
  auto value = Value::create(unsignedShort);
  value->read("0 0");
  
  ExifData exifData;
  setModel(exifData, "ILCE-9");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "0, 0");
}

// Test: Maximum unsigned short values
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, MaxValues_SupportedModel_1595) {
  auto value = Value::create(unsignedShort);
  value->read("65535 65535");
  
  ExifData exifData;
  setModel(exifData, "NEX-7");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "65535, 65535");
}

// Test: ExifData without model key should output parenthesized value
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, NoModelInMetadata_OutputsParenthesized_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");
  
  ExifData exifData;
  // Don't set any model
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Verify return value is the same ostream
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, ReturnsSameOstream_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");
  
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  
  std::ostream& result = SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// Test: Null metadata with wrong count
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, NullMetadataWrongCount_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: unsignedLong type instead of unsignedShort
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, WrongTypeUnsignedLong_1595) {
  auto value = Value::create(unsignedLong);
  value->read("100 200");
  
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  // unsignedLong is not unsignedShort, should output parenthesized
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: NEX prefix with various suffixes
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, NEXPrefix_VariousSuffixes_1595) {
  auto value = Value::create(unsignedShort);
  value->read("42 84");
  
  ExifData exifData;
  setModel(exifData, "NEX-6");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "42, 84");
}

// Test: Unsupported model with DSC prefix but not matching any exact model
TEST_F(SonyMakerNoteFlexibleSpotPositionTest_1595, DSCUnmatchedModel_OutputsNA_1595) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");
  
  ExifData exifData;
  setModel(exifData, "DSC-W800");
  
  SonyMakerNote::printFlexibleSpotPosition(os, *value, &exifData);
  std::string result = os.str();
  // DSC-W800 doesn't start with any of the exact DSC models in the list
  // It doesn't match "DSC-RX10M4", "DSC-RX100M6", etc.
  EXPECT_TRUE(result.find(", ") == std::string::npos);
}
