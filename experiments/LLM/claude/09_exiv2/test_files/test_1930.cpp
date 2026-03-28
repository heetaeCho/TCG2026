#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore_Impl.hpp"
#include "XMPUtils.hpp"

// Declaration of the function under test
extern void WXMPUtils_ComposeArrayItemPath_1(
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_Index itemIndex,
    XMP_StringPtr * fullPath,
    XMP_StringLen * pathSize,
    WXMP_Result * wResult);

class WXMPUtilsComposeArrayItemPathTest_1930 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPUtils::Initialize();
    }

    void TearDown() override {
        // Terminate XMP toolkit if needed
        XMPUtils::Terminate();
    }

    WXMP_Result wResult;
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, NullSchemaNS_ShouldError_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        nullptr, "arrayName", 1, &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS string should produce an error
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, EmptySchemaNS_ShouldError_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "", "arrayName", 1, &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null arrayName should produce an error
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, NullArrayName_ShouldError_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.example.com/", nullptr, 1, &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty arrayName string should produce an error
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, EmptyArrayName_ShouldError_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.example.com/", "", 1, &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid inputs should succeed (no error message)
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, ValidInputs_ShouldSucceed_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 1, &fullPath, &pathSize, &wResult);
    // If no error, errMessage should be null
    EXPECT_EQ(wResult.errMessage, nullptr);
    // fullPath and pathSize should have been set
    EXPECT_NE(fullPath, nullptr);
    EXPECT_GT(pathSize, 0u);
}

// Test: Null fullPath pointer should not crash (uses voidStringPtr internally)
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, NullFullPathPointer_ShouldNotCrash_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 1, nullptr, &pathSize, &wResult);
    // Should still succeed or at least not crash
    // The function replaces null with voidStringPtr
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Null pathSize pointer should not crash (uses voidStringLen internally)
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, NullPathSizePointer_ShouldNotCrash_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 1, &fullPath, nullptr, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(fullPath, nullptr);
}

// Test: Both fullPath and pathSize null should not crash
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, BothOutputPointersNull_ShouldNotCrash_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 1, nullptr, nullptr, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Index of 0 (which typically means "last" in XMP) 
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, IndexZero_ShouldHandleSpecialCase_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 0, &fullPath, &pathSize, &wResult);
    // Index 0 may have special meaning (kXMP_ArrayLastItem), should not error
    // or may throw - just check it doesn't crash
    // Whether it errors depends on implementation
}

// Test: Positive index should produce a path containing the index
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, PositiveIndex_ShouldProducePath_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 3, &fullPath, &pathSize, &wResult);
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
        // The path should contain "[3]" for item index 3
        std::string pathStr(fullPath, pathSize);
        EXPECT_NE(pathStr.find("[3]"), std::string::npos);
    }
}

// Test: Negative index may represent special XMP indices (like kXMP_ArrayLastItem = -1)
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, NegativeIndex_BehaviorCheck_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", -1, &fullPath, &pathSize, &wResult);
    // -1 is kXMP_ArrayLastItem, should produce "xmp:Creator[last()]" or similar
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}

// Test: Item index 1 should produce expected path format
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, IndexOne_ProducesCorrectPath_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 1, &fullPath, &pathSize, &wResult);
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
        std::string pathStr(fullPath, pathSize);
        EXPECT_NE(pathStr.find("[1]"), std::string::npos);
    }
}

// Test: Large index value
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, LargeIndex_ShouldHandleGracefully_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator", 999999, &fullPath, &pathSize, &wResult);
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
        std::string pathStr(fullPath, pathSize);
        EXPECT_NE(pathStr.find("[999999]"), std::string::npos);
    }
}

// Test: Both schemaNS and arrayName null should produce error about schema
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, BothInputsNull_ShouldErrorOnSchema_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        nullptr, nullptr, 1, &fullPath, &pathSize, &wResult);
    // Should fail on schemaNS check first
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid schema but empty array name
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, ValidSchemaEmptyArray_ShouldError_1930) {
    WXMPUtils_ComposeArrayItemPath_1(
        "http://ns.adobe.com/xap/1.0/", "", 1, &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized
TEST_F(WXMPUtilsComposeArrayItemPathTest_1930, ResultInitialization_1930) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
}
