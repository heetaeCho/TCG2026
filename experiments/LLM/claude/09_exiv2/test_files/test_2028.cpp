#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetProperty_Float_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    double * propValue,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

// Helper to create an XMPMeta object and get its ref
static XMPMetaRef CreateXMPMetaRef() {
    XMPMeta* meta = new XMPMeta();
    return (XMPMetaRef)meta;
}

static void DestroyXMPMetaRef(XMPMetaRef ref) {
    XMPMeta* meta = (XMPMeta*)ref;
    delete meta;
}

class WXMPMetaGetPropertyFloatTest_2028 : public ::testing::Test {
protected:
    XMPMetaRef xmpRef;
    WXMP_Result wResult;

    void SetUp() override {
        // Initialize XMP toolkit
        XMPMeta::Initialize();
        xmpRef = CreateXMPMetaRef();
        std::memset(&wResult, 0, sizeof(wResult));
    }

    void TearDown() override {
        DestroyXMPMetaRef(xmpRef);
        XMPMeta::Terminate();
    }
};

// Test: Null schema namespace pointer should cause an error
TEST_F(WXMPMetaGetPropertyFloatTest_2028, NullSchemaNS_ShouldSetError_2028) {
    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, nullptr, "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace string should cause an error
TEST_F(WXMPMetaGetPropertyFloatTest_2028, EmptySchemaNS_ShouldSetError_2028) {
    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, "", "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null property name pointer should cause an error
TEST_F(WXMPMetaGetPropertyFloatTest_2028, NullPropName_ShouldSetError_2028) {
    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", nullptr, &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name string should cause an error
TEST_F(WXMPMetaGetPropertyFloatTest_2028, EmptyPropName_ShouldSetError_2028) {
    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Property not found should return false (int32Result == 0)
TEST_F(WXMPMetaGetPropertyFloatTest_2028, PropertyNotFound_ShouldReturnFalse_2028) {
    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "NonExistentProp", &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Null propValue pointer should not crash (uses voidDouble internally)
TEST_F(WXMPMetaGetPropertyFloatTest_2028, NullPropValue_ShouldNotCrash_2028) {
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "NonExistentProp", nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Null options pointer should not crash (uses voidOptionBits internally)
TEST_F(WXMPMetaGetPropertyFloatTest_2028, NullOptions_ShouldNotCrash_2028) {
    double propValue = 0.0;

    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "NonExistentProp", &propValue, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Both propValue and options null should not crash
TEST_F(WXMPMetaGetPropertyFloatTest_2028, NullPropValueAndOptions_ShouldNotCrash_2028) {
    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "NonExistentProp", nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Set a float property and then retrieve it
TEST_F(WXMPMetaGetPropertyFloatTest_2028, SetAndGetFloatProperty_ShouldReturnTrue_2028) {
    XMPMeta* meta = (XMPMeta*)xmpRef;
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "Rating";

    // Set a float property
    meta->SetProperty_Float(schemaNS, propName, 3.14, 0);

    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
    EXPECT_NEAR(propValue, 3.14, 0.001);
}

// Test: Set a float property with zero value
TEST_F(WXMPMetaGetPropertyFloatTest_2028, GetZeroFloatProperty_ShouldReturnTrue_2028) {
    XMPMeta* meta = (XMPMeta*)xmpRef;
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "ZeroVal";

    meta->SetProperty_Float(schemaNS, propName, 0.0, 0);

    double propValue = -1.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
    EXPECT_DOUBLE_EQ(propValue, 0.0);
}

// Test: Set a negative float property
TEST_F(WXMPMetaGetPropertyFloatTest_2028, GetNegativeFloatProperty_ShouldReturnCorrectValue_2028) {
    XMPMeta* meta = (XMPMeta*)xmpRef;
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "NegVal";

    meta->SetProperty_Float(schemaNS, propName, -42.5, 0);

    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
    EXPECT_NEAR(propValue, -42.5, 0.001);
}

// Test: Set a very large float property
TEST_F(WXMPMetaGetPropertyFloatTest_2028, GetLargeFloatProperty_ShouldReturnCorrectValue_2028) {
    XMPMeta* meta = (XMPMeta*)xmpRef;
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "LargeVal";

    double largeVal = 1.0e+100;
    meta->SetProperty_Float(schemaNS, propName, largeVal, 0);

    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
    EXPECT_NEAR(propValue, largeVal, largeVal * 1e-10);
}

// Test: Set a very small float property
TEST_F(WXMPMetaGetPropertyFloatTest_2028, GetSmallFloatProperty_ShouldReturnCorrectValue_2028) {
    XMPMeta* meta = (XMPMeta*)xmpRef;
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "SmallVal";

    double smallVal = 1.0e-100;
    meta->SetProperty_Float(schemaNS, propName, smallVal, 0);

    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
    EXPECT_NEAR(propValue, smallVal, smallVal * 1e-10);
}

// Test: WXMP_Result is properly initialized to no error on success
TEST_F(WXMPMetaGetPropertyFloatTest_2028, ResultInitializedNoError_2028) {
    double propValue = 0.0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "SomeProp", &propValue, &options, &wResult);

    // No error expected, property just not found
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Both null and empty strings for schema should error
TEST_F(WXMPMetaGetPropertyFloatTest_2028, EmptySchemaAndEmptyProp_BothError_2028) {
    double propValue = 0.0;
    XMP_OptionBits options = 0;
    WXMP_Result wResult1;
    std::memset(&wResult1, 0, sizeof(wResult1));

    // Empty schema
    WXMPMeta_GetProperty_Float_1(xmpRef, "", "prop", &propValue, &options, &wResult1);
    EXPECT_NE(wResult1.errMessage, nullptr);

    WXMP_Result wResult2;
    std::memset(&wResult2, 0, sizeof(wResult2));

    // Valid schema but empty prop
    WXMPMeta_GetProperty_Float_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "", &propValue, &options, &wResult2);
    EXPECT_NE(wResult2.errMessage, nullptr);
}

// Test: Retrieve property with null propValue after setting it (should not crash)
TEST_F(WXMPMetaGetPropertyFloatTest_2028, SetThenGetWithNullPropValue_ShouldReturnFound_2028) {
    XMPMeta* meta = (XMPMeta*)xmpRef;
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "TestProp";

    meta->SetProperty_Float(schemaNS, propName, 99.99, 0);

    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Float_1(xmpRef, schemaNS, propName, nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
}

// Test: Retrieve property with null options after setting it (should not crash)
TEST_F(WXMPMetaGetPropertyFloatTest_2028, SetThenGetWithNullOptions_ShouldReturnFound_2028) {
    XMPMeta* meta = (XMPMeta*)xmpRef;
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "TestProp2";

    meta->SetProperty_Float(schemaNS, propName, 1.23, 0);

    double propValue = 0.0;

    WXMPMeta_GetProperty_Float_1(xmpRef, schemaNS, propName, &propValue, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1u);
    EXPECT_NEAR(propValue, 1.23, 0.001);
}
