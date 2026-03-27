#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/qt5/src/poppler-document.cc"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



// Test Fixture for QDateTime conversion tests

class DateTimeConversionTest_1358 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



// Normal operation test cases

TEST_F(DateTimeConversionTest_1358, ConvertValidDateWithTimezoneZ_1358) {

    const char *dateString = "D:20231010143000Z";

    QDateTime expectedDateTime(QDate(2023, 10, 10), QTime(14, 30, 0), Qt::UTC);

    EXPECT_EQ(convertDate(dateString), expectedDateTime);

}



TEST_F(DateTimeConversionTest_1358, ConvertValidDateWithPositiveTimezone_1358) {

    const char *dateString = "D:20231010143000+02'00'";

    QDateTime expectedDateTime(QDate(2023, 10, 10), QTime(14, 30, 0), QTimeZone(7200));

    EXPECT_EQ(convertDate(dateString), expectedDateTime);

}



TEST_F(DateTimeConversionTest_1358, ConvertValidDateWithNegativeTimezone_1358) {

    const char *dateString = "D:20231010143000-03'00'";

    QDateTime expectedDateTime(QDate(2023, 10, 10), QTime(14, 30, 0), QTimeZone(-10800));

    EXPECT_EQ(convertDate(dateString), expectedDateTime);

}



// Boundary conditions test cases

TEST_F(DateTimeConversionTest_1358, ConvertMinBoundaryDate_1358) {

    const char *dateString = "D:00000101000000Z";

    QDateTime expectedDateTime(QDate(2000, 1, 1), QTime(0, 0, 0), Qt::UTC); // Invalid date in Qt

    EXPECT_FALSE(convertDate(dateString).isValid());

}



TEST_F(DateTimeConversionTest_1358, ConvertMaxBoundaryDate_1358) {

    const char *dateString = "D:99991231235959Z";

    QDateTime expectedDateTime(QDate(9999, 12, 31), QTime(23, 59, 59), Qt::UTC);

    EXPECT_EQ(convertDate(dateString), expectedDateTime);

}



// Exceptional or error cases test cases

TEST_F(DateTimeConversionTest_1358, ConvertInvalidDateStringFormat_1358) {

    const char *dateString = "D:2023-10-10T14:30:00Z";

    QDateTime expectedDateTime; // Invalid date

    EXPECT_FALSE(convertDate(dateString).isValid());

}



TEST_F(DateTimeConversionTest_1358, ConvertInvalidTimezoneCharacter_1358) {

    const char *dateString = "D:20231010143000X";

    QDateTime expectedDateTime; // Invalid date

    EXPECT_FALSE(convertDate(dateString).isValid());

}



TEST_F(DateTimeConversionTest_1358, ConvertEmptyDateString_1358) {

    const char *dateString = "";

    QDateTime expectedDateTime; // Invalid date

    EXPECT_FALSE(convertDate(dateString).isValid());

}



TEST_F(DateTimeConversionTest_1358, ConvertNullDateString_1358) {

    const char *dateString = nullptr;

    QDateTime expectedDateTime; // Invalid date

    EXPECT_FALSE(convertDate(dateString).isValid());

}
