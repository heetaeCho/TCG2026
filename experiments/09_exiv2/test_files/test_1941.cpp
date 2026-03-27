#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "WXMP_Common.hpp"



// Mocking external collaborators if necessary (not required in this case)

// class MockExternalCollaborator : public ExternalCollaborator {

// public:

//     MOCK_METHOD(return_type, method_name, (param_types), (override));

// };



TEST(WXMPUtils_ConvertToInt_1941, NormalOperation_1941) {

    WXMP_Result result;

    XMP_StringPtr strValue = "123";

    WXMP_ConvertToInt_1(strValue, &result);

    EXPECT_EQ(result.int32Result, 123);

}



TEST(WXMPUtils_ConvertToInt_1941, BoundaryCondition_ZeroString_1941) {

    WXMP_Result result;

    XMP_StringPtr strValue = "0";

    WXMP_ConvertToInt_1(strValue, &result);

    EXPECT_EQ(result.int32Result, 0);

}



TEST(WXMPUtils_ConvertToInt_1941, BoundaryCondition_MaxInt_1941) {

    WXMP_Result result;

    XMP_StringPtr strValue = "2147483647"; // INT_MAX

    WXMP_ConvertToInt_1(strValue, &result);

    EXPECT_EQ(result.int32Result, 2147483647);

}



TEST(WXMPUtils_ConvertToInt_1941, BoundaryCondition_MinInt_1941) {

    WXMP_Result result;

    XMP_StringPtr strValue = "-2147483648"; // INT_MIN

    WXMP_ConvertToInt_1(strValue, &result);

    EXPECT_EQ(result.int32Result, -2147483648);

}



TEST(WXMPUtils_ConvertToInt_1941, ErrorCase_EmptyString_1941) {

    WXMP_Result result;

    XMP_StringPtr strValue = "";

    try {

        WXMP_ConvertToInt_1(strValue, &result);

        FAIL() << "Expected exception not thrown";

    } catch (const XMP_Error& error) {

        EXPECT_EQ(error.GetID(), kXMPErr_BadParam);

        EXPECT_STREQ(error.GetErrMsg(), "Empty string value");

    }

}



TEST(WXMPUtils_ConvertToInt_1941, ErrorCase_NullString_1941) {

    WXMP_Result result;

    XMP_StringPtr strValue = nullptr;

    try {

        WXMP_ConvertToInt_1(strValue, &result);

        FAIL() << "Expected exception not thrown";

    } catch (const XMP_Error& error) {

        EXPECT_EQ(error.GetID(), kXMPErr_BadParam);

        EXPECT_STREQ(error.GetErrMsg(), "Empty string value");

    }

}



TEST(WXMPUtils_ConvertToInt_1941, ErrorCase_NonNumericString_1941) {

    WXMP_Result result;

    XMP_StringPtr strValue = "abc";

    try {

        WXMP_ConvertToInt_1(strValue, &result);

        FAIL() << "Expected exception not thrown";

    } catch (const XMP_Error& error) {

        // Assuming the implementation throws kXMPErr_BadParam for non-numeric strings

        EXPECT_EQ(error.GetID(), kXMPErr_BadParam);

        EXPECT_STREQ(error.GetErrMsg(), "Empty string value");

    }

}
