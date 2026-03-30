// TEST: ./TestProjects/poppler/glib/poppler-document-date-time-to-pdf-date-test.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <memory>
#include <string>

#include "goo/GooString.h"

// Function under test (implemented in poppler-document.cc).
std::unique_ptr<GooString> _poppler_convert_date_time_to_pdf_date(GDateTime *datetime);

namespace {

class ConvertDateTimeToPdfDateTest_2264 : public ::testing::Test {
protected:
  static GTimeZone *NewOffsetTzSeconds(int offset_seconds) {
    // g_time_zone_new_offset takes seconds east of UTC (can be negative).
    return g_time_zone_new_offset(offset_seconds);
  }

  static GDateTime *NewDateTime(GTimeZone *tz, int year, int month, int day, int hour, int minute,
                               double seconds) {
    return g_date_time_new(tz, year, month, day, hour, minute, seconds);
  }
};

TEST_F(ConvertDateTimeToPdfDateTest_2264, UtcOffsetZero_AppendsZ_2264) {
  GTimeZone *tz = NewOffsetTzSeconds(0);
  ASSERT_NE(tz, nullptr);

  GDateTime *dt = NewDateTime(tz, 2020, 1, 2, 3, 4, 5.0);
  ASSERT_NE(dt, nullptr);

  std::unique_ptr<GooString> out = _poppler_convert_date_time_to_pdf_date(dt);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->toStr(), "D:20200102030405Z");

  g_date_time_unref(dt);
  g_time_zone_unref(tz);
}

TEST_F(ConvertDateTimeToPdfDateTest_2264, PositiveOffsetHours_FormatsPlusHHMM_2264) {
  // +09:00 (KST)
  GTimeZone *tz = NewOffsetTzSeconds(9 * 60 * 60);
  ASSERT_NE(tz, nullptr);

  GDateTime *dt = NewDateTime(tz, 2020, 1, 2, 3, 4, 5.0);
  ASSERT_NE(dt, nullptr);

  std::unique_ptr<GooString> out = _poppler_convert_date_time_to_pdf_date(dt);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->toStr(), "D:20200102030405+09'00'");

  g_date_time_unref(dt);
  g_time_zone_unref(tz);
}

TEST_F(ConvertDateTimeToPdfDateTest_2264, PositiveOffsetWithMinutes_FormatsPlusHHMM_2264) {
  // +05:30
  GTimeZone *tz = NewOffsetTzSeconds(5 * 60 * 60 + 30 * 60);
  ASSERT_NE(tz, nullptr);

  GDateTime *dt = NewDateTime(tz, 2020, 12, 31, 23, 59, 59.0);
  ASSERT_NE(dt, nullptr);

  std::unique_ptr<GooString> out = _poppler_convert_date_time_to_pdf_date(dt);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->toStr(), "D:20201231235959+05'30'");

  g_date_time_unref(dt);
  g_time_zone_unref(tz);
}

TEST_F(ConvertDateTimeToPdfDateTest_2264, NegativeOffsetHours_FormatsMinusHHMM_2264) {
  // -05:00
  GTimeZone *tz = NewOffsetTzSeconds(-(5 * 60 * 60));
  ASSERT_NE(tz, nullptr);

  GDateTime *dt = NewDateTime(tz, 2021, 6, 7, 8, 9, 10.0);
  ASSERT_NE(dt, nullptr);

  std::unique_ptr<GooString> out = _poppler_convert_date_time_to_pdf_date(dt);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->toStr(), "D:20210607080910-05'00'");

  g_date_time_unref(dt);
  g_time_zone_unref(tz);
}

TEST_F(ConvertDateTimeToPdfDateTest_2264, Boundary_SecondsZero_StillFormatsFullTimestamp_2264) {
  GTimeZone *tz = NewOffsetTzSeconds(0);
  ASSERT_NE(tz, nullptr);

  GDateTime *dt = NewDateTime(tz, 1999, 12, 31, 0, 0, 0.0);
  ASSERT_NE(dt, nullptr);

  std::unique_ptr<GooString> out = _poppler_convert_date_time_to_pdf_date(dt);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->toStr(), "D:19991231000000Z");

  g_date_time_unref(dt);
  g_time_zone_unref(tz);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ConvertDateTimeToPdfDateTest_2264, Error_NullDateTime_Death_2264) {
  // Observable error case: function dereferences the pointer via GLib calls.
  EXPECT_DEATH(
      {
        (void)_poppler_convert_date_time_to_pdf_date(nullptr);
      },
      "");
}
#endif

} // namespace