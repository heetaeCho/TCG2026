#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    ExifData metadata;

    Value value;

};



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printIiIso(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0002_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0002(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printAf2AreaMode(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0007_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0007(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0083_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0083(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0084_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0084(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0085_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0085(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0086_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0086(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0088_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0088(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocus_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printAfPointsInFocus(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x0089_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x0089(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x008b_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x008b(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintLensId1_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printLensId1(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintLensId2_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printLensId2(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintLensId3_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printLensId3(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintLensId4_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printLensId4(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printLensId(oss, value, &metadata, "group");

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFocusDistance(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintAperture_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printAperture(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFocal_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFocal(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFStops_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFStops(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintExitPupilPosition_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printExitPupilPosition(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashFocalLength_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashFocalLength(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printRepeatingFlashRate(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashCount_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printRepeatingFlashCount(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printExternalFlashData2Fl6(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl7_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printExternalFlashData1Fl7(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printExternalFlashData2(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl6_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashMasterDataFl6(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl7_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashMasterDataFl7(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlData_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupAControlData(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupBCControlData(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl6_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupADataFl6(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl7_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupADataFl7(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl6_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupBDataFl6(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl7_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupBDataFl7(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl6_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupCDataFl6(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl7_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashGroupCDataFl7(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData3_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printExternalFlashData3(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintCameraExposureCompensation_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printCameraExposureCompensation(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData4_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printExternalFlashData4(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFlashZoomHeadPosition_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFlashZoomHeadPosition(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintTimeZone_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printTimeZone(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintPictureControl_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printPictureControl(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x009a_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x009a(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, Print0x009e_NormalOperation_436) {

    auto& result = Nikon3MakerNote::print0x009e(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintApertureLd4_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printApertureLd4(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFocalLd4_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFocalLd4(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistanceLd4_NormalOperation_436) {

    auto& result = Nikon3MakerNote::printFocusDistanceLd4(oss, value, &metadata);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}
