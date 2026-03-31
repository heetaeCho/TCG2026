#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

// Include the internal header for SonyMakerNote
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteAFTrackingTest_1598 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to set the camera model in ExifData
  void setModel(ExifData& exifData, const std::string& model) {
    exifData["Exif.Image.Model"] = model;
  }
};

// Test: null metadata pointer should produce parenthesized output
TEST_F(SonyMakerNoteAFTrackingTest_1598, NullMetadata_1598) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: value with wrong type (not unsignedByte) should produce parenthesized output
TEST_F(SonyMakerNoteAFTrackingTest_1598, WrongValueType_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");
  auto value = Value::create(unsignedShort);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: value with count != 1 should produce parenthesized output
TEST_F(SonyMakerNoteAFTrackingTest_1598, MultipleValues_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");
  auto value = Value::create(unsignedByte);
  value->read("0 1");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Non-DSC model (e.g., ILCE-7M3) should use the tag lookup table
// value=0 means "Off" per sonyAFTracking table
TEST_F(SonyMakerNoteAFTrackingTest_1598, NonDSCModel_ValueOff_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Off");
}

// Test: Non-DSC model with value=1 should output "Face tracking"
TEST_F(SonyMakerNoteAFTrackingTest_1598, NonDSCModel_ValueFaceTracking_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");
  auto value = Value::create(unsignedByte);
  value->read("1");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Face tracking");
}

// Test: Non-DSC model with value=2 should output "Lock on AF"
TEST_F(SonyMakerNoteAFTrackingTest_1598, NonDSCModel_ValueLockOnAF_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");
  auto value = Value::create(unsignedByte);
  value->read("2");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Lock on AF");
}

// Test: DSC-RX10M4 (in the exclusion list) should use the tag lookup table, not n/a
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_RX10M4_UsesTagTable_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-RX10M4");
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Off");
}

// Test: DSC-RX100M6 (in the exclusion list) should use the tag lookup table
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_RX100M6_UsesTagTable_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-RX100M6");
  auto value = Value::create(unsignedByte);
  value->read("1");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Face tracking");
}

// Test: DSC-RX100M7 (in the exclusion list) should use the tag lookup table
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_RX100M7_UsesTagTable_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-RX100M7");
  auto value = Value::create(unsignedByte);
  value->read("2");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Lock on AF");
}

// Test: DSC-RX100M5A (in the exclusion list) should use the tag lookup table
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_RX100M5A_UsesTagTable_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-RX100M5A");
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Off");
}

// Test: DSC-HX99 (in the exclusion list) should use the tag lookup table
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_HX99_UsesTagTable_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-HX99");
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Off");
}

// Test: DSC-RX0M2 (in the exclusion list) should use the tag lookup table
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_RX0M2_UsesTagTable_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-RX0M2");
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "Off");
}

// Test: A DSC model NOT in the exclusion list should output "n/a"
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_OtherModel_OutputsNA_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-WX500");
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "n/a");
}

// Test: Another DSC model not in exclusion list
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_HX300_OutputsNA_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-HX300");
  auto value = Value::create(unsignedByte);
  value->read("1");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_EQ(result, "n/a");
}

// Test: No model in metadata should produce parenthesized output
TEST_F(SonyMakerNoteAFTrackingTest_1598, NoModelInMetadata_1598) {
  std::ostringstream os;
  ExifData metadata;
  // Don't set any model
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Non-DSC model with unknown value (e.g., 255) should still produce output
// (the tag table likely outputs the numeric value as unknown)
TEST_F(SonyMakerNoteAFTrackingTest_1598, NonDSCModel_UnknownValue_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-9");
  auto value = Value::create(unsignedByte);
  value->read("255");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  // Should produce some output (either "(255)" or a tag lookup result)
  EXPECT_FALSE(result.empty());
}

// Test: Return value is a reference to the same stream
TEST_F(SonyMakerNoteAFTrackingTest_1598, ReturnsSameStream_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& returned = SonyMakerNote::printAFTracking(os, *value, &metadata);
  EXPECT_EQ(&returned, &os);
}

// Test: Return value is the same stream even for null metadata
TEST_F(SonyMakerNoteAFTrackingTest_1598, ReturnsSameStreamNullMetadata_1598) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& returned = SonyMakerNote::printAFTracking(os, *value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test: DSC-RX100M5 is NOT in the exclusion list (only DSC-RX100M5A is)
// so it should output "n/a"
TEST_F(SonyMakerNoteAFTrackingTest_1598, DSC_RX100M5_OutputsNA_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-RX100M5");
  auto value = Value::create(unsignedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  // DSC-RX100M5 starts with "DSC-RX100M5" which also starts with "DSC-RX100M5A"? No.
  // "DSC-RX100M5".starts_with("DSC-RX100M5A") is false because M5A is longer.
  // But "DSC-RX100M5".starts_with("DSC-RX100M5") checking: the model list has "DSC-RX100M5A"
  // model.starts_with("DSC-RX100M5A") for model="DSC-RX100M5" is false.
  // However, we need to check all models in the list. None match for "DSC-RX100M5".
  // So any_of returns false, and since model starts with "DSC-", the condition is:
  // starts_with("DSC-") && !any_of(...) => true && true => falls through to n/a
  // Wait, the logic is: if (!model.starts_with("DSC-") || std::any_of(...))
  // For DSC-RX100M5: starts_with("DSC-") is true, so !starts_with is false.
  // any_of checks if model starts with any of the listed models. 
  // "DSC-RX100M5".starts_with("DSC-RX100M5A") is false. But wait...
  // Actually checking all: "DSC-RX10M4" no, "DSC-RX100M6" no, "DSC-RX100M7" no, 
  // "DSC-RX100M5A" no (M5 doesn't start with M5A), "DSC-HX99" no, "DSC-RX0M2" no.
  // So any_of is false. The whole condition: false || false = false.
  // So it goes to the else branch: n/a.
  EXPECT_EQ(result, "n/a");
}

// Test: signedByte type should produce parenthesized output (not unsignedByte)
TEST_F(SonyMakerNoteAFTrackingTest_1598, SignedByteType_1598) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");
  auto value = Value::create(signedByte);
  value->read("0");
  SonyMakerNote::printAFTracking(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}
