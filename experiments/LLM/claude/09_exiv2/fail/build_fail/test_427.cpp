#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_427 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(Nikon3MakerNoteTest_427, TagListAFTReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListVrReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListPcReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListWtReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListIiReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListAfReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListAf21ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListAf22ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListFiReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListMeReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListFl1ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListFl2ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListFl3ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListFl6ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListFl7ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListSi1ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListSi2ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListSi3ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListSi4ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListSi5ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListCb1ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListCb2ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListCb2aReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListCb2bReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListCb3ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListCb4ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListLd1ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListLd2ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListLd3ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListLd4ReturnsNonNull_427) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_427, PrintIiIsoWithSingleValue_427) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  // Just verify it produces some output or handles gracefully
  // The actual output depends on the implementation
}

TEST_F(Nikon3MakerNoteTest_427, PrintIiIsoReturnsStream_427) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0002WithSingleValue_427) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0002WithMultipleValues_427) {
  UShortValue val;
  val.read("2 0 0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0007ReturnsStream_427) {
  AsciiValue val;
  val.read("AF-S VR");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0083ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0084WithFourRationals_427) {
  URationalValue val;
  val.read("180/10 700/10 35/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0084WithEmptyValue_427) {
  URationalValue val;
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0085ReturnsStream_427) {
  URationalValue val;
  val.read("10/1");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0086ReturnsStream_427) {
  URationalValue val;
  val.read("12/10");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0088ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0089ReturnsStream_427) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x008bReturnsStream_427) {
  UByteValue val;
  val.read("0 0 0 0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceReturnsStream_427) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintApertureReturnsStream_427) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, PrintApertureZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocalReturnsStream_427) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocalZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFStopsReturnsStream_427) {
  UByteValue val;
  val.read("72");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFStopsZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExitPupilPositionReturnsStream_427) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExitPupilPositionZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashFocalLengthReturnsStream_427) {
  UByteValue val;
  val.read("35");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashFocalLengthZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashRateReturnsStream_427) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashRateZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashCountReturnsStream_427) {
  UByteValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashCountZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintTimeZoneReturnsStream_427) {
  ShortValue val;
  val.read("60");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintTimeZoneNegative_427) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, PrintTimeZoneZero_427) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x009aReturnsStream_427) {
  URationalValue val;
  val.read("640/1 480/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x009eReturnsStream_427) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintPictureControlReturnsStream_427) {
  UByteValue val;
  val.read("128");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintCameraExposureCompensationReturnsStream_427) {
  UByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintCameraExposureCompensationZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintApertureLd4ReturnsStream_427) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintApertureLd4Zero_427) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocalLd4ReturnsStream_427) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocalLd4Zero_427) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceLd4ReturnsStream_427) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceLd4Zero_427) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintLensId1ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintLensId2ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintLensId3ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintLensId4ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintLensIdWithGroup_427) {
  UByteValue val;
  val.read("0");
  std::string group = "Nikon3";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintAfPointsInFocusReturnsStream_427) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintAf2AreaModeReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashZoomHeadPositionReturnsStream_427) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashZoomHeadPositionZero_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData1Fl6ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData1Fl7ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData2Fl6ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData2ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashMasterDataFl6ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashMasterDataFl7ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupAControlDataReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupBCControlDataReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupADataFl6ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupADataFl7ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupBDataFl6ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupBDataFl7ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupCDataFl6ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupCDataFl7ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData3ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData4ReturnsStream_427) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests with ExifData
// ============================================================

TEST_F(Nikon3MakerNoteTest_427, PrintLensId1WithExifData_427) {
  ExifData exifData;
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0089WithExifData_427) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintAfPointsInFocusWithExifData_427) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintAf2AreaModeWithExifData_427) {
  ExifData exifData;
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests for print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_427, Print0x0083MaxValue_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, Print0x0088MaxValue_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, PrintApertureMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocalMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_427, PrintFStopsMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintExitPupilPositionMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashFocalLengthMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashRateMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashCountMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFlashZoomHeadPositionMaxByte_427) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintApertureLd4MaxUShort_427) {
  UShortValue val;
  val.read("65535");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocalLd4MaxUShort_427) {
  UShortValue val;
  val.read("65535");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceLd4MaxUShort_427) {
  UShortValue val;
  val.read("65535");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Multiple calls produce fresh output each time
// ============================================================

TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceMultipleCalls_427) {
  UByteValue val1;
  val1.read("10");
  Nikon3MakerNote::printFocusDistance(os, val1, nullptr);
  std::string first = os.str();
  
  std::ostringstream os2;
  UByteValue val2;
  val2.read("200");
  Nikon3MakerNote::printFocusDistance(os2, val2, nullptr);
  std::string second = os2.str();
  
  // Different inputs should potentially produce different outputs
  // (unless both map to same result, but we just test the call works)
  EXPECT_FALSE(first.empty());
  EXPECT_FALSE(second.empty());
}

// ============================================================
// Tag list first entry tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_427, TagListFirstEntryHasValidTag_427) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // The first entry should have a valid tag number (non-negative in practice)
  // and a non-null title
  EXPECT_NE(tagList[0].title_, nullptr);
}

TEST_F(Nikon3MakerNoteTest_427, TagListAFTFirstEntryHasValidTag_427) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
  EXPECT_NE(tagList[0].title_, nullptr);
}
