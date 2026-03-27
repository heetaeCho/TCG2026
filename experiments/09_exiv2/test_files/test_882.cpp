#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/value.cpp"



namespace Exiv2 {

    class TimeValueTest_882 : public ::testing::Test {

    protected:

        TimeValue timeValue;



        void SetUp() override {

            // Initialize any necessary preconditions for each test

        }

    };

}



using namespace Exiv2;



TEST_F(TimeValueTest_882, ToInt64_NoonUTC_882) {

    TimeValue::TimeStruct time = {12, 0, 0, 0, 0}; // Noon UTC

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 43200); // 12 hours * 3600 seconds/hour

}



TEST_F(TimeValueTest_882, ToInt64_MidnightUTC_882) {

    TimeValue::TimeStruct time = {0, 0, 0, 0, 0}; // Midnight UTC

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 0); // No offset from midnight

}



TEST_F(TimeValueTest_882, ToInt64_NoonUTCMinus5_882) {

    TimeValue::TimeStruct time = {17, 0, 0, 5, 0}; // Noon UTC-5

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 43200); // Converted to UTC should be noon as well

}



TEST_F(TimeValueTest_882, ToInt64_NoonUTCPlus1_882) {

    TimeValue::TimeStruct time = {11, 0, 0, -1, 0}; // Noon UTC+1

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 43200); // Converted to UTC should be noon as well

}



TEST_F(TimeValueTest_882, ToInt64_EndOfDayUTCMinus1_882) {

    TimeValue::TimeStruct time = {23, 59, 59, 1, 0}; // End of day in UTC-1

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 86399); // Last second of the day in UTC

}



TEST_F(TimeValueTest_882, ToInt64_BeginningOfDayUTCPlus1_882) {

    TimeValue::TimeStruct time = {0, 0, 1, -1, 0}; // First second of the day in UTC+1

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 1); // First second of the day in UTC

}



TEST_F(TimeValueTest_882, ToInt64_NegativeTime_882) {

    TimeValue::TimeStruct time = {23, 59, 59, 0, 0}; // Midnight - 1 second

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 86399); // Should wrap around to the last second of the day

}



TEST_F(TimeValueTest_882, ToInt64_ZeroTime_882) {

    TimeValue::TimeStruct time = {0, 0, 0, 0, 0}; // Midnight UTC with no offset

    timeValue.time_ = time;

    EXPECT_EQ(timeValue.toInt64(0), 0); // Should return zero seconds from midnight

}
