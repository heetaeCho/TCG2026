#include <gtest/gtest.h>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_Initialize_1(WXMP_Result* wResult);

class WXMPMetaInitializeTest_1988 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state before each test if possible
    }

    void TearDown() override {
        // Clean up after each test
        // Call Terminate to balance Initialize calls
        try {
            XMPMeta::Terminate();
        } catch (...) {
            // Ignore errors during cleanup
        }
    }
};

// Test that WXMPMeta_Initialize_1 returns a successful result (non-zero int32Result)
TEST_F(WXMPMetaInitializeTest_1988, InitializeReturnsSuccess_1988) {
    WXMP_Result wResult;
    WXMPMeta_Initialize_1(&wResult);

    // Initialize should succeed and return true (non-zero)
    EXPECT_NE(0u, wResult.int32Result);
    // No error message should be set on success
    EXPECT_EQ(nullptr, wResult.errMessage);
}

// Test that WXMP_Result is properly zero-initialized before the call
TEST_F(WXMPMetaInitializeTest_1988, ResultDefaultConstruction_1988) {
    WXMP_Result wResult;

    // Verify default construction sets errMessage to 0/null
    EXPECT_EQ(nullptr, wResult.errMessage);
}

// Test that calling Initialize multiple times still succeeds
TEST_F(WXMPMetaInitializeTest_1988, MultipleInitializationsSucceed_1988) {
    WXMP_Result wResult1;
    WXMPMeta_Initialize_1(&wResult1);
    EXPECT_NE(0u, wResult1.int32Result);
    EXPECT_EQ(nullptr, wResult1.errMessage);

    // Terminate before re-initializing
    XMPMeta::Terminate();

    WXMP_Result wResult2;
    WXMPMeta_Initialize_1(&wResult2);
    EXPECT_NE(0u, wResult2.int32Result);
    EXPECT_EQ(nullptr, wResult2.errMessage);
}

// Test that int32Result field is properly set after initialization
TEST_F(WXMPMetaInitializeTest_1988, Int32ResultIsSet_1988) {
    WXMP_Result wResult;
    // Set int32Result to a known value before calling to verify it gets overwritten
    wResult.int32Result = 0;

    WXMPMeta_Initialize_1(&wResult);

    // The result should be set to a boolean true value (typically 1)
    EXPECT_TRUE(wResult.int32Result != 0);
}

// Test that after successful initialization, XMPMeta operations can proceed
TEST_F(WXMPMetaInitializeTest_1988, InitializeEnablesXMPMetaOperations_1988) {
    WXMP_Result wResult;
    WXMPMeta_Initialize_1(&wResult);
    EXPECT_NE(0u, wResult.int32Result);

    // After successful initialization, we should be able to create an XMPMeta object
    // without crashing
    XMPMeta meta;
    // If we reach here without crashing, the initialization was effective
    SUCCEED();
}

// Test that the result structure's other fields are not corrupted
TEST_F(WXMPMetaInitializeTest_1988, OtherResultFieldsNotCorrupted_1988) {
    WXMP_Result wResult;
    // The default constructor sets errMessage to 0
    // Other fields may be uninitialized, but errMessage should remain null on success

    WXMPMeta_Initialize_1(&wResult);

    EXPECT_EQ(nullptr, wResult.errMessage);
    // int32Result should contain the boolean result of Initialize()
    EXPECT_TRUE(wResult.int32Result == 0 || wResult.int32Result == 1);
}

// Test sequential init-terminate-init cycle
TEST_F(WXMPMetaInitializeTest_1988, InitTerminateInitCycle_1988) {
    WXMP_Result wResult;

    // First init
    WXMPMeta_Initialize_1(&wResult);
    EXPECT_NE(0u, wResult.int32Result);
    EXPECT_EQ(nullptr, wResult.errMessage);

    // Terminate
    XMPMeta::Terminate();

    // Second init
    WXMP_Result wResult2;
    WXMPMeta_Initialize_1(&wResult2);
    EXPECT_NE(0u, wResult2.int32Result);
    EXPECT_EQ(nullptr, wResult2.errMessage);
}
