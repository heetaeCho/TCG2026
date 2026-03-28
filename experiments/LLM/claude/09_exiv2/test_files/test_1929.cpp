#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary headers for XMP SDK
#define TXMP_STRING_TYPE std::string

// We need to include the XMP headers
#include "XMPUtils.hpp"
#include "XMPCore_Impl.hpp"
#include "WXMPUtils.hpp"

// Forward declarations for the WXMPUtils C-linkage functions
extern "C" {
void WXMPUtils_Unlock_1(XMP_OptionBits options);
}

class WXMPUtilsTest_1929 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        try {
            XMPUtils::Initialize();
        } catch (...) {
            // May already be initialized
        }
    }

    void TearDown() override {
        // Cleanup
    }
};

// Test: WXMPUtils_Unlock_1 with zero options (normal operation)
TEST_F(WXMPUtilsTest_1929, UnlockWithZeroOptions_1929) {
    // WXMPUtils_Unlock_1 should not throw or crash with zero options
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0));
}

// Test: WXMPUtils_Unlock_1 with non-zero options
TEST_F(WXMPUtilsTest_1929, UnlockWithNonZeroOptions_1929) {
    // Should not throw or crash with arbitrary option bits
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0x0001));
}

// Test: WXMPUtils_Unlock_1 with max option bits
TEST_F(WXMPUtilsTest_1929, UnlockWithMaxOptions_1929) {
    // Boundary: maximum possible option bits value
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0xFFFFFFFF));
}

// Test: WXMP_Result default construction
TEST_F(WXMPUtilsTest_1929, WXMPResultDefaultConstruction_1929) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Multiple unlock calls should not crash
TEST_F(WXMPUtilsTest_1929, MultipleUnlockCalls_1929) {
    EXPECT_NO_THROW({
        WXMPUtils_Unlock_1(0);
        WXMPUtils_Unlock_1(0);
        WXMPUtils_Unlock_1(0);
    });
}

// Test: ConvertFromBool true
TEST_F(WXMPUtilsTest_1929, ConvertFromBoolTrue_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromBool(true, &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
    // "True" is the expected XMP boolean string representation
    EXPECT_STREQ(strValue, "True");
}

// Test: ConvertFromBool false
TEST_F(WXMPUtilsTest_1929, ConvertFromBoolFalse_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromBool(false, &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
    EXPECT_STREQ(strValue, "False");
}

// Test: ConvertToBool with "True"
TEST_F(WXMPUtilsTest_1929, ConvertToBoolTrue_1929) {
    bool result = XMPUtils::ConvertToBool("True");
    EXPECT_TRUE(result);
}

// Test: ConvertToBool with "False"
TEST_F(WXMPUtilsTest_1929, ConvertToBoolFalse_1929) {
    bool result = XMPUtils::ConvertToBool("False");
    EXPECT_FALSE(result);
}

// Test: ConvertFromInt basic value
TEST_F(WXMPUtilsTest_1929, ConvertFromIntBasic_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromInt(42, "", &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
    EXPECT_STREQ(strValue, "42");
}

// Test: ConvertFromInt zero
TEST_F(WXMPUtilsTest_1929, ConvertFromIntZero_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromInt(0, "", &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "0");
}

// Test: ConvertFromInt negative value
TEST_F(WXMPUtilsTest_1929, ConvertFromIntNegative_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromInt(-100, "", &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-100");
}

// Test: ConvertToInt
TEST_F(WXMPUtilsTest_1929, ConvertToIntBasic_1929) {
    XMP_Int32 result = XMPUtils::ConvertToInt("42");
    EXPECT_EQ(result, 42);
}

// Test: ConvertToInt negative
TEST_F(WXMPUtilsTest_1929, ConvertToIntNegative_1929) {
    XMP_Int32 result = XMPUtils::ConvertToInt("-100");
    EXPECT_EQ(result, -100);
}

// Test: ConvertToInt zero
TEST_F(WXMPUtilsTest_1929, ConvertToIntZero_1929) {
    XMP_Int32 result = XMPUtils::ConvertToInt("0");
    EXPECT_EQ(result, 0);
}

// Test: ConvertFromInt64 basic
TEST_F(WXMPUtilsTest_1929, ConvertFromInt64Basic_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromInt64(1234567890123LL, "", &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test: ConvertToInt64
TEST_F(WXMPUtilsTest_1929, ConvertToInt64Basic_1929) {
    XMP_Int64 result = XMPUtils::ConvertToInt64("1234567890123");
    EXPECT_EQ(result, 1234567890123LL);
}

// Test: ConvertFromFloat
TEST_F(WXMPUtilsTest_1929, ConvertFromFloatBasic_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromFloat(3.14, "", &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
}

// Test: ConvertToFloat
TEST_F(WXMPUtilsTest_1929, ConvertToFloatBasic_1929) {
    double result = XMPUtils::ConvertToFloat("3.14");
    EXPECT_NEAR(result, 3.14, 0.001);
}

// Test: ConvertToFloat zero
TEST_F(WXMPUtilsTest_1929, ConvertToFloatZero_1929) {
    double result = XMPUtils::ConvertToFloat("0.0");
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: EncodeToBase64 and DecodeFromBase64 roundtrip
TEST_F(WXMPUtilsTest_1929, Base64RoundTrip_1929) {
    const char* rawInput = "Hello, World!";
    XMP_StringLen rawInputLen = static_cast<XMP_StringLen>(strlen(rawInput));
    
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    
    EXPECT_NO_THROW(XMPUtils::EncodeToBase64(rawInput, rawInputLen, &encodedStr, &encodedLen));
    ASSERT_NE(encodedStr, nullptr);
    EXPECT_GT(encodedLen, 0u);
    
    XMP_StringPtr decodedStr = nullptr;
    XMP_StringLen decodedLen = 0;
    
    EXPECT_NO_THROW(XMPUtils::DecodeFromBase64(encodedStr, encodedLen, &decodedStr, &decodedLen));
    ASSERT_NE(decodedStr, nullptr);
    EXPECT_EQ(decodedLen, rawInputLen);
    EXPECT_EQ(std::string(decodedStr, decodedLen), std::string(rawInput, rawInputLen));
}

// Test: EncodeToBase64 empty input
TEST_F(WXMPUtilsTest_1929, Base64EncodeEmpty_1929) {
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    
    EXPECT_NO_THROW(XMPUtils::EncodeToBase64("", 0, &encodedStr, &encodedLen));
    EXPECT_EQ(encodedLen, 0u);
}

// Test: CurrentDateTime returns a valid datetime
TEST_F(WXMPUtilsTest_1929, CurrentDateTime_1929) {
    XMP_DateTime dt;
    memset(&dt, 0, sizeof(dt));
    
    EXPECT_NO_THROW(XMPUtils::CurrentDateTime(&dt));
    // Year should be reasonable (after 2000)
    EXPECT_GE(dt.year, 2000);
    // Month should be 1-12
    EXPECT_GE(dt.month, 1);
    EXPECT_LE(dt.month, 12);
    // Day should be 1-31
    EXPECT_GE(dt.day, 1);
    EXPECT_LE(dt.day, 31);
}

// Test: CompareDateTime equal dates
TEST_F(WXMPUtilsTest_1929, CompareDateTimeEqual_1929) {
    XMP_DateTime dt1, dt2;
    memset(&dt1, 0, sizeof(dt1));
    memset(&dt2, 0, sizeof(dt2));
    
    dt1.year = 2023; dt1.month = 6; dt1.day = 15;
    dt1.hour = 12; dt1.minute = 0; dt1.second = 0;
    dt1.nanoSecond = 0; dt1.hasDate = true; dt1.hasTime = true;
    
    dt2.year = 2023; dt2.month = 6; dt2.day = 15;
    dt2.hour = 12; dt2.minute = 0; dt2.second = 0;
    dt2.nanoSecond = 0; dt2.hasDate = true; dt2.hasTime = true;
    
    int cmp = XMPUtils::CompareDateTime(dt1, dt2);
    EXPECT_EQ(cmp, 0);
}

// Test: CompareDateTime left < right
TEST_F(WXMPUtilsTest_1929, CompareDateTimeLessThan_1929) {
    XMP_DateTime dt1, dt2;
    memset(&dt1, 0, sizeof(dt1));
    memset(&dt2, 0, sizeof(dt2));
    
    dt1.year = 2022; dt1.month = 1; dt1.day = 1;
    dt1.hasDate = true; dt1.hasTime = false;
    
    dt2.year = 2023; dt2.month = 1; dt2.day = 1;
    dt2.hasDate = true; dt2.hasTime = false;
    
    int cmp = XMPUtils::CompareDateTime(dt1, dt2);
    EXPECT_LT(cmp, 0);
}

// Test: CompareDateTime left > right
TEST_F(WXMPUtilsTest_1929, CompareDateTimeGreaterThan_1929) {
    XMP_DateTime dt1, dt2;
    memset(&dt1, 0, sizeof(dt1));
    memset(&dt2, 0, sizeof(dt2));
    
    dt1.year = 2024; dt1.month = 1; dt1.day = 1;
    dt1.hasDate = true; dt1.hasTime = false;
    
    dt2.year = 2023; dt2.month = 1; dt2.day = 1;
    dt2.hasDate = true; dt2.hasTime = false;
    
    int cmp = XMPUtils::CompareDateTime(dt1, dt2);
    EXPECT_GT(cmp, 0);
}

// Test: ComposeArrayItemPath
TEST_F(WXMPUtilsTest_1929, ComposeArrayItemPathBasic_1929) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ComposeArrayItemPath(
        "http://ns.adobe.com/xap/1.0/", "dc:subject", 1, &fullPath, &pathSize));
    ASSERT_NE(fullPath, nullptr);
    EXPECT_GT(pathSize, 0u);
}

// Test: ComposeStructFieldPath
TEST_F(WXMPUtilsTest_1929, ComposeStructFieldPathBasic_1929) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ComposeStructFieldPath(
        "http://ns.adobe.com/xap/1.0/", "xmp:MyStruct",
        "http://ns.adobe.com/xap/1.0/", "xmp:MyField",
        &fullPath, &pathSize));
    ASSERT_NE(fullPath, nullptr);
    EXPECT_GT(pathSize, 0u);
}

// Test: ConvertFromDate and ConvertToDate roundtrip
TEST_F(WXMPUtilsTest_1929, DateConversionRoundTrip_1929) {
    XMP_DateTime original;
    memset(&original, 0, sizeof(original));
    original.year = 2023;
    original.month = 7;
    original.day = 20;
    original.hour = 14;
    original.minute = 30;
    original.second = 45;
    original.nanoSecond = 0;
    original.hasDate = true;
    original.hasTime = true;
    original.hasTimeZone = false;
    
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromDate(original, &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_GT(strSize, 0u);
    
    XMP_DateTime converted;
    memset(&converted, 0, sizeof(converted));
    
    EXPECT_NO_THROW(XMPUtils::ConvertToDate(strValue, &converted));
    EXPECT_EQ(converted.year, original.year);
    EXPECT_EQ(converted.month, original.month);
    EXPECT_EQ(converted.day, original.day);
    EXPECT_EQ(converted.hour, original.hour);
    EXPECT_EQ(converted.minute, original.minute);
    EXPECT_EQ(converted.second, original.second);
}

// Test: Unlock called multiple times with different options
TEST_F(WXMPUtilsTest_1929, UnlockVariousOptions_1929) {
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0x0000));
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0x0001));
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0x0002));
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0x0004));
    EXPECT_NO_THROW(WXMPUtils_Unlock_1(0x0008));
}

// Test: ConvertToBool with various true-ish values
TEST_F(WXMPUtilsTest_1929, ConvertToBoolVariousTrue_1929) {
    EXPECT_TRUE(XMPUtils::ConvertToBool("true"));
    EXPECT_TRUE(XMPUtils::ConvertToBool("1"));
}

// Test: ConvertToBool with various false-ish values
TEST_F(WXMPUtilsTest_1929, ConvertToBoolVariousFalse_1929) {
    EXPECT_FALSE(XMPUtils::ConvertToBool("false"));
    EXPECT_FALSE(XMPUtils::ConvertToBool("0"));
}

// Test: ConvertFromInt with INT32_MAX boundary
TEST_F(WXMPUtilsTest_1929, ConvertFromIntMax_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromInt(2147483647, "", &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "2147483647");
}

// Test: ConvertFromInt with INT32_MIN boundary
TEST_F(WXMPUtilsTest_1929, ConvertFromIntMin_1929) {
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    
    EXPECT_NO_THROW(XMPUtils::ConvertFromInt(-2147483647 - 1, "", &strValue, &strSize));
    ASSERT_NE(strValue, nullptr);
    EXPECT_STREQ(strValue, "-2147483648");
}

// Test: Base64 encode single byte
TEST_F(WXMPUtilsTest_1929, Base64EncodeSingleByte_1929) {
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    
    EXPECT_NO_THROW(XMPUtils::EncodeToBase64("A", 1, &encodedStr, &encodedLen));
    ASSERT_NE(encodedStr, nullptr);
    EXPECT_GT(encodedLen, 0u);
}
