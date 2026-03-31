#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ConvertToFloat_1(XMP_StringPtr strValue, WXMP_Result* wResult);

class WXMPUtilsConvertToFloatTest_1943 : public ::testing::Test {
protected:
    WXMP_Result result;

    void SetUp() override {
        result = WXMP_Result();
    }
};

// Normal operation tests

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertPositiveInteger_1943) {
    WXMPUtils_ConvertToFloat_1("42", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 42.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertNegativeInteger_1943) {
    WXMPUtils_ConvertToFloat_1("-42", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, -42.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertPositiveFloat_1943) {
    WXMPUtils_ConvertToFloat_1("3.14", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NEAR(result.floatResult, 3.14, 0.001);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertNegativeFloat_1943) {
    WXMPUtils_ConvertToFloat_1("-3.14", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NEAR(result.floatResult, -3.14, 0.001);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertZero_1943) {
    WXMPUtils_ConvertToFloat_1("0", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 0.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertZeroPointZero_1943) {
    WXMPUtils_ConvertToFloat_1("0.0", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 0.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertScientificNotation_1943) {
    WXMPUtils_ConvertToFloat_1("1.5e2", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 150.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertSmallScientificNotation_1943) {
    WXMPUtils_ConvertToFloat_1("1.5e-2", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NEAR(result.floatResult, 0.015, 0.0001);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertLargeNumber_1943) {
    WXMPUtils_ConvertToFloat_1("1000000.0", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 1000000.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertVerySmallNumber_1943) {
    WXMPUtils_ConvertToFloat_1("0.000001", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NEAR(result.floatResult, 0.000001, 1e-9);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertOne_1943) {
    WXMPUtils_ConvertToFloat_1("1", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 1.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertNegativeOne_1943) {
    WXMPUtils_ConvertToFloat_1("-1", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, -1.0);
}

// Boundary condition tests

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertPositiveZero_1943) {
    WXMPUtils_ConvertToFloat_1("+0", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 0.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertNegativeZero_1943) {
    WXMPUtils_ConvertToFloat_1("-0", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 0.0);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertPositiveSign_1943) {
    WXMPUtils_ConvertToFloat_1("+3.14", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NEAR(result.floatResult, 3.14, 0.001);
}

// Error / exceptional cases

TEST_F(WXMPUtilsConvertToFloatTest_1943, NullPointerThrowsError_1943) {
    WXMPUtils_ConvertToFloat_1(nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, EmptyStringThrowsError_1943) {
    WXMPUtils_ConvertToFloat_1("", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Verify WXMP_Result is properly initialized before use

TEST_F(WXMPUtilsConvertToFloatTest_1943, ResultStructInitializedCorrectly_1943) {
    WXMP_Result freshResult;
    EXPECT_EQ(freshResult.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(freshResult.floatResult, 0.0);
}

// Test with leading/trailing whitespace (behavior depends on implementation)
TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertWithLeadingWhitespace_1943) {
    WXMPUtils_ConvertToFloat_1(" 3.14", &result);
    // We can only check if it either succeeds or reports an error
    if (result.errMessage == nullptr) {
        EXPECT_NEAR(result.floatResult, 3.14, 0.001);
    } else {
        EXPECT_NE(result.errMessage, nullptr);
    }
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertDecimalPointOnly_1943) {
    WXMPUtils_ConvertToFloat_1(".5", &result);
    if (result.errMessage == nullptr) {
        EXPECT_NEAR(result.floatResult, 0.5, 0.001);
    }
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, ConvertCapitalE_1943) {
    WXMPUtils_ConvertToFloat_1("1.5E2", &result);
    if (result.errMessage == nullptr) {
        EXPECT_DOUBLE_EQ(result.floatResult, 150.0);
    }
}

TEST_F(WXMPUtilsConvertToFloatTest_1943, MultipleCallsProduceCorrectResults_1943) {
    WXMPUtils_ConvertToFloat_1("10.0", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result.floatResult, 10.0);

    WXMP_Result result2;
    WXMPUtils_ConvertToFloat_1("20.0", &result2);
    EXPECT_EQ(result2.errMessage, nullptr);
    EXPECT_DOUBLE_EQ(result2.floatResult, 20.0);
}
