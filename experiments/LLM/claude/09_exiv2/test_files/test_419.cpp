#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_419 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// tagList tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, TagListIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagList();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListVrIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListPcIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListWtIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListIiIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListAfIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListAf21IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListAf22IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListAFTIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListFiIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListMeIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListFl1IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListFl2IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListFl3IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListFl6IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListFl7IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListSi1IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListSi2IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListSi3IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListSi4IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListSi5IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListCb1IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListCb2IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListCb2aIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListCb2bIsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListCb3IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListCb4IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListLd1IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListLd2IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListLd3IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_419, TagListLd4IsNotNull_419) {
  auto tags = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tags, nullptr);
}

// ============================================================
// print function tests - IiIso
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintIiIsoWithSingleValue_419) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintIiIsoWithNonZeroValue_419) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0002 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0002WithThreeValues_419) {
  UShortValue val;
  val.read("0 1 6");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, Print0x0002WithOneValue_419) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0007 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0007WithStringValue_419) {
  AsciiValue val;
  val.read("AF-S");
  Nikon3MakerNote::print0x0007(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0083 tests - Lens Type
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0083WithZeroValue_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, Print0x0083WithNonZeroValue_419) {
  UByteValue val;
  val.read("6");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0084 tests - Lens info
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0084WithFourRationalValues_419) {
  URationalValue val;
  val.read("240/10 700/10 40/10 56/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, Print0x0084WithFewerThanFourValues_419) {
  URationalValue val;
  val.read("240/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0085 tests - ManualFocusDistance
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0085WithZero_419) {
  URationalValue val;
  val.read("0/1");
  Nikon3MakerNote::print0x0085(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, Print0x0085WithNonZero_419) {
  URationalValue val;
  val.read("500/100");
  Nikon3MakerNote::print0x0085(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0086 tests - DigitalZoom
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0086WithZero_419) {
  URationalValue val;
  val.read("0/1");
  Nikon3MakerNote::print0x0086(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, Print0x0086WithNonZero_419) {
  URationalValue val;
  val.read("200/100");
  Nikon3MakerNote::print0x0086(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0088 tests - AF Info
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0088WithSingleValue_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0089 tests - Shooting mode
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x0089WithZeroValue_419) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, Print0x0089WithNonZeroValue_419) {
  UShortValue val;
  val.read("1");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x008b tests - Lens F-Stops
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x008bWithValues_419) {
  UByteValue val;
  val.read("6 1 12");
  Nikon3MakerNote::print0x008b(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printFocusDistance tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFocusDistanceWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintFocusDistanceWithNonZero_419) {
  UByteValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printAperture tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintApertureWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintApertureWithNonZero_419) {
  UByteValue val;
  val.read("40");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printFocal tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFocalWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintFocalWithNonZero_419) {
  UByteValue val;
  val.read("50");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printFStops tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFStopsWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintFStopsWithNonZero_419) {
  UByteValue val;
  val.read("48");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printExitPupilPosition tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintExitPupilPositionWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintExitPupilPositionWithNonZero_419) {
  UByteValue val;
  val.read("100");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printFlashFocalLength tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFlashFocalLengthWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintFlashFocalLengthWithNonZero_419) {
  UByteValue val;
  val.read("35");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printRepeatingFlashRate tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintRepeatingFlashRateWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintRepeatingFlashRateWithNonZero_419) {
  UByteValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printRepeatingFlashCount tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintRepeatingFlashCountWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintRepeatingFlashCountWithNonZero_419) {
  UByteValue val;
  val.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x009a tests - Image Size
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x009aWithTwoValues_419) {
  URationalValue val;
  val.read("4000/1 6000/1");
  Nikon3MakerNote::print0x009a(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, Print0x009aWithOneValue_419) {
  URationalValue val;
  val.read("4000/1");
  Nikon3MakerNote::print0x009a(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x009e tests - Retouch History
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, Print0x009eWithValues_419) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x009e(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printTimeZone tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintTimeZoneWithZero_419) {
  ShortValue val;
  val.read("0");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintTimeZoneWithPositive_419) {
  ShortValue val;
  val.read("60");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintTimeZoneWithNegative_419) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printPictureControl tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintPictureControlWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printPictureControl(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printLensId tests (the variant with group parameter)
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintLensIdWithEmptyGroup_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId(os, val, nullptr, "");
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printLensId1 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintLensId1_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId1(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printLensId2 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintLensId2_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId2(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printLensId3 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintLensId3_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId3(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printCameraExposureCompensation tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintCameraExposureCompensationZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintCameraExposureCompensationNonZero_419) {
  UByteValue val;
  val.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printFlashZoomHeadPosition tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFlashZoomHeadPositionZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printApertureLd4 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintApertureLd4Zero_419) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintApertureLd4NonZero_419) {
  UShortValue val;
  val.read("500");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printFocalLd4 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFocalLd4Zero_419) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintFocalLd4NonZero_419) {
  UShortValue val;
  val.read("500");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printFocusDistanceLd4 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFocusDistanceLd4Zero_419) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintFocusDistanceLd4NonZero_419) {
  UShortValue val;
  val.read("1000");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printAf2AreaMode tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintAf2AreaModeWithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printAfPointsInFocus tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintAfPointsInFocusWithZero_419) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Return value is same ostream reference
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFunctionsReturnSameStream_419) {
  UByteValue val;
  val.read("0");
  std::ostream& ret = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_419, PrintApertureReturnsSameStream_419) {
  UByteValue val;
  val.read("0");
  std::ostream& ret = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_419, PrintFocalReturnsSameStream_419) {
  UByteValue val;
  val.read("0");
  std::ostream& ret = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_419, Print0x0083ReturnsSameStream_419) {
  UByteValue val;
  val.read("0");
  std::ostream& ret = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// printExternalFlashData tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintExternalFlashData2WithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintExternalFlashData3WithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_419, PrintExternalFlashData4WithZero_419) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Boundary: 255 byte value for focus distance
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFocusDistanceMaxByte_419) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Boundary: 255 byte value for aperture
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintApertureMaxByte_419) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Boundary: 255 byte value for focal
// ============================================================

TEST_F(Nikon3MakerNoteTest_419, PrintFocalMaxByte_419) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
