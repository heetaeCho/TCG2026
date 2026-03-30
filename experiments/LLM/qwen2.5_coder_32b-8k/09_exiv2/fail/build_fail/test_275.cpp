#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2::Internal;



class SonyMakerNoteTest_275 : public ::testing::Test {

protected:

    Value dummyValue;

    const ExifData* dummyMetadata = nullptr;

};



TEST_F(SonyMakerNoteTest_275, TagList2010e_ReturnsExpectedPointer_275) {

    auto result = SonyMakerNote::tagList2010e();

    EXPECT_NE(result, nullptr);

}



TEST_F(SonyMakerNoteTest_275, PrintWhiteBalanceFineTune_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printWhiteBalanceFineTune(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintMultiBurstMode_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printMultiBurstMode(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintMultiBurstSize_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printMultiBurstSize(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintAutoHDRStd_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printAutoHDRStd(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintWBShiftABGM_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printWBShiftABGM(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintFocusMode2_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printFocusMode2(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintAFAreaModeSetting_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printAFAreaModeSetting(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintFlexibleSpotPosition_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printFlexibleSpotPosition(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintAFPointSelected_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printAFPointSelected(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintAFPointsUsed_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printAFPointsUsed(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintAFTracking_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printAFTracking(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintFocalPlaneAFPointsUsed_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printFocalPlaneAFPointsUsed(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintWBShiftABGMPrecise_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printWBShiftABGMPrecise(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintExposureStandardAdjustment_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printExposureStandardAdjustment(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintPixelShiftInfo_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printPixelShiftInfo(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintFocusFrameSize_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printFocusFrameSize(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintColorTemperature_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printColorTemperature(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintColorCompensationFilter_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printColorCompensationFilter(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintLensSpec_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printLensSpec(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintFocusMode_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printFocusMode(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintAFMode_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printAFMode(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintFocusMode3_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printFocusMode3(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintHighISONoiseReduction2_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printHighISONoiseReduction2(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSony2FpAmbientTemperature_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSony2FpAmbientTemperature(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSony2FpFocusMode_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSony2FpFocusMode(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSony2FpFocusPosition2_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSony2FpFocusPosition2(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc1CameraTemperature_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc1CameraTemperature(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc2bLensZoomPosition_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc2bLensZoomPosition(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc2bFocusPosition2_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc2bFocusPosition2(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cShotNumberSincePowerUp_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cSequenceNumber_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc3cSequenceNumber(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cQuality2_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc3cQuality2(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cSonyImageHeight_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc3cSonyImageHeight(os, dummyValue, dummyMetadata));

}



TEST_F(SonyMakerNoteTest_275, PrintSonyMisc3cModelReleaseYear_DoesNotThrow_275) {

    std::ostringstream os;

    EXPECT_NO_THROW(SonyMakerNote::printSonyMisc3cModelReleaseYear(os, dummyValue, dummyMetadata));

}
