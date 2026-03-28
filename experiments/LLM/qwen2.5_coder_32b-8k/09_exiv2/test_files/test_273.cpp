#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.hpp"



using namespace Exiv2::Internal;



class SonyMakerNoteTest_273 : public ::testing::Test {

protected:

    Value dummyValue;

    const ExifData* dummyMetadata = nullptr;



    std::ostringstream oss;

};



TEST_F(SonyMakerNoteTest_273, PrintWhiteBalanceFineTune_NormalOperation_273) {

    SonyMakerNote::printWhiteBalanceFineTune(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintMultiBurstMode_NormalOperation_273) {

    SonyMakerNote::printMultiBurstMode(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintMultiBurstSize_NormalOperation_273) {

    SonyMakerNote::printMultiBurstSize(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintAutoHDRStd_NormalOperation_273) {

    SonyMakerNote::printAutoHDRStd(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintWBShiftABGM_NormalOperation_273) {

    SonyMakerNote::printWBShiftABGM(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintFocusMode2_NormalOperation_273) {

    SonyMakerNote::printFocusMode2(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintAFAreaModeSetting_NormalOperation_273) {

    SonyMakerNote::printAFAreaModeSetting(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintFlexibleSpotPosition_NormalOperation_273) {

    SonyMakerNote::printFlexibleSpotPosition(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintAFPointSelected_NormalOperation_273) {

    SonyMakerNote::printAFPointSelected(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintAFPointsUsed_NormalOperation_273) {

    SonyMakerNote::printAFPointsUsed(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintAFTracking_NormalOperation_273) {

    SonyMakerNote::printAFTracking(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintFocalPlaneAFPointsUsed_NormalOperation_273) {

    SonyMakerNote::printFocalPlaneAFPointsUsed(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintWBShiftABGMPrecise_NormalOperation_273) {

    SonyMakerNote::printWBShiftABGMPrecise(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintExposureStandardAdjustment_NormalOperation_273) {

    SonyMakerNote::printExposureStandardAdjustment(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintPixelShiftInfo_NormalOperation_273) {

    SonyMakerNote::printPixelShiftInfo(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintFocusFrameSize_NormalOperation_273) {

    SonyMakerNote::printFocusFrameSize(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintColorTemperature_NormalOperation_273) {

    SonyMakerNote::printColorTemperature(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintColorCompensationFilter_NormalOperation_273) {

    SonyMakerNote::printColorCompensationFilter(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintLensSpec_NormalOperation_273) {

    SonyMakerNote::printLensSpec(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintImageSize_NormalOperation_273) {

    SonyMakerNote::printImageSize(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintFocusMode_NormalOperation_273) {

    SonyMakerNote::printFocusMode(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintAFMode_NormalOperation_273) {

    SonyMakerNote::printAFMode(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintFocusMode3_NormalOperation_273) {

    SonyMakerNote::printFocusMode3(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintHighISONoiseReduction2_NormalOperation_273) {

    SonyMakerNote::printHighISONoiseReduction2(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSony2FpAmbientTemperature_NormalOperation_273) {

    SonyMakerNote::printSony2FpAmbientTemperature(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSony2FpFocusMode_NormalOperation_273) {

    SonyMakerNote::printSony2FpFocusMode(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSony2FpFocusPosition2_NormalOperation_273) {

    SonyMakerNote::printSony2FpFocusPosition2(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc1CameraTemperature_NormalOperation_273) {

    SonyMakerNote::printSonyMisc1CameraTemperature(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc2bLensZoomPosition_NormalOperation_273) {

    SonyMakerNote::printSonyMisc2bLensZoomPosition(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc2bFocusPosition2_NormalOperation_273) {

    SonyMakerNote::printSonyMisc2bFocusPosition2(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cShotNumberSincePowerUp_NormalOperation_273) {

    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cSequenceNumber_NormalOperation_273) {

    SonyMakerNote::printSonyMisc3cSequenceNumber(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cQuality2_NormalOperation_273) {

    SonyMakerNote::printSonyMisc3cQuality2(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cSonyImageHeight_NormalOperation_273) {

    SonyMakerNote::printSonyMisc3cSonyImageHeight(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, PrintSonyMisc3cModelReleaseYear_NormalOperation_273) {

    SonyMakerNote::printSonyMisc3cModelReleaseYear(oss, dummyValue, dummyMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_273, TagListSonyMisc3c_ReturnsNonNull_273) {

    const auto* tagList = SonyMakerNote::tagListSonyMisc3c();

    EXPECT_NE(tagList, nullptr);

}
