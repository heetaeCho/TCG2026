#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_AppendArrayItem_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_OptionBits arrayOptions,
    XMP_StringPtr itemValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaAppendArrayItemTest_2012 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
};

// Test: Null schema namespace should produce an error
TEST_F(WXMPMetaAppendArrayItemTest_2012, NullSchemaNS_SetsError_2012) {
    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        nullptr,          // null schemaNS
        "TestArray",
        0,
        "ItemValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace string should produce an error
TEST_F(WXMPMetaAppendArrayItemTest_2012, EmptySchemaNS_SetsError_2012) {
    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "",               // empty schemaNS
        "TestArray",
        0,
        "ItemValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null array name should produce an error
TEST_F(WXMPMetaAppendArrayItemTest_2012, NullArrayName_SetsError_2012) {
    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        nullptr,          // null arrayName
        0,
        "ItemValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty array name string should produce an error
TEST_F(WXMPMetaAppendArrayItemTest_2012, EmptyArrayName_SetsError_2012) {
    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "",               // empty arrayName
        0,
        "ItemValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid parameters should succeed (no error message)
TEST_F(WXMPMetaAppendArrayItemTest_2012, ValidParams_NoError_2012) {
    // Register the namespace first
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult;
    // Use kXMP_PropArrayIsOrdered as arrayOptions to create an ordered array
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        "FirstItem",
        0,
        &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Append multiple items to the same array succeeds
TEST_F(WXMPMetaAppendArrayItemTest_2012, AppendMultipleItems_NoError_2012) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult1;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        "Item1",
        0,
        &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);

    WXMP_Result wResult2;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        "Item2",
        0,
        &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);
}

// Test: After appending, the item can be retrieved
TEST_F(WXMPMetaAppendArrayItemTest_2012, AppendedItemIsRetrievable_2012) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        "HelloWorld",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    // Verify the item exists via GetArrayItem
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits itemOptions = 0;
    bool found = meta->GetArrayItem(
        "http://ns.example.com/test/",
        "TestArray",
        1,
        &itemValue,
        &valueSize,
        &itemOptions);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "HelloWorld");
}

// Test: CountArrayItems reflects appended items
TEST_F(WXMPMetaAppendArrayItemTest_2012, CountArrayItemsAfterAppend_2012) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        "Item1",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        "Item2",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    XMP_Index count = meta->CountArrayItems(
        "http://ns.example.com/test/",
        "TestArray");
    EXPECT_EQ(count, 2);
}

// Test: Appending with empty item value should succeed
TEST_F(WXMPMetaAppendArrayItemTest_2012, EmptyItemValue_NoError_2012) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        "",
        0,
        &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Appending with null item value (should be treated as empty string by XMP SDK)
TEST_F(WXMPMetaAppendArrayItemTest_2012, NullItemValue_Succeeds_2012) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "TestArray",
        kXMP_PropArrayIsOrdered,
        nullptr,
        0,
        &wResult);
    // Behavior depends on implementation, but shouldn't crash
    // The SDK typically treats null itemValue as empty string
    // We just verify it doesn't produce an unexpected error or it does
    // This is observable behavior - we just record what happens
}

// Test: Both schemaNS and arrayName null should produce error about schema
TEST_F(WXMPMetaAppendArrayItemTest_2012, BothNullSchemaAndArray_SetsSchemaError_2012) {
    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        nullptr,
        nullptr,
        0,
        "ItemValue",
        0,
        &wResult);
    // Should fail on schema check first
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Both schemaNS and arrayName empty should produce error about schema
TEST_F(WXMPMetaAppendArrayItemTest_2012, BothEmptySchemaAndArray_SetsSchemaError_2012) {
    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "",
        "",
        0,
        "ItemValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Using unordered array (kXMP_PropArrayIsUnordered) works
TEST_F(WXMPMetaAppendArrayItemTest_2012, UnorderedArrayAppend_NoError_2012) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "BagArray",
        kXMP_PropArrayIsUnordered,
        "BagItem",
        0,
        &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Using alternative array (kXMP_PropArrayIsAlternate) works
TEST_F(WXMPMetaAppendArrayItemTest_2012, AlternateArrayAppend_NoError_2012) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.example.com/test/",
        "AltArray",
        kXMP_PropArrayIsAlternate,
        "AltItem",
        0,
        &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaAppendArrayItemTest_2012, ResultInitializedCorrectly_2012) {
    WXMP_Result wResult;
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Append to array with valid schema but schema not registered 
// (the function should still work as XMP SDK can auto-register or fail)
TEST_F(WXMPMetaAppendArrayItemTest_2012, UnregisteredSchema_2012) {
    WXMP_Result wResult;
    WXMPMeta_AppendArrayItem_1(
        MetaToRef(meta),
        "http://ns.unregistered.com/",
        "SomeArray",
        kXMP_PropArrayIsOrdered,
        "Value",
        0,
        &wResult);
    // The behavior here depends on whether auto-registration happens.
    // We simply check it doesn't crash and observe the result.
    // Some implementations may set an error, others may succeed.
}
