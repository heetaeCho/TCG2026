#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_425 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// tagList functions - verify they return non-null pointers
// =============================================================================

TEST_F(Nikon3MakerNoteTest_425, TagListReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListVrReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListPcReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListWtReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListIiReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListAfReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListAf21ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListAf22ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListAFTReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListFiReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListMeReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListFl1ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListFl2ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListFl3ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListFl6ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListFl7ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListSi1ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListSi2ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListSi3ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListSi4ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListSi5ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListCb1ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListCb2ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListCb2aReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListCb2bReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListCb3ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListCb4ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListLd1ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListLd2ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListLd3ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_425, TagListLd4ReturnsNonNull_425) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tagList, nullptr);
}

// =============================================================================
// Print functions - test with various Value types
// =============================================================================

TEST_F(Nikon3MakerNoteTest_425, PrintIiIsoWithValidValue_425) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, PrintIiIsoWithZeroValue_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0002WithSingleValue_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0002WithMultipleValues_425) {
  UShortValue val;
  val.read("0 2 0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0007ReturnsStream_425) {
  AsciiValue val;
  val.read("ISO 100");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0083WithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0083WithOne_425) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0084WithFourValues_425) {
  URationalValue val;
  val.read("180/10 700/10 28/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0084WithTwoValues_425) {
  URationalValue val;
  val.read("500/10 500/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0085ReturnsStream_425) {
  URationalValue val;
  val.read("5/1");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0086ReturnsStream_425) {
  URationalValue val;
  val.read("10/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0088WithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0089WithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x008bReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocusDistanceWithValue_425) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocusDistanceWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintApertureWithValue_425) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, PrintApertureWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocalWithValue_425) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocalWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFStopsWithValue_425) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, PrintFStopsWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintExitPupilPositionWithValue_425) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, PrintExitPupilPositionWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashFocalLengthWithValue_425) {
  UShortValue val;
  val.read("35");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashFocalLengthWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintRepeatingFlashRateWithValue_425) {
  UShortValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintRepeatingFlashRateWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintRepeatingFlashCountWithValue_425) {
  UShortValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintRepeatingFlashCountWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintTimeZoneWithValue_425) {
  ShortValue val;
  val.read("540");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_425, PrintTimeZoneWithZero_425) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintTimeZoneWithNegativeValue_425) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintPictureControlReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x009aWithTwoValues_425) {
  URationalValue val;
  val.read("640/1 480/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x009eReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintCameraExposureCompensationReturnsStream_425) {
  UShortValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintCameraExposureCompensationWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashZoomHeadPositionWithValue_425) {
  UShortValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashZoomHeadPositionWithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintApertureLd4WithValue_425) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintApertureLd4WithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocalLd4WithValue_425) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocalLd4WithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocusDistanceLd4WithValue_425) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocusDistanceLd4WithZero_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintLensId1ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintLensId2ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintLensId3ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintLensId4ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintAfPointsInFocusReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintAf2AreaModeReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData1Fl6ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData1Fl7ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData2Fl6ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData2ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashMasterDataFl6ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashMasterDataFl7ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupAControlDataReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupBCControlDataReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupADataFl6ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupADataFl7ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupBDataFl6ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupBDataFl7ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupCDataFl6ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupCDataFl7ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData3ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData4ReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintLensIdWithGroupReturnsStream_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintLensIdWithEmptyGroup_425) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, "");
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary/edge case tests
// =============================================================================

TEST_F(Nikon3MakerNoteTest_425, Print0x0084WithSingleValue_425) {
  URationalValue val;
  val.read("50/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0083WithLargeValue_425) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0088WithMultipleValues_425) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, Print0x0089WithLargeValue_425) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocusDistanceMaxValue_425) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintApertureMaxValue_425) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_425, PrintFocalMaxValue_425) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Test constexpr tag list functions return consistent results
// =============================================================================

TEST_F(Nikon3MakerNoteTest_425, TagListAf21ConsistentCalls_425) {
  auto first = Nikon3MakerNote::tagListAf21();
  auto second = Nikon3MakerNote::tagListAf21();
  EXPECT_EQ(first, second);
}

TEST_F(Nikon3MakerNoteTest_425, TagListConsistentCalls_425) {
  auto first = Nikon3MakerNote::tagList();
  auto second = Nikon3MakerNote::tagList();
  EXPECT_EQ(first, second);
}

TEST_F(Nikon3MakerNoteTest_425, TagListLd4ConsistentCalls_425) {
  auto first = Nikon3MakerNote::tagListLd4();
  auto second = Nikon3MakerNote::tagListLd4();
  EXPECT_EQ(first, second);
}
