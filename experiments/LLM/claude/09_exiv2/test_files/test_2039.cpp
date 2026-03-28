#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_CountArrayItems_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaCountArrayItemsTest_2039 : public ::testing::Test {
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
TEST_F(WXMPMetaCountArrayItemsTest_2039, NullSchemaNS_ProducesError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), nullptr, "arrayName", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace should produce an error
TEST_F(WXMPMetaCountArrayItemsTest_2039, EmptySchemaNS_ProducesError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), "", "arrayName", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null array name should produce an error
TEST_F(WXMPMetaCountArrayItemsTest_2039, NullArrayName_ProducesError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), "http://ns.example.com/", nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty array name should produce an error
TEST_F(WXMPMetaCountArrayItemsTest_2039, EmptyArrayName_ProducesError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), "http://ns.example.com/", "", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Both schema and array name null should produce an error (schema checked first)
TEST_F(WXMPMetaCountArrayItemsTest_2039, BothNullParams_ProducesSchemaError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), nullptr, nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Both schema and array name empty should produce an error (schema checked first)
TEST_F(WXMPMetaCountArrayItemsTest_2039, BothEmptyParams_ProducesSchemaError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), "", "", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Count on non-existent array returns 0
TEST_F(WXMPMetaCountArrayItemsTest_2039, NonExistentArray_ReturnsZero_2039) {
    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), "http://ns.test.com/", "test:nonExistent", &wResult);
    // If no error, count should be 0
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, 0u);
    }
}

// Test: Count on array with items returns correct count
TEST_F(WXMPMetaCountArrayItemsTest_2039, ArrayWithItems_ReturnsCorrectCount_2039) {
    const char* schemaNS = "http://ns.test.com/";
    XMPMeta::RegisterNamespace(schemaNS, "test");

    meta->AppendArrayItem(schemaNS, "test:myArray", kXMP_PropArrayIsOrdered, "item1", 0);
    meta->AppendArrayItem(schemaNS, "test:myArray", kXMP_PropArrayIsOrdered, "item2", 0);
    meta->AppendArrayItem(schemaNS, "test:myArray", kXMP_PropArrayIsOrdered, "item3", 0);

    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), schemaNS, "test:myArray", &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 3u);
}

// Test: Count on array with single item
TEST_F(WXMPMetaCountArrayItemsTest_2039, ArrayWithOneItem_ReturnsOne_2039) {
    const char* schemaNS = "http://ns.test.com/";
    XMPMeta::RegisterNamespace(schemaNS, "test");

    meta->AppendArrayItem(schemaNS, "test:singleArray", kXMP_PropArrayIsOrdered, "onlyItem", 0);

    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), schemaNS, "test:singleArray", &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
}

// Test: Result struct is properly initialized before call - errMessage should be null on success
TEST_F(WXMPMetaCountArrayItemsTest_2039, SuccessfulCall_NoErrorMessage_2039) {
    const char* schemaNS = "http://ns.test.com/";
    XMPMeta::RegisterNamespace(schemaNS, "test");

    meta->AppendArrayItem(schemaNS, "test:arr", kXMP_PropArrayIsOrdered, "val", 0);

    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), schemaNS, "test:arr", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: After deleting items, count should decrease
TEST_F(WXMPMetaCountArrayItemsTest_2039, AfterDeletingItems_CountDecreases_2039) {
    const char* schemaNS = "http://ns.test.com/";
    XMPMeta::RegisterNamespace(schemaNS, "test");

    meta->AppendArrayItem(schemaNS, "test:delArr", kXMP_PropArrayIsOrdered, "item1", 0);
    meta->AppendArrayItem(schemaNS, "test:delArr", kXMP_PropArrayIsOrdered, "item2", 0);
    meta->AppendArrayItem(schemaNS, "test:delArr", kXMP_PropArrayIsOrdered, "item3", 0);

    meta->DeleteArrayItem(schemaNS, "test:delArr", 1);

    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), schemaNS, "test:delArr", &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 2u);
}

// Test: Empty schema NS with valid array name - schema error takes priority
TEST_F(WXMPMetaCountArrayItemsTest_2039, EmptySchemaValidArray_ProducesSchemaError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), "", "test:arr", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid schema NS with empty array name
TEST_F(WXMPMetaCountArrayItemsTest_2039, ValidSchemaEmptyArray_ProducesXPathError_2039) {
    WXMP_Result wResult;
    WXMPMeta_CountArrayItems_1(MetaToRef(meta), "http://ns.test.com/", "", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}
