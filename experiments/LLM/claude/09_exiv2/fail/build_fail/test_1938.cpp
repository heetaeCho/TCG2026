#include <gtest/gtest.h>
#include <cstring>
#include <cmath>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore_Impl.hpp"
#include "XMPUtils.hpp"

// Forward declaration of the function under test
extern void WXMPUtils_ConvertFromFloat_1(
    double binValue,
    XMP_StringPtr format,
    XMP_StringPtr * strValue,
    XMP_StringLen * strSize,
    WXMP_Result * wResult
);

class WXMPUtilsConvertFromFloatTest_1938 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPUtils::Initialize();
    }

    void TearDown() override {
        XMPUtils::Terminate();
    }
};

// Test normal conversion of a positive float value
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertPositiveFloat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(3.14, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    // The string should contain a representation of 3.14
    std::string result(strValue, strSize);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.14, 0.001);
}

// Test normal conversion of a negative float value
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertNegativeFloat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(-2.718, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    std::string result(strValue, strSize);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, -2.718, 0.001);
}

// Test conversion of zero
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertZero_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(0.0, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    std::string result(strValue, strSize);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 0.0);
}

// Test conversion with null format (should default to empty string)
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertWithNullFormat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(1.5, nullptr, &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    std::string result(strValue, strSize);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1.5, 0.001);
}

// Test conversion with null strValue pointer (should not crash)
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertWithNullStrValue_1938) {
    WXMP_Result wResult;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(42.0, "", nullptr, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test conversion with null strSize pointer (should not crash)
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertWithNullStrSize_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;

    WXMPUtils_ConvertFromFloat_1(42.0, "", &strValue, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
}

// Test conversion with both null strValue and strSize
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertWithBothNullOutputs_1938) {
    WXMP_Result wResult;

    WXMPUtils_ConvertFromFloat_1(99.9, "", nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test conversion of a very large float value
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertLargeFloat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(1.0e+300, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test conversion of a very small float value
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertVerySmallFloat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(1.0e-300, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test conversion with a specific format string
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertWithSpecificFormat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(3.14159, "%f", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    std::string result(strValue, strSize);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.14159, 0.001);
}

// Test conversion with precision format
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertWithPrecisionFormat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(3.14159265, "%.2f", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    std::string result(strValue, strSize);
    // With "%.2f", we expect something like "3.14"
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test that strSize matches the actual string length
TEST_F(WXMPUtilsConvertFromFloatTest_1938, StrSizeMatchesStringLength_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(1.0, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_EQ(strSize, std::strlen(strValue));
}

// Test conversion of negative zero
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertNegativeZero_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(-0.0, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test conversion of integer-valued double
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertIntegerValuedDouble_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(42.0, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    std::string result(strValue, strSize);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 42.0);
}

// Test WXMP_Result is properly initialized
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ResultInitialization_1938) {
    WXMP_Result wResult;

    // Verify WXMP_Result default construction sets errMessage to 0
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test multiple sequential calls work correctly
TEST_F(WXMPUtilsConvertFromFloatTest_1938, MultipleSequentialCalls_1938) {
    WXMP_Result wResult1, wResult2;
    XMP_StringPtr strValue1 = nullptr, strValue2 = nullptr;
    XMP_StringLen strSize1 = 0, strSize2 = 0;

    WXMPUtils_ConvertFromFloat_1(1.0, "", &strValue1, &strSize1, &wResult1);
    WXMPUtils_ConvertFromFloat_1(2.0, "", &strValue2, &strSize2, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_NE(strValue2, nullptr);
    EXPECT_GT(strSize2, 0u);

    std::string result2(strValue2, strSize2);
    double parsed2 = std::stod(result2);
    EXPECT_NEAR(parsed2, 2.0, 0.001);
}

// Test with empty format string (explicit)
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertWithEmptyFormat_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(7.77, "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);

    std::string result(strValue, strSize);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 7.77, 0.01);
}

// Test with maximum double value
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertMaxDouble_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(std::numeric_limits<double>::max(), "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test with minimum positive double value
TEST_F(WXMPUtilsConvertFromFloatTest_1938, ConvertMinPositiveDouble_1938) {
    WXMP_Result wResult;
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;

    WXMPUtils_ConvertFromFloat_1(std::numeric_limits<double>::min(), "", &strValue, &strSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}
