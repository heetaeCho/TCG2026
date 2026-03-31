#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_275 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// ==================== tagList functions ====================

TEST_F(SonyMakerNoteTest_275, TagList2010eReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagList2010e();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListCsReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListCs2ReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagListCs2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListFpReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagListFp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListSonyMisc1ReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagListSonyMisc1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListSonyMisc2bReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagListSonyMisc2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListSonyMisc3cReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagListSonyMisc3c();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_275, TagListSonySInfo1ReturnsNonNull_275) {
  auto tagList = SonyMakerNote::tagListSonySInfo1();
  ASSERT_NE(tagList, nullptr);
}

// ==================== printWhiteBalanceFineTune ====================

TEST_F(SonyMakerNoteTest_275, PrintWhiteBalanceFineTuneNormal_275) {
  ULongValue value;
  value.read("10");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_275, PrintWhiteBalanceFineTuneZero_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printMultiBurstMode ====================

TEST_F(SonyMakerNoteTest_275, PrintMultiBurstModeNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printMultiBurstSize ====================

TEST_F(SonyMakerNoteTest_275, PrintMultiBurstSizeNormal_275) {
  ULongValue value;
  value.read("1");
  auto& result = SonyMakerNote::printMultiBurstSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printAutoHDRStd ====================

TEST_F(SonyMakerNoteTest_275, PrintAutoHDRStdNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAutoHDRStd(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printWBShiftABGM ====================

TEST_F(SonyMakerNoteTest_275, PrintWBShiftABGMNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWBShiftABGM(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printFocusMode2 ====================

TEST_F(SonyMakerNoteTest_275, PrintFocusMode2Normal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printAFAreaModeSetting ====================

TEST_F(SonyMakerNoteTest_275, PrintAFAreaModeSettingNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFAreaModeSetting(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printFlexibleSpotPosition ====================

TEST_F(SonyMakerNoteTest_275, PrintFlexibleSpotPositionNormal_275) {
  UShortValue value;
  value.read("100 200");
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printAFPointSelected ====================

TEST_F(SonyMakerNoteTest_275, PrintAFPointSelectedNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFPointSelected(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printAFPointsUsed ====================

TEST_F(SonyMakerNoteTest_275, PrintAFPointsUsedNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFPointsUsed(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printAFTracking ====================

TEST_F(SonyMakerNoteTest_275, PrintAFTrackingNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFTracking(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printFocalPlaneAFPointsUsed ====================

TEST_F(SonyMakerNoteTest_275, PrintFocalPlaneAFPointsUsedNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocalPlaneAFPointsUsed(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printWBShiftABGMPrecise ====================

TEST_F(SonyMakerNoteTest_275, PrintWBShiftABGMPreciseNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printExposureStandardAdjustment ====================

TEST_F(SonyMakerNoteTest_275, PrintExposureStandardAdjustmentNormal_275) {
  UShortValue value;
  value.read("100");
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printPixelShiftInfo ====================

TEST_F(SonyMakerNoteTest_275, PrintPixelShiftInfoNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printPixelShiftInfo(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printFocusFrameSize ====================

TEST_F(SonyMakerNoteTest_275, PrintFocusFrameSizeNormal_275) {
  UShortValue value;
  value.read("100 200");
  auto& result = SonyMakerNote::printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printColorTemperature ====================

TEST_F(SonyMakerNoteTest_275, PrintColorTemperatureNormal_275) {
  ULongValue value;
  value.read("5500");
  auto& result = SonyMakerNote::printColorTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_275, PrintColorTemperatureZero_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printColorCompensationFilter ====================

TEST_F(SonyMakerNoteTest_275, PrintColorCompensationFilterNormal_275) {
  ULongValue value;
  value.read("128");
  auto& result = SonyMakerNote::printColorCompensationFilter(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printLensSpec ====================

TEST_F(SonyMakerNoteTest_275, PrintLensSpecNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printLensSpec(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printImageSize ====================

TEST_F(SonyMakerNoteTest_275, PrintImageSizeNormal_275) {
  ULongValue value;
  value.read("1");
  auto& result = SonyMakerNote::printImageSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printFocusMode ====================

TEST_F(SonyMakerNoteTest_275, PrintFocusModeNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printAFMode ====================

TEST_F(SonyMakerNoteTest_275, PrintAFModeNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printFocusMode3 ====================

TEST_F(SonyMakerNoteTest_275, PrintFocusMode3Normal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode3(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printHighISONoiseReduction2 ====================

TEST_F(SonyMakerNoteTest_275, PrintHighISONoiseReduction2Normal_275) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printSonyMisc1CameraTemperature ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc1CameraTemperatureNormal_275) {
  ULongValue value;
  value.read("50");
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSony2FpFocusMode ====================

TEST_F(SonyMakerNoteTest_275, PrintSony2FpFocusModeNormal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ==================== printSony2FpFocusPosition2 ====================

TEST_F(SonyMakerNoteTest_275, PrintSony2FpFocusPosition2Normal_275) {
  ULongValue value;
  value.read("100");
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSony2FpAmbientTemperature ====================

TEST_F(SonyMakerNoteTest_275, PrintSony2FpAmbientTemperatureNormal_275) {
  ULongValue value;
  value.read("50");
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSonyMisc2bLensZoomPosition ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc2bLensZoomPositionNormal_275) {
  ULongValue value;
  value.read("50");
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSonyMisc2bFocusPosition2 ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc2bFocusPosition2Normal_275) {
  ULongValue value;
  value.read("100");
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSonyMisc3cShotNumberSincePowerUp ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cShotNumberSincePowerUpNormal_275) {
  ULongValue value;
  value.read("42");
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSonyMisc3cSequenceNumber ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cSequenceNumberNormal_275) {
  ULongValue value;
  value.read("1");
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSonyMisc3cSonyImageHeight ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cSonyImageHeightNormal_275) {
  ULongValue value;
  value.read("1080");
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSonyMisc3cModelReleaseYear ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cModelReleaseYearNormal_275) {
  ULongValue value;
  value.read("2020");
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== printSonyMisc3cQuality2 ====================

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cQuality2Normal_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== Return reference consistency tests ====================

TEST_F(SonyMakerNoteTest_275, PrintFunctionsReturnSameStream_275) {
  ULongValue value;
  value.read("0");

  std::ostringstream os1, os2, os3;
  EXPECT_EQ(&SonyMakerNote::printWhiteBalanceFineTune(os1, value, nullptr), &os1);
  EXPECT_EQ(&SonyMakerNote::printMultiBurstMode(os2, value, nullptr), &os2);
  EXPECT_EQ(&SonyMakerNote::printMultiBurstSize(os3, value, nullptr), &os3);
}

// ==================== Boundary: large values ====================

TEST_F(SonyMakerNoteTest_275, PrintColorTemperatureLargeValue_275) {
  ULongValue value;
  value.read("65535");
  auto& result = SonyMakerNote::printColorTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintWhiteBalanceFineTuneLargeValue_275) {
  ULongValue value;
  value.read("255");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ==================== Boundary: with ExifData ====================

TEST_F(SonyMakerNoteTest_275, PrintAutoHDRStdWithExifData_275) {
  ExifData exifData;
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAutoHDRStd(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintFocusMode2WithExifData_275) {
  ExifData exifData;
  ULongValue value;
  value.read("2");
  auto& result = SonyMakerNote::printFocusMode2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintHighISONoiseReduction2WithExifData_275) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

// ==================== Boundary: with nullptr metadata ====================

TEST_F(SonyMakerNoteTest_275, PrintSony2FpFocusPosition2NullMetadata_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc2bLensZoomPositionNullMetadata_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc2bFocusPosition2NullMetadata_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cSonyImageHeightNullMetadata_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cModelReleaseYearNullMetadata_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cQuality2NullMetadata_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_275, PrintSonyMisc1CameraTemperatureNullMetadata_275) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}
