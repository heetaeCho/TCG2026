#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_443 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions - verify they return non-null
// ============================================================

TEST_F(Nikon3MakerNoteTest_443, TagListReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListVrReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListPcReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListWtReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListIiReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListAfReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListAf21ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListAf22ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListAFTReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListFiReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListMeReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListFl1ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListFl2ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListFl3ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListFl6ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListFl7ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListSi1ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListSi2ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListSi3ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListSi4ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListSi5ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListCb1ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListCb2ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListCb2aReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListCb2bReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListCb3ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListCb4ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListLd1ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListLd2ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListLd3ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_443, TagListLd4ReturnsNonNull_443) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions with various Value inputs
// ============================================================

TEST_F(Nikon3MakerNoteTest_443, PrintIiIsoWithValidValue_443) {
  UShortValue val;
  val.read("0 100");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintIiIsoSingleValue_443) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0002WithSingleValue_443) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0002WithMultipleValues_443) {
  UShortValue val;
  val.read("0 2 0 6");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0007WithStringValue_443) {
  AsciiValue val;
  val.read("AUTO ");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0083WithZeroValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0083WithFlagValue_443) {
  ByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0084WithFourValues_443) {
  URationalValue val;
  val.read("180/10 700/10 35/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0084WithEmptyValue_443) {
  URationalValue val;
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0085WithValue_443) {
  URationalValue val;
  val.read("10/10");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0086WithValue_443) {
  URationalValue val;
  val.read("1/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0088WithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0089WithZero_443) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0089WithValue_443) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x008bWithValue_443) {
  ByteValue val;
  val.read("0 0 0 0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocusDistanceWithValue_443) {
  ByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocusDistanceWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintApertureWithValue_443) {
  ByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintApertureWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocalWithValue_443) {
  ByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocalWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFStopsWithValue_443) {
  ByteValue val;
  val.read("72");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFStopsWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintExitPupilPositionWithValue_443) {
  ByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintExitPupilPositionWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashFocalLengthWithValue_443) {
  ByteValue val;
  val.read("35");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashFocalLengthWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintRepeatingFlashRateWithValue_443) {
  ByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintRepeatingFlashRateWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintRepeatingFlashCountWithValue_443) {
  ByteValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintRepeatingFlashCountWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x009aWithTwoValues_443) {
  URationalValue val;
  val.read("640/1 480/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, Print0x009aWithOneValue_443) {
  URationalValue val;
  val.read("640/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintTimeZoneWithValue_443) {
  ShortValue val;
  val.read("540");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintTimeZoneWithZero_443) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintTimeZoneWithNegativeValue_443) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintPictureControlWithValue_443) {
  AsciiValue val;
  val.read("STANDARD");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintCameraExposureCompensationWithValue_443) {
  ByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintCameraExposureCompensationWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintLensId1WithValue_443) {
  ByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintLensId2WithValue_443) {
  ByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintLensId3WithValue_443) {
  ByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintLensId4WithValue_443) {
  ByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocusDistanceLd4WithValue_443) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocusDistanceLd4WithZero_443) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintApertureLd4WithValue_443) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintApertureLd4WithZero_443) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocalLd4WithValue_443) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocalLd4WithZero_443) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintLensIdWithGroupString_443) {
  ByteValue val;
  val.read("1");
  std::string group = "NikonLd1";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x009eWithValue_443) {
  UShortValue val;
  val.read("48 48 48 48 48 48 48 48 48 48");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintAf2AreaModeWithValue_443) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashZoomHeadPositionWithValue_443) {
  ByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashZoomHeadPositionWithZero_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintAfPointsInFocusWithNullMetadata_443) {
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for external flash print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_443, PrintExternalFlashData1Fl6WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintExternalFlashData1Fl7WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintExternalFlashData2Fl6WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintExternalFlashData2WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashMasterDataFl6WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashMasterDataFl7WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupAControlDataWithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupBCControlDataWithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupADataFl6WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupADataFl7WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupBDataFl6WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupBDataFl7WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupCDataFl6WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashGroupCDataFl7WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintExternalFlashData3WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintExternalFlashData4WithValue_443) {
  ByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for consistency - calling same function twice gives same result
// ============================================================

TEST_F(Nikon3MakerNoteTest_443, TagListCb2bConsistency_443) {
  auto tagList1 = Nikon3MakerNote::tagListCb2b();
  auto tagList2 = Nikon3MakerNote::tagListCb2b();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(Nikon3MakerNoteTest_443, TagListConsistency_443) {
  auto tagList1 = Nikon3MakerNote::tagList();
  auto tagList2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

// ============================================================
// Boundary tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_443, Print0x0088WithMaxByteValue_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, Print0x0083WithMaxByteValue_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocusDistanceWith255_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintApertureWith255_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocalWith255_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFStopsWith255_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintExitPupilPositionWith255_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFlashFocalLengthWith255_443) {
  ByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocusDistanceLd4WithMaxUShort_443) {
  UShortValue val;
  val.read("65535");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintApertureLd4WithMaxUShort_443) {
  UShortValue val;
  val.read("65535");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintFocalLd4WithMaxUShort_443) {
  UShortValue val;
  val.read("65535");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests with ExifData (non-null metadata)
// ============================================================

TEST_F(Nikon3MakerNoteTest_443, Print0x0089WithExifData_443) {
  UShortValue val;
  val.read("16");
  ExifData metadata;
  auto& result = Nikon3MakerNote::print0x0089(os, val, &metadata);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintAfPointsInFocusWithExifData_443) {
  UShortValue val;
  val.read("7");
  ExifData metadata;
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, &metadata);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_443, PrintAf2AreaModeWithExifData_443) {
  UShortValue val;
  val.read("3");
  ExifData metadata;
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, &metadata);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_443, PrintLensIdWithEmptyGroup_443) {
  ByteValue val;
  val.read("0");
  std::string group = "";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}
