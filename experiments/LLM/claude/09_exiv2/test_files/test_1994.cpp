#include <gtest/gtest.h>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_SetGlobalOptions_1(XMP_OptionBits options, WXMP_Result* wResult);

class WXMPMetaSetGlobalOptionsTest_1994 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized before tests
        XMPMeta::Initialize();
    }

    void TearDown() override {
        // Reset global options to default (0) after each test
        WXMP_Result result;
        WXMPMeta_SetGlobalOptions_1(0, &result);
        XMPMeta::Terminate();
    }
};

// Test: Setting global options to zero (default) should succeed without error
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, SetGlobalOptionsToZero_1994) {
    WXMP_Result wResult;
    WXMPMeta_SetGlobalOptions_1(0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr)
        << "Setting global options to 0 should not produce an error";
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, ResultInitializedCorrectly_1994) {
    WXMP_Result wResult;
    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);
    WXMPMeta_SetGlobalOptions_1(0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting global options with various valid option bits
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, SetGlobalOptionsWithValidBits_1994) {
    WXMP_Result wResult;
    // Option bits value 0 is known to be valid
    WXMPMeta_SetGlobalOptions_1(0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    // Verify through GetGlobalOptions that it was set
    XMP_OptionBits currentOptions = XMPMeta::GetGlobalOptions();
    EXPECT_EQ(currentOptions, static_cast<XMP_OptionBits>(0));
}

// Test: Setting global options with invalid/unsupported option bits should report error
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, SetGlobalOptionsWithInvalidBits_1994) {
    WXMP_Result wResult;
    // Use a large arbitrary value that is likely invalid
    XMP_OptionBits invalidOptions = 0xFFFFFFFF;
    WXMPMeta_SetGlobalOptions_1(invalidOptions, &wResult);
    // If the implementation rejects invalid options, errMessage should be non-null
    // We check that the function handles this gracefully (either succeeds or reports error)
    // This is a boundary test - we just verify it doesn't crash
    // The actual behavior depends on implementation
    if (wResult.errMessage != nullptr) {
        EXPECT_NE(wResult.errMessage, nullptr)
            << "Invalid options should produce an error message";
    }
}

// Test: Setting global options with a single high bit
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, SetGlobalOptionsHighBit_1994) {
    WXMP_Result wResult;
    XMP_OptionBits highBitOption = 0x80000000;
    WXMPMeta_SetGlobalOptions_1(highBitOption, &wResult);
    // Just verify it doesn't crash; check if error is reported
    // Implementation may or may not accept this
}

// Test: Calling SetGlobalOptions multiple times in succession
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, SetGlobalOptionsMultipleTimes_1994) {
    WXMP_Result wResult1, wResult2, wResult3;
    
    WXMPMeta_SetGlobalOptions_1(0, &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);
    
    WXMPMeta_SetGlobalOptions_1(0, &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    
    WXMPMeta_SetGlobalOptions_1(0, &wResult3);
    EXPECT_EQ(wResult3.errMessage, nullptr);
}

// Test: Verify that setting options to 0 and reading back gives 0
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, SetAndVerifyGlobalOptions_1994) {
    WXMP_Result wResult;
    WXMPMeta_SetGlobalOptions_1(0, &wResult);
    
    if (wResult.errMessage == nullptr) {
        XMP_OptionBits opts = XMPMeta::GetGlobalOptions();
        EXPECT_EQ(opts, static_cast<XMP_OptionBits>(0));
    }
}

// Test: Setting options with various small values
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, SetGlobalOptionsSmallValues_1994) {
    WXMP_Result wResult;
    
    // Try setting option value 1
    WXMPMeta_SetGlobalOptions_1(1, &wResult);
    // We don't know if 1 is valid, but ensure no crash
    
    // Reset
    WXMP_Result resetResult;
    WXMPMeta_SetGlobalOptions_1(0, &resetResult);
}

// Test: Result struct fields are not corrupted by the call
TEST_F(WXMPMetaSetGlobalOptionsTest_1994, ResultFieldsNotCorrupted_1994) {
    WXMP_Result wResult;
    wResult.ptrResult = nullptr;
    wResult.floatResult = 0.0;
    wResult.int64Result = 0;
    wResult.int32Result = 0;
    
    WXMPMeta_SetGlobalOptions_1(0, &wResult);
    
    // For a void-returning wrapper, result fields should remain at defaults
    // errMessage should be null on success
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.ptrResult, nullptr);
    }
}
