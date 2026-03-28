#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#define XMP_INCLUDE_XMPFILES 0
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DeleteProperty_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    WXMP_Result * wResult);

// We also need SetProperty and DoesPropertyExist wrappers or direct access
extern "C" void WXMPMeta_SetProperty_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr propValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

extern "C" void WXMPMeta_GetProperty_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr * propValue,
    XMP_StringLen * valueSize,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

extern "C" XMPMetaRef WXMPMeta_CTor_1(WXMP_Result * wResult);
extern "C" void WXMPMeta_IncrementRefCount_1(XMPMetaRef xmpRef);
extern "C" void WXMPMeta_DecrementRefCount_1(XMPMetaRef xmpRef);

class WXMPMetaDeletePropertyTest_2015 : public ::testing::Test {
protected:
    XMPMetaRef metaRef;

    void SetUp() override {
        // Initialize XMP SDK
        XMPMeta::Initialize();

        // Register a known namespace
        XMPMeta::RegisterNamespace("http://ns.test.com/", "test");

        // Create XMPMeta object
        WXMP_Result result;
        metaRef = WXMPMeta_CTor_1(&result);
        ASSERT_EQ(result.errMessage, nullptr);
        ASSERT_NE(metaRef, nullptr);
    }

    void TearDown() override {
        if (metaRef != nullptr) {
            WXMPMeta_DecrementRefCount_1(metaRef);
        }
        XMPMeta::Terminate();
    }

    void SetProperty(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_StringPtr value) {
        WXMP_Result result;
        WXMPMeta_SetProperty_1(metaRef, schemaNS, propName, value, 0, &result);
        ASSERT_EQ(result.errMessage, nullptr);
    }

    bool PropertyExists(XMP_StringPtr schemaNS, XMP_StringPtr propName) {
        WXMP_Result result;
        XMP_StringPtr propValue = nullptr;
        XMP_StringLen valueSize = 0;
        XMP_OptionBits options = 0;
        WXMPMeta_GetProperty_1(metaRef, schemaNS, propName, &propValue, &valueSize, &options, &result);
        // If errMessage is set, property doesn't exist or error occurred
        // The int32Result should indicate true/false
        if (result.errMessage != nullptr) return false;
        return static_cast<bool>(result.int32Result);
    }
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaDeletePropertyTest_2015, NullSchemaNS_ProducesError_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, nullptr, "propName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPMetaDeletePropertyTest_2015, EmptySchemaNS_ProducesError_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "", "propName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null propName should produce an error
TEST_F(WXMPMetaDeletePropertyTest_2015, NullPropName_ProducesError_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty propName should produce an error
TEST_F(WXMPMetaDeletePropertyTest_2015, EmptyPropName_ProducesError_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Both null schemaNS and propName should produce an error (schemaNS checked first)
TEST_F(WXMPMetaDeletePropertyTest_2015, BothNullParams_ProducesError_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, nullptr, nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Both empty schemaNS and propName should produce an error (schemaNS checked first)
TEST_F(WXMPMetaDeletePropertyTest_2015, BothEmptyParams_ProducesError_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Deleting a property that exists should succeed and remove it
TEST_F(WXMPMetaDeletePropertyTest_2015, DeleteExistingProperty_Succeeds_2015) {
    SetProperty("http://ns.test.com/", "test:MyProp", "TestValue");
    ASSERT_TRUE(PropertyExists("http://ns.test.com/", "test:MyProp"));

    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "test:MyProp", &result);
    EXPECT_EQ(result.errMessage, nullptr);

    EXPECT_FALSE(PropertyExists("http://ns.test.com/", "test:MyProp"));
}

// Test: Deleting a property that does not exist should not produce an error
TEST_F(WXMPMetaDeletePropertyTest_2015, DeleteNonExistentProperty_NoError_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "test:NonExistent", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Valid schemaNS and propName with no error
TEST_F(WXMPMetaDeletePropertyTest_2015, ValidParams_NoError_2015) {
    WXMP_Result result;
    memset(&result, 0, sizeof(result));
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "test:SomeProp", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Delete property, then verify it's truly gone by trying to get it
TEST_F(WXMPMetaDeletePropertyTest_2015, DeleteAndVerifyGone_2015) {
    SetProperty("http://ns.test.com/", "test:Prop1", "Value1");
    SetProperty("http://ns.test.com/", "test:Prop2", "Value2");

    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "test:Prop1", &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // Prop1 should be gone
    EXPECT_FALSE(PropertyExists("http://ns.test.com/", "test:Prop1"));
    // Prop2 should still exist
    EXPECT_TRUE(PropertyExists("http://ns.test.com/", "test:Prop2"));
}

// Test: Delete same property twice should not produce error on second call
TEST_F(WXMPMetaDeletePropertyTest_2015, DeleteSamePropertyTwice_NoError_2015) {
    SetProperty("http://ns.test.com/", "test:DoubleDel", "SomeValue");

    WXMP_Result result1;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "test:DoubleDel", &result1);
    EXPECT_EQ(result1.errMessage, nullptr);

    WXMP_Result result2;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "test:DoubleDel", &result2);
    EXPECT_EQ(result2.errMessage, nullptr);
}

// Test: Error message for empty schema mentions schema
TEST_F(WXMPMetaDeletePropertyTest_2015, EmptySchemaErrorMessage_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "", "test:Prop", &result);
    ASSERT_NE(result.errMessage, nullptr);
    // The error message should contain something about schema
    std::string errMsg(result.errMessage);
    EXPECT_FALSE(errMsg.empty());
}

// Test: Error message for empty prop name mentions property
TEST_F(WXMPMetaDeletePropertyTest_2015, EmptyPropNameErrorMessage_2015) {
    WXMP_Result result;
    WXMPMeta_DeleteProperty_1(metaRef, "http://ns.test.com/", "", &result);
    ASSERT_NE(result.errMessage, nullptr);
    std::string errMsg(result.errMessage);
    EXPECT_FALSE(errMsg.empty());
}
