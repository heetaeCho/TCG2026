#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_RegisterStandardAliases_1(XMP_StringPtr schemaNS, WXMP_Result* wResult);

class WXMPMetaRegisterStandardAliasesTest_2005 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMPMeta once for all tests
        XMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        XMPMeta::Terminate();
    }

    void SetUp() override {
        memset(&result, 0, sizeof(result));
        result.errMessage = nullptr;
    }

    WXMP_Result result;
};

// Test: Passing nullptr as schemaNS should be treated as empty string and not crash
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, NullSchemaNSDoesNotCrash_2005) {
    WXMPMeta_RegisterStandardAliases_1(nullptr, &result);
    // If no error occurred, errMessage should remain null
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Passing empty string as schemaNS should succeed
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, EmptySchemaNSSucceeds_2005) {
    WXMPMeta_RegisterStandardAliases_1("", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Passing a known XMP namespace URI for Dublin Core
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, KnownDCNamespaceSucceeds_2005) {
    WXMPMeta_RegisterStandardAliases_1("http://purl.org/dc/elements/1.1/", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Passing a known XMP namespace URI for XMP basic
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, KnownXMPBasicNamespaceSucceeds_2005) {
    WXMPMeta_RegisterStandardAliases_1("http://ns.adobe.com/xap/1.0/", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Passing a known XMP namespace URI for Photoshop
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, KnownPhotoshopNamespaceSucceeds_2005) {
    WXMPMeta_RegisterStandardAliases_1("http://ns.adobe.com/photoshop/1.0/", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Passing a known XMP namespace URI for IPTC Core
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, KnownIPTCCoreNamespaceSucceeds_2005) {
    WXMPMeta_RegisterStandardAliases_1("http://iptc.org/std/Iptc4xmpCore/1.0/xmlns/", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Passing an unknown namespace URI - may produce error or silently succeed
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, UnknownNamespaceHandledGracefully_2005) {
    WXMPMeta_RegisterStandardAliases_1("http://unknown.namespace.example.com/", &result);
    // The function may either succeed silently or report an error via errMessage
    // We just verify it doesn't crash; if there's an error, errMessage will be non-null
    // This is implementation-dependent behavior
    // No assertion on errMessage value - just verifying no crash/segfault
    SUCCEED();
}

// Test: Calling RegisterStandardAliases multiple times with empty string should be idempotent
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, MultipleCallsWithEmptyStringIdempotent_2005) {
    WXMPMeta_RegisterStandardAliases_1("", &result);
    EXPECT_EQ(result.errMessage, nullptr);

    WXMP_Result result2;
    memset(&result2, 0, sizeof(result2));
    result2.errMessage = nullptr;
    WXMPMeta_RegisterStandardAliases_1("", &result2);
    EXPECT_EQ(result2.errMessage, nullptr);
}

// Test: Calling RegisterStandardAliases multiple times with nullptr should be idempotent
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, MultipleCallsWithNullptrIdempotent_2005) {
    WXMPMeta_RegisterStandardAliases_1(nullptr, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    WXMP_Result result2;
    memset(&result2, 0, sizeof(result2));
    result2.errMessage = nullptr;
    WXMPMeta_RegisterStandardAliases_1(nullptr, &result2);
    EXPECT_EQ(result2.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, ResultInitializedProperly_2005) {
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, 0u);
    EXPECT_EQ(result.int64Result, 0u);
    
    WXMPMeta_RegisterStandardAliases_1("", &result);
    // After successful call, errMessage should still be null
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Passing XMP Rights namespace
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, KnownXMPRightsNamespaceSucceeds_2005) {
    WXMPMeta_RegisterStandardAliases_1("http://ns.adobe.com/xap/1.0/rights/", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Calling with different known namespaces sequentially
TEST_F(WXMPMetaRegisterStandardAliasesTest_2005, SequentialKnownNamespaceCalls_2005) {
    WXMPMeta_RegisterStandardAliases_1("http://purl.org/dc/elements/1.1/", &result);
    EXPECT_EQ(result.errMessage, nullptr);

    WXMP_Result result2;
    memset(&result2, 0, sizeof(result2));
    result2.errMessage = nullptr;
    WXMPMeta_RegisterStandardAliases_1("http://ns.adobe.com/xap/1.0/", &result2);
    EXPECT_EQ(result2.errMessage, nullptr);

    WXMP_Result result3;
    memset(&result3, 0, sizeof(result3));
    result3.errMessage = nullptr;
    WXMPMeta_RegisterStandardAliases_1("http://ns.adobe.com/photoshop/1.0/", &result3);
    EXPECT_EQ(result3.errMessage, nullptr);
}
