#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/minoltamn_int.hpp>



using namespace Exiv2::Internal;

using ::testing::_;



class MinoltaMakerNoteTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value valueMock;

    ExifData exifDataMock;

};



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureSpeedStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaExposureSpeedStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureTimeStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaExposureTimeStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaFNumberStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaFNumberStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureCompensationStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaExposureCompensationStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaFocalLengthStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaFocalLengthStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaDateStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaDateStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaTimeStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaTimeStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaFlashExposureCompStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaFlashExposureCompStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaWhiteBalanceStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaWhiteBalanceStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaBrightnessStd_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaBrightnessStd(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureManualBias5D_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaExposureManualBias5D(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureCompensation5D_NormalOperation_995) {

    MinoltaMakerNote::printMinoltaExposureCompensation5D(oss, valueMock, &exifDataMock);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(MinoltaMakerNoteTest, tagList_ReturnsConstantExpression_995) {

    const auto& tags = MinoltaMakerNote::tagList();

    EXPECT_TRUE(tags != nullptr);

}



TEST_F(MinoltaMakerNoteTest, tagListCsStd_ReturnsConstantExpression_995) {

    const auto& tags = MinoltaMakerNote::tagListCsStd();

    EXPECT_TRUE(tags != nullptr);

}



TEST_F(MinoltaMakerNoteTest, tagListCs7D_ReturnsConstantExpression_995) {

    const auto& tags = MinoltaMakerNote::tagListCs7D();

    EXPECT_TRUE(tags != nullptr);

}



TEST_F(MinoltaMakerNoteTest, tagListCs5D_ReturnsConstantExpression_995) {

    const auto& tags = MinoltaMakerNote::tagListCs5D();

    EXPECT_TRUE(tags != nullptr);

}



TEST_F(MinoltaMakerNoteTest, tagListCsA100_ReturnsConstantExpression_995) {

    const auto& tags = MinoltaMakerNote::tagListCsA100();

    EXPECT_TRUE(tags != nullptr);

}
