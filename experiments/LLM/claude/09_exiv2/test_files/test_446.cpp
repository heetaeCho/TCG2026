#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_446 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// tagList* functions — verify they return non-null
// =============================================================================

TEST_F(Nikon3MakerNoteTest_446, TagListNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagList());
}

TEST_F(Nikon3MakerNoteTest_446, TagListLd1NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListLd1());
}

TEST_F(Nikon3MakerNoteTest_446, TagListLd2NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListLd2());
}

TEST_F(Nikon3MakerNoteTest_446, TagListLd3NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListLd3());
}

TEST_F(Nikon3MakerNoteTest_446, TagListLd4NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListLd4());
}

TEST_F(Nikon3MakerNoteTest_446, TagListVrNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListVr());
}

TEST_F(Nikon3MakerNoteTest_446, TagListPcNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListPc());
}

TEST_F(Nikon3MakerNoteTest_446, TagListWtNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListWt());
}

TEST_F(Nikon3MakerNoteTest_446, TagListIiNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListIi());
}

TEST_F(Nikon3MakerNoteTest_446, TagListAfNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListAf());
}

TEST_F(Nikon3MakerNoteTest_446, TagListAf21NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListAf21());
}

TEST_F(Nikon3MakerNoteTest_446, TagListAf22NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListAf22());
}

TEST_F(Nikon3MakerNoteTest_446, TagListAFTNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListAFT());
}

TEST_F(Nikon3MakerNoteTest_446, TagListFiNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListFi());
}

TEST_F(Nikon3MakerNoteTest_446, TagListMeNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListMe());
}

TEST_F(Nikon3MakerNoteTest_446, TagListFl1NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListFl1());
}

TEST_F(Nikon3MakerNoteTest_446, TagListFl2NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListFl2());
}

TEST_F(Nikon3MakerNoteTest_446, TagListFl3NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListFl3());
}

TEST_F(Nikon3MakerNoteTest_446, TagListFl6NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListFl6());
}

TEST_F(Nikon3MakerNoteTest_446, TagListFl7NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListFl7());
}

TEST_F(Nikon3MakerNoteTest_446, TagListSi1NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListSi1());
}

TEST_F(Nikon3MakerNoteTest_446, TagListSi2NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListSi2());
}

TEST_F(Nikon3MakerNoteTest_446, TagListSi3NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListSi3());
}

TEST_F(Nikon3MakerNoteTest_446, TagListSi4NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListSi4());
}

TEST_F(Nikon3MakerNoteTest_446, TagListSi5NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListSi5());
}

TEST_F(Nikon3MakerNoteTest_446, TagListCb1NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListCb1());
}

TEST_F(Nikon3MakerNoteTest_446, TagListCb2NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListCb2());
}

TEST_F(Nikon3MakerNoteTest_446, TagListCb2aNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListCb2a());
}

TEST_F(Nikon3MakerNoteTest_446, TagListCb2bNotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListCb2b());
}

TEST_F(Nikon3MakerNoteTest_446, TagListCb3NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListCb3());
}

TEST_F(Nikon3MakerNoteTest_446, TagListCb4NotNull_446) {
  EXPECT_NE(nullptr, Nikon3MakerNote::tagListCb4());
}

// =============================================================================
// Print functions — basic smoke tests with simple Value objects
// =============================================================================

TEST_F(Nikon3MakerNoteTest_446, PrintIiIso_ReturnsStream_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should not be empty
  // (It may print "0" or some special string)
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0002_SingleValue_446) {
  UShortValue val;
  val.read("2 0 0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0007_ReturnsStream_446) {
  AsciiValue val;
  val.read("AF-S");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0083_SingleByte_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0084_FourRationals_446) {
  URationalValue val;
  val.read("180/10 700/10 35/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0085_Rational_446) {
  URationalValue val;
  val.read("100/100");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0086_Rational_446) {
  URationalValue val;
  val.read("10/10");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0088_ReturnsStream_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x0089_ReturnsStream_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x008b_ReturnsStream_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFocusDistance_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFocusDistance_NonZeroValue_446) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintAperture_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintAperture_NonZeroValue_446) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFocal_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFocal_NonZeroValue_446) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFStops_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintExitPupilPosition_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashFocalLength_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintRepeatingFlashRate_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintRepeatingFlashCount_ZeroValue_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintTimeZone_ReturnsStream_446) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintTimeZone_PositiveOffset_446) {
  ShortValue val;
  val.read("60");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintTimeZone_NegativeOffset_446) {
  ShortValue val;
  val.read("-300");
  Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, Print0x009a_TwoRationals_446) {
  URationalValue val;
  val.read("300/1 300/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintPictureControl_ReturnsStream_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintCameraExposureCompensation_ReturnsStream_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFocusDistanceLd4_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintApertureLd4_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFocalLd4_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintLensId1_NullMetadata_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintLensId2_NullMetadata_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintLensId3_NullMetadata_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintLensId4_NullMetadata_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintLensId_WithGroup_446) {
  UShortValue val;
  val.read("0");
  std::string group = "NikonLd1";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintAfPointsInFocus_NullMetadata_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintAf2AreaMode_NullMetadata_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, Print0x009e_ReturnsStream_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashZoomHeadPosition_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData1Fl6_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData1Fl7_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData2Fl6_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData2_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashMasterDataFl6_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashMasterDataFl7_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupAControlData_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupBCControlData_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupADataFl6_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupADataFl7_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupBDataFl6_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupBDataFl7_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupCDataFl6_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupCDataFl7_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData3_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData4_Zero_446) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Tests with ExifData (non-null)
// =============================================================================

TEST_F(Nikon3MakerNoteTest_446, Print0x0089_WithExifData_446) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintLensId1_WithExifData_446) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintLensId_WithExifDataAndGroup_446) {
  ExifData exifData;
  UShortValue val;
  val.read("0");
  std::string group = "NikonLd2";
  auto& result = Nikon3MakerNote::printLensId(os, val, &exifData, group);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// Boundary: values with max byte value (255)
// =============================================================================

TEST_F(Nikon3MakerNoteTest_446, PrintFocusDistance_MaxByte_446) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintAperture_MaxByte_446) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFocal_MaxByte_446) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFStops_MaxByte_446) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintExitPupilPosition_MaxByte_446) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintFlashFocalLength_NonZero_446) {
  UShortValue val;
  val.read("24");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintRepeatingFlashRate_NonZero_446) {
  UShortValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_446, PrintRepeatingFlashCount_NonZero_446) {
  UShortValue val;
  val.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =============================================================================
// Verify tagList returns the same pointer on repeated calls (constexpr/static)
// =============================================================================

TEST_F(Nikon3MakerNoteTest_446, TagListLd1_ConsistentReturn_446) {
  auto ptr1 = Nikon3MakerNote::tagListLd1();
  auto ptr2 = Nikon3MakerNote::tagListLd1();
  EXPECT_EQ(ptr1, ptr2);
}

TEST_F(Nikon3MakerNoteTest_446, TagList_ConsistentReturn_446) {
  auto ptr1 = Nikon3MakerNote::tagList();
  auto ptr2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(ptr1, ptr2);
}
