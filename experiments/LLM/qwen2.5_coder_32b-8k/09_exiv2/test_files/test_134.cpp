#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Return;



class DateValueTest_134 : public ::testing::Test {

protected:

    void SetUp() override {

        dateValue = std::make_unique<DateValue>();

    }



    std::unique_ptr<DateValue> dateValue;

};



TEST_F(DateValueTest_134, DefaultConstructorInitializesDate_134) {

    // Assuming default constructor initializes date to some valid state

    const Date& date = dateValue->getDate();

    EXPECT_TRUE(date.year() != 0 && date.month() != 0 && date.day() != 0);

}



TEST_F(DateValueTest_134, ParameterizedConstructorSetsDate_134) {

    int year = 2023;

    int month = 10;

    int day = 5;



    DateValue customDate(year, month, day);

    const Date& date = customDate.getDate();

    EXPECT_EQ(date.year(), year);

    EXPECT_EQ(date.month(), month);

    EXPECT_EQ(date.day(), day);

}



TEST_F(DateValueTest_134, SetDateChangesDate_134) {

    Date newDate(2023, 9, 15);

    dateValue->setDate(newDate);

    const Date& date = dateValue->getDate();

    EXPECT_EQ(date.year(), newDate.year());

    EXPECT_EQ(date.month(), newDate.month());

    EXPECT_EQ(date.day(), newDate.day());

}



TEST_F(DateValueTest_134, CountReturnsOne_134) {

    EXPECT_EQ(dateValue->count(), 1);

}



TEST_F(DateValueTest_134, SizeReturnsValidSize_134) {

    // Assuming size returns a valid non-zero value

    EXPECT_GT(dateValue->size(), 0);

}



TEST_F(DateValueTest_134, CloneCreatesCopy_134) {

    auto clone = dateValue->clone();

    EXPECT_NE(clone.get(), dateValue.get());

    EXPECT_EQ(clone->getDate().year(), dateValue->getDate().year());

    EXPECT_EQ(clone->getDate().month(), dateValue->getDate().month());

    EXPECT_EQ(clone->getDate().day(), dateValue->getDate().day());

}



TEST_F(DateValueTest_134, ReadFromStringSetsDate_134) {

    std::string dateString = "2023:10:05 12:34:56";

    int result = dateValue->read(dateString);

    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

    const Date& date = dateValue->getDate();

    EXPECT_EQ(date.year(), 2023);

    EXPECT_EQ(date.month(), 10);

    EXPECT_EQ(date.day(), 5);

}



TEST_F(DateValueTest_134, WriteToStreamOutputsDate_134) {

    std::ostringstream oss;

    dateValue->write(oss);

    // Assuming the output format is "YYYY:MM:DD"

    EXPECT_FALSE(oss.str().empty());

    EXPECT_EQ(oss.str().size(), 10); // Format "YYYY:MM:DD" should be 10 characters

}



TEST_F(DateValueTest_134, ToInt64ReturnsValidInteger_134) {

    int64_t result = dateValue->toInt64(0);

    EXPECT_TRUE(result != 0); // Assuming toInt64 returns a non-zero value for valid Date

}



TEST_F(DateValueTest_134, ToUint32ReturnsValidUnsignedInteger_134) {

    uint32_t result = dateValue->toUint32(0);

    EXPECT_TRUE(result != 0); // Assuming toUint32 returns a non-zero value for valid Date

}



TEST_F(DateValueTest_134, ToFloatReturnsValidFloat_134) {

    float result = dateValue->toFloat(0);

    EXPECT_TRUE(result != 0.0f); // Assuming toFloat returns a non-zero value for valid Date

}



TEST_F(DateValueTest_134, ToRationalReturnsValidRational_134) {

    Rational result = dateValue->toRational(0);

    EXPECT_TRUE(result.first != 0 || result.second != 0); // Assuming toRational returns a non-zero rational for valid Date

}
