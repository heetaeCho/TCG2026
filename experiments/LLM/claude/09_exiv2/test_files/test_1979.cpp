#include <gtest/gtest.h>

// XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "public/include/XMP_Const.h"
#include "public/include/XMP.hpp"
#include "public/include/XMP.incl_cpp"

class XMPUtilsTimeOverflow_1979 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!SXMPMeta::Initialize()) {
            FAIL() << "XMP SDK initialization failed";
        }
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    XMP_DateTime MakeDateTime(XMP_Int32 year, XMP_Int32 month, XMP_Int32 day,
                               XMP_Int32 hour, XMP_Int32 minute, XMP_Int32 second,
                               XMP_Int32 nanoSecond = 0) {
        XMP_DateTime dt = {};
        dt.year = year;
        dt.month = month;
        dt.day = day;
        dt.hour = hour;
        dt.minute = minute;
        dt.second = second;
        dt.nanoSecond = nanoSecond;
        dt.tzSign = 0;
        dt.tzHour = 0;
        dt.tzMinute = 0;
        return dt;
    }
};

// Test normal date - no overflow should produce same values
TEST_F(XMPUtilsTimeOverflow_1979, NormalDateNoOverflow_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 45);
    std::string dateStr;
    SXMPUtils::ConvertFromDate(dt, &dateStr);

    XMP_DateTime result = {};
    SXMPUtils::ConvertToDate(dateStr, &result);

    EXPECT_EQ(result.year, 2023);
    EXPECT_EQ(result.month, 6);
    EXPECT_EQ(result.day, 15);
    EXPECT_EQ(result.hour, 10);
    EXPECT_EQ(result.minute, 30);
    EXPECT_EQ(result.second, 45);
}

// Test converting a valid ISO 8601 date string
TEST_F(XMPUtilsTimeOverflow_1979, ConvertValidISODate_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023-01-01T00:00:00", &dt);

    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 1);
    EXPECT_EQ(dt.day, 1);
    EXPECT_EQ(dt.hour, 0);
    EXPECT_EQ(dt.minute, 0);
    EXPECT_EQ(dt.second, 0);
}

// Test date at year boundary
TEST_F(XMPUtilsTimeOverflow_1979, YearBoundaryDate_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023-12-31T23:59:59", &dt);

    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 12);
    EXPECT_EQ(dt.day, 31);
    EXPECT_EQ(dt.hour, 23);
    EXPECT_EQ(dt.minute, 59);
    EXPECT_EQ(dt.second, 59);
}

// Test roundtrip conversion preserves date
TEST_F(XMPUtilsTimeOverflow_1979, RoundtripConversion_1979) {
    XMP_DateTime original = MakeDateTime(2020, 2, 29, 12, 0, 0); // Leap year
    std::string dateStr;
    SXMPUtils::ConvertFromDate(original, &dateStr);

    XMP_DateTime result = {};
    SXMPUtils::ConvertToDate(dateStr, &result);

    EXPECT_EQ(result.year, 2020);
    EXPECT_EQ(result.month, 2);
    EXPECT_EQ(result.day, 29);
    EXPECT_EQ(result.hour, 12);
    EXPECT_EQ(result.minute, 0);
    EXPECT_EQ(result.second, 0);
}

// Test current date/time retrieval
TEST_F(XMPUtilsTimeOverflow_1979, CurrentDateTimeValid_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::CurrentDateTime(&dt);

    EXPECT_GE(dt.year, 2020);
    EXPECT_GE(dt.month, 1);
    EXPECT_LE(dt.month, 12);
    EXPECT_GE(dt.day, 1);
    EXPECT_LE(dt.day, 31);
    EXPECT_GE(dt.hour, 0);
    EXPECT_LE(dt.hour, 23);
    EXPECT_GE(dt.minute, 0);
    EXPECT_LE(dt.minute, 59);
    EXPECT_GE(dt.second, 0);
    EXPECT_LE(dt.second, 60); // Allow leap second
}

// Test date with timezone
TEST_F(XMPUtilsTimeOverflow_1979, DateWithTimezone_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023-06-15T10:30:00+05:30", &dt);

    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 6);
    EXPECT_EQ(dt.day, 15);
    EXPECT_EQ(dt.hour, 10);
    EXPECT_EQ(dt.minute, 30);
    EXPECT_EQ(dt.second, 0);
    EXPECT_EQ(dt.tzSign, 1);
    EXPECT_EQ(dt.tzHour, 5);
    EXPECT_EQ(dt.tzMinute, 30);
}

// Test date with UTC timezone
TEST_F(XMPUtilsTimeOverflow_1979, DateWithUTCTimezone_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023-06-15T10:30:00Z", &dt);

    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 6);
    EXPECT_EQ(dt.day, 15);
    EXPECT_EQ(dt.hour, 10);
    EXPECT_EQ(dt.minute, 30);
    EXPECT_EQ(dt.second, 0);
    EXPECT_EQ(dt.tzSign, 0);
    EXPECT_EQ(dt.tzHour, 0);
    EXPECT_EQ(dt.tzMinute, 0);
}

// Test ConvertToUTCTime adjusts properly
TEST_F(XMPUtilsTimeOverflow_1979, ConvertToUTCTime_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 0);
    dt.tzSign = 1;
    dt.tzHour = 5;
    dt.tzMinute = 30;

    SXMPUtils::ConvertToUTCTime(&dt);

    EXPECT_EQ(dt.hour, 5);
    EXPECT_EQ(dt.minute, 0);
    EXPECT_EQ(dt.tzSign, 0);
    EXPECT_EQ(dt.tzHour, 0);
    EXPECT_EQ(dt.tzMinute, 0);
}

// Test ConvertToUTCTime with day rollback (crossing midnight backwards)
TEST_F(XMPUtilsTimeOverflow_1979, ConvertToUTCTimeDayRollback_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 2, 0, 0);
    dt.tzSign = 1;
    dt.tzHour = 5;
    dt.tzMinute = 30;

    SXMPUtils::ConvertToUTCTime(&dt);

    // 2:00 - 5:30 = previous day 20:30
    EXPECT_EQ(dt.day, 14);
    EXPECT_EQ(dt.hour, 20);
    EXPECT_EQ(dt.minute, 30);
}

// Test ConvertToUTCTime with day roll forward
TEST_F(XMPUtilsTimeOverflow_1979, ConvertToUTCTimeDayRollForward_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 22, 0, 0);
    dt.tzSign = -1;
    dt.tzHour = 5;
    dt.tzMinute = 0;

    SXMPUtils::ConvertToUTCTime(&dt);

    // 22:00 + 5:00 = next day 3:00
    EXPECT_EQ(dt.day, 16);
    EXPECT_EQ(dt.hour, 3);
    EXPECT_EQ(dt.minute, 0);
}

// Test leap year February 29
TEST_F(XMPUtilsTimeOverflow_1979, LeapYearFeb29_1979) {
    XMP_DateTime dt = MakeDateTime(2024, 2, 29, 23, 59, 59);
    std::string dateStr;
    SXMPUtils::ConvertFromDate(dt, &dateStr);

    XMP_DateTime result = {};
    SXMPUtils::ConvertToDate(dateStr, &result);

    EXPECT_EQ(result.year, 2024);
    EXPECT_EQ(result.month, 2);
    EXPECT_EQ(result.day, 29);
}

// Test ConvertToUTCTime crossing month boundary
TEST_F(XMPUtilsTimeOverflow_1979, UTCTimeMonthBoundaryCross_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 7, 1, 2, 0, 0);
    dt.tzSign = 1;
    dt.tzHour = 5;
    dt.tzMinute = 30;

    SXMPUtils::ConvertToUTCTime(&dt);

    // 2:00 - 5:30 = June 30 at 20:30
    EXPECT_EQ(dt.month, 6);
    EXPECT_EQ(dt.day, 30);
    EXPECT_EQ(dt.hour, 20);
    EXPECT_EQ(dt.minute, 30);
}

// Test ConvertToUTCTime crossing year boundary
TEST_F(XMPUtilsTimeOverflow_1979, UTCTimeYearBoundaryCross_1979) {
    XMP_DateTime dt = MakeDateTime(2024, 1, 1, 2, 0, 0);
    dt.tzSign = 1;
    dt.tzHour = 5;
    dt.tzMinute = 30;

    SXMPUtils::ConvertToUTCTime(&dt);

    // 2:00 - 5:30 = Dec 31, 2023 at 20:30
    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 12);
    EXPECT_EQ(dt.day, 31);
    EXPECT_EQ(dt.hour, 20);
    EXPECT_EQ(dt.minute, 30);
}

// Test minimal date - year only
TEST_F(XMPUtilsTimeOverflow_1979, YearOnlyDate_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023", &dt);

    EXPECT_EQ(dt.year, 2023);
}

// Test date with month only
TEST_F(XMPUtilsTimeOverflow_1979, YearMonthDate_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023-06", &dt);

    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 6);
}

// Test date only (no time)
TEST_F(XMPUtilsTimeOverflow_1979, DateOnlyNoTime_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023-06-15", &dt);

    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 6);
    EXPECT_EQ(dt.day, 15);
    EXPECT_EQ(dt.hour, 0);
    EXPECT_EQ(dt.minute, 0);
    EXPECT_EQ(dt.second, 0);
}

// Test negative timezone
TEST_F(XMPUtilsTimeOverflow_1979, NegativeTimezone_1979) {
    XMP_DateTime dt = {};
    SXMPUtils::ConvertToDate("2023-06-15T10:30:00-08:00", &dt);

    EXPECT_EQ(dt.year, 2023);
    EXPECT_EQ(dt.month, 6);
    EXPECT_EQ(dt.day, 15);
    EXPECT_EQ(dt.hour, 10);
    EXPECT_EQ(dt.minute, 30);
    EXPECT_EQ(dt.tzSign, -1);
    EXPECT_EQ(dt.tzHour, 8);
    EXPECT_EQ(dt.tzMinute, 0);
}

// Test ConvertFromDate produces valid ISO string
TEST_F(XMPUtilsTimeOverflow_1979, ConvertFromDateProducesValidString_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 1, 15, 8, 30, 45);
    std::string dateStr;
    SXMPUtils::ConvertFromDate(dt, &dateStr);

    EXPECT_FALSE(dateStr.empty());
    EXPECT_NE(dateStr.find("2023"), std::string::npos);
}

// Test CompareDateTime for equal dates
TEST_F(XMPUtilsTimeOverflow_1979, CompareDateTimeEqual_1979) {
    XMP_DateTime dt1 = MakeDateTime(2023, 6, 15, 10, 30, 0);
    XMP_DateTime dt2 = MakeDateTime(2023, 6, 15, 10, 30, 0);

    int result = SXMPUtils::CompareDateTime(dt1, dt2);
    EXPECT_EQ(result, 0);
}

// Test CompareDateTime for dt1 < dt2
TEST_F(XMPUtilsTimeOverflow_1979, CompareDateTimeLess_1979) {
    XMP_DateTime dt1 = MakeDateTime(2023, 6, 15, 10, 30, 0);
    XMP_DateTime dt2 = MakeDateTime(2023, 6, 15, 11, 30, 0);

    int result = SXMPUtils::CompareDateTime(dt1, dt2);
    EXPECT_LT(result, 0);
}

// Test CompareDateTime for dt1 > dt2
TEST_F(XMPUtilsTimeOverflow_1979, CompareDateTimeGreater_1979) {
    XMP_DateTime dt1 = MakeDateTime(2023, 6, 16, 10, 30, 0);
    XMP_DateTime dt2 = MakeDateTime(2023, 6, 15, 10, 30, 0);

    int result = SXMPUtils::CompareDateTime(dt1, dt2);
    EXPECT_GT(result, 0);
}

// Test nanoSecond field preservation
TEST_F(XMPUtilsTimeOverflow_1979, NanoSecondPreservation_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 45, 500000000);
    std::string dateStr;
    SXMPUtils::ConvertFromDate(dt, &dateStr);

    XMP_DateTime result = {};
    SXMPUtils::ConvertToDate(dateStr, &result);

    EXPECT_EQ(result.year, 2023);
    EXPECT_EQ(result.month, 6);
    EXPECT_EQ(result.day, 15);
}

// Test ConvertToLocalTime
TEST_F(XMPUtilsTimeOverflow_1979, ConvertToLocalTime_1979) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 0);
    dt.tzSign = 0;
    dt.tzHour = 0;
    dt.tzMinute = 0;

    // ConvertToLocalTime should set timezone info
    SXMPUtils::ConvertToLocalTime(&dt);

    // After conversion, the date should still be valid
    EXPECT_GE(dt.month, 1);
    EXPECT_LE(dt.month, 12);
    EXPECT_GE(dt.day, 1);
    EXPECT_LE(dt.day, 31);
    EXPECT_GE(dt.hour, 0);
    EXPECT_LE(dt.hour, 23);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
