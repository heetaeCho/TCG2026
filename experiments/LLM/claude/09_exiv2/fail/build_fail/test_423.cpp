#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_423 : public ::testing::Test {
 protected:
  std::ostringstream os;
  ExifData exifData;
};

// ========== tagList tests ==========

TEST_F(Nikon3MakerNoteTest_423, TagListIiIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListIi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListVrIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListVr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListPcIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListPc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListWtIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListWt();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListAfIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListAf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListAf21IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListAf21();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListAf22IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListAf22();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListAFTIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListAFT();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListFiIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListMeIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListFl1IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListFl1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListFl2IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListFl2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListFl3IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListFl3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListFl6IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListFl6();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListFl7IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListFl7();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListSi1IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListSi1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListSi2IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListSi2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListSi3IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListSi3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListSi4IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListSi4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListSi5IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListSi5();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListCb1IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListCb1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListCb2IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListCb2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListCb2aIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListCb2a();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListCb2bIsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListCb2b();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListCb3IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListCb3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListCb4IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListCb4();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListLd1IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListLd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListLd2IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListLd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListLd3IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListLd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(Nikon3MakerNoteTest_423, TagListLd4IsNotNull_423) {
  auto tagList = Nikon3MakerNote::tagListLd4();
  ASSERT_NE(tagList, nullptr);
}

// ========== print function tests ==========

TEST_F(Nikon3MakerNoteTest_423, PrintIiIso_SingleValue_423) {
  UShortValue val;
  val.read("256");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintIiIso_ZeroValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0002_SingleValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0007_AsciiValue_423) {
  AsciiValue val;
  val.read("ISO");
  Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0083_NormalValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0084_FourRationals_423) {
  URationalValue val;
  val.read("50/1 50/1 14/10 14/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0084_TwoRationals_423) {
  URationalValue val;
  val.read("50/1 50/1");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0085_RationalValue_423) {
  URationalValue val;
  val.read("0/0");
  Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0086_RationalValue_423) {
  URationalValue val;
  val.read("10/10");
  Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0088_NormalValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0089_NormalValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x008b_NormalValue_423) {
  UByteValue val;
  val.read("0 0 0 0");
  Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocusDistance_NormalValue_423) {
  UByteValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocusDistance_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintAperture_NormalValue_423) {
  UByteValue val;
  val.read("50");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintAperture_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocal_NormalValue_423) {
  UByteValue val;
  val.read("50");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocal_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFStops_NormalValue_423) {
  UByteValue val;
  val.read("72");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintExitPupilPosition_NormalValue_423) {
  UByteValue val;
  val.read("10");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintExitPupilPosition_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFlashFocalLength_NormalValue_423) {
  UByteValue val;
  val.read("24");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFlashFocalLength_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintRepeatingFlashRate_NormalValue_423) {
  UByteValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintRepeatingFlashRate_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintRepeatingFlashCount_NormalValue_423) {
  UByteValue val;
  val.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintRepeatingFlashCount_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintTimeZone_NormalValue_423) {
  ShortValue val;
  val.read("60");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintTimeZone_NegativeValue_423) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintTimeZone_ZeroValue_423) {
  ShortValue val;
  val.read("0");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x009a_TwoValues_423) {
  URationalValue val;
  val.read("640/1 480/1");
  Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintCameraExposureCompensation_NormalValue_423) {
  UByteValue val;
  val.read("6");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocusDistanceLd4_NormalValue_423) {
  UShortValue val;
  val.read("1000");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocusDistanceLd4_ZeroValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintApertureLd4_NormalValue_423) {
  UShortValue val;
  val.read("500");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintApertureLd4_ZeroValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocalLd4_NormalValue_423) {
  UShortValue val;
  val.read("500");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocalLd4_ZeroValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintLensId1_NormalValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintLensId2_NormalValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintLensId3_NormalValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintLensId4_NormalValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintLensId_NormalValueWithGroup_423) {
  UByteValue val;
  val.read("0");
  std::string group = "Nikon3";
  Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintPictureControl_NormalValue_423) {
  UByteValue val;
  val.read("128");
  Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFlashZoomHeadPosition_NormalValue_423) {
  UByteValue val;
  val.read("24");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFlashZoomHeadPosition_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintFStops_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0083_AllBitsSet_423) {
  UByteValue val;
  val.read("255");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x0088_AllValues_423) {
  // Test multiple AF area values
  for (int i = 0; i < 5; i++) {
    std::ostringstream localOs;
    UByteValue val;
    val.read(std::to_string(i));
    Nikon3MakerNote::print0x0088(localOs, val, nullptr);
    EXPECT_FALSE(localOs.str().empty());
  }
}

TEST_F(Nikon3MakerNoteTest_423, PrintReturnsSameStream_423) {
  UByteValue val;
  val.read("0");
  std::ostream& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_423, PrintApertureReturnsSameStream_423) {
  UByteValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_423, PrintFocalReturnsSameStream_423) {
  UByteValue val;
  val.read("50");
  std::ostream& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_423, PrintIiIsoReturnsSameStream_423) {
  UShortValue val;
  val.read("100");
  std::ostream& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_423, PrintAf2AreaMode_NormalValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintAfPointsInFocus_NormalValue_423) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, Print0x009e_NormalValue_423) {
  UShortValue val;
  val.read("1 2 3 4 5 6 7 8 9 10");
  Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_423, PrintCameraExposureCompensation_ZeroValue_423) {
  UByteValue val;
  val.read("0");
  Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}
