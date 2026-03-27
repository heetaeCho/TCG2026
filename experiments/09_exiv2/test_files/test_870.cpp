#include <gtest/gtest.h>

#include "value.cpp"



using namespace Exiv2;



class DateValueTest_870 : public ::testing::Test {

protected:

    DateValue date_value;

};



TEST_F(DateValueTest_870, NormalOperation_870) {

    // Setting a normal date

    date_value.date_.year = 2023;

    date_value.date_.month = 10;

    date_value.date_.day = 5;



    int64_t result = date_value.toInt64(0);

    EXPECT_NE(result, -1); // Expecting a valid timestamp

}



TEST_F(DateValueTest_870, BoundaryCondition_StartOfYear_870) {

    // Setting the start of the year

    date_value.date_.year = 2023;

    date_value.date_.month = 1;

    date_value.date_.day = 1;



    int64_t result = date_value.toInt64(0);

    EXPECT_NE(result, -1); // Expecting a valid timestamp

}



TEST_F(DateValueTest_870, BoundaryCondition_EndOfYear_870) {

    // Setting the end of the year

    date_value.date_.year = 2023;

    date_value.date_.month = 12;

    date_value.date_.day = 31;



    int64_t result = date_value.toInt64(0);

    EXPECT_NE(result, -1); // Expecting a valid timestamp

}



TEST_F(DateValueTest_870, InvalidDate_DayOutOfRange_870) {

    // Setting an invalid day

    date_value.date_.year = 2023;

    date_value.date_.month = 2;

    date_value.date_.day = 30;



    int64_t result = date_value.toInt64(0);

    EXPECT_EQ(result, -1); // Expecting an invalid timestamp

}



TEST_F(DateValueTest_870, InvalidDate_MonthOutOfRange_870) {

    // Setting an invalid month

    date_value.date_.year = 2023;

    date_value.date_.month = 13;

    date_value.date_.day = 1;



    int64_t result = date_value.toInt64(0);

    EXPECT_EQ(result, -1); // Expecting an invalid timestamp

}



TEST_F(DateValueTest_870, LeapYear_February29_870) {

    // Setting a leap year date

    date_value.date_.year = 2024;

    date_value.date_.month = 2;

    date_value.date_.day = 29;



    int64_t result = date_value.toInt64(0);

    EXPECT_NE(result, -1); // Expecting a valid timestamp

}



TEST_F(DateValueTest_870, NonLeapYear_February29_870) {

    // Setting a non-leap year date

    date_value.date_.year = 2023;

    date_value.date_.month = 2;

    date_value.date_.day = 29;



    int64_t result = date_value.toInt64(0);

    EXPECT_EQ(result, -1); // Expecting an invalid timestamp

}
