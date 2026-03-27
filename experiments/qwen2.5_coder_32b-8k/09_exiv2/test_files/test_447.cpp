#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_447 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* metadata = nullptr;

};



TEST_F(Nikon3MakerNoteTest_447, TagListLd2_ReturnsConstantValue_447) {

    auto result = Nikon3MakerNote::tagListLd2();

    EXPECT_NE(nullptr, result);

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0002_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0002(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintAf2AreaMode_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printAf2AreaMode(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0007_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0007(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0083_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0083(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0084_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0084(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0085_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0085(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0086_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0086(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0088_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0088(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintAfPointsInFocus_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printAfPointsInFocus(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x0089_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x0089(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x008b_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x008b(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintLensId1_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printLensId1(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintLensId2_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printLensId2(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintLensId3_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printLensId3(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintLensId4_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printLensId4(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintLensId_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printLensId(os, value, metadata, "group");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFocusDistance_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFocusDistance(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintAperture_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printAperture(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFocal_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFocal(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFStops_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFStops(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintExitPupilPosition_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printExitPupilPosition(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintIiIso_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printIiIso(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashFocalLength_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashFocalLength(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintRepeatingFlashRate_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printRepeatingFlashRate(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintRepeatingFlashCount_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printRepeatingFlashCount(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData1Fl6_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printExternalFlashData1Fl6(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData2Fl6_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printExternalFlashData2Fl6(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData1Fl7_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printExternalFlashData1Fl7(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData2_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printExternalFlashData2(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashMasterDataFl6_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashMasterDataFl6(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashMasterDataFl7_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupAControlData_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupAControlData(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupBCControlData_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupBCControlData(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupADataFl6_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupADataFl6(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupADataFl7_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupADataFl7(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupBDataFl6_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupBDataFl6(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupBDataFl7_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupBDataFl7(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupCDataFl6_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupCDataFl6(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashGroupCDataFl7_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashGroupCDataFl7(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData3_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printExternalFlashData3(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintCameraExposureCompensation_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printCameraExposureCompensation(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintExternalFlashData4_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printExternalFlashData4(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFlashZoomHeadPosition_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFlashZoomHeadPosition(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintTimeZone_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printTimeZone(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintPictureControl_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printPictureControl(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x009a_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x009a(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, Print0x009e_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::print0x009e(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintApertureLd4_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printApertureLd4(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFocalLd4_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFocalLd4(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_447, PrintFocusDistanceLd4_NormalOperation_447) {

    os.str("");

    Nikon3MakerNote::printFocusDistanceLd4(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}
