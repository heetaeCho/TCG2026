#include <gtest/gtest.h>
#include <string>

// Include the necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "public/include/XMP.incl_cpp"
#include "public/include/XMP_Const.h"
#include "public/include/XMP.hpp"

class XMPUtilsFormatDateTest_1981 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!SXMPMeta::Initialize()) {
            FAIL() << "XMP Toolkit initialization failed";
        }
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        memset(&date, 0, sizeof(date));
    }

    XMP_DateTime date;
    std::string dateStr;
};

// Test normal date with no seconds and no nanoseconds -> format "YYYY-MM-DDThh:mm"
TEST_F(XMPUtilsFormatDateTest_1981, NoSecondsNoNano_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 0;
    date.nanoSecond = 0;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    // Should produce format without seconds: "2023-06-15T10:30"
    EXPECT_NE(dateStr.find("2023-06-15T10:30"), std::string::npos);
    // Should NOT contain seconds portion beyond minute
    // The string should not have ":00" after the minute (since second==0 and nano==0)
}

// Test normal date with seconds but no nanoseconds -> format "YYYY-MM-DDThh:mm:ss"
TEST_F(XMPUtilsFormatDateTest_1981, WithSecondsNoNano_1981) {
    date.year = 2023;
    date.month = 12;
    date.day = 25;
    date.hour = 23;
    date.minute = 59;
    date.second = 45;
    date.nanoSecond = 0;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2023-12-25T23:59:45"), std::string::npos);
}

// Test normal date with seconds and nanoseconds -> format "YYYY-MM-DDThh:mm:ss.nnnnnnnnn" (trailing zeros trimmed)
TEST_F(XMPUtilsFormatDateTest_1981, WithSecondsAndNano_1981) {
    date.year = 2023;
    date.month = 1;
    date.day = 1;
    date.hour = 0;
    date.minute = 0;
    date.second = 1;
    date.nanoSecond = 123456789;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2023-01-01T00:00:01.123456789"), std::string::npos);
}

// Test nanoseconds with trailing zeros get trimmed
TEST_F(XMPUtilsFormatDateTest_1981, NanoTrailingZerosTrimmed_1981) {
    date.year = 2020;
    date.month = 3;
    date.day = 10;
    date.hour = 5;
    date.minute = 15;
    date.second = 30;
    date.nanoSecond = 100000000; // 0.1 seconds
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2020-03-10T05:15:30.1"), std::string::npos);
    // Should not end with trailing zeros after .1
    // Check that ".10" is not present (trailing zero should be trimmed)
    size_t pos = dateStr.find("2020-03-10T05:15:30.1");
    if (pos != std::string::npos) {
        size_t afterDot1 = pos + strlen("2020-03-10T05:15:30.1");
        if (afterDot1 < dateStr.size()) {
            EXPECT_NE(dateStr[afterDot1], '0');
        }
    }
}

// Test with zero second but nonzero nanosecond -> should include seconds and nanos
TEST_F(XMPUtilsFormatDateTest_1981, ZeroSecondWithNano_1981) {
    date.year = 2021;
    date.month = 7;
    date.day = 4;
    date.hour = 12;
    date.minute = 0;
    date.second = 0;
    date.nanoSecond = 500000000; // 0.5 seconds
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2021-07-04T12:00:00.5"), std::string::npos);
}

// Test boundary: year with leading zeros (year < 1000)
TEST_F(XMPUtilsFormatDateTest_1981, SmallYear_1981) {
    date.year = 100;
    date.month = 1;
    date.day = 1;
    date.hour = 0;
    date.minute = 0;
    date.second = 0;
    date.nanoSecond = 0;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("0100-01-01T00:00"), std::string::npos);
}

// Test nanosecond = 1 (smallest nonzero) - trailing zeros trimmed
TEST_F(XMPUtilsFormatDateTest_1981, NanoSecondOne_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 5;
    date.nanoSecond = 1;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2023-06-15T10:30:05.000000001"), std::string::npos);
}

// Test nanosecond with middle zeros
TEST_F(XMPUtilsFormatDateTest_1981, NanoMiddleZeros_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 5;
    date.nanoSecond = 100100000;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2023-06-15T10:30:05.1001"), std::string::npos);
}

// Test date with all maximum-ish normal values
TEST_F(XMPUtilsFormatDateTest_1981, MaxNormalValues_1981) {
    date.year = 9999;
    date.month = 12;
    date.day = 31;
    date.hour = 23;
    date.minute = 59;
    date.second = 59;
    date.nanoSecond = 999999999;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("9999-12-31T23:59:59.999999999"), std::string::npos);
}

// Test with timezone information
TEST_F(XMPUtilsFormatDateTest_1981, WithTimezone_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 0;
    date.nanoSecond = 0;
    date.tzSign = 1;
    date.tzHour = 5;
    date.tzMinute = 30;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    // Should contain the date portion
    EXPECT_NE(dateStr.find("2023-06-15T10:30"), std::string::npos);
    // Should contain timezone info
    EXPECT_NE(dateStr.find("+05:30"), std::string::npos);
}

// Test UTC timezone (tzSign = 0 but with tzHour=0, tzMinute=0 explicitly set)
TEST_F(XMPUtilsFormatDateTest_1981, UTCTimezone_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 15;
    date.nanoSecond = 0;
    date.tzSign = 1;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2023-06-15T10:30:15"), std::string::npos);
}

// Test negative timezone
TEST_F(XMPUtilsFormatDateTest_1981, NegativeTimezone_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 0;
    date.nanoSecond = 0;
    date.tzSign = -1;
    date.tzHour = 8;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_NE(dateStr.find("2023-06-15T10:30"), std::string::npos);
    EXPECT_NE(dateStr.find("-08:00"), std::string::npos);
}

// Test round-trip: ConvertFromDate then ConvertToDate should preserve values
TEST_F(XMPUtilsFormatDateTest_1981, RoundTrip_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 45;
    date.nanoSecond = 0;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);

    XMP_DateTime parsedDate;
    memset(&parsedDate, 0, sizeof(parsedDate));
    SXMPUtils::ConvertToDate(dateStr, &parsedDate);

    EXPECT_EQ(parsedDate.year, 2023);
    EXPECT_EQ(parsedDate.month, 6);
    EXPECT_EQ(parsedDate.day, 15);
    EXPECT_EQ(parsedDate.hour, 10);
    EXPECT_EQ(parsedDate.minute, 30);
    EXPECT_EQ(parsedDate.second, 45);
}

// Test round-trip with nanoseconds
TEST_F(XMPUtilsFormatDateTest_1981, RoundTripWithNano_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 10;
    date.minute = 30;
    date.second = 45;
    date.nanoSecond = 123000000;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);

    XMP_DateTime parsedDate;
    memset(&parsedDate, 0, sizeof(parsedDate));
    SXMPUtils::ConvertToDate(dateStr, &parsedDate);

    EXPECT_EQ(parsedDate.year, 2023);
    EXPECT_EQ(parsedDate.month, 6);
    EXPECT_EQ(parsedDate.day, 15);
    EXPECT_EQ(parsedDate.hour, 10);
    EXPECT_EQ(parsedDate.minute, 30);
    EXPECT_EQ(parsedDate.second, 45);
    EXPECT_EQ(parsedDate.nanoSecond, 123000000);
}

// Test date-only (year, month, day only)
TEST_F(XMPUtilsFormatDateTest_1981, DateOnly_1981) {
    date.year = 2023;
    date.month = 6;
    date.day = 15;
    date.hour = 0;
    date.minute = 0;
    date.second = 0;
    date.nanoSecond = 0;
    date.tzSign = 0;
    date.tzHour = 0;
    date.tzMinute = 0;

    SXMPUtils::ConvertFromDate(date, &dateStr);
    EXPECT_FALSE(dateStr.empty());
    EXPECT_NE(dateStr.find("2023"), std::string::npos);
}
