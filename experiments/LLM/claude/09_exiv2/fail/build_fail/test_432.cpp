#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_432 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// tagList* tests - verify they return non-null tag info arrays
// ============================================================

TEST_F(Nikon3MakerNoteTest_432, TagListFl3_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagList_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListVr_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListVr();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListPc_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListPc();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListWt_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListWt();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListIi_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListIi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListAf_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListAf();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListAf21_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListAf22_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListAFT_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListFi_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListMe_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListFl1_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListFl2_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListFl6_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListFl7_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListSi1_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListSi2_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListSi3_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListSi4_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListSi5_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListCb1_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListCb2_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListCb2a_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListCb2b_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListCb3_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListCb4_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListLd1_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListLd2_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListLd3_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(Nikon3MakerNoteTest_432, TagListLd4_ReturnsNonNull_432) {
  auto result = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Print function tests
// ============================================================

TEST_F(Nikon3MakerNoteTest_432, PrintIiIso_SingleValue_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintIiIso_NormalValue_432) {
  UShortValue value;
  value.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0002_SingleValue_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0002_MultipleValues_432) {
  UShortValue value;
  value.read("0 0 100");
  auto& result = Nikon3MakerNote::print0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0007_ReturnsStreamRef_432) {
  AsciiValue value;
  value.read("FINE");
  auto& result = Nikon3MakerNote::print0x0007(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0083_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0083_NonZeroValue_432) {
  UByteValue value;
  value.read("6");
  auto& result = Nikon3MakerNote::print0x0083(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0084_FourValues_432) {
  URationalValue value;
  value.read("180/10 700/10 35/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0084_SingleValue_432) {
  URationalValue value;
  value.read("500/10");
  auto& result = Nikon3MakerNote::print0x0084(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0085_NormalValue_432) {
  URationalValue value;
  value.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0086_NormalValue_432) {
  URationalValue value;
  value.read("10/10");
  auto& result = Nikon3MakerNote::print0x0086(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0088_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0088_NonZeroValue_432) {
  UByteValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::print0x0088(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x0089_SingleValue_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x008b_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocusDistance_NormalValue_432) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocusDistance_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintAperture_NormalValue_432) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintAperture_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocal_NormalValue_432) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocal_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFStops_NormalValue_432) {
  UByteValue value;
  value.read("72");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFStops_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintExitPupilPosition_NormalValue_432) {
  UByteValue value;
  value.read("50");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintExitPupilPosition_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashFocalLength_NormalValue_432) {
  UByteValue value;
  value.read("35");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashFocalLength_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintRepeatingFlashRate_NormalValue_432) {
  UByteValue value;
  value.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintRepeatingFlashRate_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintRepeatingFlashCount_NormalValue_432) {
  UByteValue value;
  value.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintRepeatingFlashCount_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, Print0x009a_TwoValues_432) {
  URationalValue value;
  value.read("100/100 100/100");
  auto& result = Nikon3MakerNote::print0x009a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x009a_SingleValue_432) {
  URationalValue value;
  value.read("100/100");
  auto& result = Nikon3MakerNote::print0x009a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, Print0x009e_SingleValue_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x009e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintCameraExposureCompensation_NormalValue_432) {
  UByteValue value;
  value.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintCameraExposureCompensation_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintTimeZone_NormalValue_432) {
  ShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintPictureControl_NormalValue_432) {
  UByteValue value;
  value.read("128");
  auto& result = Nikon3MakerNote::printPictureControl(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintPictureControl_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintApertureLd4_NormalValue_432) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintApertureLd4_ZeroValue_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocalLd4_NormalValue_432) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocalLd4_ZeroValue_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocusDistanceLd4_NormalValue_432) {
  UShortValue value;
  value.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocusDistanceLd4_ZeroValue_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintLensId1_NullMetadata_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintLensId2_NullMetadata_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintLensId3_NullMetadata_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintLensId4_NullMetadata_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintLensId_WithEmptyGroup_432) {
  UByteValue value;
  value.read("0");
  std::string group = "";
  auto& result = Nikon3MakerNote::printLensId(os, value, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintAfPointsInFocus_NullMetadata_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintAf2AreaMode_NullMetadata_432) {
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashZoomHeadPosition_NormalValue_432) {
  UByteValue value;
  value.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashZoomHeadPosition_ZeroValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintExternalFlashData1Fl6_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintExternalFlashData1Fl7_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintExternalFlashData2Fl6_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintExternalFlashData2_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashMasterDataFl6_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashMasterDataFl7_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupAControlData_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupBCControlData_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupADataFl6_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupADataFl7_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupBDataFl6_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupBDataFl7_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupCDataFl6_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintFlashGroupCDataFl7_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintExternalFlashData3_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintExternalFlashData4_NormalValue_432) {
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests with ExifData (non-null metadata)
// ============================================================

TEST_F(Nikon3MakerNoteTest_432, Print0x0089_WithExifData_432) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintLensId1_WithExifData_432) {
  ExifData exifData;
  UByteValue value;
  value.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintAfPointsInFocus_WithExifData_432) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_432, PrintAf2AreaMode_WithExifData_432) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary conditions for byte-based values (max byte = 255)
// ============================================================

TEST_F(Nikon3MakerNoteTest_432, PrintFocusDistance_MaxByte_432) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintAperture_MaxByte_432) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFocal_MaxByte_432) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintFStops_MaxByte_432) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printFStops(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_432, PrintExitPupilPosition_MaxByte_432) {
  UByteValue value;
  value.read("255");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Multiple calls should not interfere with each other
// ============================================================

TEST_F(Nikon3MakerNoteTest_432, MultiplePrintCallsIndependent_432) {
  UByteValue value1;
  value1.read("50");
  Nikon3MakerNote::printFocal(os, value1, nullptr);
  std::string first = os.str();

  std::ostringstream os2;
  UByteValue value2;
  value2.read("100");
  Nikon3MakerNote::printFocal(os2, value2, nullptr);
  std::string second = os2.str();

  // Different inputs should potentially produce different outputs (or at least not crash)
  EXPECT_FALSE(first.empty());
  EXPECT_FALSE(second.empty());
}

// ============================================================
// tagList consistency: calling same function twice returns same pointer
// ============================================================

TEST_F(Nikon3MakerNoteTest_432, TagListFl3_ConsistentReturn_432) {
  auto result1 = Nikon3MakerNote::tagListFl3();
  auto result2 = Nikon3MakerNote::tagListFl3();
  EXPECT_EQ(result1, result2);
}

TEST_F(Nikon3MakerNoteTest_432, TagList_ConsistentReturn_432) {
  auto result1 = Nikon3MakerNote::tagList();
  auto result2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(result1, result2);
}
