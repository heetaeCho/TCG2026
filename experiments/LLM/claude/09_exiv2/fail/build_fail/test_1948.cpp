#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ConvertToLocalTime_1(XMP_DateTime * time, WXMP_Result * wResult);

class WXMPUtilsConvertToLocalTimeTest_1948 : public ::testing::Test {
protected:
    WXMP_Result wResult;

    void SetUp() override {
        std::memset(&wResult, 0, sizeof(wResult));
    }
};

// Test that passing a null XMP_DateTime pointer results in an error
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, NullTimePointerSetsError_1948) {
    WXMPUtils_ConvertToLocalTime_1(nullptr, &wResult);
    // When time is null, an exception should be thrown and caught,
    // resulting in errMessage being set
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test that passing a valid XMP_DateTime pointer does not produce an error
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, ValidTimePointerNoError_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));
    dt.year = 2023;
    dt.month = 6;
    dt.day = 15;
    dt.hour = 12;
    dt.minute = 0;
    dt.second = 0;
    dt.tzSign = 0;
    dt.tzHour = 0;
    dt.tzMinute = 0;
    dt.nanoSecond = 0;

    WXMPUtils_ConvertToLocalTime_1(&dt, &wResult);
    // A valid pointer should not trigger an error
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that a UTC time (tzSign=0, tzHour=0, tzMinute=0) gets converted
// without error and the result is a valid datetime
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, UTCTimeConvertedSuccessfully_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));
    dt.year = 2023;
    dt.month = 1;
    dt.day = 1;
    dt.hour = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.tzSign = 1;  // positive timezone (UTC)
    dt.tzHour = 0;
    dt.tzMinute = 0;
    dt.nanoSecond = 0;

    WXMPUtils_ConvertToLocalTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // After conversion, the date should still be valid (year should be reasonable)
    EXPECT_GE(dt.year, 2022);
    EXPECT_LE(dt.year, 2024);
}

// Test with a positive timezone offset
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, PositiveTimezoneOffset_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));
    dt.year = 2023;
    dt.month = 7;
    dt.day = 15;
    dt.hour = 10;
    dt.minute = 30;
    dt.second = 45;
    dt.tzSign = 1;
    dt.tzHour = 5;
    dt.tzMinute = 30;
    dt.nanoSecond = 0;

    WXMPUtils_ConvertToLocalTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with a negative timezone offset
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, NegativeTimezoneOffset_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));
    dt.year = 2023;
    dt.month = 12;
    dt.day = 31;
    dt.hour = 23;
    dt.minute = 59;
    dt.second = 59;
    dt.tzSign = -1;
    dt.tzHour = 8;
    dt.tzMinute = 0;
    dt.nanoSecond = 0;

    WXMPUtils_ConvertToLocalTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with zero-initialized datetime
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, ZeroInitializedDateTime_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));

    WXMPUtils_ConvertToLocalTime_1(&dt, &wResult);
    // Should not produce an error for zero-initialized datetime
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that nanosecond field is preserved or handled
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, NanoSecondFieldHandled_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));
    dt.year = 2023;
    dt.month = 6;
    dt.day = 15;
    dt.hour = 12;
    dt.minute = 0;
    dt.second = 0;
    dt.tzSign = 1;
    dt.tzHour = 0;
    dt.tzMinute = 0;
    dt.nanoSecond = 500000000;

    WXMPUtils_ConvertToLocalTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Nanoseconds should be preserved during timezone conversion
    EXPECT_EQ(dt.nanoSecond, 500000000);
}

// Test with boundary date: year boundary
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, YearBoundaryDate_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));
    dt.year = 2023;
    dt.month = 1;
    dt.day = 1;
    dt.hour = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.tzSign = 1;
    dt.tzHour = 5;
    dt.tzMinute = 0;
    dt.nanoSecond = 0;

    WXMPUtils_ConvertToLocalTime_1(&dt, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test WXMP_Result is properly initialized and errMessage remains null on success
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, ResultInitializedProperly_1948) {
    XMP_DateTime dt;
    std::memset(&dt, 0, sizeof(dt));
    dt.year = 2020;
    dt.month = 6;
    dt.day = 15;
    dt.hour = 14;
    dt.minute = 30;
    dt.second = 0;

    WXMP_Result result;
    WXMPUtils_ConvertToLocalTime_1(&dt, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test null time pointer error message content
TEST_F(WXMPUtilsConvertToLocalTimeTest_1948, NullTimePointerErrorMessage_1948) {
    WXMPUtils_ConvertToLocalTime_1(nullptr, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // The error message should contain something meaningful
    std::string errMsg(wResult.errMessage);
    EXPECT_FALSE(errMsg.empty());
}
