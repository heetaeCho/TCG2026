#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/XMPUtils.hpp"



class WXMPUtils_ConvertFromBool_Test_1935 : public ::testing::Test {

protected:

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;

};



TEST_F(WXMPUtils_ConvertFromBool_Test_1935, ConvertTrueToBooleanString_1935) {

    XMP_Bool binValue = true;

    WXMPUtils_ConvertFromBool_1(binValue, &strValue, &strSize, &wResult);

    EXPECT_STREQ(strValue, "true");

    EXPECT_EQ(strSize, 4u);

}



TEST_F(WXMPUtils_ConvertFromBool_Test_1935, ConvertFalseToBooleanString_1935) {

    XMP_Bool binValue = false;

    WXMPUtils_ConvertFromBool_1(binValue, &strValue, &strSize, &wResult);

    EXPECT_STREQ(strValue, "false");

    EXPECT_EQ(strSize, 5u);

}



TEST_F(WXMPUtils_ConvertFromBool_Test_1935, NullStrValueUsesDefault_1935) {

    XMP_Bool binValue = true;

    WXMPUtils_ConvertFromBool_1(binValue, nullptr, &strSize, &wResult);

    EXPECT_STREQ(strValue, "true");

    EXPECT_EQ(strSize, 4u);

}



TEST_F(WXMPUtils_ConvertFromBool_Test_1935, NullStrSizeUsesDefault_1935) {

    XMP_Bool binValue = false;

    WXMPUtils_ConvertFromBool_1(binValue, &strValue, nullptr, &wResult);

    EXPECT_STREQ(strValue, "false");

}



TEST_F(WXMPUtils_ConvertFromBool_Test_1935, NullWResultNoError_1935) {

    XMP_Bool binValue = true;

    WXMPUtils_ConvertFromBool_1(binValue, &strValue, &strSize, nullptr);

    EXPECT_STREQ(strValue, "true");

    EXPECT_EQ(strSize, 4u);

}
