#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declarations for the wrapper function and types
typedef void * XMPMetaRef;

extern "C" void WXMPMeta_DumpObject_1(
    XMPMetaRef xmpRef,
    XMP_TextOutputProc outProc,
    void * refCon,
    WXMP_Result * wResult);

// We need to create XMPMeta objects - include relevant headers
#include "XMPMeta.hpp"

// Helper: a simple text output callback that appends to a string
static XMP_Status TestOutputProc(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    if (refCon != nullptr && buffer != nullptr) {
        std::string * output = static_cast<std::string *>(refCon);
        output->append(buffer, bufferSize);
    }
    return 0; // success
}

// Helper: output callback that always fails
static XMP_Status FailingOutputProc(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    return -1; // indicate failure
}

// Helper to get an XMPMetaRef from an XMPMeta object
// XMPMetaRef is typically a pointer cast
static XMPMetaRef MetaToRef(XMPMeta * meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaDumpObjectTest_2035 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP toolkit is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test: Normal operation with a valid XMPMeta and valid output proc
TEST_F(WXMPMetaDumpObjectTest_2035, NormalOperation_ValidMetaAndProc_2035) {
    XMPMeta meta;
    WXMP_Result wResult;
    std::string output;

    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output, &wResult);

    // Should succeed without error
    EXPECT_EQ(wResult.errMessage, nullptr);
    // DumpObject should produce some output for even an empty meta object
    // The int32Result should contain the status
}

// Test: Null outProc should cause an error (kXMPErr_BadParam)
TEST_F(WXMPMetaDumpObjectTest_2035, NullOutProc_SetsError_2035) {
    XMPMeta meta;
    WXMP_Result wResult;

    WXMPMeta_DumpObject_1(MetaToRef(&meta), nullptr, nullptr, &wResult);

    // Should set an error message about null output routine
    EXPECT_NE(wResult.errMessage, nullptr);
    if (wResult.errMessage != nullptr) {
        // The error message should mention "Null client output routine" or similar
        EXPECT_TRUE(std::strstr(wResult.errMessage, "Null") != nullptr ||
                    std::strstr(wResult.errMessage, "null") != nullptr);
    }
}

// Test: DumpObject with refCon as nullptr but valid outProc
TEST_F(WXMPMetaDumpObjectTest_2035, NullRefCon_ValidOutProc_2035) {
    XMPMeta meta;
    WXMP_Result wResult;

    // outProc is valid but refCon is null - should still work (refCon is user context)
    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: DumpObject on meta with some properties set produces output
TEST_F(WXMPMetaDumpObjectTest_2035, MetaWithProperties_ProducesOutput_2035) {
    XMPMeta meta;
    // Register a namespace and set a property
    XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
    meta.SetProperty("http://ns.test.com/", "TestProp", "TestValue", 0);

    WXMP_Result wResult;
    std::string output;

    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    // Output should contain something related to the property
    EXPECT_FALSE(output.empty());
}

// Test: DumpObject on empty meta object still succeeds
TEST_F(WXMPMetaDumpObjectTest_2035, EmptyMeta_Succeeds_2035) {
    XMPMeta meta;
    WXMP_Result wResult;
    std::string output;

    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized and int32Result is set
TEST_F(WXMPMetaDumpObjectTest_2035, ResultStatusIsSet_2035) {
    XMPMeta meta;
    WXMP_Result wResult;
    std::string output;

    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    // The status from DumpObject should be stored in int32Result
    // For a successful dump, this is typically a non-negative status
    // We just verify it was set (not the default 0 from constructor necessarily)
    // Actually, 0 could be a valid success status
    EXPECT_GE(static_cast<int>(wResult.int32Result), 0);
}

// Test: Multiple calls to DumpObject work correctly
TEST_F(WXMPMetaDumpObjectTest_2035, MultipleCalls_Work_2035) {
    XMPMeta meta;
    WXMP_Result wResult1, wResult2;
    std::string output1, output2;

    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output1, &wResult1);
    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output2, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    // Both dumps of the same object should produce the same output
    EXPECT_EQ(output1, output2);
}

// Test: DumpObject after modifying meta produces different output
TEST_F(WXMPMetaDumpObjectTest_2035, DumpAfterModification_ReflectsChanges_2035) {
    XMPMeta meta;
    WXMP_Result wResult1, wResult2;
    std::string output1, output2;

    // Dump empty meta
    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output1, &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);

    // Add a property
    XMPMeta::RegisterNamespace("http://ns.test2.com/", "test2");
    meta.SetProperty("http://ns.test2.com/", "Prop", "Value", 0);

    // Dump again
    WXMPMeta_DumpObject_1(MetaToRef(&meta), TestOutputProc, &output2, &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);

    // The output should be different after adding a property
    EXPECT_NE(output1, output2);
}
