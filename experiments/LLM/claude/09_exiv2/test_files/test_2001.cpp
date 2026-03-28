#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the function under test
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DeleteNamespace_1(XMP_StringPtr namespaceURI, WXMP_Result * wResult);

class WXMPMetaDeleteNamespaceTest_2001 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test: Passing a null namespace URI should result in an error
TEST_F(WXMPMetaDeleteNamespaceTest_2001, NullNamespaceURI_SetsError_2001) {
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1(nullptr, &wResult);
    
    // The wrapper should catch the exception and set errMessage
    EXPECT_NE(wResult.errMessage, nullptr);
    // Verify the error message is not empty
    if (wResult.errMessage != nullptr) {
        EXPECT_GT(std::strlen(wResult.errMessage), 0u);
    }
}

// Test: Passing an empty string namespace URI should result in an error
TEST_F(WXMPMetaDeleteNamespaceTest_2001, EmptyNamespaceURI_SetsError_2001) {
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1("", &wResult);
    
    // The wrapper should catch the exception and set errMessage
    EXPECT_NE(wResult.errMessage, nullptr);
    if (wResult.errMessage != nullptr) {
        EXPECT_GT(std::strlen(wResult.errMessage), 0u);
    }
}

// Test: Passing a valid (non-empty) namespace URI should not produce an error
// Even if the namespace doesn't exist, the function should not error out
TEST_F(WXMPMetaDeleteNamespaceTest_2001, ValidNamespaceURI_NoError_2001) {
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1("http://ns.example.com/nonexistent/", &wResult);
    
    // No error should be reported for a valid (non-null, non-empty) URI
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Register a namespace and then delete it — no error expected
TEST_F(WXMPMetaDeleteNamespaceTest_2001, RegisterThenDelete_NoError_2001) {
    // Register a namespace first
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");
    
    // Verify the namespace was registered
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;
    bool found = XMPMeta::GetNamespacePrefix("http://ns.example.com/test/", &prefix, &prefixLen);
    EXPECT_TRUE(found);
    
    // Now delete it via the wrapper function
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1("http://ns.example.com/test/", &wResult);
    
    // Should not produce an error
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Passing a single character namespace URI (non-empty) should not trigger the empty check
TEST_F(WXMPMetaDeleteNamespaceTest_2001, SingleCharNamespaceURI_NoError_2001) {
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1("x", &wResult);
    
    // "x" is non-null and non-empty, so it should not trigger the BadSchema error
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized before use
TEST_F(WXMPMetaDeleteNamespaceTest_2001, ResultInitialization_2001) {
    WXMP_Result wResult;
    // Verify the default constructor sets errMessage to 0/nullptr
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Deleting the same namespace twice should not cause an error
TEST_F(WXMPMetaDeleteNamespaceTest_2001, DeleteTwice_NoError_2001) {
    XMPMeta::RegisterNamespace("http://ns.example.com/twice/", "twice");
    
    WXMP_Result wResult1;
    WXMPMeta_DeleteNamespace_1("http://ns.example.com/twice/", &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);
    
    WXMP_Result wResult2;
    WXMPMeta_DeleteNamespace_1("http://ns.example.com/twice/", &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);
}

// Test: Error message for null URI contains relevant information
TEST_F(WXMPMetaDeleteNamespaceTest_2001, NullURI_ErrorMessageContent_2001) {
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1(nullptr, &wResult);
    
    ASSERT_NE(wResult.errMessage, nullptr);
    // The error message should mention "namespace" based on the throw statement
    std::string errMsg(wResult.errMessage);
    // Check that some meaningful error info is present
    EXPECT_FALSE(errMsg.empty());
}

// Test: Error message for empty string URI contains relevant information
TEST_F(WXMPMetaDeleteNamespaceTest_2001, EmptyURI_ErrorMessageContent_2001) {
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1("", &wResult);
    
    ASSERT_NE(wResult.errMessage, nullptr);
    std::string errMsg(wResult.errMessage);
    EXPECT_FALSE(errMsg.empty());
}

// Test: A long but valid namespace URI should work without error
TEST_F(WXMPMetaDeleteNamespaceTest_2001, LongNamespaceURI_NoError_2001) {
    std::string longURI = "http://ns.example.com/";
    longURI.append(1000, 'a');
    longURI.append("/");
    
    WXMP_Result wResult;
    WXMPMeta_DeleteNamespace_1(longURI.c_str(), &wResult);
    
    // Should not trigger the empty/null check
    EXPECT_EQ(wResult.errMessage, nullptr);
}
