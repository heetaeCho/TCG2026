#include <gtest/gtest.h>
#include <memory>
#include <ctime>
#include <cstring>
#include <string>

// Include the necessary headers from poppler
#include "poppler/DateInfo.h"
#include "goo/GooString.h"

class DateInfoTest_1993 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that timeToDateString returns a non-null result for a valid time
TEST_F(DateInfoTest_1993, ReturnsNonNullForValidTime_1993) {
    time_t t = time(nullptr);
    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
}

// Test that the result starts with "D:" prefix as per PDF date format
TEST_F(DateInfoTest_1993, ResultStartsWithDPrefix_1993) {
    time_t t = time(nullptr);
    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    std::string str = result->c_str();
    EXPECT_EQ(str.substr(0, 2), "D:");
}

// Test with epoch time (January 1, 1970 00:00:00 UTC)
TEST_F(DateInfoTest_1993, EpochTime_1993) {
    time_t t = 0;
    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    std::string str = result->c_str();
    EXPECT_EQ(str.substr(0, 2), "D:");
    // After "D:" we expect a year starting with "1970"
    EXPECT_EQ(str.substr(2, 4), "1970");
}

// Test with a known specific date: 2023-06-15 12:30:45
TEST_F(DateInfoTest_1993, KnownSpecificDate_1993) {
    struct tm tm_val;
    memset(&tm_val, 0, sizeof(tm_val));
    tm_val.tm_year = 2023 - 1900;
    tm_val.tm_mon = 6 - 1; // June (0-indexed)
    tm_val.tm_mday = 15;
    tm_val.tm_hour = 12;
    tm_val.tm_min = 30;
    tm_val.tm_sec = 45;
    tm_val.tm_isdst = -1;
    time_t t = mktime(&tm_val);
    ASSERT_NE(t, (time_t)-1);

    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    std::string str = result->c_str();
    EXPECT_EQ(str.substr(0, 2), "D:");
    EXPECT_EQ(str.substr(2, 4), "2023");
    EXPECT_EQ(str.substr(6, 2), "06");
    EXPECT_EQ(str.substr(8, 2), "15");
    EXPECT_EQ(str.substr(10, 2), "12");
    EXPECT_EQ(str.substr(12, 2), "30");
    EXPECT_EQ(str.substr(14, 2), "45");
}

// Test with a date in the year 2000 (Y2K boundary)
TEST_F(DateInfoTest_1993, Y2KBoundary_1993) {
    struct tm tm_val;
    memset(&tm_val, 0, sizeof(tm_val));
    tm_val.tm_year = 2000 - 1900;
    tm_val.tm_mon = 0;  // January
    tm_val.tm_mday = 1;
    tm_val.tm_hour = 0;
    tm_val.tm_min = 0;
    tm_val.tm_sec = 0;
    tm_val.tm_isdst = -1;
    time_t t = mktime(&tm_val);
    ASSERT_NE(t, (time_t)-1);

    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    std::string str = result->c_str();
    EXPECT_EQ(str.substr(0, 2), "D:");
    EXPECT_EQ(str.substr(2, 4), "2000");
    EXPECT_EQ(str.substr(6, 2), "01");
    EXPECT_EQ(str.substr(8, 2), "01");
}

// Test that the returned string length is reasonable for a PDF date string
// PDF date format: D:YYYYMMDDHHmmSS+HH'mm' or similar
TEST_F(DateInfoTest_1993, ResultHasReasonableLength_1993) {
    time_t t = time(nullptr);
    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    // Minimum: "D:YYYYMMDDHHmmSS" = 18 chars, plus timezone info
    EXPECT_GE(result->getLength(), 18);
}

// Test with December 31st end-of-year boundary
TEST_F(DateInfoTest_1993, EndOfYearBoundary_1993) {
    struct tm tm_val;
    memset(&tm_val, 0, sizeof(tm_val));
    tm_val.tm_year = 2023 - 1900;
    tm_val.tm_mon = 11; // December
    tm_val.tm_mday = 31;
    tm_val.tm_hour = 23;
    tm_val.tm_min = 59;
    tm_val.tm_sec = 59;
    tm_val.tm_isdst = -1;
    time_t t = mktime(&tm_val);
    ASSERT_NE(t, (time_t)-1);

    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    std::string str = result->c_str();
    EXPECT_EQ(str.substr(0, 2), "D:");
    EXPECT_EQ(str.substr(2, 4), "2023");
    EXPECT_EQ(str.substr(6, 2), "12");
    EXPECT_EQ(str.substr(8, 2), "31");
    EXPECT_EQ(str.substr(10, 2), "23");
    EXPECT_EQ(str.substr(12, 2), "59");
    EXPECT_EQ(str.substr(14, 2), "59");
}

// Test with a date in 1999 (pre-Y2K)
TEST_F(DateInfoTest_1993, PreY2KDate_1993) {
    struct tm tm_val;
    memset(&tm_val, 0, sizeof(tm_val));
    tm_val.tm_year = 1999 - 1900;
    tm_val.tm_mon = 11; // December
    tm_val.tm_mday = 31;
    tm_val.tm_hour = 23;
    tm_val.tm_min = 59;
    tm_val.tm_sec = 59;
    tm_val.tm_isdst = -1;
    time_t t = mktime(&tm_val);
    ASSERT_NE(t, (time_t)-1);

    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    std::string str = result->c_str();
    EXPECT_EQ(str.substr(0, 2), "D:");
    EXPECT_EQ(str.substr(2, 4), "1999");
}

// Test that two calls with the same time produce the same result
TEST_F(DateInfoTest_1993, ConsistentResults_1993) {
    time_t t = 1000000;
    auto result1 = timeToDateString(&t);
    auto result2 = timeToDateString(&t);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    std::string str1 = result1->c_str();
    std::string str2 = result2->c_str();
    EXPECT_EQ(str1, str2);
}

// Test that different times produce different results
TEST_F(DateInfoTest_1993, DifferentTimesProduceDifferentResults_1993) {
    time_t t1 = 0;
    time_t t2 = 86400; // One day later
    auto result1 = timeToDateString(&t1);
    auto result2 = timeToDateString(&t2);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    std::string str1 = result1->c_str();
    std::string str2 = result2->c_str();
    EXPECT_NE(str1, str2);
}

// Test with a large time value (far future date)
TEST_F(DateInfoTest_1993, FarFutureDate_1993) {
    struct tm tm_val;
    memset(&tm_val, 0, sizeof(tm_val));
    tm_val.tm_year = 2038 - 1900;
    tm_val.tm_mon = 0;  // January
    tm_val.tm_mday = 1;
    tm_val.tm_hour = 0;
    tm_val.tm_min = 0;
    tm_val.tm_sec = 0;
    tm_val.tm_isdst = -1;
    time_t t = mktime(&tm_val);
    if (t != (time_t)-1) {
        auto result = timeToDateString(&t);
        ASSERT_NE(result, nullptr);
        std::string str = result->c_str();
        EXPECT_EQ(str.substr(0, 2), "D:");
        EXPECT_EQ(str.substr(2, 4), "2038");
    }
}

// Test with midnight boundary
TEST_F(DateInfoTest_1993, MidnightBoundary_1993) {
    struct tm tm_val;
    memset(&tm_val, 0, sizeof(tm_val));
    tm_val.tm_year = 2023 - 1900;
    tm_val.tm_mon = 0;
    tm_val.tm_mday = 1;
    tm_val.tm_hour = 0;
    tm_val.tm_min = 0;
    tm_val.tm_sec = 0;
    tm_val.tm_isdst = -1;
    time_t t = mktime(&tm_val);
    ASSERT_NE(t, (time_t)-1);

    auto result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    std::string str = result->c_str();
    EXPECT_EQ(str.substr(10, 2), "00");
    EXPECT_EQ(str.substr(12, 2), "00");
    EXPECT_EQ(str.substr(14, 2), "00");
}

// Test that the result is a unique_ptr (ownership semantics)
TEST_F(DateInfoTest_1993, ReturnsUniquePtr_1993) {
    time_t t = time(nullptr);
    std::unique_ptr<GooString> result = timeToDateString(&t);
    ASSERT_NE(result, nullptr);
    // Ensure we can move it
    std::unique_ptr<GooString> moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    EXPECT_NE(moved, nullptr);
}
