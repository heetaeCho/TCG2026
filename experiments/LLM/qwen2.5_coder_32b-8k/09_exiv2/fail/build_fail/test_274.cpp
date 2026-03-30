#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class SonyMakerNoteTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value mockValue;

    const ExifData* mockMetadata = nullptr;

};



TEST_F(SonyMakerNoteTest, PrintWhiteBalanceFineTune_NormalOperation_274) {

    SonyMakerNote::printWhiteBalanceFineTune(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstMode_NormalOperation_274) {

    SonyMakerNote::printMultiBurstMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstSize_NormalOperation_274) {

    SonyMakerNote::printMultiBurstSize(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAutoHDRStd_NormalOperation_274) {

    SonyMakerNote::printAutoHDRStd(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGM_NormalOperation_274) {

    SonyMakerNote::printWBShiftABGM(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode2_NormalOperation_274) {

    SonyMakerNote::printFocusMode2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFAreaModeSetting_NormalOperation_274) {

    SonyMakerNote::printAFAreaModeSetting(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFlexibleSpotPosition_NormalOperation_274) {

    SonyMakerNote::printFlexibleSpotPosition(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointSelected_NormalOperation_274) {

    SonyMakerNote::printAFPointSelected(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointsUsed_NormalOperation_274) {

    SonyMakerNote::printAFPointsUsed(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFTracking_NormalOperation_274) {

    SonyMakerNote::printAFTracking(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocalPlaneAFPointsUsed_NormalOperation_274) {

    SonyMakerNote::printFocalPlaneAFPointsUsed(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGMPrecise_NormalOperation_274) {

    SonyMakerNote::printWBShiftABGMPrecise(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintExposureStandardAdjustment_NormalOperation_274) {

    SonyMakerNote::printExposureStandardAdjustment(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintPixelShiftInfo_NormalOperation_274) {

    SonyMakerNote::printPixelShiftInfo(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusFrameSize_NormalOperation_274) {

    SonyMakerNote::printFocusFrameSize(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorTemperature_NormalOperation_274) {

    SonyMakerNote::printColorTemperature(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorCompensationFilter_NormalOperation_274) {

    SonyMakerNote::printColorCompensationFilter(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintLensSpec_NormalOperation_274) {

    SonyMakerNote::printLensSpec(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintImageSize_NormalOperation_274) {

    SonyMakerNote::printImageSize(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode_NormalOperation_274) {

    SonyMakerNote::printFocusMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFMode_NormalOperation_274) {

    SonyMakerNote::printAFMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode3_NormalOperation_274) {

    SonyMakerNote::printFocusMode3(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintHighISONoiseReduction2_NormalOperation_274) {

    SonyMakerNote::printHighISONoiseReduction2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpAmbientTemperature_NormalOperation_274) {

    SonyMakerNote::printSony2FpAmbientTemperature(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusMode_NormalOperation_274) {

    SonyMakerNote::printSony2FpFocusMode(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusPosition2_NormalOperation_274) {

    SonyMakerNote::printSony2FpFocusPosition2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc1CameraTemperature_NormalOperation_274) {

    SonyMakerNote::printSonyMisc1CameraTemperature(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bLensZoomPosition_NormalOperation_274) {

    SonyMakerNote::printSonyMisc2bLensZoomPosition(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bFocusPosition2_NormalOperation_274) {

    SonyMakerNote::printSonyMisc2bFocusPosition2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cShotNumberSincePowerUp_NormalOperation_274) {

    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSequenceNumber_NormalOperation_274) {

    SonyMakerNote::printSonyMisc3cSequenceNumber(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cQuality2_NormalOperation_274) {

    SonyMakerNote::printSonyMisc3cQuality2(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSonyImageHeight_NormalOperation_274) {

    SonyMakerNote::printSonyMisc3cSonyImageHeight(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cModelReleaseYear_NormalOperation_274) {

    SonyMakerNote::printSonyMisc3cModelReleaseYear(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}
