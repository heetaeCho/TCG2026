#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_472 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// ===========================================================================
// printLensId1 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintLensId1_WithNullMetadata_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId1(os, *value, nullptr);
  // Should return the same stream reference
  EXPECT_EQ(&result, &os);
  // Output should not be empty (either config file result or printLensId result)
  // We just verify it doesn't crash and returns valid stream
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId2_WithNullMetadata_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId3_WithNullMetadata_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId3(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId4_WithNullMetadata_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printFocusDistance tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFocusDistance_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_472, PrintFocusDistance_NonZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("100");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ===========================================================================
// printAperture tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintAperture_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printAperture(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_472, PrintAperture_NonZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printAperture(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ===========================================================================
// printFocal tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFocal_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocal(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFocal_NonZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("200");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocal(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printFStops tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFStops_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFStops(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFStops_NonZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("72");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFStops(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printExitPupilPosition tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintExitPupilPosition_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x0002 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0002_SingleValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0002(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, Print0x0002_ValueOf100_472) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0002(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x0007 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0007_StringValue_472) {
  auto value = Value::create(asciiString);
  value->read("AF-S");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0007(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x0083 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0083_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0083(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_472, Print0x0083_NonZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0083(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// print0x0084 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0084_FourRationals_472) {
  auto value = Value::create(unsignedRational);
  value->read("18/1 200/1 35/10 56/10");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0084(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_472, Print0x0084_SingleRational_472) {
  auto value = Value::create(unsignedRational);
  value->read("50/1");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0084(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x0085 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0085_ZeroValue_472) {
  auto value = Value::create(unsignedRational);
  value->read("0/1");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0085(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x0086 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0086_ZeroValue_472) {
  auto value = Value::create(unsignedRational);
  value->read("0/1");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0086(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x0088 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0088_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0088(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x0089 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x0089_ZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0089(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_472, Print0x0089_WithMetadata_472) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x0089(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x008b tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x008b_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x008b(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printIiIso tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintIiIso_ZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printIiIso(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintIiIso_NonZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("100");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printIiIso(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printFlashFocalLength tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFlashFocalLength_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashFocalLength_NonZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("24");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printRepeatingFlashRate tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintRepeatingFlashRate_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printRepeatingFlashCount tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintRepeatingFlashCount_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printTimeZone tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintTimeZone_ZeroValue_472) {
  auto value = Value::create(signedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_472, PrintTimeZone_PositiveValue_472) {
  auto value = Value::create(signedShort);
  value->read("60");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_472, PrintTimeZone_NegativeValue_472) {
  auto value = Value::create(signedShort);
  value->read("-300");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printTimeZone(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printPictureControl tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintPictureControl_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printPictureControl(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// print0x009a tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x009a_TwoRationals_472) {
  auto value = Value::create(unsignedRational);
  value->read("2872/1000 2872/1000");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x009a(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// print0x009e tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, Print0x009e_MultipleValues_472) {
  auto value = Value::create(unsignedShort);
  value->read("0 0 0 0 0 0 0 0 0 0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::print0x009e(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printApertureLd4 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintApertureLd4_ZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printApertureLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintApertureLd4_NonZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("500");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printApertureLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printFocalLd4 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFocalLd4_ZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocalLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFocalLd4_NonZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("500");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocalLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printFocusDistanceLd4 tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFocusDistanceLd4_ZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFocusDistanceLd4_NonZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("1000");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printCameraExposureCompensation tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintCameraExposureCompensation_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printFlashZoomHeadPosition tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFlashZoomHeadPosition_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printLensId with ExifData tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintLensId1_WithEmptyExifData_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId1(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId2_WithEmptyExifData_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId2(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId3_WithEmptyExifData_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId3(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId4_WithEmptyExifData_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId4(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printLensId generic tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintLensId_NullMetadata_NikonLd1_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId_NullMetadata_NikonLd2_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd2");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId_NullMetadata_NikonLd3_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd3");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId_NullMetadata_NikonLd4_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "NikonLd4");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId_EmptyExifData_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId(os, *value, &exifData, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printAfPointsInFocus tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintAfPointsInFocus_WithNullMetadata_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintAfPointsInFocus_WithEmptyMetadata_472) {
  auto value = Value::create(unsignedShort);
  value->read("1");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printAf2AreaMode tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintAf2AreaMode_ZeroValue_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintAf2AreaMode_WithMetadata_472) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  ExifData exifData;
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, *value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// Stream returns reference consistency
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, AllPrintFunctions_ReturnSameStreamRef_472) {
  auto byteVal = Value::create(unsignedByte);
  byteVal->read("0");
  auto shortVal = Value::create(unsignedShort);
  shortVal->read("0");
  auto rationalVal = Value::create(unsignedRational);
  rationalVal->read("0/1");

  std::ostringstream os;

  EXPECT_EQ(&Nikon3MakerNote::printFocusDistance(os, *byteVal, nullptr), &os);
  os.str("");
  EXPECT_EQ(&Nikon3MakerNote::printAperture(os, *byteVal, nullptr), &os);
  os.str("");
  EXPECT_EQ(&Nikon3MakerNote::printFocal(os, *byteVal, nullptr), &os);
  os.str("");
  EXPECT_EQ(&Nikon3MakerNote::printFStops(os, *byteVal, nullptr), &os);
  os.str("");
  EXPECT_EQ(&Nikon3MakerNote::printExitPupilPosition(os, *byteVal, nullptr), &os);
  os.str("");
  EXPECT_EQ(&Nikon3MakerNote::printFlashFocalLength(os, *byteVal, nullptr), &os);
  os.str("");
  EXPECT_EQ(&Nikon3MakerNote::printRepeatingFlashRate(os, *byteVal, nullptr), &os);
  os.str("");
  EXPECT_EQ(&Nikon3MakerNote::printRepeatingFlashCount(os, *byteVal, nullptr), &os);
}

// ===========================================================================
// printLensId with various byte values
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintLensId1_MaxByteValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId1(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintLensId2_MaxByteValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printLensId2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printExternalFlashData tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintExternalFlashData1Fl6_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintExternalFlashData1Fl7_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintExternalFlashData2Fl6_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintExternalFlashData2_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintExternalFlashData3_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintExternalFlashData4_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printFlashMasterData tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFlashMasterDataFl6_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashMasterDataFl7_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// printFlashGroup tests
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupAControlData_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupBCControlData_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupADataFl6_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupADataFl7_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupBDataFl6_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupBDataFl7_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupCDataFl6_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_472, PrintFlashGroupCDataFl7_ZeroValue_472) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ===========================================================================
// Boundary: printFocusDistance with max byte value
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFocusDistance_MaxByte_472) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocusDistance(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// Boundary: printAperture with max byte value
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintAperture_MaxByte_472) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printAperture(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// Boundary: printFocal with max byte value
// ===========================================================================

TEST_F(Nikon3MakerNoteTest_472, PrintFocal_MaxByte_472) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  std::ostringstream os;
  auto& result = Nikon3MakerNote::printFocal(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}
