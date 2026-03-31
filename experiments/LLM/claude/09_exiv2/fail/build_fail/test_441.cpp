#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_441 : public ::testing::Test {
 protected:
  std::ostringstream os;
  ExifData exifData;
};

// ============================================================
// Tag list accessor tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, TagListCb2IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListVrIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListPcIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListWtIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListIiIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListAfIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListAf21IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListAf22IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListAFTIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListFiIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListMeIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListFl1IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListFl2IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListFl3IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListFl6IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListFl7IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListSi1IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListSi2IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListSi3IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListSi4IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListSi5IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListCb1IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListCb2aIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListCb2bIsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListCb3IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListCb4IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListLd1IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListLd2IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListLd3IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_441, TagListLd4IsNotNull_441) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests - printIiIso
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintIiIsoWithSingleValue_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  // Just check that something was written or at least it doesn't crash
}

TEST_F(Nikon3MakerNoteTest_441, PrintIiIsoWithNonZeroValue_441) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Print function tests - print0x0002
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0002WithSingleValue_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, Print0x0002WithMultipleValues_441) {
  UShortValue val;
  val.read("0 1 2");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x0007
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0007ReturnsStream_441) {
  AsciiValue val;
  val.read("AF-S");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x0083
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0083WithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_441, Print0x0083WithValue1_441) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x0084
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0084WithFourRationalValues_441) {
  URationalValue val;
  val.read("24/1 70/1 28/10 28/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_441, Print0x0084WithSingleValue_441) {
  URationalValue val;
  val.read("50/1");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x0085
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0085ReturnsStream_441) {
  URationalValue val;
  val.read("10/1");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x0086
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0086ReturnsStream_441) {
  URationalValue val;
  val.read("1/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x0088
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0088WithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x0089
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x0089WithZero_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, Print0x0089WithNullMetadata_441) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x008b
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x008bReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printFocusDistance
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintFocusDistanceWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFocusDistanceWithNonZero_441) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Print function tests - printAperture
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintApertureWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintApertureWithNonZero_441) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Print function tests - printFocal
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintFocalWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFocalWithNonZero_441) {
  UByteValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Print function tests - printFStops
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintFStopsWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFStopsWithNonZero_441) {
  UByteValue val;
  val.read("48");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printExitPupilPosition
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintExitPupilPositionWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printFlashFocalLength
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintFlashFocalLengthWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashFocalLengthWithNonZero_441) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printRepeatingFlashRate
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintRepeatingFlashRateWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printRepeatingFlashCount
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintRepeatingFlashCountWithZero_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printTimeZone
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintTimeZoneWithZero_441) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_441, PrintTimeZoneWithPositiveOffset_441) {
  ShortValue val;
  val.read("60");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintTimeZoneWithNegativeOffset_441) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printPictureControl
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintPictureControlReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x009a
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x009aReturnsStream_441) {
  URationalValue val;
  val.read("2500/1000 2500/1000");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, Print0x009aWithSingleValue_441) {
  URationalValue val;
  val.read("1000/100");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - print0x009e
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, Print0x009eReturnsStream_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printLensId1, printLensId2, printLensId3, printLensId4
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintLensId1ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintLensId2ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintLensId3ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintLensId4ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintLensIdWithNullMetadata_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printAfPointsInFocus
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintAfPointsInFocusReturnsStream_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintAfPointsInFocusWithNullMetadata_441) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printAf2AreaMode
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintAf2AreaModeReturnsStream_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printCameraExposureCompensation
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintCameraExposureCompensationReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintCameraExposureCompensationNonZero_441) {
  UByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Print function tests - printFocusDistanceLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintFocusDistanceLd4WithZero_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFocusDistanceLd4WithNonZero_441) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printApertureLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintApertureLd4WithZero_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintApertureLd4WithNonZero_441) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Print function tests - printFocalLd4
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintFocalLd4WithZero_441) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFocalLd4WithNonZero_441) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Print function tests - printFlashZoomHeadPosition
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintFlashZoomHeadPositionReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - Flash group data functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData1Fl6ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData1Fl7ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData2Fl6ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData2ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashMasterDataFl6ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashMasterDataFl7ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupAControlDataReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupBCControlDataReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupADataFl6ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupADataFl7ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupBDataFl6ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupBDataFl7ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupCDataFl6ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupCDataFl7ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData3ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData4ReturnsStream_441) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Print function tests - printLensId with group parameter
// ============================================================

TEST_F(Nikon3MakerNoteTest_441, PrintLensIdWithEmptyGroup_441) {
  UByteValue val;
  val.read("0");
  std::string group;
  auto& result = Nikon3MakerNote::printLensId(os, val, &exifData, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_441, PrintLensIdWithNullMetadataAndGroup_441) {
  UByteValue val;
  val.read("0");
  std::string group = "Nikon";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}
