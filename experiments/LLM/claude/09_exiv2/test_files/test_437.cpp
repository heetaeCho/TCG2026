#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_437 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =====================================================================
// Tests for tagList functions - verify they return non-null pointers
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, TagListReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagList();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListVrReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListPcReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListWtReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListIiReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListAfReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListAf21ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListAf22ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListAFTReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListFiReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListMeReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListFl1ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListFl2ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListFl3ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListFl6ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListFl7ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListSi1ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListSi2ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListSi3ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListSi4ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListSi5ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListCb1ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListCb2ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListCb2aReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListCb2bReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListCb3ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListCb4ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListLd1ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListLd2ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListLd3ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_437, TagListLd4ReturnsNonNull_437) {
  auto tags = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tags, nullptr);
}

// =====================================================================
// Tests for print functions with various Value inputs
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, PrintIiIsoWithSingleValue_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintIiIsoWithNonZeroValue_437) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0002WithSingleValue_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0002WithMultipleValues_437) {
  UShortValue val;
  val.read("2 0 0");
  Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0007ReturnsStream_437) {
  AsciiValue val;
  val.read("FINE");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0083WithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0084WithFourValues_437) {
  URationalValue val;
  val.read("240/10 700/10 28/10 40/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0084WithTwoValues_437) {
  URationalValue val;
  val.read("240/10 700/10");
  Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0085ReturnsStream_437) {
  URationalValue val;
  val.read("0/0");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0086ReturnsStream_437) {
  URationalValue val;
  val.read("1/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0088WithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0089WithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x008bReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFocusDistanceWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFocusDistanceWithNonZero_437) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintApertureWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintApertureWithNonZero_437) {
  UShortValue val;
  val.read("50");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFocalWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFocalWithNonZero_437) {
  UShortValue val;
  val.read("100");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFStopsReturnsStream_437) {
  UShortValue val;
  val.read("48");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintExitPupilPositionWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashFocalLengthWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintRepeatingFlashRateWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintRepeatingFlashCountWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x009aWithTwoValues_437) {
  URationalValue val;
  val.read("0/1 0/1");
  Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x009eWithValue_437) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintTimeZoneReturnsStream_437) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintPictureControlReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintCameraExposureCompensation_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFocusDistanceLd4WithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintApertureLd4WithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFocalLd4WithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashZoomHeadPosition_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// =====================================================================
// Tests for LensId print functions
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, PrintLensId1ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintLensId2ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintLensId3ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintLensId4ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintLensIdWithGroupReturnsStream_437) {
  UShortValue val;
  val.read("0");
  std::string group = "Nikon3";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

// =====================================================================
// Tests for AF area mode print
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, PrintAf2AreaModeReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintAfPointsInFocusReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// =====================================================================
// Tests for flash-related print functions
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, PrintExternalFlashData1Fl6ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintExternalFlashData1Fl7ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintExternalFlashData2Fl6ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintExternalFlashData2ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashMasterDataFl6ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashMasterDataFl7ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupAControlDataReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupBCControlDataReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupADataFl6ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupADataFl7ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupBDataFl6ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupBDataFl7ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupCDataFl6ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashGroupCDataFl7ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintExternalFlashData3ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintExternalFlashData4ReturnsStream_437) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// =====================================================================
// Boundary / edge-case tests
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, PrintFocusDistanceWith255_437) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintApertureWith255_437) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFocalWith255_437) {
  UShortValue val;
  val.read("255");
  Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0083WithVariousFlags_437) {
  UShortValue val;
  val.read("14");
  Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, Print0x0088WithVariousValues_437) {
  // Test with different AF point values
  UShortValue val;
  val.read("1");
  Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFStopsWithZero_437) {
  UShortValue val;
  val.read("0");
  Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintExitPupilPositionWithNonZero_437) {
  UShortValue val;
  val.read("128");
  Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintFlashFocalLengthWithNonZero_437) {
  UShortValue val;
  val.read("35");
  Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintRepeatingFlashRateWithNonZero_437) {
  UShortValue val;
  val.read("10");
  Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintRepeatingFlashCountWithNonZero_437) {
  UShortValue val;
  val.read("5");
  Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// =====================================================================
// Verify multiple tagList calls return same pointer (constexpr)
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, TagListSi3ConsistentReturn_437) {
  auto tags1 = Nikon3MakerNote::tagListSi3();
  auto tags2 = Nikon3MakerNote::tagListSi3();
  EXPECT_EQ(tags1, tags2);
}

TEST_F(Nikon3MakerNoteTest_437, TagListConsistentReturn_437) {
  auto tags1 = Nikon3MakerNote::tagList();
  auto tags2 = Nikon3MakerNote::tagList();
  EXPECT_EQ(tags1, tags2);
}

TEST_F(Nikon3MakerNoteTest_437, TagListLd4ConsistentReturn_437) {
  auto tags1 = Nikon3MakerNote::tagListLd4();
  auto tags2 = Nikon3MakerNote::tagListLd4();
  EXPECT_EQ(tags1, tags2);
}

// =====================================================================
// Tests with ExifData (non-null metadata)
// =====================================================================

TEST_F(Nikon3MakerNoteTest_437, Print0x0089WithMetadata_437) {
  UShortValue val;
  val.read("0");
  ExifData exifData;
  auto& result = Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_437, PrintLensId1WithMetadata_437) {
  UShortValue val;
  val.read("0");
  ExifData exifData;
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_437, PrintAfPointsInFocusWithMetadata_437) {
  UShortValue val;
  val.read("0");
  ExifData exifData;
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}
