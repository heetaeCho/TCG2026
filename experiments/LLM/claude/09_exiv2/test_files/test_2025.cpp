#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetProperty_Bool_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_Bool * propValue,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

class WXMPMetaGetPropertyBoolTest_2025 : public ::testing::Test {
protected:
    XMPMeta meta;
    WXMP_Result wResult;

    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPMeta::Initialize();
        wResult = WXMP_Result();
    }

    void TearDown() override {
        // Clean up
    }

    XMPMetaRef GetMetaRef() {
        return reinterpret_cast<XMPMetaRef>(&meta);
    }
};

// Test: Empty schema namespace (null pointer) should produce an error
TEST_F(WXMPMetaGetPropertyBoolTest_2025, NullSchemaNS_ThrowsBadSchema_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), nullptr, "propName", &propValue, &options, &wResult);

    // Should have an error message set
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty string schema namespace should produce an error
TEST_F(WXMPMetaGetPropertyBoolTest_2025, EmptySchemaNS_ThrowsBadSchema_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), "", "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null property name should produce an error
TEST_F(WXMPMetaGetPropertyBoolTest_2025, NullPropName_ThrowsBadXPath_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), "http://ns.example.com/", nullptr, &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty string property name should produce an error
TEST_F(WXMPMetaGetPropertyBoolTest_2025, EmptyPropName_ThrowsBadXPath_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), "http://ns.example.com/", "", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Property not found returns false (int32Result == 0)
TEST_F(WXMPMetaGetPropertyBoolTest_2025, PropertyNotFound_ReturnsFalse_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    // Register namespace first
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), "http://ns.example.com/test/", "nonExistentProp", &propValue, &options, &wResult);

    // No error expected
    EXPECT_EQ(wResult.errMessage, nullptr);
    // Property not found
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Set a bool property to true, then retrieve it
TEST_F(WXMPMetaGetPropertyBoolTest_2025, SetTrueProperty_ReturnsTrue_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.example.com/testbool/";
    const char* propName = "boolProp";

    XMPMeta::RegisterNamespace(schemaNS, "testbool");
    meta.SetProperty_Bool(schemaNS, propName, true, 0);

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));  // found
    EXPECT_NE(propValue, 0);  // true
}

// Test: Set a bool property to false, then retrieve it
TEST_F(WXMPMetaGetPropertyBoolTest_2025, SetFalseProperty_ReturnsFalse_2025) {
    XMP_Bool propValue = 1;  // initialize to true
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.example.com/testboolfalse/";
    const char* propName = "boolPropFalse";

    XMPMeta::RegisterNamespace(schemaNS, "testboolfalse");
    meta.SetProperty_Bool(schemaNS, propName, false, 0);

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));  // found
    EXPECT_EQ(propValue, 0);  // false
}

// Test: Null propValue pointer should not crash (uses voidByte internally)
TEST_F(WXMPMetaGetPropertyBoolTest_2025, NullPropValuePointer_DoesNotCrash_2025) {
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.example.com/testnullval/";
    const char* propName = "someProp";

    XMPMeta::RegisterNamespace(schemaNS, "testnullval");
    meta.SetProperty_Bool(schemaNS, propName, true, 0);

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, propName, nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));  // found
}

// Test: Null options pointer should not crash (uses voidOptionBits internally)
TEST_F(WXMPMetaGetPropertyBoolTest_2025, NullOptionsPointer_DoesNotCrash_2025) {
    XMP_Bool propValue = 0;

    const char* schemaNS = "http://ns.example.com/testnullopt/";
    const char* propName = "someProp2";

    XMPMeta::RegisterNamespace(schemaNS, "testnullopt");
    meta.SetProperty_Bool(schemaNS, propName, true, 0);

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, propName, &propValue, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));  // found
    EXPECT_NE(propValue, 0);  // true
}

// Test: Both propValue and options null should not crash
TEST_F(WXMPMetaGetPropertyBoolTest_2025, BothNullPropValueAndOptions_DoesNotCrash_2025) {
    const char* schemaNS = "http://ns.example.com/testbothnull/";
    const char* propName = "someProp3";

    XMPMeta::RegisterNamespace(schemaNS, "testbothnull");
    meta.SetProperty_Bool(schemaNS, propName, false, 0);

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, propName, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));  // found
}

// Test: Both schema and prop name are empty strings
TEST_F(WXMPMetaGetPropertyBoolTest_2025, BothEmptySchemaAndPropName_ThrowsBadSchema_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), "", "", &propValue, &options, &wResult);

    // Schema check happens first
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid schema but property not set returns not found
TEST_F(WXMPMetaGetPropertyBoolTest_2025, ValidSchemaPropertyNotSet_ReturnsNotFound_2025) {
    XMP_Bool propValue = 1;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.example.com/testnotset/";
    XMPMeta::RegisterNamespace(schemaNS, "testnotset");

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, "missingProp", &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: After deleting a property, GetProperty_Bool should return not found
TEST_F(WXMPMetaGetPropertyBoolTest_2025, DeletedProperty_ReturnsNotFound_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.example.com/testdelete/";
    const char* propName = "deletableProp";

    XMPMeta::RegisterNamespace(schemaNS, "testdelete");
    meta.SetProperty_Bool(schemaNS, propName, true, 0);

    // Verify it exists first
    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, propName, &propValue, &options, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));

    // Delete and verify it's gone
    meta.DeleteProperty(schemaNS, propName);

    wResult = WXMP_Result();
    propValue = 1;
    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, propName, &propValue, &options, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: WXMP_Result is properly initialized when no error occurs
TEST_F(WXMPMetaGetPropertyBoolTest_2025, ResultInitialization_NoError_2025) {
    XMP_Bool propValue = 0;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.example.com/testresult/";
    XMPMeta::RegisterNamespace(schemaNS, "testresult");

    WXMPMeta_GetProperty_Bool_1(GetMetaRef(), schemaNS, "anyProp", &propValue, &options, &wResult);

    // No error
    EXPECT_EQ(wResult.errMessage, nullptr);
}
