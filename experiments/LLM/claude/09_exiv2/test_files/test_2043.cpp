#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_GetObjectOptions_1(XMPMetaRef xmpRef, WXMP_Result* wResult);

class WXMPMetaGetObjectOptionsTest_2043 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test: Normal operation with a freshly created XMPMeta object
// A new XMPMeta object should return default options (typically 0)
TEST_F(WXMPMetaGetObjectOptionsTest_2043, DefaultObjectOptionsReturnsZero_2043) {
    XMPMeta meta;
    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&meta);
    WXMP_Result wResult;

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Result structure is properly initialized before call
TEST_F(WXMPMetaGetObjectOptionsTest_2043, ResultStructureProperlyPopulated_2043) {
    XMPMeta meta;
    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&meta);
    WXMP_Result wResult;

    // Ensure result is in known state
    wResult.int32Result = 0xDEADBEEF;
    wResult.errMessage = nullptr;

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult);

    // After the call, int32Result should be set to the actual options
    // (not the garbage value we set)
    EXPECT_EQ(wResult.errMessage, nullptr);
    // For a default-constructed XMPMeta, options should be 0
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Multiple calls return consistent results
TEST_F(WXMPMetaGetObjectOptionsTest_2043, MultipleCallsReturnConsistentResults_2043) {
    XMPMeta meta;
    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&meta);

    WXMP_Result wResult1;
    WXMP_Result wResult2;

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult1);
    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult2);

    EXPECT_EQ(wResult1.int32Result, wResult2.int32Result);
    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
}

// Test: Null XMPMetaRef should result in an error message in wResult
TEST_F(WXMPMetaGetObjectOptionsTest_2043, NullXmpRefSetsErrorMessage_2043) {
    WXMP_Result wResult;

    WXMPMeta_GetObjectOptions_1(nullptr, &wResult);

    // When a null reference is passed, the wrapper should catch the error
    // and set errMessage to a non-null error string
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Different XMPMeta objects return their own options independently
TEST_F(WXMPMetaGetObjectOptionsTest_2043, DifferentObjectsReturnIndependentOptions_2043) {
    XMPMeta meta1;
    XMPMeta meta2;
    XMPMetaRef xmpRef1 = reinterpret_cast<XMPMetaRef>(&meta1);
    XMPMetaRef xmpRef2 = reinterpret_cast<XMPMetaRef>(&meta2);

    WXMP_Result wResult1;
    WXMP_Result wResult2;

    WXMPMeta_GetObjectOptions_1(xmpRef1, &wResult1);
    WXMPMeta_GetObjectOptions_1(xmpRef2, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    // Both default-constructed, so should have same default options
    EXPECT_EQ(wResult1.int32Result, wResult2.int32Result);
}

// Test: GetObjectOptions after setting properties on the metadata object
TEST_F(WXMPMetaGetObjectOptionsTest_2043, OptionsAfterSettingProperty_2043) {
    XMPMeta meta;

    // Set a property to modify the metadata state
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&meta);
    WXMP_Result wResult;

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    // The function should still return valid options (exact value depends on implementation)
    // We just verify no error occurred
}

// Test: GetObjectOptions after erasing the metadata object
TEST_F(WXMPMetaGetObjectOptionsTest_2043, OptionsAfterErase_2043) {
    XMPMeta meta;

    // Add then erase
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);
    meta.Erase();

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&meta);
    WXMP_Result wResult;

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    // After erase, options should be back to default
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}
