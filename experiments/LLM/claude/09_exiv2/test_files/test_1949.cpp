#include <gtest/gtest.h>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPUtils.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_CompareDateTime_1(const XMP_DateTime & left, const XMP_DateTime & right, WXMP_Result * wResult);

class WXMPUtilsCompareDateTimeTest_1949 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPUtils is initialized
        XMPUtils::Initialize();
    }

    void TearDown() override {
        XMPUtils::Terminate();
    }

    XMP_DateTime MakeDateTime(XMP_Int32 year, XMP_Int32 month, XMP_Int32 day,
                               XMP_Int32 hour, XMP_Int32 minute, XMP_Int32 second,
                               XMP_Int32 nanoSecond = 0,
                               XMP_Int32 tzSign = 0, XMP_Int32 tzHour = 0, XMP_Int32 tzMinute = 0) {
        XMP_DateTime dt;
        dt.year = year;
        dt.month = month;
        dt.day = day;
        dt.hour = hour;
        dt.minute = minute;
        dt.second = second;
        dt.nanoSecond = nanoSecond;
        dt.tzSign = tzSign;
        dt.tzHour = tzHour;
        dt.tzMinute = tzMinute;
        return dt;
    }
};

// Test: Two identical dates should compare as equal (result == 0)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, EqualDates_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is earlier than right date (by year)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftEarlierByYear_1949) {
    XMP_DateTime left = MakeDateTime(2022, 6, 15, 12, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is later than right date (by year)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftLaterByYear_1949) {
    XMP_DateTime left = MakeDateTime(2024, 6, 15, 12, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is earlier than right date (by month)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftEarlierByMonth_1949) {
    XMP_DateTime left = MakeDateTime(2023, 5, 15, 12, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is later than right date (by month)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftLaterByMonth_1949) {
    XMP_DateTime left = MakeDateTime(2023, 7, 15, 12, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is earlier by day
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftEarlierByDay_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 14, 12, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is later by day
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftLaterByDay_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 16, 12, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is earlier by hour
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftEarlierByHour_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 11, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is later by hour
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftLaterByHour_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 13, 30, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is earlier by minute
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftEarlierByMinute_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 29, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is later by minute
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftLaterByMinute_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 31, 45);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is earlier by second
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftEarlierBySecond_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 30, 44);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Left date is later by second
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftLaterBySecond_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 30, 46);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Comparison with nanosecond difference
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftEarlierByNanosecond_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 30, 45, 100);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45, 200);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LE(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Comparison with nanosecond difference (left later)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeftLaterByNanosecond_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 30, 45, 500);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45, 100);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GE(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Comparison with timezone differences - same actual time
TEST_F(WXMPUtilsCompareDateTimeTest_1949, SameTimeWithDifferentTimezones_1949) {
    // 12:00 UTC+0 == 13:00 UTC+1
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 0, 0, 0, 0, 0, 0);   // UTC
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 13, 0, 0, 0, 1, 1, 0);   // UTC+1
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Timezone makes left earlier
TEST_F(WXMPUtilsCompareDateTimeTest_1949, TimezoneLeftEarlier_1949) {
    // 12:00 UTC+0 vs 14:00 UTC+1 (14:00-1:00 = 13:00 UTC, so left < right)
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 0, 0, 0, 0, 0, 0);   // UTC
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 14, 0, 0, 0, 1, 1, 0);   // UTC+1 => 13:00 UTC
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Boundary - zero date/time values
TEST_F(WXMPUtilsCompareDateTimeTest_1949, ZeroDateTimes_1949) {
    XMP_DateTime left = MakeDateTime(0, 0, 0, 0, 0, 0);
    XMP_DateTime right = MakeDateTime(0, 0, 0, 0, 0, 0);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Boundary - minimum vs maximum year
TEST_F(WXMPUtilsCompareDateTimeTest_1949, MinVsMaxYear_1949) {
    XMP_DateTime left = MakeDateTime(1, 1, 1, 0, 0, 0);
    XMP_DateTime right = MakeDateTime(9999, 12, 31, 23, 59, 59);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized (errMessage should be null on success)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, ResultInitialization_1949) {
    XMP_DateTime left = MakeDateTime(2023, 1, 1, 0, 0, 0);
    XMP_DateTime right = MakeDateTime(2023, 1, 1, 0, 0, 0);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Symmetry - if left < right, then right > left
TEST_F(WXMPUtilsCompareDateTimeTest_1949, SymmetryProperty_1949) {
    XMP_DateTime earlier = MakeDateTime(2023, 1, 1, 0, 0, 0);
    XMP_DateTime later = MakeDateTime(2023, 12, 31, 23, 59, 59);
    WXMP_Result wResult1, wResult2;

    WXMPUtils_CompareDateTime_1(earlier, later, &wResult1);
    WXMPUtils_CompareDateTime_1(later, earlier, &wResult2);

    EXPECT_LT(wResult1.int32Result, 0);
    EXPECT_GT(wResult2.int32Result, 0);
}

// Test: Negative timezone
TEST_F(WXMPUtilsCompareDateTimeTest_1949, NegativeTimezone_1949) {
    // 10:00 UTC-2 => 12:00 UTC, same as 12:00 UTC+0
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 10, 0, 0, 0, -1, 2, 0);  // UTC-2
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 0, 0, 0, 0, 0, 0);  // UTC
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Dates differing only in timezone (left is effectively later)
TEST_F(WXMPUtilsCompareDateTimeTest_1949, TimezoneMakesLeftLater_1949) {
    // 12:00 UTC-5 => 17:00 UTC vs 12:00 UTC+0 => 12:00 UTC, so left > right
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 0, 0, 0, -1, 5, 0);  // UTC-5
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 0, 0, 0, 0, 0, 0);  // UTC
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_GT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Leap year date
TEST_F(WXMPUtilsCompareDateTimeTest_1949, LeapYearDate_1949) {
    XMP_DateTime left = MakeDateTime(2024, 2, 29, 12, 0, 0);
    XMP_DateTime right = MakeDateTime(2024, 3, 1, 12, 0, 0);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Same date different by one second
TEST_F(WXMPUtilsCompareDateTimeTest_1949, OneSecondDifference_1949) {
    XMP_DateTime left = MakeDateTime(2023, 6, 15, 12, 30, 44);
    XMP_DateTime right = MakeDateTime(2023, 6, 15, 12, 30, 45);
    WXMP_Result wResult;

    WXMPUtils_CompareDateTime_1(left, right, &wResult);

    EXPECT_LT(wResult.int32Result, 0);
    EXPECT_EQ(wResult.errMessage, nullptr);
}
