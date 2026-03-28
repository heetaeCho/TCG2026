#include <gtest/gtest.h>
#include <cstring>
#include <climits>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern void WXMPUtils_ConvertFromInt64_1(
    XMP_Int64 binValue,
    XMP_StringPtr format,
    XMP_StringPtr * strValue,
    XMP_StringLen * strSize,
    WXMP_Result * wResult);

// We need XMPUtils to be initialized for these tests to work
#include "XMPUtils.hpp"

class WXMPUtilsConvertFromInt64Test_1937 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP toolkit
        try {
            XMPUtils::Initialize();
        } catch (...) {
            // May already be initialized
        }
    }

    void SetUp() override {
        memset(&result, 0, sizeof(result));
        result.errMessage = nullptr;
        strValue = nullptr;
        strSize = 0;
    }

    WXMP_Result result;
    XMP_StringPtr strValue;
    XMP_StringLen strSize;
};

// Test normal conversion of zero
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ConvertZero_1937) {
    WXMPUtils_ConvertFromInt64_1(0, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "0");
    EXPECT_GT(strSize, 0u);
}

// Test normal conversion of a positive value
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ConvertPositiveValue_1937) {
    WXMPUtils_ConvertFromInt64_1(12345, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "12345");
    EXPECT_EQ(strSize, 5u);
}

// Test normal conversion of a negative value
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ConvertNegativeValue_1937) {
    WXMPUtils_ConvertFromInt64_1(-9876, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-9876");
    EXPECT_EQ(strSize, 5u);
}

// Test conversion of max int64 value
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ConvertMaxInt64_1937) {
    XMP_Int64 maxVal = 9223372036854775807LL;
    WXMPUtils_ConvertFromInt64_1(maxVal, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "9223372036854775807");
    EXPECT_GT(strSize, 0u);
}

// Test conversion of min int64 value
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ConvertMinInt64_1937) {
    XMP_Int64 minVal = (-9223372036854775807LL - 1);
    WXMPUtils_ConvertFromInt64_1(minVal, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test with null format (should default to "")
TEST_F(WXMPUtilsConvertFromInt64Test_1937, NullFormatDefaultsToEmpty_1937) {
    WXMPUtils_ConvertFromInt64_1(42, nullptr, &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "42");
}

// Test with null strValue pointer (should not crash)
TEST_F(WXMPUtilsConvertFromInt64Test_1937, NullStrValueDoesNotCrash_1937) {
    WXMPUtils_ConvertFromInt64_1(100, "", nullptr, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test with null strSize pointer (should not crash)
TEST_F(WXMPUtilsConvertFromInt64Test_1937, NullStrSizeDoesNotCrash_1937) {
    WXMPUtils_ConvertFromInt64_1(100, "", &strValue, nullptr, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "100");
}

// Test with both null strValue and strSize
TEST_F(WXMPUtilsConvertFromInt64Test_1937, BothOutputsNull_1937) {
    WXMPUtils_ConvertFromInt64_1(200, "", nullptr, nullptr, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test conversion of value 1
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ConvertOne_1937) {
    WXMPUtils_ConvertFromInt64_1(1, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "1");
    EXPECT_EQ(strSize, 1u);
}

// Test conversion of value -1
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ConvertNegativeOne_1937) {
    WXMPUtils_ConvertFromInt64_1(-1, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-1");
    EXPECT_EQ(strSize, 2u);
}

// Test that strSize matches string length
TEST_F(WXMPUtilsConvertFromInt64Test_1937, StrSizeMatchesLength_1937) {
    WXMPUtils_ConvertFromInt64_1(123456789, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_EQ(strSize, strlen(strValue));
}

// Test with a large positive value
TEST_F(WXMPUtilsConvertFromInt64Test_1937, LargePositiveValue_1937) {
    XMP_Int64 largeVal = 1000000000000LL;
    WXMPUtils_ConvertFromInt64_1(largeVal, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "1000000000000");
}

// Test with a large negative value
TEST_F(WXMPUtilsConvertFromInt64Test_1937, LargeNegativeValue_1937) {
    XMP_Int64 largeNeg = -1000000000000LL;
    WXMPUtils_ConvertFromInt64_1(largeNeg, "", &strValue, &strSize, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-1000000000000");
}

// Test WXMP_Result is properly initialized after call
TEST_F(WXMPUtilsConvertFromInt64Test_1937, ResultProperlySet_1937) {
    WXMP_Result res;
    res.errMessage = nullptr;
    WXMPUtils_ConvertFromInt64_1(50, "", &strValue, &strSize, &res);
    EXPECT_EQ(res.errMessage, nullptr);
}
