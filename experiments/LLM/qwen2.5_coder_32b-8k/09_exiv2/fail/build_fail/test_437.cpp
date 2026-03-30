#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include <sstream>



using namespace testing;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest, TagListSi3_ReturnsExpectedPointer_437) {

    const TagInfo* result = Nikon3MakerNote::tagListSi3();

    EXPECT_NE(result, nullptr);

}



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printIiIso(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0002_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0002(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printAf2AreaMode(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0007_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0007(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0083_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0083(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0084_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0084(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0085_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0085(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0086_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0086(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0088_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0088(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocus_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printAfPointsInFocus(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0089_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0089(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x008b_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x008b(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId1_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId1(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId2_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId3_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId4_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId(os, mockValue, &mockMetadata, "Group");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistance(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAperture_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printAperture(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocal_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFocal(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFStops_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFStops(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExitPupilPosition_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printExitPupilPosition(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashFocalLength_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashRate(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashCount_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashCount(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl7_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl6_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl7_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlData_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupAControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBCControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl6_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl7_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl6_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl7_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl6_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl7_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData3_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintCameraExposureCompensation_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printCameraExposureCompensation(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData4_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashZoomHeadPosition_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashZoomHeadPosition(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintTimeZone_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printTimeZone(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintPictureControl_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printPictureControl(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009a_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009a(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009e_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintApertureLd4_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printApertureLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocalLd4_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFocalLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistanceLd4_NormalOperation_437) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistanceLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
