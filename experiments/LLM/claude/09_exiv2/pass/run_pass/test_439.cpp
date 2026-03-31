#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_439 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(Nikon3MakerNoteTest_439, TagListReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagList();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListVrReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListPcReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListWtReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListIiReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListAfReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListAf21ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListAf22ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListAFTReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListFiReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListMeReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListFl1ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListFl2ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListFl3ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListFl6ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListFl7ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListSi1ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListSi2ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListSi3ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListSi4ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListSi5ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListCb1ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListCb2ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListCb2aReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListCb2bReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListCb3ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListCb4ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListLd1ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListLd2ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListLd3ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_439, TagListLd4ReturnsNonNull_439) {
  auto tags = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tags, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_439, PrintIiIsoWithSingleValue_439) {
  UShortValue value;
  value.read("256");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintIiIsoWithZeroValue_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0002SingleValue_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0002MultipleValues_439) {
  UShortValue value;
  value.read("2 0 6");
  Nikon3MakerNote::print0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0007ReturnsStream_439) {
  AsciiValue value;
  value.read("FINE   ");
  auto& ret = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0083WithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0083(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0084WithFourValues_439) {
  URationalValue value;
  value.read("240/10 700/10 28/10 40/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0084WithTwoValues_439) {
  URationalValue value;
  value.read("500/10 500/10 28/10 28/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0085ReturnsStream_439) {
  URationalValue value;
  value.read("10/1");
  auto& ret = Nikon3MakerNote::print0x0085(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0086ReturnsStream_439) {
  URationalValue value;
  value.read("10/1");
  auto& ret = Nikon3MakerNote::print0x0086(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0088WithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0089WithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x008bWithValue_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x008b(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocusDistanceWithValue_439) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocusDistanceWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintApertureWithValue_439) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintApertureWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocalWithValue_439) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocalWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFStopsWithValue_439) {
  UShortValue value;
  value.read("72");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFStopsWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintExitPupilPositionWithValue_439) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintExitPupilPositionWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashFocalLengthWithValue_439) {
  UShortValue value;
  value.read("35");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashFocalLengthWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashRateWithValue_439) {
  UShortValue value;
  value.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashRateWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashCountWithValue_439) {
  UShortValue value;
  value.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashCountWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x009aWithTwoRationalValues_439) {
  URationalValue value;
  value.read("3008/1 2000/1");
  Nikon3MakerNote::print0x009a(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x009eWithValue_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::print0x009e(os, value, nullptr);
  // Just ensure no crash
}

TEST_F(Nikon3MakerNoteTest_439, PrintTimeZoneWithValue_439) {
  ShortValue value;
  value.read("540");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintTimeZoneWithNegativeValue_439) {
  ShortValue value;
  value.read("-300");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintTimeZoneWithZero_439) {
  ShortValue value;
  value.read("0");
  Nikon3MakerNote::printTimeZone(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintCameraExposureCompensationValue_439) {
  UShortValue value;
  value.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintCameraExposureCompensationZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocusDistanceLd4WithValue_439) {
  UShortValue value;
  value.read("1000");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocusDistanceLd4WithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintApertureLd4WithValue_439) {
  UShortValue value;
  value.read("100");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintApertureLd4WithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocalLd4WithValue_439) {
  UShortValue value;
  value.read("200");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocalLd4WithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashZoomHeadPositionWithValue_439) {
  UShortValue value;
  value.read("50");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashZoomHeadPositionWithZero_439) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintPictureControlWithValue_439) {
  UShortValue value;
  value.read("128");
  Nikon3MakerNote::printPictureControl(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintLensId1ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintLensId2ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintLensId3ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintLensId4ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintLensIdWithGroupReturnsStream_439) {
  UShortValue value;
  value.read("0");
  std::string group = "Nikon3";
  auto& ret = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintAfPointsInFocusReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintAf2AreaModeReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData1Fl6ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData1Fl7ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData2Fl6ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData2ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashMasterDataFl6ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashMasterDataFl7ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupAControlDataReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupBCControlDataReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupADataFl6ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupADataFl7ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupBDataFl6ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupBDataFl7ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupCDataFl6ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupCDataFl7ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData3ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData4ReturnsStream_439) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Boundary / Edge case tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_439, PrintFocusDistanceMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintApertureMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printAperture(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFocalMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFocal(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0083WithVariousFlags_439) {
  UShortValue value;
  value.read("14");
  Nikon3MakerNote::print0x0083(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0088WithKnownValue_439) {
  UShortValue value;
  value.read("1");
  Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0089WithKnownShootingMode_439) {
  UShortValue value;
  value.read("1");
  Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintFStopsMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintExitPupilPositionMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, Print0x0084WithOneValue_439) {
  URationalValue value;
  value.read("500/10");
  Nikon3MakerNote::print0x0084(os, value, nullptr);
  // With less than expected values, function should still handle gracefully
}

TEST_F(Nikon3MakerNoteTest_439, PrintFlashFocalLengthMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashRateMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashCountMaxByte_439) {
  UShortValue value;
  value.read("255");
  Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
