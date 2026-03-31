#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "sonymn_int.hpp"
#include "value.hpp"
#include "exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_273 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tag list accessor tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, TagListNotNull_273) {
  auto tagList = SonyMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagListCsNotNull_273) {
  auto tagList = SonyMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagListCs2NotNull_273) {
  auto tagList = SonyMakerNote::tagListCs2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagListFpNotNull_273) {
  auto tagList = SonyMakerNote::tagListFp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagListSonyMisc1NotNull_273) {
  auto tagList = SonyMakerNote::tagListSonyMisc1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagListSonyMisc2bNotNull_273) {
  auto tagList = SonyMakerNote::tagListSonyMisc2b();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagListSonyMisc3cNotNull_273) {
  auto tagList = SonyMakerNote::tagListSonyMisc3c();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagListSonySInfo1NotNull_273) {
  auto tagList = SonyMakerNote::tagListSonySInfo1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_273, TagList2010eNotNull_273) {
  auto tagList = SonyMakerNote::tagList2010e();
  EXPECT_NE(tagList, nullptr);
}

// =============================================================================
// printWhiteBalanceFineTune tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintWhiteBalanceFineTune_SingleValue_273) {
  ULongValue value;
  value.read("10");
  SonyMakerNote::printWhiteBalanceFineTune(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintWhiteBalanceFineTune_ZeroValue_273) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printWhiteBalanceFineTune(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printMultiBurstMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintMultiBurstMode_ZeroValue_273) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintMultiBurstMode_NonZeroValue_273) {
  ULongValue value;
  value.read("1");
  SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printMultiBurstSize tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintMultiBurstSize_ValidValue_273) {
  ULongValue value;
  value.read("1");
  SonyMakerNote::printMultiBurstSize(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printAutoHDRStd tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintAutoHDRStd_ValidValue_273) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printAutoHDRStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printWBShiftABGM tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintWBShiftABGM_TwoValues_273) {
  LongValue value;
  value.read("0 0");
  SonyMakerNote::printWBShiftABGM(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printFocusMode2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintFocusMode2_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocusMode2(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printAFAreaModeSetting tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintAFAreaModeSetting_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFAreaModeSetting(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printFlexibleSpotPosition tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintFlexibleSpotPosition_TwoValues_273) {
  UShortValue value;
  value.read("100 200");
  SonyMakerNote::printFlexibleSpotPosition(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printAFPointSelected tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintAFPointSelected_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFPointSelected(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printAFTracking tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintAFTracking_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFTracking(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printFocalPlaneAFPointsUsed tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintFocalPlaneAFPointsUsed_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocalPlaneAFPointsUsed(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printWBShiftABGMPrecise tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintWBShiftABGMPrecise_ValidValue_273) {
  LongValue value;
  value.read("0 0");
  SonyMakerNote::printWBShiftABGMPrecise(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printExposureStandardAdjustment tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintExposureStandardAdjustment_ValidValue_273) {
  ShortValue value;
  value.read("0");
  SonyMakerNote::printExposureStandardAdjustment(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printPixelShiftInfo tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintPixelShiftInfo_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printPixelShiftInfo(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printFocusFrameSize tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintFocusFrameSize_ValidValue_273) {
  UShortValue value;
  value.read("100 200");
  SonyMakerNote::printFocusFrameSize(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printColorTemperature tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintColorTemperature_ValidValue_273) {
  ULongValue value;
  value.read("5500");
  SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintColorTemperature_ZeroValue_273) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printColorCompensationFilter tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintColorCompensationFilter_ValidValue_273) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printColorCompensationFilter(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printLensSpec tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintLensSpec_ValidValues_273) {
  UCharValue value;
  value.read("0 0 0 0 0 0 0 0");
  SonyMakerNote::printLensSpec(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printImageSize tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintImageSize_ValidValue_273) {
  UShortValue value;
  value.read("1");
  SonyMakerNote::printImageSize(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printFocusMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintFocusMode_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocusMode(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printAFMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintAFMode_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFMode(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printFocusMode3 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintFocusMode3_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocusMode3(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printHighISONoiseReduction2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintHighISONoiseReduction2_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printHighISONoiseReduction2(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc1CameraTemperature tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc1CameraTemperature_ValidValue_273) {
  UShortValue value;
  value.read("50");
  SonyMakerNote::printSonyMisc1CameraTemperature(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSony2FpFocusMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSony2FpFocusMode_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSony2FpFocusMode(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSony2FpFocusPosition2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSony2FpFocusPosition2_ValidValue_273) {
  UShortValue value;
  value.read("100");
  SonyMakerNote::printSony2FpFocusPosition2(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSony2FpAmbientTemperature tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSony2FpAmbientTemperature_ValidValue_273) {
  UShortValue value;
  value.read("50");
  SonyMakerNote::printSony2FpAmbientTemperature(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc2bLensZoomPosition tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc2bLensZoomPosition_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc2bFocusPosition2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc2bFocusPosition2_ValidValue_273) {
  UShortValue value;
  value.read("100");
  SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc3cShotNumberSincePowerUp tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cShotNumberSincePowerUp_ValidValue_273) {
  ULongValue value;
  value.read("42");
  SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc3cSequenceNumber tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cSequenceNumber_ValidValue_273) {
  ULongValue value;
  value.read("1");
  SonyMakerNote::printSonyMisc3cSequenceNumber(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cSequenceNumber_ZeroValue_273) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc3cSequenceNumber(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc3cSonyImageHeight tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cSonyImageHeight_ValidValue_273) {
  UShortValue value;
  value.read("1080");
  SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc3cModelReleaseYear tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cModelReleaseYear_ValidValue_273) {
  UShortValue value;
  value.read("2020");
  SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// printSonyMisc3cQuality2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cQuality2_ValidValue_273) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc3cQuality2(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// Return value tests (stream reference)
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintWhiteBalanceFineTune_ReturnsOstream_273) {
  ULongValue value;
  value.read("5");
  std::ostream& result = SonyMakerNote::printWhiteBalanceFineTune(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_273, PrintMultiBurstMode_ReturnsOstream_273) {
  ULongValue value;
  value.read("0");
  std::ostream& result = SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_273, PrintColorTemperature_ReturnsOstream_273) {
  ULongValue value;
  value.read("6500");
  std::ostream& result = SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_273, PrintLensSpec_ReturnsOstream_273) {
  UCharValue value;
  value.read("0 0 0 0 0 0 0 0");
  std::ostream& result = SonyMakerNote::printLensSpec(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cShotNumberSincePowerUp_ReturnsOstream_273) {
  ULongValue value;
  value.read("100");
  std::ostream& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Test with ExifData parameter
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintAutoHDRStd_WithExifData_273) {
  ExifData exifData;
  ULongValue value;
  value.read("0");
  SonyMakerNote::printAutoHDRStd(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintFocusMode2_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("2");
  SonyMakerNote::printFocusMode2(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintAFAreaModeSetting_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  SonyMakerNote::printAFAreaModeSetting(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSony2FpFocusPosition2_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("50");
  SonyMakerNote::printSony2FpFocusPosition2(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc2bLensZoomPosition_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("128");
  SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc2bFocusPosition2_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("200");
  SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cSonyImageHeight_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("4000");
  SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cModelReleaseYear_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("2022");
  SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cQuality2_WithExifData_273) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  SonyMakerNote::printSonyMisc3cQuality2(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// Boundary tests
// =============================================================================

TEST_F(SonyMakerNoteTest_273, PrintColorTemperature_MaxValue_273) {
  ULongValue value;
  value.read("65535");
  SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintMultiBurstSize_LargeValue_273) {
  ULongValue value;
  value.read("255");
  SonyMakerNote::printMultiBurstSize(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cShotNumberSincePowerUp_LargeValue_273) {
  ULongValue value;
  value.read("999999");
  SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSony2FpAmbientTemperature_HighTemp_273) {
  UShortValue value;
  value.read("255");
  SonyMakerNote::printSony2FpAmbientTemperature(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_273, PrintSonyMisc1CameraTemperature_HighTemp_273) {
  UShortValue value;
  value.read("255");
  SonyMakerNote::printSonyMisc1CameraTemperature(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
