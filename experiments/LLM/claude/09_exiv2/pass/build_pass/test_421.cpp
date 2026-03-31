#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_421 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions - verify they return non-null
// ============================================================

TEST_F(Nikon3MakerNoteTest_421, TagListPcReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListPc();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListVrReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListVr();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListWtReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListWt();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListIiReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListIi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListAfReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListAf();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListAf21ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListAf22ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListAFTReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListFiReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListMeReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListFl1ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListFl2ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListFl3ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListFl6ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListFl7ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListSi1ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListSi2ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListSi3ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListSi4ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListSi5ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListCb1ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListCb2ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListCb2aReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListCb2bReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListCb3ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListCb4ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListLd1ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListLd2ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListLd3ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_421, TagListLd4ReturnsNonNull_421) {
  auto result = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_421, PrintIiIsoWithValidValue_421) {
  UShortValue val;
  val.read("256");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_421, PrintIiIsoWithZeroValue_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0002WithSingleValue_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0002WithMultipleValues_421) {
  UShortValue val;
  val.read("0 2 0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0007ReturnsStream_421) {
  AsciiValue val;
  val.read("BASIC");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0083WithValue0_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0083WithValue1_421) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0084WithFourValues_421) {
  URationalValue val;
  val.read("240/10 700/10 28/10 40/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0084WithTwoValues_421) {
  URationalValue val;
  val.read("500/10 500/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0085WithValidValue_421) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0086WithValidValue_421) {
  URationalValue val;
  val.read("10/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0088WithValue0_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x0089WithValue0_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x008bReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFocusDistanceWithValidValue_421) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_421, PrintFocusDistanceWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintApertureWithValidValue_421) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_421, PrintApertureWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFocalWithValidValue_421) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_421, PrintFocalWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFStopsWithValidValue_421) {
  UShortValue val;
  val.read("72");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintExitPupilPositionWithValidValue_421) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintExitPupilPositionWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashFocalLengthWithValidValue_421) {
  UShortValue val;
  val.read("35");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashFocalLengthWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintRepeatingFlashRateWithValidValue_421) {
  UShortValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintRepeatingFlashRateWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintRepeatingFlashCountWithValidValue_421) {
  UShortValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintRepeatingFlashCountWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintTimeZoneWithValidValue_421) {
  ShortValue val;
  val.read("540");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintTimeZoneWithZero_421) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintTimeZoneWithNegativeValue_421) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x009aWithTwoValues_421) {
  URationalValue val;
  val.read("100/1 100/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, Print0x009eReturnsStream_421) {
  UShortValue val;
  val.read("0 1 2 3 4 5 6 7 8 9");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintPictureControlReturnsStream_421) {
  AsciiValue val;
  val.read("Standard");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintLensId1ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintLensId2ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintLensId3ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintLensId4ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintLensIdWithGroupReturnsStream_421) {
  UShortValue val;
  val.read("0");
  std::string group = "Nikon3";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintCameraExposureCompensationReturnsStream_421) {
  UShortValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashZoomHeadPositionReturnsStream_421) {
  UShortValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashZoomHeadPositionZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintApertureLd4WithValidValue_421) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFocalLd4WithValidValue_421) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFocusDistanceLd4WithValidValue_421) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintAf2AreaModeReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintAfPointsInFocusReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for consistency of tagList calls
// ============================================================

TEST_F(Nikon3MakerNoteTest_421, TagListPcConsistentAcrossCalls_421) {
  auto result1 = Nikon3MakerNote::tagListPc();
  auto result2 = Nikon3MakerNote::tagListPc();
  EXPECT_EQ(result1, result2);
}

TEST_F(Nikon3MakerNoteTest_421, TagListConsistentAcrossCalls_421) {
  auto result1 = Nikon3MakerNote::tagList();
  auto result2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(Nikon3MakerNoteTest_421, DifferentTagListsAreDifferent_421) {
  auto pc = Nikon3MakerNote::tagListPc();
  auto vr = Nikon3MakerNote::tagListVr();
  // They should point to different tag info arrays
  EXPECT_NE(pc, vr);
}

// ============================================================
// Edge case: flash-related print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_421, PrintExternalFlashData1Fl6ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintExternalFlashData1Fl7ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintExternalFlashData2Fl6ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintExternalFlashData2ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashMasterDataFl6ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashMasterDataFl7ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupAControlDataReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupBCControlDataReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupADataFl6ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupADataFl7ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupBDataFl6ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupBDataFl7ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupCDataFl6ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFlashGroupCDataFl7ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintExternalFlashData3ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintExternalFlashData4ReturnsStream_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary: max/min values
// ============================================================

TEST_F(Nikon3MakerNoteTest_421, PrintFocusDistanceMaxValue_421) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintApertureMaxValue_421) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFocalMaxValue_421) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_421, PrintFStopsWithZero_421) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}
