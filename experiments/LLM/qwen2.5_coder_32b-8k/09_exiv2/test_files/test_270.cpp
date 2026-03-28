#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "sonymn_int.hpp"



namespace Exiv2 {

    namespace Internal {

        class MockValue : public Value {

        public:

            MOCK_CONST_METHOD0(typeName, std::string());

            MOCK_CONST_METHOD0(size, size_t());

            MOCK_METHOD1(read, void(const byte*));

            MOCK_METHOD1(write, void(byte*) const);

            MOCK_METHOD0(count, size_t()) const;

            MOCK_METHOD2(toLong, long(size_t, ByteOrder) const);

            MOCK_METHOD2(toFloat, float(size_t, ByteOrder) const);

            MOCK_METHOD2(toString, std::string(size_t, ByteOrder) const);

        };



        class MockExifData : public ExifData {

        public:

            MOCK_CONST_METHOD1(findKey, const Exifdatum*(const ExifKey&) const);

            MOCK_METHOD1(add, void(const Exifdatum&));

            MOCK_METHOD0(count, size_t() const);

        };

    }

}



using namespace Exiv2::Internal;

using ::testing::_;



class SonyMakerNoteTest_270 : public ::testing::Test {

protected:

    MockValue mockValue;

    MockExifData mockMetadata;

};



TEST_F(SonyMakerNoteTest_270, PrintWhiteBalanceFineTune_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Normal"));

    SonyMakerNote::printWhiteBalanceFineTune(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Normal");

}



TEST_F(SonyMakerNoteTest_270, PrintMultiBurstMode_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("On"));

    SonyMakerNote::printMultiBurstMode(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "On");

}



TEST_F(SonyMakerNoteTest_270, PrintMultiBurstSize_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("3"));

    SonyMakerNote::printMultiBurstSize(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "3");

}



TEST_F(SonyMakerNoteTest_270, PrintAutoHDRStd_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Off"));

    SonyMakerNote::printAutoHDRStd(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Off");

}



TEST_F(SonyMakerNoteTest_270, PrintWBShiftABGM_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("0"));

    SonyMakerNote::printWBShiftABGM(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "0");

}



TEST_F(SonyMakerNoteTest_270, PrintFocusMode2_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Continuous"));

    SonyMakerNote::printFocusMode2(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Continuous");

}



TEST_F(SonyMakerNoteTest_270, PrintAFAreaModeSetting_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Wide"));

    SonyMakerNote::printAFAreaModeSetting(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Wide");

}



TEST_F(SonyMakerNoteTest_270, PrintFlexibleSpotPosition_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Center"));

    SonyMakerNote::printFlexibleSpotPosition(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_270, PrintAFPointSelected_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("1"));

    SonyMakerNote::printAFPointSelected(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "1");

}



TEST_F(SonyMakerNoteTest_270, PrintAFPointsUsed_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("3"));

    SonyMakerNote::printAFPointsUsed(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "3");

}



TEST_F(SonyMakerNoteTest_270, PrintAFTracking_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("On"));

    SonyMakerNote::printAFTracking(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "On");

}



TEST_F(SonyMakerNoteTest_270, PrintFocalPlaneAFPointsUsed_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("9"));

    SonyMakerNote::printFocalPlaneAFPointsUsed(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "9");

}



TEST_F(SonyMakerNoteTest_270, PrintWBShiftABGMPrecise_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("0.5"));

    SonyMakerNote::printWBShiftABGMPrecise(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "0.5");

}



TEST_F(SonyMakerNoteTest_270, PrintExposureStandardAdjustment_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("1.0"));

    SonyMakerNote::printExposureStandardAdjustment(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "1.0");

}



TEST_F(SonyMakerNoteTest_270, PrintPixelShiftInfo_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Off"));

    SonyMakerNote::printPixelShiftInfo(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Off");

}



TEST_F(SonyMakerNoteTest_270, PrintFocusFrameSize_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("1.5"));

    SonyMakerNote::printFocusFrameSize(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "1.5");

}



TEST_F(SonyMakerNoteTest_270, PrintColorTemperature_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("6500"));

    SonyMakerNote::printColorTemperature(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "6500");

}



TEST_F(SonyMakerNoteTest_270, PrintColorCompensationFilter_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("0"));

    SonyMakerNote::printColorCompensationFilter(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "0");

}



TEST_F(SonyMakerNoteTest_270, PrintLensSpec_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("E 35mm f/1.8 OSS"));

    SonyMakerNote::printLensSpec(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "E 35mm f/1.8 OSS");

}



TEST_F(SonyMakerNoteTest_270, PrintFocusMode_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Manual"));

    SonyMakerNote::printFocusMode(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Manual");

}



TEST_F(SonyMakerNoteTest_270, PrintAFMode_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Phase Detect"));

    SonyMakerNote::printAFMode(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Phase Detect");

}



TEST_F(SonyMakerNoteTest_270, PrintFocusMode3_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Continuous"));

    SonyMakerNote::printFocusMode3(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Continuous");

}



TEST_F(SonyMakerNoteTest_270, PrintHighISONoiseReduction2_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Off"));

    SonyMakerNote::printHighISONoiseReduction2(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Off");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc1CameraTemperature_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("30"));

    SonyMakerNote::printSonyMisc1CameraTemperature(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "30");

}



TEST_F(SonyMakerNoteTest_270, PrintSony2FpAmbientTemperature_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("15"));

    SonyMakerNote::printSony2FpAmbientTemperature(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "15");

}



TEST_F(SonyMakerNoteTest_270, PrintSony2FpFocusMode_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Manual"));

    SonyMakerNote::printSony2FpFocusMode(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Manual");

}



TEST_F(SonyMakerNoteTest_270, PrintSony2FpFocusPosition2_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("1"));

    SonyMakerNote::printSony2FpFocusPosition2(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "1");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc2bLensZoomPosition_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("5.0"));

    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "5.0");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc2bFocusPosition2_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("2"));

    SonyMakerNote::printSonyMisc2bFocusPosition2(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "2");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cShotNumberSincePowerUp_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("100"));

    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "100");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cSequenceNumber_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("5"));

    SonyMakerNote::printSonyMisc3cSequenceNumber(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "5");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cQuality2_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("Fine"));

    SonyMakerNote::printSonyMisc3cQuality2(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Fine");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cSonyImageHeight_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("480"));

    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "480");

}



TEST_F(SonyMakerNoteTest_270, PrintSonyMisc3cModelReleaseYear_NormalOperation_270) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString(0, _)).WillOnce(::testing::Return("2021"));

    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "2021");

}
