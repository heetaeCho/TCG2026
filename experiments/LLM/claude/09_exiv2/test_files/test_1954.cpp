#include <gtest/gtest.h>
#include <string>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore_Impl.hpp"
#include "XMPMeta.hpp"
#include "XMPUtils.hpp"

// Forward declaration of the function under test
extern void WXMPUtils_CatenateArrayItems_1(
    XMPMetaRef wxmpObj,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_StringPtr separator,
    XMP_StringPtr quotes,
    XMP_OptionBits options,
    XMP_StringPtr * catedStr,
    XMP_StringLen * catedLen,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef ToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPUtilsCatenateArrayItemsTest_1954 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP toolkit is initialized
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test: Null schema namespace should produce an error
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NullSchemaNS_ThrowsBadSchema_1954) {
    XMPMeta meta;
    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        nullptr,  // null schemaNS
        "arrayName",
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
    // Should report a BadSchema error
}

// Test: Empty schema namespace should produce an error
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, EmptySchemaNS_ThrowsBadSchema_1954) {
    XMPMeta meta;
    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "",  // empty schemaNS
        "arrayName",
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null array name should produce an error
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NullArrayName_ThrowsBadXPath_1954) {
    XMPMeta meta;
    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        nullptr,  // null arrayName
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty array name should produce an error
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, EmptyArrayName_ThrowsBadXPath_1954) {
    XMPMeta meta;
    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "",  // empty arrayName
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null separator defaults to "; "
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NullSeparator_DefaultsToSemicolonSpace_1954) {
    XMPMeta meta;
    // Set up a simple bag array with items
    meta.SetProperty("http://ns.example.com/", "testArray", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "testArray", kXMP_ArrayLastItem, "item1", 0);
    meta.SetArrayItem("http://ns.example.com/", "testArray", kXMP_ArrayLastItem, "item2", 0);

    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "testArray",
        nullptr,  // null separator -> defaults to "; "
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    // Should succeed
    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr && catedStr != nullptr) {
        std::string result(catedStr, catedLen);
        // Items should be separated by "; "
        EXPECT_NE(result.find("; "), std::string::npos);
    }
}

// Test: Null quotes defaults to double-quote character
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NullQuotes_DefaultsToDoubleQuote_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "testArray", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "testArray", kXMP_ArrayLastItem, "item1", 0);

    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "testArray",
        "; ",
        nullptr,  // null quotes -> defaults to "\""
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Null catedStr pointer should not crash (uses internal void pointer)
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NullCatedStr_DoesNotCrash_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "testArray", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "testArray", kXMP_ArrayLastItem, "item1", 0);

    WXMP_Result wResult;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "testArray",
        "; ",
        "\"",
        0,
        nullptr,  // null catedStr
        &catedLen,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Null catedLen pointer should not crash (uses internal void length)
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NullCatedLen_DoesNotCrash_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "testArray", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "testArray", kXMP_ArrayLastItem, "item1", 0);

    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "testArray",
        "; ",
        "\"",
        0,
        &catedStr,
        nullptr,  // null catedLen
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Normal operation with a valid bag array containing multiple items
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NormalOperation_MultipleBagItems_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "colors", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "colors", kXMP_ArrayLastItem, "red", 0);
    meta.SetArrayItem("http://ns.example.com/", "colors", kXMP_ArrayLastItem, "green", 0);
    meta.SetArrayItem("http://ns.example.com/", "colors", kXMP_ArrayLastItem, "blue", 0);

    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "colors",
        ", ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr && catedStr != nullptr) {
        std::string result(catedStr, catedLen);
        EXPECT_FALSE(result.empty());
        EXPECT_NE(result.find("red"), std::string::npos);
        EXPECT_NE(result.find("green"), std::string::npos);
        EXPECT_NE(result.find("blue"), std::string::npos);
    }
}

// Test: Normal operation with a single item array
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NormalOperation_SingleItem_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "single", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "single", kXMP_ArrayLastItem, "onlyone", 0);

    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "single",
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr && catedStr != nullptr) {
        std::string result(catedStr, catedLen);
        EXPECT_NE(result.find("onlyone"), std::string::npos);
    }
}

// Test: Both null catedStr and catedLen should not crash
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, BothNullOutputParams_DoesNotCrash_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "arr", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "arr", kXMP_ArrayLastItem, "val", 0);

    WXMP_Result wResult;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "arr",
        "; ",
        "\"",
        0,
        nullptr,
        nullptr,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Non-existent array name should handle gracefully (may produce empty or error)
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, NonExistentArray_HandlesGracefully_1954) {
    XMPMeta meta;

    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "nonexistent",
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    // Either succeeds with empty result or reports an error - just don't crash
    // The behavior depends on the implementation
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(catedLen, 0u);
    }
}

// Test: Custom separator is used
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, CustomSeparator_IsUsed_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "items", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "items", kXMP_ArrayLastItem, "A", 0);
    meta.SetArrayItem("http://ns.example.com/", "items", kXMP_ArrayLastItem, "B", 0);

    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "items",
        " | ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr && catedStr != nullptr) {
        std::string result(catedStr, catedLen);
        EXPECT_NE(result.find(" | "), std::string::npos);
        EXPECT_NE(result.find("A"), std::string::npos);
        EXPECT_NE(result.find("B"), std::string::npos);
    }
}

// Test: WXMP_Result is properly initialized on success
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, ResultInitialized_OnSuccess_1954) {
    XMPMeta meta;
    meta.SetProperty("http://ns.example.com/", "arr", nullptr, kXMP_PropValueIsArray);
    meta.SetArrayItem("http://ns.example.com/", "arr", kXMP_ArrayLastItem, "test", 0);

    WXMP_Result wResult;

    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "arr",
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: WXMP_Result errMessage is set on schema error
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, ResultHasError_OnBadSchema_1954) {
    XMPMeta meta;
    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "",  // empty -> error
        "arr",
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
    if (wResult.errMessage != nullptr) {
        std::string errMsg(wResult.errMessage);
        EXPECT_FALSE(errMsg.empty());
    }
}

// Test: WXMP_Result errMessage is set on bad xpath (empty array name)
TEST_F(WXMPUtilsCatenateArrayItemsTest_1954, ResultHasError_OnBadXPath_1954) {
    XMPMeta meta;
    WXMP_Result wResult;
    XMP_StringPtr catedStr = nullptr;
    XMP_StringLen catedLen = 0;

    WXMPUtils_CatenateArrayItems_1(
        ToRef(&meta),
        "http://ns.example.com/",
        "",  // empty -> error
        "; ",
        "\"",
        0,
        &catedStr,
        &catedLen,
        &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
    if (wResult.errMessage != nullptr) {
        std::string errMsg(wResult.errMessage);
        EXPECT_FALSE(errMsg.empty());
    }
}
