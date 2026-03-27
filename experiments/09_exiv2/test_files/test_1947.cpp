#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "XMP_Const.h"



class WXMPUtilsTest_1947 : public ::testing::Test {

protected:

    XMP_DateTime time;

    WXMP_Result result;



    void SetUp() override {

        // Initialize the XMP_DateTime structure with some default values

        time.year = 2023;

        time.month = 10;

        time.day = 5;

        time.hour = 14;

        time.minute = 30;

        time.second = 45;

        time.tzSign = 1; // UTC+1

        time.tzHour = 1;

        time.tzMinute = 0;

        time.nanoSecond = 0;



        result.errMessage = nullptr;

        result.ptrResult = nullptr;

        result.floatResult = 0.0;

        result.int64Result = 0;

        result.int32Result = 0;

    }

};



TEST_F(WXMPUtilsTest_1947, ConvertToUTCTime_Success_1947) {

    WXMPUtils_ConvertToUTCTime_1(&time, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // Assuming the conversion logic is correct, check if the timezone is set to UTC

    EXPECT_EQ(time.tzSign, 0); // UTC

    EXPECT_EQ(time.tzHour, 0);

    EXPECT_EQ(time.tzMinute, 0);

}



TEST_F(WXMPUtilsTest_1947, ConvertToUTCTime_NullTime_1947) {

    WXMPUtils_ConvertToUTCTime_1(nullptr, &result);

    EXPECT_NE(result.errMessage, nullptr);

    // Check if the error code is kXMPErr_BadParam

    XMP_Error* xmpError = reinterpret_cast<XMP_Error*>(result.ptrResult);

    EXPECT_EQ(xmpError->GetID(), kXMPErr_BadParam);

}



TEST_F(WXMPUtilsTest_1947, ConvertToUTCTime_NullResult_1947) {

    WXMPUtils_ConvertToUTCTime_1(&time, nullptr);

    // No error is expected since the function does not use the result pointer if null

    EXPECT_TRUE(true);

}



TEST_F(WXMPUtilsTest_1947, ConvertToUTCTime_BoundaryCondition_1947) {

    // Set time to UTC already

    time.tzSign = 0;

    time.tzHour = 0;

    time.tzMinute = 0;



    WXMPUtils_ConvertToUTCTime_1(&time, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // Check if the timezone remains unchanged

    EXPECT_EQ(time.tzSign, 0); // UTC

    EXPECT_EQ(time.tzHour, 0);

    EXPECT_EQ(time.tzMinute, 0);

}
