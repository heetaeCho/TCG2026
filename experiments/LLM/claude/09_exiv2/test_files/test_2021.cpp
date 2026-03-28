#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declarations for the wrapper function
extern "C" {
    typedef void* XMPMetaRef;
}

// Declaration of the function under test
extern void WXMPMeta_DoesStructFieldExist_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr structName,
    XMP_StringPtr fieldNS,
    XMP_StringPtr fieldName,
    WXMP_Result * wResult);

// We need access to XMPMeta to create valid refs
#include "XMPMeta.hpp"

class WXMPMetaDoesStructFieldExistTest_2021 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = reinterpret_cast<XMPMetaRef>(meta);
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
    WXMP_Result wResult;
};

// Test: Empty schemaNS (null pointer) should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, NullSchemaNS_ThrowsBadSchema_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, nullptr, "structName", "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty schemaNS (empty string) should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, EmptySchemaNS_ThrowsBadSchema_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, "", "structName", "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null structName should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, NullStructName_ThrowsBadXPath_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, "http://ns.example.com/", nullptr, "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty structName should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, EmptyStructName_ThrowsBadXPath_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, "http://ns.example.com/", "", "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null fieldNS should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, NullFieldNS_ThrowsBadSchema_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, "http://ns.example.com/", "structName", nullptr, "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty fieldNS should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, EmptyFieldNS_ThrowsBadSchema_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, "http://ns.example.com/", "structName", "", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null fieldName should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, NullFieldName_ThrowsBadXPath_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, "http://ns.example.com/", "structName", "http://fieldNS/", nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty fieldName should produce an error
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, EmptyFieldName_ThrowsBadXPath_2021) {
    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef, "http://ns.example.com/", "structName", "http://fieldNS/", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Valid parameters but field does not exist returns false (0)
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, FieldDoesNotExist_ReturnsFalse_2021) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");
    XMPMeta::RegisterNamespace("http://ns.example.com/field/", "fld");

    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef,
        "http://ns.example.com/test/",
        "MyStruct",
        "http://ns.example.com/field/",
        "MyField",
        &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Valid parameters and field exists returns true (1)
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, FieldExists_ReturnsTrue_2021) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");
    XMPMeta::RegisterNamespace("http://ns.example.com/field/", "fld");

    // Set a struct field first
    meta->SetStructField("http://ns.example.com/test/", "MyStruct",
                         "http://ns.example.com/field/", "MyField",
                         "SomeValue", 0);

    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef,
        "http://ns.example.com/test/",
        "MyStruct",
        "http://ns.example.com/field/",
        "MyField",
        &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Field exists, then delete, then check it doesn't exist
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, FieldDeletedNoLongerExists_2021) {
    XMPMeta::RegisterNamespace("http://ns.example.com/test2/", "test2");
    XMPMeta::RegisterNamespace("http://ns.example.com/field2/", "fld2");

    meta->SetStructField("http://ns.example.com/test2/", "AStruct",
                         "http://ns.example.com/field2/", "AField",
                         "AValue", 0);

    // Confirm it exists
    WXMP_Result result1;
    WXMPMeta_DoesStructFieldExist_1(xmpRef,
        "http://ns.example.com/test2/", "AStruct",
        "http://ns.example.com/field2/", "AField", &result1);
    EXPECT_EQ(result1.errMessage, nullptr);
    EXPECT_NE(result1.int32Result, static_cast<XMP_Uns32>(0));

    // Delete the struct field
    meta->DeleteStructField("http://ns.example.com/test2/", "AStruct",
                            "http://ns.example.com/field2/", "AField");

    // Confirm it no longer exists
    WXMP_Result result2;
    WXMPMeta_DoesStructFieldExist_1(xmpRef,
        "http://ns.example.com/test2/", "AStruct",
        "http://ns.example.com/field2/", "AField", &result2);
    EXPECT_EQ(result2.errMessage, nullptr);
    EXPECT_EQ(result2.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: WXMP_Result is properly initialized when no error occurs
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, ResultInitialized_NoError_2021) {
    XMPMeta::RegisterNamespace("http://ns.example.com/init/", "init");
    XMPMeta::RegisterNamespace("http://ns.example.com/initf/", "initf");

    WXMP_Result result;
    result.errMessage = nullptr;
    result.int32Result = 999; // Set to garbage to verify it gets overwritten

    WXMPMeta_DoesStructFieldExist_1(xmpRef,
        "http://ns.example.com/init/", "SomeStruct",
        "http://ns.example.com/initf/", "SomeField", &result);

    EXPECT_EQ(result.errMessage, nullptr);
    // Should be 0 since the field doesn't exist
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Different field name doesn't match existing field
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, DifferentFieldName_ReturnsFalse_2021) {
    XMPMeta::RegisterNamespace("http://ns.example.com/diff/", "diff");
    XMPMeta::RegisterNamespace("http://ns.example.com/difff/", "difff");

    meta->SetStructField("http://ns.example.com/diff/", "Struct1",
                         "http://ns.example.com/difff/", "Field1",
                         "Value1", 0);

    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef,
        "http://ns.example.com/diff/", "Struct1",
        "http://ns.example.com/difff/", "Field2", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Different struct name doesn't match existing struct
TEST_F(WXMPMetaDoesStructFieldExistTest_2021, DifferentStructName_ReturnsFalse_2021) {
    XMPMeta::RegisterNamespace("http://ns.example.com/ds/", "ds");
    XMPMeta::RegisterNamespace("http://ns.example.com/dsf/", "dsf");

    meta->SetStructField("http://ns.example.com/ds/", "StructA",
                         "http://ns.example.com/dsf/", "FieldA",
                         "ValueA", 0);

    WXMP_Result result;
    WXMPMeta_DoesStructFieldExist_1(xmpRef,
        "http://ns.example.com/ds/", "StructB",
        "http://ns.example.com/dsf/", "FieldA", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}
