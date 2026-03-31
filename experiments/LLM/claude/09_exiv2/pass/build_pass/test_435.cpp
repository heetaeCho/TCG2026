#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_435 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// ========== Tag list accessor tests ==========

TEST_F(Nikon3MakerNoteTest_435, TagListSi1ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListVrReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListPcReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListWtReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListIiReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListAfReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListAf21ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListAf22ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListAFTReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListFiReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListMeReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListFl1ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListFl2ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListFl3ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListFl6ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListFl7ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListSi2ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListSi3ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListSi4ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListSi5ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListCb1ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListCb2ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListCb2aReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListCb2bReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListCb3ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListCb4ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListLd1ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListLd2ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListLd3ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_435, TagListLd4ReturnsNonNull_435) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ========== Print function tests ==========

TEST_F(Nikon3MakerNoteTest_435, PrintIiIsoWithSingleValue_435) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printIiIso(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0002WithSingleValue_435) {
  AsciiValue value;
  value.read("0210");
  Nikon3MakerNote::print0x0002(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0007ReturnsOutputStream_435) {
  AsciiValue value;
  value.read("FINE");
  auto& ret = Nikon3MakerNote::print0x0007(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0083WithZeroValue_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0083(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0084WithFourValues_435) {
  URationalValue value;
  value.read("240/10 700/10 28/10 28/10");
  Nikon3MakerNote::print0x0084(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0085WithValue_435) {
  URationalValue value;
  value.read("50/10");
  Nikon3MakerNote::print0x0085(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0086WithValue_435) {
  URationalValue value;
  value.read("12/1");
  Nikon3MakerNote::print0x0086(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0088WithValue_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0088(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0089WithValue_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0089(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x008bWithValue_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x008b(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocusDistanceWithValue_435) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printFocusDistance(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocusDistanceWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistance(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintApertureWithValue_435) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printAperture(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintApertureWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printAperture(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocalWithValue_435) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printFocal(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocalWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocal(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFStopsWithValue_435) {
  UShortValue value;
  value.read("72");
  Nikon3MakerNote::printFStops(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFStopsWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFStops(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintExitPupilPositionWithValue_435) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printExitPupilPosition(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintExitPupilPositionWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printExitPupilPosition(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFlashFocalLengthWithValue_435) {
  UShortValue value;
  value.read("24");
  Nikon3MakerNote::printFlashFocalLength(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFlashFocalLengthWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFlashFocalLength(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintRepeatingFlashRateWithValue_435) {
  UShortValue value;
  value.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintRepeatingFlashRateWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintRepeatingFlashCountWithValue_435) {
  UShortValue value;
  value.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintRepeatingFlashCountWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x009aWithTwoValues_435) {
  URationalValue value;
  value.read("300/100 200/100");
  Nikon3MakerNote::print0x009a(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintTimeZoneWithValue_435) {
  ShortValue value;
  value.read("540");
  Nikon3MakerNote::printTimeZone(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintTimeZoneWithZero_435) {
  ShortValue value;
  value.read("0");
  Nikon3MakerNote::printTimeZone(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintTimeZoneWithNegativeValue_435) {
  ShortValue value;
  value.read("-300");
  Nikon3MakerNote::printTimeZone(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintCameraExposureCompensationWithValue_435) {
  UShortValue value;
  value.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintCameraExposureCompensationWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocusDistanceLd4WithValue_435) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printFocusDistanceLd4(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintApertureLd4WithValue_435) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printApertureLd4(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocalLd4WithValue_435) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printFocalLd4(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintLensId1WithValue_435) {
  UShortValue value;
  value.read("1");
  Nikon3MakerNote::printLensId1(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintLensId2WithValue_435) {
  UShortValue value;
  value.read("1");
  Nikon3MakerNote::printLensId2(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintLensId3WithValue_435) {
  UShortValue value;
  value.read("1");
  Nikon3MakerNote::printLensId3(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintLensId4WithValue_435) {
  UShortValue value;
  value.read("1");
  Nikon3MakerNote::printLensId4(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintLensIdWithValueAndGroup_435) {
  UShortValue value;
  value.read("1");
  std::string group = "Nikon3";
  Nikon3MakerNote::printLensId(os_, value, nullptr, group);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintPictureControlWithValue_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printPictureControl(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFlashZoomHeadPositionWithValue_435) {
  UShortValue value;
  value.read("24");
  Nikon3MakerNote::printFlashZoomHeadPosition(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFlashZoomHeadPositionWithZero_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// Test return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_435, PrintFocusDistanceReturnsSameStream_435) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, PrintApertureReturnsSameStream_435) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printAperture(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocalReturnsSameStream_435) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFocal(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, PrintFStopsReturnsSameStream_435) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFStops(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, PrintIiIsoReturnsSameStream_435) {
  UShortValue value;
  value.read("100");
  auto& ret = Nikon3MakerNote::printIiIso(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0083ReturnsSameStream_435) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x0083(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0088ReturnsSameStream_435) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x0088(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

TEST_F(Nikon3MakerNoteTest_435, PrintTimeZoneReturnsSameStream_435) {
  ShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printTimeZone(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

// Test with boundary values
TEST_F(Nikon3MakerNoteTest_435, PrintFocusDistanceMaxByte_435) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFocusDistance(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintApertureMaxByte_435) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printAperture(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintFocalMaxByte_435) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFocal(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0084WithTwoValues_435) {
  URationalValue value;
  value.read("240/10 700/10");
  Nikon3MakerNote::print0x0084(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x0084WithSingleValue_435) {
  URationalValue value;
  value.read("240/10");
  Nikon3MakerNote::print0x0084(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintAfPointsInFocusWithNullMetadata_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, PrintAf2AreaModeWithNullMetadata_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printAf2AreaMode(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_435, Print0x009eWithValue_435) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x009e(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}
