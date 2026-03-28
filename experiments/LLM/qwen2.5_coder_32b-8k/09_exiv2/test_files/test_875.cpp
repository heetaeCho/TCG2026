#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class TimeValueTest : public ::testing::Test {

protected:

    TimeValue timeValue;

};



TEST_F(TimeValueTest_875, ReadValidTimeNoTz_875) {

    std::string validTime = "12:34:56";

    EXPECT_EQ(timeValue.read(validTime), 0);

}



TEST_F(TimeValueTest_875, ReadValidTimeWithPositiveTz_875) {

    std::string validTime = "12:34:56+03:00";

    EXPECT_EQ(timeValue.read(validTime), 0);

}



TEST_F(TimeValueTest_875, ReadValidTimeWithNegativeTz_875) {

    std::string validTime = "12:34:56-03:00";

    EXPECT_EQ(timeValue.read(validTime), 0);

}



TEST_F(TimeValueTest_875, ReadValidShortTimeNoTz_875) {

    std::string validTime = "1234";

    EXPECT_EQ(timeValue.read(validTime), 0);

}



TEST_F(TimeValueTest_875, ReadInvalidTooShort_875) {

    std::string invalidTime = "12";

    EXPECT_EQ(timeValue.read(invalidTime), 1);

}



TEST_F(TimeValueTest_875, ReadInvalidCharacters_875) {

    std::string invalidTime = "12:34;56";

    EXPECT_EQ(timeValue.read(invalidTime), 1);

}



TEST_F(TimeValueTest_875, ReadInvalidHourTooHigh_875) {

    std::string invalidTime = "25:34:56";

    EXPECT_EQ(timeValue.read(invalidTime), 1);

}



TEST_F(TimeValueTest_875, ReadInvalidMinuteTooHigh_875) {

    std::string invalidTime = "12:60:56";

    EXPECT_EQ(timeValue.read(invalidTime), 1);

}



TEST_F(TimeValueTest_875, ReadInvalidSecondTooHigh_875) {

    std::string invalidTime = "12:34:61";

    EXPECT_EQ(timeValue.read(invalidTime), 1);

}



TEST_F(TimeValueTest_875, ReadInvalidTzHourTooHigh_875) {

    std::string invalidTime = "12:34:56+24:00";

    EXPECT_EQ(timeValue.read(invalidTime), 1);

}



TEST_F(TimeValueTest_875, ReadInvalidTzMinuteTooHigh_875) {

    std::string invalidTime = "12:34:56+03:60";

    EXPECT_EQ(timeValue.read(invalidTime), 1);

}
