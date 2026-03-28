#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_420 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ========== tagList accessor tests ==========

TEST_F(Nikon3MakerNoteTest_420, TagListVrReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListPcReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListWtReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListIiReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListAfReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListAf21ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListAf22ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListAFTReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListFiReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListMeReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListFl1ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListFl2ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListFl3ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListFl6ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListFl7ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListSi1ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListSi2ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListSi3ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListSi4ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListSi5ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListCb1ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListCb2ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListCb2aReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListCb2bReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListCb3ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListCb4ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListLd1ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListLd2ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListLd3ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_420, TagListLd4ReturnsNonNull_420) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ========== print function tests ==========

TEST_F(Nikon3MakerNoteTest_420, PrintIiIsoWithSingleValue_420) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintIiIsoWithZeroValue_420) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0002WithSingleValue_420) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0002WithMultipleValues_420) {
  UShortValue value;
  value.read("0 1 2");
  Nikon3MakerNote::print0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0007ReturnsStream_420) {
  AsciiValue value;
  value.read("Test Focus");
  auto& ret = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0083WithValue0_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::print0x0083(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0084WithFourRationals_420) {
  URationalValue value;
  value.read("180/10 700/10 35/10 56/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0084WithLessThanFourValues_420) {
  URationalValue value;
  value.read("180/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0085WithValue_420) {
  URationalValue value;
  value.read("10/1");
  Nikon3MakerNote::print0x0085(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0086WithValue_420) {
  URationalValue value;
  value.read("100/1");
  Nikon3MakerNote::print0x0086(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0088WithValue_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::print0x0088(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x0089WithValue_420) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0089(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x008bWithValue_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::print0x008b(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocusDistanceWithValue_420) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocusDistanceWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintApertureWithValue_420) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintApertureWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocalWithValue_420) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocalWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFStopsWithValue_420) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFStopsWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintExitPupilPositionWithValue_420) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintExitPupilPositionWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x009aWithTwoValues_420) {
  URationalValue value;
  value.read("640/1 480/1");
  Nikon3MakerNote::print0x009a(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, Print0x009eWithValue_420) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x009e(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashFocalLengthWithValue_420) {
  UByteValue value;
  value.read("50");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashFocalLengthWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintRepeatingFlashRateWithValue_420) {
  UByteValue value;
  value.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintRepeatingFlashRateWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintRepeatingFlashCountWithValue_420) {
  UByteValue value;
  value.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintRepeatingFlashCountWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintTimeZoneWithValue_420) {
  ShortValue value;
  value.read("540");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintTimeZoneWithZero_420) {
  ShortValue value;
  value.read("0");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintTimeZoneWithNegativeValue_420) {
  ShortValue value;
  value.read("-300");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintLensId1ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintLensId2ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintLensId3ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintLensId4ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintCameraExposureCompensationWithValue_420) {
  UByteValue value;
  value.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintCameraExposureCompensationWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintPictureControlWithValue_420) {
  UByteValue value;
  value.read("128");
  Nikon3MakerNote::printPictureControl(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashZoomHeadPositionWithValue_420) {
  UByteValue value;
  value.read("24");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashZoomHeadPositionWithZero_420) {
  UByteValue value;
  value.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintApertureLd4WithValue_420) {
  UShortValue value;
  value.read("500");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintApertureLd4WithZero_420) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocalLd4WithValue_420) {
  UShortValue value;
  value.read("500");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocalLd4WithZero_420) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocusDistanceLd4WithValue_420) {
  UShortValue value;
  value.read("500");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocusDistanceLd4WithZero_420) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintAfPointsInFocusReturnsStream_420) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintAf2AreaModeWithValue_420) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintLensIdWithGroupParam_420) {
  UByteValue value;
  value.read("0");
  std::string group = "Nikon3";
  auto& ret = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintExternalFlashData1Fl6ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintExternalFlashData1Fl7ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintExternalFlashData2Fl6ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintExternalFlashData2ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashMasterDataFl6ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashMasterDataFl7ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupAControlDataReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupBCControlDataReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupADataFl6ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupADataFl7ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupBDataFl6ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupBDataFl7ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupCDataFl6ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashGroupCDataFl7ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintExternalFlashData3ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_420, PrintExternalFlashData4ReturnsStream_420) {
  UByteValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ========== Consistency tests for tagList functions ==========

TEST_F(Nikon3MakerNoteTest_420, TagListVrConsistentOnMultipleCalls_420) {
  auto tagList1 = Nikon3MakerNote::tagListVr();
  auto tagList2 = Nikon3MakerNote::tagListVr();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(Nikon3MakerNoteTest_420, TagListConsistentOnMultipleCalls_420) {
  auto tagList1 = Nikon3MakerNote::tagList();
  auto tagList2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

// ========== Boundary: large values ==========

TEST_F(Nikon3MakerNoteTest_420, PrintFocusDistanceWithMaxByte_420) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintApertureWithMaxByte_420) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocalWithMaxByte_420) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFStopsWithMaxByte_420) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintExitPupilPositionWithMaxByte_420) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFlashFocalLengthWithMaxByte_420) {
  UByteValue value;
  value.read("255");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintApertureLd4WithMaxUShort_420) {
  UShortValue value;
  value.read("65535");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocalLd4WithMaxUShort_420) {
  UShortValue value;
  value.read("65535");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_420, PrintFocusDistanceLd4WithMaxUShort_420) {
  UShortValue value;
  value.read("65535");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ========== TagInfo first entry checks ==========

TEST_F(Nikon3MakerNoteTest_420, TagListVrFirstEntryHasValidTag_420) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
  // First entry should have a valid tag (non-negative or specific sentinel)
  // We just check it's accessible
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(Nikon3MakerNoteTest_420, TagListFirstEntryHasValidTag_420) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(Nikon3MakerNoteTest_420, TagListLd4FirstEntryHasValidTag_420) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}
