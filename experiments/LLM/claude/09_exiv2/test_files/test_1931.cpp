#include <gtest/gtest.h>
#include <string>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_ComposeStructFieldPath_1(
    XMP_StringPtr schemaNS,
    XMP_StringPtr structName,
    XMP_StringPtr fieldNS,
    XMP_StringPtr fieldName,
    XMP_StringPtr * fullPath,
    XMP_StringLen * pathSize,
    WXMP_Result * wResult);

class WXMPUtilsComposeStructFieldPathTest_1931 : public ::testing::Test {
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
// Normal operation tests
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, ValidInputsProduceNoError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error for valid inputs";
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, ValidInputsProduceNonEmptyPath_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, NullFullPathDoesNotCrash_1931) {
    // fullPath is null, should use internal voidStringPtr
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        nullptr,
        &pathSize,
        &wResult);

    // Should still succeed
    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error when fullPath is null";
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, NullPathSizeDoesNotCrash_1931) {
    // pathSize is null, should use internal voidStringLen
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        nullptr,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error when pathSize is null";
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, BothFullPathAndPathSizeNull_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        nullptr,
        nullptr,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error when both output params are null";
}

// =============================================================================
// Error cases: Empty or null schemaNS
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, NullSchemaNamespaceReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        nullptr,
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for null schemaNS";
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptySchemaNamespaceReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for empty schemaNS";
}

// =============================================================================
// Error cases: Empty or null structName
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, NullStructNameReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        nullptr,
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for null structName";
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptyStructNameReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for empty structName";
}

// =============================================================================
// Error cases: Empty or null fieldNS
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, NullFieldNamespaceReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        nullptr,
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for null fieldNS";
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptyFieldNamespaceReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for empty fieldNS";
}

// =============================================================================
// Error cases: Empty or null fieldName
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, NullFieldNameReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        nullptr,
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for null fieldName";
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptyFieldNameReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for empty fieldName";
}

// =============================================================================
// Error cases: All null parameters
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, AllNullInputsReturnsError_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr) << "Expected error for all null inputs";
}

// =============================================================================
// Boundary: Different namespace URIs for schema and field
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, DifferentNamespacesForSchemaAndField_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/photoshop/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error for different but valid namespaces";
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}

// =============================================================================
// Verify WXMP_Result is properly initialized before use
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, ResultInitiallyHasNoError_1931) {
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// =============================================================================
// Multiple calls should each produce independent results
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, MultipleCallsWorkIndependently_1931) {
    // First call - valid
    XMP_StringPtr fullPath1 = nullptr;
    XMP_StringLen pathSize1 = 0;
    WXMP_Result wResult1;

    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:StructA",
        "http://ns.adobe.com/xap/1.0/",
        "FieldA",
        &fullPath1,
        &pathSize1,
        &wResult1);

    // Second call - also valid but with different names
    XMP_StringPtr fullPath2 = nullptr;
    XMP_StringLen pathSize2 = 0;
    WXMP_Result wResult2;

    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:StructB",
        "http://ns.adobe.com/xap/1.0/",
        "FieldB",
        &fullPath2,
        &pathSize2,
        &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
}

// =============================================================================
// Error then success: ensure error state doesn't persist
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, ErrorThenSuccessRecovers_1931) {
    // First call - invalid (empty schemaNS)
    WXMP_Result wResult1;
    WXMPUtils_ComposeStructFieldPath_1(
        "",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult1);

    EXPECT_NE(wResult1.errMessage, nullptr) << "First call should fail";

    // Second call - valid
    WXMP_Result wResult2;
    XMP_StringPtr fullPath2 = nullptr;
    XMP_StringLen pathSize2 = 0;

    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath2,
        &pathSize2,
        &wResult2);

    EXPECT_EQ(wResult2.errMessage, nullptr) << "Second call should succeed";
}

// =============================================================================
// Boundary: Single character names
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, SingleCharacterNames_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "x",
        "y",
        "z",
        "w",
        &fullPath,
        &pathSize,
        &wResult);

    // This may or may not succeed depending on whether single-char URIs are valid.
    // We're just ensuring it doesn't crash and returns a consistent result.
    // The result will either be an error or a valid path.
    // No assertion on success/failure since it depends on internal validation.
}

// =============================================================================
// Verify error message content hints at the right issue
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptySchemaNSErrorMessageMentionsSchema_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    ASSERT_NE(wResult.errMessage, nullptr);
    std::string errMsg(wResult.errMessage);
    // The error message should mention "schema" based on the code
    EXPECT_NE(errMsg.find("schema"), std::string::npos)
        << "Error message should reference schema: " << errMsg;
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptyStructNameErrorMessageMentionsStruct_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    ASSERT_NE(wResult.errMessage, nullptr);
    std::string errMsg(wResult.errMessage);
    EXPECT_NE(errMsg.find("struct"), std::string::npos)
        << "Error message should reference struct: " << errMsg;
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptyFieldNSErrorMessageMentionsField_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    ASSERT_NE(wResult.errMessage, nullptr);
    std::string errMsg(wResult.errMessage);
    // The error message should mention "field" based on the code
    EXPECT_NE(errMsg.find("field"), std::string::npos)
        << "Error message should reference field: " << errMsg;
}

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, EmptyFieldNameErrorMessageMentionsField_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "",
        &fullPath,
        &pathSize,
        &wResult);

    ASSERT_NE(wResult.errMessage, nullptr);
    std::string errMsg(wResult.errMessage);
    EXPECT_NE(errMsg.find("field"), std::string::npos)
        << "Error message should reference field: " << errMsg;
}

// =============================================================================
// Verify pathSize matches string length of fullPath
// =============================================================================

TEST_F(WXMPUtilsComposeStructFieldPathTest_1931, PathSizeMatchesStringLength_1931) {
    WXMPUtils_ComposeStructFieldPath_1(
        "http://ns.adobe.com/xap/1.0/",
        "xmp:SomeStruct",
        "http://ns.adobe.com/xap/1.0/",
        "FieldName",
        &fullPath,
        &pathSize,
        &wResult);

    if (wResult.errMessage == nullptr && fullPath != nullptr) {
        EXPECT_EQ(pathSize, std::strlen(fullPath))
            << "pathSize should match the actual string length of fullPath";
    }
}
