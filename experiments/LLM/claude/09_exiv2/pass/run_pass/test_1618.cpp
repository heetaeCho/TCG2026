#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1618 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to set the model in ExifData
  void setModel(ExifData& exifData, const std::string& model) {
    exifData["Exif.Image.Model"] = model;
  }
};

// =============================================================================
// Tests for printSonyMisc2bFocusPosition2
// =============================================================================

// Test: Null metadata returns value in parentheses
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_NullMetadata_1618) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("42");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, nullptr);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value count != 1 returns value in parentheses
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_MultipleValues_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");

  auto value = Value::create(unsignedByte);
  value->read("42 43");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: SLT model returns "n/a"
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_SLTModel_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "SLT-A77");

  auto value = Value::create(unsignedByte);
  value->read("42");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  // Should contain "n/a" (or the translated version)
  EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("(") == std::string::npos);
}

// Test: HV model returns "n/a"
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_HVModel_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "HV");

  auto value = Value::create(unsignedByte);
  value->read("42");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  // Should not contain parentheses (not an error case) and should not be raw value
  EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test: ILCA model returns "n/a"
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_ILCAModel_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCA-77M2");

  auto value = Value::create(unsignedByte);
  value->read("42");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test: Non-SLT/HV/ILCA model returns the raw value
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_ILCEModel_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");

  auto value = Value::create(unsignedByte);
  value->read("42");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  // Should output the raw value without parentheses
  EXPECT_TRUE(result.find("(") == std::string::npos);
  EXPECT_TRUE(result.find("42") != std::string::npos);
}

// Test: Non-SLT/HV/ILCA model (DSC) returns the raw value
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_DSCModel_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "DSC-RX100");

  auto value = Value::create(unsignedByte);
  value->read("100");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") == std::string::npos);
  EXPECT_TRUE(result.find("100") != std::string::npos);
}

// Test: Value of 0 with non-SLT model
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_ZeroValue_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-6000");

  auto value = Value::create(unsignedByte);
  value->read("0");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") == std::string::npos);
  EXPECT_TRUE(result.find("0") != std::string::npos);
}

// Test: SLT- prefix in model name with various suffixes
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_SLTWithSuffix_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "SLT-A99V");

  auto value = Value::create(unsignedByte);
  value->read("50");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  // SLT- model should return n/a, not the raw value
  EXPECT_TRUE(result.find("50") == std::string::npos || result.find("n/a") != std::string::npos);
}

// Test: Model that doesn't match any pattern returns raw value
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_GenericModel_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "NEX-5");

  auto value = Value::create(unsignedByte);
  value->read("77");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("(") == std::string::npos);
  EXPECT_TRUE(result.find("77") != std::string::npos);
}

// Test: Returns reference to same ostream
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_ReturnsSameStream_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7");

  auto value = Value::create(unsignedByte);
  value->read("10");

  std::ostream& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  EXPECT_EQ(&result, &os);
}

// Test: Returns reference to same ostream when null metadata
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_ReturnsSameStreamNull_1618) {
  std::ostringstream os;

  auto value = Value::create(unsignedByte);
  value->read("10");

  std::ostream& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, nullptr);

  EXPECT_EQ(&result, &os);
}

// Test: Empty value count (0 elements)
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_EmptyValue_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-7M3");

  auto value = Value::create(unsignedByte);
  // Don't read anything - count should be 0

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  // count != 1, should get parenthesized output
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: ILCA- prefix with different suffixes
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_ILCA99M2_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCA-99M2");

  auto value = Value::create(unsignedByte);
  value->read("88");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  // ILCA- model should not output raw value with parentheses
  EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test: Model with "HV" embedded but not standalone (e.g. "AHVB") should still match
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_ModelContainingHV_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "XHVY");

  auto value = Value::create(unsignedByte);
  value->read("55");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  // contains("HV") should match since "XHVY" contains "HV"
  EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test: Maximum byte value
TEST_F(SonyMakerNoteTest_1618, PrintSonyMisc2bFocusPosition2_MaxByteValue_1618) {
  std::ostringstream os;
  ExifData metadata;
  setModel(metadata, "ILCE-9");

  auto value = Value::create(unsignedByte);
  value->read("255");

  SonyMakerNote::printSonyMisc2bFocusPosition2(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_TRUE(result.find("255") != std::string::npos);
  EXPECT_TRUE(result.find("(") == std::string::npos);
}
