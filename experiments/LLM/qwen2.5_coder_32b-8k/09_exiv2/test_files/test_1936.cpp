#include <gtest/gtest.h>

#include "WXMPUtils.hpp"

#include "XMP_Const.h"



#define TEST_ID 1936



TEST(WXMPUtils_ConvertFromInt_1936, NormalOperation_DefaultFormat_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(42, "", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "42");

    EXPECT_EQ(strSize, 2);

}



TEST(WXMPUtils_ConvertFromInt_1936, NormalOperation_CustomFormat_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(42, "%d", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "42");

    EXPECT_EQ(strSize, 2);

}



TEST(WXMPUtils_ConvertFromInt_1936, NullStrValue_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(42, "", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "42");

    EXPECT_EQ(strSize, 2);

}



TEST(WXMPUtils_ConvertFromInt_1936, NullStrSize_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(42, "", &strValue, nullptr, &wResult);



    EXPECT_STREQ(strValue, "42");

}



TEST(WXMPUtils_ConvertFromInt_1936, NullFormat_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(42, nullptr, &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "42");

    EXPECT_EQ(strSize, 2);

}



TEST(WXMPUtils_ConvertFromInt_1936, NullWResult_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;



    WXMPUtils_ConvertFromInt_1(42, "", &strValue, &strSize, nullptr);



    EXPECT_STREQ(strValue, "42");

    EXPECT_EQ(strSize, 2);

}



TEST(WXMPUtils_ConvertFromInt_1936, BoundaryCondition_MinInt_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(INT_MIN, "", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "-2147483648");

    EXPECT_EQ(strSize, 11);

}



TEST(WXMPUtils_ConvertFromInt_1936, BoundaryCondition_MaxInt_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(INT_MAX, "", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "2147483647");

    EXPECT_EQ(strSize, 10);

}



TEST(WXMPUtils_ConvertFromInt_1936, CustomFormatWithPadding_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(42, "%05d", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "00042");

    EXPECT_EQ(strSize, 5);

}



TEST(WXMPUtils_ConvertFromInt_1936, CustomFormatWithSign_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(42, "%+d", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "+42");

    EXPECT_EQ(strSize, 3);

}



TEST(WXMPUtils_ConvertFromInt_1936, CustomFormatWithHexLower_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(255, "%x", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "ff");

    EXPECT_EQ(strSize, 2);

}



TEST(WXMPUtils_ConvertFromInt_1936, CustomFormatWithHexUpper_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(255, "%X", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "FF");

    EXPECT_EQ(strSize, 2);

}



TEST(WXMPUtils_ConvertFromInt_1936, CustomFormatWithOctal_1936) {

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ConvertFromInt_1(255, "%o", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "377");

    EXPECT_EQ(strSize, 3);

}
