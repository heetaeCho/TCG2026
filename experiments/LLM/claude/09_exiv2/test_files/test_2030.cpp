#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_SetProperty_Bool_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_Bool propValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

// We also need the WtoXMPMeta_Ptr or equivalent, and creation functions
extern "C" XMPMetaRef WXMPMeta_CTor_1(WXMP_Result * wResult);
extern "C" void WXMPMeta_DTor_1(XMPMetaRef xmpRef);
extern "C" void WXMPMeta_GetProperty_Bool_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_Bool * propValue,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

static const char* kTestNS = "http://ns.test.com/test/";
static const char* kTestProp = "TestBoolProp";

class WXMPMetaSetPropertyBoolTest_2030 : public ::testing::Test {
protected:
    XMPMetaRef metaRef;
    WXMP_Result result;

    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPMeta::Initialize();
        // Register a test namespace
        XMPMeta::RegisterNamespace(kTestNS, "test:");

        WXMP_Result ctorResult;
        metaRef = WXMPMeta_CTor_1(&ctorResult);
        ASSERT_EQ(ctorResult.errMessage, nullptr);
        ASSERT_NE(metaRef, 0);
        memset(&result, 0, sizeof(result));
    }

    void TearDown() override {
        if (metaRef != 0) {
            WXMPMeta_DTor_1(metaRef);
            metaRef = 0;
        }
        XMPMeta::Terminate();
    }
};

// Test: Null schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyBoolTest_2030, NullSchemaNS_ProducesError_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, nullptr, kTestProp, true, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(strstr(result.errMessage, "Empty schema namespace URI") != nullptr ||
                    strstr(result.errMessage, "schema") != nullptr);
    }
}

// Test: Empty schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyBoolTest_2030, EmptySchemaNS_ProducesError_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, "", kTestProp, true, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null property name should produce an error
TEST_F(WXMPMetaSetPropertyBoolTest_2030, NullPropName_ProducesError_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, nullptr, true, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(strstr(result.errMessage, "Empty property name") != nullptr ||
                    strstr(result.errMessage, "property") != nullptr);
    }
}

// Test: Empty property name should produce an error
TEST_F(WXMPMetaSetPropertyBoolTest_2030, EmptyPropName_ProducesError_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, "", true, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Setting a bool property with value true succeeds
TEST_F(WXMPMetaSetPropertyBoolTest_2030, SetBoolTrue_Succeeds_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, kTestProp, true, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // Verify by reading back
    XMP_Bool readValue = false;
    XMP_OptionBits opts = 0;
    WXMP_Result getResult;
    memset(&getResult, 0, sizeof(getResult));
    WXMPMeta_GetProperty_Bool_1(metaRef, kTestNS, kTestProp, &readValue, &opts, &getResult);
    EXPECT_EQ(getResult.errMessage, nullptr);
    EXPECT_TRUE(getResult.int32Result); // property found
    EXPECT_TRUE(readValue);
}

// Test: Setting a bool property with value false succeeds
TEST_F(WXMPMetaSetPropertyBoolTest_2030, SetBoolFalse_Succeeds_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, kTestProp, false, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_Bool readValue = true;
    XMP_OptionBits opts = 0;
    WXMP_Result getResult;
    memset(&getResult, 0, sizeof(getResult));
    WXMPMeta_GetProperty_Bool_1(metaRef, kTestNS, kTestProp, &readValue, &opts, &getResult);
    EXPECT_EQ(getResult.errMessage, nullptr);
    EXPECT_TRUE(getResult.int32Result); // property found
    EXPECT_FALSE(readValue);
}

// Test: Overwriting a bool property value
TEST_F(WXMPMetaSetPropertyBoolTest_2030, OverwriteBoolProperty_Succeeds_2030) {
    // Set to true first
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, kTestProp, true, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // Overwrite with false
    WXMP_Result result2;
    memset(&result2, 0, sizeof(result2));
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, kTestProp, false, 0, &result2);
    EXPECT_EQ(result2.errMessage, nullptr);

    // Verify the overwritten value
    XMP_Bool readValue = true;
    XMP_OptionBits opts = 0;
    WXMP_Result getResult;
    memset(&getResult, 0, sizeof(getResult));
    WXMPMeta_GetProperty_Bool_1(metaRef, kTestNS, kTestProp, &readValue, &opts, &getResult);
    EXPECT_EQ(getResult.errMessage, nullptr);
    EXPECT_TRUE(getResult.int32Result);
    EXPECT_FALSE(readValue);
}

// Test: Both schemaNS and propName are null
TEST_F(WXMPMetaSetPropertyBoolTest_2030, BothNullParams_ProducesError_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, nullptr, nullptr, true, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Both schemaNS and propName are empty strings
TEST_F(WXMPMetaSetPropertyBoolTest_2030, BothEmptyParams_ProducesError_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, "", "", true, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Setting property with options=0 (default) is successful
TEST_F(WXMPMetaSetPropertyBoolTest_2030, DefaultOptions_Succeeds_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, "BoolPropDefault", true, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized with no error on success
TEST_F(WXMPMetaSetPropertyBoolTest_2030, ResultCleanOnSuccess_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, kTestProp, true, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Error message for empty schema mentions schema
TEST_F(WXMPMetaSetPropertyBoolTest_2030, ErrorMessageForEmptySchema_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, "", kTestProp, true, 0, &result);
    ASSERT_NE(result.errMessage, nullptr);
    // The error message should reference schema
    EXPECT_TRUE(strstr(result.errMessage, "schema") != nullptr ||
                strstr(result.errMessage, "Schema") != nullptr);
}

// Test: Error message for empty prop name mentions property
TEST_F(WXMPMetaSetPropertyBoolTest_2030, ErrorMessageForEmptyPropName_2030) {
    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, "", true, 0, &result);
    ASSERT_NE(result.errMessage, nullptr);
    EXPECT_TRUE(strstr(result.errMessage, "property") != nullptr ||
                strstr(result.errMessage, "Property") != nullptr ||
                strstr(result.errMessage, "name") != nullptr);
}

// Test: Multiple different properties can be set
TEST_F(WXMPMetaSetPropertyBoolTest_2030, MultipleProperties_Succeeds_2030) {
    WXMP_Result r1, r2;
    memset(&r1, 0, sizeof(r1));
    memset(&r2, 0, sizeof(r2));

    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, "BoolProp1", true, 0, &r1);
    EXPECT_EQ(r1.errMessage, nullptr);

    WXMPMeta_SetProperty_Bool_1(metaRef, kTestNS, "BoolProp2", false, 0, &r2);
    EXPECT_EQ(r2.errMessage, nullptr);

    // Verify both
    XMP_Bool val1 = false, val2 = true;
    XMP_OptionBits opts = 0;
    WXMP_Result gr1, gr2;
    memset(&gr1, 0, sizeof(gr1));
    memset(&gr2, 0, sizeof(gr2));

    WXMPMeta_GetProperty_Bool_1(metaRef, kTestNS, "BoolProp1", &val1, &opts, &gr1);
    EXPECT_EQ(gr1.errMessage, nullptr);
    EXPECT_TRUE(val1);

    WXMPMeta_GetProperty_Bool_1(metaRef, kTestNS, "BoolProp2", &val2, &opts, &gr2);
    EXPECT_EQ(gr2.errMessage, nullptr);
    EXPECT_FALSE(val2);
}
