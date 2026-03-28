#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_445 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(Nikon3MakerNoteTest_445, TagListIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListVrIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListPcIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListWtIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListIiIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListAfIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListAf21IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListAf22IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListAFTIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListFiIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListMeIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListFl1IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListFl2IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListFl3IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListFl6IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListFl7IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListSi1IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListSi2IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListSi3IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListSi4IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListSi5IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListCb1IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListCb2IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListCb2aIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListCb2bIsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListCb3IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListCb4IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListLd1IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListLd2IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListLd3IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_445, TagListLd4IsNotNull_445) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions - basic smoke tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_445, PrintIiIso_SingleValue_445) {
  UShortValue val;
  val.read("256");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  // Just ensure something was written
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintIiIso_ZeroValue_445) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0002_SingleValue_445) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0002_MultipleValues_445) {
  UShortValue val;
  val.read("0 2 0 0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0007_ReturnsStream_445) {
  AsciiValue val;
  val.read("ISO 100");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0083_Value0_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0084_FourValues_445) {
  URationalValue val;
  val.read("180/10 700/10 28/10 28/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0084_EmptyValue_445) {
  URationalValue val;
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  // Should handle gracefully
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0085_ReturnsStream_445) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0086_ReturnsStream_445) {
  URationalValue val;
  val.read("10/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0088_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0089_ReturnsStream_445) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x008b_ReturnsStream_445) {
  UByteValue val;
  val.read("0 0 0 0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocusDistance_ReturnsStream_445) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocusDistance_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintAperture_ReturnsStream_445) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintAperture_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocal_ReturnsStream_445) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFStops_ReturnsStream_445) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintExitPupilPosition_ReturnsStream_445) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashFocalLength_ReturnsStream_445) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashFocalLength_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintRepeatingFlashRate_ReturnsStream_445) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintRepeatingFlashRate_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintRepeatingFlashCount_ReturnsStream_445) {
  UByteValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintRepeatingFlashCount_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x009a_TwoValues_445) {
  URationalValue val;
  val.read("100/1 100/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x009e_ReturnsStream_445) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintTimeZone_ReturnsStream_445) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintTimeZone_PositiveOffset_445) {
  ShortValue val;
  val.read("60");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintTimeZone_NegativeOffset_445) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintPictureControl_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintCameraExposureCompensation_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashZoomHeadPosition_ReturnsStream_445) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashZoomHeadPosition_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintApertureLd4_ReturnsStream_445) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocalLd4_ReturnsStream_445) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocusDistanceLd4_ReturnsStream_445) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintLensId1_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintLensId2_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintLensId3_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintLensId4_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintAfPointsInFocus_ReturnsStream_445) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintAf2AreaMode_ReturnsStream_445) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for Ld4 print functions with boundary values
// ============================================================

TEST_F(Nikon3MakerNoteTest_445, PrintApertureLd4_ZeroValue_445) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocalLd4_ZeroValue_445) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocusDistanceLd4_ZeroValue_445) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for flash data print functions
// ============================================================

TEST_F(Nikon3MakerNoteTest_445, PrintExternalFlashData1Fl6_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintExternalFlashData1Fl7_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintExternalFlashData2Fl6_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintExternalFlashData2_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashMasterDataFl6_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashMasterDataFl7_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupAControlData_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupBCControlData_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupADataFl6_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupADataFl7_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupBDataFl6_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupBDataFl7_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupCDataFl6_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintFlashGroupCDataFl7_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintExternalFlashData3_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, PrintExternalFlashData4_ReturnsStream_445) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print functions with ExifData
// ============================================================

TEST_F(Nikon3MakerNoteTest_445, PrintLensId_WithEmptyExifData_445) {
  UByteValue val;
  val.read("0");
  ExifData exifData;
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0089_WithExifData_445) {
  UShortValue val;
  val.read("1");
  ExifData exifData;
  auto& result = Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for boundary/edge case values
// ============================================================

TEST_F(Nikon3MakerNoteTest_445, PrintFocusDistance_MaxByteValue_445) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintAperture_MaxByteValue_445) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocal_MaxByteValue_445) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFStops_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintExitPupilPosition_ZeroValue_445) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintCameraExposureCompensation_HighValue_445) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0083_AllBitsSet_445) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, Print0x0088_NonZeroValue_445) {
  UByteValue val;
  val.read("1");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintApertureLd4_LargeValue_445) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocalLd4_LargeValue_445) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_445, PrintFocusDistanceLd4_LargeValue_445) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}
