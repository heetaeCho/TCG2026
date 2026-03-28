#include <gtest/gtest.h>
#include <ctime>
#include <cstring>

// Declaration of the function under test
namespace Exiv2 {
int exifTime(const char* buf, tm* tm);
}

class ExifTimeTest_1155 : public ::testing::Test {
 protected:
  tm result;

  void SetUp() override {
    std::memset(&result, 0, sizeof(result));
  }
};

// Normal operation: valid EXIF date/time string
TEST_F(ExifTimeTest_1155, ValidDateTimeReturnsZero_1155) {
  const char* buf = "2023:06:15 10:30:45";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
}

TEST_F(ExifTimeTest_1155, ValidDateTimeParsesYear_1155) {
  const char* buf = "2023:06:15 10:30:45";
  Exiv2::exifTime(buf, &result);
  EXPECT_EQ(result.tm_year, 2023 - 1900);
}

TEST_F(ExifTimeTest_1155, ValidDateTimeParsesMonth_1155) {
  const char* buf = "2023:06:15 10:30:45";
  Exiv2::exifTime(buf, &result);
  EXPECT_EQ(result.tm_mon, 6 - 1);
}

TEST_F(ExifTimeTest_1155, ValidDateTimeParsesDay_1155) {
  const char* buf = "2023:06:15 10:30:45";
  Exiv2::exifTime(buf, &result);
  EXPECT_EQ(result.tm_mday, 15);
}

TEST_F(ExifTimeTest_1155, ValidDateTimeParsesHour_1155) {
  const char* buf = "2023:06:15 10:30:45";
  Exiv2::exifTime(buf, &result);
  EXPECT_EQ(result.tm_hour, 10);
}

TEST_F(ExifTimeTest_1155, ValidDateTimeParsesMinute_1155) {
  const char* buf = "2023:06:15 10:30:45";
  Exiv2::exifTime(buf, &result);
  EXPECT_EQ(result.tm_min, 30);
}

TEST_F(ExifTimeTest_1155, ValidDateTimeParsesSecond_1155) {
  const char* buf = "2023:06:15 10:30:45";
  Exiv2::exifTime(buf, &result);
  EXPECT_EQ(result.tm_sec, 45);
}

// Boundary: midnight time
TEST_F(ExifTimeTest_1155, MidnightTime_1155) {
  const char* buf = "2000:01:01 00:00:00";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_year, 100);
  EXPECT_EQ(result.tm_mon, 0);
  EXPECT_EQ(result.tm_mday, 1);
  EXPECT_EQ(result.tm_hour, 0);
  EXPECT_EQ(result.tm_min, 0);
  EXPECT_EQ(result.tm_sec, 0);
}

// Boundary: end of day
TEST_F(ExifTimeTest_1155, EndOfDayTime_1155) {
  const char* buf = "2023:12:31 23:59:59";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_year, 2023 - 1900);
  EXPECT_EQ(result.tm_mon, 11);
  EXPECT_EQ(result.tm_mday, 31);
  EXPECT_EQ(result.tm_hour, 23);
  EXPECT_EQ(result.tm_min, 59);
  EXPECT_EQ(result.tm_sec, 59);
}

// Boundary: year 1900 (tm_year should be 0)
TEST_F(ExifTimeTest_1155, Year1900_1155) {
  const char* buf = "1900:01:01 00:00:00";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_year, 0);
}

// Error: empty string
TEST_F(ExifTimeTest_1155, EmptyStringReturnsOne_1155) {
  const char* buf = "";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
}

// Error: incomplete date
TEST_F(ExifTimeTest_1155, IncompleteDateReturnsOne_1155) {
  const char* buf = "2023:06:15";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
}

// Error: only date and partial time
TEST_F(ExifTimeTest_1155, PartialTimeReturnsOne_1155) {
  const char* buf = "2023:06:15 10:30";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
}

// Error: completely invalid string
TEST_F(ExifTimeTest_1155, GarbageStringReturnsOne_1155) {
  const char* buf = "not a date at all";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
}

// Error: wrong separator (dashes instead of colons)
TEST_F(ExifTimeTest_1155, WrongDateSeparatorReturnsOne_1155) {
  const char* buf = "2023-06-15 10:30:45";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
}

// Error: missing time separator (no space between date and time)
TEST_F(ExifTimeTest_1155, MissingSpaceSeparatorReturnsOne_1155) {
  const char* buf = "2023:06:1510:30:45";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
}

// Error: only year
TEST_F(ExifTimeTest_1155, OnlyYearReturnsOne_1155) {
  const char* buf = "2023";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
}

// Normal: single digit month/day/time values with leading zeros
TEST_F(ExifTimeTest_1155, SingleDigitValuesWithLeadingZeros_1155) {
  const char* buf = "2023:01:05 03:07:09";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_year, 2023 - 1900);
  EXPECT_EQ(result.tm_mon, 0);
  EXPECT_EQ(result.tm_mday, 5);
  EXPECT_EQ(result.tm_hour, 3);
  EXPECT_EQ(result.tm_min, 7);
  EXPECT_EQ(result.tm_sec, 9);
}

// Boundary: year 0000
TEST_F(ExifTimeTest_1155, YearZero_1155) {
  const char* buf = "0000:01:01 00:00:00";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_year, 0 - 1900);
}

// Verify tm struct is not modified on failure
TEST_F(ExifTimeTest_1155, TmNotModifiedOnFailure_1155) {
  result.tm_year = 999;
  result.tm_mon = 999;
  result.tm_mday = 999;
  result.tm_hour = 999;
  result.tm_min = 999;
  result.tm_sec = 999;

  const char* buf = "invalid";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 1);
  EXPECT_EQ(result.tm_year, 999);
  EXPECT_EQ(result.tm_mon, 999);
  EXPECT_EQ(result.tm_mday, 999);
  EXPECT_EQ(result.tm_hour, 999);
  EXPECT_EQ(result.tm_min, 999);
  EXPECT_EQ(result.tm_sec, 999);
}

// Normal: February 29 in a leap year
TEST_F(ExifTimeTest_1155, LeapYearDate_1155) {
  const char* buf = "2024:02:29 12:00:00";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_year, 2024 - 1900);
  EXPECT_EQ(result.tm_mon, 1);
  EXPECT_EQ(result.tm_mday, 29);
}

// Note: exifTime does not validate date ranges, so out-of-range values
// should still parse successfully as it only uses sscanf pattern matching
TEST_F(ExifTimeTest_1155, OutOfRangeMonthStillParses_1155) {
  const char* buf = "2023:13:01 00:00:00";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_mon, 12);  // 13 - 1
}

TEST_F(ExifTimeTest_1155, OutOfRangeHourStillParses_1155) {
  const char* buf = "2023:01:01 25:00:00";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_hour, 25);
}

// Extra characters after valid input should still parse (sscanf behavior)
TEST_F(ExifTimeTest_1155, ExtraCharsAfterValidInput_1155) {
  const char* buf = "2023:06:15 10:30:45 extra data";
  int rc = Exiv2::exifTime(buf, &result);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(result.tm_year, 2023 - 1900);
  EXPECT_EQ(result.tm_sec, 45);
}
