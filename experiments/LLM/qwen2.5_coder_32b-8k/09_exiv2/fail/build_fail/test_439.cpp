#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon3MakerNoteTest_439 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value; // Assuming Value is a type used in the actual implementation

    ExifData exifData; // Assuming ExifData is a type used in the actual implementation

};



TEST_F(Nikon3MakerNoteTest_439, TagListSi5_ReturnsConstantValue_439) {

    const auto& result = Nikon3MakerNote::tagListSi5();

    EXPECT_EQ(&result, &Nikon3MakerNote::tagInfoSi5_);

}



TEST_F(Nikon3MakerNoteTest_439, PrintIiIso_NormalOperation_439) {

    Nikon3MakerNote::printIiIso(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printIiIso outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0002_NormalOperation_439) {

    Nikon3MakerNote::print0x0002(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0002 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintAf2AreaMode_NormalOperation_439) {

    Nikon3MakerNote::printAf2AreaMode(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printAf2AreaMode outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0007_NormalOperation_439) {

    Nikon3MakerNote::print0x0007(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0007 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0083_NormalOperation_439) {

    Nikon3MakerNote::print0x0083(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0083 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0084_NormalOperation_439) {

    Nikon3MakerNote::print0x0084(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0084 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0085_NormalOperation_439) {

    Nikon3MakerNote::print0x0085(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0085 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0086_NormalOperation_439) {

    Nikon3MakerNote::print0x0086(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0086 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0088_NormalOperation_439) {

    Nikon3MakerNote::print0x0088(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0088 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintAfPointsInFocus_NormalOperation_439) {

    Nikon3MakerNote::printAfPointsInFocus(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printAfPointsInFocus outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x0089_NormalOperation_439) {

    Nikon3MakerNote::print0x0089(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x0089 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x008b_NormalOperation_439) {

    Nikon3MakerNote::print0x008b(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x008b outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintLensId1_NormalOperation_439) {

    Nikon3MakerNote::printLensId1(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printLensId1 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintLensId2_NormalOperation_439) {

    Nikon3MakerNote::printLensId2(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printLensId2 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintLensId3_NormalOperation_439) {

    Nikon3MakerNote::printLensId3(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printLensId3 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintLensId4_NormalOperation_439) {

    Nikon3MakerNote::printLensId4(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printLensId4 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintLensId_NormalOperation_439) {

    Nikon3MakerNote::printLensId(os, value, &exifData, "group");

    EXPECT_FALSE(os.str().empty()); // Assuming printLensId outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFocusDistance_NormalOperation_439) {

    Nikon3MakerNote::printFocusDistance(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFocusDistance outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintAperture_NormalOperation_439) {

    Nikon3MakerNote::printAperture(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printAperture outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFocal_NormalOperation_439) {

    Nikon3MakerNote::printFocal(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFocal outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFStops_NormalOperation_439) {

    Nikon3MakerNote::printFStops(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFStops outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintExitPupilPosition_NormalOperation_439) {

    Nikon3MakerNote::printExitPupilPosition(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printExitPupilPosition outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashFocalLength_NormalOperation_439) {

    Nikon3MakerNote::printFlashFocalLength(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashFocalLength outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashRate_NormalOperation_439) {

    Nikon3MakerNote::printRepeatingFlashRate(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printRepeatingFlashRate outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintRepeatingFlashCount_NormalOperation_439) {

    Nikon3MakerNote::printRepeatingFlashCount(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printRepeatingFlashCount outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData1Fl6_NormalOperation_439) {

    Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printExternalFlashData1Fl6 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData2Fl6_NormalOperation_439) {

    Nikon3MakerNote::printExternalFlashData2Fl6(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printExternalFlashData2Fl6 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData1Fl7_NormalOperation_439) {

    Nikon3MakerNote::printExternalFlashData1Fl7(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printExternalFlashData1Fl7 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData2_NormalOperation_439) {

    Nikon3MakerNote::printExternalFlashData2(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printExternalFlashData2 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashMasterDataFl6_NormalOperation_439) {

    Nikon3MakerNote::printFlashMasterDataFl6(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashMasterDataFl6 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashMasterDataFl7_NormalOperation_439) {

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashMasterDataFl7 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupAControlData_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupAControlData(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupAControlData outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupBCControlData_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupBCControlData(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupBCControlData outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupADataFl6_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupADataFl6(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupADataFl6 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupADataFl7_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupADataFl7(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupADataFl7 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupBDataFl6_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupBDataFl6(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupBDataFl6 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupBDataFl7_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupBDataFl7(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupBDataFl7 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupCDataFl6_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupCDataFl6(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupCDataFl6 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashGroupCDataFl7_NormalOperation_439) {

    Nikon3MakerNote::printFlashGroupCDataFl7(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashGroupCDataFl7 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData3_NormalOperation_439) {

    Nikon3MakerNote::printExternalFlashData3(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printExternalFlashData3 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintCameraExposureCompensation_NormalOperation_439) {

    Nikon3MakerNote::printCameraExposureCompensation(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printCameraExposureCompensation outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintExternalFlashData4_NormalOperation_439) {

    Nikon3MakerNote::printExternalFlashData4(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printExternalFlashData4 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFlashZoomHeadPosition_NormalOperation_439) {

    Nikon3MakerNote::printFlashZoomHeadPosition(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFlashZoomHeadPosition outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintTimeZone_NormalOperation_439) {

    Nikon3MakerNote::printTimeZone(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printTimeZone outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintPictureControl_NormalOperation_439) {

    Nikon3MakerNote::printPictureControl(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printPictureControl outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x009a_NormalOperation_439) {

    Nikon3MakerNote::print0x009a(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x009a outputs something

}



TEST_F(Nikon3MakerNoteTest_439, Print0x009e_NormalOperation_439) {

    Nikon3MakerNote::print0x009e(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x009e outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintApertureLd4_NormalOperation_439) {

    Nikon3MakerNote::printApertureLd4(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printApertureLd4 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFocalLd4_NormalOperation_439) {

    Nikon3MakerNote::printFocalLd4(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFocalLd4 outputs something

}



TEST_F(Nikon3MakerNoteTest_439, PrintFocusDistanceLd4_NormalOperation_439) {

    Nikon3MakerNote::printFocusDistanceLd4(os, value, &exifData);

    EXPECT_FALSE(os.str().empty()); // Assuming printFocusDistanceLd4 outputs something

}
