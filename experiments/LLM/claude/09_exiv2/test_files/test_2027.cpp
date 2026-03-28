#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetProperty_Int64_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_Int64 * propValue,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

class WXMPMetaGetPropertyInt64Test_2027 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;

    XMPMetaRef GetRef() {
        return (XMPMetaRef)meta;
    }
};

// Test: Null schema namespace URI causes error
TEST_F(WXMPMetaGetPropertyInt64Test_2027, NullSchemaNS_ThrowsBadSchema_2027) {
    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), nullptr, "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace URI string causes error
TEST_F(WXMPMetaGetPropertyInt64Test_2027, EmptySchemaNS_ThrowsBadSchema_2027) {
    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), "", "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null property name causes error
TEST_F(WXMPMetaGetPropertyInt64Test_2027, NullPropName_ThrowsBadXPath_2027) {
    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), "http://ns.adobe.com/xap/1.0/", nullptr, &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name string causes error
TEST_F(WXMPMetaGetPropertyInt64Test_2027, EmptyPropName_ThrowsBadXPath_2027) {
    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Property not found returns false (int32Result == 0)
TEST_F(WXMPMetaGetPropertyInt64Test_2027, PropertyNotFound_ReturnsFalse_2027) {
    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "NonExistentProp", &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: Property found returns true and correct value
TEST_F(WXMPMetaGetPropertyInt64Test_2027, PropertyFound_ReturnsTrueAndValue_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "TestInt64Prop";
    XMP_Int64 setValue = 1234567890123LL;

    meta->SetProperty_Int64(schemaNS, propName, setValue, 0);

    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);  // found == true
    EXPECT_EQ(propValue, setValue);
}

// Test: Null propValue pointer does not crash (uses voidInt64)
TEST_F(WXMPMetaGetPropertyInt64Test_2027, NullPropValuePointer_DoesNotCrash_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "TestInt64Prop";
    XMP_Int64 setValue = 42;

    meta->SetProperty_Int64(schemaNS, propName, setValue, 0);

    WXMP_Result wResult;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: Null options pointer does not crash (uses voidOptionBits)
TEST_F(WXMPMetaGetPropertyInt64Test_2027, NullOptionsPointer_DoesNotCrash_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "TestInt64Prop";
    XMP_Int64 setValue = 99;

    meta->SetProperty_Int64(schemaNS, propName, setValue, 0);

    WXMP_Result wResult;
    XMP_Int64 propValue = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, &propValue, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
    EXPECT_EQ(propValue, setValue);
}

// Test: Both null propValue and options do not crash
TEST_F(WXMPMetaGetPropertyInt64Test_2027, BothNullPropValueAndOptions_DoesNotCrash_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "TestInt64Prop";

    meta->SetProperty_Int64(schemaNS, propName, 555, 0);

    WXMP_Result wResult;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
}

// Test: Negative Int64 value
TEST_F(WXMPMetaGetPropertyInt64Test_2027, NegativeInt64Value_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "NegativeInt64Prop";
    XMP_Int64 setValue = -9876543210LL;

    meta->SetProperty_Int64(schemaNS, propName, setValue, 0);

    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
    EXPECT_EQ(propValue, setValue);
}

// Test: Zero Int64 value
TEST_F(WXMPMetaGetPropertyInt64Test_2027, ZeroInt64Value_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "ZeroInt64Prop";
    XMP_Int64 setValue = 0;

    meta->SetProperty_Int64(schemaNS, propName, setValue, 0);

    WXMP_Result wResult;
    XMP_Int64 propValue = -1;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
    EXPECT_EQ(propValue, 0);
}

// Test: Large Int64 value (max boundary)
TEST_F(WXMPMetaGetPropertyInt64Test_2027, MaxInt64Value_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "MaxInt64Prop";
    XMP_Int64 setValue = 9223372036854775807LL; // INT64_MAX

    meta->SetProperty_Int64(schemaNS, propName, setValue, 0);

    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0);
    EXPECT_EQ(propValue, setValue);
}

// Test: Property not found with non-existent namespace returns false
TEST_F(WXMPMetaGetPropertyInt64Test_2027, NonExistentNamespace_ReturnsFalse_2027) {
    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), "http://nonexistent.namespace/", "SomeProp", &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0);
}

// Test: WXMP_Result is properly initialized on success
TEST_F(WXMPMetaGetPropertyInt64Test_2027, ResultInitializedOnSuccess_2027) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "TestProp";

    meta->SetProperty_Int64(schemaNS, propName, 100, 0);

    WXMP_Result wResult;
    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 1);  // true - property found
}

// Test: Different schemas can hold different properties
TEST_F(WXMPMetaGetPropertyInt64Test_2027, DifferentSchemas_IndependentProperties_2027) {
    const char* schemaNS1 = "http://ns.adobe.com/xap/1.0/";
    const char* schemaNS2 = "http://purl.org/dc/elements/1.1/";
    const char* propName = "SharedPropName";

    meta->SetProperty_Int64(schemaNS1, propName, 111, 0);
    meta->SetProperty_Int64(schemaNS2, propName, 222, 0);

    WXMP_Result wResult1, wResult2;
    XMP_Int64 propValue1 = 0, propValue2 = 0;
    XMP_OptionBits options1 = 0, options2 = 0;

    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS1, propName, &propValue1, &options1, &wResult1);
    WXMPMeta_GetProperty_Int64_1(GetRef(), schemaNS2, propName, &propValue2, &options2, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_NE(wResult1.int32Result, 0);
    EXPECT_NE(wResult2.int32Result, 0);
    EXPECT_EQ(propValue1, 111);
    EXPECT_EQ(propValue2, 222);
}
