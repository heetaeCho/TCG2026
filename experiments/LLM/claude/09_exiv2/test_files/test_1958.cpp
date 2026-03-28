#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore/XMPCoreDefn.h"
#include "XMPMeta.hpp"
#include "XMPUtils.hpp"

// Declaration of the function under test
extern "C" void WXMPUtils_DuplicateSubtree_1(
    XMPMetaRef wSource,
    XMPMetaRef wDest,
    XMP_StringPtr sourceNS,
    XMP_StringPtr sourceRoot,
    XMP_StringPtr destNS,
    XMP_StringPtr destRoot,
    XMP_OptionBits options,
    WXMP_Result * wResult);

class WXMPUtilsDuplicateSubtreeTest_1958 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        SXMPMeta::Initialize();
        
        source_ = new SXMPMeta();
        dest_ = new SXMPMeta();
    }

    void TearDown() override {
        delete source_;
        delete dest_;
        SXMPMeta::Terminate();
    }

    XMPMetaRef GetSourceRef() {
        return WtoXMPMeta_Ref(*source_);
    }

    XMPMetaRef GetDestRef() {
        return WtoXMPMeta_Ref(*dest_);
    }

    SXMPMeta* source_;
    SXMPMeta* dest_;
};

// Test: Null destination pointer should set error message about null output XMP pointer
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, NullDestThrowsBadParam_1958) {
    WXMP_Result result;
    XMPMetaRef sourceRef = GetSourceRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, 0,
        "http://ns.example.com/", "Root",
        "http://ns.example.com/", "Root",
        0, &result);
    
    EXPECT_NE(result.errMessage, nullptr);
    EXPECT_TRUE(std::strstr(result.errMessage, "null") != nullptr ||
                std::strstr(result.errMessage, "Output XMP pointer is null") != nullptr);
}

// Test: Null sourceNS should set error message about empty schema
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, NullSourceNSThrowsBadSchema_1958) {
    WXMP_Result result;
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        nullptr, "Root",
        "http://ns.example.com/", "Root",
        0, &result);
    
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty sourceNS string should set error message about empty schema
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, EmptySourceNSThrowsBadSchema_1958) {
    WXMP_Result result;
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        "", "Root",
        "http://ns.example.com/", "Root",
        0, &result);
    
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null sourceRoot should set error message about empty root name
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, NullSourceRootThrowsBadXPath_1958) {
    WXMP_Result result;
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        "http://ns.example.com/", nullptr,
        "http://ns.example.com/", "Root",
        0, &result);
    
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty sourceRoot string should set error message about empty root name
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, EmptySourceRootThrowsBadXPath_1958) {
    WXMP_Result result;
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        "http://ns.example.com/", "",
        "http://ns.example.com/", "Root",
        0, &result);
    
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Valid parameters with existing property should succeed (no error)
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, ValidParamsNoError_1958) {
    WXMP_Result result;
    
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    const char* kPropName = "CreatorTool";
    
    source_->SetProperty(kNS, kPropName, "TestValue");
    
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        kNS, kPropName,
        nullptr, nullptr,
        0, &result);
    
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: destNS null defaults to sourceNS (no error expected)
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, NullDestNSDefaultsToSourceNS_1958) {
    WXMP_Result result;
    
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    const char* kPropName = "CreatorTool";
    
    source_->SetProperty(kNS, kPropName, "TestValue");
    
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        kNS, kPropName,
        nullptr, nullptr,
        0, &result);
    
    EXPECT_EQ(result.errMessage, nullptr);
    
    // Verify the property was duplicated
    std::string value;
    EXPECT_TRUE(dest_->GetProperty(kNS, kPropName, &value, nullptr));
    EXPECT_EQ(value, "TestValue");
}

// Test: destRoot null defaults to sourceRoot (no error expected)
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, NullDestRootDefaultsToSourceRoot_1958) {
    WXMP_Result result;
    
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    const char* kPropName = "CreatorTool";
    
    source_->SetProperty(kNS, kPropName, "SomeValue");
    
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        kNS, kPropName,
        kNS, nullptr,
        0, &result);
    
    EXPECT_EQ(result.errMessage, nullptr);
    
    std::string value;
    EXPECT_TRUE(dest_->GetProperty(kNS, kPropName, &value, nullptr));
    EXPECT_EQ(value, "SomeValue");
}

// Test: Duplicate to different destRoot
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, DuplicateToDifferentDestRoot_1958) {
    WXMP_Result result;
    
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    const char* kSourceRoot = "CreatorTool";
    const char* kDestRoot = "Label";
    
    source_->SetProperty(kNS, kSourceRoot, "ToolName");
    
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        kNS, kSourceRoot,
        kNS, kDestRoot,
        0, &result);
    
    EXPECT_EQ(result.errMessage, nullptr);
    
    std::string value;
    EXPECT_TRUE(dest_->GetProperty(kNS, kDestRoot, &value, nullptr));
    EXPECT_EQ(value, "ToolName");
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, ResultInitializedProperly_1958) {
    WXMP_Result result;
    
    // Verify default initialization
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, 0u);
}

// Test: Source with no matching property - should not error but property won't exist
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, SourcePropertyDoesNotExist_1958) {
    WXMP_Result result;
    
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    const char* kPropName = "NonExistentProp";
    
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        kNS, kPropName,
        nullptr, nullptr,
        0, &result);
    
    // The function may or may not error - observe behavior
    // If no property exists, it might just be a no-op
    // This test documents the actual behavior
}

// Test: Both sourceNS and sourceRoot are valid but destNS is empty string (not null)
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, EmptyDestNSStringBehavior_1958) {
    WXMP_Result result;
    
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    const char* kPropName = "CreatorTool";
    
    source_->SetProperty(kNS, kPropName, "TestValue");
    
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    // Empty string for destNS is not null, so it won't be defaulted
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        kNS, kPropName,
        "", kPropName,
        0, &result);
    
    // Empty destNS might cause an error from the underlying DuplicateSubtree
    // This documents the behavior
}

// Test: Options parameter zero is valid
TEST_F(WXMPUtilsDuplicateSubtreeTest_1958, ZeroOptionsIsValid_1958) {
    WXMP_Result result;
    
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    const char* kPropName = "CreatorTool";
    
    source_->SetProperty(kNS, kPropName, "Value");
    
    XMPMetaRef sourceRef = GetSourceRef();
    XMPMetaRef destRef = GetDestRef();
    
    WXMPUtils_DuplicateSubtree_1(
        sourceRef, destRef,
        kNS, kPropName,
        nullptr, nullptr,
        0, &result);
    
    EXPECT_EQ(result.errMessage, nullptr);
}
