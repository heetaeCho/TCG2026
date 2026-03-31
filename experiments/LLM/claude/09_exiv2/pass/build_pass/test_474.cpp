#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_474 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ---------------------------------------------------------------------------
// printLensId3 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintLensId3_WithNullMetadata_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId3(os, *value, nullptr);
  // Should produce some output (either from config file or printLensId fallback)
  // We just verify no crash and stream is returned properly
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId3_WithEmptyExifData_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  Nikon3MakerNote::printLensId3(os, *value, &exifData);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId3_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId3(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printLensId1 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintLensId1_WithNullMetadata_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId1(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId1_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId1(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printLensId2 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintLensId2_WithNullMetadata_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId2(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId2_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printLensId4 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintLensId4_WithNullMetadata_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printLensId4(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId4_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printFocusDistance tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFocusDistance_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintFocusDistance_NonZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintFocusDistance_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printAperture tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintAperture_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintAperture_NonZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintAperture_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("25");
  std::ostream& result = Nikon3MakerNote::printAperture(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printFocal tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFocal_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintFocal_NonZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("100");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintFocal_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  std::ostream& result = Nikon3MakerNote::printFocal(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printFStops tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFStops_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFStops(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintFStops_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  std::ostream& result = Nikon3MakerNote::printFStops(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printExitPupilPosition tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintExitPupilPosition_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExitPupilPosition(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintExitPupilPosition_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("5");
  std::ostream& result = Nikon3MakerNote::printExitPupilPosition(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0002 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0002_SingleValue_474) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::print0x0002(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, Print0x0002_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("256");
  std::ostream& result = Nikon3MakerNote::print0x0002(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0007 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0007_ReturnsOstream_474) {
  auto value = Value::create(asciiString);
  value->read("AF-S");
  std::ostream& result = Nikon3MakerNote::print0x0007(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0083 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0083_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::print0x0083(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, Print0x0083_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  std::ostream& result = Nikon3MakerNote::print0x0083(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0084 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0084_WithRationalValues_474) {
  auto value = Value::create(unsignedRational);
  value->read("18/1 200/1 35/10 56/10");
  Nikon3MakerNote::print0x0084(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, Print0x0084_ReturnsOstream_474) {
  auto value = Value::create(unsignedRational);
  value->read("50/1 50/1 14/10 14/10");
  std::ostream& result = Nikon3MakerNote::print0x0084(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0085 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0085_ReturnsOstream_474) {
  auto value = Value::create(unsignedRational);
  value->read("100/1");
  std::ostream& result = Nikon3MakerNote::print0x0085(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0086 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0086_ReturnsOstream_474) {
  auto value = Value::create(unsignedRational);
  value->read("10/1");
  std::ostream& result = Nikon3MakerNote::print0x0086(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0088 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0088_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::print0x0088(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, Print0x0088_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::print0x0088(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x0089 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x0089_ZeroValue_474) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::print0x0089(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, Print0x0089_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  std::ostream& result = Nikon3MakerNote::print0x0089(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x008b tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x008b_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0 0 0 0");
  std::ostream& result = Nikon3MakerNote::print0x008b(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printIiIso tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintIiIso_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  std::ostream& result = Nikon3MakerNote::printIiIso(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printFlashFocalLength tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFlashFocalLength_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashFocalLength_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("24");
  std::ostream& result = Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printRepeatingFlashRate tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintRepeatingFlashRate_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintRepeatingFlashRate_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashRate(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printRepeatingFlashCount tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintRepeatingFlashCount_ZeroValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintRepeatingFlashCount_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("5");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashCount(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printTimeZone tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintTimeZone_ReturnsOstream_474) {
  auto value = Value::create(signedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintTimeZone_PositiveOffset_474) {
  auto value = Value::create(signedShort);
  value->read("60");
  Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, PrintTimeZone_NegativeOffset_474) {
  auto value = Value::create(signedShort);
  value->read("-300");
  Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

// ---------------------------------------------------------------------------
// printPictureControl tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintPictureControl_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printPictureControl(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x009a tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x009a_ReturnsOstream_474) {
  auto value = Value::create(unsignedRational);
  value->read("2500/1000 1663/1000");
  std::ostream& result = Nikon3MakerNote::print0x009a(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// print0x009e tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, Print0x009e_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("0 0 0 0 0 0 0 0 0 0");
  std::ostream& result = Nikon3MakerNote::print0x009e(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printApertureLd4 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintApertureLd4_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printApertureLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printFocalLd4 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFocalLd4_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFocalLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printFocusDistanceLd4 tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFocusDistanceLd4_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFocusDistanceLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printCameraExposureCompensation tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintCameraExposureCompensation_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printCameraExposureCompensation(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintCameraExposureCompensation_NonZero_474) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, *value, nullptr);
  EXPECT_TRUE(os.good());
}

// ---------------------------------------------------------------------------
// printFlashZoomHeadPosition tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFlashZoomHeadPosition_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printLensId with explicit group tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintLensId_WithNikonLd3Group_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd3");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId_WithNikonLd1Group_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId_WithEmptyGroup_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "");
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printAfPointsInFocus tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintAfPointsInFocus_ReturnsOstream_474) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printAfPointsInFocus(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// printAf2AreaMode tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintAf2AreaMode_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// Multiple value sizes - boundary tests
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFocusDistance_MaxByteValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintAperture_MaxByteValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printAperture(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_474, PrintFocal_MaxByteValue_474) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printFocal(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ---------------------------------------------------------------------------
// printLensId3 with ExifData containing some metadata
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintLensId3_WithExifDataContainingKeys_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  // Add some generic exif data
  exifData["Exif.Photo.FocalLength"] = "50/1";
  Nikon3MakerNote::printLensId3(os, *value, &exifData);
  EXPECT_TRUE(os.good());
}

TEST_F(Nikon3MakerNoteTest_474, PrintLensId1_WithExifDataContainingKeys_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  exifData["Exif.Photo.FocalLength"] = "50/1";
  Nikon3MakerNote::printLensId1(os, *value, &exifData);
  EXPECT_TRUE(os.good());
}

// ---------------------------------------------------------------------------
// External flash data functions
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintExternalFlashData1Fl6_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintExternalFlashData1Fl7_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintExternalFlashData2Fl6_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintExternalFlashData2_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintExternalFlashData3_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintExternalFlashData4_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// Flash master data functions
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFlashMasterDataFl6_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashMasterDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashMasterDataFl7_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashMasterDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// Flash group control data functions
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupAControlData_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupBCControlData_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ---------------------------------------------------------------------------
// Flash group data functions
// ---------------------------------------------------------------------------

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupADataFl6_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupADataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupADataFl7_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupADataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupBDataFl6_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupBDataFl7_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupCDataFl6_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_474, PrintFlashGroupCDataFl7_ReturnsOstream_474) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}
