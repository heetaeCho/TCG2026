#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_271 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// =============================================================================
// Tag list accessor tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, TagListNotNull_271) {
  auto tagList = SonyMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagListCsNotNull_271) {
  auto tagList = SonyMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagListCs2NotNull_271) {
  auto tagList = SonyMakerNote::tagListCs2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagListFpNotNull_271) {
  auto tagList = SonyMakerNote::tagListFp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagListSonyMisc1NotNull_271) {
  auto tagList = SonyMakerNote::tagListSonyMisc1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagListSonyMisc2bNotNull_271) {
  auto tagList = SonyMakerNote::tagListSonyMisc2b();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagListSonyMisc3cNotNull_271) {
  auto tagList = SonyMakerNote::tagListSonyMisc3c();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagListSonySInfo1NotNull_271) {
  auto tagList = SonyMakerNote::tagListSonySInfo1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_271, TagList2010eNotNull_271) {
  auto tagList = SonyMakerNote::tagList2010e();
  EXPECT_NE(tagList, nullptr);
}

// =============================================================================
// printWhiteBalanceFineTune tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintWhiteBalanceFineTune_SingleValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintWhiteBalanceFineTune_NonZeroValue_271) {
  UShortValue value;
  value.read("128");
  SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printMultiBurstMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintMultiBurstMode_Zero_271) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printMultiBurstMode(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintMultiBurstMode_One_271) {
  ULongValue value;
  value.read("1");
  SonyMakerNote::printMultiBurstMode(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printMultiBurstSize tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintMultiBurstSize_ValidValue_271) {
  ULongValue value;
  value.read("1");
  SonyMakerNote::printMultiBurstSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printAutoHDRStd tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintAutoHDRStd_ValidValue_271) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printAutoHDRStd(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printWBShiftABGM tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintWBShiftABGM_TwoValues_271) {
  LongValue value;
  value.read("0 0");
  SonyMakerNote::printWBShiftABGM(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintWBShiftABGM_SingleValue_271) {
  LongValue value;
  value.read("5");
  SonyMakerNote::printWBShiftABGM(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printFocusMode2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFocusMode2_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocusMode2(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printAFAreaModeSetting tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintAFAreaModeSetting_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFAreaModeSetting(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printFlexibleSpotPosition tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFlexibleSpotPosition_TwoValues_271) {
  UShortValue value;
  value.read("100 200");
  SonyMakerNote::printFlexibleSpotPosition(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintFlexibleSpotPosition_SingleValue_271) {
  UShortValue value;
  value.read("100");
  SonyMakerNote::printFlexibleSpotPosition(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printAFPointSelected tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintAFPointSelected_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFPointSelected(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printAFPointsUsed tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintAFPointsUsed_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFPointsUsed(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printAFTracking tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintAFTracking_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFTracking(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printFocalPlaneAFPointsUsed tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFocalPlaneAFPointsUsed_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocalPlaneAFPointsUsed(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printWBShiftABGMPrecise tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintWBShiftABGMPrecise_ValidValues_271) {
  LongValue value;
  value.read("0 0");
  SonyMakerNote::printWBShiftABGMPrecise(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printExposureStandardAdjustment tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintExposureStandardAdjustment_ValidValue_271) {
  ShortValue value;
  value.read("0");
  SonyMakerNote::printExposureStandardAdjustment(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printPixelShiftInfo tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintPixelShiftInfo_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printPixelShiftInfo(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printFocusFrameSize tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFocusFrameSize_ValidValues_271) {
  UShortValue value;
  value.read("100 200");
  SonyMakerNote::printFocusFrameSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintFocusFrameSize_SingleValue_271) {
  UShortValue value;
  value.read("100");
  SonyMakerNote::printFocusFrameSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printColorTemperature tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintColorTemperature_ValidValue_271) {
  ULongValue value;
  value.read("5500");
  SonyMakerNote::printColorTemperature(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintColorTemperature_ZeroValue_271) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printColorTemperature(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printColorCompensationFilter tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintColorCompensationFilter_ValidValue_271) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printColorCompensationFilter(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printLensSpec tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintLensSpec_ValidValues_271) {
  UShortValue value;
  value.read("0 0 0 0 0 0 0 0");
  SonyMakerNote::printLensSpec(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printImageSize tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintImageSize_ValidValue_271) {
  UShortValue value;
  value.read("1");
  SonyMakerNote::printImageSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printFocusMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFocusMode_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocusMode(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printAFMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintAFMode_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFMode(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printFocusMode3 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFocusMode3_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocusMode3(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printHighISONoiseReduction2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintHighISONoiseReduction2_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printHighISONoiseReduction2(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc1CameraTemperature tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc1CameraTemperature_ValidValue_271) {
  UShortValue value;
  value.read("50");
  SonyMakerNote::printSonyMisc1CameraTemperature(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSony2FpFocusMode tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSony2FpFocusMode_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSony2FpFocusMode(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSony2FpFocusPosition2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSony2FpFocusPosition2_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSony2FpFocusPosition2(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSony2FpAmbientTemperature tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSony2FpAmbientTemperature_ValidValue_271) {
  UShortValue value;
  value.read("50");
  SonyMakerNote::printSony2FpAmbientTemperature(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc2bLensZoomPosition tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc2bLensZoomPosition_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc2bLensZoomPosition(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc2bFocusPosition2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc2bFocusPosition2_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc2bFocusPosition2(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc3cShotNumberSincePowerUp tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc3cShotNumberSincePowerUp_ValidValue_271) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc3cSequenceNumber tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc3cSequenceNumber_ValidValue_271) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc3cSequenceNumber(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc3cSonyImageHeight tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc3cSonyImageHeight_ValidValue_271) {
  UShortValue value;
  value.read("1080");
  SonyMakerNote::printSonyMisc3cSonyImageHeight(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc3cModelReleaseYear tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc3cModelReleaseYear_ValidValue_271) {
  UShortValue value;
  value.read("2020");
  SonyMakerNote::printSonyMisc3cModelReleaseYear(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// printSonyMisc3cQuality2 tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc3cQuality2_ValidValue_271) {
  UShortValue value;
  value.read("0");
  SonyMakerNote::printSonyMisc3cQuality2(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Return value tests - verify ostream reference is returned properly
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFunctions_ReturnOstreamReference_271) {
  UShortValue value;
  value.read("0");

  std::ostream& ref = SonyMakerNote::printWhiteBalanceFineTune(os_, value, nullptr);
  EXPECT_EQ(&ref, &os_);
}

TEST_F(SonyMakerNoteTest_271, PrintMultiBurstMode_ReturnOstreamReference_271) {
  ULongValue value;
  value.read("0");
  std::ostream& ref = SonyMakerNote::printMultiBurstMode(os_, value, nullptr);
  EXPECT_EQ(&ref, &os_);
}

TEST_F(SonyMakerNoteTest_271, PrintColorTemperature_ReturnOstreamReference_271) {
  ULongValue value;
  value.read("5500");
  std::ostream& ref = SonyMakerNote::printColorTemperature(os_, value, nullptr);
  EXPECT_EQ(&ref, &os_);
}

// =============================================================================
// Boundary value tests
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintColorTemperature_MaxValue_271) {
  ULongValue value;
  value.read("65535");
  SonyMakerNote::printColorTemperature(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc1CameraTemperature_MaxByte_271) {
  UShortValue value;
  value.read("255");
  SonyMakerNote::printSonyMisc1CameraTemperature(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintSony2FpAmbientTemperature_MaxByte_271) {
  UShortValue value;
  value.read("255");
  SonyMakerNote::printSony2FpAmbientTemperature(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintMultiBurstSize_ZeroValue_271) {
  ULongValue value;
  value.read("0");
  SonyMakerNote::printMultiBurstSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintSonyMisc3cShotNumberSincePowerUp_LargeValue_271) {
  ULongValue value;
  value.read("999999");
  SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Test with ExifData pointer
// =============================================================================

TEST_F(SonyMakerNoteTest_271, PrintFocusMode2_WithExifData_271) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  SonyMakerNote::printFocusMode2(os_, value, &exifData);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintAFAreaModeSetting_WithExifData_271) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  SonyMakerNote::printAFAreaModeSetting(os_, value, &exifData);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_271, PrintAutoHDRStd_WithExifData_271) {
  ExifData exifData;
  ULongValue value;
  value.read("0");
  SonyMakerNote::printAutoHDRStd(os_, value, &exifData);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}
