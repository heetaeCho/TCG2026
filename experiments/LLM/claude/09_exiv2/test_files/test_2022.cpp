#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DoesQualifierExist_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr qualNS,
    XMP_StringPtr qualName,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaDoesQualifierExistTest_2022 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        std::memset(&result, 0, sizeof(result));
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    WXMP_Result result;

    static constexpr const char* kTestNS = "http://ns.test.com/test/";
    static constexpr const char* kTestProp = "TestProperty";
    static constexpr const char* kQualNS = "http://ns.test.com/qual/";
    static constexpr const char* kQualName = "TestQualifier";
};

// Test: Empty schemaNS (null pointer) should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullSchemaNS_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), nullptr, kTestProp, kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty schemaNS (empty string) should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptySchemaNS_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), "", kTestProp, kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null propName should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullPropName_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, nullptr, kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty propName should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptyPropName_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, "", kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null qualNS should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullQualNS_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, nullptr, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty qualNS should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptyQualNS_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, "", kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null qualName should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullQualName_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, kQualNS, nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty qualName should produce an error
TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptyQualName_ReturnsError_2022) {
    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, kQualNS, "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Qualifier does not exist on empty metadata returns false
TEST_F(WXMPMetaDoesQualifierExistTest_2022, QualifierNotExist_ReturnsFalse_2022) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");
    meta->SetProperty(kTestNS, kTestProp, "SomeValue", 0);

    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(false));
}

// Test: Qualifier exists after being set returns true
TEST_F(WXMPMetaDoesQualifierExistTest_2022, QualifierExists_ReturnsTrue_2022) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");
    meta->SetProperty(kTestNS, kTestProp, "SomeValue", 0);
    meta->SetQualifier(kTestNS, kTestProp, kQualNS, kQualName, "QualValue", 0);

    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(true));
}

// Test: Property does not exist - qualifier check returns false
TEST_F(WXMPMetaDoesQualifierExistTest_2022, PropertyNotExist_ReturnsFalse_2022) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");

    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, "NonExistentProp", kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(false));
}

// Test: Qualifier deleted - returns false after deletion
TEST_F(WXMPMetaDoesQualifierExistTest_2022, QualifierDeletedReturnsFalse_2022) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");
    meta->SetProperty(kTestNS, kTestProp, "SomeValue", 0);
    meta->SetQualifier(kTestNS, kTestProp, kQualNS, kQualName, "QualValue", 0);
    meta->DeleteQualifier(kTestNS, kTestProp, kQualNS, kQualName);

    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(false));
}

// Test: Different qualifier name - returns false
TEST_F(WXMPMetaDoesQualifierExistTest_2022, DifferentQualName_ReturnsFalse_2022) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");
    meta->SetProperty(kTestNS, kTestProp, "SomeValue", 0);
    meta->SetQualifier(kTestNS, kTestProp, kQualNS, kQualName, "QualValue", 0);

    WXMPMeta_DoesQualifierExist_1(
        MetaToRef(meta), kTestNS, kTestProp, kQualNS, "OtherQualifier", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(false));
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaDoesQualifierExistTest_2022, ResultInitialized_2022) {
    WXMP_Result freshResult;
    EXPECT_EQ(freshResult.errMessage, nullptr);
    EXPECT_EQ(freshResult.int32Result, 0u);
}
