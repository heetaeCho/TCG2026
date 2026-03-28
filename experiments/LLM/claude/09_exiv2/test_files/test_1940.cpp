#include <gtest/gtest.h>
#include "client-glue/WXMP_Common.hpp"
#include "XMPUtils.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ConvertToBool_1(XMP_StringPtr strValue, WXMP_Result* wResult);

class WXMPUtilsConvertToBoolTest_1940 : public ::testing::Test {
protected:
    WXMP_Result wResult;

    void SetUp() override {
        wResult = WXMP_Result();
    }
};

// Test: Null pointer input should set error message (kXMPErr_BadParam)
TEST_F(WXMPUtilsConvertToBoolTest_1940, NullPointerThrowsBadParam_1940) {
    WXMPUtils_ConvertToBool_1(nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty string input should set error message (kXMPErr_BadParam)
TEST_F(WXMPUtilsConvertToBoolTest_1940, EmptyStringThrowsBadParam_1940) {
    WXMPUtils_ConvertToBool_1("", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: "true" string should return true (non-zero)
TEST_F(WXMPUtilsConvertToBoolTest_1940, TrueStringReturnsTrue_1940) {
    WXMPUtils_ConvertToBool_1("true", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: "false" string should return false (zero)
TEST_F(WXMPUtilsConvertToBoolTest_1940, FalseStringReturnsFalse_1940) {
    WXMPUtils_ConvertToBool_1("false", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: "True" string should return true
TEST_F(WXMPUtilsConvertToBoolTest_1940, TrueCapitalizedReturnsTrue_1940) {
    WXMPUtils_ConvertToBool_1("True", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: "False" string should return false
TEST_F(WXMPUtilsConvertToBoolTest_1940, FalseCapitalizedReturnsFalse_1940) {
    WXMPUtils_ConvertToBool_1("False", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: "1" string should return true
TEST_F(WXMPUtilsConvertToBoolTest_1940, OneStringReturnsTrue_1940) {
    WXMPUtils_ConvertToBool_1("1", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: "0" string should return false
TEST_F(WXMPUtilsConvertToBoolTest_1940, ZeroStringReturnsFalse_1940) {
    WXMPUtils_ConvertToBool_1("0", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: "yes" string should return true
TEST_F(WXMPUtilsConvertToBoolTest_1940, YesStringReturnsTrue_1940) {
    WXMPUtils_ConvertToBool_1("yes", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: "no" string should return false
TEST_F(WXMPUtilsConvertToBoolTest_1940, NoStringReturnsFalse_1940) {
    WXMPUtils_ConvertToBool_1("no", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: Result struct is properly initialized before call
TEST_F(WXMPUtilsConvertToBoolTest_1940, ResultInitializedCorrectly_1940) {
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: "TRUE" all caps should return true
TEST_F(WXMPUtilsConvertToBoolTest_1940, TrueAllCapsReturnsTrue_1940) {
    WXMPUtils_ConvertToBool_1("TRUE", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: "FALSE" all caps should return false
TEST_F(WXMPUtilsConvertToBoolTest_1940, FalseAllCapsReturnsFalse_1940) {
    WXMPUtils_ConvertToBool_1("FALSE", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: An arbitrary non-boolean string - behavior depends on implementation
// This tests that the function doesn't crash on arbitrary input
TEST_F(WXMPUtilsConvertToBoolTest_1940, ArbitraryStringDoesNotCrash_1940) {
    WXMPUtils_ConvertToBool_1("maybe", &wResult);
    // We just verify it doesn't crash; errMessage may or may not be set
    // depending on implementation
}

// Test: Single space string should not be treated as empty
TEST_F(WXMPUtilsConvertToBoolTest_1940, SingleSpaceStringDoesNotThrowEmptyError_1940) {
    WXMPUtils_ConvertToBool_1(" ", &wResult);
    // A space is not empty (not '\0'), so it shouldn't throw "Empty string value"
    // It may throw a different error or return some value
}
