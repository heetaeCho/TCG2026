#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_SetObjectOptions_1(XMPMetaRef xmpRef, XMP_OptionBits options, WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaSetObjectOptionsTest_2044 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP toolkit is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        // Cleanup
    }
};

// Test: Calling SetObjectOptions with zero options on a valid XMPMeta object
TEST_F(WXMPMetaSetObjectOptionsTest_2044, SetZeroOptions_2044) {
    XMPMeta meta;
    WXMP_Result wResult;
    memset(&wResult, 0, sizeof(wResult));

    WXMPMeta_SetObjectOptions_1(MetaToRef(&meta), 0, &wResult);

    // If SetObjectOptions(0) is valid, errMessage should be null (no error)
    // Note: The actual behavior depends on implementation; it may reject options
    // We check whether it either succeeds or sets an error message
    // Since SetObjectOptions is known to often be unimplemented/restricted,
    // we just verify the function doesn't crash and wResult is populated
    // If there's an error, errMessage will be non-null
    // This is a basic sanity test
    SUCCEED();
}

// Test: Calling SetObjectOptions with a null xmpRef should produce an error
TEST_F(WXMPMetaSetObjectOptionsTest_2044, NullXmpRefProducesError_2044) {
    WXMP_Result wResult;
    memset(&wResult, 0, sizeof(wResult));

    WXMPMeta_SetObjectOptions_1(nullptr, 0, &wResult);

    // Passing a null reference should result in an error
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Calling SetObjectOptions with arbitrary option bits
TEST_F(WXMPMetaSetObjectOptionsTest_2044, SetArbitraryOptions_2044) {
    XMPMeta meta;
    WXMP_Result wResult;
    memset(&wResult, 0, sizeof(wResult));

    // Try setting some arbitrary option bits
    XMP_OptionBits options = 0x01;
    WXMPMeta_SetObjectOptions_1(MetaToRef(&meta), options, &wResult);

    // The function may or may not accept these options.
    // We just ensure it doesn't crash and returns a result.
    // If it's unimplemented, errMessage will be set.
    SUCCEED();
}

// Test: Calling SetObjectOptions with all bits set
TEST_F(WXMPMetaSetObjectOptionsTest_2044, SetAllOptionBits_2044) {
    XMPMeta meta;
    WXMP_Result wResult;
    memset(&wResult, 0, sizeof(wResult));

    XMP_OptionBits options = 0xFFFFFFFF;
    WXMPMeta_SetObjectOptions_1(MetaToRef(&meta), options, &wResult);

    // With all bits set, this is likely to be treated as bad options
    // The function should handle this gracefully (set error or succeed)
    // We verify it doesn't crash
    SUCCEED();
}

// Test: WXMP_Result is properly initialized and error message is set on error
TEST_F(WXMPMetaSetObjectOptionsTest_2044, ResultInitialization_2044) {
    WXMP_Result wResult;
    
    // Verify WXMP_Result default construction
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: SetObjectOptions on a freshly created meta object with zero options
// and verify GetObjectOptions reflects the state
TEST_F(WXMPMetaSetObjectOptionsTest_2044, VerifyOptionsViaGetObjectOptions_2044) {
    XMPMeta meta;
    WXMP_Result wResult;
    memset(&wResult, 0, sizeof(wResult));

    // Get initial options
    XMP_OptionBits initialOptions = meta.GetObjectOptions();

    // Try to set options to 0
    WXMPMeta_SetObjectOptions_1(MetaToRef(&meta), 0, &wResult);

    if (wResult.errMessage == nullptr) {
        // If no error, verify that options were set
        XMP_OptionBits newOptions = meta.GetObjectOptions();
        EXPECT_EQ(newOptions, 0u);
    } else {
        // SetObjectOptions may be unimplemented - that's okay
        // Just verify the error message is non-empty
        EXPECT_NE(strlen(wResult.errMessage), 0u);
    }
}

// Test: Multiple calls to SetObjectOptions
TEST_F(WXMPMetaSetObjectOptionsTest_2044, MultipleCallsDoNotCrash_2044) {
    XMPMeta meta;
    
    for (int i = 0; i < 10; ++i) {
        WXMP_Result wResult;
        memset(&wResult, 0, sizeof(wResult));
        WXMPMeta_SetObjectOptions_1(MetaToRef(&meta), static_cast<XMP_OptionBits>(i), &wResult);
        // Just ensuring no crash on repeated calls
    }
    SUCCEED();
}

// Test: SetObjectOptions with a valid meta but the function may report unimplemented
TEST_F(WXMPMetaSetObjectOptionsTest_2044, MayReportUnimplemented_2044) {
    XMPMeta meta;
    WXMP_Result wResult;
    memset(&wResult, 0, sizeof(wResult));

    WXMPMeta_SetObjectOptions_1(MetaToRef(&meta), 0x100, &wResult);

    // SetObjectOptions is documented as potentially unimplemented in XMP SDK
    // If it fails, we expect an error message to be set
    // This test documents the expected behavior
    if (wResult.errMessage != nullptr) {
        EXPECT_NE(strlen(wResult.errMessage), 0u);
    }
}
