#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::StrEq;



class Nikon3MakerNoteTest_427 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* metadata = nullptr;

};



TEST_F(Nikon3MakerNoteTest_427, TagListAFT_ReturnsExpectedValue_427) {

    auto tagList = Nikon3MakerNote::tagListAFT();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(Nikon3MakerNoteTest_427, PrintIiIso_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for IiIso"; // Placeholder for actual expected output

    Nikon3MakerNote::printIiIso(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0002_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0002"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0002(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintAf2AreaMode_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for Af2AreaMode"; // Placeholder for actual expected output

    Nikon3MakerNote::printAf2AreaMode(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0007_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0007"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0007(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0083_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0083"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0083(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0084_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0084"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0084(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0085_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0085"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0085(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0086_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0086"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0086(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0088_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0088"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0088(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintAfPointsInFocus_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for AfPointsInFocus"; // Placeholder for actual expected output

    Nikon3MakerNote::printAfPointsInFocus(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x0089_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x0089"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x0089(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x008b_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x008b"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x008b(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintLensId1_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for LensId1"; // Placeholder for actual expected output

    Nikon3MakerNote::printLensId1(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintLensId2_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for LensId2"; // Placeholder for actual expected output

    Nikon3MakerNote::printLensId2(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintLensId3_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for LensId3"; // Placeholder for actual expected output

    Nikon3MakerNote::printLensId3(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintLensId4_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for LensId4"; // Placeholder for actual expected output

    Nikon3MakerNote::printLensId4(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistance_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FocusDistance"; // Placeholder for actual expected output

    Nikon3MakerNote::printFocusDistance(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintAperture_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for Aperture"; // Placeholder for actual expected output

    Nikon3MakerNote::printAperture(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFocal_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for Focal"; // Placeholder for actual expected output

    Nikon3MakerNote::printFocal(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFStops_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FStops"; // Placeholder for actual expected output

    Nikon3MakerNote::printFStops(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintExitPupilPosition_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ExitPupilPosition"; // Placeholder for actual expected output

    Nikon3MakerNote::printExitPupilPosition(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashFocalLength_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashFocalLength"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashFocalLength(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashRate_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for RepeatingFlashRate"; // Placeholder for actual expected output

    Nikon3MakerNote::printRepeatingFlashRate(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintRepeatingFlashCount_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for RepeatingFlashCount"; // Placeholder for actual expected output

    Nikon3MakerNote::printRepeatingFlashCount(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData1Fl6_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ExternalFlashData1Fl6"; // Placeholder for actual expected output

    Nikon3MakerNote::printExternalFlashData1Fl6(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData2Fl6_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ExternalFlashData2Fl6"; // Placeholder for actual expected output

    Nikon3MakerNote::printExternalFlashData2Fl6(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData1Fl7_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ExternalFlashData1Fl7"; // Placeholder for actual expected output

    Nikon3MakerNote::printExternalFlashData1Fl7(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData2_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ExternalFlashData2"; // Placeholder for actual expected output

    Nikon3MakerNote::printExternalFlashData2(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashMasterDataFl6_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashMasterDataFl6"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashMasterDataFl6(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashMasterDataFl7_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashMasterDataFl7"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupAControlData_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupAControlData"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupAControlData(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupBCControlData_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupBCControlData"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupBCControlData(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupADataFl6_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupADataFl6"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupADataFl6(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupADataFl7_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupADataFl7"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupADataFl7(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupBDataFl6_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupBDataFl6"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupBDataFl6(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupBDataFl7_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupBDataFl7"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupBDataFl7(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupCDataFl6_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupCDataFl6"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupCDataFl6(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashGroupCDataFl7_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashGroupCDataFl7"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashGroupCDataFl7(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData3_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ExternalFlashData3"; // Placeholder for actual expected output

    Nikon3MakerNote::printExternalFlashData3(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintCameraExposureCompensation_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for CameraExposureCompensation"; // Placeholder for actual expected output

    Nikon3MakerNote::printCameraExposureCompensation(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintExternalFlashData4_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ExternalFlashData4"; // Placeholder for actual expected output

    Nikon3MakerNote::printExternalFlashData4(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFlashZoomHeadPosition_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FlashZoomHeadPosition"; // Placeholder for actual expected output

    Nikon3MakerNote::printFlashZoomHeadPosition(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintTimeZone_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for TimeZone"; // Placeholder for actual expected output

    Nikon3MakerNote::printTimeZone(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintPictureControl_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for PictureControl"; // Placeholder for actual expected output

    Nikon3MakerNote::printPictureControl(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x009a_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x009a"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x009a(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, Print0x009e_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for 0x009e"; // Placeholder for actual expected output

    Nikon3MakerNote::print0x009e(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintApertureLd4_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for ApertureLd4"; // Placeholder for actual expected output

    Nikon3MakerNote::printApertureLd4(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFocalLd4_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FocalLd4"; // Placeholder for actual expected output

    Nikon3MakerNote::printFocalLd4(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}



TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceLd4_NormalOperation_427) {

    std::string expectedOutput = "Expected Output for FocusDistanceLd4"; // Placeholder for actual expected output

    Nikon3MakerNote::printFocusDistanceLd4(os, value, metadata);

    EXPECT_EQ(os.str(), expectedOutput); 

}
