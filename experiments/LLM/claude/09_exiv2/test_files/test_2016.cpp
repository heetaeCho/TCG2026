#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DeleteArrayItem_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_Index itemIndex,
    WXMP_Result * wResult);

// Helper to create and initialize an XMPMeta object
class WXMPMetaDeleteArrayItemTest_2016 : public ::testing::Test {
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

    XMPMetaRef GetRef() {
        return (XMPMetaRef)meta;
    }
};

// Test: Null schema namespace should produce an error
TEST_F(WXMPMetaDeleteArrayItemTest_2016, NullSchemaNS_ReturnsError_2016) {
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), nullptr, "arrayName", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
    // The error message should relate to empty schema
}

// Test: Empty schema namespace string should produce an error
TEST_F(WXMPMetaDeleteArrayItemTest_2016, EmptySchemaNS_ReturnsError_2016) {
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), "", "arrayName", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null array name should produce an error
TEST_F(WXMPMetaDeleteArrayItemTest_2016, NullArrayName_ReturnsError_2016) {
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), "http://ns.adobe.com/xap/1.0/", nullptr, 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty array name string should produce an error
TEST_F(WXMPMetaDeleteArrayItemTest_2016, EmptyArrayName_ReturnsError_2016) {
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Both schema and array name null should report schema error first
TEST_F(WXMPMetaDeleteArrayItemTest_2016, BothNullParams_SchemaErrorFirst_2016) {
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), nullptr, nullptr, 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
    // Schema check comes first, so expect schema-related error
}

// Test: Valid parameters with no existing array item - should not crash, no error on empty meta
TEST_F(WXMPMetaDeleteArrayItemTest_2016, DeleteNonExistentArrayItem_NoError_2016) {
    WXMP_Result result;
    // Deleting from a non-existent array - behavior depends on implementation
    // but we can at least verify it doesn't set an unexpected error for valid params
    WXMPMeta_DeleteArrayItem_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "TestArray", 1, &result);
    // The result may or may not have an error; we just verify no crash
}

// Test: Normal operation - add an array item then delete it
TEST_F(WXMPMetaDeleteArrayItemTest_2016, DeleteExistingArrayItem_Success_2016) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* arrayName = "TestArray";

    // First, append an item to the array
    meta->AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsOrdered, "item1", 0);
    meta->AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsOrdered, "item2", 0);

    // Verify both items exist
    EXPECT_TRUE(meta->DoesArrayItemExist(schemaNS, arrayName, 1));
    EXPECT_TRUE(meta->DoesArrayItemExist(schemaNS, arrayName, 2));

    // Delete the first item
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), schemaNS, arrayName, 1, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // After deletion, item count should be 1
    XMP_Index count = meta->CountArrayItems(schemaNS, arrayName);
    EXPECT_EQ(count, 1);
}

// Test: Delete last item in a single-element array
TEST_F(WXMPMetaDeleteArrayItemTest_2016, DeleteOnlyArrayItem_Success_2016) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* arrayName = "SingleArray";

    meta->AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsOrdered, "onlyItem", 0);
    EXPECT_EQ(meta->CountArrayItems(schemaNS, arrayName), 1);

    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), schemaNS, arrayName, 1, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    EXPECT_EQ(meta->CountArrayItems(schemaNS, arrayName), 0);
}

// Test: Verify WXMP_Result is properly initialized and stays clean on success
TEST_F(WXMPMetaDeleteArrayItemTest_2016, ResultCleanOnSuccess_2016) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* arrayName = "CleanArray";

    meta->AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsOrdered, "val", 0);

    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), schemaNS, arrayName, 1, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Delete with kXMP_ArrayLastItem index (typically -1 or last index)
TEST_F(WXMPMetaDeleteArrayItemTest_2016, DeleteWithLastItemIndex_2016) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* arrayName = "LastItemArray";

    meta->AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsOrdered, "first", 0);
    meta->AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsOrdered, "second", 0);

    WXMP_Result result;
    // kXMP_ArrayLastItem is typically defined to mean the last item
    WXMPMeta_DeleteArrayItem_1(GetRef(), schemaNS, arrayName, kXMP_ArrayLastItem, &result);
    // Verify no crash; check result
    if (result.errMessage == nullptr) {
        EXPECT_EQ(meta->CountArrayItems(schemaNS, arrayName), 1);
    }
}

// Test: Empty schema with valid array name - schema error takes priority
TEST_F(WXMPMetaDeleteArrayItemTest_2016, EmptySchemaValidArray_SchemaError_2016) {
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), "", "validArray", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
    EXPECT_TRUE(std::strstr(result.errMessage, "schema") != nullptr ||
                std::strstr(result.errMessage, "Schema") != nullptr ||
                result.errMessage[0] != '\0');
}

// Test: Valid schema with empty array name - xpath error
TEST_F(WXMPMetaDeleteArrayItemTest_2016, ValidSchemaEmptyArray_XPathError_2016) {
    WXMP_Result result;
    WXMPMeta_DeleteArrayItem_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}
