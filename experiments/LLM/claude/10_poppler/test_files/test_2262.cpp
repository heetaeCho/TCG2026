#include <gtest/gtest.h>
#include <glib.h>
#include <time.h>
#include <cstring>
#include "GooString.h"

// Declaration of the function under test
extern "C" {
gboolean _poppler_convert_pdf_date_to_gtime(const GooString *date, time_t *gdate);
}

// If the function isn't declared with C linkage, try this:
// gboolean _poppler_convert_pdf_date_to_gtime(const GooString *date, time_t *gdate);

class PopplerConvertPdfDateToGtimeTest_2262 : public ::testing::Test {
protected:
    time_t gdate;

    void SetUp() override {
        gdate = 0;
    }
};

// Test a well-formed PDF date string: D:YYYYMMDDHHmmSS
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, ValidFullDateString_2262) {
    GooString date("D:20230615120000");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    EXPECT_TRUE(result);
    EXPECT_NE(gdate, 0);
}

// Test a date string with only the year
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, ValidYearOnlyDate_2262) {
    GooString date("D:2023");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    // Whether this succeeds depends on how lenient poppler_date_parse is
    // We just check the function doesn't crash
    (void)result;
}

// Test a date string with year and month
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, ValidYearMonthDate_2262) {
    GooString date("D:202306");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    (void)result;
}

// Test a date string with year, month, and day
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, ValidYearMonthDayDate_2262) {
    GooString date("D:20230615");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    if (result) {
        EXPECT_NE(gdate, 0);
    }
}

// Test an empty date string
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, EmptyDateString_2262) {
    GooString date("");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    EXPECT_FALSE(result);
}

// Test a completely invalid date string
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, InvalidDateString_2262) {
    GooString date("not_a_date");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    EXPECT_FALSE(result);
}

// Test a date string with timezone offset +
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, ValidDateWithPositiveTimezone_2262) {
    GooString date("D:20230615120000+05'30'");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    if (result) {
        EXPECT_NE(gdate, 0);
    }
}

// Test a date string with timezone offset -
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, ValidDateWithNegativeTimezone_2262) {
    GooString date("D:20230615120000-08'00'");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    if (result) {
        EXPECT_NE(gdate, 0);
    }
}

// Test a date string with Z timezone (UTC)
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, ValidDateWithUTCTimezone_2262) {
    GooString date("D:20230615120000Z");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    if (result) {
        EXPECT_NE(gdate, 0);
    }
}

// Test a date string with Unicode BOM (UTF-16BE encoding)
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, UnicodeBOMDateString_2262) {
    // UTF-16BE BOM is 0xFE 0xFF, followed by UTF-16BE encoded "D:20230615120000"
    // "D" = 0x00 0x44, ":" = 0x00 0x3A, "2" = 0x00 0x32, etc.
    const char *ascii_date = "D:20230615120000";
    size_t ascii_len = strlen(ascii_date);
    
    // Build UTF-16BE string with BOM
    std::string utf16be;
    utf16be.push_back((char)0xFE);
    utf16be.push_back((char)0xFF);
    for (size_t i = 0; i < ascii_len; i++) {
        utf16be.push_back('\0');
        utf16be.push_back(ascii_date[i]);
    }
    
    GooString date(utf16be.c_str(), utf16be.size());
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    if (result) {
        EXPECT_NE(gdate, 0);
    }
}

// Test date without the "D:" prefix
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, DateWithoutDPrefix_2262) {
    GooString date("20230615120000");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    // Behavior depends on poppler_date_parse implementation
    (void)result;
}

// Test a date at Unix epoch boundary
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, UnixEpochDate_2262) {
    GooString date("D:19700101000000Z");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    if (result) {
        EXPECT_EQ(gdate, 0);
    }
}

// Test a date far in the past
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, OldDate_2262) {
    GooString date("D:19000101000000Z");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    // May fail since it's before Unix epoch on some systems
    (void)result;
}

// Test a date with only the D: prefix
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, OnlyDPrefixDate_2262) {
    GooString date("D:");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    EXPECT_FALSE(result);
}

// Test a single character date string
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, SingleCharDate_2262) {
    GooString date("D");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    EXPECT_FALSE(result);
}

// Test that two different valid dates produce different time values
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, DifferentDatesProduceDifferentTimes_2262) {
    GooString date1("D:20230615120000Z");
    GooString date2("D:20230616120000Z");
    
    time_t gdate1 = 0, gdate2 = 0;
    gboolean result1 = _poppler_convert_pdf_date_to_gtime(&date1, &gdate1);
    gboolean result2 = _poppler_convert_pdf_date_to_gtime(&date2, &gdate2);
    
    if (result1 && result2) {
        EXPECT_NE(gdate1, gdate2);
        // date2 should be exactly 24 hours (86400 seconds) after date1
        EXPECT_EQ(gdate2 - gdate1, 86400);
    }
}

// Test date string with garbage after valid date
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, DateWithTrailingGarbage_2262) {
    GooString date("D:20230615120000Zgarbage");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    // May or may not parse successfully, just shouldn't crash
    (void)result;
}

// Test Unicode BOM with empty content after BOM
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, UnicodeBOMEmptyContent_2262) {
    std::string utf16be;
    utf16be.push_back((char)0xFE);
    utf16be.push_back((char)0xFF);
    
    GooString date(utf16be.c_str(), utf16be.size());
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    EXPECT_FALSE(result);
}

// Test a well-known specific date and verify the time_t value
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, KnownDateValue_2262) {
    // 2000-01-01 00:00:00 UTC
    GooString date("D:20000101000000Z");
    gboolean result = _poppler_convert_pdf_date_to_gtime(&date, &gdate);
    if (result) {
        // 2000-01-01 00:00:00 UTC = 946684800 seconds since epoch
        EXPECT_EQ(gdate, 946684800);
    }
}
