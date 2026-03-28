#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/panasonicmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class PanasonicMakerNoteTest_705 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockExifData;

};



TEST_F(PanasonicMakerNoteTest_705, print0x000f_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::print0x000f(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, print0x0023_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::print0x0023(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, print0x0029_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::print0x0029(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, print0x0033_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::print0x0033(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, print0x0036_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::print0x0036(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, print0x003c_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::print0x003c(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, printPressure_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::printPressure(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, printPanasonicText_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::printPanasonicText(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, printAccelerometer_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::printAccelerometer(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, printRollAngle_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::printRollAngle(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(PanasonicMakerNoteTest_705, printPitchAngle_NormalOperation_705) {

    std::ostringstream oss;

    PanasonicMakerNote::printPitchAngle(oss, mockValue, &mockExifData);

    EXPECT_FALSE(oss.str().empty());

}
