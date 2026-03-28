#include <gtest/gtest.h>
#include <string>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetNamespaceURI_1(
    XMP_StringPtr namespacePrefix,
    XMP_StringPtr * namespaceURI,
    XMP_StringLen * uriSize,
    WXMP_Result * wResult);

class WXMPMetaGetNamespaceURITest_2000 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        // Clean up
    }
};

// Test: Null namespace prefix should throw/set error (kXMPErr_BadSchema)
TEST_F(WXMPMetaGetNamespaceURITest_2000, NullPrefixThrowsBadSchema_2000) {
    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    WXMPMeta_GetNamespaceURI_1(nullptr, &namespaceURI, &uriSize, &wResult);

    // When prefix is null, the function should set an error message
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty namespace prefix (empty string) should throw/set error (kXMPErr_BadSchema)
TEST_F(WXMPMetaGetNamespaceURITest_2000, EmptyPrefixThrowsBadSchema_2000) {
    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    WXMPMeta_GetNamespaceURI_1("", &namespaceURI, &uriSize, &wResult);

    // When prefix is empty string, the function should set an error message
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid but unregistered prefix should return not found (int32Result == 0)
TEST_F(WXMPMetaGetNamespaceURITest_2000, UnregisteredPrefixReturnsNotFound_2000) {
    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    WXMPMeta_GetNamespaceURI_1("nonexistent_prefix:", &namespaceURI, &uriSize, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should return false (not found)
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Register a namespace and then retrieve its URI by prefix
TEST_F(WXMPMetaGetNamespaceURITest_2000, RegisteredPrefixReturnsURI_2000) {
    // Register a namespace first
    XMPMeta::RegisterNamespace("http://test.example.com/ns/", "testprefix:");

    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    WXMPMeta_GetNamespaceURI_1("testprefix:", &namespaceURI, &uriSize, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should return true (found)
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
    // URI should match what was registered
    EXPECT_NE(namespaceURI, nullptr);
    EXPECT_STREQ(namespaceURI, "http://test.example.com/ns/");
    EXPECT_GT(uriSize, static_cast<XMP_StringLen>(0));
}

// Test: Null namespaceURI output pointer should not crash (uses internal void pointer)
TEST_F(WXMPMetaGetNamespaceURITest_2000, NullURIOutputDoesNotCrash_2000) {
    // Register a namespace
    XMPMeta::RegisterNamespace("http://test2.example.com/ns/", "testprefix2:");

    WXMP_Result wResult;
    XMP_StringLen uriSize = 0;

    // Pass null for namespaceURI output
    WXMPMeta_GetNamespaceURI_1("testprefix2:", nullptr, &uriSize, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should still report found
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
}

// Test: Null uriSize output pointer should not crash (uses internal void size)
TEST_F(WXMPMetaGetNamespaceURITest_2000, NullURISizeOutputDoesNotCrash_2000) {
    // Register a namespace
    XMPMeta::RegisterNamespace("http://test3.example.com/ns/", "testprefix3:");

    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;

    // Pass null for uriSize output
    WXMPMeta_GetNamespaceURI_1("testprefix3:", &namespaceURI, nullptr, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should still report found
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
    EXPECT_NE(namespaceURI, nullptr);
    EXPECT_STREQ(namespaceURI, "http://test3.example.com/ns/");
}

// Test: Both namespaceURI and uriSize null should not crash
TEST_F(WXMPMetaGetNamespaceURITest_2000, BothOutputsNullDoesNotCrash_2000) {
    XMPMeta::RegisterNamespace("http://test4.example.com/ns/", "testprefix4:");

    WXMP_Result wResult;

    WXMPMeta_GetNamespaceURI_1("testprefix4:", nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
}

// Test: Well-known XMP namespace prefix should return its URI
TEST_F(WXMPMetaGetNamespaceURITest_2000, WellKnownDCPrefixReturnsURI_2000) {
    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    // "dc:" is a well-known Dublin Core prefix typically registered by default
    WXMPMeta_GetNamespaceURI_1("dc:", &namespaceURI, &uriSize, &wResult);

    // If dc: is registered by default, this should succeed
    if (wResult.errMessage == nullptr && wResult.int32Result != 0) {
        EXPECT_NE(namespaceURI, nullptr);
        EXPECT_GT(uriSize, static_cast<XMP_StringLen>(0));
    }
    // Otherwise just verify no crash occurred
    // (some builds may not have dc: pre-registered)
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaGetNamespaceURITest_2000, ResultInitializedCorrectly_2000) {
    WXMP_Result wResult;

    // Verify the default construction
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    WXMPMeta_GetNamespaceURI_1("unknown_prefix:", &namespaceURI, &uriSize, &wResult);

    // After calling with an unknown prefix, errMessage should still be null (no error)
    EXPECT_EQ(wResult.errMessage, nullptr);
    // But the result should be false (not found)
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: URI size is correct for a registered namespace
TEST_F(WXMPMetaGetNamespaceURITest_2000, URISizeMatchesStringLength_2000) {
    const char* testURI = "http://urisize.example.com/ns/";
    XMPMeta::RegisterNamespace(testURI, "urisizetest:");

    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    WXMPMeta_GetNamespaceURI_1("urisizetest:", &namespaceURI, &uriSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(1));
    EXPECT_NE(namespaceURI, nullptr);
    EXPECT_EQ(uriSize, static_cast<XMP_StringLen>(strlen(testURI)));
}

// Test: Prefix with only whitespace-like characters (not empty but unusual)
TEST_F(WXMPMetaGetNamespaceURITest_2000, WhitespacePrefixNotFound_2000) {
    WXMP_Result wResult;
    XMP_StringPtr namespaceURI = nullptr;
    XMP_StringLen uriSize = 0;

    WXMPMeta_GetNamespaceURI_1(" ", &namespaceURI, &uriSize, &wResult);

    // This is a non-empty prefix, so it shouldn't throw BadSchema
    // But it likely won't be found as a registered namespace
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
    }
}
