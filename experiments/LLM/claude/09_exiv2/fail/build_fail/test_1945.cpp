#include <gtest/gtest.h>
#include <ctime>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_CurrentDateTime_1(XMP_DateTime * time, WXMP_Result * wResult);

class WXMPUtilsCurrentDateTimeTest_1945 : public ::testing::Test {
protected:
    void SetUp() override {
        // Nothing special needed
    }

    void TearDown() override {
        // Nothing special needed
    }
};

// Test normal operation: passing a valid XMP_DateTime pointer and valid WXMP_Result
TEST_F(WXMPUtilsCurrentDateTimeTest_1945, NormalOperation_ValidPointers_1945) {
    XMP_DateTime dt;
    memset(&dt, 0, sizeof(dt));
    WXMP_Result wResult;

    WXMPUtils_CurrentDateTime_1(&dt, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);

    // The year should be reasonable (current year or close to it)
    time_t now = time(nullptr);
    struct tm* localTime = localtime(&now);
    int currentYear = localTime->tm_year + 1900;

    EXPECT_GE(dt.year, currentYear - 1);
    EXPECT_LE(dt.year, currentYear + 1);

    // Month should be between 1 and 12
    EXPECT_GE(dt.month, 1);
    EXPECT_LE(dt.month, 12);

    // Day should be between 1 and 31
    EXPECT_GE(dt.day, 1);
    EXPECT_LE(dt.day, 31);

    // Hour should be between 0 and 23
    EXPECT_GE(dt.hour, 0);
    EXPECT_LE(dt.hour, 23);

    // Minute should be between 0 and 59
    EXPECT_GE(dt.minute, 0);
    EXPECT_LE(dt.minute, 59);

    // Second should be between 0 and 60 (60 for leap second)
    EXPECT_GE(dt.second, 0);
    EXPECT_LE(dt.second, 60);
}

// Test error case: passing a null XMP_DateTime pointer should result in error
TEST_F(WXMPUtilsCurrentDateTimeTest_1945, NullDateTimePointer_SetsError_1945) {
    WXMP_Result wResult;

    WXMPUtils_CurrentDateTime_1(nullptr, &wResult);

    // Should have an error message set
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test that calling the function twice in quick succession gives reasonable results
TEST_F(WXMPUtilsCurrentDateTimeTest_1945, ConsecutiveCalls_ReasonableResults_1945) {
    XMP_DateTime dt1, dt2;
    memset(&dt1, 0, sizeof(dt1));
    memset(&dt2, 0, sizeof(dt2));
    WXMP_Result wResult1, wResult2;

    WXMPUtils_CurrentDateTime_1(&dt1, &wResult1);
    WXMPUtils_CurrentDateTime_1(&dt2, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);

    // Both should have the same year (unless called right at year boundary, extremely unlikely)
    EXPECT_EQ(dt1.year, dt2.year);

    // Both should have the same month (unless called right at month boundary)
    EXPECT_EQ(dt1.month, dt2.month);

    // Both should have the same day (unless called right at day boundary)
    EXPECT_EQ(dt1.day, dt2.day);
}

// Test that timezone fields are set to valid values
TEST_F(WXMPUtilsCurrentDateTimeTest_1945, TimezoneFieldsAreValid_1945) {
    XMP_DateTime dt;
    memset(&dt, 0, sizeof(dt));
    WXMP_Result wResult;

    WXMPUtils_CurrentDateTime_1(&dt, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

    // tzSign should be -1, 0, or 1
    EXPECT_GE(dt.tzSign, -1);
    EXPECT_LE(dt.tzSign, 1);

    // tzHour should be between 0 and 23
    EXPECT_GE(dt.tzHour, 0);
    EXPECT_LE(dt.tzHour, 23);

    // tzMinute should be between 0 and 59
    EXPECT_GE(dt.tzMinute, 0);
    EXPECT_LE(dt.tzMinute, 59);
}

// Test that nanoSecond field is within valid range
TEST_F(WXMPUtilsCurrentDateTimeTest_1945, NanoSecondFieldIsValid_1945) {
    XMP_DateTime dt;
    memset(&dt, 0, sizeof(dt));
    WXMP_Result wResult;

    WXMPUtils_CurrentDateTime_1(&dt, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

    // nanoSecond should be between 0 and 999999999
    EXPECT_GE(dt.nanoSecond, 0);
    EXPECT_LE(dt.nanoSecond, 999999999);
}

// Test that WXMP_Result is properly initialized (no error) on success
TEST_F(WXMPUtilsCurrentDateTimeTest_1945, ResultInitializedOnSuccess_1945) {
    XMP_DateTime dt;
    memset(&dt, 0, sizeof(dt));
    WXMP_Result wResult;

    WXMPUtils_CurrentDateTime_1(&dt, &wResult);

    // errMessage should be null on success
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test boundary: ensure the function populates all fields (not all zero after call)
TEST_F(WXMPUtilsCurrentDateTimeTest_1945, FieldsArePopulated_1945) {
    XMP_DateTime dt;
    memset(&dt, 0, sizeof(dt));
    WXMP_Result wResult;

    WXMPUtils_CurrentDateTime_1(&dt, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

    // At minimum, year, month, and day should be non-zero for any valid current date
    EXPECT_NE(dt.year, 0);
    EXPECT_NE(dt.month, 0);
    EXPECT_NE(dt.day, 0);
}
