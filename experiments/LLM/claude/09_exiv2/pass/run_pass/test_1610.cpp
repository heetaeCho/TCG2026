#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteAFModeTest_1610 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When value count is not 1, should output raw value in parentheses
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_WrongCount_1610) {
  // Create a value with count != 1 (two values)
  UShortValue val;
  val.read("1 2");
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  // Should contain parentheses since count != 1
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value type is not unsignedShort, should output raw value in parentheses
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_WrongType_1610) {
  // Create a value with wrong type (unsigned long instead of unsigned short)
  ULongValue val;
  val.read("1");
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When metadata is null, should output raw value in parentheses
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_NullMetadata_1610) {
  UShortValue val;
  val.read("1");
  
  SonyMakerNote::printAFMode(os, val, nullptr);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: With valid unsignedShort value and empty metadata (no meta version),
// should use AFModeSet1 lookup table
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_NoMetaVersion_UsesSet1_1610) {
  UShortValue val;
  val.read("0");  // 0 = "Default" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  // Should not have parentheses (valid lookup)
  // With no meta version key, it falls through to Set1
  EXPECT_FALSE(result.empty());
}

// Test: Value "1" with empty metadata should map to "Multi" in Set1
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value1_NoMetaVersion_Multi_1610) {
  UShortValue val;
  val.read("1");  // 1 = "Multi" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value "2" with empty metadata should map to "Center" in Set1
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value2_NoMetaVersion_Center_1610) {
  UShortValue val;
  val.read("2");  // 2 = "Center" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value "65535" with empty metadata should map to "n/a" in Set1
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value65535_NoMetaVersion_NA_1610) {
  UShortValue val;
  val.read("65535");  // 65535 = "n/a" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Stream reference is returned properly for chaining
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_ReturnsOstream_1610) {
  UShortValue val;
  val.read("0");
  
  ExifData metadata;
  std::ostream& ret = SonyMakerNote::printAFMode(os, val, &metadata);
  
  EXPECT_EQ(&ret, &os);
}

// Test: Stream reference is returned properly when metadata is null
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_ReturnsOstream_NullMeta_1610) {
  UShortValue val;
  val.read("0");
  
  std::ostream& ret = SonyMakerNote::printAFMode(os, val, nullptr);
  
  EXPECT_EQ(&ret, &os);
}

// Test: Value "3" maps to "Spot" in Set1 with empty metadata
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value3_Spot_1610) {
  UShortValue val;
  val.read("3");  // 3 = "Spot" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value "4" maps to "Flexible Spot" in Set1 with empty metadata
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value4_FlexibleSpot_1610) {
  UShortValue val;
  val.read("4");  // 4 = "Flexible Spot" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value "14" maps to "Tracking" in Set1 with empty metadata
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value14_Tracking_1610) {
  UShortValue val;
  val.read("14");  // 14 = "Tracking" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value "15" maps to "Face Detected" in Set1 with empty metadata
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value15_FaceDetected_1610) {
  UShortValue val;
  val.read("15");  // 15 = "Face Detected" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Using signedShort type should trigger the error path (not unsignedShort)
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_SignedShortType_1610) {
  ShortValue val;
  val.read("1");
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  // signedShort != unsignedShort, so should output parenthesized value
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Value "6" maps to "Touch" in Set1 with empty metadata
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_Value6_Touch_1610) {
  UShortValue val;
  val.read("6");  // 6 = "Touch" in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Unknown value in Set1 should still produce some output
TEST_F(SonyMakerNoteAFModeTest_1610, PrintAFMode_UnknownValue_1610) {
  UShortValue val;
  val.read("99");  // 99 is not in sonyAFModeSet1
  
  ExifData metadata;
  SonyMakerNote::printAFMode(os, val, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
