#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/WXMPUtils.cpp"



TEST(WXMPUtils_ConvertToBool_Test_1940, NormalOperation_True_1940) {

    WXMP_Result wResult;

    WXMPUtils_ConvertToBool_1("true", &wResult);

    EXPECT_EQ(wResult.int32Result, 1);

}



TEST(WXMPUtils_ConvertToBool_Test_1940, NormalOperation_False_1940) {

    WXMP_Result wResult;

    WXMPUtils_ConvertToBool_1("false", &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

}



TEST(WXMPUtils_ConvertToBool_Test_1940, NormalOperation_CaseInsensitiveTrue_1940) {

    WXMP_Result wResult;

    WXMPUtils_ConvertToBool_1("TRUE", &wResult);

    EXPECT_EQ(wResult.int32Result, 1);

}



TEST(WXMPUtils_ConvertToBool_Test_1940, NormalOperation_CaseInsensitiveFalse_1940) {

    WXMP_Result wResult;

    WXMPUtils_ConvertToBool_1("FALSE", &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

}



TEST(WXMPUtils_ConvertToBool_Test_1940, BoundaryCondition_EmptyString_1940) {

    WXMP_Result wResult;

    EXPECT_THROW(WXMPUtils_ConvertToBool_1("", &wResult), XMP_Error);

}



TEST(WXMPUtils_ConvertToBool_Test_1940, BoundaryCondition_NullPointer_1940) {

    WXMP_Result wResult;

    EXPECT_THROW(WXMPUtils_ConvertToBool_1(nullptr, &wResult), XMP_Error);

}



TEST(WXMPUtils_ConvertToBool_Test_1940, ExceptionalCase_InvalidString_1940) {

    WXMP_Result wResult;

    WXMPUtils_ConvertToBool_1("invalid", &wResult);

    EXPECT_EQ(wResult.int32Result, 0); // Assuming "invalid" is treated as false

}



TEST(WXMPUtils_ConvertToBool_Test_1940, ExceptionalCase_ZeroString_1940) {

    WXMP_Result wResult;

    EXPECT_THROW(WXMPUtils_ConvertToBool_1("0", &wResult), XMP_Error);

}
