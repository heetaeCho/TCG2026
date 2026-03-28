#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" void WXMPUtils_ConvertToDate_1(XMP_StringPtr strValue, XMP_DateTime * binValue, WXMP_Result * wResult);

// We also need XMPUtils initialization
#include "XMPUtils.hpp"

class WXMPUtilsConvertToDateTest_1944 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP SDK if needed
        XMPUtils::Initialize();
    }

    static void TearDownTestSuite() {
        XMPUtils::Terminate();
    }

    void SetUp() override {
        memset(&binValue_, 0, sizeof(XMP_DateTime));
        memset(&wResult_, 0, sizeof(WXMP_Result));
    }

    XMP_DateTime binValue_;
    WXMP_Result wResult_;
};

// Test: Normal ISO 8601 date string converts correctly
TEST_F(WXMPUtilsConvertToDateTest_1944, NormalDateConversion_1944) {
    WXMPUtils_ConvertToDate_1("2023-06-15T10:30:00", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 6);
    EXPECT_EQ(binValue_.day, 15);
    EXPECT_EQ(binValue_.hour, 10);
    EXPECT_EQ(binValue_.minute, 30);
    EXPECT_EQ(binValue_.second, 0);
}

// Test: Date with timezone offset
TEST_F(WXMPUtilsConvertToDateTest_1944, DateWithTimezoneOffset_1944) {
    WXMPUtils_ConvertToDate_1("2023-06-15T10:30:00+05:30", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 6);
    EXPECT_EQ(binValue_.day, 15);
    EXPECT_EQ(binValue_.hour, 10);
    EXPECT_EQ(binValue_.minute, 30);
    EXPECT_EQ(binValue_.second, 0);
    EXPECT_EQ(binValue_.tzSign, 1);
    EXPECT_EQ(binValue_.tzHour, 5);
    EXPECT_EQ(binValue_.tzMinute, 30);
}

// Test: Date with UTC timezone (Z suffix)
TEST_F(WXMPUtilsConvertToDateTest_1944, DateWithUTCTimezone_1944) {
    WXMPUtils_ConvertToDate_1("2023-06-15T10:30:00Z", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 6);
    EXPECT_EQ(binValue_.day, 15);
    EXPECT_EQ(binValue_.hour, 10);
    EXPECT_EQ(binValue_.minute, 30);
    EXPECT_EQ(binValue_.second, 0);
    EXPECT_EQ(binValue_.tzSign, 0);
    EXPECT_EQ(binValue_.tzHour, 0);
    EXPECT_EQ(binValue_.tzMinute, 0);
}

// Test: Null binValue pointer should cause an error
TEST_F(WXMPUtilsConvertToDateTest_1944, NullBinValueThrowsError_1944) {
    WXMPUtils_ConvertToDate_1("2023-06-15T10:30:00", nullptr, &wResult_);
    EXPECT_NE(wResult_.errMessage, nullptr);
}

// Test: Date-only string (no time component)
TEST_F(WXMPUtilsConvertToDateTest_1944, DateOnlyString_1944) {
    WXMPUtils_ConvertToDate_1("2023-06-15", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 6);
    EXPECT_EQ(binValue_.day, 15);
}

// Test: Year-only string
TEST_F(WXMPUtilsConvertToDateTest_1944, YearOnlyString_1944) {
    WXMPUtils_ConvertToDate_1("2023", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
}

// Test: Year and month only
TEST_F(WXMPUtilsConvertToDateTest_1944, YearMonthString_1944) {
    WXMPUtils_ConvertToDate_1("2023-06", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 6);
}

// Test: Empty string should result in zeroed date (or handle gracefully)
TEST_F(WXMPUtilsConvertToDateTest_1944, EmptyStringInput_1944) {
    WXMPUtils_ConvertToDate_1("", &binValue_, &wResult_);
    // Empty string should not cause a crash; result may vary
    // At minimum, no crash and errMessage should be null (graceful handling)
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 0);
    EXPECT_EQ(binValue_.month, 0);
    EXPECT_EQ(binValue_.day, 0);
}

// Test: Date with negative timezone offset
TEST_F(WXMPUtilsConvertToDateTest_1944, DateWithNegativeTimezone_1944) {
    WXMPUtils_ConvertToDate_1("2023-12-25T23:59:59-08:00", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 12);
    EXPECT_EQ(binValue_.day, 25);
    EXPECT_EQ(binValue_.hour, 23);
    EXPECT_EQ(binValue_.minute, 59);
    EXPECT_EQ(binValue_.second, 59);
    EXPECT_EQ(binValue_.tzSign, -1);
    EXPECT_EQ(binValue_.tzHour, 8);
    EXPECT_EQ(binValue_.tzMinute, 0);
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPUtilsConvertToDateTest_1944, ResultInitializedProperly_1944) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
    WXMPUtils_ConvertToDate_1("2023-01-01T00:00:00Z", &binValue_, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Boundary - January 1st
TEST_F(WXMPUtilsConvertToDateTest_1944, BoundaryJanFirst_1944) {
    WXMPUtils_ConvertToDate_1("2000-01-01T00:00:00Z", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2000);
    EXPECT_EQ(binValue_.month, 1);
    EXPECT_EQ(binValue_.day, 1);
    EXPECT_EQ(binValue_.hour, 0);
    EXPECT_EQ(binValue_.minute, 0);
    EXPECT_EQ(binValue_.second, 0);
}

// Test: Boundary - December 31st end of day
TEST_F(WXMPUtilsConvertToDateTest_1944, BoundaryDecThirtyFirst_1944) {
    WXMPUtils_ConvertToDate_1("1999-12-31T23:59:59Z", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 1999);
    EXPECT_EQ(binValue_.month, 12);
    EXPECT_EQ(binValue_.day, 31);
    EXPECT_EQ(binValue_.hour, 23);
    EXPECT_EQ(binValue_.minute, 59);
    EXPECT_EQ(binValue_.second, 59);
}

// Test: Full date-time with nanoseconds (if supported)
TEST_F(WXMPUtilsConvertToDateTest_1944, DateTimeWithNanoseconds_1944) {
    WXMPUtils_ConvertToDate_1("2023-06-15T10:30:00.123456789Z", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 6);
    EXPECT_EQ(binValue_.day, 15);
    EXPECT_EQ(binValue_.hour, 10);
    EXPECT_EQ(binValue_.minute, 30);
    EXPECT_EQ(binValue_.second, 0);
    // nanoSecond might be set depending on implementation
    EXPECT_GE(binValue_.nanoSecond, 0);
}

// Test: Null string value should be handled gracefully
TEST_F(WXMPUtilsConvertToDateTest_1944, NullStringValue_1944) {
    // Passing null string - behavior depends on implementation
    // Should either handle gracefully or set error message
    WXMPUtils_ConvertToDate_1(nullptr, &binValue_, &wResult_);
    // We just verify it doesn't crash; error handling is implementation-dependent
}

// Test: Date with only hours and minutes (no seconds)
TEST_F(WXMPUtilsConvertToDateTest_1944, DateTimeNoSeconds_1944) {
    WXMPUtils_ConvertToDate_1("2023-06-15T10:30Z", &binValue_, &wResult_);
    EXPECT_EQ(wResult_.errMessage, nullptr);
    EXPECT_EQ(binValue_.year, 2023);
    EXPECT_EQ(binValue_.month, 6);
    EXPECT_EQ(binValue_.day, 15);
    EXPECT_EQ(binValue_.hour, 10);
    EXPECT_EQ(binValue_.minute, 30);
}
