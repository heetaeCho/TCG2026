#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPUtils.cpp"  // Assuming the file is included this way for testing purposes



// Since DaysInMonth is a static function within XMPUtils.cpp and not part of a class,

// we will create a simple wrapper class to make it testable with Google Test.

class XMPUtilsWrapper {

public:

    static int DaysInMonth(XMP_Int32 year, XMP_Int32 month) {

        return ::DaysInMonth(year, month);

    }

};



using namespace testing;



TEST(DaysInMonthTest_1978, JanuaryHas31Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 1), 31);

}



TEST(DaysInMonthTest_1978, FebruaryNonLeapYearHas28Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 2), 28);

}



TEST(DaysInMonthTest_1978, FebruaryLeapYearHas29Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2024, 2), 29);

}



TEST(DaysInMonthTest_1978, MarchHas31Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 3), 31);

}



TEST(DaysInMonthTest_1978, AprilHas30Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 4), 30);

}



TEST(DaysInMonthTest_1978, MayHas31Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 5), 31);

}



TEST(DaysInMonthTest_1978, JuneHas30Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 6), 30);

}



TEST(DaysInMonthTest_1978, JulyHas31Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 7), 31);

}



TEST(DaysInMonthTest_1978, AugustHas31Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 8), 31);

}



TEST(DaysInMonthTest_1978, SeptemberHas30Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 9), 30);

}



TEST(DaysInMonthTest_1978, OctoberHas31Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 10), 31);

}



TEST(DaysInMonthTest_1978, NovemberHas30Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 11), 30);

}



TEST(DaysInMonthTest_1978, DecemberHas31Days_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 12), 31);

}



TEST(DaysInMonthTest_1978, InvalidMonthReturnsZero_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 0), 0);   // Month out of range

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(2023, 13), 0);  // Month out of range

}



TEST(DaysInMonthTest_1978, BoundaryYearLeapYearCheck_1978) {

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(1600, 2), 29);  // Leap year divisible by 400

    EXPECT_EQ(XMPUtilsWrapper::DaysInMonth(1700, 2), 28);  // Not a leap year (divisible by 100 but not 400)

}
