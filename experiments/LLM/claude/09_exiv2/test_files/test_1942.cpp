#include <gtest/gtest.h>
#include "client-glue/WXMP_Common.hpp"
#include "XMP_Const.h"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ConvertToInt64_1(XMP_StringPtr strValue, WXMP_Result* wResult);

class WXMPUtilsConvertToInt64Test_1942 : public ::testing::Test {
protected:
    WXMP_Result wResult;
    
    void SetUp() override {
        wResult = WXMP_Result();
    }
};

// Normal operation tests

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertPositiveInteger_1942) {
    WXMPUtils_ConvertToInt64_1("42", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 42);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertNegativeInteger_1942) {
    WXMPUtils_ConvertToInt64_1("-42", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), -42);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertZero_1942) {
    WXMPUtils_ConvertToInt64_1("0", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 0);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertOne_1942) {
    WXMPUtils_ConvertToInt64_1("1", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 1);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertNegativeOne_1942) {
    WXMPUtils_ConvertToInt64_1("-1", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), -1);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertLargePositiveNumber_1942) {
    WXMPUtils_ConvertToInt64_1("9223372036854775807", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 9223372036854775807LL);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertLargeNegativeNumber_1942) {
    // INT64_MIN = -9223372036854775808
    WXMPUtils_ConvertToInt64_1("-9223372036854775808", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Use the explicit cast to avoid literal issues
    XMP_Int64 expected = static_cast<XMP_Int64>(-9223372036854775807LL - 1);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), expected);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertSmallNumber_1942) {
    WXMPUtils_ConvertToInt64_1("123456789", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 123456789LL);
}

// Boundary and edge case tests

TEST_F(WXMPUtilsConvertToInt64Test_1942, NullPointerStrValue_1942) {
    WXMPUtils_ConvertToInt64_1(nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, EmptyStringStrValue_1942) {
    WXMPUtils_ConvertToInt64_1("", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test with leading/trailing whitespace (depending on implementation behavior)
TEST_F(WXMPUtilsConvertToInt64Test_1942, StringWithLeadingSpaces_1942) {
    WXMPUtils_ConvertToInt64_1("   42", &wResult);
    // The function may or may not handle whitespace; we just check it doesn't crash
    // If it succeeds, check the value
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 42);
    }
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertPositiveWithPlusSign_1942) {
    WXMPUtils_ConvertToInt64_1("+100", &wResult);
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 100);
    }
}

// Verify WXMP_Result is properly initialized
TEST_F(WXMPUtilsConvertToInt64Test_1942, ResultInitialization_1942) {
    WXMP_Result freshResult;
    EXPECT_EQ(freshResult.errMessage, nullptr);
}

// Test with a moderately large number
TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertModerateNumber_1942) {
    WXMPUtils_ConvertToInt64_1("1000000000000", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), 1000000000000LL);
}

TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertNegativeModerateNumber_1942) {
    WXMPUtils_ConvertToInt64_1("-1000000000000", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(static_cast<XMP_Int64>(wResult.int64Result), -1000000000000LL);
}
