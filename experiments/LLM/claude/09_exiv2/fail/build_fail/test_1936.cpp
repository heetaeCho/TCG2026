#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore_Impl.hpp"
#include "XMPUtils.hpp"

// Declaration of the function under test
extern "C" void WXMPUtils_ConvertFromInt_1(
    XMP_Int32 binValue,
    XMP_StringPtr format,
    XMP_StringPtr * strValue,
    XMP_StringLen * strSize,
    WXMP_Result * wResult);

class WXMPUtilsConvertFromIntTest_1936 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP toolkit is initialized
        XMPUtils::Initialize();
    }

    void TearDown() override {
        XMPUtils::Terminate();
    }
};

// Test normal conversion with a positive integer and default (empty) format
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertPositiveIntDefaultFormat_1936) {
    XMP_Int32 binValue = 42;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error";
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "42");
    EXPECT_EQ(strSize, std::strlen("42"));
}

// Test conversion with zero value
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertZero_1936) {
    XMP_Int32 binValue = 0;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "0");
    EXPECT_EQ(strSize, std::strlen("0"));
}

// Test conversion with a negative integer
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertNegativeInt_1936) {
    XMP_Int32 binValue = -100;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-100");
    EXPECT_EQ(strSize, std::strlen("-100"));
}

// Test conversion with INT32_MAX
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertIntMax_1936) {
    XMP_Int32 binValue = 2147483647; // INT32_MAX
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "2147483647");
    EXPECT_EQ(strSize, std::strlen("2147483647"));
}

// Test conversion with INT32_MIN
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertIntMin_1936) {
    XMP_Int32 binValue = -2147483647 - 1; // INT32_MIN
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-2147483648");
    EXPECT_EQ(strSize, std::strlen("-2147483648"));
}

// Test conversion with null format (should be treated as empty format)
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertWithNullFormat_1936) {
    XMP_Int32 binValue = 123;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, nullptr, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "123");
    EXPECT_EQ(strSize, std::strlen("123"));
}

// Test conversion with null strValue pointer (should not crash)
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertWithNullStrValue_1936) {
    XMP_Int32 binValue = 99;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    // strValue is null - the function should handle it gracefully by using voidStringPtr
    WXMPUtils_ConvertFromInt_1(binValue, "", nullptr, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test conversion with null strSize pointer (should not crash)
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertWithNullStrSize_1936) {
    XMP_Int32 binValue = 77;
    XMP_StringPtr strValue = nullptr;
    WXMP_Result wResult;

    // strSize is null - the function should handle it gracefully by using voidStringLen
    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "77");
}

// Test conversion with both null strValue and null strSize
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertWithNullStrValueAndStrSize_1936) {
    XMP_Int32 binValue = 55;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test conversion with a custom format string (hex format)
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertWithHexFormat_1936) {
    XMP_Int32 binValue = 255;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "%x", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "ff");
    EXPECT_EQ(strSize, std::strlen("ff"));
}

// Test conversion with a custom format string (zero-padded)
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertWithZeroPaddedFormat_1936) {
    XMP_Int32 binValue = 7;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "%05d", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "00007");
    EXPECT_EQ(strSize, std::strlen("00007"));
}

// Test that strSize matches the actual string length
TEST_F(WXMPUtilsConvertFromIntTest_1936, StrSizeMatchesStringLength_1936) {
    XMP_Int32 binValue = 12345;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_EQ(strSize, static_cast<XMP_StringLen>(std::strlen(strValue)));
}

// Test conversion with value 1
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertOne_1936) {
    XMP_Int32 binValue = 1;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "1");
    EXPECT_EQ(strSize, static_cast<XMP_StringLen>(1));
}

// Test conversion with value -1
TEST_F(WXMPUtilsConvertFromIntTest_1936, ConvertNegativeOne_1936) {
    XMP_Int32 binValue = -1;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-1");
    EXPECT_EQ(strSize, std::strlen("-1"));
}

// Test WXMP_Result is properly initialized before the call
TEST_F(WXMPUtilsConvertFromIntTest_1936, ResultInitialized_1936) {
    WXMP_Result wResult;
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_Int32 binValue = 10;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromInt_1(binValue, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test multiple conversions in sequence
TEST_F(WXMPUtilsConvertFromIntTest_1936, MultipleConversions_1936) {
    XMP_StringPtr strValue1 = nullptr;
    XMP_StringLen strSize1 = 0;
    WXMP_Result wResult1;

    WXMPUtils_ConvertFromInt_1(100, "", &strValue1, &strSize1, &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);
    ASSERT_NE(strValue1, nullptr);

    XMP_StringPtr strValue2 = nullptr;
    XMP_StringLen strSize2 = 0;
    WXMP_Result wResult2;

    WXMPUtils_ConvertFromInt_1(200, "", &strValue2, &strSize2, &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    ASSERT_NE(strValue2, nullptr);
    EXPECT_STREQ(strValue2, "200");
}

// Test with all null optional params except wResult
TEST_F(WXMPUtilsConvertFromIntTest_1936, AllNullOptionalParams_1936) {
    WXMP_Result wResult;

    WXMPUtils_ConvertFromInt_1(42, nullptr, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}
