#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_442 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test that tagListCb2a returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListCb2aReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagList returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListVr returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListVrReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListPc returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListPcReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListWt returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListWtReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListIi returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListIiReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAf returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListAfReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAf21 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListAf21ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAf22 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListAf22ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAFT returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListAFTReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFi returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListFiReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListMe returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListMeReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFl1 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListFl1ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFl2 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListFl2ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFl3 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListFl3ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFl6 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListFl6ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFl7 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListFl7ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListSi1 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListSi1ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListSi2 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListSi2ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListSi3 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListSi3ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListSi4 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListSi4ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListSi5 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListSi5ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCb1 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListCb1ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCb2 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListCb2ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCb2b returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListCb2bReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCb3 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListCb3ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCb4 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListCb4ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListLd1 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListLd1ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListLd2 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListLd2ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListLd3 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListLd3ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListLd4 returns a non-null pointer
TEST_F(Nikon3MakerNoteTest_442, TagListLd4ReturnsNonNull_442) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// Test printIiIso with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintIiIsoNormalValue_442) {
  UShortValue val;
  val.read("100");
  std::ostream& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printIiIso with zero value
TEST_F(Nikon3MakerNoteTest_442, PrintIiIsoZeroValue_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0002 with a single value
TEST_F(Nikon3MakerNoteTest_442, Print0x0002SingleValue_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0002 with multiple values
TEST_F(Nikon3MakerNoteTest_442, Print0x0002MultipleValues_442) {
  UShortValue val;
  val.read("2 0 0");
  std::ostream& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0007 with a string value
TEST_F(Nikon3MakerNoteTest_442, Print0x0007Normal_442) {
  AsciiValue val;
  val.read("AF-S");
  std::ostream& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test print0x0083 with a value
TEST_F(Nikon3MakerNoteTest_442, Print0x0083Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0084 with lens specification values
TEST_F(Nikon3MakerNoteTest_442, Print0x0084Normal_442) {
  URationalValue val;
  val.read("180/10 700/10 28/10 40/10");
  std::ostream& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0085 with a focus distance value
TEST_F(Nikon3MakerNoteTest_442, Print0x0085Normal_442) {
  URationalValue val;
  val.read("50/10");
  std::ostream& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0086 with a digital zoom value
TEST_F(Nikon3MakerNoteTest_442, Print0x0086Normal_442) {
  URationalValue val;
  val.read("1/1");
  std::ostream& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0088 with AF info value
TEST_F(Nikon3MakerNoteTest_442, Print0x0088Normal_442) {
  UByteValue val;
  val.read("0 0 0 0");
  std::ostream& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0089 with shooting mode value
TEST_F(Nikon3MakerNoteTest_442, Print0x0089Normal_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x008b with lens info value
TEST_F(Nikon3MakerNoteTest_442, Print0x008bNormal_442) {
  UByteValue val;
  val.read("0 0 0 0");
  std::ostream& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFocusDistance with a byte value
TEST_F(Nikon3MakerNoteTest_442, PrintFocusDistanceNormal_442) {
  UByteValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printFocusDistance with zero (infinity or unknown)
TEST_F(Nikon3MakerNoteTest_442, PrintFocusDistanceZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printAperture with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintApertureNormal_442) {
  UByteValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printAperture with zero
TEST_F(Nikon3MakerNoteTest_442, PrintApertureZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFocal with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintFocalNormal_442) {
  UByteValue val;
  val.read("100");
  std::ostream& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printFocal with zero
TEST_F(Nikon3MakerNoteTest_442, PrintFocalZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFStops with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintFStopsNormal_442) {
  UByteValue val;
  val.read("48");
  std::ostream& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExitPupilPosition with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintExitPupilPositionNormal_442) {
  UByteValue val;
  val.read("10");
  std::ostream& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExitPupilPosition with zero
TEST_F(Nikon3MakerNoteTest_442, PrintExitPupilPositionZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashFocalLength with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashFocalLengthNormal_442) {
  UByteValue val;
  val.read("35");
  std::ostream& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashFocalLength with zero
TEST_F(Nikon3MakerNoteTest_442, PrintFlashFocalLengthZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printRepeatingFlashRate with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintRepeatingFlashRateNormal_442) {
  UByteValue val;
  val.read("10");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printRepeatingFlashRate with zero
TEST_F(Nikon3MakerNoteTest_442, PrintRepeatingFlashRateZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printRepeatingFlashCount with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintRepeatingFlashCountNormal_442) {
  UByteValue val;
  val.read("5");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printRepeatingFlashCount with zero
TEST_F(Nikon3MakerNoteTest_442, PrintRepeatingFlashCountZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x009a with values
TEST_F(Nikon3MakerNoteTest_442, Print0x009aNormal_442) {
  URationalValue val;
  val.read("640/1 480/1");
  std::ostream& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x009e with a value
TEST_F(Nikon3MakerNoteTest_442, Print0x009eNormal_442) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  std::ostream& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printTimeZone with a value
TEST_F(Nikon3MakerNoteTest_442, PrintTimeZoneNormal_442) {
  ShortValue val;
  val.read("540");
  std::ostream& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printTimeZone with zero (UTC)
TEST_F(Nikon3MakerNoteTest_442, PrintTimeZoneZero_442) {
  ShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printTimeZone with negative value
TEST_F(Nikon3MakerNoteTest_442, PrintTimeZoneNegative_442) {
  ShortValue val;
  val.read("-300");
  std::ostream& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printPictureControl with a value
TEST_F(Nikon3MakerNoteTest_442, PrintPictureControlNormal_442) {
  UByteValue val;
  val.read("128");
  std::ostream& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printCameraExposureCompensation
TEST_F(Nikon3MakerNoteTest_442, PrintCameraExposureCompensationNormal_442) {
  UByteValue val;
  val.read("6");
  std::ostream& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printCameraExposureCompensation with zero
TEST_F(Nikon3MakerNoteTest_442, PrintCameraExposureCompensationZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashZoomHeadPosition with normal value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashZoomHeadPositionNormal_442) {
  UByteValue val;
  val.read("24");
  std::ostream& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashZoomHeadPosition with zero
TEST_F(Nikon3MakerNoteTest_442, PrintFlashZoomHeadPositionZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printApertureLd4 with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintApertureLd4Normal_442) {
  UShortValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printApertureLd4 with zero
TEST_F(Nikon3MakerNoteTest_442, PrintApertureLd4Zero_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFocalLd4 with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintFocalLd4Normal_442) {
  UShortValue val;
  val.read("100");
  std::ostream& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFocalLd4 with zero
TEST_F(Nikon3MakerNoteTest_442, PrintFocalLd4Zero_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFocusDistanceLd4 with a normal value
TEST_F(Nikon3MakerNoteTest_442, PrintFocusDistanceLd4Normal_442) {
  UShortValue val;
  val.read("200");
  std::ostream& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFocusDistanceLd4 with zero
TEST_F(Nikon3MakerNoteTest_442, PrintFocusDistanceLd4Zero_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printLensId1 with nullptr metadata
TEST_F(Nikon3MakerNoteTest_442, PrintLensId1NullMetadata_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printLensId2 with nullptr metadata
TEST_F(Nikon3MakerNoteTest_442, PrintLensId2NullMetadata_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printLensId3 with nullptr metadata
TEST_F(Nikon3MakerNoteTest_442, PrintLensId3NullMetadata_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printLensId4 with nullptr metadata
TEST_F(Nikon3MakerNoteTest_442, PrintLensId4NullMetadata_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printAfPointsInFocus with nullptr metadata
TEST_F(Nikon3MakerNoteTest_442, PrintAfPointsInFocusNullMetadata_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printAf2AreaMode with nullptr metadata
TEST_F(Nikon3MakerNoteTest_442, PrintAf2AreaModeNullMetadata_442) {
  UShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExternalFlashData1Fl6 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintExternalFlashData1Fl6Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExternalFlashData1Fl7 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintExternalFlashData1Fl7Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExternalFlashData2Fl6 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintExternalFlashData2Fl6Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExternalFlashData2 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintExternalFlashData2Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashMasterDataFl6 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashMasterDataFl6Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashMasterDataFl7 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashMasterDataFl7Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupAControlData with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupAControlDataNormal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupBCControlData with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupBCControlDataNormal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupADataFl6 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupADataFl6Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupADataFl7 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupADataFl7Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupBDataFl6 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupBDataFl6Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupBDataFl7 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupBDataFl7Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupCDataFl6 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupCDataFl6Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFlashGroupCDataFl7 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintFlashGroupCDataFl7Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExternalFlashData3 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintExternalFlashData3Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printExternalFlashData4 with a value
TEST_F(Nikon3MakerNoteTest_442, PrintExternalFlashData4Normal_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printLensId with an empty group string
TEST_F(Nikon3MakerNoteTest_442, PrintLensIdEmptyGroup_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printLensId(os, val, nullptr, "");
  EXPECT_EQ(&result, &os);
}

// Test printLensId with a group string
TEST_F(Nikon3MakerNoteTest_442, PrintLensIdWithGroup_442) {
  UByteValue val;
  val.read("1");
  std::ostream& result = Nikon3MakerNote::printLensId(os, val, nullptr, "NikonLd1");
  EXPECT_EQ(&result, &os);
}

// Test output stream returns same reference for chaining
TEST_F(Nikon3MakerNoteTest_442, OutputStreamReturnsSameRef_442) {
  UByteValue val;
  val.read("128");
  std::ostream& ref1 = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&ref1, &os);
}

// Test printFStops with boundary value 0
TEST_F(Nikon3MakerNoteTest_442, PrintFStopsZero_442) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFStops with max byte value
TEST_F(Nikon3MakerNoteTest_442, PrintFStopsMax_442) {
  UByteValue val;
  val.read("255");
  std::ostream& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFocusDistance with max byte value
TEST_F(Nikon3MakerNoteTest_442, PrintFocusDistanceMax_442) {
  UByteValue val;
  val.read("255");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0084 with insufficient components
TEST_F(Nikon3MakerNoteTest_442, Print0x0084InsufficientComponents_442) {
  URationalValue val;
  val.read("180/10");
  std::ostream& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0084 with zero denominator rational
TEST_F(Nikon3MakerNoteTest_442, Print0x0084ZeroDenominator_442) {
  URationalValue val;
  val.read("0/0 0/0 0/0 0/0");
  std::ostream& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}
