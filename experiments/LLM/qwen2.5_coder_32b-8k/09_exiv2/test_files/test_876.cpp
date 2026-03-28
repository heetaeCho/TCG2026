#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class TimeValueTest_876 : public ::testing::Test {

protected:

    void SetUp() override {

        timeValue = std::make_unique<TimeValue>();

        testTime = {12, 30, 45, -5, 30}; // Example time: 12:30:45 with timezone -5:30

    }



    std::unique_ptr<TimeValue> timeValue;

    Time testTime;

};



TEST_F(TimeValueTest_876, SetTimeAndGetTime_NormalOperation_876) {

    timeValue->setTime(testTime);

    const Time& retrievedTime = timeValue->getTime();

    EXPECT_EQ(retrievedTime.hour, testTime.hour);

    EXPECT_EQ(retrievedTime.minute, testTime.minute);

    EXPECT_EQ(retrievedTime.second, testTime.second);

    EXPECT_EQ(retrievedTime.tzHour, testTime.tzHour);

    EXPECT_EQ(retrievedTime.tzMinute, testTime.tzMinute);

}



TEST_F(TimeValueTest_876, Count_ReturnsOne_876) {

    EXPECT_EQ(timeValue->count(), 1);

}



TEST_F(TimeValueTest_876, Size_ReturnsCorrectSize_876) {

    // Assuming size() returns the size in bytes of the Time structure

    EXPECT_EQ(timeValue->size(), sizeof(Time));

}



TEST_F(TimeValueTest_876, SetTimeAndGetTime_BoundaryConditions_876) {

    Time boundaryTime = {0, 0, 0, -12, 0}; // Midnight with timezone -12:00

    timeValue->setTime(boundaryTime);

    const Time& retrievedTime = timeValue->getTime();

    EXPECT_EQ(retrievedTime.hour, boundaryTime.hour);

    EXPECT_EQ(retrievedTime.minute, boundaryTime.minute);

    EXPECT_EQ(retrievedTime.second, boundaryTime.second);

    EXPECT_EQ(retrievedTime.tzHour, boundaryTime.tzHour);

    EXPECT_EQ(retrievedTime.tzMinute, boundaryTime.tzMinute);



    Time maxBoundaryTime = {23, 59, 59, 14, 0}; // Last second of the day with timezone +14:00

    timeValue->setTime(maxBoundaryTime);

    const Time& retrievedMaxTime = timeValue->getTime();

    EXPECT_EQ(retrievedMaxTime.hour, maxBoundaryTime.hour);

    EXPECT_EQ(retrievedMaxTime.minute, maxBoundaryTime.minute);

    EXPECT_EQ(retrievedMaxTime.second, maxBoundaryTime.second);

    EXPECT_EQ(retrievedMaxTime.tzHour, maxBoundaryTime.tzHour);

    EXPECT_EQ(retrievedMaxTime.tzMinute, maxBoundaryTime.tzMinute);

}



TEST_F(TimeValueTest_876, SetTimeAndGetTime_ExceptionalCases_876) {

    // No exceptional cases are observable through the interface based on provided information

}
