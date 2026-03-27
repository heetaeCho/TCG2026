#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMPUtils.hpp"



class WXMPUtils_CompareDateTimeTest_1949 : public ::testing::Test {

protected:

    WXMP_Result result;



    XMP_DateTime CreateDateTime(int year, int month, int day, int hour, int minute, int second,

                                int tzSign, int tzHour, int tzMinute, int nanoSecond) {

        XMP_DateTime dt;

        dt.year = year;

        dt.month = month;

        dt.day = day;

        dt.hour = hour;

        dt.minute = minute;

        dt.second = second;

        dt.tzSign = tzSign;

        dt.tzHour = tzHour;

        dt.tzMinute = tzMinute;

        dt.nanoSecond = nanoSecond;

        return dt;

    }

};



TEST_F(WXMPUtils_CompareDateTimeTest_1949, EqualDates_1949) {

    XMP_DateTime left = CreateDateTime(2023, 10, 5, 12, 0, 0, 0, 0, 0, 0);

    XMP_DateTime right = CreateDateTime(2023, 10, 5, 12, 0, 0, 0, 0, 0, 0);



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_EQ(result.int32Result, 0);

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, LeftEarlierThanRight_1949) {

    XMP_DateTime left = CreateDateTime(2023, 10, 5, 12, 0, 0, 0, 0, 0, 0);

    XMP_DateTime right = CreateDateTime(2023, 10, 6, 12, 0, 0, 0, 0, 0, 0);



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_LT(result.int32Result, 0);

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, LeftLaterThanRight_1949) {

    XMP_DateTime left = CreateDateTime(2023, 10, 6, 12, 0, 0, 0, 0, 0, 0);

    XMP_DateTime right = CreateDateTime(2023, 10, 5, 12, 0, 0, 0, 0, 0, 0);



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_GT(result.int32Result, 0);

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, DifferentTimezonesSameLocalTime_1949) {

    XMP_DateTime left = CreateDateTime(2023, 10, 5, 12, 0, 0, -1, 5, 0, 0); // UTC-5

    XMP_DateTime right = CreateDateTime(2023, 10, 5, 18, 0, 0, 1, 5, 0, 0); // UTC+5



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_EQ(result.int32Result, 0);

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, SameYearMonthDayDifferentTime_1949) {

    XMP_DateTime left = CreateDateTime(2023, 10, 5, 12, 0, 0, 0, 0, 0, 0);

    XMP_DateTime right = CreateDateTime(2023, 10, 5, 18, 0, 0, 0, 0, 0, 0);



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_LT(result.int32Result, 0);

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, BoundaryConditionMinValues_1949) {

    XMP_DateTime left = CreateDateTime(1, 1, 1, 0, 0, 0, 0, 0, 0, 0);

    XMP_DateTime right = CreateDateTime(2, 1, 1, 0, 0, 0, 0, 0, 0, 0);



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_LT(result.int32Result, 0);

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, BoundaryConditionMaxValues_1949) {

    XMP_DateTime left = CreateDateTime(9999, 12, 31, 23, 59, 59, 0, 0, 0, 0);

    XMP_DateTime right = CreateDateTime(9998, 12, 31, 23, 59, 59, 0, 0, 0, 0);



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_GT(result.int32Result, 0);

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, SameDateTimeDifferentNanoSeconds_1949) {

    XMP_DateTime left = CreateDateTime(2023, 10, 5, 12, 0, 0, 0, 0, 0, 0);

    XMP_DateTime right = CreateDateTime(2023, 10, 5, 12, 0, 0, 0, 0, 0, 1);



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_EQ(result.int32Result, 0); // Assuming nanoSeconds do not affect comparison

}



TEST_F(WXMPUtils_CompareDateTimeTest_1949, SameDateTimeDifferentTimeZoneSigns_1949) {

    XMP_DateTime left = CreateDateTime(2023, 10, 5, 12, 0, 0, -1, 0, 0, 0); // UTC-0

    XMP_DateTime right = CreateDateTime(2023, 10, 5, 12, 0, 0, 1, 0, 0, 0);  // UTC+0



    WXMPUtils_CompareDateTime_1(left, right, &result);



    EXPECT_EQ(result.int32Result, 0);

}
