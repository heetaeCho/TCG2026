#include <gtest/gtest.h>
#include <glib.h>
#include "GooString.h"

// Declaration of the function under test
GDateTime *_poppler_convert_pdf_date_to_date_time(const GooString *date);

class PopplerConvertPdfDateTest_2263 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup is handled per test
    }
};

// Test normal PDF date string with positive timezone
TEST_F(PopplerConvertPdfDateTest_2263, ValidDateWithPositiveTimezone_2263) {
    GooString date("D:20230615120000+05'30");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2023);
    EXPECT_EQ(g_date_time_get_month(dt), 6);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 15);
    EXPECT_EQ(g_date_time_get_hour(dt), 12);
    EXPECT_EQ(g_date_time_get_minute(dt), 0);
    EXPECT_EQ(g_date_time_get_second(dt), 0);
    g_date_time_unref(dt);
}

// Test normal PDF date string with negative timezone
TEST_F(PopplerConvertPdfDateTest_2263, ValidDateWithNegativeTimezone_2263) {
    GooString date("D:20230615120000-05'00");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2023);
    EXPECT_EQ(g_date_time_get_month(dt), 6);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 15);
    EXPECT_EQ(g_date_time_get_hour(dt), 12);
    EXPECT_EQ(g_date_time_get_minute(dt), 0);
    EXPECT_EQ(g_date_time_get_second(dt), 0);
    g_date_time_unref(dt);
}

// Test PDF date string with UTC timezone (Z)
TEST_F(PopplerConvertPdfDateTest_2263, ValidDateWithUTCTimezone_2263) {
    GooString date("D:20230615120000Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2023);
    EXPECT_EQ(g_date_time_get_month(dt), 6);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 15);
    EXPECT_EQ(g_date_time_get_hour(dt), 12);
    EXPECT_EQ(g_date_time_get_minute(dt), 0);
    EXPECT_EQ(g_date_time_get_second(dt), 0);
    g_date_time_unref(dt);
}

// Test PDF date string with no timezone (should default to UTC)
TEST_F(PopplerConvertPdfDateTest_2263, ValidDateWithNoTimezone_2263) {
    GooString date("D:20230615120000");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2023);
    EXPECT_EQ(g_date_time_get_month(dt), 6);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 15);
    g_date_time_unref(dt);
}

// Test with only year
TEST_F(PopplerConvertPdfDateTest_2263, ValidDateYearOnly_2263) {
    GooString date("D:2023");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    // May or may not parse depending on implementation; just check non-crash
    if (dt != nullptr) {
        EXPECT_EQ(g_date_time_get_year(dt), 2023);
        g_date_time_unref(dt);
    }
}

// Test with invalid date string
TEST_F(PopplerConvertPdfDateTest_2263, InvalidDateString_2263) {
    GooString date("not_a_date");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    EXPECT_EQ(dt, nullptr);
}

// Test with empty date string
TEST_F(PopplerConvertPdfDateTest_2263, EmptyDateString_2263) {
    GooString date("");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    EXPECT_EQ(dt, nullptr);
}

// Test with date at boundary: midnight Jan 1
TEST_F(PopplerConvertPdfDateTest_2263, BoundaryDateMidnightJan1_2263) {
    GooString date("D:20000101000000Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2000);
    EXPECT_EQ(g_date_time_get_month(dt), 1);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 1);
    EXPECT_EQ(g_date_time_get_hour(dt), 0);
    EXPECT_EQ(g_date_time_get_minute(dt), 0);
    EXPECT_EQ(g_date_time_get_second(dt), 0);
    g_date_time_unref(dt);
}

// Test with date at boundary: Dec 31 end of day
TEST_F(PopplerConvertPdfDateTest_2263, BoundaryDateDec31EndOfDay_2263) {
    GooString date("D:20231231235959Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2023);
    EXPECT_EQ(g_date_time_get_month(dt), 12);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 31);
    EXPECT_EQ(g_date_time_get_hour(dt), 23);
    EXPECT_EQ(g_date_time_get_minute(dt), 59);
    EXPECT_EQ(g_date_time_get_second(dt), 59);
    g_date_time_unref(dt);
}

// Test with positive timezone offset +00:00 (equivalent to UTC)
TEST_F(PopplerConvertPdfDateTest_2263, PositiveTimezoneZeroOffset_2263) {
    GooString date("D:20230615120000+00'00");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2023);
    EXPECT_EQ(g_date_time_get_hour(dt), 12);
    g_date_time_unref(dt);
}

// Test with negative timezone offset -12:00
TEST_F(PopplerConvertPdfDateTest_2263, NegativeTimezone12Hours_2263) {
    GooString date("D:20230615120000-12'00");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2023);
    g_date_time_unref(dt);
}

// Test PDF date with year and month only
TEST_F(PopplerConvertPdfDateTest_2263, ValidDateYearMonthOnly_2263) {
    GooString date("D:202306");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    if (dt != nullptr) {
        EXPECT_EQ(g_date_time_get_year(dt), 2023);
        EXPECT_EQ(g_date_time_get_month(dt), 6);
        g_date_time_unref(dt);
    }
}

// Test with leap year date
TEST_F(PopplerConvertPdfDateTest_2263, LeapYearDate_2263) {
    GooString date("D:20240229120000Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 2024);
    EXPECT_EQ(g_date_time_get_month(dt), 2);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 29);
    g_date_time_unref(dt);
}

// Test with non-leap year Feb 29 (invalid date)
TEST_F(PopplerConvertPdfDateTest_2263, NonLeapYearFeb29_2263) {
    GooString date("D:20230229120000Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    // g_date_time_new returns NULL for invalid dates
    // This may return nullptr since Feb 29 doesn't exist in 2023
    if (dt != nullptr) {
        g_date_time_unref(dt);
    }
}

// Test with date string without the D: prefix
TEST_F(PopplerConvertPdfDateTest_2263, DateWithoutPrefix_2263) {
    GooString date("20230615120000Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    // parseDateString may or may not handle this
    if (dt != nullptr) {
        g_date_time_unref(dt);
    }
}

// Test timezone offset with positive large values
TEST_F(PopplerConvertPdfDateTest_2263, PositiveTimezone14Hours_2263) {
    GooString date("D:20230615120000+14'00");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    if (dt != nullptr) {
        EXPECT_EQ(g_date_time_get_year(dt), 2023);
        g_date_time_unref(dt);
    }
}

// Test with year 1970 (epoch)
TEST_F(PopplerConvertPdfDateTest_2263, EpochDate_2263) {
    GooString date("D:19700101000000Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), 1970);
    EXPECT_EQ(g_date_time_get_month(dt), 1);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), 1);
    g_date_time_unref(dt);
}

// Test with a very old date
TEST_F(PopplerConvertPdfDateTest_2263, OldDate_2263) {
    GooString date("D:19000101000000Z");
    GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&date);
    if (dt != nullptr) {
        EXPECT_EQ(g_date_time_get_year(dt), 1900);
        g_date_time_unref(dt);
    }
}
