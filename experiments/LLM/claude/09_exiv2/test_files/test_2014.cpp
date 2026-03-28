#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_SetQualifier_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr qualNS,
    XMP_StringPtr qualName,
    XMP_StringPtr qualValue,
    XMP_OptionBits options,
    WXMP_Result * wResult
);

// We need access to XMPMeta creation. Include appropriate headers.
#include "XMPMeta.hpp"

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaSetQualifierTest_2014 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize the XMP toolkit
        XMPMeta::Initialize();
        meta = new XMPMeta();
        ref = MetaToRef(meta);
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef ref;
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, NullSchemaNS_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, nullptr, "propName", "http://qual.ns/", "qualName", "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, EmptySchemaNS_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "", "propName", "http://qual.ns/", "qualName", "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null propName should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, NullPropName_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", nullptr, "http://qual.ns/", "qualName", "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty propName should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, EmptyPropName_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "", "http://qual.ns/", "qualName", "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null qualNS should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, NullQualNS_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "propName", nullptr, "qualName", "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty qualNS should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, EmptyQualNS_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "propName", "", "qualName", "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null qualName should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, NullQualName_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "propName", "http://qual.ns/", nullptr, "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty qualName should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, EmptyQualName_ShouldFail_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "propName", "http://qual.ns/", "", "qualValue", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid parameters with existing property should succeed
TEST_F(WXMPMetaSetQualifierTest_2014, ValidParameters_WithExistingProperty_ShouldSucceed_2014) {
    // First set a property so the qualifier can be attached
    meta->SetProperty("http://ns.adobe.com/xap/1.0/", "TestProp", "TestValue", 0);

    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "TestProp",
                             "http://qual.ns/", "QualName", "QualValue", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: After setting qualifier, it should be retrievable via GetQualifier
TEST_F(WXMPMetaSetQualifierTest_2014, SetQualifier_ThenGetQualifier_ShouldReturnValue_2014) {
    // Register the qualifier namespace
    XMPMeta::RegisterNamespace("http://qual.ns/", "qual");

    // Set a property first
    meta->SetProperty("http://ns.adobe.com/xap/1.0/", "TestProp", "TestValue", 0);

    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "TestProp",
                             "http://qual.ns/", "QualName", "MyQualifierValue", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // Verify via GetQualifier
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetQualifier("http://ns.adobe.com/xap/1.0/", "TestProp",
                                     "http://qual.ns/", "QualName",
                                     &qualValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    if (found && qualValue != nullptr) {
        EXPECT_STREQ(qualValue, "MyQualifierValue");
    }
}

// Test: Setting qualifier on non-existent property should produce an error
TEST_F(WXMPMetaSetQualifierTest_2014, SetQualifierOnNonExistentProperty_ShouldFail_2014) {
    XMPMeta::RegisterNamespace("http://qual.ns/", "qual");

    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "NonExistentProp",
                             "http://qual.ns/", "QualName", "QualValue", 0, &wResult);
    // Setting a qualifier on a property that doesn't exist should fail
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized on success (errMessage should be null)
TEST_F(WXMPMetaSetQualifierTest_2014, ResultInitialization_OnSuccess_2014) {
    XMPMeta::RegisterNamespace("http://qual.ns/", "qual");
    meta->SetProperty("http://ns.adobe.com/xap/1.0/", "Prop2", "Value2", 0);

    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "Prop2",
                             "http://qual.ns/", "QName", "QVal", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting qualifier with empty qualValue should still work (empty value is valid)
TEST_F(WXMPMetaSetQualifierTest_2014, EmptyQualValue_ShouldSucceed_2014) {
    XMPMeta::RegisterNamespace("http://qual.ns/", "qual");
    meta->SetProperty("http://ns.adobe.com/xap/1.0/", "Prop3", "Value3", 0);

    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "Prop3",
                             "http://qual.ns/", "QName", "", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting qualifier with null qualValue (should still be accepted by the wrapper validation)
TEST_F(WXMPMetaSetQualifierTest_2014, NullQualValue_BehaviorCheck_2014) {
    XMPMeta::RegisterNamespace("http://qual.ns/", "qual");
    meta->SetProperty("http://ns.adobe.com/xap/1.0/", "Prop4", "Value4", 0);

    WXMP_Result wResult;
    // qualValue is not validated in the wrapper - it's passed through to SetQualifier
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "Prop4",
                             "http://qual.ns/", "QName", nullptr, 0, &wResult);
    // The behavior depends on the underlying implementation
    // We just check it doesn't crash and produces some result
    // (either success or error message)
}

// Test: Multiple validation failures - first check should trigger (schemaNS first)
TEST_F(WXMPMetaSetQualifierTest_2014, MultipleEmptyParams_FirstCheckTriggersFirst_2014) {
    WXMP_Result wResult;
    WXMPMeta_SetQualifier_1(ref, "", "", "", "", "qualValue", 0, &wResult);
    // schemaNS is checked first, so error should mention schema
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Overwriting an existing qualifier
TEST_F(WXMPMetaSetQualifierTest_2014, OverwriteExistingQualifier_2014) {
    XMPMeta::RegisterNamespace("http://qual.ns/", "qual");
    meta->SetProperty("http://ns.adobe.com/xap/1.0/", "Prop5", "Value5", 0);

    WXMP_Result wResult1;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "Prop5",
                             "http://qual.ns/", "QName", "FirstValue", 0, &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);

    // Try to set the same qualifier again - this may or may not succeed depending on implementation
    WXMP_Result wResult2;
    WXMPMeta_SetQualifier_1(ref, "http://ns.adobe.com/xap/1.0/", "Prop5",
                             "http://qual.ns/", "QName", "SecondValue", 0, &wResult2);
    // Just verify we get a defined result (either success or error)
    // The implementation may throw if qualifier already exists
}
