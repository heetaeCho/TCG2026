#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class TimeValueTest : public Test {

protected:

    TimeValue timeValueDefault;

    TimeValue timeValueCustom{12, 30, 45, -6, 0};

};



TEST_F(TimeValueTest_135, DefaultConstructorInitializesTime_135) {

    // Assuming default constructor initializes to some default state

    const Time& time = timeValueDefault.getTime();

    // Check if the default time is initialized as expected (this check needs to be adapted based on actual behavior)

    EXPECT_EQ(time.hour(), 0);

    EXPECT_EQ(time.minute(), 0);

    EXPECT_EQ(time.second(), 0);

    EXPECT_EQ(time.tzHour(), 0);

    EXPECT_EQ(time.tzMinute(), 0);

}



TEST_F(TimeValueTest_135, ParameterizedConstructorInitializesTime_135) {

    const Time& time = timeValueCustom.getTime();

    EXPECT_EQ(time.hour(), 12);

    EXPECT_EQ(time.minute(), 30);

    EXPECT_EQ(time.second(), 45);

    EXPECT_EQ(time.tzHour(), -6);

    EXPECT_EQ(time.tzMinute(), 0);

}



TEST_F(TimeValueTest_135, CloneCreatesNewInstance_135) {

    UniquePtr clonedTime = timeValueCustom.clone();

    const Time& originalTime = timeValueCustom.getTime();

    const Time& clonedTimeValue = clonedTime->getTime();



    EXPECT_EQ(clonedTimeValue.hour(), originalTime.hour());

    EXPECT_EQ(clonedTimeValue.minute(), originalTime.minute());

    EXPECT_EQ(clonedTimeValue.second(), originalTime.second());

    EXPECT_EQ(clonedTimeValue.tzHour(), originalTime.tzHour());

    EXPECT_EQ(clonedTimeValue.tzMinute(), originalTime.tzMinute());



    EXPECT_NE(&clonedTime, &timeValueCustom);

}



TEST_F(TimeValueTest_135, SetTimeUpdatesTimeValue_135) {

    Time newTime{9, 15, 20, -7, 30};

    timeValueDefault.setTime(newTime);



    const Time& updatedTime = timeValueDefault.getTime();

    EXPECT_EQ(updatedTime.hour(), 9);

    EXPECT_EQ(updatedTime.minute(), 15);

    EXPECT_EQ(updatedTime.second(), 20);

    EXPECT_EQ(updatedTime.tzHour(), -7);

    EXPECT_EQ(updatedTime.tzMinute(), 30);

}



TEST_F(TimeValueTest_135, CountReturnsOne_135) {

    // Assuming count() should return 1 as TimeValue holds a single time instance

    EXPECT_EQ(timeValueDefault.count(), 1);

}



TEST_F(TimeValueTest_135, SizeReturnsExpectedSize_135) {

    // This test assumes size returns the correct byte size of the internal time representation.

    // Actual value depends on implementation details but should be consistent.

    EXPECT_EQ(timeValueCustom.size(), sizeof(Time));

}



TEST_F(TimeValueTest_135, ToInt64ThrowsException_135) {

    EXPECT_THROW(timeValueDefault.toInt64(0), Error); // Assuming toInt64 is not supported and throws an error

}



TEST_F(TimeValueTest_135, ToUint32ThrowsException_135) {

    EXPECT_THROW(timeValueCustom.toUint32(0), Error); // Assuming toUint32 is not supported and throws an error

}



TEST_F(TimeValueTest_135, ToFloatThrowsException_135) {

    EXPECT_THROW(timeValueDefault.toFloat(0), Error); // Assuming toFloat is not supported and throws an error

}



TEST_F(TimeValueTest_135, ToRationalThrowsException_135) {

    EXPECT_THROW(timeValueCustom.toRational(0), Error); // Assuming toRational is not supported and throws an error

}
