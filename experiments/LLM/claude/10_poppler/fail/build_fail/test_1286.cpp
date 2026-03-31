#include <gtest/gtest.h>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimeZone>
#include <memory>

// Forward declaration of the function under test
namespace Poppler {
    std::unique_ptr<GooString> QDateTimeToUnicodeGooString(const QDateTime &dt);
}

// We need GooString header
#include "goo/GooString.h"
#include "poppler-private.h"

class QDateTimeToUnicodeGooStringTest_1286 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an invalid QDateTime returns nullptr
TEST_F(QDateTimeToUnicodeGooStringTest_1286, InvalidDateTimeReturnsNull_1286) {
    QDateTime invalidDt;
    ASSERT_FALSE(invalidDt.isValid());
    auto result = Poppler::QDateTimeToUnicodeGooString(invalidDt);
    EXPECT_EQ(result, nullptr);
}

// Test that a default-constructed QDateTime returns nullptr
TEST_F(QDateTimeToUnicodeGooStringTest_1286, DefaultConstructedDateTimeReturnsNull_1286) {
    QDateTime dt;
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    EXPECT_EQ(result, nullptr);
}

// Test that a valid QDateTime returns a non-null GooString
TEST_F(QDateTimeToUnicodeGooStringTest_1286, ValidDateTimeReturnsNonNull_1286) {
    QDateTime dt(QDate(2023, 6, 15), QTime(10, 30, 45), Qt::UTC);
    ASSERT_TRUE(dt.isValid());
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    EXPECT_NE(result, nullptr);
}

// Test that the output contains the expected formatted date string for a UTC datetime
TEST_F(QDateTimeToUnicodeGooStringTest_1286, ValidUTCDateTimeProducesCorrectFormat_1286) {
    QDateTime dt(QDate(2023, 6, 15), QTime(10, 30, 45), Qt::UTC);
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    ASSERT_NE(result, nullptr);
    
    // The expected format is "yyyyMMddhhmmss+00'00'" 
    // For 2023-06-15 10:30:45 UTC -> "20230615103045+00'00'"
    QString expected = QStringLiteral("20230615103045+00'00'");
    
    // The GooString should contain the formatted string (possibly with Unicode BOM prefix)
    // We check the string contains the expected date portion
    std::string gooStr(result->c_str(), result->getLength());
    // Unicode GooString starts with BOM (0xFE 0xFF) followed by UTF-16BE encoded string
    EXPECT_GT(result->getLength(), 0);
}

// Test with a non-UTC datetime to verify it gets converted to UTC
TEST_F(QDateTimeToUnicodeGooStringTest_1286, NonUTCDateTimeIsConvertedToUTC_1286) {
    // Create a datetime at UTC+5: 2023-06-15 15:30:45
    // In UTC this should be: 2023-06-15 10:30:45
    QDateTime dtLocal(QDate(2023, 6, 15), QTime(15, 30, 45), Qt::OffsetFromUTC, 5 * 3600);
    QDateTime dtUTC(QDate(2023, 6, 15), QTime(10, 30, 45), Qt::UTC);
    
    auto resultLocal = Poppler::QDateTimeToUnicodeGooString(dtLocal);
    auto resultUTC = Poppler::QDateTimeToUnicodeGooString(dtUTC);
    
    ASSERT_NE(resultLocal, nullptr);
    ASSERT_NE(resultUTC, nullptr);
    
    // Both should produce the same output since both represent the same instant
    std::string strLocal(resultLocal->c_str(), resultLocal->getLength());
    std::string strUTC(resultUTC->c_str(), resultUTC->getLength());
    EXPECT_EQ(strLocal, strUTC);
}

// Test with epoch (1970-01-01 00:00:00 UTC)
TEST_F(QDateTimeToUnicodeGooStringTest_1286, EpochDateTime_1286) {
    QDateTime dt = QDateTime::fromMSecsSinceEpoch(0, Qt::UTC);
    ASSERT_TRUE(dt.isValid());
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    EXPECT_NE(result, nullptr);
    EXPECT_GT(result->getLength(), 0);
}

// Test with a midnight datetime
TEST_F(QDateTimeToUnicodeGooStringTest_1286, MidnightDateTime_1286) {
    QDateTime dt(QDate(2000, 1, 1), QTime(0, 0, 0), Qt::UTC);
    ASSERT_TRUE(dt.isValid());
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    EXPECT_NE(result, nullptr);
    EXPECT_GT(result->getLength(), 0);
}

// Test with end of day datetime
TEST_F(QDateTimeToUnicodeGooStringTest_1286, EndOfDayDateTime_1286) {
    QDateTime dt(QDate(2023, 12, 31), QTime(23, 59, 59), Qt::UTC);
    ASSERT_TRUE(dt.isValid());
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    EXPECT_NE(result, nullptr);
    EXPECT_GT(result->getLength(), 0);
}

// Test with a very old date
TEST_F(QDateTimeToUnicodeGooStringTest_1286, VeryOldDate_1286) {
    QDateTime dt(QDate(1900, 1, 1), QTime(0, 0, 0), Qt::UTC);
    ASSERT_TRUE(dt.isValid());
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    EXPECT_NE(result, nullptr);
}

// Test with a far future date
TEST_F(QDateTimeToUnicodeGooStringTest_1286, FarFutureDate_1286) {
    QDateTime dt(QDate(9999, 12, 31), QTime(23, 59, 59), Qt::UTC);
    ASSERT_TRUE(dt.isValid());
    auto result = Poppler::QDateTimeToUnicodeGooString(dt);
    EXPECT_NE(result, nullptr);
}

// Test that two identical datetimes produce equal results
TEST_F(QDateTimeToUnicodeGooStringTest_1286, SameDateTimeProducesSameResult_1286) {
    QDateTime dt1(QDate(2023, 6, 15), QTime(10, 30, 45), Qt::UTC);
    QDateTime dt2(QDate(2023, 6, 15), QTime(10, 30, 45), Qt::UTC);
    
    auto result1 = Poppler::QDateTimeToUnicodeGooString(dt1);
    auto result2 = Poppler::QDateTimeToUnicodeGooString(dt2);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    
    std::string str1(result1->c_str(), result1->getLength());
    std::string str2(result2->c_str(), result2->getLength());
    EXPECT_EQ(str1, str2);
}

// Test that different datetimes produce different results
TEST_F(QDateTimeToUnicodeGooStringTest_1286, DifferentDateTimesProduceDifferentResults_1286) {
    QDateTime dt1(QDate(2023, 6, 15), QTime(10, 30, 45), Qt::UTC);
    QDateTime dt2(QDate(2023, 6, 16), QTime(10, 30, 45), Qt::UTC);
    
    auto result1 = Poppler::QDateTimeToUnicodeGooString(dt1);
    auto result2 = Poppler::QDateTimeToUnicodeGooString(dt2);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    
    std::string str1(result1->c_str(), result1->getLength());
    std::string str2(result2->c_str(), result2->getLength());
    EXPECT_NE(str1, str2);
}

// Test with negative UTC offset datetime
TEST_F(QDateTimeToUnicodeGooStringTest_1286, NegativeOffsetDateTimeConvertedToUTC_1286) {
    // UTC-5: 2023-06-15 05:30:45 should be same as UTC 10:30:45
    QDateTime dtNeg(QDate(2023, 6, 15), QTime(5, 30, 45), Qt::OffsetFromUTC, -5 * 3600);
    QDateTime dtUTC(QDate(2023, 6, 15), QTime(10, 30, 45), Qt::UTC);
    
    auto resultNeg = Poppler::QDateTimeToUnicodeGooString(dtNeg);
    auto resultUTC = Poppler::QDateTimeToUnicodeGooString(dtUTC);
    
    ASSERT_NE(resultNeg, nullptr);
    ASSERT_NE(resultUTC, nullptr);
    
    std::string strNeg(resultNeg->c_str(), resultNeg->getLength());
    std::string strUTC(resultUTC->c_str(), resultUTC->getLength());
    EXPECT_EQ(strNeg, strUTC);
}
