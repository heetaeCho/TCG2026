// TEST_ID: 2263
// Unit tests for _poppler_convert_pdf_date_to_date_time()
// File: poppler-convert-pdf-date-to-date-time-test-2263.cc

#include <gtest/gtest.h>

#include <glib.h>

#include "goo/GooString.h"

// Function under test (defined in ./glib/poppler-document.cc)
GDateTime *_poppler_convert_pdf_date_to_date_time(const GooString *date);

namespace {

class PopplerConvertPdfDateToDateTimeTest_2263 : public ::testing::Test {
protected:
  static void AssertDateTimeFields(GDateTime *dt,
                                  int year,
                                  int month,
                                  int day,
                                  int hour,
                                  int minute,
                                  int second) {
    ASSERT_NE(dt, nullptr);
    EXPECT_EQ(g_date_time_get_year(dt), year);
    EXPECT_EQ(g_date_time_get_month(dt), month);
    EXPECT_EQ(g_date_time_get_day_of_month(dt), day);
    EXPECT_EQ(g_date_time_get_hour(dt), hour);
    EXPECT_EQ(g_date_time_get_minute(dt), minute);
    EXPECT_EQ(g_date_time_get_second(dt), second);
  }

  static void AssertUtcOffsetSeconds(GDateTime *dt, gint64 expected_seconds) {
    ASSERT_NE(dt, nullptr);
    // g_date_time_get_utc_offset returns microseconds.
    const gint64 offset_us = g_date_time_get_utc_offset(dt);
    EXPECT_EQ(offset_us, expected_seconds * G_TIME_SPAN_SECOND);
  }
};

TEST_F(PopplerConvertPdfDateToDateTimeTest_2263, ReturnsNullptrForInvalidString_2263) {
  GooString invalid("not-a-pdf-date");
  GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&invalid);
  EXPECT_EQ(dt, nullptr);
}

TEST_F(PopplerConvertPdfDateToDateTimeTest_2263, ParsesUtcWithZSuffix_2263) {
  // Common PDF date form: D:YYYYMMDDHHmmSSZ
  GooString s("D:20240102123456Z");
  GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&s);

  AssertDateTimeFields(dt, 2024, 1, 2, 12, 34, 56);
  AssertUtcOffsetSeconds(dt, 0);

  if (dt) {
    g_date_time_unref(dt);
  }
}

TEST_F(PopplerConvertPdfDateToDateTimeTest_2263, ParsesUtcWhenTimezoneIsOmitted_2263) {
  // Some producers omit tz info; implementation falls back to UTC if tz is '\0'.
  GooString s("D:20240102123456");
  GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&s);

  AssertDateTimeFields(dt, 2024, 1, 2, 12, 34, 56);
  AssertUtcOffsetSeconds(dt, 0);

  if (dt) {
    g_date_time_unref(dt);
  }
}

TEST_F(PopplerConvertPdfDateToDateTimeTest_2263, ParsesPositiveTimezoneOffset_2263) {
  // PDF date with offset: D:YYYYMMDDHHmmSS+HH'mm'
  GooString s("D:20240102123456+09'00'");
  GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&s);

  AssertDateTimeFields(dt, 2024, 1, 2, 12, 34, 56);
  AssertUtcOffsetSeconds(dt, 9 * 3600);

  if (dt) {
    g_date_time_unref(dt);
  }
}

TEST_F(PopplerConvertPdfDateToDateTimeTest_2263, ParsesNegativeTimezoneOffset_2263) {
  // PDF date with negative offset: D:YYYYMMDDHHmmSS-HH'mm'
  GooString s("D:20240102123456-08'30'");
  GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&s);

  AssertDateTimeFields(dt, 2024, 1, 2, 12, 34, 56);
  AssertUtcOffsetSeconds(dt, -(8 * 3600 + 30 * 60));

  if (dt) {
    g_date_time_unref(dt);
  }
}

TEST_F(PopplerConvertPdfDateToDateTimeTest_2263, BoundarySecondsAtStartOfDay_2263) {
  GooString s("D:20240229000000Z"); // leap day boundary (valid date)
  GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&s);

  AssertDateTimeFields(dt, 2024, 2, 29, 0, 0, 0);
  AssertUtcOffsetSeconds(dt, 0);

  if (dt) {
    g_date_time_unref(dt);
  }
}

TEST_F(PopplerConvertPdfDateToDateTimeTest_2263, BoundarySecondsAtEndOfDay_2263) {
  GooString s("D:20240101235959Z");
  GDateTime *dt = _poppler_convert_pdf_date_to_date_time(&s);

  AssertDateTimeFields(dt, 2024, 1, 1, 23, 59, 59);
  AssertUtcOffsetSeconds(dt, 0);

  if (dt) {
    g_date_time_unref(dt);
  }
}

} // namespace