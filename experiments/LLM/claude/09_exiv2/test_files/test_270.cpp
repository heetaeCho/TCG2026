#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_270 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// ============================================================
// Tag list accessor tests
// ============================================================

TEST_F(SonyMakerNoteTest_270, TagListFpNotNull_270) {
  auto tagList = SonyMakerNote::tagListFp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagListNotNull_270) {
  auto tagList = SonyMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagListCsNotNull_270) {
  auto tagList = SonyMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagListCs2NotNull_270) {
  auto tagList = SonyMakerNote::tagListCs2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagListSonyMisc1NotNull_270) {
  auto tagList = SonyMakerNote::tagListSonyMisc1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagListSonyMisc2bNotNull_270) {
  auto tagList = SonyMakerNote::tagListSonyMisc2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagListSonyMisc3cNotNull_270) {
  auto tagList = SonyMakerNote::tagListSonyMisc3c();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagListSonySInfo1NotNull_270) {
  auto tagList = SonyMakerNote::tagListSonySInfo1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_270, TagList2010eNotNull_270) {
  auto tagList = SonyMakerNote::tagList2010e();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests - Normal operation
// ============================================================

TEST_F(SonyMakerNoteTest_270, PrintWhiteBalanceFineTune_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  // Output should contain something
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintMultiBurstMode_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintMultiBurstSize_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printMultiBurstSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAutoHDRStd_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAutoHDRStd(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintWBShiftABGM_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWBShiftABGM(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusMode2_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFAreaModeSetting_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFAreaModeSetting(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFlexibleSpotPosition_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFPointSelected_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFPointSelected(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFPointsUsed_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFPointsUsed(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFTracking_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFTracking(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocalPlaneAFPointsUsed_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocalPlaneAFPointsUsed(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintWBShiftABGMPrecise_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintExposureStandardAdjustment_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintPixelShiftInfo_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printPixelShiftInfo(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusFrameSize_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintColorTemperature_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintColorCompensationFilter_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printColorCompensationFilter(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintLensSpec_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printLensSpec(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintImageSize_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printImageSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusMode_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFMode_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFMode(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusMode3_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode3(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintHighISONoiseReduction2_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc1CameraTemperature_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSony2FpFocusMode_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSony2FpFocusPosition2_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSony2FpAmbientTemperature_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc2bLensZoomPosition_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc2bFocusPosition2_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cShotNumberSincePowerUp_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cSequenceNumber_NormalValue_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cSonyImageHeight_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cModelReleaseYear_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cQuality2_NormalValue_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

// ============================================================
// Boundary tests with nullptr metadata
// ============================================================

TEST_F(SonyMakerNoteTest_270, PrintAutoHDRStd_NullMetadata_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAutoHDRStd(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusMode2_NullMetadata_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFAreaModeSetting_NullMetadata_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFAreaModeSetting(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusMode_NullMetadata_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFMode_NullMetadata_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printAFMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintHighISONoiseReduction2_NullMetadata_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ============================================================
// Tests with specific values to check output variations
// ============================================================

TEST_F(SonyMakerNoteTest_270, PrintMultiBurstMode_Value1_270) {
  ULongValue value;
  value.read("1");
  auto& result = SonyMakerNote::printMultiBurstMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintMultiBurstSize_Value1_270) {
  ULongValue value;
  value.read("1");
  auto& result = SonyMakerNote::printMultiBurstSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintWhiteBalanceFineTune_PositiveValue_270) {
  ULongValue value;
  value.read("5");
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintColorTemperature_SpecificValue_270) {
  ULongValue value;
  value.read("5500");
  auto& result = SonyMakerNote::printColorTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintImageSize_Value1_270) {
  ULongValue value;
  value.read("1");
  auto& result = SonyMakerNote::printImageSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintSony2FpFocusMode_Value1_270) {
  ULongValue value;
  value.read("1");
  auto& result = SonyMakerNote::printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ============================================================
// Stream chaining test
// ============================================================

TEST_F(SonyMakerNoteTest_270, PrintFunctions_ReturnSameStream_270) {
  ULongValue value;
  value.read("0");

  std::ostringstream os1, os2, os3;
  auto& r1 = SonyMakerNote::printWhiteBalanceFineTune(os1, value, nullptr);
  auto& r2 = SonyMakerNote::printMultiBurstMode(os2, value, nullptr);
  auto& r3 = SonyMakerNote::printMultiBurstSize(os3, value, nullptr);

  EXPECT_EQ(&r1, &os1);
  EXPECT_EQ(&r2, &os2);
  EXPECT_EQ(&r3, &os3);
}

// ============================================================
// Tests with large/boundary values
// ============================================================

TEST_F(SonyMakerNoteTest_270, PrintColorTemperature_MaxValue_270) {
  ULongValue value;
  value.read("65535");
  auto& result = SonyMakerNote::printColorTemperature(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cSequenceNumber_LargeValue_270) {
  ULongValue value;
  value.read("9999");
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintExposureStandardAdjustment_NormalValue_270) {
  ULongValue value;
  value.read("100");
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_270, PrintColorCompensationFilter_NormalValue_270) {
  ULongValue value;
  value.read("128");
  auto& result = SonyMakerNote::printColorCompensationFilter(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// ============================================================
// Print functions with empty ExifData
// ============================================================

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc1CameraTemperature_EmptyExifData_270) {
  ULongValue value;
  value.read("25");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSony2FpAmbientTemperature_EmptyExifData_270) {
  ULongValue value;
  value.read("30");
  ExifData exifData;
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSony2FpFocusPosition2_EmptyExifData_270) {
  ULongValue value;
  value.read("50");
  ExifData exifData;
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc2bLensZoomPosition_EmptyExifData_270) {
  ULongValue value;
  value.read("100");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc2bFocusPosition2_EmptyExifData_270) {
  ULongValue value;
  value.read("200");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cShotNumberSincePowerUp_EmptyExifData_270) {
  ULongValue value;
  value.read("42");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cSonyImageHeight_EmptyExifData_270) {
  ULongValue value;
  value.read("4000");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cModelReleaseYear_EmptyExifData_270) {
  ULongValue value;
  value.read("2020");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cQuality2_EmptyExifData_270) {
  ULongValue value;
  value.read("1");
  ExifData exifData;
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintLensSpec_MultipleValues_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printLensSpec(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintPixelShiftInfo_Value0_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printPixelShiftInfo(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusFrameSize_Value0_270) {
  ULongValue value;
  value.read("0");
  auto& result = SonyMakerNote::printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFocusMode3_EmptyExifData_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode3(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFTracking_EmptyExifData_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFTracking(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintFlexibleSpotPosition_EmptyExifData_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFPointSelected_EmptyExifData_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFPointSelected(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_270, PrintAFPointsUsed_EmptyExifData_270) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = SonyMakerNote::printAFPointsUsed(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}
