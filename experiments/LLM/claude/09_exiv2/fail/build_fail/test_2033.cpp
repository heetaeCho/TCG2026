#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_SetProperty_Float_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    double propValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaSetPropertyFloatTest_2033 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        // Register a test namespace
        XMPMeta::RegisterNamespace("http://ns.test.com/test/", "test");
    }

    void TearDown() override {
        delete meta;
        meta = nullptr;
    }

    XMPMeta* meta = nullptr;
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaSetPropertyFloatTest_2033, NullSchemaNS_ReturnsError_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), nullptr, "propName", 3.14, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS string should produce an error
TEST_F(WXMPMetaSetPropertyFloatTest_2033, EmptySchemaNS_ReturnsError_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "", "propName", 3.14, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null propName should produce an error
TEST_F(WXMPMetaSetPropertyFloatTest_2033, NullPropName_ReturnsError_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", nullptr, 3.14, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty propName string should produce an error
TEST_F(WXMPMetaSetPropertyFloatTest_2033, EmptyPropName_ReturnsError_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "", 3.14, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid parameters should succeed (no error)
TEST_F(WXMPMetaSetPropertyFloatTest_2033, ValidParams_NoError_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "floatProp", 3.14, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: After setting float property, it can be retrieved
TEST_F(WXMPMetaSetPropertyFloatTest_2033, SetAndGetFloat_ValueRoundTrips_2033) {
    WXMP_Result wResult;
    double setValue = 2.71828;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "floatProp", setValue, 0, &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    double getValue = 0.0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Float("http://ns.test.com/test/", "floatProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_NEAR(getValue, setValue, 0.0001);
}

// Test: Setting zero value
TEST_F(WXMPMetaSetPropertyFloatTest_2033, SetZeroFloat_Succeeds_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "zeroProp", 0.0, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    double getValue = -1.0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Float("http://ns.test.com/test/", "zeroProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_DOUBLE_EQ(getValue, 0.0);
}

// Test: Setting negative float value
TEST_F(WXMPMetaSetPropertyFloatTest_2033, SetNegativeFloat_Succeeds_2033) {
    WXMP_Result wResult;
    double negValue = -99.5;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "negProp", negValue, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    double getValue = 0.0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Float("http://ns.test.com/test/", "negProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_NEAR(getValue, negValue, 0.0001);
}

// Test: Setting a very large float value
TEST_F(WXMPMetaSetPropertyFloatTest_2033, SetLargeFloat_Succeeds_2033) {
    WXMP_Result wResult;
    double largeValue = 1.0e+300;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "largeProp", largeValue, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting a very small float value
TEST_F(WXMPMetaSetPropertyFloatTest_2033, SetSmallFloat_Succeeds_2033) {
    WXMP_Result wResult;
    double smallValue = 1.0e-300;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "smallProp", smallValue, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Overwriting an existing float property
TEST_F(WXMPMetaSetPropertyFloatTest_2033, OverwriteExistingFloat_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "overwriteProp", 1.0, 0, &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "overwriteProp", 2.0, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    double getValue = 0.0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Float("http://ns.test.com/test/", "overwriteProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_NEAR(getValue, 2.0, 0.0001);
}

// Test: Both schemaNS and propName are null
TEST_F(WXMPMetaSetPropertyFloatTest_2033, BothNullSchemaAndProp_ReturnsError_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), nullptr, nullptr, 1.0, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Both schemaNS and propName are empty
TEST_F(WXMPMetaSetPropertyFloatTest_2033, BothEmptySchemaAndProp_ReturnsError_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "", "", 1.0, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: WXMP_Result is properly initialized on success
TEST_F(WXMPMetaSetPropertyFloatTest_2033, ResultInitializedOnSuccess_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "initProp", 42.0, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Property exists after setting it
TEST_F(WXMPMetaSetPropertyFloatTest_2033, PropertyExistsAfterSet_2033) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Float_1(MetaToRef(meta), "http://ns.test.com/test/", "existsProp", 7.77, 0, &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    bool exists = meta->DoesPropertyExist("http://ns.test.com/test/", "existsProp");
    EXPECT_TRUE(exists);
}
