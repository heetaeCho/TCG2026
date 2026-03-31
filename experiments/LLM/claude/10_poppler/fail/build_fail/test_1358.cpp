#include <gtest/gtest.h>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimeZone>

// Forward declaration of the function under test
namespace Poppler {
QDateTime convertDate(const char *dateString);
}

class ConvertDateTest_1358 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Valid date string with UTC timezone ('Z')
TEST_F(ConvertDateTest_1358, ValidDateWithUTCTimezone_1358) {
    QDateTime result = Poppler::convertDate("D:20230615120000Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2023, 6, 15));
    EXPECT_EQ(result.time(), QTime(12, 0, 0));
    EXPECT_EQ(result.timeZone().fixedSecondsAheadOfUtc(), 0);
}

// Test: Valid date string with positive timezone offset
TEST_F(ConvertDateTest_1358, ValidDateWithPositiveTimezone_1358) {
    QDateTime result = Poppler::convertDate("D:20230615120000+05'30'");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2023, 6, 15));
    EXPECT_EQ(result.time(), QTime(12, 0, 0));
    EXPECT_EQ(result.timeZone().fixedSecondsAheadOfUtc(), 5 * 3600 + 30 * 60);
}

// Test: Valid date string with negative timezone offset
TEST_F(ConvertDateTest_1358, ValidDateWithNegativeTimezone_1358) {
    QDateTime result = Poppler::convertDate("D:20230615120000-08'00'");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2023, 6, 15));
    EXPECT_EQ(result.time(), QTime(12, 0, 0));
    EXPECT_EQ(result.timeZone().fixedSecondsAheadOfUtc(), -(8 * 3600));
}

// Test: Valid date at the start of the year (boundary)
TEST_F(ConvertDateTest_1358, ValidDateStartOfYear_1358) {
    QDateTime result = Poppler::convertDate("D:20230101000000Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2023, 1, 1));
    EXPECT_EQ(result.time(), QTime(0, 0, 0));
}

// Test: Valid date at end of year (boundary)
TEST_F(ConvertDateTest_1358, ValidDateEndOfYear_1358) {
    QDateTime result = Poppler::convertDate("D:20231231235959Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2023, 12, 31));
    EXPECT_EQ(result.time(), QTime(23, 59, 59));
}

// Test: Invalid date string returns invalid QDateTime
TEST_F(ConvertDateTest_1358, InvalidDateStringReturnsInvalid_1358) {
    QDateTime result = Poppler::convertDate("not_a_date");
    EXPECT_FALSE(result.isValid());
}

// Test: Empty date string returns invalid QDateTime
TEST_F(ConvertDateTest_1358, EmptyDateStringReturnsInvalid_1358) {
    QDateTime result = Poppler::convertDate("");
    EXPECT_FALSE(result.isValid());
}

// Test: Date with only year and month specified
TEST_F(ConvertDateTest_1358, DateWithPartialInfo_1358) {
    QDateTime result = Poppler::convertDate("D:202306");
    // The result depends on parseDateString behavior, but it should either be valid or invalid
    // We just test it doesn't crash
    // If it's valid, check some basic properties
    if (result.isValid()) {
        EXPECT_EQ(result.date().year(), 2023);
        EXPECT_EQ(result.date().month(), 6);
    }
}

// Test: Date with only year specified
TEST_F(ConvertDateTest_1358, DateWithOnlyYear_1358) {
    QDateTime result = Poppler::convertDate("D:2023");
    if (result.isValid()) {
        EXPECT_EQ(result.date().year(), 2023);
    }
}

// Test: Valid date with negative timezone with minutes
TEST_F(ConvertDateTest_1358, NegativeTimezoneWithMinutes_1358) {
    QDateTime result = Poppler::convertDate("D:20200101120000-05'30'");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2020, 1, 1));
    EXPECT_EQ(result.time(), QTime(12, 0, 0));
    int expectedOffset = -(5 * 3600 + 30 * 60);
    EXPECT_EQ(result.timeZone().fixedSecondsAheadOfUtc(), expectedOffset);
}

// Test: Valid date with zero timezone offset (equivalent to UTC)
TEST_F(ConvertDateTest_1358, PositiveZeroOffset_1358) {
    QDateTime result = Poppler::convertDate("D:20230615120000+00'00'");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.timeZone().fixedSecondsAheadOfUtc(), 0);
}

// Test: Leap year date Feb 29
TEST_F(ConvertDateTest_1358, LeapYearDate_1358) {
    QDateTime result = Poppler::convertDate("D:20200229120000Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2020, 2, 29));
    EXPECT_EQ(result.time(), QTime(12, 0, 0));
}

// Test: Non-leap year Feb 29 should return invalid
TEST_F(ConvertDateTest_1358, NonLeapYearFeb29_1358) {
    QDateTime result = Poppler::convertDate("D:20230229120000Z");
    // Feb 29, 2023 is invalid since 2023 is not a leap year
    EXPECT_FALSE(result.isValid());
}

// Test: Invalid month (13) should return invalid
TEST_F(ConvertDateTest_1358, InvalidMonth_1358) {
    QDateTime result = Poppler::convertDate("D:20231315120000Z");
    EXPECT_FALSE(result.isValid());
}

// Test: Invalid day (32) should return invalid
TEST_F(ConvertDateTest_1358, InvalidDay_1358) {
    QDateTime result = Poppler::convertDate("D:20230132120000Z");
    EXPECT_FALSE(result.isValid());
}

// Test: Invalid hour (25) should return invalid
TEST_F(ConvertDateTest_1358, InvalidHour_1358) {
    QDateTime result = Poppler::convertDate("D:20230615250000Z");
    EXPECT_FALSE(result.isValid());
}

// Test: Invalid minute (60) should return invalid
TEST_F(ConvertDateTest_1358, InvalidMinute_1358) {
    QDateTime result = Poppler::convertDate("D:20230615126000Z");
    EXPECT_FALSE(result.isValid());
}

// Test: Date without D: prefix might still be parseable depending on parseDateString
TEST_F(ConvertDateTest_1358, DateWithoutDPrefix_1358) {
    QDateTime result = Poppler::convertDate("20230615120000Z");
    // Just ensure it doesn't crash; validity depends on parseDateString
    // No assertion on validity since behavior is implementation-defined
}

// Test: Year 2000 boundary
TEST_F(ConvertDateTest_1358, Year2000Boundary_1358) {
    QDateTime result = Poppler::convertDate("D:20000101000000Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(2000, 1, 1));
    EXPECT_EQ(result.time(), QTime(0, 0, 0));
}

// Test: Year 1999 boundary
TEST_F(ConvertDateTest_1358, Year1999Boundary_1358) {
    QDateTime result = Poppler::convertDate("D:19991231235959Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.date(), QDate(1999, 12, 31));
    EXPECT_EQ(result.time(), QTime(23, 59, 59));
}

// Test: Large positive timezone offset
TEST_F(ConvertDateTest_1358, LargePositiveTimezoneOffset_1358) {
    QDateTime result = Poppler::convertDate("D:20230615120000+12'00'");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.timeZone().fixedSecondsAheadOfUtc(), 12 * 3600);
}

// Test: Large negative timezone offset
TEST_F(ConvertDateTest_1358, LargeNegativeTimezoneOffset_1358) {
    QDateTime result = Poppler::convertDate("D:20230615120000-12'00'");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.timeZone().fixedSecondsAheadOfUtc(), -(12 * 3600));
}

// Test: Midnight boundary time
TEST_F(ConvertDateTest_1358, MidnightBoundary_1358) {
    QDateTime result = Poppler::convertDate("D:20230615000000Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.time(), QTime(0, 0, 0));
}

// Test: End of day boundary time
TEST_F(ConvertDateTest_1358, EndOfDayBoundary_1358) {
    QDateTime result = Poppler::convertDate("D:20230615235959Z");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.time(), QTime(23, 59, 59));
}
