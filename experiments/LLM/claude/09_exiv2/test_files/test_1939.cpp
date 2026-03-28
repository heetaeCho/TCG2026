#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore_Impl.hpp"
#include "XMPUtils.hpp"

// Declaration of the function under test
extern "C" void WXMPUtils_ConvertFromDate_1(
    const XMP_DateTime & binValue,
    XMP_StringPtr * strValue,
    XMP_StringLen * strSize,
    WXMP_Result * wResult);

class WXMPUtilsConvertFromDateTest_1939 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP toolkit is initialized
        XMPUtils::Initialize();
    }

    void TearDown() override {
        // Cleanup if needed
    }

    XMP_DateTime MakeDateTime(XMP_Int32 year, XMP_Int32 month, XMP_Int32 day,
                               XMP_Int32 hour, XMP_Int32 minute, XMP_Int32 second,
                               XMP_Int32 tzSign = 0, XMP_Int32 tzHour = 0,
                               XMP_Int32 tzMinute = 0, XMP_Int32 nanoSecond = 0) {
        XMP_DateTime dt;
        dt.year = year;
        dt.month = month;
        dt.day = day;
        dt.hour = hour;
        dt.minute = minute;
        dt.second = second;
        dt.tzSign = tzSign;
        dt.tzHour = tzHour;
        dt.tzMinute = tzMinute;
        dt.nanoSecond = nanoSecond;
        return dt;
    }
};

// Test normal date conversion with a valid date
TEST_F(WXMPUtilsConvertFromDateTest_1939, NormalDateConversion_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 45, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error for valid date";
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test with UTC timezone (tzSign = 0)
TEST_F(WXMPUtilsConvertFromDateTest_1939, UTCTimezone_1939) {
    XMP_DateTime dt = MakeDateTime(2020, 1, 1, 0, 0, 0, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test with positive timezone offset
TEST_F(WXMPUtilsConvertFromDateTest_1939, PositiveTimezone_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 12, 25, 14, 30, 0, 1, 5, 30);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test with negative timezone offset
TEST_F(WXMPUtilsConvertFromDateTest_1939, NegativeTimezone_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 7, 4, 8, 0, 0, -1, 8, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test passing null strValue pointer - should use voidStringPtr internally
TEST_F(WXMPUtilsConvertFromDateTest_1939, NullStrValuePointer_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 1, 1, 0, 0, 0);
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, nullptr, &strSize, &wResult);

    // Should not crash; the function handles null strValue by substituting voidStringPtr
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test passing null strSize pointer - should use voidStringLen internally
TEST_F(WXMPUtilsConvertFromDateTest_1939, NullStrSizePointer_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 1, 1, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, nullptr, &wResult);

    // Should not crash; the function handles null strSize by substituting voidStringLen
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
}

// Test passing both null strValue and strSize pointers
TEST_F(WXMPUtilsConvertFromDateTest_1939, BothNullOutputPointers_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 1, 12, 0, 0);
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, nullptr, nullptr, &wResult);

    // Should not crash; both are handled by substitution
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with zero/default date
TEST_F(WXMPUtilsConvertFromDateTest_1939, ZeroDate_1939) {
    XMP_DateTime dt = MakeDateTime(0, 0, 0, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    // Zero date should still produce some output or handle gracefully
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with date containing nanoseconds
TEST_F(WXMPUtilsConvertFromDateTest_1939, DateWithNanoseconds_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 3, 14, 15, 9, 26, 0, 0, 0, 535897932);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test with date only (year-month-day, no time components)
TEST_F(WXMPUtilsConvertFromDateTest_1939, DateOnly_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
}

// Test with year only
TEST_F(WXMPUtilsConvertFromDateTest_1939, YearOnly_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 0, 0, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
}

// Test strSize matches string length
TEST_F(WXMPUtilsConvertFromDateTest_1939, StrSizeMatchesStringLength_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 45, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (strValue != nullptr && strSize > 0) {
        EXPECT_EQ(strSize, std::strlen(strValue));
    }
}

// Test with boundary month values
TEST_F(WXMPUtilsConvertFromDateTest_1939, BoundaryMonth12_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 12, 31, 23, 59, 59);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test with boundary month value 1
TEST_F(WXMPUtilsConvertFromDateTest_1939, BoundaryMonth1_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 1, 1, 0, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test WXMP_Result is properly initialized before call
TEST_F(WXMPUtilsConvertFromDateTest_1939, ResultInitialization_1939) {
    WXMP_Result wResult;
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 45);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with negative year (BCE dates)
TEST_F(WXMPUtilsConvertFromDateTest_1939, NegativeYear_1939) {
    XMP_DateTime dt = MakeDateTime(-44, 3, 15, 12, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    // Behavior may vary; just ensure it doesn't crash
    // The function should either succeed or set an error message
}

// Test with leap year date
TEST_F(WXMPUtilsConvertFromDateTest_1939, LeapYearDate_1939) {
    XMP_DateTime dt = MakeDateTime(2024, 2, 29, 12, 0, 0);
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromDate_1(dt, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test consistency: same input produces same output
TEST_F(WXMPUtilsConvertFromDateTest_1939, ConsistentOutput_1939) {
    XMP_DateTime dt = MakeDateTime(2023, 6, 15, 10, 30, 45, 1, 5, 30);

    XMP_StringPtr strValue1 = nullptr;
    XMP_StringLen strSize1 = 0;
    WXMP_Result wResult1;
    WXMPUtils_ConvertFromDate_1(dt, &strValue1, &strSize1, &wResult1);

    XMP_StringPtr strValue2 = nullptr;
    XMP_StringLen strSize2 = 0;
    WXMP_Result wResult2;
    WXMPUtils_ConvertFromDate_1(dt, &strValue2, &strSize2, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_EQ(strSize1, strSize2);
    if (strValue1 != nullptr && strValue2 != nullptr) {
        EXPECT_STREQ(strValue1, strValue2);
    }
}
