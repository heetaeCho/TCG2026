#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_449 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ==================== tagList tests ====================

TEST_F(Nikon3MakerNoteTest_449, TagListLd4ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListVrReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListPcReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListWtReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListIiReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListAfReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListAf21ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListAf22ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListAFTReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListFiReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListMeReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListFl1ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListFl2ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListFl3ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListFl6ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListFl7ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListSi1ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListSi2ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListSi3ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListSi4ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListSi5ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListCb1ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListCb2ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListCb2aReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListCb2bReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListCb3ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListCb4ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListLd1ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListLd2ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_449, TagListLd3ReturnsNonNull_449) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

// ==================== Print function tests ====================

TEST_F(Nikon3MakerNoteTest_449, PrintIiIsoWithSingleValue_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  // Should produce some output without crashing
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintIiIsoReturnsOstream_449) {
  UShortValue value;
  value.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0002WithEmptyValue_449) {
  AsciiValue value;
  value.read("");
  Nikon3MakerNote::print0x0002(os, value, nullptr);
  // Should not crash
  SUCCEED();
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0007WithAsciiValue_449) {
  AsciiValue value;
  value.read("AF-S");
  auto& result = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0083WithUShort_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0084WithFourRationals_449) {
  URationalValue value;
  value.read("180/10 700/10 28/10 40/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0084WithEmptyValue_449) {
  URationalValue value;
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  SUCCEED();
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0085WithRational_449) {
  URationalValue value;
  value.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0086WithRational_449) {
  URationalValue value;
  value.read("10/1");
  auto& result = Nikon3MakerNote::print0x0086(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0088WithUShort_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0089WithUShort_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x008bWithUShort_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocusDistanceWithByte_449) {
  UShortValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocusDistanceZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintApertureWithByte_449) {
  UShortValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintApertureZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocalWithByte_449) {
  UShortValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocalZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFStopsWithByte_449) {
  UShortValue value;
  value.read("48");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFStopsZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintExitPupilPositionWithByte_449) {
  UShortValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintExitPupilPositionZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashFocalLengthWithByte_449) {
  UShortValue value;
  value.read("24");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashFocalLengthZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintRepeatingFlashRateWithByte_449) {
  UShortValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintRepeatingFlashRateZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintRepeatingFlashCountWithByte_449) {
  UShortValue value;
  value.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintRepeatingFlashCountZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, Print0x009aWithTwoRationals_449) {
  URationalValue value;
  value.read("2500/1000 2500/1000");
  auto& result = Nikon3MakerNote::print0x009a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, Print0x009eWithUShortMultipleValues_449) {
  UShortValue value;
  value.read("0 1 2 3 4 5 6 7 8 9");
  auto& result = Nikon3MakerNote::print0x009e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintTimeZoneReturnsStream_449) {
  ShortValue value;
  value.read("540");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintTimeZoneNegative_449) {
  ShortValue value;
  value.read("-300");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintPictureControlReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintCameraExposureCompensationReturnsStream_449) {
  UShortValue value;
  value.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashZoomHeadPositionReturnsStream_449) {
  UShortValue value;
  value.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashZoomHeadPositionZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintApertureLd4ReturnsStream_449) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintApertureLd4Zero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocalLd4ReturnsStream_449) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocalLd4Zero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocusDistanceLd4ReturnsStream_449) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocusDistanceLd4Zero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintLensId1ReturnsStream_449) {
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintLensId2ReturnsStream_449) {
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintLensId3ReturnsStream_449) {
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintLensId4ReturnsStream_449) {
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintLensIdWithGroupReturnsStream_449) {
  UShortValue value;
  value.read("1");
  std::string group = "Nikon3";
  auto& result = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintAfPointsInFocusReturnsStream_449) {
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintAf2AreaModeReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintExternalFlashData1Fl6ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintExternalFlashData1Fl7ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintExternalFlashData2Fl6ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintExternalFlashData2ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashMasterDataFl6ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashMasterDataFl7ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupAControlDataReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupBCControlDataReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupADataFl6ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupADataFl7ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupBDataFl6ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupBDataFl7ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupCDataFl6ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintFlashGroupCDataFl7ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintExternalFlashData3ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_449, PrintExternalFlashData4ReturnsStream_449) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Boundary and edge cases ====================

TEST_F(Nikon3MakerNoteTest_449, PrintFocusDistanceMaxByte_449) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintApertureMaxByte_449) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocalMaxByte_449) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFStopsMaxByte_449) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintTimeZoneZero_449) {
  ShortValue value;
  value.read("0");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0083AllBitsSet_449) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0088MultipleValues_449) {
  UShortValue value;
  value.read("0 1 2 3");
  Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintCameraExposureCompensationZero_449) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, Print0x0084SingleRational_449) {
  URationalValue value;
  value.read("50/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  // With only 1 rational instead of expected 4, it should still handle gracefully
  SUCCEED();
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocusDistanceLd4MaxValue_449) {
  UShortValue value;
  value.read("65535");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintApertureLd4MaxValue_449) {
  UShortValue value;
  value.read("65535");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_449, PrintFocalLd4MaxValue_449) {
  UShortValue value;
  value.read("65535");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
