#include <gtest/gtest.h>

// Include necessary headers for XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetGlobalOptions_1(WXMP_Result* wResult);

class WXMPMetaGetGlobalOptionsTest_1993 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP SDK once for all tests
        XMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        XMPMeta::Terminate();
    }

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that calling GetGlobalOptions with a valid result struct succeeds
TEST_F(WXMPMetaGetGlobalOptionsTest_1993, ReturnsOptionsSuccessfully_1993) {
    WXMP_Result wResult;
    WXMPMeta_GetGlobalOptions_1(&wResult);
    
    // The call should not set an error message
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that the result is a valid option bits value (non-negative as unsigned)
TEST_F(WXMPMetaGetGlobalOptionsTest_1993, ReturnsValidOptionBits_1993) {
    WXMP_Result wResult;
    WXMPMeta_GetGlobalOptions_1(&wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
    // The result should be some valid XMP_OptionBits value stored in int32Result
    XMP_OptionBits options = static_cast<XMP_OptionBits>(wResult.int32Result);
    // We just verify it's retrievable; the actual value depends on global state
    (void)options;
}

// Test that calling GetGlobalOptions multiple times returns consistent results
TEST_F(WXMPMetaGetGlobalOptionsTest_1993, ConsistentResultsOnMultipleCalls_1993) {
    WXMP_Result wResult1;
    WXMPMeta_GetGlobalOptions_1(&wResult1);
    
    WXMP_Result wResult2;
    WXMPMeta_GetGlobalOptions_1(&wResult2);
    
    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_EQ(wResult1.int32Result, wResult2.int32Result);
}

// Test that the default global options are zero (default state after initialization)
TEST_F(WXMPMetaGetGlobalOptionsTest_1993, DefaultGlobalOptionsAreZero_1993) {
    WXMP_Result wResult;
    WXMPMeta_GetGlobalOptions_1(&wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Typically, default global options should be 0
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test that WXMP_Result is properly initialized before call
TEST_F(WXMPMetaGetGlobalOptionsTest_1993, ResultStructProperlyUsed_1993) {
    WXMP_Result wResult;
    // Verify default construction sets errMessage to 0
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    WXMPMeta_GetGlobalOptions_1(&wResult);
    
    // After call, errMessage should still be null (no error)
    EXPECT_EQ(wResult.errMessage, nullptr);
    // int32Result should contain the options
    XMP_Uns32 result = wResult.int32Result;
    (void)result; // Just verify it's accessible
}

// Test that GetGlobalOptions reflects changes made by SetGlobalOptions if applicable
// Note: SetGlobalOptions may be unimplemented/restricted, so we just verify no crash
TEST_F(WXMPMetaGetGlobalOptionsTest_1993, GetOptionsAfterDefaultState_1993) {
    WXMP_Result wResult;
    WXMPMeta_GetGlobalOptions_1(&wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    // Store the initial value
    XMP_Uns32 initialOptions = wResult.int32Result;
    
    // Call again to verify stability
    WXMP_Result wResult2;
    WXMPMeta_GetGlobalOptions_1(&wResult2);
    
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_EQ(wResult2.int32Result, initialOptions);
}
