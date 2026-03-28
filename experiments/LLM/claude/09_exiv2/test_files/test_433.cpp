#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_433 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// tagList* tests - verify they return non-null tag info arrays
// ============================================================

TEST_F(Nikon3MakerNoteTest_433, TagListFl6ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagList();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListVrReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListVr();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListPcReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListPc();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListWtReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListWt();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListIiReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListIi();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListAfReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListAf();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListAf21ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListAf22ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListAFTReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListFiReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListFi();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListMeReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListMe();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListFl1ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListFl2ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListFl3ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListFl7ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListSi1ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListSi2ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListSi3ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListSi4ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListSi5ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListCb1ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListCb2ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListCb2aReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListCb2bReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListCb3ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListCb4ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListLd1ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListLd2ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListLd3ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_433, TagListLd4ReturnsNonNull_433) {
  auto result = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(result, nullptr);
}

// ============================================================
// Print function tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_433, PrintIiIsoWithValidValue_433) {
  UShortValue val;
  val.read("256");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintIiIsoWithZeroValue_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0002WithSingleValue_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0002WithMultipleValues_433) {
  UShortValue val;
  val.read("0 2 0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0007ReturnsStream_433) {
  AsciiValue val;
  val.read("FINE");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0083WithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0084WithFourValues_433) {
  URationalValue val;
  val.read("240/10 700/10 35/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0084WithTwoValues_433) {
  URationalValue val;
  val.read("240/10 700/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0085WithValidValue_433) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0086WithValidValue_433) {
  URationalValue val;
  val.read("12/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0088WithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0089WithSingleValue_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x008bReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocusDistanceWithValue_433) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocusDistanceWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintApertureWithValidValue_433) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintApertureWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocalWithValidValue_433) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocalWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFStopsWithValidValue_433) {
  UByteValue val;
  val.read("72");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintFStopsWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintExitPupilPositionWithValue_433) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintExitPupilPositionWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashFocalLengthWithValue_433) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashFocalLengthWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintRepeatingFlashRateWithValue_433) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintRepeatingFlashRateWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintRepeatingFlashCountWithValue_433) {
  UByteValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintRepeatingFlashCountWithZero_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintTimeZoneReturnsStream_433) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintTimeZoneNegativeOffset_433) {
  ShortValue val;
  val.read("-60");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintPictureControlReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x009aWithTwoValues_433) {
  URationalValue val;
  val.read("100/1 100/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x009eWithValues_433) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintCameraExposureCompensationReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashZoomHeadPositionReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocusDistanceLd4ReturnsStream_433) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintApertureLd4ReturnsStream_433) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocalLd4ReturnsStream_433) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, PrintLensId1WithNullMetadata_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintLensId2WithNullMetadata_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintLensId3WithNullMetadata_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintLensId4WithNullMetadata_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintLensIdWithGroupAndNullMetadata_433) {
  UByteValue val;
  val.read("0");
  std::string group = "Nikon3";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintAfPointsInFocusWithNullMetadata_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintAf2AreaModeWithNullMetadata_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintExternalFlashData1Fl6ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintExternalFlashData1Fl7ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintExternalFlashData2Fl6ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintExternalFlashData2ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashMasterDataFl6ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashMasterDataFl7ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupAControlDataReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupBCControlDataReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupADataFl6ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupADataFl7ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupBDataFl6ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupBDataFl7ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupCDataFl6ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFlashGroupCDataFl7ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintExternalFlashData3ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintExternalFlashData4ReturnsStream_433) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests with specific values
// ============================================================

TEST_F(Nikon3MakerNoteTest_433, PrintFocusDistanceWithMaxByte_433) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintApertureWithMaxByte_433) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocalWithMaxByte_433) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFStopsWithMaxByte_433) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocusDistanceLd4WithZero_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintApertureLd4WithZero_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintFocalLd4WithZero_433) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0083WithNonZeroValue_433) {
  UByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0088WithNonZeroValue_433) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests with ExifData (non-null metadata)
// ============================================================

TEST_F(Nikon3MakerNoteTest_433, PrintLensId1WithEmptyExifData_433) {
  ExifData exifData;
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintLensId2WithEmptyExifData_433) {
  ExifData exifData;
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, Print0x0089WithEmptyExifData_433) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintAfPointsInFocusWithEmptyExifData_433) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_433, PrintAf2AreaModeWithEmptyExifData_433) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}
