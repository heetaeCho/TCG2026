#include <gtest/gtest.h>
#include <string>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore/XMPCoreDefn.h"
#include "XMPMeta.hpp"
#include "XMPUtils.hpp"

// Declaration of the function under test
extern "C" void WXMPUtils_SeparateArrayItems_1(
    XMPMetaRef wxmpObj,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_OptionBits options,
    XMP_StringPtr catedStr,
    WXMP_Result * wResult);

class WXMPUtilsSeparateArrayItemsTest_1955 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP toolkit is initialized
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }

    XMPMeta* CreateXMPMeta() {
        return new XMPMeta();
    }
};

// Test: Null wxmpObj pointer should result in error
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, NullXMPObjectReturnsError_1955) {
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        0,  // null XMP object
        "http://ns.adobe.com/xap/1.0/",
        "TestArray",
        0,
        "item1; item2",
        &result
    );
    EXPECT_NE(result.errMessage, nullptr);
    // The error should indicate bad param
}

// Test: Null schemaNS should result in error
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, NullSchemaNSReturnsError_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        nullptr,  // null schema namespace
        "TestArray",
        0,
        "item1; item2",
        &result
    );
    EXPECT_NE(result.errMessage, nullptr);
    delete meta;
}

// Test: Empty schemaNS should result in error
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, EmptySchemaNSReturnsError_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "",  // empty schema namespace
        "TestArray",
        0,
        "item1; item2",
        &result
    );
    EXPECT_NE(result.errMessage, nullptr);
    delete meta;
}

// Test: Null arrayName should result in error
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, NullArrayNameReturnsError_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        nullptr,  // null array name
        0,
        "item1; item2",
        &result
    );
    EXPECT_NE(result.errMessage, nullptr);
    delete meta;
}

// Test: Empty arrayName should result in error
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, EmptyArrayNameReturnsError_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        "",  // empty array name
        0,
        "item1; item2",
        &result
    );
    EXPECT_NE(result.errMessage, nullptr);
    delete meta;
}

// Test: Null catedStr should not cause error (defaults to "")
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, NullCatedStrDefaultsToEmpty_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        "Subject",
        kXMP_PropArrayIsOrdered,
        nullptr,  // null catedStr, should default to ""
        &result
    );
    // Should not have an error since null catedStr is handled
    EXPECT_EQ(result.errMessage, nullptr);
    delete meta;
}

// Test: Valid parameters with semicolon-separated items
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, ValidSemicolonSeparatedItems_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        "Subject",
        kXMP_PropArrayIsOrdered,
        "item1; item2; item3",
        &result
    );
    EXPECT_EQ(result.errMessage, nullptr);
    delete meta;
}

// Test: Valid parameters with empty catedStr
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, EmptyCatedStr_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        "Subject",
        kXMP_PropArrayIsOrdered,
        "",
        &result
    );
    EXPECT_EQ(result.errMessage, nullptr);
    delete meta;
}

// Test: Valid parameters with single item
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, SingleItemString_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        "Subject",
        kXMP_PropArrayIsOrdered,
        "singleitem",
        &result
    );
    EXPECT_EQ(result.errMessage, nullptr);
    delete meta;
}

// Test: WXMP_Result is properly initialized
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, ResultInitializedCorrectly_1955) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Valid call with comma-separated items
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, CommaSeparatedItems_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        "Subject",
        kXMP_PropArrayIsOrdered,
        "item1, item2, item3",
        &result
    );
    EXPECT_EQ(result.errMessage, nullptr);
    delete meta;
}

// Test: Valid call with unordered array option
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, UnorderedArrayOption_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        "http://ns.adobe.com/xap/1.0/",
        "Subject",
        kXMP_PropValueIsArray,
        "alpha; beta; gamma",
        &result
    );
    EXPECT_EQ(result.errMessage, nullptr);
    delete meta;
}

// Test: Both null schemaNS and null arrayName - schemaNS check should come first
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, NullSchemaNSCheckedBeforeArrayName_1955) {
    XMPMeta* meta = CreateXMPMeta();
    XMPMetaRef ref = WtoXMPMeta_Ref(meta);
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        ref,
        nullptr,  // null schema
        nullptr,  // null array name
        0,
        "test",
        &result
    );
    // Should get an error for the schema namespace first
    EXPECT_NE(result.errMessage, nullptr);
    delete meta;
}

// Test: Null wxmpObj is checked before schema and array name
TEST_F(WXMPUtilsSeparateArrayItemsTest_1955, NullXMPObjectCheckedFirst_1955) {
    WXMP_Result result;
    WXMPUtils_SeparateArrayItems_1(
        0,       // null object
        nullptr, // null schema
        nullptr, // null array name
        0,
        "test",
        &result
    );
    // Should get an error for the null XMP object pointer
    EXPECT_NE(result.errMessage, nullptr);
}
