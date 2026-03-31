#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_424 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// tagListAf and other tagList functions - verify they return non-null
// ============================================================

TEST_F(Nikon3MakerNoteTest_424, TagListAfReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListAf();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListVrReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListVr();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListPcReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListPc();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListWtReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListWt();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListIiReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListIi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListAf21ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListAf22ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListAFTReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListFiReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListMeReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListFl1ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListFl2ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListFl3ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListFl6ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListFl7ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListSi1ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListSi2ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListSi3ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListSi4ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListSi5ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListCb1ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListCb2ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListCb2aReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListCb2bReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListCb3ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListCb4ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListLd1ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListLd2ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListLd3ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_424, TagListLd4ReturnsNonNull_424) {
  auto result = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Print functions with various Value types
// ============================================================

TEST_F(Nikon3MakerNoteTest_424, Print0x0002WithSingleValue_424) {
  UShortValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0002WithMultipleValues_424) {
  UShortValue val;
  val.read("6 0 100");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0007ReturnsSameStream_424) {
  AsciiValue val;
  val.read("FINE");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0083WithZeroValue_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0084WithFourRationals_424) {
  URationalValue val;
  val.read("180/10 700/10 28/10 40/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0084WithSingleRational_424) {
  URationalValue val;
  val.read("500/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0085FocusDistance_424) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0086DigitalZoom_424) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0088WithSingleByte_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0089WithValue_424) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, Print0x008bReturnsSameStream_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintIiIsoWithZero_424) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintIiIsoWithNonZero_424) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocusDistanceWithByte_424) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocusDistanceWithZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintApertureWithByte_424) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintApertureWithZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocalWithByte_424) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocalWithZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFStopsWithByte_424) {
  UByteValue val;
  val.read("48");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintExitPupilPosition_424) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintExitPupilPositionZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, Print0x009aWithTwoValues_424) {
  URationalValue val;
  val.read("640/1 480/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, Print0x009eWithValues_424) {
  UShortValue val;
  val.read("1 2 3 4 5 6 7 8 9 10");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashFocalLength_424) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashFocalLengthZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintRepeatingFlashRate_424) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintRepeatingFlashRateZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintRepeatingFlashCount_424) {
  UByteValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintRepeatingFlashCountZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintTimeZone_424) {
  ShortValue val;
  val.read("540");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintPictureControl_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintCameraExposureCompensation_424) {
  UByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashZoomHeadPosition_424) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashZoomHeadPositionZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintLensId1_424) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintLensId2_424) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintLensId3_424) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintLensId4_424) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintLensIdWithGroup_424) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintAfPointsInFocusNullMetadata_424) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintAf2AreaModeNullMetadata_424) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocusDistanceLd4_424) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocusDistanceLd4Zero_424) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintApertureLd4_424) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintApertureLd4Zero_424) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocalLd4_424) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintFocalLd4Zero_424) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Flash-related print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_424, PrintExternalFlashData1Fl6_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintExternalFlashData1Fl7_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintExternalFlashData2Fl6_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintExternalFlashData2_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashMasterDataFl6_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashMasterDataFl7_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupAControlData_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupBCControlData_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupADataFl6_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupADataFl7_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupBDataFl6_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupBDataFl7_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupCDataFl6_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFlashGroupCDataFl7_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintExternalFlashData3_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintExternalFlashData4_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Consistency: Calling the same tagList function twice returns the same pointer
// ============================================================

TEST_F(Nikon3MakerNoteTest_424, TagListAfConsistency_424) {
  auto result1 = Nikon3MakerNote::tagListAf();
  auto result2 = Nikon3MakerNote::tagListAf();
  EXPECT_EQ(result1, result2);
}

TEST_F(Nikon3MakerNoteTest_424, TagListConsistency_424) {
  auto result1 = Nikon3MakerNote::tagList();
  auto result2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

// ============================================================
// Boundary: Multiple calls to print functions with same stream
// ============================================================

TEST_F(Nikon3MakerNoteTest_424, PrintFStopsWithZero_424) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintFStopsWith255_424) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0083WithVariousFlags_424) {
  UByteValue val;
  val.read("14");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, Print0x0089WithHighValue_424) {
  UShortValue val;
  val.read("65535");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_424, PrintTimeZoneNegative_424) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_424, PrintTimeZoneZero_424) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}
