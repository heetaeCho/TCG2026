#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_436 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// tagList functions - verify they return non-null tag info arrays
// ============================================================

TEST_F(Nikon3MakerNoteTest_436, TagListSi2ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagList();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListVrReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListVr();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListPcReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListPc();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListWtReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListWt();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListIiReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListIi();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListAfReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListAf();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListAf21ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListAf22ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListAFTReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListFiReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListFi();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListMeReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListMe();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListFl1ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListFl2ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListFl3ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListFl6ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListFl7ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListSi1ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListSi3ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListSi4ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListSi5ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListCb1ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListCb2ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListCb2aReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListCb2bReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListCb3ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListCb4ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListLd1ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListLd2ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListLd3ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_436, TagListLd4ReturnsNonNull_436) {
  auto result = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(result, nullptr);
}

// ============================================================
// Print functions - test that they return the ostream reference
// and produce some output
// ============================================================

TEST_F(Nikon3MakerNoteTest_436, PrintIiIsoWithSingleValue_436) {
  UShortValue val;
  val.read("256");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintIiIsoWithZeroValue_436) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0002SingleValue_436) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0002MultipleValues_436) {
  UShortValue val;
  val.read("2 0 0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0007ReturnsStream_436) {
  AsciiValue val;
  val.read("ISO 100");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0083ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0084WithFourValues_436) {
  URationalValue val;
  val.read("180/10 700/10 28/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0084WithFewerValues_436) {
  URationalValue val;
  val.read("0/0");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0085ReturnsStream_436) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0086ReturnsStream_436) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0088ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0089ReturnsStream_436) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x008bReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocusDistanceReturnsStream_436) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocusDistanceZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintApertureReturnsStream_436) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintApertureZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocalReturnsStream_436) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocalZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFStopsReturnsStream_436) {
  UByteValue val;
  val.read("72");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFStopsZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExitPupilPositionReturnsStream_436) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExitPupilPositionZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashFocalLengthReturnsStream_436) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashFocalLengthZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintRepeatingFlashRateReturnsStream_436) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintRepeatingFlashRateZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintRepeatingFlashCountReturnsStream_436) {
  UByteValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintRepeatingFlashCountZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintTimeZoneReturnsStream_436) {
  ShortValue val;
  val.read("60");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintTimeZoneNegative_436) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintTimeZoneZero_436) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintPictureControlReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x009aWithTwoValues_436) {
  URationalValue val;
  val.read("2592/1 1728/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x009aSingleValue_436) {
  URationalValue val;
  val.read("100/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x009eReturnsStream_436) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintApertureLd4ReturnsStream_436) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintApertureLd4Zero_436) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocalLd4ReturnsStream_436) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocalLd4Zero_436) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocusDistanceLd4ReturnsStream_436) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocusDistanceLd4Zero_436) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintCameraExposureCompensationReturnsStream_436) {
  UByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintCameraExposureCompensationZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashZoomHeadPositionReturnsStream_436) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashZoomHeadPositionZero_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintLensId1ReturnsStream_436) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintLensId2ReturnsStream_436) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintLensId3ReturnsStream_436) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintLensId4ReturnsStream_436) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintLensIdWithGroupReturnsStream_436) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintAfPointsInFocusReturnsStream_436) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintAf2AreaModeReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExternalFlashData1Fl6ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExternalFlashData1Fl7ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExternalFlashData2Fl6ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExternalFlashData2ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashMasterDataFl6ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashMasterDataFl7ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupAControlDataReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupBCControlDataReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupADataFl6ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupADataFl7ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupBDataFl6ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupBDataFl7ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupCDataFl6ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFlashGroupCDataFl7ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExternalFlashData3ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintExternalFlashData4ReturnsStream_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Additional boundary / edge case tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_436, Print0x0083WithVariousBitmasks_436) {
  // Test with value 1 (D lens)
  UByteValue val1;
  val1.read("1");
  Nikon3MakerNote::print0x0083(os, val1, nullptr);
  std::string result1 = os.str();

  // Test with value 2 (G lens)
  os.str("");
  UByteValue val2;
  val2.read("2");
  Nikon3MakerNote::print0x0083(os, val2, nullptr);
  std::string result2 = os.str();

  // Different values should potentially produce different output
  // (at minimum we verify no crash)
  EXPECT_FALSE(result1.empty());
  EXPECT_FALSE(result2.empty());
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0088WithDifferentValues_436) {
  // AF center
  UByteValue val0;
  val0.read("0");
  Nikon3MakerNote::print0x0088(os, val0, nullptr);
  std::string r0 = os.str();

  os.str("");
  UByteValue val1;
  val1.read("1");
  Nikon3MakerNote::print0x0088(os, val1, nullptr);
  std::string r1 = os.str();

  EXPECT_FALSE(r0.empty());
  EXPECT_FALSE(r1.empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintLensIdWithEmptyGroup_436) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, "");
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocusDistanceMaxValue_436) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintApertureMaxValue_436) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintFocalMaxValue_436) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintFStopsMaxValue_436) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_436, Print0x0089WithMultipleFlags_436) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);

  os.str("");
  UShortValue val2;
  val2.read("16");
  Nikon3MakerNote::print0x0089(os, val2, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_436, PrintExternalFlashData2DifferentValues_436) {
  UByteValue val1;
  val1.read("0");
  Nikon3MakerNote::printExternalFlashData2(os, val1, nullptr);
  EXPECT_FALSE(os.str().empty());

  os.str("");
  UByteValue val2;
  val2.read("255");
  Nikon3MakerNote::printExternalFlashData2(os, val2, nullptr);
  EXPECT_FALSE(os.str().empty());
}
