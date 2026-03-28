#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace ::testing;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_444 : public Test {

protected:

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be mocked or used directly

    ExifData mockMetadata; // Assuming ExifData is a type that can be mocked or used directly

};



TEST_F(Nikon3MakerNoteTest_444, PrintIiIso_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printIiIso(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0002_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0002(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintAf2AreaMode_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printAf2AreaMode(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0007_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0007(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0083_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0083(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0084_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0084(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0085_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0085(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0086_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0086(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0088_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0088(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintAfPointsInFocus_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printAfPointsInFocus(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x0089_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x0089(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x008b_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x008b(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintLensId1_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printLensId1(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintLensId2_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printLensId2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintLensId3_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printLensId3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintLensId4_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printLensId4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintLensId_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printLensId(os, mockValue, &mockMetadata, "Group");

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistance_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFocusDistance(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintAperture_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printAperture(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFocal_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFocal(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFStops_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFStops(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintExitPupilPosition_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printExitPupilPosition(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashFocalLength_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintRepeatingFlashRate_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printRepeatingFlashRate(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintRepeatingFlashCount_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printRepeatingFlashCount(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData1Fl6_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData2Fl6_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData2Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData1Fl7_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData1Fl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData2_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashMasterDataFl6_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashMasterDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashMasterDataFl7_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashMasterDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupAControlData_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupAControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupBCControlData_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupBCControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupADataFl6_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupADataFl7_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupADataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupBDataFl6_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupBDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupBDataFl7_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupBDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupCDataFl6_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupCDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashGroupCDataFl7_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupCDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData3_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintCameraExposureCompensation_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printCameraExposureCompensation(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintExternalFlashData4_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFlashZoomHeadPosition_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFlashZoomHeadPosition(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintTimeZone_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printTimeZone(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintPictureControl_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printPictureControl(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x009a_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x009a(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, Print0x009e_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::print0x009e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintApertureLd4_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printApertureLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFocalLd4_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFocalLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}



TEST_F(Nikon3MakerNoteTest_444, PrintFocusDistanceLd4_NormalOperation_444) {

    Exiv2::Internal::Nikon3MakerNote::printFocusDistanceLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty()); // Expect some output

}
