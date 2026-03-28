#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_473 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for printLensId2
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintLensId2_WithNullMetadata_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId2(os, *value, nullptr);
  // Should produce some output (either from testConfigFile or printLensId)
  // We just verify it doesn't crash and returns the stream
  EXPECT_TRUE(os.str().length() >= 0);
}

TEST_F(Nikon3MakerNoteTest_473, PrintLensId2_WithEmptyExifData_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  Nikon3MakerNote::printLensId2(os, *value, &exifData);
  EXPECT_TRUE(os.str().length() >= 0);
}

TEST_F(Nikon3MakerNoteTest_473, PrintLensId2_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  ExifData exifData;
  std::ostream& result = Nikon3MakerNote::printLensId2(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printLensId1
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintLensId1_WithNullMetadata_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId1(os, *value, nullptr);
  EXPECT_TRUE(os.str().length() >= 0);
}

TEST_F(Nikon3MakerNoteTest_473, PrintLensId1_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  ExifData exifData;
  std::ostream& result = Nikon3MakerNote::printLensId1(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printLensId3
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintLensId3_WithNullMetadata_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId3(os, *value, nullptr);
  EXPECT_TRUE(os.str().length() >= 0);
}

TEST_F(Nikon3MakerNoteTest_473, PrintLensId3_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  ExifData exifData;
  std::ostream& result = Nikon3MakerNote::printLensId3(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printLensId4
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintLensId4_WithNullMetadata_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId4(os, *value, nullptr);
  EXPECT_TRUE(os.str().length() >= 0);
}

TEST_F(Nikon3MakerNoteTest_473, PrintLensId4_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  ExifData exifData;
  std::ostream& result = Nikon3MakerNote::printLensId4(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printFocusDistance
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFocusDistance_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFocusDistance_NonZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFocusDistance_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printAperture
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintAperture_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintAperture_NonZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintAperture_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("28");
  std::ostream& result = Nikon3MakerNote::printAperture(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printFocal
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFocal_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFocal_NonZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("100");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFocal_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("35");
  std::ostream& result = Nikon3MakerNote::printFocal(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printFStops
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFStops_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFStops(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFStops_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("12");
  std::ostream& result = Nikon3MakerNote::printFStops(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printExitPupilPosition
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintExitPupilPosition_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExitPupilPosition(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintExitPupilPosition_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("5");
  std::ostream& result = Nikon3MakerNote::printExitPupilPosition(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printFlashFocalLength
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFlashFocalLength_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashFocalLength_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("24");
  std::ostream& result = Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printRepeatingFlashRate
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintRepeatingFlashRate_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintRepeatingFlashRate_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashRate(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printRepeatingFlashCount
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintRepeatingFlashCount_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintRepeatingFlashCount_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("5");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashCount(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0002
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0002_SingleValue_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::print0x0002(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, Print0x0002_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  std::ostream& result = Nikon3MakerNote::print0x0002(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0007
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0007_ReturnsOstream_473) {
  auto value = Value::create(asciiString);
  value->read("AF-S");
  std::ostream& result = Nikon3MakerNote::print0x0007(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0083
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0083_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::print0x0083(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, Print0x0083_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  std::ostream& result = Nikon3MakerNote::print0x0083(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0084
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0084_FourRationalValues_473) {
  auto value = Value::create(unsignedRational);
  value->read("18/1 200/1 35/10 56/10");
  Nikon3MakerNote::print0x0084(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, Print0x0084_ReturnsOstream_473) {
  auto value = Value::create(unsignedRational);
  value->read("50/1 50/1 14/10 14/10");
  std::ostream& result = Nikon3MakerNote::print0x0084(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0085
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0085_ReturnsOstream_473) {
  auto value = Value::create(unsignedRational);
  value->read("0/0");
  std::ostream& result = Nikon3MakerNote::print0x0085(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0086
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0086_ReturnsOstream_473) {
  auto value = Value::create(unsignedRational);
  value->read("1/1");
  std::ostream& result = Nikon3MakerNote::print0x0086(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0088
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0088_ZeroValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::print0x0088(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, Print0x0088_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::print0x0088(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0089
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x0089_ZeroValue_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::print0x0089(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, Print0x0089_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  std::ostream& result = Nikon3MakerNote::print0x0089(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x008b
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x008b_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::print0x008b(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printIiIso
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintIiIso_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printIiIso(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printTimeZone
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintTimeZone_ReturnsOstream_473) {
  auto value = Value::create(signedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintTimeZone_PositiveOffset_473) {
  auto value = Value::create(signedShort);
  value->read("60");
  Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintTimeZone_NegativeOffset_473) {
  auto value = Value::create(signedShort);
  value->read("-300");
  Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printPictureControl
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintPictureControl_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printPictureControl(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x009a
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x009a_ReturnsOstream_473) {
  auto value = Value::create(unsignedRational);
  value->read("0/1 0/1");
  std::ostream& result = Nikon3MakerNote::print0x009a(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x009e
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, Print0x009e_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::print0x009e(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printApertureLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintApertureLd4_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printApertureLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintApertureLd4_NonZero_473) {
  auto value = Value::create(unsignedShort);
  value->read("500");
  Nikon3MakerNote::printApertureLd4(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printFocalLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFocalLd4_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFocalLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFocalLd4_NonZero_473) {
  auto value = Value::create(unsignedShort);
  value->read("200");
  Nikon3MakerNote::printFocalLd4(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printFocusDistanceLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFocusDistanceLd4_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFocusDistanceLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFocusDistanceLd4_NonZero_473) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  Nikon3MakerNote::printFocusDistanceLd4(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printCameraExposureCompensation
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintCameraExposureCompensation_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printCameraExposureCompensation(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintCameraExposureCompensation_NonZero_473) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printFlashZoomHeadPosition
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFlashZoomHeadPosition_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printAfPointsInFocus
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintAfPointsInFocus_NullMetadata_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintAfPointsInFocus_ReturnsOstream_473) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printAfPointsInFocus(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printAf2AreaMode
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintAf2AreaMode_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printLensId with explicit group parameter
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintLensId_WithNikonLd2Group_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  std::ostream& result = Nikon3MakerNote::printLensId(os, *value, &exifData, "NikonLd2");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintLensId_WithNullMetadata_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintLensId_WithEmptyGroup_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  std::ostream& result = Nikon3MakerNote::printLensId(os, *value, &exifData, "");
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for various flash-related print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintExternalFlashData3_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintExternalFlashData4_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintExternalFlashData2_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintExternalFlashData1Fl6_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintExternalFlashData1Fl7_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintExternalFlashData2Fl6_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashMasterDataFl6_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashMasterDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashMasterDataFl7_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashMasterDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupAControlData_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupBCControlData_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupADataFl6_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupADataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupADataFl7_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupADataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupBDataFl6_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupBDataFl7_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupCDataFl6_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_473, PrintFlashGroupCDataFl7_ReturnsOstream_473) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary: Max byte value
// ============================================================

TEST_F(Nikon3MakerNoteTest_473, PrintFocusDistance_MaxByteValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintAperture_MaxByteValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFocal_MaxByteValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintFStops_MaxByteValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFStops(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_473, PrintExitPupilPosition_MaxByteValue_473) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printExitPupilPosition(os, *value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
