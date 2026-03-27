#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_435 : public ::testing::Test {

protected:

    std::ostringstream os;

    MockValue mockValue;  // Assuming Value is an interface or class that can be mocked

    const ExifData* metadata = nullptr;

};



TEST_F(Nikon3MakerNoteTest_435, Print0x0002_NormalOperation_435) {

    Nikon3MakerNote::print0x0002(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintAf2AreaMode_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printAf2AreaMode(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x0007_NormalOperation_435) {

    Nikon3MakerNote::print0x0007(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x0083_NormalOperation_435) {

    Nikon3MakerNote::print0x0083(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x0084_NormalOperation_435) {

    Nikon3MakerNote::print0x0084(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x0085_NormalOperation_435) {

    Nikon3MakerNote::print0x0085(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x0086_NormalOperation_435) {

    Nikon3MakerNote::print0x0086(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x0088_NormalOperation_435) {

    Nikon3MakerNote::print0x0088(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintAfPointsInFocus_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printAfPointsInFocus(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x0089_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::print0x0089(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x008B_NormalOperation_435) {

    Nikon3MakerNote::print0x008b(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintLensId1_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printLensId1(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintLensId2_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printLensId2(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintLensId3_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printLensId3(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintLensId4_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printLensId4(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintLensId_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printLensId(os, mockValue, &exifData, "Group");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFocusDistance_NormalOperation_435) {

    Nikon3MakerNote::printFocusDistance(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintAperture_NormalOperation_435) {

    Nikon3MakerNote::printAperture(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFocal_NormalOperation_435) {

    Nikon3MakerNote::printFocal(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFStops_NormalOperation_435) {

    Nikon3MakerNote::printFStops(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintExitPupilPosition_NormalOperation_435) {

    Nikon3MakerNote::printExitPupilPosition(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashFocalLength_NormalOperation_435) {

    Nikon3MakerNote::printFlashFocalLength(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintRepeatingFlashRate_NormalOperation_435) {

    Nikon3MakerNote::printRepeatingFlashRate(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintRepeatingFlashCount_NormalOperation_435) {

    Nikon3MakerNote::printRepeatingFlashCount(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintExternalFlashData1Fl6_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintExternalFlashData2Fl6_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printExternalFlashData2Fl6(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintExternalFlashData1Fl7_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printExternalFlashData1Fl7(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintExternalFlashData2_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printExternalFlashData2(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashMasterDataFl6_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashMasterDataFl6(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashMasterDataFl7_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashMasterDataFl7(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupAControlData_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupAControlData(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupBCControlData_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupBCControlData(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupADataFl6_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupADataFl7_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupADataFl7(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupBDataFl6_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupBDataFl6(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupBDataFl7_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupBDataFl7(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupCDataFl6_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupCDataFl6(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashGroupCDataFl7_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printFlashGroupCDataFl7(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintExternalFlashData3_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printExternalFlashData3(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintCameraExposureCompensation_NormalOperation_435) {

    Nikon3MakerNote::printCameraExposureCompensation(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintExternalFlashData4_NormalOperation_435) {

    const ExifData exifData;

    Nikon3MakerNote::printExternalFlashData4(os, mockValue, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFlashZoomHeadPosition_NormalOperation_435) {

    Nikon3MakerNote::printFlashZoomHeadPosition(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintTimeZone_NormalOperation_435) {

    Nikon3MakerNote::printTimeZone(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintPictureControl_NormalOperation_435) {

    Nikon3MakerNote::printPictureControl(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x009A_NormalOperation_435) {

    Nikon3MakerNote::print0x009a(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, Print0x009E_NormalOperation_435) {

    Nikon3MakerNote::print0x009e(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintIiIso_NormalOperation_435) {

    Nikon3MakerNote::printIiIso(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintApertureLd4_NormalOperation_435) {

    Nikon3MakerNote::printApertureLd4(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFocalLd4_NormalOperation_435) {

    Nikon3MakerNote::printFocalLd4(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_435, PrintFocusDistanceLd4_NormalOperation_435) {

    Nikon3MakerNote::printFocusDistanceLd4(os, mockValue, metadata);

    EXPECT_FALSE(os.str().empty());

}
