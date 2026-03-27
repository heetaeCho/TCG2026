#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class TimeValueTest_2174 : public ::testing::Test {

protected:

    TimeValue timeValue;

    

    TimeValueTest_2174() 

        : timeValue(12, 30, 45, -5, 30) {}

};



TEST_F(TimeValueTest_2174, InitializationWithValidTime_2174) {

    EXPECT_EQ(timeValue.getTime().hour, 12);

    EXPECT_EQ(timeValue.getTime().minute, 30);

    EXPECT_EQ(timeValue.getTime().second, 45);

    EXPECT_EQ(timeValue.getTime().tzHour, -5);

    EXPECT_EQ(timeValue.getTime().tzMinute, 30);

}



TEST_F(TimeValueTest_2174, InitializationWithZeroTime_2174) {

    TimeValue zeroTime(0, 0, 0, 0, 0);

    EXPECT_EQ(zeroTime.getTime().hour, 0);

    EXPECT_EQ(zeroTime.getTime().minute, 0);

    EXPECT_EQ(zeroTime.getTime().second, 0);

    EXPECT_EQ(zeroTime.getTime().tzHour, 0);

    EXPECT_EQ(zeroTime.getTime().tzMinute, 0);

}



TEST_F(TimeValueTest_2174, InitializationWithMaxTime_2174) {

    TimeValue maxTime(23, 59, 59, 14, 59);

    EXPECT_EQ(maxTime.getTime().hour, 23);

    EXPECT_EQ(maxTime.getTime().minute, 59);

    EXPECT_EQ(maxTime.getTime().second, 59);

    EXPECT_EQ(maxTime.getTime().tzHour, 14);

    EXPECT_EQ(maxTime.getTime().tzMinute, 59);

}



TEST_F(TimeValueTest_2174, InitializationWithMinTime_2174) {

    TimeValue minTime(-12, -30, -15, -14, -59);

    EXPECT_EQ(minTime.getTime().hour, -12);

    EXPECT_EQ(minTime.getTime().minute, -30);

    EXPECT_EQ(minTime.getTime().second, -15);

    EXPECT_EQ(minTime.getTime().tzHour, -14);

    EXPECT_EQ(minTime.getTime().tzMinute, -59);

}



TEST_F(TimeValueTest_2174, CountReturnsOne_2174) {

    EXPECT_EQ(timeValue.count(), 1);

}



TEST_F(TimeValueTest_2174, SizeReturnsExpectedSize_2174) {

    // Assuming size is calculated based on the Time struct size

    EXPECT_EQ(timeValue.size(), sizeof(Time));

}



TEST_F(TimeValueTest_2174, OkMethodReturnsTrue_2174) {

    EXPECT_TRUE(timeValue.ok());

}
