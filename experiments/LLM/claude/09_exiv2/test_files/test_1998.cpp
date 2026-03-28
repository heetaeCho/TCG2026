#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_RegisterNamespace_1(
    XMP_StringPtr namespaceURI,
    XMP_StringPtr prefix,
    WXMP_Result* wResult);

class WXMPMetaRegisterNamespaceTest_1998 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test: Normal registration with valid namespaceURI and prefix
TEST_F(WXMPMetaRegisterNamespaceTest_1998, ValidNamespaceAndPrefix_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1("http://ns.example.com/test/", "test:", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr)
        << "Expected no error for valid namespace URI and prefix";
}

// Test: Null namespaceURI should produce an error
TEST_F(WXMPMetaRegisterNamespaceTest_1998, NullNamespaceURI_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1(nullptr, "prefix:", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr)
        << "Expected error message for null namespace URI";
}

// Test: Empty namespaceURI should produce an error
TEST_F(WXMPMetaRegisterNamespaceTest_1998, EmptyNamespaceURI_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1("", "prefix:", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr)
        << "Expected error message for empty namespace URI";
}

// Test: Null prefix should produce an error
TEST_F(WXMPMetaRegisterNamespaceTest_1998, NullPrefix_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1("http://ns.example.com/test2/", nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr)
        << "Expected error message for null prefix";
}

// Test: Empty prefix should produce an error
TEST_F(WXMPMetaRegisterNamespaceTest_1998, EmptyPrefix_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1("http://ns.example.com/test3/", "", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr)
        << "Expected error message for empty prefix";
}

// Test: Both null namespaceURI and null prefix should produce an error (URI checked first)
TEST_F(WXMPMetaRegisterNamespaceTest_1998, BothNullNamespaceAndPrefix_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1(nullptr, nullptr, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr)
        << "Expected error message when both namespace URI and prefix are null";
}

// Test: Both empty namespaceURI and empty prefix should produce an error (URI checked first)
TEST_F(WXMPMetaRegisterNamespaceTest_1998, BothEmptyNamespaceAndPrefix_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1("", "", &wResult);
    EXPECT_NE(wResult.errMessage, nullptr)
        << "Expected error message when both namespace URI and prefix are empty";
}

// Test: Registering the same namespace twice should not produce an error
TEST_F(WXMPMetaRegisterNamespaceTest_1998, RegisterSameNamespaceTwice_1998) {
    WXMP_Result wResult1;
    WXMPMeta_RegisterNamespace_1("http://ns.example.com/dup/", "dup:", &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);

    WXMP_Result wResult2;
    WXMPMeta_RegisterNamespace_1("http://ns.example.com/dup/", "dup:", &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr)
        << "Re-registering the same namespace should not produce an error";
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaRegisterNamespaceTest_1998, ResultInitialization_1998) {
    WXMP_Result wResult;
    // Verify default construction sets errMessage to 0/null
    EXPECT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_RegisterNamespace_1("http://ns.example.com/init/", "init:", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid namespace with a long URI and prefix
TEST_F(WXMPMetaRegisterNamespaceTest_1998, LongNamespaceURIAndPrefix_1998) {
    std::string longURI = "http://ns.example.com/";
    for (int i = 0; i < 100; ++i) {
        longURI += "segment/";
    }
    std::string longPrefix = "longprefix";
    for (int i = 0; i < 10; ++i) {
        longPrefix += "ext";
    }
    longPrefix += ":";

    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1(longURI.c_str(), longPrefix.c_str(), &wResult);
    // We just check it doesn't crash; error or success depends on implementation
    // but it shouldn't be a null/empty error
}

// Test: Error message content for empty namespace URI
TEST_F(WXMPMetaRegisterNamespaceTest_1998, ErrorMessageContentForEmptyURI_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1("", "prefix:", &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // The error message should contain something about "namespace"
    EXPECT_TRUE(std::strstr(wResult.errMessage, "namespace") != nullptr ||
                std::strstr(wResult.errMessage, "Empty") != nullptr)
        << "Error message: " << wResult.errMessage;
}

// Test: Error message content for empty prefix
TEST_F(WXMPMetaRegisterNamespaceTest_1998, ErrorMessageContentForEmptyPrefix_1998) {
    WXMP_Result wResult;
    WXMPMeta_RegisterNamespace_1("http://ns.example.com/err/", "", &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    EXPECT_TRUE(std::strstr(wResult.errMessage, "prefix") != nullptr ||
                std::strstr(wResult.errMessage, "Empty") != nullptr)
        << "Error message: " << wResult.errMessage;
}
