#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPUtils.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ConvertToUTCTime_1(XMP_DateTime * time, WXMP_Result * wResult);

class WXMPUtilsConvertToUTCTimeTest_1947 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        // This may be required for XMPUtils functions to work
    }

    void TearDown() override {
    }

    XMP_DateTime MakeDateTime(XMP_Int32 year, XMP_Int32 month, XMP_Int32 day,
                               XMP_Int32 hour, XMP_Int32 minute, XMP_Int32 second,
                               XMP_Int32 tzSign, XMP_Int32 tzHour, XMP_Int32 tzMinute,
                               XMP_Int32 nanoSecond = 0) {
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

// Test that passing a null time pointer sets an error message in wResult
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, NullTimePointerReturnsError_1947) {
    WXMP_Result wResult;
    WXMPUtils_ConvertToUTCTime_1(nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
    // The error message should indicate a null output date / bad param
    EXPECT_TRUE(wResult.errMessage != nullptr);
}

// Test that passing a null time pointer produces an error message containing relevant text
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, NullTimePointerErrorMessage_1947) {
    WXMP_Result wResult;
    WXMPUtils_ConvertToUTCTime_1(nullptr, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // Check that error message is non-empty
    EXPECT_GT(std::strlen(wResult.errMessage), 0u);
}

// Test that a valid UTC time (tzSign=0) does not produce an error
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, ValidUTCTimeNoError_1947) {
    WXMP_Result wResult;
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 12, 30, 45, 0, 0, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that a time with positive timezone offset is converted to UTC
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, PositiveTimezoneConvertedToUTC_1947) {
    WXMP_Result wResult;
    // 2023-06-15 14:30:00 +05:00 should become 2023-06-15 09:30:00 UTC
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 14, 30, 0, 1, 5, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // After conversion, the timezone should be UTC (tzSign=0 or tzHour=0, tzMinute=0)
    EXPECT_EQ(dt.hour, 9);
    EXPECT_EQ(dt.minute, 30);
    EXPECT_EQ(dt.second, 0);
    EXPECT_EQ(dt.tzSign, 0);
    EXPECT_EQ(dt.tzHour, 0);
    EXPECT_EQ(dt.tzMinute, 0);
}

// Test that a time with negative timezone offset is converted to UTC
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, NegativeTimezoneConvertedToUTC_1947) {
    WXMP_Result wResult;
    // 2023-06-15 07:30:00 -05:00 should become 2023-06-15 12:30:00 UTC
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 7, 30, 0, -1, 5, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.hour, 12);
    EXPECT_EQ(dt.minute, 30);
    EXPECT_EQ(dt.second, 0);
    EXPECT_EQ(dt.tzSign, 0);
    EXPECT_EQ(dt.tzHour, 0);
    EXPECT_EQ(dt.tzMinute, 0);
}

// Test conversion across day boundary (positive offset causing day change)
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, DayBoundaryCrossPositiveOffset_1947) {
    WXMP_Result wResult;
    // 2023-06-15 02:00:00 +05:00 should become 2023-06-14 21:00:00 UTC
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 2, 0, 0, 1, 5, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.day, 14);
    EXPECT_EQ(dt.hour, 21);
    EXPECT_EQ(dt.tzSign, 0);
}

// Test conversion across day boundary (negative offset causing day change)
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, DayBoundaryCrossNegativeOffset_1947) {
    WXMP_Result wResult;
    // 2023-06-15 22:00:00 -05:00 should become 2023-06-16 03:00:00 UTC
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 22, 0, 0, -1, 5, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.day, 16);
    EXPECT_EQ(dt.hour, 3);
    EXPECT_EQ(dt.tzSign, 0);
}

// Test that already UTC time remains unchanged
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, AlreadyUTCRemainsUnchanged_1947) {
    WXMP_Result wResult;
    XMP_DateTime dt = MakeDateTime(2023, 1, 1, 0, 0, 0, 0, 0, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 1);
    EXPECT_EQ(dt.day, 1);
    EXPECT_EQ(dt.hour, 0);
    EXPECT_EQ(dt.minute, 0);
    EXPECT_EQ(dt.second, 0);
}

// Test with timezone offset including minutes
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, TimezoneWithMinutesOffset_1947) {
    WXMP_Result wResult;
    // 2023-06-15 12:00:00 +05:30 should become 2023-06-15 06:30:00 UTC
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 12, 0, 0, 1, 5, 30);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.hour, 6);
    EXPECT_EQ(dt.minute, 30);
    EXPECT_EQ(dt.tzSign, 0);
    EXPECT_EQ(dt.tzHour, 0);
    EXPECT_EQ(dt.tzMinute, 0);
}

// Test that nanoseconds are preserved during conversion
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, NanoSecondsPreserved_1947) {
    WXMP_Result wResult;
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 12, 30, 45, 1, 3, 0, 123456789);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.nanoSecond, 123456789);
    EXPECT_EQ(dt.tzSign, 0);
}

// Test with WXMP_Result initialized properly - no error for valid input
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, WXMPResultInitializedProperly_1947) {
    WXMP_Result wResult;
    // Verify WXMP_Result default constructor sets errMessage to 0
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_DateTime dt = MakeDateTime(2023, 12, 31, 23, 59, 59, 0, 0, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test year boundary crossing (positive offset at start of year)
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, YearBoundaryCrossPositiveOffset_1947) {
    WXMP_Result wResult;
    // 2024-01-01 02:00:00 +05:00 should become 2023-12-31 21:00:00 UTC
    XMP_DateTime dt = MakeDateTime(2024, 1, 1, 2, 0, 0, 1, 5, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 12);
    EXPECT_EQ(dt.day, 31);
    EXPECT_EQ(dt.hour, 21);
    EXPECT_EQ(dt.tzSign, 0);
}

// Test month boundary crossing
TEST_F(WXMPUtilsConvertToUTCTimeTest_1947, MonthBoundaryCrossNegativeOffset_1947) {
    WXMP_Result wResult;
    // 2023-06-30 23:00:00 -03:00 should become 2023-07-01 02:00:00 UTC
    XMP_DateTime dt = MakeDateTime(2023, 6, 30, 23, 0, 0, -1, 3, 0);
    WXMPUtils_ConvertToUTCTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(dt.month, 7);
    EXPECT_EQ(dt.day, 1);
    EXPECT_EQ(dt.hour, 2);
    EXPECT_EQ(dt.tzSign, 0);
}
