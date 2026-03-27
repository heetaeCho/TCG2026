#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



namespace {



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNoteTest() = default;

};



TEST_F(Nikon3MakerNoteTest, TagListCb4_ReturnsExpectedValue_445) {

    const auto& tagList = Nikon3MakerNote::tagListCb4();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printIiIso(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0002_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0002(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printAf2AreaMode(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0007_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0007(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0083_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0083(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0084_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0084(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0085_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0085(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0086_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0086(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0088_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0088(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocus_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printAfPointsInFocus(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0089_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x0089(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x008b_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x008b(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId1_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printLensId1(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId2_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printLensId2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId3_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printLensId3(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId4_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printLensId4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printLensId(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFocusDistance(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAperture_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printAperture(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocal_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFocal(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFStops_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFStops(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExitPupilPosition_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printExitPupilPosition(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashFocalLength_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashFocalLength(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printRepeatingFlashRate(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashCount_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printRepeatingFlashCount(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printExternalFlashData2Fl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl7_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printExternalFlashData1Fl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl6_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashMasterDataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl7_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlData_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupAControlData(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupBCControlData(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl6_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupADataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl7_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupADataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl6_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupBDataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl7_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupBDataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl6_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupCDataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl7_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData3_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printExternalFlashData3(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintCameraExposureCompensation_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printCameraExposureCompensation(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData4_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printExternalFlashData4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashZoomHeadPosition_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFlashZoomHeadPosition(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintTimeZone_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printTimeZone(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintPictureControl_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printPictureControl(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009a_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x009a(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009e_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::print0x009e(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintApertureLd4_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printApertureLd4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocalLd4_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFocalLd4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistanceLd4_NormalOperation_445) {

    std::ostringstream os;

    Value value; // Assuming Value is default-constructible

    ExifData metadata;

    Nikon3MakerNote::printFocusDistanceLd4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



} // namespace
