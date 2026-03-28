#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_DumpNamespaces_1(XMP_TextOutputProc outProc, void * refCon, WXMP_Result * wResult);

// A simple callback that accumulates output into a string
static XMP_Status TestOutputProc(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    if (refCon != nullptr && buffer != nullptr) {
        std::string * output = static_cast<std::string *>(refCon);
        output->append(buffer, bufferSize);
    }
    return 0; // success
}

// A callback that always returns an error status
static XMP_Status ErrorOutputProc(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    return -1; // simulate error
}

// A callback that counts how many times it was called
static XMP_Status CountingOutputProc(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    if (refCon != nullptr) {
        int * count = static_cast<int *>(refCon);
        (*count)++;
    }
    (void)buffer;
    (void)bufferSize;
    return 0;
}

class WXMPMetaDumpNamespacesTest_1995 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        // Clean up
    }
};

// Test: Passing null outProc should result in an error (exception reported via wResult)
TEST_F(WXMPMetaDumpNamespacesTest_1995, NullOutProcSetsError_1995) {
    WXMP_Result wResult;
    WXMPMeta_DumpNamespaces_1(nullptr, nullptr, &wResult);
    // When outProc is null, an exception should be thrown internally and
    // errMessage should be set (non-null)
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid outProc with null refCon should succeed without error
TEST_F(WXMPMetaDumpNamespacesTest_1995, ValidOutProcNullRefCon_1995) {
    WXMP_Result wResult;
    WXMPMeta_DumpNamespaces_1(TestOutputProc, nullptr, &wResult);
    // Should not set an error message
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid outProc with valid refCon should succeed and produce output
TEST_F(WXMPMetaDumpNamespacesTest_1995, ValidOutProcWithRefCon_1995) {
    WXMP_Result wResult;
    std::string output;
    WXMPMeta_DumpNamespaces_1(TestOutputProc, &output, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // DumpNamespaces should produce some output (at least standard namespaces)
    // We just verify some output was generated
    EXPECT_FALSE(output.empty());
}

// Test: The function returns a status in int32Result
TEST_F(WXMPMetaDumpNamespacesTest_1995, ReturnsStatusInInt32Result_1995) {
    WXMP_Result wResult;
    std::string output;
    WXMPMeta_DumpNamespaces_1(TestOutputProc, &output, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // The status should be a valid XMP_Status value (typically 0 for success)
    // We just verify it's set
    XMP_Status status = static_cast<XMP_Status>(wResult.int32Result);
    (void)status; // Just ensuring it's accessible
}

// Test: Calling with a counting callback to verify the proc is actually invoked
TEST_F(WXMPMetaDumpNamespacesTest_1995, OutputProcIsInvoked_1995) {
    WXMP_Result wResult;
    int callCount = 0;
    WXMPMeta_DumpNamespaces_1(CountingOutputProc, &callCount, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // The output proc should have been called at least once
    EXPECT_GT(callCount, 0);
}

// Test: WXMP_Result is properly initialized before call and reflects result after call
TEST_F(WXMPMetaDumpNamespacesTest_1995, ResultInitializedProperly_1995) {
    WXMP_Result wResult;
    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);

    std::string output;
    WXMPMeta_DumpNamespaces_1(TestOutputProc, &output, &wResult);
    // After successful call, errMessage should remain null
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: After registering a namespace, DumpNamespaces output should contain it
TEST_F(WXMPMetaDumpNamespacesTest_1995, DumpContainsRegisteredNamespace_1995) {
    // Register a custom namespace
    XMPMeta::RegisterNamespace("http://test.example.com/ns/", "testns");

    WXMP_Result wResult;
    std::string output;
    WXMPMeta_DumpNamespaces_1(TestOutputProc, &output, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // The output should contain the registered namespace URI or prefix
    EXPECT_NE(output.find("http://test.example.com/ns/"), std::string::npos);
}

// Test: Multiple calls produce consistent results
TEST_F(WXMPMetaDumpNamespacesTest_1995, MultipleCalls_1995) {
    std::string output1, output2;
    WXMP_Result wResult1, wResult2;

    WXMPMeta_DumpNamespaces_1(TestOutputProc, &output1, &wResult1);
    WXMPMeta_DumpNamespaces_1(TestOutputProc, &output2, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_EQ(output1, output2);
    EXPECT_EQ(wResult1.int32Result, wResult2.int32Result);
}

// Test: Null outProc error message should mention the issue
TEST_F(WXMPMetaDumpNamespacesTest_1995, NullOutProcErrorMessage_1995) {
    WXMP_Result wResult;
    WXMPMeta_DumpNamespaces_1(nullptr, nullptr, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // The error message should be non-empty
    EXPECT_GT(std::strlen(wResult.errMessage), 0u);
}
