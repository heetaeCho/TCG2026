#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

#include "TestProjects/exiv2/xmpsdk/src/WXMPUtils.cpp"



class WXMPUtilsTest_1945 : public ::testing::Test {

protected:

    XMP_DateTime time;

    WXMP_Result result;



    void SetUp() override {

        memset(&time, 0, sizeof(XMP_DateTime));

        memset(&result, 0, sizeof(WXMP_Result));

    }

};



TEST_F(WXMPUtilsTest_1945, CurrentDateTime_Success_1945) {

    WXMPUtils_CurrentDateTime_1(&time, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    EXPECT_NE(time.year, 0); // Assuming year should be non-zero for a valid date

}



TEST_F(WXMPUtilsTest_1945, CurrentDateTime_NullTimePointer_1945) {

    WXMPUtils_CurrentDateTime_1(nullptr, &result);

    EXPECT_STREQ(result.errMessage, "Null output date");

    EXPECT_EQ(result.int32Result, kXMPErr_BadParam);

}



TEST_F(WXMPUtilsTest_1945, CurrentDateTime_ValidTimePointer_1945) {

    WXMP_DateTime validTime;

    memset(&validTime, 0, sizeof(XMP_DateTime));

    WXMPUtils_CurrentDateTime_1(&validTime, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    EXPECT_NE(validTime.year, 0); // Assuming year should be non-zero for a valid date

}
