#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "sonymn_int.hpp"
#include "value.hpp"
#include "exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_272 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tag List Tests
// =============================================================================

TEST_F(SonyMakerNoteTest_272, TagListSonyMisc2bNotNull_272) {
  auto tagList = SonyMakerNote::tagListSonyMisc2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagListNotNull_272) {
  auto tagList = SonyMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagListCsNotNull_272) {
  auto tagList = SonyMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagListCs2NotNull_272) {
  auto tagList = SonyMakerNote::tagListCs2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagListFpNotNull_272) {
  auto tagList = SonyMakerNote::tagListFp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagListSonyMisc1NotNull_272) {
  auto tagList = SonyMakerNote::tagListSonyMisc1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagListSonyMisc3cNotNull_272) {
  auto tagList = SonyMakerNote::tagListSonyMisc3c();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagListSonySInfo1NotNull_272) {
  auto tagList = SonyMakerNote::tagListSonySInfo1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_272, TagList2010eNotNull_272) {
  auto tagList = SonyMakerNote::tagList2010e();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Print Function Tests - Normal Operation
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintWhiteBalanceFineTuneReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_272, PrintMultiBurstModeReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintMultiBurstSizeReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAutoHDRStdReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAutoHDRStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintColorTemperatureReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintColorCompensationFilterReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorCompensationFilter(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintLensSpecReturnsStream_272) {
  UShortValue value;
  value.read("0 0 0 0 0 0 0 0");
  auto& result = SonyMakerNote::printLensSpec(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintImageSizeReturnsStream_272) {
  UShortValue value;
  value.read("1");
  auto& result = SonyMakerNote::printImageSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintFocusModeReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAFModeReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintFocusMode2ReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintFocusMode3ReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintHighISONoiseReduction2ReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAFAreaModeSettingReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFAreaModeSetting(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintFlexibleSpotPositionReturnsStream_272) {
  UShortValue value;
  value.read("0 0");
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAFPointSelectedReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFPointSelected(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAFTrackingReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFTracking(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintWBShiftABGMReturnsStream_272) {
  UShortValue value;
  value.read("0 0");
  auto& result = SonyMakerNote::printWBShiftABGM(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintWBShiftABGMPreciseReturnsStream_272) {
  UShortValue value;
  value.read("0 0 0 0");
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintExposureStandardAdjustmentReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintPixelShiftInfoReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printPixelShiftInfo(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintFocusFrameSizeReturnsStream_272) {
  UShortValue value;
  value.read("0 0");
  auto& result = SonyMakerNote::printFocusFrameSize(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintFocalPlaneAFPointsUsedReturnsStream_272) {
  UShortValue value;
  value.read("0 0");
  auto& result = SonyMakerNote::printFocalPlaneAFPointsUsed(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAFPointsUsedReturnsStream_272) {
  UShortValue value;
  value.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = SonyMakerNote::printAFPointsUsed(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Sony2Fp Print Functions
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintSony2FpFocusModeReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSony2FpFocusPosition2ReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSony2FpAmbientTemperatureReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// SonyMisc1 Print Functions
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc1CameraTemperatureReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// SonyMisc2b Print Functions
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc2bLensZoomPositionReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc2bFocusPosition2ReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// SonyMisc3c Print Functions
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cShotNumberSincePowerUpReturnsStream_272) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cSequenceNumberReturnsStream_272) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cSonyImageHeightReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cModelReleaseYearReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cQuality2ReturnsStream_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary / Edge Cases
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintWhiteBalanceFineTuneWithMaxValue_272) {
  UShortValue value;
  value.read("65535");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_272, PrintColorTemperatureWithHighValue_272) {
  UShortValue value;
  value.read("10000");
  auto& result = SonyMakerNote::printColorTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_272, PrintMultiBurstModeZero_272) {
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_272, PrintMultiBurstModeOne_272) {
  UShortValue value;
  value.read("1");
  auto& result = SonyMakerNote::printMultiBurstMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_272, PrintImageSizeWithVariousValues_272) {
  for (int i = 0; i <= 5; ++i) {
    std::ostringstream localOs;
    UShortValue value;
    value.read(std::to_string(i));
    auto& result = SonyMakerNote::printImageSize(localOs, value, nullptr);
    EXPECT_EQ(&result, &localOs);
    EXPECT_FALSE(localOs.str().empty());
  }
}

TEST_F(SonyMakerNoteTest_272, PrintSony2FpAmbientTemperatureWithNullMetadata_272) {
  UShortValue value;
  value.read("128");
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc1CameraTemperatureWithNullMetadata_272) {
  UShortValue value;
  value.read("128");
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// Tests with ExifData
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintFocusMode2WithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAutoHDRStdWithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAutoHDRStd(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cQuality2WithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSony2FpFocusPosition2WithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc2bLensZoomPositionWithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc2bFocusPosition2WithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cSonyImageHeightWithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cModelReleaseYearWithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintFocusModeWithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintAFModeWithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFMode(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_272, PrintHighISONoiseReduction2WithExifData_272) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Consistency: calling same function multiple times
// =============================================================================

TEST_F(SonyMakerNoteTest_272, PrintWhiteBalanceFineTuneConsistency_272) {
  UShortValue value;
  value.read("100");

  std::ostringstream os1, os2;
  SonyMakerNote::printWhiteBalanceFineTune(os1, value, nullptr);
  SonyMakerNote::printWhiteBalanceFineTune(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(SonyMakerNoteTest_272, PrintMultiBurstSizeConsistency_272) {
  UShortValue value;
  value.read("5");

  std::ostringstream os1, os2;
  SonyMakerNote::printMultiBurstSize(os1, value, nullptr);
  SonyMakerNote::printMultiBurstSize(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}
