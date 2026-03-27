#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



// Test Fixture for WXMPUtils_ConvertToDate_1

class WXMPUtils_ConvertToDate_Test_1944 : public ::testing::Test {

protected:

    XMP_DateTime binValue;

    WXMP_Result wResult;



    void SetUp() override {

        memset(&binValue, 0, sizeof(XMP_DateTime));

        memset(&wResult, 0, sizeof(WXMP_Result));

    }

};



// Test normal operation with a valid date string

TEST_F(WXMPUtils_ConvertToDate_Test_1944, ValidDateString_1944) {

    const XMP_StringPtr strValue = "2023-10-05T14:48:00+02:00";

    WXMPUtils_ConvertToDate_1(strValue, &binValue, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_EQ(binValue.year, 2023);

    EXPECT_EQ(binValue.month, 10);

    EXPECT_EQ(binValue.day, 5);

    EXPECT_EQ(binValue.hour, 14);

    EXPECT_EQ(binValue.minute, 48);

    EXPECT_EQ(binValue.second, 0);

    EXPECT_EQ(binValue.tzSign, 1);

    EXPECT_EQ(binValue.tzHour, 2);

    EXPECT_EQ(binValue.tzMinute, 0);

}



// Test boundary condition with minimum date string

TEST_F(WXMPUtils_ConvertToDate_Test_1944, MinimumDateString_1944) {

    const XMP_StringPtr strValue = "0001-01-01T00:00:00Z";

    WXMPUtils_ConvertToDate_1(strValue, &binValue, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_EQ(binValue.year, 1);

    EXPECT_EQ(binValue.month, 1);

    EXPECT_EQ(binValue.day, 1);

    EXPECT_EQ(binValue.hour, 0);

    EXPECT_EQ(binValue.minute, 0);

    EXPECT_EQ(binValue.second, 0);

    EXPECT_EQ(binValue.tzSign, 0);

    EXPECT_EQ(binValue.tzHour, 0);

    EXPECT_EQ(binValue.tzMinute, 0);

}



// Test boundary condition with maximum date string

TEST_F(WXMPUtils_ConvertToDate_Test_1944, MaximumDateString_1944) {

    const XMP_StringPtr strValue = "9999-12-31T23:59:59Z";

    WXMPUtils_ConvertToDate_1(strValue, &binValue, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_EQ(binValue.year, 9999);

    EXPECT_EQ(binValue.month, 12);

    EXPECT_EQ(binValue.day, 31);

    EXPECT_EQ(binValue.hour, 23);

    EXPECT_EQ(binValue.minute, 59);

    EXPECT_EQ(binValue.second, 59);

    EXPECT_EQ(binValue.tzSign, 0);

    EXPECT_EQ(binValue.tzHour, 0);

    EXPECT_EQ(binValue.tzMinute, 0);

}



// Test exceptional case with invalid date string

TEST_F(WXMPUtils_ConvertToDate_Test_1944, InvalidDateString_1944) {

    const XMP_StringPtr strValue = "invalid-date";

    WXMPUtils_ConvertToDate_1(strValue, &binValue, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



// Test exceptional case with null output date pointer

TEST_F(WXMPUtils_ConvertToDate_Test_1944, NullOutputDatePointer_1944) {

    const XMP_StringPtr strValue = "2023-10-05T14:48:00+02:00";

    WXMPUtils_ConvertToDate_1(strValue, nullptr, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



// Test exceptional case with null input date string

TEST_F(WXMPUtils_ConvertToDate_Test_1944, NullInputDateString_1944) {

    const XMP_StringPtr strValue = nullptr;

    WXMPUtils_ConvertToDate_1(strValue, &binValue, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}
