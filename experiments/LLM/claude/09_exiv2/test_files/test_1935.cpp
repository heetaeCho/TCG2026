#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ConvertFromBool_1(
    XMP_Bool binValue,
    XMP_StringPtr * strValue,
    XMP_StringLen * strSize,
    WXMP_Result * wResult);

class WXMPUtilsConvertFromBoolTest_1935 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(&result, 0, sizeof(result));
        result.errMessage = nullptr;
    }

    WXMP_Result result;
};

// Test converting true value produces "True" string
TEST_F(WXMPUtilsConvertFromBoolTest_1935, ConvertTrueValue_1935) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromBool_1(true, &strValue, &strSize, &result);

    EXPECT_EQ(result.errMessage, nullptr) << "Expected no error for true conversion";
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "True");
    EXPECT_GT(strSize, 0u);
    EXPECT_EQ(strSize, strlen("True"));
}

// Test converting false value produces "False" string
TEST_F(WXMPUtilsConvertFromBoolTest_1935, ConvertFalseValue_1935) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromBool_1(false, &strValue, &strSize, &result);

    EXPECT_EQ(result.errMessage, nullptr) << "Expected no error for false conversion";
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "False");
    EXPECT_GT(strSize, 0u);
    EXPECT_EQ(strSize, strlen("False"));
}

// Test with null strValue pointer (should not crash, uses voidStringPtr)
TEST_F(WXMPUtilsConvertFromBoolTest_1935, NullStrValuePointer_1935) {
    XMP_StringLen strSize = 0;

    EXPECT_NO_FATAL_FAILURE(
        WXMPUtils_ConvertFromBool_1(true, nullptr, &strSize, &result)
    );
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test with null strSize pointer (should not crash, uses voidStringLen)
TEST_F(WXMPUtilsConvertFromBoolTest_1935, NullStrSizePointer_1935) {
    XMP_StringPtr strValue = nullptr;

    EXPECT_NO_FATAL_FAILURE(
        WXMPUtils_ConvertFromBool_1(true, &strValue, nullptr, &result)
    );
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "True");
}

// Test with both null strValue and strSize pointers
TEST_F(WXMPUtilsConvertFromBoolTest_1935, BothNullOutputPointers_1935) {
    EXPECT_NO_FATAL_FAILURE(
        WXMPUtils_ConvertFromBool_1(false, nullptr, nullptr, &result)
    );
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test that non-zero XMP_Bool values are treated as true
TEST_F(WXMPUtilsConvertFromBoolTest_1935, NonZeroBoolValueTreatedAsTrue_1935) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromBool_1(static_cast<XMP_Bool>(2), &strValue, &strSize, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "True");
}

// Test that zero XMP_Bool value produces false
TEST_F(WXMPUtilsConvertFromBoolTest_1935, ZeroBoolValueProducesFalse_1935) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromBool_1(static_cast<XMP_Bool>(0), &strValue, &strSize, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "False");
}

// Test that result structure is properly initialized after successful call
TEST_F(WXMPUtilsConvertFromBoolTest_1935, ResultStructureCleanAfterSuccess_1935) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromBool_1(true, &strValue, &strSize, &result);

    EXPECT_EQ(result.errMessage, nullptr);
}

// Test string size matches actual string length for true
TEST_F(WXMPUtilsConvertFromBoolTest_1935, StringSizeMatchesLengthTrue_1935) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromBool_1(true, &strValue, &strSize, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_EQ(strSize, static_cast<XMP_StringLen>(strlen(strValue)));
}

// Test string size matches actual string length for false
TEST_F(WXMPUtilsConvertFromBoolTest_1935, StringSizeMatchesLengthFalse_1935) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromBool_1(false, &strValue, &strSize, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_EQ(strSize, static_cast<XMP_StringLen>(strlen(strValue)));
}
