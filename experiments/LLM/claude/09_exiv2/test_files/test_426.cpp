#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_426 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// tagListAf22 tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_426, TagListAf22_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// tagList tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_426, TagList_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListVr_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListPc_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListWt_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListIi_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListAf_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListAf21_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListAFT_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListFi_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListMe_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListFl1_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListFl2_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListFl3_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListFl6_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListFl7_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListSi1_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListSi2_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListSi3_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListSi4_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListSi5_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListCb1_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListCb2_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListCb2a_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListCb2b_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListCb3_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListCb4_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListLd1_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListLd2_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListLd3_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_426, TagListLd4_ReturnsNonNull_426) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_426, PrintIiIso_SingleValue_426) {
  UShortValue value;
  value.read("0");
  Nikon3MakerNote::printIiIso(os, value, nullptr);
  // Just verify it doesn't crash and produces some output
  // The actual output depends on implementation
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0002_WithSingleValue_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0007_ReturnsStream_426) {
  AsciiValue value;
  value.read("ISO 100");
  auto& ret = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0083_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0084_WithFourRationalValues_426) {
  URationalValue value;
  value.read("24/1 70/1 28/10 28/10");
  auto& ret = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0084_EmptyValue_426) {
  URationalValue value;
  auto& ret = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0085_ReturnsStream_426) {
  URationalValue value;
  value.read("10/1");
  auto& ret = Nikon3MakerNote::print0x0085(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0086_ReturnsStream_426) {
  URationalValue value;
  value.read("10/1");
  auto& ret = Nikon3MakerNote::print0x0086(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0088_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0089_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x008b_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x008b(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFocusDistance_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_426, PrintFocusDistance_ZeroValue_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintAperture_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_426, PrintAperture_ZeroValue_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFocal_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_426, PrintFStops_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintExitPupilPosition_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashFocalLength_ReturnsStream_426) {
  UShortValue value;
  value.read("24");
  auto& ret = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashFocalLength_ZeroValue_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintRepeatingFlashRate_ReturnsStream_426) {
  UShortValue value;
  value.read("10");
  auto& ret = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintRepeatingFlashRate_ZeroValue_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintRepeatingFlashCount_ReturnsStream_426) {
  UShortValue value;
  value.read("5");
  auto& ret = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintRepeatingFlashCount_ZeroValue_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintTimeZone_ReturnsStream_426) {
  ShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_426, PrintPictureControl_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printPictureControl(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x009a_ReturnsStream_426) {
  URationalValue value;
  value.read("100/1 100/1");
  auto& ret = Nikon3MakerNote::print0x009a(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x009e_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::print0x009e(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintApertureLd4_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFocalLd4_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFocusDistanceLd4_ReturnsStream_426) {
  UShortValue value;
  value.read("50");
  auto& ret = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintCameraExposureCompensation_ReturnsStream_426) {
  UShortValue value;
  value.read("6");
  auto& ret = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashZoomHeadPosition_ReturnsStream_426) {
  UShortValue value;
  value.read("24");
  auto& ret = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashZoomHeadPosition_ZeroValue_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintLensId1_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintLensId2_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintLensId3_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintLensId4_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintLensId_WithGroup_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  std::string group = "NikonLd1";
  auto& ret = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintAfPointsInFocus_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintAf2AreaMode_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData1Fl6_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData1Fl7_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData2Fl6_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData2_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashMasterDataFl6_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashMasterDataFl7_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupAControlData_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupBCControlData_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupADataFl6_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupADataFl7_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupBDataFl6_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupBDataFl7_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupCDataFl6_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFlashGroupCDataFl7_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData3_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData4_ReturnsStream_426) {
  UShortValue value;
  value.read("0");
  auto& ret = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Boundary / Edge case tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_426, PrintFocusDistance_MaxByteValue_426) {
  UShortValue value;
  value.read("255");
  auto& ret = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintAperture_MaxByteValue_426) {
  UShortValue value;
  value.read("255");
  auto& ret = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintFocal_MaxByteValue_426) {
  UShortValue value;
  value.read("255");
  auto& ret = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintTimeZone_NegativeValue_426) {
  ShortValue value;
  value.read("-60");
  auto& ret = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_426, PrintTimeZone_PositiveValue_426) {
  ShortValue value;
  value.read("60");
  auto& ret = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0084_SingleRationalValue_426) {
  URationalValue value;
  value.read("50/1");
  auto& ret = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0084_TwoRationalValues_426) {
  URationalValue value;
  value.read("24/1 70/1");
  auto& ret = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintLensId_EmptyGroup_426) {
  UShortValue value;
  value.read("0");
  std::string group;
  auto& ret = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// With ExifData tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_426, PrintLensId1_WithExifData_426) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& ret = Nikon3MakerNote::printLensId1(os, value, &exifData);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, Print0x0089_WithExifData_426) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& ret = Nikon3MakerNote::print0x0089(os, value, &exifData);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintAfPointsInFocus_WithExifData_426) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& ret = Nikon3MakerNote::printAfPointsInFocus(os, value, &exifData);
  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_426, PrintAf2AreaMode_WithExifData_426) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& ret = Nikon3MakerNote::printAf2AreaMode(os, value, &exifData);
  EXPECT_EQ(&ret, &os);
}
