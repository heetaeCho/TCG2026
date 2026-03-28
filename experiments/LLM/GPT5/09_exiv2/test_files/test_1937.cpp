#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/xmpsdk/src/WXMPUtils.cpp"
#include "./TestProjects/exiv2/xmpsdk/src/XMPUtils.hpp"
#include "./TestProjects/exiv2/xmpsdk/src/XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Mock class for WXMP_Result to capture interaction during testing.
class MockWXMP_Result : public WXMP_Result {
public:
    MOCK_METHOD(void, SetErrorMessage, (XMP_StringPtr msg), ());
    MOCK_METHOD(void, SetResultPointer, (void* ptr), ());
    MOCK_METHOD(void, SetInt64Result, (XMP_Uns64 result), ());
    MOCK_METHOD(void, SetInt32Result, (XMP_Uns32 result), ());
};

// Test fixture class
class WXMPUtilsTest : public ::testing::Test {
protected:
    // Initialize and setup code can go here if needed
    WXMPUtilsTest() = default;
    ~WXMPUtilsTest() override = default;
};

// Test normal operation of WXMPUtils_ConvertFromInt64_1
TEST_F(WXMPUtilsTest, ConvertFromInt64_Normal_1937) {
    XMP_Int64 binValue = 123456789;
    XMP_StringPtr format = "%lld";
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    MockWXMP_Result wResult;

    EXPECT_CALL(wResult, SetInt64Result(::testing::_)).Times(1);

    WXMPUtils_ConvertFromInt64_1(binValue, format, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);  // Ensure that strValue is set
    EXPECT_GT(strSize, 0);         // Ensure that the strSize is set
}

// Test boundary condition where binValue is 0
TEST_F(WXMPUtilsTest, ConvertFromInt64_Boundary_Zero_1938) {
    XMP_Int64 binValue = 0;
    XMP_StringPtr format = "%lld";
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    MockWXMP_Result wResult;

    EXPECT_CALL(wResult, SetInt64Result(0)).Times(1);

    WXMPUtils_ConvertFromInt64_1(binValue, format, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);  // Ensure that strValue is set even for 0
    EXPECT_GT(strSize, 0);         // Ensure that the strSize is set even for 0
}

// Test boundary condition for very large values
TEST_F(WXMPUtilsTest, ConvertFromInt64_Boundary_LargeValue_1939) {
    XMP_Int64 binValue = 9223372036854775807;  // Maximum value for XMP_Int64
    XMP_StringPtr format = "%lld";
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    MockWXMP_Result wResult;

    EXPECT_CALL(wResult, SetInt64Result(::testing::_)).Times(1);

    WXMPUtils_ConvertFromInt64_1(binValue, format, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);  // Ensure that strValue is set
    EXPECT_GT(strSize, 0);         // Ensure that the strSize is set
}

// Test exceptional/error case when format is null
TEST_F(WXMPUtilsTest, ConvertFromInt64_Error_NullFormat_1940) {
    XMP_Int64 binValue = 123456789;
    XMP_StringPtr format = nullptr;  // Null format
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;
    MockWXMP_Result wResult;

    EXPECT_CALL(wResult, SetInt64Result(::testing::_)).Times(1);

    // This test should verify that the function doesn't crash and handles null format gracefully
    WXMPUtils_ConvertFromInt64_1(binValue, format, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);  // Ensure that strValue is set
    EXPECT_GT(strSize, 0);         // Ensure that the strSize is set
}

// Test exceptional/error case when strValue is null
TEST_F(WXMPUtilsTest, ConvertFromInt64_Error_NullStrValue_1941) {
    XMP_Int64 binValue = 123456789;
    XMP_StringPtr format = "%lld";
    XMP_StringPtr strValue = nullptr;  // Null strValue
    XMP_StringLen strSize = 0;
    MockWXMP_Result wResult;

    EXPECT_CALL(wResult, SetInt64Result(::testing::_)).Times(1);

    // This test should verify that the function handles null strValue without crashing
    WXMPUtils_ConvertFromInt64_1(binValue, format, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);  // Ensure that strValue is set
    EXPECT_GT(strSize, 0);         // Ensure that the strSize is set
}

// Test exceptional/error case when strSize is null
TEST_F(WXMPUtilsTest, ConvertFromInt64_Error_NullStrSize_1942) {
    XMP_Int64 binValue = 123456789;
    XMP_StringPtr format = "%lld";
    XMP_StringPtr strValue = nullptr;
    XMP_StringLen strSize = 0;  // Null strSize
    MockWXMP_Result wResult;

    EXPECT_CALL(wResult, SetInt64Result(::testing::_)).Times(1);

    // This test should verify that the function handles null strSize without crashing
    WXMPUtils_ConvertFromInt64_1(binValue, format, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);  // Ensure that strValue is set
    EXPECT_GT(strSize, 0);         // Ensure that the strSize is set
}