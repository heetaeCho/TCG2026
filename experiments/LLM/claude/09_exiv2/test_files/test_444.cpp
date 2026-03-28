#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_444 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// tagList accessor tests
// =============================================================================

TEST_F(Nikon3MakerNoteTest_444, TagListCb3IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListVrIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListPcIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListWtIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListIiIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListAfIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListAf21IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListAf22IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListAFTIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListFiIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListMeIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListFl1IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListFl2IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListFl3IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListFl6IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListFl7IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListSi1IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListSi2IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListSi3IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListSi4IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListSi5IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListCb1IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListCb2IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListCb2aIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListCb2bIsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListCb4IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListLd1IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListLd2IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListLd3IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_444, TagListLd4IsNotNull_444) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tagList, nullptr);
}

// =============================================================================
// Print function tests - using UShortValue / ULongValue / AsciiValue etc.
// =============================================================================

TEST_F(Nikon3MakerNoteTest_444, PrintIiIso_NormalValue_444) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintIiIso_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0002_SingleValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0002_MultipleValues_444) {
  UShortValue val;
  val.read("0 100 200");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0007_ReturnsStream_444) {
  AsciiValue val;
  val.read("ISO Auto");
  Nikon3MakerNote::print0x0007(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0083_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0083_NonZeroValue_444) {
  UShortValue val;
  val.read("6");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0084_FourValues_444) {
  URationalValue val;
  val.read("180/10 700/10 28/10 56/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0084_TwoValues_444) {
  URationalValue val;
  val.read("500/10 28/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0085_NormalValue_444) {
  URationalValue val;
  val.read("100/100");
  Nikon3MakerNote::print0x0085(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0086_NormalValue_444) {
  URationalValue val;
  val.read("10/1");
  Nikon3MakerNote::print0x0086(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0088_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0089_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x008b_NormalValue_444) {
  UShortValue val;
  val.read("0 0 0 0");
  Nikon3MakerNote::print0x008b(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistance_NormalValue_444) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistance_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintAperture_NormalValue_444) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintAperture_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocal_NormalValue_444) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocal_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFStops_NormalValue_444) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFStops_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExitPupilPosition_NormalValue_444) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExitPupilPosition_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashFocalLength_NormalValue_444) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashFocalLength_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintRepeatingFlashRate_NormalValue_444) {
  UShortValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintRepeatingFlashRate_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintRepeatingFlashCount_NormalValue_444) {
  UShortValue val;
  val.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintRepeatingFlashCount_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintTimeZone_NormalValue_444) {
  ShortValue val;
  val.read("0");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintTimeZone_PositiveOffset_444) {
  ShortValue val;
  val.read("60");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintTimeZone_NegativeOffset_444) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x009a_TwoValues_444) {
  URationalValue val;
  val.read("2500/1000 2500/1000");
  Nikon3MakerNote::print0x009a(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x009e_NormalValue_444) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  Nikon3MakerNote::print0x009e(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintPictureControl_NormalValue_444) {
  UShortValue val;
  val.read("128");
  Nikon3MakerNote::printPictureControl(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintCameraExposureCompensation_NormalValue_444) {
  UShortValue val;
  val.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintCameraExposureCompensation_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintLensId1_NullMetadata_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printLensId1(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintLensId2_NullMetadata_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printLensId2(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintLensId3_NullMetadata_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printLensId3(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintLensId4_NullMetadata_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printLensId4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintAfPointsInFocus_NullMetadata_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintAf2AreaMode_NullMetadata_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistanceLd4_NormalValue_444) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistanceLd4_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintApertureLd4_NormalValue_444) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintApertureLd4_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocalLd4_NormalValue_444) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocalLd4_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashZoomHeadPosition_NormalValue_444) {
  UShortValue val;
  val.read("24");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashZoomHeadPosition_ZeroValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintLensId_WithGroupParam_444) {
  UShortValue val;
  val.read("0");
  std::string group = "NikonLd1";
  Nikon3MakerNote::printLensId(os, val, nullptr, group);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintLensId_WithEmptyGroup_444) {
  UShortValue val;
  val.read("0");
  std::string group;
  Nikon3MakerNote::printLensId(os, val, nullptr, group);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Flash data print functions
// =============================================================================

TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData1Fl6_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData1Fl7_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData2Fl6_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData2_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashMasterDataFl6_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashMasterDataFl7_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupAControlData_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupBCControlData_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupADataFl6_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupADataFl7_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupBDataFl6_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupBDataFl7_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupCDataFl6_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupCDataFl7_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData3_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData4_NormalValue_444) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Return value verification - functions should return the same ostream ref
// =============================================================================

TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistanceReturnsOstream_444) {
  UShortValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_444, PrintApertureReturnsOstream_444) {
  UShortValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocalReturnsOstream_444) {
  UShortValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_444, PrintIiIsoReturnsOstream_444) {
  UShortValue val;
  val.read("100");
  std::ostream& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_444, PrintTimeZoneReturnsOstream_444) {
  ShortValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_444, PrintFStopsReturnsOstream_444) {
  UShortValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary value tests
// =============================================================================

TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistance_MaxByte_444) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintAperture_MaxByte_444) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFocal_MaxByte_444) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintFStops_MaxByte_444) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintExitPupilPosition_MaxByte_444) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0083_AllBitsSet_444) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0088_VariousValues_444) {
  for (int i = 0; i < 16; i++) {
    std::ostringstream localOs;
    UShortValue val;
    val.read(std::to_string(i));
    Nikon3MakerNote::print0x0088(localOs, val, nullptr);
    EXPECT_FALSE(localOs.str().empty()) << "Failed for value " << i;
  }
}

TEST_F(Nikon3MakerNoteTest_444, PrintPictureControl_BoundaryValues_444) {
  // Test value 0
  {
    std::ostringstream localOs;
    UShortValue val;
    val.read("0");
    Nikon3MakerNote::printPictureControl(localOs, val, nullptr);
    EXPECT_FALSE(localOs.str().empty());
  }
  // Test value 255
  {
    std::ostringstream localOs;
    UShortValue val;
    val.read("255");
    Nikon3MakerNote::printPictureControl(localOs, val, nullptr);
    EXPECT_FALSE(localOs.str().empty());
  }
}

// =============================================================================
// With ExifData tests
// =============================================================================

TEST_F(Nikon3MakerNoteTest_444, PrintLensId1_WithExifData_444) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printLensId1(os, val, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, Print0x0089_WithExifData_444) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintAfPointsInFocus_WithExifData_444) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_444, PrintAf2AreaMode_WithExifData_444) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAf2AreaMode(os, val, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
