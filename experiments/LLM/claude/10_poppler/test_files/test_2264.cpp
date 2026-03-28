#include <gtest/gtest.h>
#include <glib.h>
#include <memory>
#include <string>

// Forward declarations and includes needed
#include "goo/GooString.h"

// Declaration of the function under test
std::unique_ptr<GooString> _poppler_convert_date_time_to_pdf_date(GDateTime *datetime);

class ConvertDateTimeToPdfDateTest_2264 : public ::testing::Test {
protected:
    void TearDown() override {
        // GDateTime objects are freed in individual tests
    }
};

// Test: UTC datetime should produce a string ending with 'Z'
TEST_F(ConvertDateTimeToPdfDateTest_2264, UtcDateTimeProducesZSuffix_2264) {
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *dt = g_date_time_new(tz, 2023, 6, 15, 10, 30, 45);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20230615103045Z");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Positive offset timezone
TEST_F(ConvertDateTimeToPdfDateTest_2264, PositiveOffsetTimezone_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("+05:30");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2023, 1, 1, 0, 0, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20230101000000+05'30'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Negative offset timezone
TEST_F(ConvertDateTimeToPdfDateTest_2264, NegativeOffsetTimezone_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("-08:00");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2020, 12, 25, 23, 59, 59);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20201225235959-08'00'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Positive whole hour offset
TEST_F(ConvertDateTimeToPdfDateTest_2264, PositiveWholeHourOffset_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("+03:00");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2000, 1, 1, 12, 0, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20000101120000+03'00'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Negative offset with minutes
TEST_F(ConvertDateTimeToPdfDateTest_2264, NegativeOffsetWithMinutes_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("-09:30");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2015, 7, 4, 18, 30, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20150704183000-09'30'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Boundary - start of year
TEST_F(ConvertDateTimeToPdfDateTest_2264, StartOfYear_2264) {
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *dt = g_date_time_new(tz, 2024, 1, 1, 0, 0, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20240101000000Z");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Boundary - end of year
TEST_F(ConvertDateTimeToPdfDateTest_2264, EndOfYear_2264) {
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *dt = g_date_time_new(tz, 2024, 12, 31, 23, 59, 59);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20241231235959Z");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Leap year date
TEST_F(ConvertDateTimeToPdfDateTest_2264, LeapYearDate_2264) {
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *dt = g_date_time_new(tz, 2024, 2, 29, 12, 0, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20240229120000Z");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: String starts with "D:" prefix
TEST_F(ConvertDateTimeToPdfDateTest_2264, StartsWithDPrefix_2264) {
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *dt = g_date_time_new(tz, 2023, 6, 15, 10, 30, 45);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_TRUE(str.substr(0, 2) == "D:");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Offset +01:00
TEST_F(ConvertDateTimeToPdfDateTest_2264, PositiveOneHourOffset_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("+01:00");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2023, 3, 15, 8, 0, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20230315080000+01'00'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Offset +05:45 (Nepal timezone - unusual offset)
TEST_F(ConvertDateTimeToPdfDateTest_2264, UnusualOffsetNepal_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("+05:45");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2023, 8, 20, 14, 15, 30);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20230820141530+05'45'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Result is a unique_ptr (non-null for valid input)
TEST_F(ConvertDateTimeToPdfDateTest_2264, ResultIsNonNull_2264) {
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *dt = g_date_time_new(tz, 2023, 6, 15, 10, 30, 45);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    EXPECT_NE(result, nullptr);
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Offset -12:00 (extreme negative offset)
TEST_F(ConvertDateTimeToPdfDateTest_2264, ExtremeNegativeOffset_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("-12:00");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2023, 6, 1, 0, 0, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20230601000000-12'00'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Offset +14:00 (extreme positive offset, e.g., Line Islands)
TEST_F(ConvertDateTimeToPdfDateTest_2264, ExtremePositiveOffset_2264) {
    GTimeZone *tz = g_time_zone_new_identifier("+14:00");
    ASSERT_NE(tz, nullptr);
    GDateTime *dt = g_date_time_new(tz, 2023, 6, 1, 0, 0, 0);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    EXPECT_EQ(str, "D:20230601000000+14'00'");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

// Test: Single digit month and day are zero-padded
TEST_F(ConvertDateTimeToPdfDateTest_2264, ZeroPaddedMonthAndDay_2264) {
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *dt = g_date_time_new(tz, 2023, 3, 5, 7, 8, 9);
    
    auto result = _poppler_convert_date_time_to_pdf_date(dt);
    
    ASSERT_NE(result, nullptr);
    std::string str = result->toStr();
    // The format string %Y%m%d%H%M%S should zero-pad
    EXPECT_EQ(str, "D:20230305070809Z");
    
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}
