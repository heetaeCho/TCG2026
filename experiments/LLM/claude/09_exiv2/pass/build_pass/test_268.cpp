#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "sonymn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_268 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tag list accessor tests
// ============================================================

TEST_F(SonyMakerNoteTest_268, TagListCsReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagListReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagListCs2ReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagListCs2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagListFpReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagListFp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagListSonyMisc1ReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagListSonyMisc1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagListSonyMisc2bReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagListSonyMisc2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagListSonyMisc3cReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagListSonyMisc3c();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagListSonySInfo1ReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagListSonySInfo1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_268, TagList2010eReturnsNonNull_268) {
  auto tagList = SonyMakerNote::tagList2010e();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests — normal operation with valid values
// ============================================================

TEST_F(SonyMakerNoteTest_268, PrintWhiteBalanceFineTune_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // The function should have written something to the stream
  // We don't check the exact content since we treat implementation as black box
}

TEST_F(SonyMakerNoteTest_268, PrintMultiBurstMode_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintMultiBurstSize_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAutoHDRStd_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAutoHDRStd(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintWBShiftABGM_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWBShiftABGM(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocusMode2_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFAreaModeSetting_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFAreaModeSetting(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFlexibleSpotPosition_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFPointSelected_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFPointSelected(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFPointsUsed_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFPointsUsed(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFTracking_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFTracking(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocalPlaneAFPointsUsed_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocalPlaneAFPointsUsed(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintWBShiftABGMPrecise_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintExposureStandardAdjustment_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintPixelShiftInfo_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printPixelShiftInfo(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocusFrameSize_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusFrameSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintColorTemperature_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintColorCompensationFilter_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorCompensationFilter(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintLensSpec_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printLensSpec(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintImageSize_NormalValue_268) {
  UShortValue value;
  value.read("1");
  auto& result = SonyMakerNote::printImageSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocusMode_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFMode_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFMode(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocusMode3_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode3(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintHighISONoiseReduction2_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc1CameraTemperature_NormalValue_268) {
  UShortValue value;
  value.read("100");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSony2FpFocusMode_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSony2FpFocusPosition2_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSony2FpAmbientTemperature_NormalValue_268) {
  UShortValue value;
  value.read("100");
  ExifData exifData;
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc2bLensZoomPosition_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc2bFocusPosition2_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cShotNumberSincePowerUp_NormalValue_268) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cSequenceNumber_NormalValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cSonyImageHeight_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cModelReleaseYear_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cQuality2_NormalValue_268) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary / edge case tests
// ============================================================

TEST_F(SonyMakerNoteTest_268, PrintWhiteBalanceFineTune_NullMetadata_268) {
  UShortValue value;
  value.read("255");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_268, PrintMultiBurstMode_NullMetadata_268) {
  UShortValue value;
  value.read("1");
  auto& result = SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintMultiBurstSize_LargeValue_268) {
  UShortValue value;
  value.read("65535");
  auto& result = SonyMakerNote::printMultiBurstSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_268, PrintColorTemperature_ZeroValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintColorCompensationFilter_ZeroValue_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorCompensationFilter(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocusMode_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFMode_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocusMode2_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFocusMode3_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintHighISONoiseReduction2_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAutoHDRStd_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAutoHDRStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc1CameraTemperature_NullMetadata_268) {
  UShortValue value;
  value.read("100");
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSony2FpAmbientTemperature_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSony2FpFocusPosition2_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc2bLensZoomPosition_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc2bFocusPosition2_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cShotNumberSincePowerUp_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cSonyImageHeight_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cModelReleaseYear_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cQuality2_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Return value / stream chaining tests
// ============================================================

TEST_F(SonyMakerNoteTest_268, PrintFunctionsReturnSameStream_268) {
  UShortValue value;
  value.read("0");

  std::ostringstream os1, os2, os3;
  auto& r1 = SonyMakerNote::printWhiteBalanceFineTune(os1, value, nullptr);
  auto& r2 = SonyMakerNote::printMultiBurstMode(os2, value, nullptr);
  auto& r3 = SonyMakerNote::printMultiBurstSize(os3, value, nullptr);

  EXPECT_EQ(&r1, &os1);
  EXPECT_EQ(&r2, &os2);
  EXPECT_EQ(&r3, &os3);
}

TEST_F(SonyMakerNoteTest_268, PrintLensSpec_WritesToStream_268) {
  // LensSpec typically expects 8 bytes but we test with a simple value
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printLensSpec(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Stream should have some content (even if it's an error/fallback string)
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_268, PrintImageSize_WritesToStream_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printImageSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests with different value types
// ============================================================

TEST_F(SonyMakerNoteTest_268, PrintExposureStandardAdjustment_WithValue_268) {
  UShortValue value;
  value.read("128");
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_268, PrintAFAreaModeSetting_NullMetadata_268) {
  UShortValue value;
  value.read("1");
  auto& result = SonyMakerNote::printAFAreaModeSetting(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintFlexibleSpotPosition_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFPointSelected_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFPointSelected(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFPointsUsed_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFPointsUsed(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintAFTracking_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFTracking(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSonyMisc3cSequenceNumber_NullMetadata_268) {
  UShortValue value;
  value.read("5");
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_268, PrintSony2FpFocusMode_NullMetadata_268) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}
