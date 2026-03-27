#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class SonyMakerNoteTest : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    ExifData metadata;

};



TEST_F(SonyMakerNoteTest, PrintWhiteBalanceFineTune_Normal_267) {

    SonyMakerNote::printWhiteBalanceFineTune(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstMode_Normal_267) {

    SonyMakerNote::printMultiBurstMode(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstSize_Normal_267) {

    SonyMakerNote::printMultiBurstSize(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAutoHDRStd_Normal_267) {

    SonyMakerNote::printAutoHDRStd(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGM_Normal_267) {

    SonyMakerNote::printWBShiftABGM(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode2_Normal_267) {

    SonyMakerNote::printFocusMode2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFAreaModeSetting_Normal_267) {

    SonyMakerNote::printAFAreaModeSetting(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFlexibleSpotPosition_Normal_267) {

    SonyMakerNote::printFlexibleSpotPosition(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointSelected_Normal_267) {

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointsUsed_Normal_267) {

    SonyMakerNote::printAFPointsUsed(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFTracking_Normal_267) {

    SonyMakerNote::printAFTracking(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocalPlaneAFPointsUsed_Normal_267) {

    SonyMakerNote::printFocalPlaneAFPointsUsed(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGMPrecise_Normal_267) {

    SonyMakerNote::printWBShiftABGMPrecise(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintExposureStandardAdjustment_Normal_267) {

    SonyMakerNote::printExposureStandardAdjustment(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintPixelShiftInfo_Normal_267) {

    SonyMakerNote::printPixelShiftInfo(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusFrameSize_Normal_267) {

    SonyMakerNote::printFocusFrameSize(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorTemperature_Normal_267) {

    SonyMakerNote::printColorTemperature(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorCompensationFilter_Normal_267) {

    SonyMakerNote::printColorCompensationFilter(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintLensSpec_Normal_267) {

    SonyMakerNote::printLensSpec(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode_Normal_267) {

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFMode_Normal_267) {

    SonyMakerNote::printAFMode(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode3_Normal_267) {

    SonyMakerNote::printFocusMode3(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintHighISONoiseReduction2_Normal_267) {

    SonyMakerNote::printHighISONoiseReduction2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc1CameraTemperature_Normal_267) {

    SonyMakerNote::printSonyMisc1CameraTemperature(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusMode_Normal_267) {

    SonyMakerNote::printSony2FpFocusMode(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusPosition2_Normal_267) {

    SonyMakerNote::printSony2FpFocusPosition2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpAmbientTemperature_Normal_267) {

    SonyMakerNote::printSony2FpAmbientTemperature(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bLensZoomPosition_Normal_267) {

    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bFocusPosition2_Normal_267) {

    SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cShotNumberSincePowerUp_Normal_267) {

    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSequenceNumber_Normal_267) {

    SonyMakerNote::printSonyMisc3cSequenceNumber(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cQuality2_Normal_267) {

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSonyImageHeight_Normal_267) {

    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cModelReleaseYear_Normal_267) {

    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}
