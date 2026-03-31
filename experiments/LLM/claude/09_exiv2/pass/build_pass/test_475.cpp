#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_475 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for printLensId4
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintLensId4_WithNullMetadata_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId4(os, *value, nullptr);
  // Just ensure it doesn't crash and produces some output
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintLensId4_WithEmptyExifData_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  Nikon3MakerNote::printLensId4(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintLensId4_ReturnsOstreamReference_475) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  ExifData exifData;
  std::ostream& ret = Nikon3MakerNote::printLensId4(os, *value, &exifData);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printLensId1
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintLensId1_WithNullMetadata_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId1(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintLensId1_ReturnsOstreamReference_475) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  std::ostream& ret = Nikon3MakerNote::printLensId1(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printLensId2
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintLensId2_WithNullMetadata_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId2(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printLensId3
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintLensId3_WithNullMetadata_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printFocusDistance
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFocusDistance_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFocusDistance_NonZero_475) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFocusDistance_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  std::ostream& ret = Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printFocusDistanceLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFocusDistanceLd4_Zero_475) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFocusDistanceLd4_NonZero_475) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  Nikon3MakerNote::printFocusDistanceLd4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printAperture
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintAperture_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintAperture_NonZero_475) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printApertureLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintApertureLd4_Zero_475) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printApertureLd4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintApertureLd4_NonZero_475) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  Nikon3MakerNote::printApertureLd4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printFocal
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFocal_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFocal_NonZero_475) {
  auto value = Value::create(unsignedByte);
  value->read("70");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printFocalLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFocalLd4_Zero_475) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printFocalLd4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFocalLd4_NonZero_475) {
  auto value = Value::create(unsignedShort);
  value->read("200");
  Nikon3MakerNote::printFocalLd4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printFStops
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFStops_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFStops(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFStops_NonZero_475) {
  auto value = Value::create(unsignedByte);
  value->read("12");
  Nikon3MakerNote::printFStops(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printExitPupilPosition
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintExitPupilPosition_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExitPupilPosition(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0002
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0002_SingleValue_475) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  Nikon3MakerNote::print0x0002(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, Print0x0002_ReturnsOstream_475) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  std::ostream& ret = Nikon3MakerNote::print0x0002(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for print0x0007
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0007_ReturnsOstream_475) {
  auto value = Value::create(asciiString);
  value->read("AF-S");
  std::ostream& ret = Nikon3MakerNote::print0x0007(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for print0x0083
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0083_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::print0x0083(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, Print0x0083_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  std::ostream& ret = Nikon3MakerNote::print0x0083(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for print0x0084
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0084_FourRationals_475) {
  auto value = Value::create(unsignedRational);
  value->read("18/1 200/1 35/10 56/10");
  Nikon3MakerNote::print0x0084(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, Print0x0084_SingleValue_475) {
  auto value = Value::create(unsignedRational);
  value->read("50/1");
  Nikon3MakerNote::print0x0084(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0085
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0085_ReturnsOstream_475) {
  auto value = Value::create(unsignedRational);
  value->read("5/1");
  std::ostream& ret = Nikon3MakerNote::print0x0085(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for print0x0086
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0086_ReturnsOstream_475) {
  auto value = Value::create(unsignedRational);
  value->read("10/1");
  std::ostream& ret = Nikon3MakerNote::print0x0086(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for print0x0088
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0088_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::print0x0088(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0089
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x0089_WithNullMetadata_475) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::print0x0089(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, Print0x0089_WithMetadata_475) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  ExifData exifData;
  Nikon3MakerNote::print0x0089(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x008b
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x008b_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0 0 0 0");
  std::ostream& ret = Nikon3MakerNote::print0x008b(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printFlashFocalLength
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFlashFocalLength_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFlashFocalLength_NonZero_475) {
  auto value = Value::create(unsignedByte);
  value->read("24");
  Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printRepeatingFlashRate
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintRepeatingFlashRate_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printRepeatingFlashCount
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintRepeatingFlashCount_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printIiIso
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintIiIso_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printIiIso(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printTimeZone
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintTimeZone_ReturnsOstream_475) {
  auto value = Value::create(signedShort);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_475, PrintTimeZone_PositiveOffset_475) {
  auto value = Value::create(signedShort);
  value->read("60");
  Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintTimeZone_NegativeOffset_475) {
  auto value = Value::create(signedShort);
  value->read("-300");
  Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printPictureControl
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintPictureControl_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printPictureControl(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for print0x009a
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x009a_TwoRationals_475) {
  auto value = Value::create(unsignedRational);
  value->read("4000/1000 4000/1000");
  Nikon3MakerNote::print0x009a(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, Print0x009a_ReturnsOstream_475) {
  auto value = Value::create(unsignedRational);
  value->read("6000/1000 4000/1000");
  std::ostream& ret = Nikon3MakerNote::print0x009a(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for print0x009e
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, Print0x009e_ReturnsOstream_475) {
  auto value = Value::create(unsignedShort);
  value->read("0 0 0 0 0 0 0 0 0 0");
  std::ostream& ret = Nikon3MakerNote::print0x009e(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printCameraExposureCompensation
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintCameraExposureCompensation_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintCameraExposureCompensation_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  std::ostream& ret = Nikon3MakerNote::printCameraExposureCompensation(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printFlashZoomHeadPosition
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFlashZoomHeadPosition_Zero_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printLensId with explicit group parameter
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintLensId_NikonLd4Group_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  Nikon3MakerNote::printLensId(os, *value, &exifData, "NikonLd4");
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintLensId_NikonLd1Group_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  Nikon3MakerNote::printLensId(os, *value, &exifData, "NikonLd1");
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintLensId_NullMetadata_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd4");
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printAfPointsInFocus
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintAfPointsInFocus_WithNullMetadata_475) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintAfPointsInFocus_ReturnsOstream_475) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  std::ostream& ret = Nikon3MakerNote::printAfPointsInFocus(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printAf2AreaMode
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintAf2AreaMode_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printExternalFlashData2
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintExternalFlashData2_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printExternalFlashData3
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintExternalFlashData3_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printExternalFlashData4
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintExternalFlashData4_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for various flash group data printers
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupAControlData_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupBCControlData_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printExternalFlashData1Fl6
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintExternalFlashData1Fl6_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printExternalFlashData1Fl7
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintExternalFlashData1Fl7_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printExternalFlashData2Fl6
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintExternalFlashData2Fl6_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printFlashMasterDataFl6
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFlashMasterDataFl6_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashMasterDataFl6(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for printFlashMasterDataFl7
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFlashMasterDataFl7_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashMasterDataFl7(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Tests for flash group data (Fl6 and Fl7 variants)
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupADataFl6_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupADataFl6(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupADataFl7_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupADataFl7(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupBDataFl6_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupBDataFl7_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupCDataFl6_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_475, PrintFlashGroupCDataFl7_ReturnsOstream_475) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Boundary: Large value tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_475, PrintFocusDistance_MaxByte_475) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintAperture_MaxByte_475) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFocal_MaxByte_475) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_475, PrintFStops_MaxByte_475) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFStops(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
