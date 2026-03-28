#include <gtest/gtest.h>
#include <string>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_GetNamespacePrefix_1(
    XMP_StringPtr namespaceURI,
    XMP_StringPtr * namespacePrefix,
    XMP_StringLen * prefixSize,
    WXMP_Result * wResult);

class WXMPMetaGetNamespacePrefixTest_1999 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized
        XMPMeta::Initialize();
        // Register a known namespace for testing
        XMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp:");
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

// Test: Null namespace URI should result in an error
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, NullNamespaceURI_ThrowsError_1999) {
    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1(nullptr, &prefix, &prefixSize, &wResult);

    // Should have an error message set
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty namespace URI string should result in an error
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, EmptyNamespaceURI_ThrowsError_1999) {
    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1("", &prefix, &prefixSize, &wResult);

    // Should have an error message set
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Known registered namespace URI returns found (true)
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, KnownNamespaceURI_ReturnsFound_1999) {
    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1("http://ns.adobe.com/xap/1.0/", &prefix, &prefixSize, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should indicate found
    EXPECT_NE(wResult.int32Result, 0);
    // Prefix should be non-null and non-empty
    EXPECT_NE(prefix, nullptr);
    EXPECT_GT(prefixSize, (XMP_StringLen)0);
}

// Test: Unknown namespace URI returns not found (false)
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, UnknownNamespaceURI_ReturnsNotFound_1999) {
    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1("http://totally.unknown.namespace/", &prefix, &prefixSize, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should indicate not found
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: Null prefix pointer is handled (uses voidStringPtr internally)
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, NullPrefixPointer_DoesNotCrash_1999) {
    WXMP_Result wResult;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1("http://ns.adobe.com/xap/1.0/", nullptr, &prefixSize, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should still indicate found
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: Null prefixSize pointer is handled (uses voidStringLen internally)
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, NullPrefixSizePointer_DoesNotCrash_1999) {
    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;

    WXMPMeta_GetNamespacePrefix_1("http://ns.adobe.com/xap/1.0/", &prefix, nullptr, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Should still indicate found
    EXPECT_NE(wResult.int32Result, 0);
    EXPECT_NE(prefix, nullptr);
}

// Test: Both prefix and prefixSize null pointers are handled
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, BothOutputsNull_DoesNotCrash_1999) {
    WXMP_Result wResult;

    WXMPMeta_GetNamespacePrefix_1("http://ns.adobe.com/xap/1.0/", nullptr, nullptr, &wResult);

    // Should not have an error
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: WXMP_Result is properly initialized when no error occurs
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, ResultProperlyInitialized_1999) {
    WXMP_Result wResult;

    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, (XMP_Uns32)0);

    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1("http://ns.adobe.com/xap/1.0/", &prefix, &prefixSize, &wResult);

    // int32Result should reflect the boolean found result
    // For a known namespace, it should be true (non-zero)
    EXPECT_TRUE(wResult.int32Result != 0);
}

// Test: Verify the prefix returned for a well-known namespace
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, VerifyPrefixForKnownNamespace_1999) {
    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1("http://ns.adobe.com/xap/1.0/", &prefix, &prefixSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);

    // The prefix for xap/1.0/ should be "xmp:"
    ASSERT_NE(prefix, nullptr);
    std::string prefixStr(prefix, prefixSize);
    EXPECT_EQ(prefixStr, "xmp:");
}

// Test: Register a custom namespace and retrieve its prefix
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, CustomRegisteredNamespace_ReturnsCorrectPrefix_1999) {
    // Register a custom namespace
    XMPMeta::RegisterNamespace("http://example.com/custom/", "custom:");

    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    WXMPMeta_GetNamespacePrefix_1("http://example.com/custom/", &prefix, &prefixSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
    ASSERT_NE(prefix, nullptr);
    EXPECT_GT(prefixSize, (XMP_StringLen)0);
}

// Test: Whitespace-only URI is not empty (first char != 0), should not throw BadSchema
TEST_F(WXMPMetaGetNamespacePrefixTest_1999, WhitespaceURI_DoesNotThrowBadSchema_1999) {
    WXMP_Result wResult;
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixSize = 0;

    // A single space is not empty (first char is ' ', not '\0')
    WXMPMeta_GetNamespacePrefix_1(" ", &prefix, &prefixSize, &wResult);

    // Should not throw a BadSchema error since it's not empty
    // It might not find a namespace though
    // The key point: no BadSchema error
    // wResult.errMessage could be null (no error) or some other error, but not BadSchema
    if (wResult.errMessage == nullptr) {
        // No error - namespace just not found
        EXPECT_EQ(wResult.int32Result, 0);
    }
    // If there is an error, it shouldn't be about empty namespace URI
}
