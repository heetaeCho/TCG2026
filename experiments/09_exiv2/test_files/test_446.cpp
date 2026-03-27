#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_446 : public ::testing::Test {

protected:

    Value dummyValue;

    ExifData* mockMetadata = nullptr; // Assuming ExifData is a pointer for mocking purposes

};



TEST_F(Nikon3MakerNoteTest_446, TagListLd1_ReturnsExpectedTagInfo_446) {

    const auto& tagList = Nikon3MakerNote::tagListLd1();

    EXPECT_TRUE(tagList != nullptr);

}



TEST_F(Nikon3MakerNoteTest_446, PrintIiIso_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printIiIso(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0002_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0002(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintAf2AreaMode_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printAf2AreaMode(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0007_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0007(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0083_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0083(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0084_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0084(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0085_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0085(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0086_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0086(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0088_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0088(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintAfPointsInFocus_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printAfPointsInFocus(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x0089_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0089(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x008b_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x008b(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintLensId1_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId1(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintLensId2_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId2(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintLensId3_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId3(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintLensId4_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId4(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintLensId_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId(os, dummyValue, mockMetadata, "");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFocusDistance_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistance(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintAperture_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printAperture(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFocal_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFocal(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFStops_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFStops(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintExitPupilPosition_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printExitPupilPosition(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashFocalLength_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashFocalLength(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintRepeatingFlashRate_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashRate(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintRepeatingFlashCount_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashCount(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData1Fl6_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData2Fl6_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2Fl6(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData1Fl7_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl7(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData2_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashMasterDataFl6_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl6(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashMasterDataFl7_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl7(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupAControlData_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupAControlData(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupBCControlData_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBCControlData(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupADataFl6_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl6(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupADataFl7_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl7(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupBDataFl6_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl6(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupBDataFl7_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl7(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupCDataFl6_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl6(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashGroupCDataFl7_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl7(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData3_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData3(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintCameraExposureCompensation_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printCameraExposureCompensation(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintExternalFlashData4_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData4(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFlashZoomHeadPosition_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashZoomHeadPosition(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintTimeZone_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printTimeZone(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintPictureControl_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printPictureControl(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x009a_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009a(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, Print0x009e_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009e(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintApertureLd4_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printApertureLd4(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFocalLd4_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFocalLd4(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_446, PrintFocusDistanceLd4_OperatesNormally_446) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistanceLd4(os, dummyValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
