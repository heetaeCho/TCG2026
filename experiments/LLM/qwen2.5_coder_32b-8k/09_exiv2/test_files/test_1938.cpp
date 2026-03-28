#include <gtest/gtest.h>

#include "WXMPUtils.hpp"

#include "XMP_Const.h"



class WXMPUtilsTest_1938 : public ::testing::Test {

protected:

    XMP_StringPtr strValue;

    XMP_StringLen strSize;

    WXMP_Result wResult;



    void SetUp() override {

        strValue = nullptr;

        strSize = 0;

        wResult.errMessage = nullptr;

    }

};



TEST_F(WXMPUtilsTest_1938, ConvertFromFloat_NormalOperation_1938) {

    double binValue = 3.14159;

    XMP_StringPtr format = "fixed";



    WXMPUtils_ConvertFromFloat_1(binValue, format, &strValue, &strSize, &wResult);



    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1938, ConvertFromFloat_DefaultFormat_1938) {

    double binValue = 2.718;



    WXMPUtils_ConvertFromFloat_1(binValue, nullptr, &strValue, &strSize, &wResult);



    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1938, ConvertFromFloat_NullStrValue_1938) {

    double binValue = 1.618;

    XMP_StringPtr format = "scientific";



    WXMPUtils_ConvertFromFloat_1(binValue, format, nullptr, &strSize, &wResult);



    EXPECT_EQ(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1938, ConvertFromFloat_NullStrSize_1938) {

    double binValue = 42.0;

    XMP_StringPtr format = "general";



    WXMPUtils_ConvertFromFloat_1(binValue, format, &strValue, nullptr, &wResult);



    EXPECT_NE(strValue, nullptr);

    EXPECT_EQ(strSize, 0);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1938, ConvertFromFloat_NullWResult_1938) {

    double binValue = 0.577;

    XMP_StringPtr format = "fixed";



    WXMPUtils_ConvertFromFloat_1(binValue, format, &strValue, &strSize, nullptr);



    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

}



TEST_F(WXMPUtilsTest_1938, ConvertFromFloat_LargeNumber_1938) {

    double binValue = 1.23456789e+30;

    XMP_StringPtr format = "fixed";



    WXMPUtils_ConvertFromFloat_1(binValue, format, &strValue, &strSize, &wResult);



    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1938, ConvertFromFloat_SmallNumber_1938) {

    double binValue = 1.23456789e-30;

    XMP_StringPtr format = "scientific";



    WXMPUtils_ConvertFromFloat_1(binValue, format, &strValue, &strSize, &wResult);



    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    EXPECT_EQ(wResult.errMessage, nullptr);

}
