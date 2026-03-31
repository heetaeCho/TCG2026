#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_438 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tag List Tests - Verify tag lists are non-null
// =============================================================================

TEST_F(Nikon3MakerNoteTest_438, TagListSi4_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagList_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListVr_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListPc_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListWt_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListIi_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListAf_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListAf21_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListAf22_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListAFT_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListFi_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListMe_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListFl1_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListFl2_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListFl3_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListFl6_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListFl7_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListSi1_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListSi2_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListSi3_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListSi5_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListCb1_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListCb2_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListCb2a_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListCb2b_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListCb3_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListCb4_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListLd1_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListLd2_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListLd3_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_438, TagListLd4_ReturnsNonNull_438) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Print Function Tests - Verify they return ostream reference and produce output
// =============================================================================

TEST_F(Nikon3MakerNoteTest_438, PrintIiIso_WithValidValue_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintIiIso_WithNonZeroValue_438) {
  UShortValue value;
  value.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0002_SingleValue_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0002_MultipleValues_438) {
  UShortValue value;
  value.read("0 6 8");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0007_ReturnsOstream_438) {
  AsciiValue value;
  value.read("FINE");
  auto& result = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0083_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0084_WithFourValues_438) {
  URationalValue value;
  value.read("240/10 700/10 35/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0084_WithOneValue_438) {
  URationalValue value;
  value.read("500/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0085_ReturnsOstream_438) {
  URationalValue value;
  value.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0086_ReturnsOstream_438) {
  URationalValue value;
  value.read("30/10");
  auto& result = Nikon3MakerNote::print0x0086(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0088_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0089_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x008b_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFocusDistance_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFocusDistance_NonZero_438) {
  UShortValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintAperture_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintAperture_NonZero_438) {
  UShortValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintFocal_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFocal_NonZero_438) {
  UShortValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintFStops_ReturnsOstream_438) {
  UShortValue value;
  value.read("48");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExitPupilPosition_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExitPupilPosition_NonZero_438) {
  UShortValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashFocalLength_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashFocalLength_NonZero_438) {
  UShortValue value;
  value.read("24");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintRepeatingFlashRate_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintRepeatingFlashRate_NonZero_438) {
  UShortValue value;
  value.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintRepeatingFlashCount_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintRepeatingFlashCount_NonZero_438) {
  UShortValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, Print0x009a_ReturnsOstream_438) {
  URationalValue value;
  value.read("100/10 200/10");
  auto& result = Nikon3MakerNote::print0x009a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x009e_ReturnsOstream_438) {
  UShortValue value;
  value.read("0 1 2 3 4 5 6 7 8 9");
  auto& result = Nikon3MakerNote::print0x009e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintTimeZone_ReturnsOstream_438) {
  ShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintPictureControl_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintCameraExposureCompensation_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashZoomHeadPosition_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintLensId1_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintLensId2_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintLensId3_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintLensId4_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintLensId_WithGroup_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  std::string group = "NikonLd1";
  auto& result = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintAfPointsInFocus_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintAf2AreaMode_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFocusDistanceLd4_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintApertureLd4_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFocalLd4_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExternalFlashData1Fl6_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExternalFlashData1Fl7_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExternalFlashData2Fl6_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExternalFlashData2_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashMasterDataFl6_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashMasterDataFl7_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupAControlData_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupBCControlData_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupADataFl6_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupADataFl7_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupBDataFl6_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupBDataFl7_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupCDataFl6_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintFlashGroupCDataFl7_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExternalFlashData3_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintExternalFlashData4_ReturnsOstream_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary / Edge cases
// =============================================================================

TEST_F(Nikon3MakerNoteTest_438, PrintFocusDistance_MaxValue_438) {
  UShortValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintAperture_MaxByte_438) {
  UShortValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintFocal_MaxByte_438) {
  UShortValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintFStops_Zero_438) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, Print0x0083_WithFlags_438) {
  UShortValue value;
  value.read("14");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintTimeZone_Positive_438) {
  ShortValue value;
  value.read("60");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_438, PrintTimeZone_Negative_438) {
  ShortValue value;
  value.read("-60");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test with ExifData provided (non-null)
TEST_F(Nikon3MakerNoteTest_438, Print0x0089_WithExifData_438) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintAfPointsInFocus_WithExifData_438) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_438, PrintLensId_WithEmptyGroup_438) {
  UShortValue value;
  value.read("0");
  std::string group;
  auto& result = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&result, &os);
}
