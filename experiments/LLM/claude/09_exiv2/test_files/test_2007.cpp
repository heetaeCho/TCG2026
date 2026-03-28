#include <gtest/gtest.h>
#include <string>

// XMP SDK headers
#define XMP_INCLUDE_XMPFILES 0
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_GetArrayItem_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_Index itemIndex,
    XMP_StringPtr * itemValue,
    XMP_StringLen * valueSize,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaGetArrayItemTest_2007 : public ::testing::Test {
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

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaGetArrayItemTest_2007, NullSchemaThrowsBadSchema_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), nullptr, "arrayName", 1,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPMetaGetArrayItemTest_2007, EmptySchemaThrowsBadSchema_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), "", "arrayName", 1,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null arrayName should produce an error
TEST_F(WXMPMetaGetArrayItemTest_2007, NullArrayNameThrowsBadXPath_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), "http://ns.example.com/", nullptr, 1,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty arrayName should produce an error
TEST_F(WXMPMetaGetArrayItemTest_2007, EmptyArrayNameThrowsBadXPath_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), "http://ns.example.com/", "", 1,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Getting item from non-existent array returns not found
TEST_F(WXMPMetaGetArrayItemTest_2007, NonExistentArrayReturnsNotFound_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), "http://ns.example.com/test/", "nonExistent", 1,
                             &itemValue, &valueSize, &options, &wResult);

    // Either error or not found
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, 0u);
    }
}

// Test: Null output pointers should not crash (uses void defaults)
TEST_F(WXMPMetaGetArrayItemTest_2007, NullOutputPointersDoNotCrash_2007) {
    WXMP_Result wResult;

    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), "http://ns.example.com/test/", "arr", 1,
                             nullptr, nullptr, nullptr, &wResult);

    // Should not crash; may return not-found or error
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, 0u);
    }
}

// Test: Existing array item returns found with correct value
TEST_F(WXMPMetaGetArrayItemTest_2007, ExistingArrayItemReturnsFound_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* ns = "http://ns.example.com/test/";
    XMPMeta::RegisterNamespace(ns, "test");

    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "value1", 0);

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), ns, "myArray", 1,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    ASSERT_NE(itemValue, nullptr);
    EXPECT_STREQ(itemValue, "value1");
    EXPECT_EQ(valueSize, 6u);
}

// Test: Multiple array items, retrieve second item
TEST_F(WXMPMetaGetArrayItemTest_2007, GetSecondArrayItem_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* ns = "http://ns.example.com/test/";
    XMPMeta::RegisterNamespace(ns, "test");

    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "first", 0);
    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "second", 0);

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), ns, "myArray", 2,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    ASSERT_NE(itemValue, nullptr);
    EXPECT_STREQ(itemValue, "second");
}

// Test: Out-of-range index returns not found or error
TEST_F(WXMPMetaGetArrayItemTest_2007, OutOfRangeIndexReturnsError_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* ns = "http://ns.example.com/test/";
    XMPMeta::RegisterNamespace(ns, "test");

    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "only", 0);

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), ns, "myArray", 5,
                             &itemValue, &valueSize, &options, &wResult);

    // Should be not found or error
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, 0u);
    }
}

// Test: WXMP_Result is properly initialized when no error
TEST_F(WXMPMetaGetArrayItemTest_2007, ResultProperlyInitialized_2007) {
    WXMP_Result wResult;

    const char* ns = "http://ns.example.com/test/";
    XMPMeta::RegisterNamespace(ns, "test");

    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "item", 0);

    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), ns, "myArray", 1,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_TRUE(wResult.int32Result != 0);
}

// Test: Index 0 behavior
TEST_F(WXMPMetaGetArrayItemTest_2007, IndexZeroBehavior_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* ns = "http://ns.example.com/test/";
    XMPMeta::RegisterNamespace(ns, "test");

    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "val", 0);

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), ns, "myArray", 0,
                             &itemValue, &valueSize, &options, &wResult);

    // Index 0 may be invalid - just check it doesn't crash
    // It could return an error or not found
}

// Test: Negative index (kXMP_ArrayLastItem) behavior
TEST_F(WXMPMetaGetArrayItemTest_2007, LastItemIndex_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* ns = "http://ns.example.com/test/";
    XMPMeta::RegisterNamespace(ns, "test");

    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "first", 0);
    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "last", 0);

    // kXMP_ArrayLastItem is typically -1
    WXMPMeta_GetArrayItem_1(MetaToRef(meta), ns, "myArray", kXMP_ArrayLastItem,
                             &itemValue, &valueSize, &options, &wResult);

    if (wResult.errMessage == nullptr && wResult.int32Result != 0) {
        ASSERT_NE(itemValue, nullptr);
        EXPECT_STREQ(itemValue, "last");
    }
}

// Test: Empty value in array item
TEST_F(WXMPMetaGetArrayItemTest_2007, EmptyValueArrayItem_2007) {
    WXMP_Result wResult;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* ns = "http://ns.example.com/test/";
    XMPMeta::RegisterNamespace(ns, "test");

    meta->AppendArrayItem(ns, "myArray", kXMP_PropValueIsArray, "", 0);

    WXMPMeta_GetArrayItem_1(MetaToRef(meta), ns, "myArray", 1,
                             &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    ASSERT_NE(itemValue, nullptr);
    EXPECT_STREQ(itemValue, "");
    EXPECT_EQ(valueSize, 0u);
}
