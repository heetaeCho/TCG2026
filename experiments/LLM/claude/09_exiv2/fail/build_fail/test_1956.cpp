#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_RemoveProperties_1(
    XMPMetaRef wxmpObj,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_OptionBits options,
    WXMP_Result * wResult);

// We need XMPMeta to create valid objects
#include "XMPCore/XMPCoreDefines.h"
#include "TXMPMeta.hpp"
#include "XMP.hpp"

class WXMPUtilsRemovePropertiesTest_1956 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP SDK if needed
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that passing a null wxmpObj results in an error
TEST_F(WXMPUtilsRemovePropertiesTest_1956, NullXmpObjThrowsError_1956) {
    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(0, "http://ns.adobe.com/xap/1.0/", "Creator", 0, &wResult);
    // The function should report an error when wxmpObj is null
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test that passing null schemaNS defaults it to empty string and does not error
TEST_F(WXMPUtilsRemovePropertiesTest_1956, NullSchemaNSDefaultsToEmpty_1956) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(metaRef, nullptr, nullptr, 0, &wResult);
    // Should not produce an error - null schemaNS and propName are defaulted to ""
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that passing null propName defaults it to empty string and does not error
TEST_F(WXMPUtilsRemovePropertiesTest_1956, NullPropNameDefaultsToEmpty_1956) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(metaRef, "http://ns.adobe.com/xap/1.0/", nullptr, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test normal operation: remove a specific property
TEST_F(WXMPUtilsRemovePropertiesTest_1956, RemoveSpecificProperty_1956) {
    SXMPMeta meta;
    const char* kNS = "http://ns.adobe.com/xap/1.0/";

    // Set a property first
    meta.SetProperty(kNS, "CreatorTool", "TestTool");

    // Verify it exists
    std::string value;
    ASSERT_TRUE(meta.GetProperty(kNS, "CreatorTool", &value, nullptr));
    ASSERT_EQ(value, "TestTool");

    XMPMetaRef metaRef = meta.GetInternalRef();
    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(metaRef, kNS, "CreatorTool", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // Verify property is removed
    EXPECT_FALSE(meta.GetProperty(kNS, "CreatorTool", &value, nullptr));
}

// Test normal operation: remove all properties in a schema
TEST_F(WXMPUtilsRemovePropertiesTest_1956, RemoveAllPropertiesInSchema_1956) {
    SXMPMeta meta;
    const char* kNS = "http://ns.adobe.com/xap/1.0/";

    meta.SetProperty(kNS, "CreatorTool", "TestTool");
    meta.SetProperty(kNS, "CreateDate", "2023-01-01");

    XMPMetaRef metaRef = meta.GetInternalRef();
    WXMP_Result wResult;
    // Empty propName with a specific schema should remove all properties in that schema
    WXMPUtils_RemoveProperties_1(metaRef, kNS, "", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    std::string value;
    EXPECT_FALSE(meta.GetProperty(kNS, "CreatorTool", &value, nullptr));
    EXPECT_FALSE(meta.GetProperty(kNS, "CreateDate", &value, nullptr));
}

// Test normal operation: remove with empty schemaNS and empty propName
TEST_F(WXMPUtilsRemovePropertiesTest_1956, RemoveWithEmptySchemaAndProp_1956) {
    SXMPMeta meta;
    const char* kNS1 = "http://ns.adobe.com/xap/1.0/";
    const char* kNS2 = "http://purl.org/dc/elements/1.1/";

    meta.SetProperty(kNS1, "CreatorTool", "TestTool");
    meta.SetProperty(kNS2, "title", "TestTitle");

    XMPMetaRef metaRef = meta.GetInternalRef();
    WXMP_Result wResult;
    // Both empty: should remove all properties
    WXMPUtils_RemoveProperties_1(metaRef, "", "", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with valid object but non-existent property
TEST_F(WXMPUtilsRemovePropertiesTest_1956, RemoveNonExistentProperty_1956) {
    SXMPMeta meta;
    const char* kNS = "http://ns.adobe.com/xap/1.0/";

    XMPMetaRef metaRef = meta.GetInternalRef();
    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(metaRef, kNS, "NonExistentProp", 0, &wResult);
    // Should not error when removing a property that doesn't exist
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with empty metadata object
TEST_F(WXMPUtilsRemovePropertiesTest_1956, RemoveFromEmptyMeta_1956) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(metaRef, "", "", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that WXMP_Result is properly initialized on success
TEST_F(WXMPUtilsRemovePropertiesTest_1956, ResultProperlyInitializedOnSuccess_1956) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(metaRef, "http://ns.adobe.com/xap/1.0/", "SomeProp", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that error message is set when wxmpObj is 0
TEST_F(WXMPUtilsRemovePropertiesTest_1956, ErrorMessageSetForNullObj_1956) {
    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(0, "", "", 0, &wResult);
    ASSERT_NE(wResult.errMessage, nullptr);
    // The error message should mention something about null pointer
    EXPECT_TRUE(std::strlen(wResult.errMessage) > 0);
}

// Test with options parameter
TEST_F(WXMPUtilsRemovePropertiesTest_1956, RemoveWithOptions_1956) {
    SXMPMeta meta;
    const char* kNS = "http://ns.adobe.com/xap/1.0/";
    meta.SetProperty(kNS, "CreatorTool", "TestTool");

    XMPMetaRef metaRef = meta.GetInternalRef();
    WXMP_Result wResult;
    // Pass some options value
    WXMPUtils_RemoveProperties_1(metaRef, kNS, "CreatorTool", 0x0001, &wResult);
    // We just verify it doesn't crash and handles the options
    // The actual behavior depends on the options interpretation
    // No assertion on errMessage as behavior depends on option validity
}

// Test both schemaNS and propName are null
TEST_F(WXMPUtilsRemovePropertiesTest_1956, BothNullSchemaAndPropName_1956) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPUtils_RemoveProperties_1(metaRef, nullptr, nullptr, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}
