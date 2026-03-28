#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/minoltamn_int.hpp"



namespace {



using namespace Exiv2::Internal;

using ::testing::_;



class MinoltaMakerNoteTest : public ::testing::Test {

protected:

    Value dummyValue;

    ExifData dummyExifData;

};



TEST_F(MinoltaMakerNoteTest, tagListCsA100_ReturnsNonNull_999) {

    const TagInfo* result = MinoltaMakerNote::tagListCsA100();

    EXPECT_NE(result, nullptr);

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureSpeedStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaExposureSpeedStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureTimeStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaExposureTimeStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaFNumberStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaFNumberStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureCompensationStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaExposureCompensationStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaFocalLengthStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaFocalLengthStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaDateStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaDateStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaTimeStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaTimeStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaFlashExposureCompStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaWhiteBalanceStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaBrightnessStd_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaBrightnessStd(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureManualBias5D_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaExposureManualBias5D(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



TEST_F(MinoltaMakerNoteTest, printMinoltaExposureCompensation5D_NormalOperation_999) {

    std::ostringstream os;

    auto& result = MinoltaMakerNote::printMinoltaExposureCompensation5D(os, dummyValue, &dummyExifData);

    EXPECT_EQ(&result, &os);  // Verify that the function returns the same stream

}



}  // namespace
