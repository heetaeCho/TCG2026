#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest, TagListLd4_ReturnsCorrectPointer_449) {

    const auto* tagList = Nikon3MakerNote::tagListLd4();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(Nikon3MakerNoteTest, Print0x0002_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0002(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printAf2AreaMode(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, Print0x0083_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::print0x0083(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocus_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printAfPointsInFocus(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printLensId(oss, mockValue, &mockMetadata, "Group");

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printFocusDistance(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAperture_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printAperture(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocal_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printFocal(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFStops_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printFStops(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExitPupilPosition_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printExitPupilPosition(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printIiIso(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashFocalLength_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashFocalLength(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printRepeatingFlashRate(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashCount_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printRepeatingFlashCount(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData1Fl6(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData2(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl6_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashMasterDataFl6(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlData_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashGroupAControlData(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData3_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData3(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, PrintCameraExposureCompensation_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printCameraExposureCompensation(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData4_MetadataNullptr_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printExternalFlashData4(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming it handles null metadata gracefully

}



TEST_F(Nikon3MakerNoteTest, PrintFlashZoomHeadPosition_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printFlashZoomHeadPosition(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintTimeZone_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printTimeZone(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintPictureControl_NormalOperation_449) {

    std::ostringstream oss;

    Nikon3MakerNote::printPictureControl(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}
