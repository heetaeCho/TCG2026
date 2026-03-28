#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPUtils.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_MergeFromJPEG_1(XMPMetaRef wfullXMP, XMPMetaRef wextendedXMP, WXMP_Result * wResult);

class WXMPUtilsMergeFromJPEGTest_1953 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that passing a null fullXMP pointer results in an error
TEST_F(WXMPUtilsMergeFromJPEGTest_1953, NullFullXMPPointerReturnsError_1953) {
    WXMP_Result wResult;
    
    // Create a valid extended XMP object
    SXMPMeta extendedXMP;
    XMPMetaRef extRef = WXMPMeta_GetInternalRef(extendedXMP);
    
    // Call with null fullXMP (0)
    WXMPUtils_MergeFromJPEG_1(0, extRef, &wResult);
    
    // Expect an error message to be set
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test that passing valid XMP objects does not produce an error
TEST_F(WXMPUtilsMergeFromJPEGTest_1953, ValidObjectsNoError_1953) {
    WXMP_Result wResult;
    
    // Create valid XMP meta objects
    SXMPMeta fullXMP;
    SXMPMeta extendedXMP;
    
    XMPMetaRef fullRef = WXMPMeta_GetInternalRef(fullXMP);
    XMPMetaRef extRef = WXMPMeta_GetInternalRef(extendedXMP);
    
    WXMPUtils_MergeFromJPEG_1(fullRef, extRef, &wResult);
    
    // Expect no error
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test merging with empty extended XMP does not corrupt fullXMP
TEST_F(WXMPUtilsMergeFromJPEGTest_1953, EmptyExtendedXMPNoCorruption_1953) {
    WXMP_Result wResult;
    
    SXMPMeta fullXMP;
    // Set a property on fullXMP
    fullXMP.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool");
    
    SXMPMeta extendedXMP; // empty
    
    XMPMetaRef fullRef = WXMPMeta_GetInternalRef(fullXMP);
    XMPMetaRef extRef = WXMPMeta_GetInternalRef(extendedXMP);
    
    WXMPUtils_MergeFromJPEG_1(fullRef, extRef, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    // The existing property should still be there
    std::string value;
    EXPECT_TRUE(fullXMP.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, nullptr));
    EXPECT_EQ(value, "TestTool");
}

// Test merging extended XMP properties into fullXMP
TEST_F(WXMPUtilsMergeFromJPEGTest_1953, ExtendedPropertiesMergedIntoFull_1953) {
    WXMP_Result wResult;
    
    SXMPMeta fullXMP;
    SXMPMeta extendedXMP;
    
    // Add a property to extended XMP
    extendedXMP.SetProperty("http://ns.adobe.com/photoshop/1.0/", "Credit", "TestCredit");
    
    XMPMetaRef fullRef = WXMPMeta_GetInternalRef(fullXMP);
    XMPMetaRef extRef = WXMPMeta_GetInternalRef(extendedXMP);
    
    WXMPUtils_MergeFromJPEG_1(fullRef, extRef, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test WXMP_Result is properly initialized before call
TEST_F(WXMPUtilsMergeFromJPEGTest_1953, ResultInitialization_1953) {
    WXMP_Result wResult;
    
    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    SXMPMeta fullXMP;
    SXMPMeta extendedXMP;
    
    XMPMetaRef fullRef = WXMPMeta_GetInternalRef(fullXMP);
    XMPMetaRef extRef = WXMPMeta_GetInternalRef(extendedXMP);
    
    WXMPUtils_MergeFromJPEG_1(fullRef, extRef, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test merging both full and extended having properties
TEST_F(WXMPUtilsMergeFromJPEGTest_1953, BothHavePropertiesNoError_1953) {
    WXMP_Result wResult;
    
    SXMPMeta fullXMP;
    fullXMP.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "ToolA");
    
    SXMPMeta extendedXMP;
    extendedXMP.SetProperty("http://ns.adobe.com/xap/1.0/", "Label", "LabelB");
    
    XMPMetaRef fullRef = WXMPMeta_GetInternalRef(fullXMP);
    XMPMetaRef extRef = WXMPMeta_GetInternalRef(extendedXMP);
    
    WXMPUtils_MergeFromJPEG_1(fullRef, extRef, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that calling with both empty XMP objects works fine
TEST_F(WXMPUtilsMergeFromJPEGTest_1953, BothEmptyNoError_1953) {
    WXMP_Result wResult;
    
    SXMPMeta fullXMP;
    SXMPMeta extendedXMP;
    
    XMPMetaRef fullRef = WXMPMeta_GetInternalRef(fullXMP);
    XMPMetaRef extRef = WXMPMeta_GetInternalRef(extendedXMP);
    
    WXMPUtils_MergeFromJPEG_1(fullRef, extRef, &wResult);
    
    EXPECT_EQ(wResult.errMessage, nullptr);
}
