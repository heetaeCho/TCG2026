#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_461 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tests for printAf2AreaMode
// =============================================================================

// Test: When metadata is nullptr, should use ContrastDetectAfOff table
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_NullMetadata_UsesOffTable_461) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Single-point AF");
}

// Test: When metadata is nullptr with value 1
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_NullMetadata_Value1_461) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF");
}

// Test: When metadata has ContrastDetectAF = 0, should use Off table
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_Zero_UsesOffTable_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(0);

  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Single-point AF");
}

// Test: When metadata has ContrastDetectAF = 1, should use On table
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_One_UsesOnTable_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(1);

  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Contrast AF");
}

// Test: ContrastDetectAF = 1 with value 1 -> "Normal-area AF"
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_One_Value1_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(1);

  auto value = Value::create(unsignedShort);
  value->read("1");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Normal-area AF");
}

// Test: ContrastDetectAF = 1 with value 2 -> "Wide-area AF"
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_One_Value2_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(1);

  auto value = Value::create(unsignedShort);
  value->read("2");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Wide-area AF");
}

// Test: ContrastDetectAF = 1 with value 3 -> "Face-priority AF"
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_One_Value3_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(1);

  auto value = Value::create(unsignedShort);
  value->read("3");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Face-priority AF");
}

// Test: ContrastDetectAF = 1 with value 4 -> "Subject-tracking AF"
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_One_Value4_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(1);

  auto value = Value::create(unsignedShort);
  value->read("4");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Subject-tracking AF");
}

// Test: ContrastDetectAF = 1 with value 5 -> "Pinpoint AF"
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_One_Value5_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(1);

  auto value = Value::create(unsignedShort);
  value->read("5");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Pinpoint AF");
}

// Test: ContrastDetectAF Off table - various values
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value8_AutoAreaAF_461) {
  auto value = Value::create(unsignedShort);
  value->read("8");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Auto-area AF");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value9_3DTracking_461) {
  auto value = Value::create(unsignedShort);
  value->read("9");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "3D-tracking");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value13_GroupAreaAF_461) {
  auto value = Value::create(unsignedShort);
  value->read("13");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Group-area AF");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value17_GroupAreaAFVL_461) {
  auto value = Value::create(unsignedShort);
  value->read("17");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Group-area AF (VL)");
}

// Test: When metadata exists but ContrastDetectAF key is not found, should default to 0 (Off table)
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_MetadataWithoutContrastDetectAF_UsesOffTable_461) {
  ExifData exifData;
  // Add some other key, but not ContrastDetectAF
  exifData["Exif.Photo.ExposureTime"] = "1/100";

  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Single-point AF");
}

// Test: Boundary - unknown value in Off table (value beyond known range)
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_UnknownValue_461) {
  auto value = Value::create(unsignedShort);
  value->read("99");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  std::string result = os.str();
  // Unknown values typically print as "(99)"
  EXPECT_FALSE(result.empty());
}

// Test: Boundary - unknown value in On table (value beyond known range)
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OnTable_UnknownValue_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(1);

  auto value = Value::create(unsignedShort);
  value->read("99");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: ContrastDetectAF with value > 1 should still use On table (non-zero)
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAF_GreaterThanOne_UsesOnTable_461) {
  ExifData exifData;
  exifData["Exif.NikonAf2.ContrastDetectAF"] = uint16_t(2);

  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Contrast AF");
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ReturnsOstream_461) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test: Off table value 2 -> "Closest Subject"
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value2_ClosestSubject_461) {
  auto value = Value::create(unsignedShort);
  value->read("2");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Closest Subject");
}

// Test: Off table value 7 -> "Dynamic-area AF (51 points), 3D-tracking"
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value7_461) {
  auto value = Value::create(unsignedShort);
  value->read("7");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF (51 points), 3D-tracking");
}

// Test: Off table all values are accessible
TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value3_GroupDynamicAF_461) {
  auto value = Value::create(unsignedShort);
  value->read("3");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Group Dynamic AF");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value4_461) {
  auto value = Value::create(unsignedShort);
  value->read("4");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF (9 points)");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value5_461) {
  auto value = Value::create(unsignedShort);
  value->read("5");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF (21 points)");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value6_461) {
  auto value = Value::create(unsignedShort);
  value->read("6");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF (51 points)");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value10_461) {
  auto value = Value::create(unsignedShort);
  value->read("10");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Single Area AF, Wide");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value11_461) {
  auto value = Value::create(unsignedShort);
  value->read("11");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF, Wide");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value12_461) {
  auto value = Value::create(unsignedShort);
  value->read("12");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "3D-tracking/Wide");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value14_461) {
  auto value = Value::create(unsignedShort);
  value->read("14");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF (25 points)");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value15_461) {
  auto value = Value::create(unsignedShort);
  value->read("15");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Dynamic-area AF (72 points)");
}

TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OffTable_Value16_461) {
  auto value = Value::create(unsignedShort);
  value->read("16");
  Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Group-area AF (HL)");
}
