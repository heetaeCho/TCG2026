#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_442 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value dummyValue; // Assuming Value is a placeholder for actual data type

    const ExifData* dummyMetadata = nullptr; // Assuming ExifData is a placeholder for actual metadata type



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(Nikon3MakerNoteTest_442, tagListCb2a_ReturnsValidTagInfo_442) {

    auto tagList = Nikon3MakerNote::tagListCb2a();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(Nikon3MakerNoteTest_442, printIiIso_ValidOutput_442) {

    Nikon3MakerNote::printIiIso(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0002_ValidOutput_442) {

    Nikon3MakerNote::print0x0002(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printAf2AreaMode_ValidOutput_442) {

    Nikon3MakerNote::printAf2AreaMode(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0007_ValidOutput_442) {

    Nikon3MakerNote::print0x0007(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0083_ValidOutput_442) {

    Nikon3MakerNote::print0x0083(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0084_ValidOutput_442) {

    Nikon3MakerNote::print0x0084(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0085_ValidOutput_442) {

    Nikon3MakerNote::print0x0085(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0086_ValidOutput_442) {

    Nikon3MakerNote::print0x0086(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0088_ValidOutput_442) {

    Nikon3MakerNote::print0x0088(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printAfPointsInFocus_ValidOutput_442) {

    Nikon3MakerNote::printAfPointsInFocus(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x0089_ValidOutput_442) {

    Nikon3MakerNote::print0x0089(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x008b_ValidOutput_442) {

    Nikon3MakerNote::print0x008b(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printLensId1_ValidOutput_442) {

    Nikon3MakerNote::printLensId1(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printLensId2_ValidOutput_442) {

    Nikon3MakerNote::printLensId2(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printLensId3_ValidOutput_442) {

    Nikon3MakerNote::printLensId3(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printLensId4_ValidOutput_442) {

    Nikon3MakerNote::printLensId4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printLensId_ValidOutput_442) {

    Nikon3MakerNote::printLensId(os, dummyValue, dummyMetadata, "dummyGroup");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFocusDistance_ValidOutput_442) {

    Nikon3MakerNote::printFocusDistance(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printAperture_ValidOutput_442) {

    Nikon3MakerNote::printAperture(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFocal_ValidOutput_442) {

    Nikon3MakerNote::printFocal(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFStops_ValidOutput_442) {

    Nikon3MakerNote::printFStops(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printExitPupilPosition_ValidOutput_442) {

    Nikon3MakerNote::printExitPupilPosition(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashFocalLength_ValidOutput_442) {

    Nikon3MakerNote::printFlashFocalLength(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printRepeatingFlashRate_ValidOutput_442) {

    Nikon3MakerNote::printRepeatingFlashRate(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printRepeatingFlashCount_ValidOutput_442) {

    Nikon3MakerNote::printRepeatingFlashCount(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printExternalFlashData1Fl6_ValidOutput_442) {

    Nikon3MakerNote::printExternalFlashData1Fl6(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printExternalFlashData2Fl6_ValidOutput_442) {

    Nikon3MakerNote::printExternalFlashData2Fl6(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printExternalFlashData1Fl7_ValidOutput_442) {

    Nikon3MakerNote::printExternalFlashData1Fl7(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printExternalFlashData2_ValidOutput_442) {

    Nikon3MakerNote::printExternalFlashData2(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashMasterDataFl6_ValidOutput_442) {

    Nikon3MakerNote::printFlashMasterDataFl6(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashMasterDataFl7_ValidOutput_442) {

    Nikon3MakerNote::printFlashMasterDataFl7(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupAControlData_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupAControlData(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupBCControlData_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupBCControlData(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupADataFl6_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupADataFl6(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupADataFl7_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupADataFl7(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupBDataFl6_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupBDataFl6(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupBDataFl7_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupBDataFl7(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupCDataFl6_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupCDataFl6(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashGroupCDataFl7_ValidOutput_442) {

    Nikon3MakerNote::printFlashGroupCDataFl7(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printExternalFlashData3_ValidOutput_442) {

    Nikon3MakerNote::printExternalFlashData3(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printCameraExposureCompensation_ValidOutput_442) {

    Nikon3MakerNote::printCameraExposureCompensation(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printExternalFlashData4_ValidOutput_442) {

    Nikon3MakerNote::printExternalFlashData4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFlashZoomHeadPosition_ValidOutput_442) {

    Nikon3MakerNote::printFlashZoomHeadPosition(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printTimeZone_ValidOutput_442) {

    Nikon3MakerNote::printTimeZone(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printPictureControl_ValidOutput_442) {

    Nikon3MakerNote::printPictureControl(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x009a_ValidOutput_442) {

    Nikon3MakerNote::print0x009a(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, print0x009e_ValidOutput_442) {

    Nikon3MakerNote::print0x009e(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printApertureLd4_ValidOutput_442) {

    Nikon3MakerNote::printApertureLd4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFocalLd4_ValidOutput_442) {

    Nikon3MakerNote::printFocalLd4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_442, printFocusDistanceLd4_ValidOutput_442) {

    Nikon3MakerNote::printFocusDistanceLd4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}
