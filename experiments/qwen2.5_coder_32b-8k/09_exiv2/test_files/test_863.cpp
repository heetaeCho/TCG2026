#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class DateValueTest_863 : public ::testing::Test {

protected:

    DateValue dateValue;

};



TEST_F(DateValueTest_863, ReadValidDate_863) {

    std::string validDate = "2023-10-15";

    EXPECT_EQ(dateValue.read(validDate), 0);

}



TEST_F(DateValueTest_863, ReadShortValidDate_863) {

    std::string shortValidDate = "20231015";

    EXPECT_EQ(dateValue.read(shortValidDate), 0);

}



TEST_F(DateValueTest_863, ReadInvalidDateTooShort_863) {

    std::string tooShortDate = "2023-10";

    EXPECT_EQ(dateValue.read(tooShortDate), 1);

}



TEST_F(DateValueTest_863, ReadInvalidDateNonNumericYear_863) {

    std::string invalidYear = "abcd-10-15";

    EXPECT_EQ(dateValue.read(invalidYear), 1);

}



TEST_F(DateValueTest_863, ReadInvalidDateNonNumericMonth_863) {

    std::string invalidMonth = "2023-ab-15";

    EXPECT_EQ(dateValue.read(invalidMonth), 1);

}



TEST_F(DateValueTest_863, ReadInvalidDateNonNumericDay_863) {

    std::string invalidDay = "2023-10-cd";

    EXPECT_EQ(dateValue.read(invalidDay), 1);

}



TEST_F(DateValueTest_863, ReadInvalidDateMonthGreaterThan12_863) {

    std::string monthTooLarge = "2023-13-15";

    EXPECT_EQ(dateValue.read(monthTooLarge), 1);

}



TEST_F(DateValueTest_863, ReadInvalidDateDayGreaterThan31_863) {

    std::string dayTooLarge = "2023-10-32";

    EXPECT_EQ(dateValue.read(dayTooLarge), 1);

}
