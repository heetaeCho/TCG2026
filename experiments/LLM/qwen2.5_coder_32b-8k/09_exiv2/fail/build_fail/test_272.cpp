#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class SonyMakerNoteTest_272 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value mockValue;

    const ExifData* mockMetadata = nullptr; // Assuming ExifData is a valid type in the context

};



TEST_F(SonyMakerNoteTest_272, TagListSonyMisc2b_ReturnsCorrectTagInfo_272) {

    auto tagList = SonyMakerNote::tagListSonyMisc2b();

    EXPECT_TRUE(tagList != nullptr); // Assuming tagList returns a non-null pointer for valid tags

}



TEST_F(SonyMakerNoteTest_272, PrintWhiteBalanceFineTune_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printWhiteBalanceFineTune(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintMultiBurstMode_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printMultiBurstMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintMultiBurstSize_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printMultiBurstSize(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintAutoHDRStd_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printAutoHDRStd(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintWBShiftABGM_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printWBShiftABGM(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintFocusMode2_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printFocusMode2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintAFAreaModeSetting_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printAFAreaModeSetting(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintFlexibleSpotPosition_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printFlexibleSpotPosition(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintAFPointSelected_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printAFPointSelected(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintAFPointsUsed_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printAFPointsUsed(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintAFTracking_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printAFTracking(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintFocalPlaneAFPointsUsed_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printFocalPlaneAFPointsUsed(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintWBShiftABGMPrecise_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printWBShiftABGMPrecise(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintExposureStandardAdjustment_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printExposureStandardAdjustment(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintPixelShiftInfo_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printPixelShiftInfo(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintFocusFrameSize_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printFocusFrameSize(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintColorTemperature_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printColorTemperature(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintColorCompensationFilter_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printColorCompensationFilter(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintLensSpec_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printLensSpec(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintImageSize_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printImageSize(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintFocusMode_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printFocusMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintAFMode_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printAFMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintFocusMode3_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printFocusMode3(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintHighISONoiseReduction2_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printHighISONoiseReduction2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc1CameraTemperature_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc1CameraTemperature(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSony2FpAmbientTemperature_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSony2FpAmbientTemperature(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSony2FpFocusMode_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSony2FpFocusMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSony2FpFocusPosition2_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSony2FpFocusPosition2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc2bLensZoomPosition_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc2bLensZoomPosition(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc2bFocusPosition2_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc2bFocusPosition2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cShotNumberSincePowerUp_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cSequenceNumber_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc3cSequenceNumber(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cQuality2_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc3cQuality2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cSonyImageHeight_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc3cSonyImageHeight(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(SonyMakerNoteTest_272, PrintSonyMisc3cModelReleaseYear_NormalOperation_272) {

    std::ostringstream oss;

    SonyMakerNote::printSonyMisc3cModelReleaseYear(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}
