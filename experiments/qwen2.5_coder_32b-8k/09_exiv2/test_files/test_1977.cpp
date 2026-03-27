#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPUtils.cpp"  // Include the file with the partial implementation



// Since the provided code snippet does not contain any class definition or public functions,

// we will assume a simple testing structure for demonstration purposes.

// Let's assume there is a function IsLeapYear that needs to be tested.



class LeapYearTest_1977 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple test

};



TEST_F(LeapYearTest_1977, NonMultipleOf4IsNotLeapYear_1977) {

    EXPECT_FALSE(IsLeapYear(2019));

}



TEST_F(LeapYearTest_1977, MultipleOf4ButNotMultipleOf100IsLeapYear_1977) {

    EXPECT_TRUE(IsLeapYear(2020));

}



TEST_F(LeapYearTest_1977, MultipleOf100ButNotMultipleOf400IsNotLeapYear_1977) {

    EXPECT_FALSE(IsLeapYear(1900));

}



TEST_F(LeapYearTest_1977, MultipleOf400IsLeapYear_1977) {

    EXPECT_TRUE(IsLeapYear(2000));

}



// Edge cases

TEST_F(LeapYearTest_1977, YearZeroIsNotLeapYear_1977) {

    EXPECT_FALSE(IsLeapYear(0));  // Year 0 is not considered a leap year in the Gregorian calendar

}



TEST_F(LeapYearTest_1977, NegativeYearHandling_1977) {

    EXPECT_FALSE(IsLeapYear(-4)); // Assuming negative years follow the same rules as positive

}
