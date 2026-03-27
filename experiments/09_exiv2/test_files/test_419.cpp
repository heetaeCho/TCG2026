#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest, TagList_ReturnsConstantReference_419) {

    auto tagList = Nikon3MakerNote::tagList();

    EXPECT_TRUE(tagList != nullptr);

}



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printIiIso(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0002_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0002(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printAf2AreaMode(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0007_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0007(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0083_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0083(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0084_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0084(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0085_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0085(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0086_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0086(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocus_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printAfPointsInFocus(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0088_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0088(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0089_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0089(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x008b_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x008b(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printLensId(oss, mockValue, &mockMetadata, "Group");

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId1_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printLensId1(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId2_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printLensId2(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId3_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printLensId3(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId4_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printLensId4(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFocusDistance(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAperture_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printAperture(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocal_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFocal(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFStops_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFStops(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExitPupilPosition_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printExitPupilPosition(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashFocalLength_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashFocalLength(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printRepeatingFlashRate(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashCount_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printRepeatingFlashCount(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData1Fl6(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData2Fl6(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl7_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData1Fl7(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData2(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl6_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashMasterDataFl6(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl7_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashMasterDataFl7(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlData_DataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupAControlData(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_DataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupBCControlData(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl6_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupADataFl6(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl7_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupADataFl7(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl6_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupBDataFl6(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl7_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupBDataFl7(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl6_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupCDataFl6(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl7_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupCDataFl7(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData3_DataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData3(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintCameraExposureCompensation_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printCameraExposureCompensation(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData4_MetadataDependency_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData4(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashZoomHeadPosition_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashZoomHeadPosition(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintTimeZone_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printTimeZone(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintPictureControl_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printPictureControl(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009a_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x009a(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009e_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x009e(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintApertureLd4_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printApertureLd4(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocalLd4_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFocalLd4(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistanceLd4_NormalOperation_419) {

    std::ostringstream oss;

    Nikon3MakerNote::printFocusDistanceLd4(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}
