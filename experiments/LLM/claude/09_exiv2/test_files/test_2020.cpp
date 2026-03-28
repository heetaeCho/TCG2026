#include <gtest/gtest.h>
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DoesArrayItemExist_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_Index itemIndex,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaDoesArrayItemExistTest_2020 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        memset(&result, 0, sizeof(result));
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    WXMP_Result result;
};

// Test: Null schema namespace should set error message
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, NullSchemaNS_SetsError_2020) {
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), nullptr, "arrayName", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty schema namespace should set error message
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, EmptySchemaNS_SetsError_2020) {
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), "", "arrayName", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null array name should set error message
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, NullArrayName_SetsError_2020) {
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), "http://ns.example.com/", nullptr, 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty array name should set error message
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, EmptyArrayName_SetsError_2020) {
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), "http://ns.example.com/", "", 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Non-existent array item returns false (0)
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, NonExistentArrayItem_ReturnsFalse_2020) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), "http://ns.example.com/test/", "TestArray", 1, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Existing array item returns true (1)
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, ExistingArrayItem_ReturnsTrue_2020) {
    const char* ns = "http://ns.example.com/test2/";
    XMPMeta::RegisterNamespace(ns, "test2");
    meta->AppendArrayItem(ns, "MyArray", kXMP_PropArrayIsOrdered, "ItemValue", 0);
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), ns, "MyArray", 1, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Out of range index returns false
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, OutOfRangeIndex_ReturnsFalse_2020) {
    const char* ns = "http://ns.example.com/test3/";
    XMPMeta::RegisterNamespace(ns, "test3");
    meta->AppendArrayItem(ns, "MyArray", kXMP_PropArrayIsOrdered, "ItemValue", 0);
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), ns, "MyArray", 5, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Index 0 on empty array returns false
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, IndexZeroOnNonExistentArray_ReturnsFalse_2020) {
    const char* ns = "http://ns.example.com/test4/";
    XMPMeta::RegisterNamespace(ns, "test4");
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), ns, "SomeArray", 0, &result);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Multiple items, check second item exists
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, MultipleItems_SecondExists_2020) {
    const char* ns = "http://ns.example.com/test5/";
    XMPMeta::RegisterNamespace(ns, "test5");
    meta->AppendArrayItem(ns, "Arr", kXMP_PropArrayIsOrdered, "First", 0);
    meta->AppendArrayItem(ns, "Arr", kXMP_PropArrayIsOrdered, "Second", 0);
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), ns, "Arr", 2, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Result struct is properly initialized with no error on valid call
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, ValidCall_NoError_2020) {
    const char* ns = "http://ns.example.com/test6/";
    XMPMeta::RegisterNamespace(ns, "test6");
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), ns, "NonExistent", 1, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Negative index on non-existent array
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, NegativeIndex_ReturnsFalse_2020) {
    const char* ns = "http://ns.example.com/test7/";
    XMPMeta::RegisterNamespace(ns, "test7");
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), ns, "SomeArr", -1, &result);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Both schema and array name are null
TEST_F(WXMPMetaDoesArrayItemExistTest_2020, BothNull_SetsError_2020) {
    WXMPMeta_DoesArrayItemExist_1(MetaToRef(meta), nullptr, nullptr, 1, &result);
    EXPECT_NE(result.errMessage, nullptr);
}
