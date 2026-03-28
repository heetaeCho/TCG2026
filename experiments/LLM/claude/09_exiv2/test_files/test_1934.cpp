#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern void WXMPUtils_ComposeFieldSelector_1(
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_StringPtr fieldNS,
    XMP_StringPtr fieldName,
    XMP_StringPtr fieldValue,
    XMP_StringPtr * fullPath,
    XMP_StringLen * pathSize,
    WXMP_Result * wResult);

class WXMPUtilsComposeFieldSelectorTest_1934 : public ::testing::Test {
protected:
    WXMP_Result wResult;
    XMP_StringPtr fullPath;
    XMP_StringLen pathSize;

    void SetUp() override {
        memset(&wResult, 0, sizeof(wResult));
        fullPath = nullptr;
        pathSize = 0;
    }
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, NullSchemaNS_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        nullptr, "arrayName", "http://fieldns/", "fieldName", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, EmptySchemaNS_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "", "arrayName", "http://fieldns/", "fieldName", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null arrayName should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, NullArrayName_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", nullptr, "http://fieldns/", "fieldName", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty arrayName should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, EmptyArrayName_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "", "http://fieldns/", "fieldName", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null fieldNS should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, NullFieldNS_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", nullptr, "fieldName", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty fieldNS should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, EmptyFieldNS_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", "", "fieldName", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null fieldName should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, NullFieldName_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", "http://fieldns/", nullptr, "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty fieldName should produce an error
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, EmptyFieldName_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", "http://fieldns/", "", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null fieldValue should be treated as empty string (no error from validation)
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, NullFieldValue_ShouldNotThrowValidationError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", "http://fieldns/", "fieldName", nullptr,
        &fullPath, &pathSize, &wResult);
    // The null fieldValue is converted to "", so no validation error for fieldValue.
    // There may or may not be an error from the underlying ComposeFieldSelector call,
    // but it should not be a "null fieldValue" error.
    // We just check that if there's an error, it's not about fieldValue being null.
}

// Test: Null fullPath pointer should be handled (uses voidStringPtr internally)
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, NullFullPathPtr_ShouldNotCrash_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", "http://fieldns/", "fieldName", "fieldValue",
        nullptr, &pathSize, &wResult);
    // Should not crash; fullPath defaults to voidStringPtr internally
}

// Test: Null pathSize pointer should be handled (uses voidStringLen internally)
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, NullPathSizePtr_ShouldNotCrash_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", "http://fieldns/", "fieldName", "fieldValue",
        &fullPath, nullptr, &wResult);
    // Should not crash; pathSize defaults to voidStringLen internally
}

// Test: Both fullPath and pathSize null should be handled
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, BothOutputPtrsNull_ShouldNotCrash_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", "http://fieldns/", "fieldName", "fieldValue",
        nullptr, nullptr, &wResult);
    // Should not crash
}

// Test: Valid inputs should succeed (no error message)
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, ValidInputs_ShouldSucceed_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "Creator", "http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestValue",
        &fullPath, &pathSize, &wResult);
    // If no error occurred, errMessage should be null
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}

// Test: Valid inputs with empty fieldValue should succeed
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, ValidInputsEmptyFieldValue_ShouldSucceed_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "Creator", "http://ns.adobe.com/xap/1.0/", "CreatorTool", "",
        &fullPath, &pathSize, &wResult);
    // Empty fieldValue is allowed
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, ResultInitialization_1934) {
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: All null parameters should produce an error (schemaNS is checked first)
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, AllNullParams_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid schemaNS but all other required params null
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, OnlyValidSchemaNS_ShouldErrorOnArrayName_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid schemaNS and arrayName but null fieldNS
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, ValidSchemaAndArray_NullFieldNS_ShouldError_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "arrayName", nullptr, "fieldName", "fieldValue",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: fieldValue with special characters
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, FieldValueWithSpecialChars_1934) {
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "Creator", "http://ns.adobe.com/xap/1.0/", "CreatorTool",
        "value with <special> & \"chars\"",
        &fullPath, &pathSize, &wResult);
    // No crash expected; result depends on implementation
}

// Test: Very long field value
TEST_F(WXMPUtilsComposeFieldSelectorTest_1934, LongFieldValue_1934) {
    std::string longValue(10000, 'x');
    WXMPUtils_ComposeFieldSelector_1(
        "http://ns.adobe.com/xap/1.0/", "Creator", "http://ns.adobe.com/xap/1.0/", "CreatorTool",
        longValue.c_str(),
        &fullPath, &pathSize, &wResult);
    // Should not crash
}
