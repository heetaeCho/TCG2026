#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_440 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// tagList functions - verify they return non-null pointers
// =============================================================================

TEST_F(Nikon3MakerNoteTest_440, TagListCb1ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListVrReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListPcReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListWtReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListIiReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListAfReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListAf21ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListAf22ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListAFTReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListFiReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListMeReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListFl1ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListFl2ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListFl3ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListFl6ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListFl7ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListSi1ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListSi2ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListSi3ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListSi4ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListSi5ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListCb2ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListCb2aReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListCb2bReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListCb3ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListCb4ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListLd1ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListLd2ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListLd3ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_440, TagListLd4ReturnsNonNull_440) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Print functions - test with various values
// =============================================================================

TEST_F(Nikon3MakerNoteTest_440, PrintIiIsoWithValidValue_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should be non-empty or at least not crash
}

TEST_F(Nikon3MakerNoteTest_440, PrintIiIsoWithNonZeroValue_440) {
  UShortValue value;
  value.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0002WithSingleValue_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0002WithMultipleValues_440) {
  UShortValue value;
  value.read("2 0 0");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0007WithValue_440) {
  AsciiValue value;
  value.read("AF-S");
  auto& result = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0083WithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0083WithValue_440) {
  UByteValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0084WithFourValues_440) {
  URationalValue value;
  value.read("180/10 700/10 28/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0084WithTwoValues_440) {
  URationalValue value;
  value.read("500/10 500/10 28/10 28/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0085WithValue_440) {
  URationalValue value;
  value.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0086WithValue_440) {
  URationalValue value;
  value.read("100/100");
  auto& result = Nikon3MakerNote::print0x0086(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0088WithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0088WithNonZero_440) {
  UByteValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x0089WithValue_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x008bWithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocusDistanceWithValue_440) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocusDistanceWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintApertureWithValue_440) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, PrintApertureWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocalWithValue_440) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocalWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFStopsWithValue_440) {
  UByteValue value;
  value.read("72");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFStopsWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExitPupilPositionWithValue_440) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExitPupilPositionWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashFocalLengthWithValue_440) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashFocalLengthWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintRepeatingFlashRateWithValue_440) {
  UByteValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintRepeatingFlashRateWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintRepeatingFlashCountWithValue_440) {
  UByteValue value;
  value.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintRepeatingFlashCountWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintTimeZoneWithValue_440) {
  ShortValue value;
  value.read("60");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, PrintTimeZoneWithNegativeValue_440) {
  ShortValue value;
  value.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_440, PrintTimeZoneWithZero_440) {
  ShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x009aWithTwoValues_440) {
  URationalValue value;
  value.read("300/100 300/100");
  auto& result = Nikon3MakerNote::print0x009a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, Print0x009eWithValue_440) {
  UShortValue value;
  value.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = Nikon3MakerNote::print0x009e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintPictureControlWithValue_440) {
  UByteValue value;
  value.read("128");
  auto& result = Nikon3MakerNote::printPictureControl(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintCameraExposureCompensationWithValue_440) {
  UByteValue value;
  value.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintCameraExposureCompensationWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintLensId1WithValue_440) {
  UByteValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintLensId2WithValue_440) {
  UByteValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintLensId3WithValue_440) {
  UByteValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintLensId4WithValue_440) {
  UByteValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintLensIdWithGroupValue_440) {
  UByteValue value;
  value.read("1");
  std::string group = "NikonLd1";
  auto& result = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintAfPointsInFocusWithValue_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintAf2AreaModeWithValue_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashZoomHeadPositionWithValue_440) {
  UByteValue value;
  value.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashZoomHeadPositionWithZero_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintApertureLd4WithValue_440) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintApertureLd4WithZero_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocalLd4WithValue_440) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocalLd4WithZero_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocusDistanceLd4WithValue_440) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocusDistanceLd4WithZero_440) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Flash-related print functions
// =============================================================================

TEST_F(Nikon3MakerNoteTest_440, PrintExternalFlashData1Fl6WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExternalFlashData1Fl7WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExternalFlashData2Fl6WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExternalFlashData2WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashMasterDataFl6WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashMasterDataFl7WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupAControlDataWithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupBCControlDataWithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupADataFl6WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupADataFl7WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupBDataFl6WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupBDataFl7WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupCDataFl6WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupCDataFl7WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExternalFlashData3WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExternalFlashData4WithValue_440) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary/edge cases
// =============================================================================

TEST_F(Nikon3MakerNoteTest_440, PrintFocusDistanceWith255_440) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintApertureWith255_440) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocalWith255_440) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFStopsWith255_440) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintExitPupilPositionWith255_440) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocusDistanceLd4WithMaxUShort_440) {
  UShortValue value;
  value.read("65535");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintApertureLd4WithMaxUShort_440) {
  UShortValue value;
  value.read("65535");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintFocalLd4WithMaxUShort_440) {
  UShortValue value;
  value.read("65535");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Ensure stream is returned properly when called with ExifData
TEST_F(Nikon3MakerNoteTest_440, Print0x0089WithExifData_440) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  auto& result = Nikon3MakerNote::print0x0089(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_440, PrintAfPointsInFocusWithExifData_440) {
  UShortValue value;
  value.read("255");
  ExifData exifData;
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Verify stream output is chained correctly
// =============================================================================

TEST_F(Nikon3MakerNoteTest_440, StreamChainingWorks_440) {
  UByteValue value;
  value.read("50");
  std::ostringstream os1, os2;
  Nikon3MakerNote::printFocusDistance(os1, value, nullptr);
  Nikon3MakerNote::printAperture(os2, value, nullptr);
  // Both should have produced some output
  EXPECT_FALSE(os1.str().empty());
  EXPECT_FALSE(os2.str().empty());
}
