#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/minoltamn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class MinoltaMakerNoteTest_996 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue; // Assuming Value is some type defined elsewhere

    const ExifData* mockExifData = nullptr; // Assuming ExifData is some type defined elsewhere

};



TEST_F(MinoltaMakerNoteTest_996, TagListCsStd_ReturnsExpectedValue_996) {

    auto result = MinoltaMakerNote::tagListCsStd();

    EXPECT_NE(nullptr, result);

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaExposureSpeedStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaExposureTimeStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaExposureTimeStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaFNumberStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaFNumberStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaExposureCompensationStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaExposureCompensationStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaFocalLengthStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaFocalLengthStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaDateStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaDateStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaTimeStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaTimeStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaFlashExposureCompStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaWhiteBalanceStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaBrightnessStd_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaBrightnessStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaExposureManualBias5D_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaExposureManualBias5D(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_996, PrintMinoltaExposureCompensation5D_NormalOperation_996) {

    os.str("");

    MinoltaMakerNote::printMinoltaExposureCompensation5D(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}
