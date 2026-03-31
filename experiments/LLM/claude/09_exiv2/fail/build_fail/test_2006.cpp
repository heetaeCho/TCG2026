#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#define UNIX_ENV 1
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetProperty_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr * propValue,
    XMP_StringLen * valueSize,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

class WXMPMetaGetPropertyTest_2006 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
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

// Test: Empty schema namespace (null pointer) should produce an error
TEST_F(WXMPMetaGetPropertyTest_2006, NullSchemaNamespaceThrowsError_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_1(GetRef(), nullptr, "propName", &propValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace (empty string) should produce an error
TEST_F(WXMPMetaGetPropertyTest_2006, EmptySchemaNamespaceThrowsError_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_1(GetRef(), "", "propName", &propValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null property name should produce an error
TEST_F(WXMPMetaGetPropertyTest_2006, NullPropNameThrowsError_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.adobe.com/xap/1.0/", nullptr, &propValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name should produce an error
TEST_F(WXMPMetaGetPropertyTest_2006, EmptyPropNameThrowsError_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "", &propValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Getting a non-existent property should return false (int32Result == 0)
TEST_F(WXMPMetaGetPropertyTest_2006, NonExistentPropertyReturnsFalse_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    // Register namespace first
    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "NonExistentProp", &propValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Setting and then getting a property should return true and correct value
TEST_F(WXMPMetaGetPropertyTest_2006, ExistingPropertyReturnsTrue_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta->SetProperty("http://ns.test.com/", "TestProp", "TestValue", 0);

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "TestProp", &propValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    ASSERT_NE(propValue, nullptr);
    EXPECT_STREQ(propValue, "TestValue");
    EXPECT_EQ(valueSize, static_cast<XMP_StringLen>(std::strlen("TestValue")));
}

// Test: Passing null propValue pointer should not crash (uses voidStringPtr internally)
TEST_F(WXMPMetaGetPropertyTest_2006, NullPropValuePointerDoesNotCrash_2006) {
    WXMP_Result wResult;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta->SetProperty("http://ns.test.com/", "TestProp", "TestValue", 0);

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "TestProp", nullptr, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Passing null valueSize pointer should not crash (uses voidStringLen internally)
TEST_F(WXMPMetaGetPropertyTest_2006, NullValueSizePointerDoesNotCrash_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta->SetProperty("http://ns.test.com/", "TestProp", "TestValue", 0);

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "TestProp", &propValue, nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Passing null options pointer should not crash (uses voidOptionBits internally)
TEST_F(WXMPMetaGetPropertyTest_2006, NullOptionsPointerDoesNotCrash_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta->SetProperty("http://ns.test.com/", "TestProp", "TestValue", 0);

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "TestProp", &propValue, &valueSize, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: All output params null except wResult - should not crash for nonexistent property
TEST_F(WXMPMetaGetPropertyTest_2006, AllOutputParamsNullNonExistent_2006) {
    WXMP_Result wResult;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "NoSuchProp", nullptr, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Property with empty value
TEST_F(WXMPMetaGetPropertyTest_2006, PropertyWithEmptyValue_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta->SetProperty("http://ns.test.com/", "EmptyProp", "", 0);

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "EmptyProp", &propValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    ASSERT_NE(propValue, nullptr);
    EXPECT_STREQ(propValue, "");
    EXPECT_EQ(valueSize, static_cast<XMP_StringLen>(0));
}

// Test: Setting property then deleting it, then getting should return false
TEST_F(WXMPMetaGetPropertyTest_2006, DeletedPropertyReturnsFalse_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta->SetProperty("http://ns.test.com/", "TempProp", "TempValue", 0);
    meta->DeleteProperty("http://ns.test.com/", "TempProp");

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "TempProp", &propValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Updating a property value and getting the updated value
TEST_F(WXMPMetaGetPropertyTest_2006, UpdatedPropertyReturnsNewValue_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta->SetProperty("http://ns.test.com/", "UpdateProp", "OldValue", 0);
    meta->SetProperty("http://ns.test.com/", "UpdateProp", "NewValue", 0);

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "UpdateProp", &propValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    ASSERT_NE(propValue, nullptr);
    EXPECT_STREQ(propValue, "NewValue");
}

// Test: Using a well-known namespace (dc)
TEST_F(WXMPMetaGetPropertyTest_2006, WellKnownNamespace_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* kXMP_NS_DC = "http://purl.org/dc/elements/1.1/";
    meta->SetProperty(kXMP_NS_DC, "title", "MyTitle", 0);

    WXMPMeta_GetProperty_1(GetRef(), kXMP_NS_DC, "title", &propValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    ASSERT_NE(propValue, nullptr);
    EXPECT_STREQ(propValue, "MyTitle");
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaGetPropertyTest_2006, ResultInitialization_2006) {
    WXMP_Result wResult;
    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));

    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test.com/", "NoProp", nullptr, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Both schema and propname are empty
TEST_F(WXMPMetaGetPropertyTest_2006, BothSchemaAndPropNameEmpty_2006) {
    WXMP_Result wResult;

    WXMPMeta_GetProperty_1(GetRef(), "", "", nullptr, nullptr, nullptr, &wResult);

    // Should fail on schema first
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid schema but property name in different namespace returns false
TEST_F(WXMPMetaGetPropertyTest_2006, WrongNamespaceReturnsFalse_2006) {
    WXMP_Result wResult;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test1.com/", "test1");
    XMPMeta::RegisterNamespace("http://ns.test2.com/", "test2");
    meta->SetProperty("http://ns.test1.com/", "MyProp", "MyValue", 0);

    WXMPMeta_GetProperty_1(GetRef(), "http://ns.test2.com/", "MyProp", &propValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}
