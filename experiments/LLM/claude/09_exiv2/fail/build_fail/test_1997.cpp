#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for XMP SDK
#define TXMP_STRING_TYPE std::string

// Forward declarations and includes needed for the XMP SDK
#include "public/include/XMP_Environment.h"
#include "public/include/XMP_Const.h"

// Include the XMPMeta header
#include "XMPMeta.hpp"

// Include WXMPMeta declarations
extern "C" {
    void WXMPMeta_Unlock_1(XMP_OptionBits options);
}

// Include for WXMP_Result
#include "client-glue/WXMP_Common.hpp"

class WXMPMetaUnlockTest_1997 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP toolkit once for all tests
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

// Test that WXMPMeta_Unlock_1 can be called with zero options without crashing
TEST_F(WXMPMetaUnlockTest_1997, UnlockWithZeroOptions_1997) {
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0));
}

// Test that WXMPMeta_Unlock_1 can be called with various option bits without crashing
TEST_F(WXMPMetaUnlockTest_1997, UnlockWithNonZeroOptions_1997) {
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0x0001));
}

// Test that WXMPMeta_Unlock_1 handles maximum option bits
TEST_F(WXMPMetaUnlockTest_1997, UnlockWithMaxOptions_1997) {
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0xFFFFFFFF));
}

// Test calling Unlock multiple times in succession
TEST_F(WXMPMetaUnlockTest_1997, UnlockCalledMultipleTimes_1997) {
    EXPECT_NO_THROW({
        WXMPMeta_Unlock_1(0);
        WXMPMeta_Unlock_1(0);
        WXMPMeta_Unlock_1(0);
    });
}

// Test with different option bit patterns
TEST_F(WXMPMetaUnlockTest_1997, UnlockWithVariousOptionBits_1997) {
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0x00000001));
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0x00000002));
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0x00000004));
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0x80000000));
}

// Test WXMP_Result default construction
TEST_F(WXMPMetaUnlockTest_1997, WXMPResultDefaultConstruction_1997) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test that the static Unlock on XMPMeta can be called directly
TEST_F(WXMPMetaUnlockTest_1997, XMPMetaUnlockDirect_1997) {
    EXPECT_NO_THROW(XMPMeta::Unlock(0));
}

// Test XMPMeta static Unlock with options
TEST_F(WXMPMetaUnlockTest_1997, XMPMetaUnlockWithOptions_1997) {
    EXPECT_NO_THROW(XMPMeta::Unlock(0x0001));
}

// Test that WXMPMeta_Unlock_1 doesn't corrupt the global void_wResult
TEST_F(WXMPMetaUnlockTest_1997, UnlockDoesNotCorruptGlobalResult_1997) {
    WXMPMeta_Unlock_1(0);
    // The void_wResult should still be valid after the call
    // We verify by calling again without crash
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0));
}

// Test XMPMeta construction and basic lifecycle alongside Unlock
TEST_F(WXMPMetaUnlockTest_1997, UnlockAfterMetaOperations_1997) {
    XMPMeta meta;
    // Perform some basic operation
    meta.Erase();
    // Then call unlock - should not interfere
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0));
}

// Test that Unlock with boundary option value (just below max) works
TEST_F(WXMPMetaUnlockTest_1997, UnlockWithBoundaryOptionValue_1997) {
    EXPECT_NO_THROW(WXMPMeta_Unlock_1(0xFFFFFFFE));
}

// Test Unlock with single bit set at various positions
TEST_F(WXMPMetaUnlockTest_1997, UnlockWithSingleBitOptions_1997) {
    for (int i = 0; i < 32; ++i) {
        XMP_OptionBits opt = static_cast<XMP_OptionBits>(1u << i);
        EXPECT_NO_THROW(WXMPMeta_Unlock_1(opt)) << "Failed for bit position " << i;
    }
}
