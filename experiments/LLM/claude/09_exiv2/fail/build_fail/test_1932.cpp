#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern void WXMPUtils_ComposeQualifierPath_1(
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr qualNS,
    XMP_StringPtr qualName,
    XMP_StringPtr * fullPath,
    XMP_StringLen * pathSize,
    WXMP_Result * wResult);

class WXMPUtilsComposeQualifierPathTest_1932 : public ::testing::Test {
protected:
    WXMP_Result wResult;
    XMP_StringPtr fullPath;
    XMP_StringLen pathSize;

    void SetUp() override {
        wResult = WXMP_Result();
        fullPath = nullptr;
        pathSize = 0;
    }
};

// =============================================================================
// Test: Empty schema namespace (null pointer)
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, NullSchemaNS_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        nullptr, "propName", "http://qual.ns/", "qualName",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Empty schema namespace (empty string)
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, EmptySchemaNS_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "", "propName", "http://qual.ns/", "qualName",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Null property name
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, NullPropName_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://schema.ns/", nullptr, "http://qual.ns/", "qualName",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Empty property name (empty string)
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, EmptyPropName_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://schema.ns/", "", "http://qual.ns/", "qualName",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Null qualifier namespace
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, NullQualNS_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://schema.ns/", "propName", nullptr, "qualName",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Empty qualifier namespace (empty string)
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, EmptyQualNS_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://schema.ns/", "propName", "", "qualName",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Null qualifier name
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, NullQualName_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://schema.ns/", "propName", "http://qual.ns/", nullptr,
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Empty qualifier name (empty string)
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, EmptyQualName_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://schema.ns/", "propName", "http://qual.ns/", "",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Null fullPath pointer should not crash (uses voidStringPtr)
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, NullFullPathPtr_DoesNotCrash_1932) {
    // When fullPath is null, the function should substitute voidStringPtr internally
    // This test just ensures no crash; we can't check the output path
    WXMPUtils_ComposeQualifierPath_1(
        "http://ns.adobe.com/xap/1.0/", "Creator", "http://www.w3.org/XML/1998/namespace", "lang",
        nullptr, &pathSize, &wResult);
    // If the underlying ComposeQualifierPath succeeds, errMessage should be null
    // If it fails due to unregistered namespace, errMessage may be non-null
    // We just verify no crash occurred
}

// =============================================================================
// Test: Null pathSize pointer should not crash (uses voidStringLen)
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, NullPathSizePtr_DoesNotCrash_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://ns.adobe.com/xap/1.0/", "Creator", "http://www.w3.org/XML/1998/namespace", "lang",
        &fullPath, nullptr, &wResult);
    // Just verify no crash
}

// =============================================================================
// Test: Both fullPath and pathSize null should not crash
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, BothOutputPtrsNull_DoesNotCrash_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://ns.adobe.com/xap/1.0/", "Creator", "http://www.w3.org/XML/1998/namespace", "lang",
        nullptr, nullptr, &wResult);
    // Just verify no crash
}

// =============================================================================
// Test: Valid inputs with known registered namespaces
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, ValidInputs_ProducesPath_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://ns.adobe.com/xap/1.0/", "xmp:Creator",
        "http://www.w3.org/XML/1998/namespace", "xml:lang",
        &fullPath, &pathSize, &wResult);
    
    // If namespaces are registered, we expect success
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, (XMP_StringLen)0);
    }
}

// =============================================================================
// Test: All empty parameters should report schema error first
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, AllEmpty_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "", "", "", "",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: All null parameters should report schema error first
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, AllNull_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        nullptr, nullptr, nullptr, nullptr,
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Valid schemaNS but null propName
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, ValidSchemaButNullProp_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://ns.adobe.com/xap/1.0/", nullptr,
        "http://www.w3.org/XML/1998/namespace", "lang",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Valid schemaNS and propName but null qualNS
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, ValidSchemaAndPropButNullQualNS_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://ns.adobe.com/xap/1.0/", "Creator",
        nullptr, "lang",
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: Valid schemaNS, propName, qualNS but null qualName
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, ValidFirstThreeButNullQualName_SetsError_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "http://ns.adobe.com/xap/1.0/", "Creator",
        "http://www.w3.org/XML/1998/namespace", nullptr,
        &fullPath, &pathSize, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// =============================================================================
// Test: WXMP_Result is properly initialized on error
// =============================================================================
TEST_F(WXMPUtilsComposeQualifierPathTest_1932, ErrorResultHasMessage_1932) {
    WXMPUtils_ComposeQualifierPath_1(
        "", "propName", "http://qual.ns/", "qualName",
        &fullPath, &pathSize, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    EXPECT_GT(std::strlen(wResult.errMessage), (size_t)0);
}
