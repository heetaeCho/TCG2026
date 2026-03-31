#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for Nikon3MakerNote tests
class Nikon3MakerNoteTest_431 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ==================== tagList tests ====================

TEST_F(Nikon3MakerNoteTest_431, TagListReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListVrReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListPcReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListWtReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListIiReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListAfReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListAf21ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListAf22ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListAFTReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListFiReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListMeReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListFl1ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListFl2ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListFl3ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListFl6ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListFl7ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListSi1ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListSi2ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListSi3ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListSi4ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListSi5ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListCb1ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListCb2ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListCb2aReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListCb2bReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListCb3ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListCb4ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListLd1ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListLd2ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListLd3ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_431, TagListLd4ReturnsNonNull_431) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tagList, nullptr);
}

// ==================== print function tests ====================

TEST_F(Nikon3MakerNoteTest_431, PrintIiIsoWithValidValue_431) {
  UShortValue value;
  value.read("256");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_431, PrintIiIsoWithZeroValue_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0002WithSingleValue_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0002WithMultipleValues_431) {
  UShortValue value;
  value.read("0 2 0");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0007ReturnsOstream_431) {
  AsciiValue value;
  value.read("Test");
  auto& result = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0083WithZeroValue_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0084WithFourValues_431) {
  URationalValue value;
  value.read("180/10 700/10 28/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0084WithTwoValues_431) {
  URationalValue value;
  value.read("180/10 700/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0085ReturnsOstream_431) {
  URationalValue value;
  value.read("50/10");
  auto& result = Nikon3MakerNote::print0x0085(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0086ReturnsOstream_431) {
  URationalValue value;
  value.read("10/10");
  auto& result = Nikon3MakerNote::print0x0086(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0088WithZeroValue_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0089ReturnsOstream_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x008bReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocusDistanceReturnsOstream_431) {
  UByteValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocusDistanceZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintApertureReturnsOstream_431) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintApertureZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocalReturnsOstream_431) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocalZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFStopsReturnsOstream_431) {
  UByteValue value;
  value.read("48");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintExitPupilPositionReturnsOstream_431) {
  UByteValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintExitPupilPositionZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashFocalLengthReturnsOstream_431) {
  UByteValue value;
  value.read("24");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashFocalLengthZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintRepeatingFlashRateReturnsOstream_431) {
  UByteValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintRepeatingFlashRateZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintRepeatingFlashCountReturnsOstream_431) {
  UByteValue value;
  value.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintRepeatingFlashCountZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintTimeZoneReturnsOstream_431) {
  ShortValue value;
  value.read("540");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintTimeZoneNegativeValue_431) {
  ShortValue value;
  value.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintTimeZoneZero_431) {
  ShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x009aReturnsOstream_431) {
  URationalValue value;
  value.read("640/1 480/1");
  auto& result = Nikon3MakerNote::print0x009a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x009eReturnsOstream_431) {
  UShortValue value;
  value.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = Nikon3MakerNote::print0x009e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintCameraExposureCompensationReturnsOstream_431) {
  UByteValue value;
  value.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintCameraExposureCompensationZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintPictureControlReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintLensId1ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintLensId2ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintLensId3ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintLensId4ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintLensIdWithGroupReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId(os, value, nullptr, "Nikon3");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocusDistanceLd4ReturnsOstream_431) {
  UShortValue value;
  value.read("100");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocusDistanceLd4Zero_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintApertureLd4ReturnsOstream_431) {
  UShortValue value;
  value.read("100");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintApertureLd4Zero_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocalLd4ReturnsOstream_431) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocalLd4Zero_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashZoomHeadPositionReturnsOstream_431) {
  UByteValue value;
  value.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashZoomHeadPositionZero_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintAf2AreaModeReturnsOstream_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintAfPointsInFocusReturnsOstream_431) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Flash data print tests ====================

TEST_F(Nikon3MakerNoteTest_431, PrintExternalFlashData1Fl6ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintExternalFlashData1Fl7ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintExternalFlashData2Fl6ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintExternalFlashData2ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashMasterDataFl6ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashMasterDataFl7ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupAControlDataReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupBCControlDataReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupADataFl6ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupADataFl7ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupBDataFl6ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupBDataFl7ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupCDataFl6ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFlashGroupCDataFl7ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintExternalFlashData3ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintExternalFlashData4ReturnsOstream_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Consistency tests ====================

TEST_F(Nikon3MakerNoteTest_431, TagListFl2ConsistentAcrossCalls_431) {
  auto tagList1 = Nikon3MakerNote::tagListFl2();
  auto tagList2 = Nikon3MakerNote::tagListFl2();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(Nikon3MakerNoteTest_431, TagListConsistentAcrossCalls_431) {
  auto tagList1 = Nikon3MakerNote::tagList();
  auto tagList2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(Nikon3MakerNoteTest_431, MultiplePrintCallsSameValue_431) {
  UByteValue value;
  value.read("50");

  std::ostringstream os1, os2;
  Nikon3MakerNote::printFocusDistance(os1, value, nullptr);
  Nikon3MakerNote::printFocusDistance(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(Nikon3MakerNoteTest_431, PrintFStopsZeroValue_431) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0083WithBitFlags_431) {
  UByteValue value;
  value.read("14");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_431, Print0x0088WithMultipleValues_431) {
  UByteValue value;
  value.read("0 1 2 3");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocusDistanceMaxValue_431) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_431, PrintApertureMaxValue_431) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_431, PrintFocalMaxValue_431) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}
