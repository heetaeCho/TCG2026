#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class TimeValueTest : public ::testing::Test {

protected:

    TimeValue timeValue;

};



TEST_F(TimeValueTest_2173, DefaultConstructorInitializesTime_2173) {

    EXPECT_EQ(timeValue.getTime().hour, 0);

    EXPECT_EQ(timeValue.getTime().minute, 0);

    EXPECT_EQ(timeValue.getTime().second, 0);

    EXPECT_EQ(timeValue.getTime().tzHour, 0);

    EXPECT_EQ(timeValue.getTime().tzMinute, 0);

}



TEST_F(TimeValueTest_2173, CountReturnsOne_2173) {

    EXPECT_EQ(timeValue.count(), 1);

}



TEST_F(TimeValueTest_2173, SizeReturnsEight_2173) {

    // Assuming size() returns the total bytes of Time structure

    EXPECT_EQ(timeValue.size(), sizeof(Time));

}



TEST_F(TimeValueTest_2173, OkMethodReturnsTrue_2173) {

    EXPECT_TRUE(timeValue.ok());

}



TEST_F(TimeValueTest_2173, SetTimeUpdatesInternalTime_2173) {

    Time newTime = {10, 30, 45, -5, 30};

    timeValue.setTime(newTime);

    EXPECT_EQ(timeValue.getTime().hour, newTime.hour);

    EXPECT_EQ(timeValue.getTime().minute, newTime.minute);

    EXPECT_EQ(timeValue.getTime().second, newTime.second);

    EXPECT_EQ(timeValue.getTime().tzHour, newTime.tzHour);

    EXPECT_EQ(timeValue.getTime().tzMinute, newTime.tzMinute);

}



TEST_F(TimeValueTest_2173, ToInt64ReturnsCorrectValue_2173) {

    Time newTime = {10, 30, 45, -5, 30};

    timeValue.setTime(newTime);

    int64_t expected = (newTime.hour * 3600 + newTime.minute * 60 + newTime.second) -

                       ((newTime.tzHour * 3600 + newTime.tzMinute * 60));

    EXPECT_EQ(timeValue.toInt64(0), expected);

}



TEST_F(TimeValueTest_2173, ToUint32ReturnsCorrectValue_2173) {

    Time newTime = {10, 30, 45, -5, 30};

    timeValue.setTime(newTime);

    uint32_t expected = static_cast<uint32_t>((newTime.hour * 3600 + newTime.minute * 60 + newTime.second) -

                                             ((newTime.tzHour * 3600 + newTime.tzMinute * 60)));

    EXPECT_EQ(timeValue.toUint32(0), expected);

}



TEST_F(TimeValueTest_2173, ToFloatReturnsCorrectValue_2173) {

    Time newTime = {10, 30, 45, -5, 30};

    timeValue.setTime(newTime);

    float expected = static_cast<float>((newTime.hour * 3600 + newTime.minute * 60 + newTime.second) -

                                       ((newTime.tzHour * 3600 + newTime.tzMinute * 60)));

    EXPECT_FLOAT_EQ(timeValue.toFloat(0), expected);

}



TEST_F(TimeValueTest_2173, ToRationalReturnsCorrectValue_2173) {

    Time newTime = {10, 30, 45, -5, 30};

    timeValue.setTime(newTime);

    int64_t numerator = (newTime.hour * 3600 + newTime.minute * 60 + newTime.second) -

                        ((newTime.tzHour * 3600 + newTime.tzMinute * 60));

    Rational expected(numerator, 1);

    EXPECT_EQ(timeValue.toRational(0), expected);

}



TEST_F(TimeValueTest_2173, ToStringReturnsCorrectFormat_2173) {

    Time newTime = {10, 30, 45, -5, 30};

    timeValue.setTime(newTime);

    std::string expected = "10:30:45-05:30";

    EXPECT_EQ(timeValue.toString(), expected);

}



TEST_F(TimeValueTest_2173, CopyMethodReturnsCorrectSize_2173) {

    byte buffer[8];

    ByteOrder byteOrder = littleEndian;

    size_t copiedSize = timeValue.copy(buffer, byteOrder);

    EXPECT_EQ(copiedSize, sizeof(Time));

}
