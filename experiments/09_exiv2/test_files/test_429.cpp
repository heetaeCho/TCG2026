#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class Nikon3MakerNoteTest_429 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest_429, TagListMe_ReturnsValidTagList_429) {

    auto tagList = Nikon3MakerNote::tagListMe();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0002_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0002(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintAf2AreaMode_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printAf2AreaMode(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0007_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0007(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0083_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0083(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0084_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0084(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0085_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0085(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0086_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0086(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0088_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0088(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintAfPointsInFocus_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printAfPointsInFocus(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x0089_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0089(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x008b_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x008b(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintLensId1_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId1(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintLensId2_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintLensId3_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintLensId4_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintLensId_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId(os, mockValue, &mockMetadata, "group");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistance_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistance(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintAperture_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printAperture(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFocal_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFocal(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFStops_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFStops(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintExitPupilPosition_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printExitPupilPosition(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x009a_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009a(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, Print0x009e_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintIiIso_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printIiIso(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashFocalLength_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintRepeatingFlashRate_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashRate(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintRepeatingFlashCount_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashCount(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData1Fl6_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData2Fl6_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData1Fl7_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData2_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashMasterDataFl6_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashMasterDataFl7_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupAControlData_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupAControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupBCControlData_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBCControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupADataFl6_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupADataFl7_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupBDataFl6_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupBDataFl7_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupCDataFl6_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashGroupCDataFl7_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData3_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintCameraExposureCompensation_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printCameraExposureCompensation(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintExternalFlashData4_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFlashZoomHeadPosition_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashZoomHeadPosition(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintTimeZone_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printTimeZone(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintPictureControl_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printPictureControl(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintApertureLd4_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printApertureLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFocalLd4_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFocalLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_429, PrintFocusDistanceLd4_NormalOperation_429) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistanceLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
