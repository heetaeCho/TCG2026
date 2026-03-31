#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_274 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(SonyMakerNoteTest_274, TagListSonySInfo1_NotNull_274) {
  auto tagList = SonyMakerNote::tagListSonySInfo1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagList_NotNull_274) {
  auto tagList = SonyMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagListCs_NotNull_274) {
  auto tagList = SonyMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagListCs2_NotNull_274) {
  auto tagList = SonyMakerNote::tagListCs2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagListFp_NotNull_274) {
  auto tagList = SonyMakerNote::tagListFp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagListSonyMisc1_NotNull_274) {
  auto tagList = SonyMakerNote::tagListSonyMisc1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagListSonyMisc2b_NotNull_274) {
  auto tagList = SonyMakerNote::tagListSonyMisc2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagListSonyMisc3c_NotNull_274) {
  auto tagList = SonyMakerNote::tagListSonyMisc3c();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(SonyMakerNoteTest_274, TagList2010e_NotNull_274) {
  auto tagList = SonyMakerNote::tagList2010e();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions - normal operation
// ============================================================

TEST_F(SonyMakerNoteTest_274, PrintWhiteBalanceFineTune_SingleValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintMultiBurstMode_SingleValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintMultiBurstSize_SingleValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstSize(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintColorTemperature_SingleValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\xe8\x03"), 2, littleEndian);  // 1000
  auto& result = SonyMakerNote::printColorTemperature(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintColorCompensationFilter_SingleValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x05\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printColorCompensationFilter(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintLensSpec_ReturnsOstream_274) {
  ULongValue val;
  byte data[32] = {0};
  val.read(data, 32, littleEndian);
  auto& result = SonyMakerNote::printLensSpec(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintImageSize_SingleValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printImageSize(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSony2FpAmbientTemperature_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x80\x00"), 2, littleEndian);  // 128
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintSony2FpFocusMode_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpFocusMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cSequenceNumber_274) {
  ULongValue val;
  byte data[4] = {0x01, 0x00, 0x00, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintExposureStandardAdjustment_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintAutoHDRStd_WithNullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAutoHDRStd(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintWBShiftABGM_274) {
  UShortValue val;
  byte data[4] = {0x00, 0x00, 0x00, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printWBShiftABGM(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintFocusMode2_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintAFAreaModeSetting_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFAreaModeSetting(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintFocalPlaneAFPointsUsed_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocalPlaneAFPointsUsed(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintWBShiftABGMPrecise_274) {
  UShortValue val;
  byte data[8] = {0};
  val.read(data, 8, littleEndian);
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintPixelShiftInfo_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printPixelShiftInfo(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintFocusFrameSize_274) {
  UShortValue val;
  byte data[4] = {0x00, 0x00, 0x00, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printFocusFrameSize(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintFocusMode_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintAFMode_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintFocusMode3_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintHighISONoiseReduction2_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc1CameraTemperature_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x80\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSony2FpFocusPosition2_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x80\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc2bLensZoomPosition_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc2bFocusPosition2_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cShotNumberSincePowerUp_274) {
  ULongValue val;
  byte data[4] = {0x0A, 0x00, 0x00, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cSonyImageHeight_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x10"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cModelReleaseYear_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x14\x00"), 2, littleEndian);  // 20
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cQuality2_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests with ExifData present
// ============================================================

TEST_F(SonyMakerNoteTest_274, PrintMultiBurstMode_WithExifData_274) {
  ExifData exifData;
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstMode(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintAutoHDRStd_WithExifData_274) {
  ExifData exifData;
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x03\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAutoHDRStd(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintFlexibleSpotPosition_NullMetadata_274) {
  UShortValue val;
  byte data[4] = {0x10, 0x00, 0x20, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintAFPointSelected_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFPointSelected(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintAFPointsUsed_NullMetadata_274) {
  UShortValue val;
  byte data[10] = {0};
  val.read(data, 10, littleEndian);
  auto& result = SonyMakerNote::printAFPointsUsed(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintAFTracking_NullMetadata_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFTracking(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(SonyMakerNoteTest_274, PrintColorTemperature_ZeroValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printColorTemperature(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintColorTemperature_MaxValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\xFF\xFF"), 2, littleEndian);  // 65535
  auto& result = SonyMakerNote::printColorTemperature(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintWhiteBalanceFineTune_MaxValue_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\xFF\xFF"), 2, littleEndian);
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintSony2FpAmbientTemperature_Zero_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(SonyMakerNoteTest_274, PrintSony2FpAmbientTemperature_MaxByte_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\xFF\x00"), 2, littleEndian);  // 255
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for return value chaining
// ============================================================

TEST_F(SonyMakerNoteTest_274, PrintFunctions_ReturnSameOstream_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);

  std::ostringstream os1, os2;
  auto& r1 = SonyMakerNote::printImageSize(os1, val, nullptr);
  auto& r2 = SonyMakerNote::printImageSize(os2, val, nullptr);

  EXPECT_EQ(&r1, &os1);
  EXPECT_EQ(&r2, &os2);
  // Both should produce identical output for the same input
  EXPECT_EQ(os1.str(), os2.str());
}

// ============================================================
// Tests for SonyMisc3c functions with various inputs
// ============================================================

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cShotNumberSincePowerUp_Zero_274) {
  ULongValue val;
  byte data[4] = {0x00, 0x00, 0x00, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cSequenceNumber_Zero_274) {
  ULongValue val;
  byte data[4] = {0x00, 0x00, 0x00, 0x00};
  val.read(data, 4, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(SonyMakerNoteTest_274, PrintExposureStandardAdjustment_NonZero_274) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x64\x00"), 2, littleEndian);  // 100
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}
