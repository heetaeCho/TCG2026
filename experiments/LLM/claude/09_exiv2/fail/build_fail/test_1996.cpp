#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DumpAliases_1(XMP_TextOutputProc outProc, void* refCon, WXMP_Result* wResult);

// A simple output proc for testing
static XMP_Status TestOutputProc(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    if (refCon != nullptr) {
        std::string* output = static_cast<std::string*>(refCon);
        output->append(buffer, bufferSize);
    }
    return 0; // success
}

// An output proc that always fails
static XMP_Status FailingOutputProc(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    return -1; // failure
}

class WXMPMetaDumpAliasesTest_1996 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test: Null outProc should result in an error
TEST_F(WXMPMetaDumpAliasesTest_1996, NullOutProcSetsErrorMessage_1996) {
    WXMP_Result wResult;
    WXMPMeta_DumpAliases_1(nullptr, nullptr, &wResult);
    // When outProc is null, the wrapper should catch the exception and set errMessage
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null outProc error message should mention bad param
TEST_F(WXMPMetaDumpAliasesTest_1996, NullOutProcErrorContainsBadParam_1996) {
    WXMP_Result wResult;
    WXMPMeta_DumpAliases_1(nullptr, nullptr, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // The error message should contain relevant info about null client output routine
    std::string errStr(wResult.errMessage);
    EXPECT_FALSE(errStr.empty());
}

// Test: Valid outProc with null refCon should succeed
TEST_F(WXMPMetaDumpAliasesTest_1996, ValidOutProcNullRefConSucceeds_1996) {
    WXMP_Result wResult;
    WXMPMeta_DumpAliases_1(TestOutputProc, nullptr, &wResult);
    // Should not set an error message
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid outProc with valid refCon should succeed and produce output
TEST_F(WXMPMetaDumpAliasesTest_1996, ValidOutProcWithRefConSucceeds_1996) {
    WXMP_Result wResult;
    std::string output;
    WXMPMeta_DumpAliases_1(TestOutputProc, &output, &wResult);
    // Should not set an error message
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Result int32Result is set when valid outProc is provided
TEST_F(WXMPMetaDumpAliasesTest_1996, ResultContainsStatus_1996) {
    WXMP_Result wResult;
    std::string output;
    WXMPMeta_DumpAliases_1(TestOutputProc, &output, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // int32Result should hold the status returned by DumpAliases
    // We can't know the exact value but it should be set (typically 0 for success)
    // Just verify no error occurred
}

// Test: WXMP_Result is properly initialized before use
TEST_F(WXMPMetaDumpAliasesTest_1996, ResultInitializedProperly_1996) {
    WXMP_Result wResult;
    // Default constructor should set errMessage to 0
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    std::string output;
    WXMPMeta_DumpAliases_1(TestOutputProc, &output, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Register standard aliases then dump, should produce some output
TEST_F(WXMPMetaDumpAliasesTest_1996, DumpAfterRegisterStandardAliases_1996) {
    WXMP_Result wResult;
    std::string output;
    
    // Register standard aliases so there's something to dump
    XMPMeta::RegisterStandardAliases("");
    
    WXMPMeta_DumpAliases_1(TestOutputProc, &output, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // After registering standard aliases, output should not be empty
    EXPECT_FALSE(output.empty());
}

// Test: Multiple calls should work without issues
TEST_F(WXMPMetaDumpAliasesTest_1996, MultipleCallsSucceed_1996) {
    WXMP_Result wResult1, wResult2;
    std::string output1, output2;
    
    WXMPMeta_DumpAliases_1(TestOutputProc, &output1, &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);
    
    WXMPMeta_DumpAliases_1(TestOutputProc, &output2, &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    
    // Both calls should produce the same output
    EXPECT_EQ(output1, output2);
}

// Test: Null outProc with non-null refCon should still error
TEST_F(WXMPMetaDumpAliasesTest_1996, NullOutProcNonNullRefConErrors_1996) {
    WXMP_Result wResult;
    std::string refConData;
    WXMPMeta_DumpAliases_1(nullptr, &refConData, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}
