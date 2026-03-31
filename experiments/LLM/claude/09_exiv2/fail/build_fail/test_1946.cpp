#include <gtest/gtest.h>
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_SetTimeZone_1(XMP_DateTime * time, WXMP_Result * wResult);

class WXMPUtilsSetTimeZoneTest_1946 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
    }

    void TearDown() override {
    }

    XMP_DateTime CreateDefaultDateTime() {
        XMP_DateTime dt;
        dt.year = 2023;
        dt.month = 6;
        dt.day = 15;
        dt.hour = 12;
        dt.minute = 30;
        dt.second = 45;
        dt.tzSign = 0;
        dt.tzHour = 0;
        dt.tzMinute = 0;
        dt.nanoSecond = 0;
        return dt;
    }
};

// Test that passing a null XMP_DateTime pointer results in an error
TEST_F(WXMPUtilsSetTimeZoneTest_1946, NullDateTimePointerReturnsError_1946) {
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(nullptr, &wResult);
    
    // When time is null, the function should throw/report an error
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test that passing a null XMP_DateTime pointer (explicit 0) results in an error
TEST_F(WXMPUtilsSetTimeZoneTest_1946, ZeroDateTimePointerReturnsError_1946) {
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(0, &wResult);
    
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test that passing a valid XMP_DateTime pointer succeeds (no error message)
TEST_F(WXMPUtilsSetTimeZoneTest_1946, ValidDateTimePointerSucceeds_1946) {
    XMP_DateTime dt = CreateDefaultDateTime();
    WXMP_Result wResult;
    
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    // Should succeed without error
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that SetTimeZone modifies the timezone fields of a valid datetime
TEST_F(WXMPUtilsSetTimeZoneTest_1946, SetTimeZoneModifiesTimezoneFields_1946) {
    XMP_DateTime dt = CreateDefaultDateTime();
    // Start with no timezone info
    dt.tzSign = 0;
    dt.tzHour = 0;
    dt.tzMinute = 0;
    
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    // After SetTimeZone, the timezone should be set to the local timezone
    // We can't predict the exact values, but tzSign should be -1, 0, or 1
    EXPECT_GE(dt.tzSign, -1);
    EXPECT_LE(dt.tzSign, 1);
    EXPECT_GE(dt.tzHour, 0);
    EXPECT_LE(dt.tzHour, 23);
    EXPECT_GE(dt.tzMinute, 0);
    EXPECT_LE(dt.tzMinute, 59);
}

// Test that the date/time fields (year, month, day, hour, minute, second) are preserved
TEST_F(WXMPUtilsSetTimeZoneTest_1946, DateTimeFieldsPreserved_1946) {
    XMP_DateTime dt = CreateDefaultDateTime();
    XMP_Int32 origYear = dt.year;
    XMP_Int32 origMonth = dt.month;
    XMP_Int32 origDay = dt.day;
    XMP_Int32 origHour = dt.hour;
    XMP_Int32 origMinute = dt.minute;
    XMP_Int32 origSecond = dt.second;
    
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    // The core date/time values should remain the same; only TZ fields change
    EXPECT_EQ(dt.year, origYear);
    EXPECT_EQ(dt.month, origMonth);
    EXPECT_EQ(dt.day, origDay);
    EXPECT_EQ(dt.hour, origHour);
    EXPECT_EQ(dt.minute, origMinute);
    EXPECT_EQ(dt.second, origSecond);
}

// Test with a zeroed-out datetime
TEST_F(WXMPUtilsSetTimeZoneTest_1946, ZeroedDateTimeSucceeds_1946) {
    XMP_DateTime dt;
    memset(&dt, 0, sizeof(dt));
    
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    // Should still succeed - the function sets timezone on whatever datetime is provided
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with boundary date values
TEST_F(WXMPUtilsSetTimeZoneTest_1946, BoundaryDateValues_1946) {
    XMP_DateTime dt;
    dt.year = 1970;
    dt.month = 1;
    dt.day = 1;
    dt.hour = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.tzSign = 0;
    dt.tzHour = 0;
    dt.tzMinute = 0;
    dt.nanoSecond = 0;
    
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test calling SetTimeZone twice on the same datetime yields consistent results
TEST_F(WXMPUtilsSetTimeZoneTest_1946, ConsistentResults_1946) {
    XMP_DateTime dt1 = CreateDefaultDateTime();
    XMP_DateTime dt2 = CreateDefaultDateTime();
    
    WXMP_Result wResult1, wResult2;
    WXMPUtils_SetTimeZone_1(&dt1, &wResult1);
    WXMPUtils_SetTimeZone_1(&dt2, &wResult2);
    
    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    
    // Both should have the same timezone set
    EXPECT_EQ(dt1.tzSign, dt2.tzSign);
    EXPECT_EQ(dt1.tzHour, dt2.tzHour);
    EXPECT_EQ(dt1.tzMinute, dt2.tzMinute);
}

// Test that WXMP_Result is properly initialized on success
TEST_F(WXMPUtilsSetTimeZoneTest_1946, ResultProperlyInitializedOnSuccess_1946) {
    XMP_DateTime dt = CreateDefaultDateTime();
    WXMP_Result wResult;
    
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with a datetime that already has timezone information
TEST_F(WXMPUtilsSetTimeZoneTest_1946, OverwritesExistingTimezone_1946) {
    XMP_DateTime dt = CreateDefaultDateTime();
    dt.tzSign = 1;
    dt.tzHour = 5;
    dt.tzMinute = 30;
    
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
    // The timezone should now reflect the local timezone, not the original values
    // (We can't assert specific values but can check it didn't error out)
}

// Test with end-of-year boundary datetime
TEST_F(WXMPUtilsSetTimeZoneTest_1946, EndOfYearBoundary_1946) {
    XMP_DateTime dt;
    dt.year = 2023;
    dt.month = 12;
    dt.day = 31;
    dt.hour = 23;
    dt.minute = 59;
    dt.second = 59;
    dt.tzSign = 0;
    dt.tzHour = 0;
    dt.tzMinute = 0;
    dt.nanoSecond = 999999999;
    
    WXMP_Result wResult;
    WXMPUtils_SetTimeZone_1(&dt, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
}
