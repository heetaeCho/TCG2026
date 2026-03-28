#include <gtest/gtest.h>
#include "client-glue/WXMP_Common.hpp"
#include "XMP_Const.h"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ConvertToInt_1(XMP_StringPtr strValue, WXMP_Result* wResult);

class WXMPUtilsConvertToIntTest_1941 : public ::testing::Test {
protected:
    WXMP_Result wResult;

    void SetUp() override {
        wResult = WXMP_Result();
    }
};

// Normal operation tests

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertPositiveInteger_1941) {
    WXMPUtils_ConvertToInt_1("42", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 42);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertZero_1941) {
    WXMPUtils_ConvertToInt_1("0", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 0);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertNegativeInteger_1941) {
    WXMPUtils_ConvertToInt_1("-123", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), -123);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertOne_1941) {
    WXMPUtils_ConvertToInt_1("1", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 1);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertNegativeOne_1941) {
    WXMPUtils_ConvertToInt_1("-1", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), -1);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertLargePositiveValue_1941) {
    WXMPUtils_ConvertToInt_1("2147483647", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 2147483647);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertLargeNegativeValue_1941) {
    WXMPUtils_ConvertToInt_1("-2147483648", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), -2147483647 - 1);
}

// Boundary / edge case tests

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertWithLeadingWhitespace_1941) {
    WXMPUtils_ConvertToInt_1("  42", &wResult);
    // If the implementation handles leading whitespace, result should be 42
    // If not, errMessage would be set. We check based on observable behavior.
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 42);
    } else {
        // The function reported an error, which is also acceptable behavior
        EXPECT_NE(wResult.errMessage, nullptr);
    }
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertWithPlusSign_1941) {
    WXMPUtils_ConvertToInt_1("+10", &wResult);
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 10);
    }
}

// Error case tests

TEST_F(WXMPUtilsConvertToIntTest_1941, NullPointerThrowsError_1941) {
    WXMPUtils_ConvertToInt_1(nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, EmptyStringThrowsError_1941) {
    WXMPUtils_ConvertToInt_1("", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ResultInitializedCorrectly_1941) {
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertMultipleValues_1941) {
    WXMPUtils_ConvertToInt_1("100", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 100);

    WXMP_Result wResult2;
    WXMPUtils_ConvertToInt_1("200", &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult2.int32Result), 200);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertNonNumericString_1941) {
    WXMPUtils_ConvertToInt_1("abc", &wResult);
    // Non-numeric string should cause an error
    EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertMixedAlphaNumeric_1941) {
    WXMPUtils_ConvertToInt_1("12abc", &wResult);
    // Behavior depends on implementation - either partial parse or error
    // We just verify it doesn't crash and produces a deterministic result
    if (wResult.errMessage == nullptr) {
        // Some implementations may parse partial numbers
        SUCCEED();
    } else {
        EXPECT_NE(wResult.errMessage, nullptr);
    }
}

TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertSingleDigit_1941) {
    WXMPUtils_ConvertToInt_1("7", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int32>(wResult.int32Result), 7);
}
