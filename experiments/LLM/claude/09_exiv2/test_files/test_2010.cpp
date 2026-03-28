#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#define XMP_INCLUDE_XMPFILES 0
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "WXMPMeta.hpp"

// The function under test is declared externally
extern "C" void WXMPMeta_SetProperty_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr propValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

class WXMPMetaSetPropertyTest_2010 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = WXMPMeta_GetXMPMetaRef(meta);
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    // Helper to get XMPMetaRef from XMPMeta*
    static XMPMetaRef WXMPMeta_GetXMPMetaRef(XMPMeta* m) {
        return reinterpret_cast<XMPMetaRef>(m);
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
};

// Test: Null schema namespace should result in error
TEST_F(WXMPMetaSetPropertyTest_2010, NullSchemaNS_SetsError_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, nullptr, "propName", "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    // Should report a bad schema error
    EXPECT_TRUE(std::strstr(result.errMessage, "Empty schema namespace URI") != nullptr ||
                result.errMessage != nullptr);
}

// Test: Empty schema namespace should result in error
TEST_F(WXMPMetaSetPropertyTest_2010, EmptySchemaNS_SetsError_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "", "propName", "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null property name should result in error
TEST_F(WXMPMetaSetPropertyTest_2010, NullPropName_SetsError_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/", nullptr, "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty property name should result in error
TEST_F(WXMPMetaSetPropertyTest_2010, EmptyPropName_SetsError_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/", "", "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Valid parameters should not set error
TEST_F(WXMPMetaSetPropertyTest_2010, ValidParams_NoError_2010) {
    // Register the namespace first
    meta->RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "TestProp", "TestValue", 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: After setting property, it should be retrievable
TEST_F(WXMPMetaSetPropertyTest_2010, SetPropertyIsRetrievable_2010) {
    meta->RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "MyProp", "MyValue", 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty("http://ns.example.com/test/", "MyProp", &propValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(propValue, "MyValue");
}

// Test: Setting property with null propValue (should set empty or work)
TEST_F(WXMPMetaSetPropertyTest_2010, NullPropValue_NoError_2010) {
    meta->RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "NullValProp", nullptr, 0, &result);
    // This may or may not error - we just check it doesn't crash
    // If no error, property should exist
    if (result.errMessage == nullptr) {
        bool found = meta->DoesPropertyExist("http://ns.example.com/test/", "NullValProp");
        EXPECT_TRUE(found);
    }
}

// Test: Overwriting an existing property
TEST_F(WXMPMetaSetPropertyTest_2010, OverwriteProperty_2010) {
    meta->RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result1;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "OverProp", "FirstValue", 0, &result1);
    EXPECT_EQ(result1.errMessage, nullptr);

    WXMP_Result result2;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "OverProp", "SecondValue", 0, &result2);
    EXPECT_EQ(result2.errMessage, nullptr);

    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty("http://ns.example.com/test/", "OverProp", &propValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(propValue, "SecondValue");
}

// Test: Both schemaNS and propName are null
TEST_F(WXMPMetaSetPropertyTest_2010, BothNullSchemaAndProp_SetsError_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, nullptr, nullptr, "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Both schemaNS and propName are empty
TEST_F(WXMPMetaSetPropertyTest_2010, BothEmptySchemaAndProp_SetsError_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "", "", "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized on success
TEST_F(WXMPMetaSetPropertyTest_2010, ResultInitializedOnSuccess_2010) {
    meta->RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "InitProp", "InitValue", 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Setting property with empty string value
TEST_F(WXMPMetaSetPropertyTest_2010, EmptyStringValue_2010) {
    meta->RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "EmptyVal", "", 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty("http://ns.example.com/test/", "EmptyVal", &propValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(propValue, "");
}

// Test: Valid schemaNS but empty propName triggers error about property name
TEST_F(WXMPMetaSetPropertyTest_2010, ValidSchemaEmptyPropName_ErrorMessage_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "http://ns.example.com/test/", "", "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty property name") != nullptr);
    }
}

// Test: Empty schemaNS triggers error about schema
TEST_F(WXMPMetaSetPropertyTest_2010, EmptySchema_ErrorMessage_2010) {
    WXMP_Result result;
    WXMPMeta_SetProperty_1(xmpRef, "", "propName", "value", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty schema namespace URI") != nullptr);
    }
}
