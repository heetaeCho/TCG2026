#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetProperty_Int_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_Int32 * propValue,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

// Helper to create and initialize an XMPMeta object and get its ref
static XMPMetaRef CreateXMPMetaRef() {
    XMPMeta* meta = new XMPMeta();
    return (XMPMetaRef)meta;
}

static void DestroyXMPMetaRef(XMPMetaRef ref) {
    XMPMeta* meta = (XMPMeta*)ref;
    delete meta;
}

class WXMPMetaGetPropertyIntTest_2026 : public ::testing::Test {
protected:
    XMPMetaRef xmpRef;
    WXMP_Result wResult;

    void SetUp() override {
        // Ensure XMPMeta is initialized
        XMPMeta::Initialize();
        xmpRef = CreateXMPMetaRef();
        std::memset(&wResult, 0, sizeof(wResult));
    }

    void TearDown() override {
        DestroyXMPMetaRef(xmpRef);
    }
};

// Test: Null schema namespace should result in an error
TEST_F(WXMPMetaGetPropertyIntTest_2026, NullSchemaNS_ShouldSetError_2026) {
    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, nullptr, "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace should result in an error
TEST_F(WXMPMetaGetPropertyIntTest_2026, EmptySchemaNS_ShouldSetError_2026) {
    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, "", "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null property name should result in an error
TEST_F(WXMPMetaGetPropertyIntTest_2026, NullPropName_ShouldSetError_2026) {
    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, "http://ns.example.com/", nullptr, &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name should result in an error
TEST_F(WXMPMetaGetPropertyIntTest_2026, EmptyPropName_ShouldSetError_2026) {
    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, "http://ns.example.com/", "", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Non-existent property should return not found (int32Result == 0)
TEST_F(WXMPMetaGetPropertyIntTest_2026, NonExistentProperty_ShouldReturnNotFound_2026) {
    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    // Register namespace first
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMPMeta_GetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "NonExistent", &propValue, &options, &wResult);

    // Should succeed (no error) but not find the property
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Null propValue pointer should not crash (uses internal voidInt32)
TEST_F(WXMPMetaGetPropertyIntTest_2026, NullPropValue_ShouldNotCrash_2026) {
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.example.com/test2/", "test2");

    WXMPMeta_GetProperty_Int_1(xmpRef, "http://ns.example.com/test2/", "SomeProp", nullptr, &options, &wResult);

    // Should not crash; property likely not found
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Null options pointer should not crash (uses internal voidOptionBits)
TEST_F(WXMPMetaGetPropertyIntTest_2026, NullOptions_ShouldNotCrash_2026) {
    XMP_Int32 propValue = 0;

    XMPMeta::RegisterNamespace("http://ns.example.com/test3/", "test3");

    WXMPMeta_GetProperty_Int_1(xmpRef, "http://ns.example.com/test3/", "SomeProp", &propValue, nullptr, &wResult);

    // Should not crash; property likely not found
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Both propValue and options null should not crash
TEST_F(WXMPMetaGetPropertyIntTest_2026, BothNullOutputPointers_ShouldNotCrash_2026) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test4/", "test4");

    WXMPMeta_GetProperty_Int_1(xmpRef, "http://ns.example.com/test4/", "SomeProp", nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Set an integer property and then retrieve it
TEST_F(WXMPMetaGetPropertyIntTest_2026, ExistingIntProperty_ShouldReturnValue_2026) {
    const char* ns = "http://ns.example.com/inttest/";
    const char* propName = "IntProp";

    XMPMeta::RegisterNamespace(ns, "inttest");

    XMPMeta* meta = (XMPMeta*)xmpRef;
    meta->SetProperty_Int(ns, propName, 42, 0);

    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, ns, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));  // found
    EXPECT_EQ(propValue, 42);
}

// Test: Set a negative integer property and retrieve it
TEST_F(WXMPMetaGetPropertyIntTest_2026, NegativeIntProperty_ShouldReturnValue_2026) {
    const char* ns = "http://ns.example.com/negtest/";
    const char* propName = "NegProp";

    XMPMeta::RegisterNamespace(ns, "negtest");

    XMPMeta* meta = (XMPMeta*)xmpRef;
    meta->SetProperty_Int(ns, propName, -100, 0);

    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, ns, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
    EXPECT_EQ(propValue, -100);
}

// Test: Set zero integer property and retrieve it
TEST_F(WXMPMetaGetPropertyIntTest_2026, ZeroIntProperty_ShouldReturnValue_2026) {
    const char* ns = "http://ns.example.com/zerotest/";
    const char* propName = "ZeroProp";

    XMPMeta::RegisterNamespace(ns, "zerotest");

    XMPMeta* meta = (XMPMeta*)xmpRef;
    meta->SetProperty_Int(ns, propName, 0, 0);

    XMP_Int32 propValue = 999;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, ns, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
    EXPECT_EQ(propValue, 0);
}

// Test: wResult is properly initialized with no error on success
TEST_F(WXMPMetaGetPropertyIntTest_2026, WResultNoError_OnValidCall_2026) {
    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.example.com/noerrtest/", "noerrtest");

    WXMPMeta_GetProperty_Int_1(xmpRef, "http://ns.example.com/noerrtest/", "AnyProp", &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Both null schema and null propName - schema error should take precedence
TEST_F(WXMPMetaGetPropertyIntTest_2026, BothNullSchemaAndPropName_SchemaErrorFirst_2026) {
    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, nullptr, nullptr, &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Set max int32 value and retrieve it
TEST_F(WXMPMetaGetPropertyIntTest_2026, MaxInt32Property_ShouldReturnValue_2026) {
    const char* ns = "http://ns.example.com/maxtest/";
    const char* propName = "MaxProp";

    XMPMeta::RegisterNamespace(ns, "maxtest");

    XMPMeta* meta = (XMPMeta*)xmpRef;
    meta->SetProperty_Int(ns, propName, 2147483647, 0);  // INT32_MAX

    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, ns, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
    EXPECT_EQ(propValue, 2147483647);
}

// Test: Set min int32 value and retrieve it
TEST_F(WXMPMetaGetPropertyIntTest_2026, MinInt32Property_ShouldReturnValue_2026) {
    const char* ns = "http://ns.example.com/mintest/";
    const char* propName = "MinProp";

    XMPMeta::RegisterNamespace(ns, "mintest");

    XMPMeta* meta = (XMPMeta*)xmpRef;
    XMP_Int32 minVal = -2147483647 - 1;  // INT32_MIN
    meta->SetProperty_Int(ns, propName, minVal, 0);

    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int_1(xmpRef, ns, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
    EXPECT_EQ(propValue, minVal);
}
