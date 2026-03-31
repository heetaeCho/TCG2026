#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_429 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (non-null return)
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, TagListReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagList();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListMeReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListVrReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListPcReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListWtReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListIiReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListAfReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListAf21ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListAf22ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListAFTReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListFiReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListFl1ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListFl2ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListFl3ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListFl6ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListFl7ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListSi1ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListSi2ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListSi3ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListSi4ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListSi5ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListCb1ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListCb2ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListCb2aReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListCb2bReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListCb3ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListCb4ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListLd1ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListLd2ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListLd3ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_429, TagListLd4ReturnsNonNull_429) {
  auto tags = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tags, nullptr);
}

// ============================================================
// Tests for print functions with various values
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintIiIsoWithValidValue_429) {
  UShortValue val;
  val.read("256");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintIiIsoWithZeroValue_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0002WithSingleValue_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0002WithMultipleValues_429) {
  UShortValue val;
  val.read("2 0 0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0007ReturnsStream_429) {
  AsciiValue val;
  val.read("TEST");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0083WithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0083WithNonZero_429) {
  UShortValue val;
  val.read("2");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0084WithFourValues_429) {
  URationalValue val;
  val.read("180/10 700/10 28/10 56/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0084WithTwoValues_429) {
  URationalValue val;
  val.read("180/10 700/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0085WithValidValue_429) {
  URationalValue val;
  val.read("100/100");
  Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0086WithValidValue_429) {
  URationalValue val;
  val.read("100/1");
  Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0088WithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x0089WithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x008bWithValue_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistanceWithValidValue_429) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistanceWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintApertureWithValidValue_429) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintApertureWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocalWithValidValue_429) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocalWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFStopsWithValidValue_429) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintExitPupilPositionWithValidValue_429) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintExitPupilPositionWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashFocalLengthWithValidValue_429) {
  UShortValue val;
  val.read("35");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashFocalLengthWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintRepeatingFlashRateWithValidValue_429) {
  UShortValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintRepeatingFlashRateWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintRepeatingFlashCountWithValidValue_429) {
  UShortValue val;
  val.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintRepeatingFlashCountWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x009aWithTwoValues_429) {
  URationalValue val;
  val.read("2500/1000 1600/1000");
  Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, Print0x009eWithValue_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintTimeZoneWithValue_429) {
  ShortValue val;
  val.read("540");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintTimeZoneWithNegativeValue_429) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintTimeZoneWithZero_429) {
  ShortValue val;
  val.read("0");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintPictureControlWithValue_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintCameraExposureCompensationWithValue_429) {
  UShortValue val;
  val.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintCameraExposureCompensationWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashZoomHeadPositionWithValue_429) {
  UShortValue val;
  val.read("35");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashZoomHeadPositionWithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintApertureLd4WithValue_429) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintApertureLd4WithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocalLd4WithValue_429) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocalLd4WithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistanceLd4WithValue_429) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistanceLd4WithZero_429) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for LensId print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintLensId1ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintLensId2ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintLensId3ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintLensId4ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for AF Area Mode print
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintAf2AreaModeWithValidValue_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for AF Points In Focus
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintAfPointsInFocusReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for external flash data prints
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData1Fl6ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData1Fl7ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData2Fl6ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData2ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData3ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData4ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for flash master data prints
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintFlashMasterDataFl6ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashMasterDataFl7ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for flash group control data prints
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupAControlDataReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupBCControlDataReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for flash group data prints
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupADataFl6ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupADataFl7ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupBDataFl6ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupBDataFl7ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupCDataFl6ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupCDataFl7ReturnsStream_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests with ExifData passed (non-null metadata)
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, Print0x0089WithExifData_429) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintLensIdWithGroupString_429) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, "Nikon3");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintLensId1WithExifData_429) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_429, PrintAf2AreaModeWithExifData_429) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary: large values
// ============================================================

TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistanceWithMaxByte_429) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintApertureWithMaxByte_429) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocalWithMaxByte_429) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFStopsWithMaxByte_429) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistanceLd4WithLargeValue_429) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintFocalLd4WithLargeValue_429) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_429, PrintApertureLd4WithLargeValue_429) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}
