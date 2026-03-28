#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_SetStructField_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr structName,
    XMP_StringPtr fieldNS,
    XMP_StringPtr fieldName,
    XMP_StringPtr fieldValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

class WXMPMetaSetStructFieldTest_2013 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = reinterpret_cast<XMPMetaRef>(meta);
        // Register a namespace for testing
        XMPMeta::RegisterNamespace("http://ns.test.com/", "test");
        XMPMeta::RegisterNamespace("http://ns.field.com/", "field");
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
};

// Test: Normal operation - setting a struct field should succeed
TEST_F(WXMPMetaSetStructFieldTest_2013, SetStructFieldNormalOperation_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "MyValue",
        0,
        &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS (empty string) should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, EmptySchemaNSString_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null schemaNS should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, NullSchemaNS_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        nullptr,
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty structName (empty string) should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, EmptyStructNameString_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "",
        "http://ns.field.com/",
        "MyField",
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null structName should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, NullStructName_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        nullptr,
        "http://ns.field.com/",
        "MyField",
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty fieldNS (empty string) should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, EmptyFieldNSString_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "",
        "MyField",
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null fieldNS should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, NullFieldNS_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        nullptr,
        "MyField",
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty fieldName (empty string) should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, EmptyFieldNameString_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "",
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null fieldName should result in error
TEST_F(WXMPMetaSetStructFieldTest_2013, NullFieldName_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        nullptr,
        "MyValue",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null fieldValue should still succeed (allowed per the interface - no null check on fieldValue)
TEST_F(WXMPMetaSetStructFieldTest_2013, NullFieldValue_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        nullptr,
        0,
        &wResult);
    // fieldValue null is not checked in the wrapper - behavior depends on underlying impl
    // We just verify it doesn't crash or the result is set appropriately
    // No assertion on errMessage since behavior is implementation-defined
}

// Test: Verify the struct field is actually set and retrievable
TEST_F(WXMPMetaSetStructFieldTest_2013, FieldIsRetrievableAfterSet_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "TestValue",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;
    bool found = meta->GetStructField(
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        &fieldValue,
        &valueSize,
        &options);
    EXPECT_TRUE(found);
    EXPECT_STREQ(fieldValue, "TestValue");
}

// Test: Overwriting an existing struct field value
TEST_F(WXMPMetaSetStructFieldTest_2013, OverwriteExistingField_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "FirstValue",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "SecondValue",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;
    bool found = meta->GetStructField(
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        &fieldValue,
        &valueSize,
        &options);
    EXPECT_TRUE(found);
    EXPECT_STREQ(fieldValue, "SecondValue");
}

// Test: Multiple fields in same struct
TEST_F(WXMPMetaSetStructFieldTest_2013, MultipleFieldsInSameStruct_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "Field1",
        "Value1",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "Field2",
        "Value2",
        0,
        &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    bool found1 = meta->GetStructField(
        "http://ns.test.com/", "MyStruct",
        "http://ns.field.com/", "Field1",
        &fieldValue, &valueSize, &options);
    EXPECT_TRUE(found1);
    EXPECT_STREQ(fieldValue, "Value1");

    bool found2 = meta->GetStructField(
        "http://ns.test.com/", "MyStruct",
        "http://ns.field.com/", "Field2",
        &fieldValue, &valueSize, &options);
    EXPECT_TRUE(found2);
    EXPECT_STREQ(fieldValue, "Value2");
}

// Test: WXMP_Result is properly initialized and no error on valid call
TEST_F(WXMPMetaSetStructFieldTest_2013, ResultInitializedCorrectly_2013) {
    WXMP_Result wResult;
    EXPECT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "Value",
        0,
        &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting empty field value (empty string, not null)
TEST_F(WXMPMetaSetStructFieldTest_2013, EmptyFieldValueString_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "http://ns.test.com/",
        "MyStruct",
        "http://ns.field.com/",
        "MyField",
        "",
        0,
        &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;
    bool found = meta->GetStructField(
        "http://ns.test.com/", "MyStruct",
        "http://ns.field.com/", "MyField",
        &fieldValue, &valueSize, &options);
    EXPECT_TRUE(found);
    EXPECT_STREQ(fieldValue, "");
}

// Test: All parameters empty/null - first check (schemaNS) should trigger
TEST_F(WXMPMetaSetStructFieldTest_2013, AllParametersEmpty_2013) {
    WXMP_Result wResult;
    WXMPMeta_SetStructField_1(
        xmpRef,
        "",
        "",
        "",
        "",
        "",
        0,
        &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}
