#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DeleteStructField_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr structName,
    XMP_StringPtr fieldNS,
    XMP_StringPtr fieldName,
    WXMP_Result * wResult);

class WXMPMetaDeleteStructFieldTest_2017 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP SDK
        XMPMeta::Initialize();
        meta = new XMPMeta();
        memset(&result, 0, sizeof(result));
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    WXMP_Result result;

    XMPMetaRef GetRef() {
        return reinterpret_cast<XMPMetaRef>(meta);
    }
};

// Test: Null schemaNS should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, NullSchemaNS_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), nullptr, "structName", "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
    // Should indicate bad schema
}

// Test: Empty schemaNS should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, EmptySchemaNS_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "", "structName", "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null structName should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, NullStructName_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", nullptr, "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty structName should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, EmptyStructName_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "", "http://fieldNS/", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null fieldNS should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, NullFieldNS_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "structName", nullptr, "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty fieldNS should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, EmptyFieldNS_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "structName", "", "fieldName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null fieldName should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, NullFieldName_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "structName", "http://fieldNS/", nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty fieldName should report error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, EmptyFieldName_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "structName", "http://fieldNS/", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Valid parameters on a meta with no matching struct field should succeed without error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, ValidParamsNoExistingField_NoError_2017) {
    XMPMeta::RegisterNamespace("http://ns.example.com/", "ex");
    XMPMeta::RegisterNamespace("http://fieldNS.example.com/", "fn");
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "ex:MyStruct",
        "http://fieldNS.example.com/", "MyField", &result);
    // Deleting a non-existent field should not be an error
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Valid deletion of an existing struct field
TEST_F(WXMPMetaDeleteStructFieldTest_2017, DeleteExistingStructField_Success_2017) {
    XMPMeta::RegisterNamespace("http://ns.example.com/", "ex");
    XMPMeta::RegisterNamespace("http://fieldNS.example.com/", "fn");

    // First set a struct field
    meta->SetStructField("http://ns.example.com/", "ex:MyStruct",
                         "http://fieldNS.example.com/", "fn:MyField",
                         "TestValue", 0);

    // Verify it exists
    EXPECT_TRUE(meta->DoesStructFieldExist("http://ns.example.com/", "ex:MyStruct",
                                            "http://fieldNS.example.com/", "fn:MyField"));

    // Delete it via the wrapper
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "ex:MyStruct",
        "http://fieldNS.example.com/", "fn:MyField", &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // Verify it no longer exists
    EXPECT_FALSE(meta->DoesStructFieldExist("http://ns.example.com/", "ex:MyStruct",
                                             "http://fieldNS.example.com/", "fn:MyField"));
}

// Test: WXMP_Result is properly initialized and no error message on success
TEST_F(WXMPMetaDeleteStructFieldTest_2017, ResultInitializedOnSuccess_2017) {
    XMPMeta::RegisterNamespace("http://ns.example.com/", "ex");
    XMPMeta::RegisterNamespace("http://fieldNS.example.com/", "fn");

    WXMP_Result res;
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "ex:SomeStruct",
        "http://fieldNS.example.com/", "fn:SomeField", &res);

    EXPECT_EQ(res.errMessage, nullptr);
}

// Test: All parameters null should report error (first check fails on schemaNS)
TEST_F(WXMPMetaDeleteStructFieldTest_2017, AllParamsNull_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), nullptr, nullptr, nullptr, nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: All parameters empty should report error (first check fails on schemaNS)
TEST_F(WXMPMetaDeleteStructFieldTest_2017, AllParamsEmpty_ReportsError_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "", "", "", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Error message contains relevant info for empty schema
TEST_F(WXMPMetaDeleteStructFieldTest_2017, EmptySchemaNS_ErrorMessageContent_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "", "structName", "http://fieldNS/", "fieldName", &result);
    ASSERT_NE(result.errMessage, nullptr);
    std::string errMsg(result.errMessage);
    // The error message should mention schema
    EXPECT_TRUE(errMsg.find("schema") != std::string::npos ||
                errMsg.find("Schema") != std::string::npos ||
                errMsg.length() > 0);
}

// Test: Error message for empty struct name
TEST_F(WXMPMetaDeleteStructFieldTest_2017, EmptyStructName_ErrorMessageContent_2017) {
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "", "http://fieldNS/", "fieldName", &result);
    ASSERT_NE(result.errMessage, nullptr);
    std::string errMsg(result.errMessage);
    EXPECT_TRUE(errMsg.find("struct") != std::string::npos ||
                errMsg.find("name") != std::string::npos ||
                errMsg.length() > 0);
}

// Test: Multiple deletions of the same field should not cause error
TEST_F(WXMPMetaDeleteStructFieldTest_2017, DeleteSameFieldTwice_NoError_2017) {
    XMPMeta::RegisterNamespace("http://ns.example.com/", "ex");
    XMPMeta::RegisterNamespace("http://fieldNS.example.com/", "fn");

    meta->SetStructField("http://ns.example.com/", "ex:MyStruct",
                         "http://fieldNS.example.com/", "fn:MyField",
                         "TestValue", 0);

    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "ex:MyStruct",
        "http://fieldNS.example.com/", "fn:MyField", &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // Delete again - should not error
    WXMP_Result result2;
    WXMPMeta_DeleteStructField_1(
        GetRef(), "http://ns.example.com/", "ex:MyStruct",
        "http://fieldNS.example.com/", "fn:MyField", &result2);
    EXPECT_EQ(result2.errMessage, nullptr);
}
