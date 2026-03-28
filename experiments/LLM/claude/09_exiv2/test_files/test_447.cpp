#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_447 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// tagList functions - verify they return non-null pointers
// =============================================================================

TEST_F(Nikon3MakerNoteTest_447, TagListReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagList();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListLd2ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListLd2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListLd1ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListLd1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListLd3ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListLd3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListLd4ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListLd4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListVrReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListVr();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListPcReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListPc();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListWtReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListWt();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListIiReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListIi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListAfReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListAf();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListAf21ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListAf21();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListAf22ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListAf22();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListAFTReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListAFT();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListFiReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListFi();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListMeReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListMe();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListFl1ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListFl1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListFl2ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListFl2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListFl3ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListFl3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListFl6ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListFl6();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListFl7ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListFl7();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListSi1ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListSi1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListSi2ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListSi2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListSi3ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListSi3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListSi4ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListSi4();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListSi5ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListSi5();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListCb1ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListCb1();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListCb2ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListCb2();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListCb2aReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListCb2a();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListCb2bReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListCb2b();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListCb3ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListCb3();
  EXPECT_NE(tags, nullptr);
}

TEST_F(Nikon3MakerNoteTest_447, TagListCb4ReturnsNonNull_447) {
  auto tags = Nikon3MakerNote::tagListCb4();
  EXPECT_NE(tags, nullptr);
}

// =============================================================================
// Print functions - test that they return the ostream reference and produce output
// =============================================================================

TEST_F(Nikon3MakerNoteTest_447, PrintIiIsoSingleValue_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintIiIsoNonZero_447) {
  UShortValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printIiIso(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0002SingleComponent_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0002ThreeComponents_447) {
  UShortValue val;
  val.read("2 0 6");
  auto& result = Nikon3MakerNote::print0x0002(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0007ReturnsOstream_447) {
  AsciiValue val;
  val.read("FINE");
  auto& result = Nikon3MakerNote::print0x0007(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0083ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0083(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0084SingleValue_447) {
  URationalValue val;
  val.read("180/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0084FourValues_447) {
  URationalValue val;
  val.read("180/10 700/10 28/10 56/10");
  auto& result = Nikon3MakerNote::print0x0084(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0085ReturnsOstream_447) {
  URationalValue val;
  val.read("500/100");
  auto& result = Nikon3MakerNote::print0x0085(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0086ReturnsOstream_447) {
  URationalValue val;
  val.read("100/1");
  auto& result = Nikon3MakerNote::print0x0086(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0088ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0089ReturnsOstream_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::print0x0089(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x008bReturnsOstream_447) {
  UByteValue val;
  val.read("0 1 2 3");
  auto& result = Nikon3MakerNote::print0x008b(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocusDistanceReturnsOstream_447) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocusDistanceZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintApertureReturnsOstream_447) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintApertureZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocalReturnsOstream_447) {
  UByteValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocalZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFStopsReturnsOstream_447) {
  UByteValue val;
  val.read("48");
  auto& result = Nikon3MakerNote::printFStops(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExitPupilPositionReturnsOstream_447) {
  UByteValue val;
  val.read("100");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExitPupilPositionZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExitPupilPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashFocalLengthReturnsOstream_447) {
  UByteValue val;
  val.read("50");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashFocalLengthZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashFocalLength(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintRepeatingFlashRateReturnsOstream_447) {
  UByteValue val;
  val.read("10");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintRepeatingFlashRateZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintRepeatingFlashCountReturnsOstream_447) {
  UByteValue val;
  val.read("5");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintRepeatingFlashCountZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x009aReturnsOstream_447) {
  URationalValue val;
  val.read("100/1 100/1");
  auto& result = Nikon3MakerNote::print0x009a(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x009eReturnsOstream_447) {
  UShortValue val;
  val.read("0 0 0 0 0 0 0 0 0 0");
  auto& result = Nikon3MakerNote::print0x009e(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintTimeZoneReturnsOstream_447) {
  ShortValue val;
  val.read("60");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintTimeZoneNegative_447) {
  ShortValue val;
  val.read("-300");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintTimeZoneZero_447) {
  ShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printTimeZone(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintPictureControlReturnsOstream_447) {
  UByteValue val;
  val.read("128");
  auto& result = Nikon3MakerNote::printPictureControl(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintLensId1ReturnsOstream_447) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId1(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintLensId2ReturnsOstream_447) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintLensId3ReturnsOstream_447) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintLensId4ReturnsOstream_447) {
  UByteValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printLensId4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintCameraExposureCompensationReturnsOstream_447) {
  UByteValue val;
  val.read("6");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintCameraExposureCompensationZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printCameraExposureCompensation(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashZoomHeadPositionReturnsOstream_447) {
  UByteValue val;
  val.read("24");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashZoomHeadPositionZero_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocusDistanceLd4ReturnsOstream_447) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocusDistanceLd4Zero_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocusDistanceLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintApertureLd4ReturnsOstream_447) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintApertureLd4Zero_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printApertureLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocalLd4ReturnsOstream_447) {
  UShortValue val;
  val.read("500");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocalLd4Zero_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFocalLd4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintAf2AreaModeReturnsOstream_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintAfPointsInFocusReturnsOstream_447) {
  UShortValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintLensIdWithGroupReturnsOstream_447) {
  UByteValue val;
  val.read("1");
  std::string group = "NikonLd1";
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData1Fl6ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData1Fl7ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData2Fl6ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData2ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData2(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashMasterDataFl6ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashMasterDataFl7ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashMasterDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupAControlDataReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupAControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupBCControlDataReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBCControlData(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupADataFl6ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupADataFl7ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupADataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupBDataFl6ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupBDataFl7ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupCDataFl6ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupCDataFl7ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData3ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData3(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData4ReturnsOstream_447) {
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printExternalFlashData4(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary / edge cases
// =============================================================================

TEST_F(Nikon3MakerNoteTest_447, PrintFocusDistanceMaxValue_447) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocusDistance(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintApertureMaxValue_447) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printAperture(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, PrintFocalMaxValue_447) {
  UByteValue val;
  val.read("255");
  auto& result = Nikon3MakerNote::printFocal(os, val, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0088MultipleComponents_447) {
  UByteValue val;
  val.read("0 0 0 10");
  auto& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintLensIdWithEmptyGroup_447) {
  UByteValue val;
  val.read("0");
  std::string group;
  auto& result = Nikon3MakerNote::printLensId(os, val, nullptr, group);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// ExifData interaction tests
// =============================================================================

TEST_F(Nikon3MakerNoteTest_447, PrintLensId1WithExifData_447) {
  ExifData exifData;
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId1(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintLensId2WithExifData_447) {
  ExifData exifData;
  UByteValue val;
  val.read("0");
  auto& result = Nikon3MakerNote::printLensId2(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, Print0x0089WithExifData_447) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::print0x0089(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintAfPointsInFocusWithExifData_447) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAfPointsInFocus(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(Nikon3MakerNoteTest_447, PrintAf2AreaModeWithExifData_447) {
  ExifData exifData;
  UShortValue val;
  val.read("1");
  auto& result = Nikon3MakerNote::printAf2AreaMode(os, val, &exifData);
  EXPECT_EQ(&result, &os);
}
