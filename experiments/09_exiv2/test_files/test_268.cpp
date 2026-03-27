#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/sonymn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class SonyMakerNoteTest : public ::testing::Test {

protected:

    Value dummyValue;

    const ExifData* dummyMetadata = nullptr;

};



TEST_F(SonyMakerNoteTest, PrintWhiteBalanceFineTune_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printWhiteBalanceFineTune(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstMode_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printMultiBurstMode(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintMultiBurstSize_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printMultiBurstSize(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAutoHDRStd_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printAutoHDRStd(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGM_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printWBShiftABGM(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode2_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFAreaModeSetting_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printAFAreaModeSetting(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFlexibleSpotPosition_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printFlexibleSpotPosition(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointSelected_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printAFPointSelected(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFPointsUsed_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printAFPointsUsed(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFTracking_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printAFTracking(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocalPlaneAFPointsUsed_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printFocalPlaneAFPointsUsed(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintWBShiftABGMPrecise_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printWBShiftABGMPrecise(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintExposureStandardAdjustment_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printExposureStandardAdjustment(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintPixelShiftInfo_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printPixelShiftInfo(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusFrameSize_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printFocusFrameSize(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorTemperature_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printColorTemperature(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintColorCompensationFilter_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printColorCompensationFilter(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintLensSpec_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printLensSpec(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printFocusMode(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintImageSize_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printImageSize(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintAFMode_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printAFMode(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintFocusMode3_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printFocusMode3(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintHighISONoiseReduction2_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printHighISONoiseReduction2(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc1CameraTemperature_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc1CameraTemperature(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpAmbientTemperature_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSony2FpAmbientTemperature(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusMode_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSony2FpFocusMode(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSony2FpFocusPosition2_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSony2FpFocusPosition2(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bLensZoomPosition_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc2bFocusPosition2_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc2bFocusPosition2(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cShotNumberSincePowerUp_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSequenceNumber_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc3cSequenceNumber(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cQuality2_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc3cQuality2(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cSonyImageHeight_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(SonyMakerNoteTest, PrintSonyMisc3cModelReleaseYear_NormalOperation_268) {

    std::ostringstream os;

    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}
