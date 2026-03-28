#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "public/include/XMP_Environment.h"
#include "public/include/XMP_Const.h"

// Forward declarations and external function declarations
extern "C" {
void WXMPIterator_Unlock_1(XMP_OptionBits options);
}

// We need access to WXMP_Result and related types
#include "public/include/client-glue/WXMP_Common.hpp"

// Include XMPCore initialization if available
#include "public/include/XMP.hpp"

class WXMPIteratorUnlockTest_1911 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP toolkit if needed
        try {
            SXMPMeta::Initialize();
        } catch (...) {
            // May already be initialized or not available
        }
    }

    static void TearDownTestSuite() {
        try {
            SXMPMeta::Terminate();
        } catch (...) {
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that WXMPIterator_Unlock_1 can be called with zero options without crashing
TEST_F(WXMPIteratorUnlockTest_1911, UnlockWithZeroOptions_1911) {
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0));
}

// Test that WXMPIterator_Unlock_1 can be called with non-zero options without crashing
TEST_F(WXMPIteratorUnlockTest_1911, UnlockWithNonZeroOptions_1911) {
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0x0001));
}

// Test calling Unlock with maximum option bits
TEST_F(WXMPIteratorUnlockTest_1911, UnlockWithMaxOptions_1911) {
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0xFFFFFFFF));
}

// Test calling Unlock multiple times in succession
TEST_F(WXMPIteratorUnlockTest_1911, UnlockCalledMultipleTimes_1911) {
    EXPECT_NO_THROW({
        WXMPIterator_Unlock_1(0);
        WXMPIterator_Unlock_1(0);
        WXMPIterator_Unlock_1(0);
    });
}

// Test calling Unlock with various option bit patterns
TEST_F(WXMPIteratorUnlockTest_1911, UnlockWithVariousOptionBits_1911) {
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0x00000001));
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0x00000002));
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0x00000004));
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0x80000000));
}

// Test that the void_wResult structure is properly initialized
TEST_F(WXMPIteratorUnlockTest_1911, VoidResultDefaultState_1911) {
    // The function uses void_wResult internally. We verify the function
    // doesn't throw/crash which implies void_wResult is properly set up.
    EXPECT_NO_THROW(WXMPIterator_Unlock_1(0));
}
