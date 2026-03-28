#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_269 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(SonyMakerNoteTest_269, TagListReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagList();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListCsReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagListCs();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListCs2ReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagListCs2();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListFpReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagListFp();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListSonyMisc1ReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagListSonyMisc1();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListSonyMisc2bReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagListSonyMisc2b();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListSonyMisc3cReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagListSonyMisc3c();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListSonySInfo1ReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagListSonySInfo1();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagList2010eReturnsNonNull_269) {
  auto tags = SonyMakerNote::tagList2010e();
  ASSERT_NE(tags, nullptr);
}

// ============================================================
// Tests for print functions - normal cases
// ============================================================

TEST_F(SonyMakerNoteTest_269, PrintWhiteBalanceFineTune_SingleValue_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(SonyMakerNoteTest_269, PrintMultiBurstMode_WithValue_269) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintMultiBurstSize_WithValue_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintColorTemperature_WithValue_269) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printColorTemperature(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintColorCompensationFilter_WithValue_269) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSony2FpAmbientTemperature_WithValue_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x80\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpAmbientTemperature(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSony2FpFocusMode_WithValue_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpFocusMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cSequenceNumber_WithValue_269) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cSequenceNumber(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintExposureStandardAdjustment_WithValue_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printExposureStandardAdjustment(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintLensSpec_WithEightValues_269) {
  // LensSpec expects 8 unsigned byte values
  DataValue val(unsignedByte);
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00\x00\x00\x00\x00"), 8, littleEndian);
  auto& result = SonyMakerNote::printLensSpec(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ============================================================
// Tests for print functions - boundary/error cases
// ============================================================

TEST_F(SonyMakerNoteTest_269, PrintWhiteBalanceFineTune_EmptyValue_269) {
  UShortValue val;
  // Don't read any data - empty value
  auto& result = SonyMakerNote::printWhiteBalanceFineTune(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintMultiBurstMode_NullMetadata_269) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printMultiBurstMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintMultiBurstSize_EmptyValue_269) {
  UShortValue val;
  auto& result = SonyMakerNote::printMultiBurstSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintImageSize_WithValue_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printImageSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintFocusMode_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintAFMode_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFMode(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintFocusMode2_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintFocusMode3_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode3(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintHighISONoiseReduction2_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printHighISONoiseReduction2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintAutoHDRStd_WithNullMetadata_269) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printAutoHDRStd(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintWBShiftABGM_WithValue_269) {
  // WBShiftABGM expects multiple values
  LongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00\x00\x00\x00\x00"), 8, littleEndian);
  auto& result = SonyMakerNote::printWBShiftABGM(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintWBShiftABGMPrecise_WithValue_269) {
  LongValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00\x00\x00\x00\x00"), 8, littleEndian);
  auto& result = SonyMakerNote::printWBShiftABGMPrecise(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintPixelShiftInfo_WithValue_269) {
  DataValue val(unsignedByte);
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printPixelShiftInfo(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintFocusFrameSize_WithValue_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printFocusFrameSize(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintAFAreaModeSetting_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFAreaModeSetting(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintFlexibleSpotPosition_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printFlexibleSpotPosition(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintAFPointSelected_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFPointSelected(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintAFPointsUsed_WithNullMetadata_269) {
  DataValue val(unsignedByte);
  val.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"), 10, littleEndian);
  auto& result = SonyMakerNote::printAFPointsUsed(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintAFTracking_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFTracking(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintFocalPlaneAFPointsUsed_WithValue_269) {
  DataValue val(unsignedByte);
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocalPlaneAFPointsUsed(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc1CameraTemperature_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x80\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSony2FpFocusPosition2_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSony2FpFocusPosition2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc2bLensZoomPosition_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc2bLensZoomPosition(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc2bFocusPosition2_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc2bFocusPosition2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cShotNumberSincePowerUp_WithNullMetadata_269) {
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cSonyImageHeight_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cSonyImageHeight(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cModelReleaseYear_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cModelReleaseYear(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cQuality2_WithNullMetadata_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc3cQuality2(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ============================================================
// Tests verifying stream chaining works (returns same stream)
// ============================================================

TEST_F(SonyMakerNoteTest_269, PrintFunctionsReturnSameStream_269) {
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);

  std::ostringstream os1;
  auto& r1 = SonyMakerNote::printWhiteBalanceFineTune(os1, val, nullptr);
  EXPECT_EQ(&r1, &os1);

  std::ostringstream os2;
  auto& r2 = SonyMakerNote::printMultiBurstSize(os2, val, nullptr);
  EXPECT_EQ(&r2, &os2);

  std::ostringstream os3;
  auto& r3 = SonyMakerNote::printImageSize(os3, val, nullptr);
  EXPECT_EQ(&r3, &os3);
}

// ============================================================
// Tests with ExifData provided
// ============================================================

TEST_F(SonyMakerNoteTest_269, PrintAutoHDRStd_WithExifData_269) {
  ExifData exifData;
  ULongValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00\x00\x00"), 4, littleEndian);
  auto& result = SonyMakerNote::printAutoHDRStd(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintFocusMode_WithExifData_269) {
  ExifData exifData;
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printFocusMode(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintAFMode_WithExifData_269) {
  ExifData exifData;
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printAFMode(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(SonyMakerNoteTest_269, PrintSonyMisc1CameraTemperature_WithExifData_269) {
  ExifData exifData;
  UShortValue val;
  val.read(reinterpret_cast<const byte*>("\x50\x00"), 2, littleEndian);
  auto& result = SonyMakerNote::printSonyMisc1CameraTemperature(os_, val, &exifData);
  EXPECT_EQ(&result, &os_);
}

// ============================================================
// Tag list first entry verification
// ============================================================

TEST_F(SonyMakerNoteTest_269, TagListFirstEntryHasValidTag_269) {
  auto tags = SonyMakerNote::tagList();
  // The first entry should have a valid tag number (non-negative when accessed)
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListCs2FirstEntryHasValidTag_269) {
  auto tags = SonyMakerNote::tagListCs2();
  ASSERT_NE(tags, nullptr);
}

TEST_F(SonyMakerNoteTest_269, TagListConsistency_269) {
  // Calling tagList multiple times should return the same pointer
  auto tags1 = SonyMakerNote::tagList();
  auto tags2 = SonyMakerNote::tagList();
  EXPECT_EQ(tags1, tags2);
}

TEST_F(SonyMakerNoteTest_269, TagListCs2Consistency_269) {
  auto tags1 = SonyMakerNote::tagListCs2();
  auto tags2 = SonyMakerNote::tagListCs2();
  EXPECT_EQ(tags1, tags2);
}

TEST_F(SonyMakerNoteTest_269, TagListFpConsistency_269) {
  auto tags1 = SonyMakerNote::tagListFp();
  auto tags2 = SonyMakerNote::tagListFp();
  EXPECT_EQ(tags1, tags2);
}
