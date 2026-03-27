// SPDX-License-Identifier: GPL-2.0-or-later
// Single-file unit tests for Exiv2::exifTime (types.cpp)
//
// Constraints honored:
// - Treat implementation as black-box: only verify observable effects (return value + tm fields).
// - No private/internal access.
// - Boundary + error cases included.
// - TEST_ID appended to every test name.

#include <gtest/gtest.h>

#include <ctime>
#include <cstring>

namespace Exiv2 {
int exifTime(const char* buf, tm* tm);
}

namespace {

class ExifTimeTest_1155 : public ::testing::Test {
 protected:
  static tm MakeSentinelTm() {
    tm t{};
    // Use distinctive values to detect changes reliably.
    t.tm_year = 777;
    t.tm_mon = 88;
    t.tm_mday = 99;
    t.tm_hour = 11;
    t.tm_min = 22;
    t.tm_sec = 33;
    t.tm_wday = 4;
    t.tm_yday = 123;
    t.tm_isdst = -1;
    return t;
  }
};

}  // namespace

TEST_F(ExifTimeTest_1155, ParsesValidExifDateTime_1155) {
  tm t = MakeSentinelTm();

  const int rc = Exiv2::exifTime("2010:12:31 23:59:58", &t);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(2010 - 1900, t.tm_year);
  EXPECT_EQ(12 - 1, t.tm_mon);
  EXPECT_EQ(31, t.tm_mday);
  EXPECT_EQ(23, t.tm_hour);
  EXPECT_EQ(59, t.tm_min);
  EXPECT_EQ(58, t.tm_sec);
}

TEST_F(ExifTimeTest_1155, AcceptsSingleDigitFieldsDueToNumericScanning_1155) {
  tm t = MakeSentinelTm();

  // Even though the format string uses %2d, scanf can still parse "1" as 1.
  const int rc = Exiv2::exifTime("2010:1:2 3:4:5", &t);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(2010 - 1900, t.tm_year);
  EXPECT_EQ(1 - 1, t.tm_mon);
  EXPECT_EQ(2, t.tm_mday);
  EXPECT_EQ(3, t.tm_hour);
  EXPECT_EQ(4, t.tm_min);
  EXPECT_EQ(5, t.tm_sec);
}

TEST_F(ExifTimeTest_1155, LeavesOtherTmFieldsUnchangedOnSuccess_1155) {
  tm t = MakeSentinelTm();

  const int old_wday = t.tm_wday;
  const int old_yday = t.tm_yday;
  const int old_isdst = t.tm_isdst;

  const int rc = Exiv2::exifTime("2001:02:03 04:05:06", &t);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(old_wday, t.tm_wday);
  EXPECT_EQ(old_yday, t.tm_yday);
  EXPECT_EQ(old_isdst, t.tm_isdst);
}

TEST_F(ExifTimeTest_1155, ReturnsErrorAndDoesNotModifyTmOnNonMatchingFormat_1155) {
  tm t = MakeSentinelTm();
  const tm before = t;

  // Wrong separators/order.
  const int rc = Exiv2::exifTime("2010-12-31 23:59:58", &t);

  EXPECT_NE(0, rc);
  EXPECT_EQ(before.tm_year, t.tm_year);
  EXPECT_EQ(before.tm_mon, t.tm_mon);
  EXPECT_EQ(before.tm_mday, t.tm_mday);
  EXPECT_EQ(before.tm_hour, t.tm_hour);
  EXPECT_EQ(before.tm_min, t.tm_min);
  EXPECT_EQ(before.tm_sec, t.tm_sec);
  EXPECT_EQ(before.tm_wday, t.tm_wday);
  EXPECT_EQ(before.tm_yday, t.tm_yday);
  EXPECT_EQ(before.tm_isdst, t.tm_isdst);
}

TEST_F(ExifTimeTest_1155, ReturnsErrorAndDoesNotModifyTmOnMissingFields_1155) {
  tm t = MakeSentinelTm();
  const tm before = t;

  // Missing seconds.
  const int rc = Exiv2::exifTime("2010:12:31 23:59", &t);

  EXPECT_NE(0, rc);
  EXPECT_EQ(0, std::memcmp(&before, &t, sizeof(tm)));
}

TEST_F(ExifTimeTest_1155, ReturnsErrorAndDoesNotModifyTmOnTrailingGarbage_1155) {
  tm t = MakeSentinelTm();
  const tm before = t;

  // If parsing doesn't match exactly 6 conversions, function should fail.
  const int rc = Exiv2::exifTime("2010:12:31 23:59:58 extra", &t);

  EXPECT_NE(0, rc);
  EXPECT_EQ(0, std::memcmp(&before, &t, sizeof(tm)));
}

TEST_F(ExifTimeTest_1155, ParsesBoundaryLikeZerosAndLargeValuesWithoutValidation_1155) {
  tm t = MakeSentinelTm();

  // Interface-level behavior: success is determined by parse match, not by calendar validity.
  const int rc = Exiv2::exifTime("0000:00:00 00:00:00", &t);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(0 - 1900, t.tm_year);
  EXPECT_EQ(0 - 1, t.tm_mon);
  EXPECT_EQ(0, t.tm_mday);
  EXPECT_EQ(0, t.tm_hour);
  EXPECT_EQ(0, t.tm_min);
  EXPECT_EQ(0, t.tm_sec);
}

TEST_F(ExifTimeTest_1155, ParsesLeapDayLikeInput_1155) {
  tm t = MakeSentinelTm();

  const int rc = Exiv2::exifTime("2012:02:29 00:00:00", &t);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(2012 - 1900, t.tm_year);
  EXPECT_EQ(2 - 1, t.tm_mon);
  EXPECT_EQ(29, t.tm_mday);
  EXPECT_EQ(0, t.tm_hour);
  EXPECT_EQ(0, t.tm_min);
  EXPECT_EQ(0, t.tm_sec);
}

TEST_F(ExifTimeTest_1155, ReturnsErrorAndDoesNotModifyTmOnCompletelyInvalidText_1155) {
  tm t = MakeSentinelTm();
  const tm before = t;

  const int rc = Exiv2::exifTime("not a time", &t);

  EXPECT_NE(0, rc);
  EXPECT_EQ(0, std::memcmp(&before, &t, sizeof(tm)));
}