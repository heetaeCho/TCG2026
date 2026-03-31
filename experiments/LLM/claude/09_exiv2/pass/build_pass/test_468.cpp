#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_468 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When value type is not unsignedShort, output raw value in parentheses
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_NonUnsignedShortType_468) {
  // Use a string value (asciiString type) which is not unsignedShort
  StringValue strVal;
  strVal.read("test");
  
  Nikon3MakerNote::printAfPointsInFocus(os, strVal, nullptr);
  std::string result = os.str();
  // Should output "(test)" or similar parenthesized form
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When metadata is nullptr, no byte swap occurs (non-D model path)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_NullMetadata_468) {
  UShortValue val;
  val.value_.push_back(1);  // Center point

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // With value 1 and no D model, bit 0 = Center
  EXPECT_TRUE(result.find("Center") != std::string::npos);
}

// Test: When value is 0x07ff without D model, should print "All 11 Points"
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_All11Points_NoDModel_468) {
  UShortValue val;
  val.value_.push_back(0x07ff);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("All 11 Points") != std::string::npos);
}

// Test: With NIKON D model, bytes are swapped. 0x07ff after swap should give all 11 points
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_All11Points_DModel_468) {
  ExifData exifData;
  exifData["Exif.Image.Model"] = "NIKON D700";

  // For D model, val = (val >> 8) | ((val & 0x00ff) << 8)
  // We want after swap to get 0x07ff
  // 0x07ff -> swap -> (0x07ff >> 8) | ((0x07ff & 0xff) << 8) = 0x07 | (0xff << 8) = 0x07 | 0xff00 = 0xff07
  // So we need input such that after swap = 0x07ff
  // input >> 8 | (input & 0xff) << 8 = 0x07ff
  // Let input = 0xff07: (0xff07 >> 8) | ((0xff07 & 0xff) << 8) = 0xff | (0x07 << 8) = 0xff | 0x0700 = 0x07ff
  UShortValue val;
  val.value_.push_back(0xff07);

  Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("All 11 Points") != std::string::npos);
}

// Test: With NIKON D model, byte swap is applied for single AF point
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_CenterPoint_DModel_468) {
  ExifData exifData;
  exifData["Exif.Image.Model"] = "NIKON D5000";

  // We want after swap = 1 (Center)
  // input such that (input >> 8) | ((input & 0xff) << 8) = 1
  // input = 0x0100: (0x0100 >> 8) | ((0x0100 & 0xff) << 8) = 0x01 | 0x0000 = 0x01
  UShortValue val;
  val.value_.push_back(0x0100);

  Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
}

// Test: With non-Nikon D model, no byte swap
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_NonDModel_468) {
  ExifData exifData;
  exifData["Exif.Image.Model"] = "NIKON COOLPIX";

  UShortValue val;
  val.value_.push_back(1);  // Center

  Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
}

// Test: Top AF point (bit 1 = 2)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_TopPoint_468) {
  UShortValue val;
  val.value_.push_back(2);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Top") != std::string::npos);
}

// Test: Multiple AF points (Center + Top)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_MultiplePoints_468) {
  UShortValue val;
  val.value_.push_back(3);  // bits 0 and 1: Center + Top

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
  EXPECT_TRUE(result.find("Top") != std::string::npos);
}

// Test: Value of 0 (no AF points in focus)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_NoPoints_468) {
  UShortValue val;
  val.value_.push_back(0);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  // With 0, no bits set, output might be empty or "(none)" etc
  // Just verify it doesn't crash and produces some output
  EXPECT_TRUE(result.find("Center") == std::string::npos);
}

// Test: Bottom AF point (bit 2 = 4)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_BottomPoint_468) {
  UShortValue val;
  val.value_.push_back(4);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Bottom") != std::string::npos);
}

// Test: Far Right AF point (bit 10 = 1024)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_FarRight_468) {
  UShortValue val;
  val.value_.push_back(1024);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Far Right") != std::string::npos);
}

// Test: Empty ExifData (model key not found), should behave like no D model
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_EmptyExifData_468) {
  ExifData exifData;

  UShortValue val;
  val.value_.push_back(0x07ff);

  Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("All 11 Points") != std::string::npos);
}

// Test: Mid-left AF point (bit 3 = 8)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_MidLeft_468) {
  UShortValue val;
  val.value_.push_back(8);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Mid-left") != std::string::npos);
}

// Test: Mid-right AF point (bit 4 = 16)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_MidRight_468) {
  UShortValue val;
  val.value_.push_back(16);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Mid-right") != std::string::npos);
}

// Test: With signedShort type (not unsignedShort), should output in parentheses
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_SignedShortType_468) {
  auto val = Value::create(signedShort);
  val->read("42");

  Nikon3MakerNote::printAfPointsInFocus(os, *val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_ReturnsSameStream_468) {
  UShortValue val;
  val.value_.push_back(1);

  std::ostream& ret = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: Model string "NIKON D" exactly triggers D model path
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_ModelExactNikonD_468) {
  ExifData exifData;
  exifData["Exif.Image.Model"] = "NIKON D";

  // With D model: val = (0x0100 >> 8) | ((0x0100 & 0xff) << 8) = 1 | 0 = 1 = Center
  UShortValue val;
  val.value_.push_back(0x0100);

  Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
}

// Test: Upper-left AF point (bit 5 = 32)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_UpperLeft_468) {
  UShortValue val;
  val.value_.push_back(32);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Upper-left") != std::string::npos);
}

// Test: Lower-right AF point (bit 8 = 256)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_LowerRight_468) {
  UShortValue val;
  val.value_.push_back(256);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Lower-right") != std::string::npos);
}

// Test: Far Left AF point (bit 9 = 512)
TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_FarLeft_468) {
  UShortValue val;
  val.value_.push_back(512);

  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Far Left") != std::string::npos);
}
