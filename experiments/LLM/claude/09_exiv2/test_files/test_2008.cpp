#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetStructField_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr structName,
    XMP_StringPtr fieldNS,
    XMP_StringPtr fieldName,
    XMP_StringPtr * fieldValue,
    XMP_StringLen * valueSize,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

class WXMPMetaGetStructFieldTest_2008 : public ::testing::Test {
protected:
    XMPMeta* meta;
    WXMP_Result wResult;

    void SetUp() override {
        // Initialize XMP toolkit
        XMPMeta::Initialize();
        meta = new XMPMeta();
        memset(&wResult, 0, sizeof(wResult));
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMetaRef GetRef() {
        return (XMPMetaRef)meta;
    }
};

// Test: Empty schema namespace (null pointer) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptySchemaNS_Null_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), nullptr, "structName", "http://ns.field/", "fieldName",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace (empty string) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptySchemaNS_EmptyString_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), "", "structName", "http://ns.field/", "fieldName",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty struct name (null pointer) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptyStructName_Null_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.schema/", nullptr, "http://ns.field/", "fieldName",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty struct name (empty string) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptyStructName_EmptyString_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.schema/", "", "http://ns.field/", "fieldName",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty field namespace (null pointer) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptyFieldNS_Null_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.schema/", "structName", nullptr, "fieldName",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty field namespace (empty string) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptyFieldNS_EmptyString_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.schema/", "structName", "", "fieldName",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty field name (null pointer) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptyFieldName_Null_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.schema/", "structName", "http://ns.field/", nullptr,
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty field name (empty string) should produce an error
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptyFieldName_EmptyString_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.schema/", "structName", "http://ns.field/", "",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Getting a non-existent struct field should return false (int32Result == 0)
TEST_F(WXMPMetaGetStructFieldTest_2008, NonExistentField_ReturnsFalse_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    // Register namespace first
    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        &fieldValue, &valueSize, &options, &wResult);

    // No error should be set for a valid but non-existent field
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Setting and getting a struct field should return true and the correct value
TEST_F(WXMPMetaGetStructFieldTest_2008, SetAndGetStructField_ReturnsTrue_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    // Register namespaces
    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    // Set a struct field
    meta->SetStructField(
        "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        "hello_world", 0);

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    ASSERT_NE(fieldValue, nullptr);
    EXPECT_STREQ(fieldValue, "hello_world");
    EXPECT_EQ(valueSize, strlen("hello_world"));
}

// Test: Passing null for fieldValue pointer should not crash (uses voidStringPtr)
TEST_F(WXMPMetaGetStructFieldTest_2008, NullFieldValuePtr_2008) {
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        nullptr, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Passing null for valueSize pointer should not crash (uses voidStringLen)
TEST_F(WXMPMetaGetStructFieldTest_2008, NullValueSizePtr_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        &fieldValue, nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Passing null for options pointer should not crash (uses voidOptionBits)
TEST_F(WXMPMetaGetStructFieldTest_2008, NullOptionsPtr_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;

    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        &fieldValue, &valueSize, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: All output pointers null should not crash for non-existent field
TEST_F(WXMPMetaGetStructFieldTest_2008, AllOutputPtrsNull_2008) {
    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        nullptr, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Set struct field with empty value and retrieve it
TEST_F(WXMPMetaGetStructFieldTest_2008, EmptyFieldValue_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    meta->SetStructField(
        "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        "", 0);

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    ASSERT_NE(fieldValue, nullptr);
    EXPECT_STREQ(fieldValue, "");
    EXPECT_EQ(valueSize, 0u);
}

// Test: Multiple fields in the same struct
TEST_F(WXMPMetaGetStructFieldTest_2008, MultipleFieldsSameStruct_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    meta->SetStructField(
        "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:field1",
        "value1", 0);

    meta->SetStructField(
        "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:field2",
        "value2", 0);

    // Get field1
    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:field1",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    EXPECT_STREQ(fieldValue, "value1");

    // Reset result
    memset(&wResult, 0, sizeof(wResult));
    fieldValue = nullptr;
    valueSize = 0;
    options = 0;

    // Get field2
    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:field2",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    EXPECT_STREQ(fieldValue, "value2");
}

// Test: Delete struct field and then try to get it
TEST_F(WXMPMetaGetStructFieldTest_2008, DeletedFieldReturnsNotFound_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    meta->SetStructField(
        "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        "to_be_deleted", 0);

    meta->DeleteStructField(
        "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField");

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:myStruct",
        "http://ns.test.field/", "tfield:myField",
        &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: WXMP_Result is properly initialized to zero before call with valid but non-existent data
TEST_F(WXMPMetaGetStructFieldTest_2008, WResultInitialization_2008) {
    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    XMPMeta::RegisterNamespace("http://ns.test.schema/", "tschema:");
    XMPMeta::RegisterNamespace("http://ns.test.field/", "tfield:");

    WXMP_Result freshResult;
    // WXMP_Result constructor should initialize errMessage to 0
    EXPECT_EQ(freshResult.errMessage, nullptr);

    WXMPMeta_GetStructField_1(
        GetRef(), "http://ns.test.schema/", "tschema:nonExistent",
        "http://ns.test.field/", "tfield:nonExistent",
        &fieldValue, &valueSize, &options, &freshResult);

    EXPECT_EQ(freshResult.errMessage, nullptr);
    EXPECT_EQ(freshResult.int32Result, 0u);
}
