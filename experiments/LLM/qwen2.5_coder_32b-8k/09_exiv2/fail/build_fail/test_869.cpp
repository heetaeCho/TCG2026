#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;

using testing::Eq;



TEST_F(DateValueTest_869, WriteOutputsCorrectFormat_869) {

    DateValue dateValue(2023, 10, 5);

    std::ostringstream oss;

    dateValue.write(oss);

    EXPECT_EQ("2023-10-05", oss.str());

}



TEST_F(DateValueTest_869, WriteOutputsCorrectFormatForBoundaryConditions_869) {

    DateValue dateValue(0, 1, 1);

    std::ostringstream oss;

    dateValue.write(oss);

    EXPECT_EQ("0000-01-01", oss.str());

}



TEST_F(DateValueTest_869, WriteOutputsCorrectFormatForLargeValues_869) {

    DateValue dateValue(9999, 12, 31);

    std::ostringstream oss;

    dateValue.write(oss);

    EXPECT_EQ("9999-12-31", oss.str());

}



TEST_F(DateValueTest_869, SetDateChangesOutput_869) {

    DateValue dateValue;

    Date newDate{2024, 2, 29};

    dateValue.setDate(newDate);

    std::ostringstream oss;

    dateValue.write(oss);

    EXPECT_EQ("2024-02-29", oss.str());

}



TEST_F(DateValueTest_869, GetDateReturnsCorrectDate_869) {

    Date expectedDate{2025, 3, 15};

    DateValue dateValue(expectedDate.year, expectedDate.month, expectedDate.day);

    EXPECT_EQ(expectedDate.year, dateValue.getDate().year);

    EXPECT_EQ(expectedDate.month, dateValue.getDate().month);

    EXPECT_EQ(expectedDate.day, dateValue.getDate().day);

}



TEST_F(DateValueTest_869, DefaultConstructorInitializesToZero_869) {

    DateValue dateValue;

    const Date& date = dateValue.getDate();

    EXPECT_EQ(0, date.year);

    EXPECT_EQ(0, date.month);

    EXPECT_EQ(0, date.day);

}



TEST_F(DateValueTest_869, CountReturnsOne_869) {

    DateValue dateValue;

    EXPECT_EQ(1u, dateValue.count());

}
