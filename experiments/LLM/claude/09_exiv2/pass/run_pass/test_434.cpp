#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "value.hpp"
#include "exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_434 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ==================== tagList tests ====================

TEST_F(Nikon3MakerNoteTest_434, TagListFl7_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagList_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListVr_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListPc_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListWt_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListIi_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListAf_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListAf21_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListAf22_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListAFT_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListFi_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListMe_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListFl1_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListFl2_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListFl3_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListFl6_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListSi1_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListSi2_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListSi3_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListSi4_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListSi5_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListCb1_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListCb2_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListCb2a_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListCb2b_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListCb3_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListCb4_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListLd1_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListLd2_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListLd3_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_434, TagListLd4_NotNull_434) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ==================== print function tests ====================

TEST_F(Nikon3MakerNoteTest_434, PrintIiIso_SingleValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintIiIso_NonZero_434) {
  UShortValue val;
  val.read("256");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0002_SingleValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0002_TwoValues_434) {
  UShortValue val;
  val.read("0 6");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0007_ReturnsOstream_434) {
  AsciiValue val;
  val.read("ISO 100");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0083_ZeroValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0084_FourValues_434) {
  URationalValue val;
  val.read("240/10 700/10 35/10 56/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0084_TwoValues_434) {
  URationalValue val;
  val.read("500/10 500/10 28/10 28/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0085_ReturnsOstream_434) {
  URationalValue val;
  val.read("10/1");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0086_ReturnsOstream_434) {
  URationalValue val;
  val.read("100/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0088_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0089_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, Print0x008b_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFocusDistance_ReturnsOstream_434) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintFocusDistance_ZeroValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintAperture_ReturnsOstream_434) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintAperture_ZeroValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintFocal_ReturnsOstream_434) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFocal_ZeroValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintFStops_ReturnsOstream_434) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintExitPupilPosition_ReturnsOstream_434) {
  UShortValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, Print0x009a_TwoValues_434) {
  URationalValue val;
  val.read("100/1 100/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, Print0x009e_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashFocalLength_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashFocalLength_NonZero_434) {
  UShortValue val;
  val.read("24");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintRepeatingFlashRate_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintRepeatingFlashCount_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintTimeZone_ReturnsOstream_434) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintPictureControl_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintCameraExposureCompensation_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintLensId1_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintLensId2_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintLensId3_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintLensId4_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintAfPointsInFocus_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintAf2AreaMode_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFocusDistanceLd4_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintApertureLd4_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFocalLd4_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData1Fl6_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData1Fl7_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData2Fl6_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData2_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashMasterDataFl6_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashMasterDataFl7_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupAControlData_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupBCControlData_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupADataFl6_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupADataFl7_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupBDataFl6_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupBDataFl7_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupCDataFl6_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupCDataFl7_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData3_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData4_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintFlashZoomHeadPosition_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_434, PrintLensId_WithGroup_ReturnsOstream_434) {
  UShortValue val;
  val.read("0");
  std::string group = "Nikon3";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

// ==================== Boundary condition tests ====================

TEST_F(Nikon3MakerNoteTest_434, PrintFocusDistance_MaxValue_434) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintAperture_MaxValue_434) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintFocal_MaxValue_434) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintFStops_ZeroValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintExitPupilPosition_ZeroValue_434) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0083_AllBitsSet_434) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0088_NonZero_434) {
  UShortValue val;
  val.read("1");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, Print0x0089_NonZero_434) {
  UShortValue val;
  val.read("1");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// Tests with ExifData
TEST_F(Nikon3MakerNoteTest_434, PrintLensId1_WithMetadata_434) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintAfPointsInFocus_WithMetadata_434) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintTimeZone_PositiveOffset_434) {
  ShortValue val;
  val.read("60");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_434, PrintTimeZone_NegativeOffset_434) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}
