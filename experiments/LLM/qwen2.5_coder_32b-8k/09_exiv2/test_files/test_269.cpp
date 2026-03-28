#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/sonymn_int.hpp"

#include <sstream>



namespace Exiv2 {

    class Value {};

    class ExifData {};

}



using namespace Exiv2::Internal;



class SonyMakerNoteTest_269 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Exiv2::Value value;

    const Exiv2::ExifData* metadata = nullptr;

};



TEST_F(SonyMakerNoteTest_269, TagListCs2_ReturnsConstexprArray_269) {

    auto tags = SonyMakerNote::tagListCs2();

    EXPECT_TRUE(tags != nullptr);

}



TEST_F(SonyMakerNoteTest_269, PrintWhiteBalanceFineTune_NormalOperation_269) {

    SonyMakerNote::printWhiteBalanceFineTune(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintMultiBurstMode_MetadataNull_269) {

    SonyMakerNote::printMultiBurstMode(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintMultiBurstSize_NormalOperation_269) {

    SonyMakerNote::printMultiBurstSize(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintAutoHDRStd_MetadataNull_269) {

    SonyMakerNote::printAutoHDRStd(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintWBShiftABGM_NormalOperation_269) {

    SonyMakerNote::printWBShiftABGM(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintFocusMode2_MetadataNull_269) {

    SonyMakerNote::printFocusMode2(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintAFAreaModeSetting_MetadataNull_269) {

    SonyMakerNote::printAFAreaModeSetting(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintFlexibleSpotPosition_MetadataNull_269) {

    SonyMakerNote::printFlexibleSpotPosition(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintAFPointSelected_MetadataNull_269) {

    SonyMakerNote::printAFPointSelected(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintAFPointsUsed_NormalOperation_269) {

    SonyMakerNote::printAFPointsUsed(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintAFTracking_MetadataNull_269) {

    SonyMakerNote::printAFTracking(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintFocalPlaneAFPointsUsed_NormalOperation_269) {

    SonyMakerNote::printFocalPlaneAFPointsUsed(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintWBShiftABGMPrecise_NormalOperation_269) {

    SonyMakerNote::printWBShiftABGMPrecise(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintExposureStandardAdjustment_MetadataNull_269) {

    SonyMakerNote::printExposureStandardAdjustment(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintPixelShiftInfo_NormalOperation_269) {

    SonyMakerNote::printPixelShiftInfo(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintFocusFrameSize_MetadataNull_269) {

    SonyMakerNote::printFocusFrameSize(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintColorTemperature_NormalOperation_269) {

    SonyMakerNote::printColorTemperature(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintColorCompensationFilter_MetadataNull_269) {

    SonyMakerNote::printColorCompensationFilter(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintLensSpec_NormalOperation_269) {

    SonyMakerNote::printLensSpec(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintFocusMode_MetadataNull_269) {

    SonyMakerNote::printFocusMode(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintImageSize_NormalOperation_269) {

    SonyMakerNote::printImageSize(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintAFMode_MetadataNull_269) {

    SonyMakerNote::printAFMode(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintFocusMode3_NormalOperation_269) {

    SonyMakerNote::printFocusMode3(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintHighISONoiseReduction2_MetadataNull_269) {

    SonyMakerNote::printHighISONoiseReduction2(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSony2FpAmbientTemperature_NormalOperation_269) {

    SonyMakerNote::printSony2FpAmbientTemperature(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSony2FpFocusMode_MetadataNull_269) {

    SonyMakerNote::printSony2FpFocusMode(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSony2FpFocusPosition2_NormalOperation_269) {

    SonyMakerNote::printSony2FpFocusPosition2(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc1CameraTemperature_MetadataNull_269) {

    SonyMakerNote::printSonyMisc1CameraTemperature(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc2bLensZoomPosition_NormalOperation_269) {

    SonyMakerNote::printSonyMisc2bLensZoomPosition(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc2bFocusPosition2_MetadataNull_269) {

    SonyMakerNote::printSonyMisc2bFocusPosition2(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cShotNumberSincePowerUp_NormalOperation_269) {

    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cSequenceNumber_MetadataNull_269) {

    SonyMakerNote::printSonyMisc3cSequenceNumber(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cQuality2_NormalOperation_269) {

    SonyMakerNote::printSonyMisc3cQuality2(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cSonyImageHeight_MetadataNull_269) {

    SonyMakerNote::printSonyMisc3cSonyImageHeight(oss, value, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(SonyMakerNoteTest_269, PrintSonyMisc3cModelReleaseYear_NormalOperation_269) {

    SonyMakerNote::printSonyMisc3cModelReleaseYear(oss, value, metadata);

    EXPECT_FALSE(oss.str().empty());

}
