#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "minoltamn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class MinoltaMakerNoteTest_998 : public ::testing::Test {

protected:

    std::ostringstream os;

    MockValue mockValue; // Assuming Value can be mocked or we have a mock class

    const ExifData* mockExifData = nullptr;

};



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaExposureSpeedStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaExposureTimeStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaExposureTimeStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaFNumberStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaFNumberStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaExposureCompensationStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaExposureCompensationStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaFocalLengthStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaFocalLengthStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaDateStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaDateStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaTimeStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaTimeStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaFlashExposureCompStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaWhiteBalanceStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaBrightnessStd_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaBrightnessStd(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaExposureManualBias5D_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaExposureManualBias5D(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, PrintMinoltaExposureCompensation5D_NormalOperation_998) {

    MinoltaMakerNote::printMinoltaExposureCompensation5D(os, mockValue, mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(MinoltaMakerNoteTest_998, TagListCs5DBoundaryCondition_998) {

    auto tagList = MinoltaMakerNote::tagListCs5D();

    EXPECT_NE(tagList, nullptr);

}
