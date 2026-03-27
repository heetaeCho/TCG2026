#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QDateTime>

#include <unicodegoostring.h>  // Assuming this is where GooString is defined



namespace Poppler {

    std::unique_ptr<GooString> QDateTimeToUnicodeGooString(const QDateTime &dt);

}



using namespace testing;



class QDateTimeToUnicodeGooStringTest_1286 : public ::testing::Test {};



TEST_F(QDateTimeToUnicodeGooStringTest_1286, ValidDateTime_ReturnsNonNullPtr_1286) {

    QDateTime validDateTime = QDateTime::currentDateTimeUtc();

    std::unique_ptr<GooString> result = Poppler::QDateTimeToUnicodeGooString(validDateTime);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(QDateTimeToUnicodeGooStringTest_1286, ValidDateTime_CorrectFormat_1286) {

    QDateTime validDateTime(QDate(2023, 10, 5), QTime(14, 30, 0));

    std::unique_ptr<GooString> result = Poppler::QDateTimeToUnicodeGooString(validDateTime);

    ASSERT_NE(result.get(), nullptr);

    EXPECT_EQ(std::string(result->getCString()), "20231005143000+00'00'");

}



TEST_F(QDateTimeToUnicodeGooStringTest_1286, InvalidDateTime_ReturnsNullPtr_1286) {

    QDateTime invalidDateTime;

    std::unique_ptr<GooString> result = Poppler::QDateTimeToUnicodeGooString(invalidDateTime);

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(QDateTimeToUnicodeGooStringTest_1286, BoundaryCondition_StartOfDay_ReturnsCorrectFormat_1286) {

    QDateTime startOfDay(QDate(2023, 1, 1), QTime(0, 0, 0));

    std::unique_ptr<GooString> result = Poppler::QDateTimeToUnicodeGooString(startOfDay);

    ASSERT_NE(result.get(), nullptr);

    EXPECT_EQ(std::string(result->getCString()), "20230101000000+00'00'");

}



TEST_F(QDateTimeToUnicodeGooStringTest_1286, BoundaryCondition_EndOfDay_ReturnsCorrectFormat_1286) {

    QDateTime endOfDay(QDate(2023, 12, 31), QTime(23, 59, 59));

    std::unique_ptr<GooString> result = Poppler::QDateTimeToUnicodeGooString(endOfDay);

    ASSERT_NE(result.get(), nullptr);

    EXPECT_EQ(std::string(result->getCString()), "20231231235959+00'00'");

}
