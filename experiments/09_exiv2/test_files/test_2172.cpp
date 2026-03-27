#include <gtest/gtest.h>

#include "exiv2/value.hpp"



namespace {



TEST(DateValueTest_2172, ConstructorInitializesDate_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    const auto& date = dateValue.getDate();

    EXPECT_EQ(date.year, 2023);

    EXPECT_EQ(date.month, 10);

    EXPECT_EQ(date.day, 5);

}



TEST(DateValueTest_2172, DefaultConstructorInitializesDefaultDate_2172) {

    Exiv2::DateValue dateValue;

    const auto& date = dateValue.getDate();

    EXPECT_EQ(date.year, 0);

    EXPECT_EQ(date.month, 0);

    EXPECT_EQ(date.day, 0);

}



TEST(DateValueTest_2172, SetDateUpdatesDate_2172) {

    Exiv2::DateValue dateValue;

    Exiv2::DateValue::Date newDate = {2024, 1, 1};

    dateValue.setDate(newDate);

    const auto& date = dateValue.getDate();

    EXPECT_EQ(date.year, 2024);

    EXPECT_EQ(date.month, 1);

    EXPECT_EQ(date.day, 1);

}



TEST(DateValueTest_2172, CountReturnsOne_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    EXPECT_EQ(dateValue.count(), 1);

}



TEST(DateValueTest_2172, SizeReturnsAppropriateSize_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    EXPECT_EQ(dateValue.size(), sizeof(Exiv2::DateValue::Date));

}



TEST(DateValueTest_2172, ToInt64ReturnsYear_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    EXPECT_EQ(dateValue.toInt64(0), 2023);

}



TEST(DateValueTest_2172, ToUint32ReturnsYear_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    EXPECT_EQ(dateValue.toUint32(0), 2023u);

}



TEST(DateValueTest_2172, ToFloatThrowsException_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    EXPECT_THROW(dateValue.toFloat(0), std::logic_error);

}



TEST(DateValueTest_2172, ToRationalThrowsException_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    EXPECT_THROW(dateValue.toRational(0), std::logic_error);

}



TEST(DateValueTest_2172, ToStringReturnsDateString_2172) {

    Exiv2::DateValue dateValue(2023, 10, 5);

    EXPECT_EQ(dateValue.toString(), "2023-10-05");

}



} // namespace
