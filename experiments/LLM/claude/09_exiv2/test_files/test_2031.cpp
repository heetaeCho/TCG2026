#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "WXMPMeta.hpp"

// The function under test
extern "C" void WXMPMeta_SetProperty_Int_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_Int32 propValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

class WXMPMetaSetPropertyIntTest_2031 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = WXMPMeta_GetXMPMetaRef(meta);
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
};

// Test: Null schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyIntTest_2031, NullSchemaNS_ProducesError_2031) {
    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, nullptr, "propName", 42, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyIntTest_2031, EmptySchemaNS_ProducesError_2031) {
    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "", "propName", 42, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null property name should produce an error
TEST_F(WXMPMetaSetPropertyIntTest_2031, NullPropName_ProducesError_2031) {
    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/", nullptr, 42, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty property name should produce an error
TEST_F(WXMPMetaSetPropertyIntTest_2031, EmptyPropName_ProducesError_2031) {
    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/", "", 42, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Valid parameters should succeed (no error message)
TEST_F(WXMPMetaSetPropertyIntTest_2031, ValidParams_NoError_2031) {
    // Register namespace first
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "TestProp", 42, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: After setting an int property, we can retrieve it with the correct value
TEST_F(WXMPMetaSetPropertyIntTest_2031, SetAndGetPropertyInt_2031) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "IntProp", 12345, 0, &result);
    ASSERT_EQ(result.errMessage, nullptr);

    XMP_Int32 retrievedValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int("http://ns.example.com/test/", "IntProp", &retrievedValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedValue, 12345);
}

// Test: Setting a negative integer value
TEST_F(WXMPMetaSetPropertyIntTest_2031, SetNegativeIntValue_2031) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "NegProp", -9999, 0, &result);
    ASSERT_EQ(result.errMessage, nullptr);

    XMP_Int32 retrievedValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int("http://ns.example.com/test/", "NegProp", &retrievedValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedValue, -9999);
}

// Test: Setting zero value
TEST_F(WXMPMetaSetPropertyIntTest_2031, SetZeroValue_2031) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "ZeroProp", 0, 0, &result);
    ASSERT_EQ(result.errMessage, nullptr);

    XMP_Int32 retrievedValue = -1;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int("http://ns.example.com/test/", "ZeroProp", &retrievedValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedValue, 0);
}

// Test: Setting INT32_MAX boundary value
TEST_F(WXMPMetaSetPropertyIntTest_2031, SetMaxIntValue_2031) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    XMP_Int32 maxVal = 2147483647; // INT32_MAX
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "MaxProp", maxVal, 0, &result);
    ASSERT_EQ(result.errMessage, nullptr);

    XMP_Int32 retrievedValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int("http://ns.example.com/test/", "MaxProp", &retrievedValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedValue, maxVal);
}

// Test: Setting INT32_MIN boundary value
TEST_F(WXMPMetaSetPropertyIntTest_2031, SetMinIntValue_2031) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    XMP_Int32 minVal = (-2147483647 - 1); // INT32_MIN
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "MinProp", minVal, 0, &result);
    ASSERT_EQ(result.errMessage, nullptr);

    XMP_Int32 retrievedValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int("http://ns.example.com/test/", "MinProp", &retrievedValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedValue, minVal);
}

// Test: Overwriting an existing property
TEST_F(WXMPMetaSetPropertyIntTest_2031, OverwriteExistingProperty_2031) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");

    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "OverProp", 100, 0, &result);
    ASSERT_EQ(result.errMessage, nullptr);

    WXMPMeta_SetProperty_Int_1(xmpRef, "http://ns.example.com/test/", "OverProp", 200, 0, &result);
    ASSERT_EQ(result.errMessage, nullptr);

    XMP_Int32 retrievedValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int("http://ns.example.com/test/", "OverProp", &retrievedValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedValue, 200);
}

// Test: Both schema and prop name null
TEST_F(WXMPMetaSetPropertyIntTest_2031, BothNullParams_ProducesError_2031) {
    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, nullptr, nullptr, 42, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Both schema and prop name empty
TEST_F(WXMPMetaSetPropertyIntTest_2031, BothEmptyParams_ProducesError_2031) {
    WXMP_Result result;
    WXMPMeta_SetProperty_Int_1(xmpRef, "", "", 42, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaSetPropertyIntTest_2031, ResultInitialized_2031) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
}
