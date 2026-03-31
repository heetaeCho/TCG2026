#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_428 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ==================== tagList tests ====================

TEST_F(Nikon3MakerNoteTest_428, TagListFiIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListVrIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListPcIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListWtIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListIiIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListAfIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListAf21IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListAf22IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListAFTIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListMeIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListFl1IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListFl2IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListFl3IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListFl6IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListFl7IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListSi1IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListSi2IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListSi3IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListSi4IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListSi5IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListCb1IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListCb2IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListCb2aIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListCb2bIsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListCb3IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListCb4IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListLd1IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListLd2IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListLd3IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_428, TagListLd4IsNotNull_428) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ==================== print function tests ====================

TEST_F(Nikon3MakerNoteTest_428, PrintIiIsoWithSingleValue_428) {
  UShortValue value;
  value.read("256");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintIiIsoWithZeroValue_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0002WithSingleValue_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0002WithThreeValues_428) {
  UShortValue value;
  value.read("0 2 6");
  Nikon3MakerNote::print0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0007ReturnsStream_428) {
  AsciiValue value;
  value.read("FINE");
  Nikon3MakerNote::print0x0007(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0083WithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::print0x0083(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0084WithFourValues_428) {
  URationalValue value;
  value.read("240/10 700/10 28/10 45/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0084WithTwoValues_428) {
  URationalValue value;
  value.read("240/10 700/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0085ReturnsStream_428) {
  URationalValue value;
  value.read("100/100");
  Nikon3MakerNote::print0x0085(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0086ReturnsStream_428) {
  URationalValue value;
  value.read("10/1");
  Nikon3MakerNote::print0x0086(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0088WithSingleValue_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::print0x0088(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0089WithZeroValue_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0089(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x008bWithSingleValue_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::print0x008b(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocusDistanceWithValue_428) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocusDistanceWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintApertureWithValue_428) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintApertureWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocalWithValue_428) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocalWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFStopsWithValue_428) {
  UByteValue value;
  value.read("48");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFStopsWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExitPupilPositionWithValue_428) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExitPupilPositionWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashFocalLengthWithValue_428) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashFocalLengthWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintRepeatingFlashRateWithValue_428) {
  UByteValue value;
  value.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintRepeatingFlashRateWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintRepeatingFlashCountWithValue_428) {
  UByteValue value;
  value.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintRepeatingFlashCountWithZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x009aWithTwoValues_428) {
  URationalValue value;
  value.read("0/1 0/1");
  Nikon3MakerNote::print0x009a(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x009eWithSingleValue_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x009e(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintTimeZoneReturnsStream_428) {
  ShortValue value;
  value.read("540");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintTimeZoneNegativeOffset_428) {
  ShortValue value;
  value.read("-300");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintTimeZoneZero_428) {
  ShortValue value;
  value.read("0");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintCameraExposureCompensation_428) {
  UByteValue value;
  value.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintCameraExposureCompensationZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocusDistanceLd4_428) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocusDistanceLd4Zero_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintApertureLd4_428) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintApertureLd4Zero_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocalLd4_428) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocalLd4Zero_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintPictureControlWithValue_428) {
  UByteValue value;
  value.read("128");
  Nikon3MakerNote::printPictureControl(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashZoomHeadPositionWithValue_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashZoomHeadPositionNonZero_428) {
  UByteValue value;
  value.read("24");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintLensId1WithNullMetadata_428) {
  UByteValue value;
  value.read("1");
  Nikon3MakerNote::printLensId1(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintLensId2WithNullMetadata_428) {
  UByteValue value;
  value.read("1");
  Nikon3MakerNote::printLensId2(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintLensId3WithNullMetadata_428) {
  UByteValue value;
  value.read("1");
  Nikon3MakerNote::printLensId3(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintLensId4WithNullMetadata_428) {
  UByteValue value;
  value.read("1");
  Nikon3MakerNote::printLensId4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintLensIdWithEmptyGroup_428) {
  UByteValue value;
  value.read("1");
  std::string group;
  Nikon3MakerNote::printLensId(os, value, nullptr, group);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintAfPointsInFocusWithNullMetadata_428) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintAf2AreaModeWithNullMetadata_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test that print functions return a reference to the same ostream
TEST_F(Nikon3MakerNoteTest_428, PrintFocusDistanceReturnsSameStream_428) {
  UByteValue value;
  value.read("50");
  std::ostream& returned = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

TEST_F(Nikon3MakerNoteTest_428, PrintApertureReturnsSameStream_428) {
  UByteValue value;
  value.read("50");
  std::ostream& returned = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocalReturnsSameStream_428) {
  UByteValue value;
  value.read("50");
  std::ostream& returned = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

TEST_F(Nikon3MakerNoteTest_428, PrintFStopsReturnsSameStream_428) {
  UByteValue value;
  value.read("48");
  std::ostream& returned = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

TEST_F(Nikon3MakerNoteTest_428, PrintIiIsoReturnsSameStream_428) {
  UShortValue value;
  value.read("100");
  std::ostream& returned = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

TEST_F(Nikon3MakerNoteTest_428, PrintTimeZoneReturnsSameStream_428) {
  ShortValue value;
  value.read("0");
  std::ostream& returned = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test with ExifData (non-null)
TEST_F(Nikon3MakerNoteTest_428, PrintLensId1WithExifData_428) {
  ExifData exifData;
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printLensId1(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintLensId2WithExifData_428) {
  ExifData exifData;
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printLensId2(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0089WithExifData_428) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  Nikon3MakerNote::print0x0089(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Boundary test for values at extremes
TEST_F(Nikon3MakerNoteTest_428, PrintFocusDistanceMaxByte_428) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintApertureMaxByte_428) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFocalMaxByte_428) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFStopsMaxByte_428) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0083MultipleBits_428) {
  UByteValue value;
  value.read("14");
  Nikon3MakerNote::print0x0083(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, Print0x0088MultipleValues_428) {
  UByteValue value;
  value.read("0 1 2 3");
  Nikon3MakerNote::print0x0088(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintPictureControlZero_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printPictureControl(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExternalFlashData1Fl6_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExternalFlashData1Fl7_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExternalFlashData2Fl6_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExternalFlashData2_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExternalFlashData3_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintExternalFlashData4_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashMasterDataFl6_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashMasterDataFl7_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupAControlData_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupBCControlData_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupADataFl6_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupADataFl7_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupBDataFl6_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupBDataFl7_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupCDataFl6_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_428, PrintFlashGroupCDataFl7_428) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
