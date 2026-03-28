#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_SetArrayItem_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_Index itemIndex,
    XMP_StringPtr itemValue,
    XMP_OptionBits options,
    WXMP_Result * wResult
);

class WXMPMetaSetArrayItemTest_2011 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = reinterpret_cast<XMPMetaRef>(meta);
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaSetArrayItemTest_2011, NullSchemaNS_ProducesError_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, nullptr, "arrayName", 1, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPMetaSetArrayItemTest_2011, EmptySchemaNS_ProducesError_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "", "arrayName", 1, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null arrayName should produce an error
TEST_F(WXMPMetaSetArrayItemTest_2011, NullArrayName_ProducesError_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", nullptr, 1, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty arrayName should produce an error
TEST_F(WXMPMetaSetArrayItemTest_2011, EmptyArrayName_ProducesError_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "", 1, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid parameters with existing array should succeed (no error)
TEST_F(WXMPMetaSetArrayItemTest_2011, ValidParamsWithExistingArray_NoError_2011) {
    // First, create an ordered array with one item
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "initialValue", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 1, "newValue", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // Verify the value was set
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 1, &itemValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "newValue");
}

// Test: Error message content for empty schema contains expected text
TEST_F(WXMPMetaSetArrayItemTest_2011, EmptySchemaNS_ErrorMessageContent_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "", "arrayName", 1, "value", 0, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // The error message should mention schema
    EXPECT_TRUE(std::strstr(wResult.errMessage, "schema") != nullptr || std::strstr(wResult.errMessage, "Schema") != nullptr);
}

// Test: Error message content for empty array name contains expected text
TEST_F(WXMPMetaSetArrayItemTest_2011, EmptyArrayName_ErrorMessageContent_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "", 1, "value", 0, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    EXPECT_TRUE(std::strstr(wResult.errMessage, "array") != nullptr || std::strstr(wResult.errMessage, "Empty") != nullptr);
}

// Test: Invalid index on an existing array should produce an error
TEST_F(WXMPMetaSetArrayItemTest_2011, InvalidIndex_ProducesError_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);

    WXMP_Result wResult;
    // Index 5 is out of bounds for a 1-item array
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 5, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Setting item on non-existent array should produce an error
TEST_F(WXMPMetaSetArrayItemTest_2011, NonExistentArray_ProducesError_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "NonExistentArray", 1, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Setting with kXMP_InsertBeforeItem option
TEST_F(WXMPMetaSetArrayItemTest_2011, InsertBeforeItem_NoError_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 0, "item2", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 1, "insertedBefore", kXMP_InsertBeforeItem, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting with kXMP_InsertAfterItem option
TEST_F(WXMPMetaSetArrayItemTest_2011, InsertAfterItem_NoError_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 0, "item2", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 1, "insertedAfter", kXMP_InsertAfterItem, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaSetArrayItemTest_2011, ResultInitialization_2011) {
    WXMP_Result wResult;
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting empty item value on existing array should succeed
TEST_F(WXMPMetaSetArrayItemTest_2011, EmptyItemValue_NoError_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 1, "", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting null item value on existing array
TEST_F(WXMPMetaSetArrayItemTest_2011, NullItemValue_NoError_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 1, nullptr, 0, &wResult);
    // Should either succeed or fail gracefully
    // The function doesn't validate itemValue, so it likely succeeds
}

// Test: Zero index should produce an error (indices are 1-based)
TEST_F(WXMPMetaSetArrayItemTest_2011, ZeroIndex_ProducesError_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 0, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Negative index should produce an error
TEST_F(WXMPMetaSetArrayItemTest_2011, NegativeIndex_ProducesError_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", -1, "value", 0, &wResult);
    // kXMP_ArrayLastItem is typically -1, so this might succeed
    // If it does, verify no error
}

// Test: Schema validation happens before array name validation
TEST_F(WXMPMetaSetArrayItemTest_2011, SchemaValidatedBeforeArrayName_2011) {
    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "", "", 1, "value", 0, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // Should report schema error first
    EXPECT_TRUE(std::strstr(wResult.errMessage, "schema") != nullptr || std::strstr(wResult.errMessage, "Schema") != nullptr);
}

// Test: Replacing value in multi-item array
TEST_F(WXMPMetaSetArrayItemTest_2011, ReplaceValueInMultiItemArray_2011) {
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", kXMP_PropValueIsArray, "item1", 0);
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 0, "item2", 0);
    meta->AppendArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 0, "item3", 0);

    WXMP_Result wResult;
    WXMPMeta_SetArrayItem_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "TestArray", 2, "replacedItem2", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 2, &itemValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "replacedItem2");

    // Verify other items unchanged
    found = meta->GetArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 1, &itemValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "item1");

    found = meta->GetArrayItem("http://ns.adobe.com/xap/1.0/", "TestArray", 3, &itemValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "item3");
}
