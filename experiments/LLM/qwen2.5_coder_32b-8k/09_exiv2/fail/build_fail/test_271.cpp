#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2::Internal;



class SonyMakerNoteTest : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    std::ostringstream os;

    Value mockValue;

    const ExifData* mockMetadata = nullptr;

};



TEST_F(SonyMakerNoteTest, PrintWhiteBalanceFineTune_NormalOperation_271) {

    sonyMakerNote.printWhiteBalanceFineTune(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstMode_NormalOperation_271) {

    sonyMakerNote.printMultiBurstMode(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstSize_NormalOperation_271) {

    sonyMakerNote.printMultiBurstSize(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAutoHDRStd_NormalOperation_271) {

    sonyMakerNote.printAutoHDRStd(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGM_NormalOperation_271) {

    sonyMakerNote.printWBShiftABGM(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode2_NormalOperation_271) {

    sonyMakerNote.printFocusMode2(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFAreaModeSetting_NormalOperation_271) {

    sonyMakerNote.printAFAreaModeSetting(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFlexibleSpotPosition_NormalOperation_271) {

    sonyMakerNote.printFlexibleSpotPosition(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointSelected_NormalOperation_271) {

    sonyMakerNote.printAFPointSelected(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointsUsed_NormalOperation_271) {

    sonyMakerNote.printAFPointsUsed(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFTracking_NormalOperation_271) {

    sonyMakerNote.printAFTracking(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocalPlaneAFPointsUsed_NormalOperation_271) {

    sonyMakerNote.printFocalPlaneAFPointsUsed(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGMPrecise_NormalOperation_271) {

    sonyMakerNote.printWBShiftABGMPrecise(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintExposureStandardAdjustment_NormalOperation_271) {

    sonyMakerNote.printExposureStandardAdjustment(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintPixelShiftInfo_NormalOperation_271) {

    sonyMakerNote.printPixelShiftInfo(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusFrameSize_NormalOperation_271) {

    sonyMakerNote.printFocusFrameSize(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorTemperature_NormalOperation_271) {

    sonyMakerNote.printColorTemperature(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorCompensationFilter_NormalOperation_271) {

    sonyMakerNote.printColorCompensationFilter(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintLensSpec_NormalOperation_271) {

    sonyMakerNote.printLensSpec(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode_NormalOperation_271) {

    sonyMakerNote.printFocusMode(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFMode_NormalOperation_271) {

    sonyMakerNote.printAFMode(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode3_NormalOperation_271) {

    sonyMakerNote.printFocusMode3(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintHighISONoiseReduction2_NormalOperation_271) {

    sonyMakerNote.printHighISONoiseReduction2(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc1CameraTemperature_NormalOperation_271) {

    sonyMakerNote.printSonyMisc1CameraTemperature(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusMode_NormalOperation_271) {

    sonyMakerNote.printSony2FpFocusMode(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusPosition2_NormalOperation_271) {

    sonyMakerNote.printSony2FpFocusPosition2(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpAmbientTemperature_NormalOperation_271) {

    sonyMakerNote.printSony2FpAmbientTemperature(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bLensZoomPosition_NormalOperation_271) {

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bFocusPosition2_NormalOperation_271) {

    sonyMakerNote.printSonyMisc2bFocusPosition2(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cShotNumberSincePowerUp_NormalOperation_271) {

    sonyMakerNote.printSonyMisc3cShotNumberSincePowerUp(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSequenceNumber_NormalOperation_271) {

    sonyMakerNote.printSonyMisc3cSequenceNumber(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cQuality2_NormalOperation_271) {

    sonyMakerNote.printSonyMisc3cQuality2(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSonyImageHeight_NormalOperation_271) {

    sonyMakerNote.printSonyMisc3cSonyImageHeight(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cModelReleaseYear_NormalOperation_271) {

    sonyMakerNote.printSonyMisc3cModelReleaseYear(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
