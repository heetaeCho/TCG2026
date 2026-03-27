#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



// Mocking XMPUtils::ConvertToInt64 for external interaction verification

class MockXMPUtils {

public:

    MOCK_STATIC_METHOD1(ConvertToInt64, XMP_Int64(XMP_StringPtr));

};



// Test fixture for WXMPUtils_ConvertToInt64_1

class WXMPUtils_ConvertToInt64_Test_1942 : public ::testing::Test {

protected:

    WXMP_Result wResult;

    void SetUp() override {

        // Initialize the result structure

        wResult.errMessage = nullptr;

        wResult.int64Result = 0;

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(WXMPUtils_ConvertToInt64_Test_1942, ValidConversion_1942) {

    XMP_StringPtr strValue = "12345";

    MockXMPUtils::ConvertToInt64(strValue);

    EXPECT_CALL(MockXMPUtils, ConvertToInt64(strValue)).WillOnce(::testing::Return(12345));



    WXMPUtils_ConvertToInt64_1(strValue, &wResult);



    EXPECT_EQ(wResult.int64Result, 12345);

}



TEST_F(WXMPUtils_ConvertToInt64_Test_1942, NegativeConversion_1942) {

    XMP_StringPtr strValue = "-12345";

    MockXMPUtils::ConvertToInt64(strValue);

    EXPECT_CALL(MockXMPUtils, ConvertToInt64(strValue)).WillOnce(::testing::Return(-12345));



    WXMPUtils_ConvertToInt64_1(strValue, &wResult);



    EXPECT_EQ(wResult.int64Result, -12345);

}



TEST_F(WXMPUtils_ConvertToInt64_Test_1942, ZeroConversion_1942) {

    XMP_StringPtr strValue = "0";

    MockXMPUtils::ConvertToInt64(strValue);

    EXPECT_CALL(MockXMPUtils, ConvertToInt64(strValue)).WillOnce(::testing::Return(0));



    WXMPUtils_ConvertToInt64_1(strValue, &wResult);



    EXPECT_EQ(wResult.int64Result, 0);

}



TEST_F(WXMPUtils_ConvertToInt64_Test_1942, EmptyString_1942) {

    XMP_StringPtr strValue = "";

    MockXMPUtils::ConvertToInt64(strValue);



    EXPECT_THROW(WXMPUtils_ConvertToInt64_1(strValue, &wResult), XMP_Error);

}



TEST_F(WXMPUtils_ConvertToInt64_Test_1942, NullString_1942) {

    XMP_StringPtr strValue = nullptr;

    MockXMPUtils::ConvertToInt64(strValue);



    EXPECT_THROW(WXMPUtils_ConvertToInt64_1(strValue, &wResult), XMP_Error);

}



TEST_F(WXMPUtils_ConvertToInt64_Test_1942, NonNumericString_1942) {

    XMP_StringPtr strValue = "abc";

    MockXMPUtils::ConvertToInt64(strValue);



    EXPECT_THROW(WXMPUtils_ConvertToInt64_1(strValue, &wResult), XMP_Error);

}
