#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



class WXMPUtilsTest_1946 : public ::testing::Test {

protected:

    XMP_DateTime time;

    WXMP_Result result;



    void SetUp() override {

        memset(&time, 0, sizeof(XMP_DateTime));

        memset(&result, 0, sizeof(WXMP_Result));

    }

};



TEST_F(WXMPUtilsTest_1946, SetTimeZoneWithValidDateTime_1946) {

    WXMPUtils_SetTimeZone_1(&time, &result);

    // Assuming the function modifies time.tzSign and time.tzHour/tzMinute as expected

    EXPECT_NE(time.tzSign, 0);  // This is a basic check to ensure some change happened.

}



TEST_F(WXMPUtilsTest_1946, SetTimeZoneWithNullDateTime_1946) {

    WXMPUtils_SetTimeZone_1(nullptr, &result);

    EXPECT_STREQ(result.errMessage, "Null output date");

    EXPECT_EQ(result.int32Result, kXMPErr_BadParam);

}



TEST_F(WXMPUtilsTest_1946, SetTimeZoneWithNullResult_1946) {

    WXMPUtils_SetTimeZone_1(&time, nullptr);

    // Assuming the function does not throw when result is null (as per typical C-style error handling)

    EXPECT_EQ(time.tzSign, 0);  // No change expected since result is not checked.

}
