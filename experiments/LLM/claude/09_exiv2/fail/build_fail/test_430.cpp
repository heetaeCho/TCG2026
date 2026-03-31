#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_430 : public ::testing::Test {
 protected:
  std::ostringstream os;
  ExifData exifData;
};

// ==================== tagList* tests ====================

TEST_F(Nikon3MakerNoteTest_430, TagListFl1_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagList_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListVr_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListVr();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListPc_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListPc();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListWt_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListWt();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListIi_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListIi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListAf_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListAf();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListAf21_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListAf22_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListAFT_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListFi_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListMe_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListFl2_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListFl3_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListFl6_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListFl7_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListSi1_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListSi2_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListSi3_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListSi4_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListSi5_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListCb1_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListCb2_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListCb2a_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListCb2b_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListCb3_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListCb4_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListLd1_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListLd2_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListLd3_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_430, TagListLd4_ReturnsNonNull_430) {
  auto result = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(result, nullptr);
}

// ==================== print function tests ====================

TEST_F(Nikon3MakerNoteTest_430, PrintIiIso_WithValidValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_430, PrintIiIso_WithNonZeroValue_430) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0002_SingleValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0002_MultipleValues_430) {
  UShortValue val;
  val.read("0 1 2");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0007_WithValue_430) {
  AsciiValue val;
  val.read("AF-S VR");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0083_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0084_WithFourValues_430) {
  URationalValue val;
  val.read("240/10 700/10 35/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0084_WithTwoValues_430) {
  URationalValue val;
  val.read("240/10 700/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0085_WithValue_430) {
  URationalValue val;
  val.read("50/10");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0086_WithValue_430) {
  URationalValue val;
  val.read("10/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0088_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0089_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x008b_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocusDistance_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocusDistance_WithNonZero_430) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintAperture_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintAperture_WithNonZero_430) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocal_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocal_WithNonZero_430) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFStops_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintExitPupilPosition_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashFocalLength_WithZero_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashFocalLength_WithNonZero_430) {
  UShortValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintRepeatingFlashRate_WithZero_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintRepeatingFlashCount_WithZero_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintCameraExposureCompensation_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintCameraExposureCompensation_WithNonZero_430) {
  UShortValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashZoomHeadPosition_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintTimeZone_WithValue_430) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintPictureControl_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x009a_WithTwoValues_430) {
  URationalValue val;
  val.read("2272/100 1704/100");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x009e_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintApertureLd4_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocalLd4_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocusDistanceLd4_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintLensId1_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintLensId2_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintLensId3_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintLensId4_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintLensId_WithGroupAndValue_430) {
  UShortValue val;
  val.read("0");
  std::string group = "Nikon3";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintAfPointsInFocus_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintAf2AreaMode_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Flash-related print tests ====================

TEST_F(Nikon3MakerNoteTest_430, PrintExternalFlashData1Fl6_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintExternalFlashData1Fl7_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintExternalFlashData2Fl6_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintExternalFlashData2_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashMasterDataFl6_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashMasterDataFl7_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupAControlData_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupBCControlData_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupADataFl6_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupADataFl7_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupBDataFl6_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupBDataFl7_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupCDataFl6_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFlashGroupCDataFl7_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintExternalFlashData3_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintExternalFlashData4_WithValue_430) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Boundary / Edge cases ====================

TEST_F(Nikon3MakerNoteTest_430, PrintFocusDistance_MaxValue_430) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintAperture_MaxValue_430) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocal_MaxValue_430) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0083_AllBitsSet_430) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, Print0x0088_AllBitsSet_430) {
  UShortValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintTimeZone_NegativeOffset_430) {
  ShortValue val;
  val.read("-60");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_430, PrintTimeZone_PositiveOffset_430) {
  ShortValue val;
  val.read("540");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Stream output verification ====================

TEST_F(Nikon3MakerNoteTest_430, PrintFocusDistance_ProducesOutput_430) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string output = os.str();
  // Should produce some output (distance or "Unknown")
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_430, PrintAperture_ProducesOutput_430) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_430, PrintFocal_ProducesOutput_430) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_430, PrintFStops_ProducesOutput_430) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_430, PrintExitPupilPosition_ProducesOutput_430) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_430, PrintRepeatingFlashRate_ProducesOutput_430) {
  UShortValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(Nikon3MakerNoteTest_430, PrintRepeatingFlashCount_ProducesOutput_430) {
  UShortValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// Verify return reference chains properly
TEST_F(Nikon3MakerNoteTest_430, StreamChaining_Works_430) {
  UShortValue val;
  val.read("50");
  std::ostringstream chained;
  Nikon3MakerNote::printFocusDistance(chained, val, nullptr) << " extra";
  std::string output = chained.str();
  EXPECT_NE(output.find("extra"), std::string::npos);
}
