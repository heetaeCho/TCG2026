#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_267 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// =========================================================================
// tagList* should return non-null pointers
// =========================================================================

TEST_F(SonyMakerNoteTest_267, TagListNotNull_267) {
  auto tags = SonyMakerNote::tagList();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagListCsNotNull_267) {
  auto tags = SonyMakerNote::tagListCs();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagListCs2NotNull_267) {
  auto tags = SonyMakerNote::tagListCs2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagListFpNotNull_267) {
  auto tags = SonyMakerNote::tagListFp();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagListSonyMisc1NotNull_267) {
  auto tags = SonyMakerNote::tagListSonyMisc1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagListSonyMisc2bNotNull_267) {
  auto tags = SonyMakerNote::tagListSonyMisc2b();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagListSonyMisc3cNotNull_267) {
  auto tags = SonyMakerNote::tagListSonyMisc3c();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagListSonySInfo1NotNull_267) {
  auto tags = SonyMakerNote::tagListSonySInfo1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_267, TagList2010eNotNull_267) {
  auto tags = SonyMakerNote::tagList2010e();
  EXPECT_NE(tags, nullptr);
}

// =========================================================================
// printWhiteBalanceFineTune tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintWhiteBalanceFineTune_SingleValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintWhiteBalanceFineTune_EmptyValue_267) {
  UShortValue val;
  // No data read - count is 0
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printMultiBurstMode tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintMultiBurstMode_ZeroValue_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintMultiBurstMode_EmptyValue_267) {
  ULongValue val;
  auto& result = SonyMakerNote::printMultiBurstMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printMultiBurstSize tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintMultiBurstSize_SingleValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printAutoHDRStd tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintAutoHDRStd_NormalValue_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printAutoHDRStd(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printWBShiftABGM tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintWBShiftABGM_TwoValues_267) {
  // Provide two long values
  ULongValue val;
  byte data[8] = {0};
  val.read(data, 8, littleEndian);
  auto& result = SonyMakerNote::printWBShiftABGM(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_267, PrintWBShiftABGM_EmptyValue_267) {
  ULongValue val;
  auto& result = SonyMakerNote::printWBShiftABGM(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printFocusMode2 tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintFocusMode2_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x02\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printAFAreaModeSetting tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintAFAreaModeSetting_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFAreaModeSetting(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printFlexibleSpotPosition tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintFlexibleSpotPosition_TwoValues_267) {
  UShortValue val;
  byte data[4] = {0x80, 0x00, 0x80, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_267, PrintFlexibleSpotPosition_EmptyValue_267) {
  UShortValue val;
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printAFPointSelected tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintAFPointSelected_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFPointSelected(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printAFPointsUsed tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintAFPointsUsed_NormalValue_267) {
  UShortValue val;
  byte data[20] = {0};
  val.read(data, 20, littleEndian);
  auto& result = SonyMakerNote::printAFPointsUsed(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printAFTracking tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintAFTracking_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFTracking(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printFocalPlaneAFPointsUsed tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintFocalPlaneAFPointsUsed_NormalValue_267) {
  UShortValue val;
  byte data[4] = {0};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printFocalPlaneAFPointsUsed(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printWBShiftABGMPrecise tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintWBShiftABGMPrecise_NormalValue_267) {
  ULongValue val;
  byte data[16] = {0};
  val.read(data, 16, littleEndian);
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_267, PrintWBShiftABGMPrecise_EmptyValue_267) {
  ULongValue val;
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printExposureStandardAdjustment tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintExposureStandardAdjustment_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printPixelShiftInfo tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintPixelShiftInfo_NormalValue_267) {
  UShortValue val;
  byte data[4] = {0};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printPixelShiftInfo(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printFocusFrameSize tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintFocusFrameSize_NormalValue_267) {
  UShortValue val;
  byte data[6] = {0};
  val.read(data, 6, littleEndian);
  auto& result = SonyMakerNote::printFocusFrameSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_267, PrintFocusFrameSize_EmptyValue_267) {
  UShortValue val;
  auto& result = SonyMakerNote::printFocusFrameSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printColorTemperature tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintColorTemperature_NormalValue_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\xe8\x03\x00\x00"), 4, littleEndian); // 1000
  auto& result = SonyMakerNote::printColorTemperature(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintColorTemperature_ZeroValue_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printColorTemperature(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printColorCompensationFilter tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintColorCompensationFilter_NormalValue_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printLensSpec tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintLensSpec_NormalValue_267) {
  UShortValue val;
  byte data[16] = {0};
  val.read(data, 16, littleEndian);
  auto& result = SonyMakerNote::printLensSpec(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_267, PrintLensSpec_EmptyValue_267) {
  UShortValue val;
  auto& result = SonyMakerNote::printLensSpec(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printFocusMode tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintFocusMode_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printImageSize tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintImageSize_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printImageSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printAFMode tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintAFMode_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printFocusMode3 tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintFocusMode3_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode3(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printHighISONoiseReduction2 tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintHighISONoiseReduction2_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// printSonyMisc1CameraTemperature tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc1CameraTemperature_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x20\x00"), 2, littleEndian); // value 32
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSony2FpFocusMode tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSony2FpFocusMode_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpFocusMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSony2FpFocusPosition2 tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSony2FpFocusPosition2_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x80\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSony2FpAmbientTemperature tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSony2FpAmbientTemperature_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x19\x00"), 2, littleEndian); // value 25
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSonyMisc2bLensZoomPosition tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc2bLensZoomPosition_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x64\x00"), 2, littleEndian); // value 100
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSonyMisc2bFocusPosition2 tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc2bFocusPosition2_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x80\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSonyMisc3cShotNumberSincePowerUp tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc3cShotNumberSincePowerUp_NormalValue_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x0a\x00\x00\x00"), 4, littleEndian); // value 10
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSonyMisc3cSequenceNumber tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc3cSequenceNumber_NormalValue_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSonyMisc3cSonyImageHeight tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc3cSonyImageHeight_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x10"), 2, littleEndian); // 4096
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSonyMisc3cModelReleaseYear tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc3cModelReleaseYear_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x14\x00"), 2, littleEndian); // value 20
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// printSonyMisc3cQuality2 tests
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintSonyMisc3cQuality2_NormalValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =========================================================================
// Return type verification: all print functions should return the same stream
// =========================================================================

TEST_F(SonyMakerNoteTest_267, AllPrintFunctionsReturnSameStream_267) {
  UShortValue shortVal;
  shortVal.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);

  ULongValue longVal;
  longVal.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);

  std::ostringstream os1, os2, os3;
  EXPECT_EQ(&SonyMakerNote::printWhiteBalanceFineTune(os1, shortVal, nullptr), &os1);
  EXPECT_EQ(&SonyMakerNote::printMultiBurstMode(os2, longVal, nullptr), &os2);
  EXPECT_EQ(&SonyMakerNote::printMultiBurstSize(os3, shortVal, nullptr), &os3);
}

// =========================================================================
// Boundary: passing nullptr for ExifData across multiple functions
// =========================================================================

TEST_F(SonyMakerNoteTest_267, NullptrExifDataForAllFunctions_267) {
  UShortValue shortVal;
  shortVal.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);

  // Just verify none of these crash with nullptr metadata
  std::ostringstream os;
  EXPECT_NO_THROW(SonyMakerNote::printWhiteBalanceFineTune(os, shortVal, nullptr));
  os.str("");
  EXPECT_NO_THROW(SonyMakerNote::printMultiBurstSize(os, shortVal, nullptr));
  os.str("");
  EXPECT_NO_THROW(SonyMakerNote::printColorTemperature(os, shortVal, nullptr));
  os.str("");
  EXPECT_NO_THROW(SonyMakerNote::printColorCompensationFilter(os, shortVal, nullptr));
  os.str("");
  EXPECT_NO_THROW(SonyMakerNote::printExposureStandardAdjustment(os, shortVal, nullptr));
}

// =========================================================================
// Boundary: Values with maximum shorts
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintWhiteBalanceFineTune_MaxValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\xff\xff"), 2, littleEndian); // 65535
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintImageSize_MaxValue_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\xff\xff"), 2, littleEndian);
  auto& result = SonyMakerNote::printImageSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// With ExifData provided
// =========================================================================

TEST_F(SonyMakerNoteTest_267, PrintFocusMode2_WithExifData_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x02\x00"), 2, littleEndian);
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode2(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintAutoHDRStd_WithExifData_267) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  ExifData exifData;
  auto& result = SonyMakerNote::printAutoHDRStd(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_267, PrintAFAreaModeSetting_WithExifData_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x03\x00"), 2, littleEndian);
  ExifData exifData;
  auto& result = SonyMakerNote::printAFAreaModeSetting(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintFocusMode_WithExifData_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  ExifData exifData;
  auto& result = SonyMakerNote::printFocusMode(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintAFMode_WithExifData_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  ExifData exifData;
  auto& result = SonyMakerNote::printAFMode(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_267, PrintHighISONoiseReduction2_WithExifData_267) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  ExifData exifData;
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

// =========================================================================
// Test tagList returns consistent results when called multiple times
// =========================================================================

TEST_F(SonyMakerNoteTest_267, TagListConsistentOnMultipleCalls_267) {
  auto tags1 = SonyMakerNote::tagList();
  auto tags2 = SonyMakerNote::tagList();
  EXPECT_EQ(tags1, tags2);
}

TEST_F(SonyMakerNoteTest_267, TagListCsConsistentOnMultipleCalls_267) {
  auto tags1 = SonyMakerNote::tagListCs();
  auto tags2 = SonyMakerNote::tagListCs();
  EXPECT_EQ(tags1, tags2);
}

TEST_F(SonyMakerNoteTest_267, TagListFpConsistentOnMultipleCalls_267) {
  auto tags1 = SonyMakerNote::tagListFp();
  auto tags2 = SonyMakerNote::tagListFp();
  EXPECT_EQ(tags1, tags2);
}
