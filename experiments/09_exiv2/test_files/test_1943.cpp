#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



// Assuming WXMPUtils_ConvertToFloat_1 is declared in a header file included here



TEST(WXMPUtils_ConvertToFloat_1943, NormalOperation_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "123.45";

    WXMPUtils_ConvertToFloat_1(strValue, &wResult);

    EXPECT_EQ(wResult.floatResult, 123.45);

}



TEST(WXMPUtils_ConvertToFloat_1943, BoundaryCondition_ZeroString_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "0";

    WXMPUtils_ConvertToFloat_1(strValue, &wResult);

    EXPECT_EQ(wResult.floatResult, 0.0);

}



TEST(WXMPUtils_ConvertToFloat_1943, BoundaryCondition_MaxFloatString_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "3.402823466e+38"; // Max float value

    WXMPUtils_ConvertToFloat_1(strValue, &wResult);

    EXPECT_EQ(wResult.floatResult, 3.402823466e+38);

}



TEST(WXMPUtils_ConvertToFloat_1943, BoundaryCondition_MinFloatString_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "-3.402823466e+38"; // Min float value

    WXMPUtils_ConvertToFloat_1(strValue, &wResult);

    EXPECT_EQ(wResult.floatResult, -3.402823466e+38);

}



TEST(WXMPUtils_ConvertToFloat_1943, ExceptionalCase_EmptyString_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "";

    EXPECT_THROW(WXMPUtils_ConvertToFloat_1(strValue, &wResult), XMP_Error);

}



TEST(WXMPUtils_ConvertToFloat_1943, ExceptionalCase_NullString_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = nullptr;

    EXPECT_THROW(WXMPUtils_ConvertToFloat_1(strValue, &wResult), XMP_Error);

}



TEST(WXMPUtils_ConvertToFloat_1943, ExceptionalCase_NonNumericString_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "abc";

    EXPECT_THROW(WXMPUtils_ConvertToFloat_1(strValue, &wResult), XMP_Error);

}



TEST(WXMPUtils_ConvertToFloat_1943, ExceptionalCase_FloatOverflow_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "1e+39"; // This should overflow the float range

    EXPECT_THROW(WXMPUtils_ConvertToFloat_1(strValue, &wResult), XMP_Error);

}



TEST(WXMPUtils_ConvertToFloat_1943, ExceptionalCase_FloatUnderflow_1943) {

    WXMP_Result wResult;

    XMP_StringPtr strValue = "-1e+39"; // This should underflow the float range

    EXPECT_THROW(WXMPUtils_ConvertToFloat_1(strValue, &wResult), XMP_Error);

}
