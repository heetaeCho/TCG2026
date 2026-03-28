#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_448 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ===== tagList tests =====

TEST_F(Nikon3MakerNoteTest_448, TagListLd3_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagList_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListVr_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListPc_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListWt_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListIi_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListAf_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListAf21_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListAf22_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListAFT_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListFi_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListMe_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListFl1_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListFl2_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListFl3_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListFl6_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListFl7_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListSi1_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListSi2_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListSi3_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListSi4_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListSi5_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListCb1_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListCb2_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListCb2a_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListCb2b_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListCb3_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListCb4_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListLd1_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListLd2_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_448, TagListLd4_ReturnsNonNull_448) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ===== Print function tests =====

TEST_F(Nikon3MakerNoteTest_448, PrintIiIso_WithSingleValue_448) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintIiIso_WithNonZeroValue_448) {
  UShortValue val;
  val.read("1");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0002_WithSingleValue_448) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0002_WithMultipleValues_448) {
  UShortValue val;
  val.read("0 6 0 0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0007_WithAsciiValue_448) {
  AsciiValue val;
  val.read("ISO 100");
  Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0083_WithZeroValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0084_ReturnsStream_448) {
  URationalValue val;
  val.read("240/10 700/10 28/10 28/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  // Just check the stream is returned and something was written
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0085_WithValue_448) {
  URationalValue val;
  val.read("100/100");
  Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0086_WithValue_448) {
  URationalValue val;
  val.read("12/1");
  Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0088_WithValue_448) {
  UByteValue val;
  val.read("0 0 0 0");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0089_WithZeroValue_448) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x008b_WithValue_448) {
  UByteValue val;
  val.read("0 0 0 0");
  Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocusDistance_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocusDistance_WithNonZero_448) {
  UByteValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintAperture_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintAperture_WithNonZero_448) {
  UByteValue val;
  val.read("50");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocal_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocal_WithNonZero_448) {
  UByteValue val;
  val.read("100");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFStops_WithValue_448) {
  UByteValue val;
  val.read("12");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExitPupilPosition_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExitPupilPosition_WithNonZero_448) {
  UByteValue val;
  val.read("10");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x009a_WithTwoValues_448) {
  URationalValue val;
  val.read("100/100 100/100");
  Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, Print0x009e_WithValues_448) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashFocalLength_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashFocalLength_WithNonZero_448) {
  UByteValue val;
  val.read("35");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintRepeatingFlashRate_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintRepeatingFlashCount_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintTimeZone_WithValue_448) {
  ShortValue val;
  val.read("0");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintPictureControl_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintCameraExposureCompensation_WithValue_448) {
  UByteValue val;
  val.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintApertureLd4_WithValue_448) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocalLd4_WithValue_448) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocusDistanceLd4_WithValue_448) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocusDistanceLd4_WithNonZero_448) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintLensId1_WithEmptyMetadata_448) {
  UByteValue val;
  val.read("0");
  ExifData metadata;
  Nikon3MakerNote::printLensId1(os, val, &metadata);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintLensId2_WithEmptyMetadata_448) {
  UByteValue val;
  val.read("0");
  ExifData metadata;
  Nikon3MakerNote::printLensId2(os, val, &metadata);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintLensId3_WithEmptyMetadata_448) {
  UByteValue val;
  val.read("0");
  ExifData metadata;
  Nikon3MakerNote::printLensId3(os, val, &metadata);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintLensId4_WithEmptyMetadata_448) {
  UByteValue val;
  val.read("0");
  ExifData metadata;
  Nikon3MakerNote::printLensId4(os, val, &metadata);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintLensId_WithGroup_448) {
  UByteValue val;
  val.read("0");
  ExifData metadata;
  std::string group = "NikonLd3";
  Nikon3MakerNote::printLensId(os, val, &metadata, group);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintLensId1_WithNullMetadata_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintAfPointsInFocus_WithValue_448) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintAf2AreaMode_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashZoomHeadPosition_WithZero_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashZoomHeadPosition_WithNonZero_448) {
  UByteValue val;
  val.read("24");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// Test that print functions return the same ostream reference
TEST_F(Nikon3MakerNoteTest_448, PrintFocusDistance_ReturnsOstream_448) {
  UByteValue val;
  val.read("10");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_448, PrintAperture_ReturnsOstream_448) {
  UByteValue val;
  val.read("10");
  std::ostream& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocal_ReturnsOstream_448) {
  UByteValue val;
  val.read("10");
  std::ostream& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_448, PrintFStops_ReturnsOstream_448) {
  UByteValue val;
  val.read("12");
  std::ostream& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_448, Print0x0083_ReturnsOstream_448) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Edge case: large values
TEST_F(Nikon3MakerNoteTest_448, PrintFocusDistance_WithMaxValue_448) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintAperture_WithMaxValue_448) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocal_WithMaxValue_448) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFStops_WithZeroValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExitPupilPosition_WithMaxValue_448) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintTimeZone_WithPositiveOffset_448) {
  ShortValue val;
  val.read("60");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintTimeZone_WithNegativeOffset_448) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// Test ExternalFlashData functions
TEST_F(Nikon3MakerNoteTest_448, PrintExternalFlashData1Fl6_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExternalFlashData1Fl7_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExternalFlashData2Fl6_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExternalFlashData2_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExternalFlashData3_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintExternalFlashData4_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashMasterDataFl6_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashMasterDataFl7_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupAControlData_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupBCControlData_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupADataFl6_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupADataFl7_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupBDataFl6_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupBDataFl7_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupCDataFl6_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFlashGroupCDataFl7_WithValue_448) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// Boundary: ApertureLd4, FocalLd4, FocusDistanceLd4 with max UShort
TEST_F(Nikon3MakerNoteTest_448, PrintApertureLd4_WithMaxValue_448) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocalLd4_WithMaxValue_448) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_448, PrintFocusDistanceLd4_WithMaxValue_448) {
  UShortValue val;
  val.read("65535");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}
