#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_DeleteQualifier_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr qualNS,
    XMP_StringPtr qualName,
    WXMP_Result * wResult);

// We need access to XMPMeta to create valid refs
#include "XMPMeta.hpp"

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaDeleteQualifierTest_2018 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = MetaToRef(meta);
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
    WXMP_Result wResult;

    static constexpr const char* kTestNS = "http://ns.test.com/test/";
    static constexpr const char* kTestProp = "TestProp";
    static constexpr const char* kQualNS = "http://ns.test.com/qual/";
    static constexpr const char* kQualName = "TestQual";
};

// Test: Empty schemaNS (null pointer) should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, NullSchemaNS_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, nullptr, kTestProp, kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
    EXPECT_STRNE(result.errMessage, "");
}

// Test: Empty schemaNS (empty string) should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, EmptySchemaNS_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, "", kTestProp, kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null propName should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, NullPropName_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, nullptr, kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty propName (empty string) should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, EmptyPropName_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, "", kQualNS, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null qualNS should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, NullQualNS_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, nullptr, kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty qualNS (empty string) should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, EmptyQualNS_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, "", kQualName, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null qualName should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, NullQualName_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, kQualNS, nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty qualName (empty string) should report error
TEST_F(WXMPMetaDeleteQualifierTest_2018, EmptyQualName_ReportsError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, kQualNS, "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Valid parameters on non-existent property should not report error
// (Deleting a qualifier that doesn't exist should be a no-op, not an error)
TEST_F(WXMPMetaDeleteQualifierTest_2018, NonExistentProperty_NoError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, "NonExistentProp", kQualNS, kQualName, &result);
    // The function may or may not report an error for non-existent properties.
    // This test documents the behavior.
    // Typically, delete on non-existent is a no-op with no error.
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Normal operation - set a property with qualifier, then delete the qualifier
TEST_F(WXMPMetaDeleteQualifierTest_2018, DeleteExistingQualifier_Succeeds_2018) {
    // Register namespaces first
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");

    // Set a property
    meta->SetProperty(kTestNS, kTestProp, "TestValue", 0);

    // Set a qualifier on that property
    meta->SetQualifier(kTestNS, kTestProp, kQualNS, kQualName, "QualValue", 0);

    // Verify qualifier exists
    EXPECT_TRUE(meta->DoesQualifierExist(kTestNS, kTestProp, kQualNS, kQualName));

    // Delete the qualifier via the wrapper
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // Verify qualifier no longer exists
    EXPECT_FALSE(meta->DoesQualifierExist(kTestNS, kTestProp, kQualNS, kQualName));
}

// Test: Property still exists after deleting its qualifier
TEST_F(WXMPMetaDeleteQualifierTest_2018, PropertyExistsAfterQualifierDeletion_2018) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");

    meta->SetProperty(kTestNS, kTestProp, "TestValue", 0);
    meta->SetQualifier(kTestNS, kTestProp, kQualNS, kQualName, "QualValue", 0);

    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // Property itself should still exist
    EXPECT_TRUE(meta->DoesPropertyExist(kTestNS, kTestProp));
}

// Test: Error message contains meaningful text for empty schema
TEST_F(WXMPMetaDeleteQualifierTest_2018, EmptySchemaNS_ErrorMessageContent_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, "", kTestProp, kQualNS, kQualName, &result);
    ASSERT_NE(result.errMessage, nullptr);
    // The error message should mention schema
    EXPECT_TRUE(std::strstr(result.errMessage, "schema") != nullptr ||
                std::strstr(result.errMessage, "Empty") != nullptr);
}

// Test: Error message for empty propName contains meaningful text
TEST_F(WXMPMetaDeleteQualifierTest_2018, EmptyPropName_ErrorMessageContent_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, "", kQualNS, kQualName, &result);
    ASSERT_NE(result.errMessage, nullptr);
    EXPECT_TRUE(std::strstr(result.errMessage, "property") != nullptr ||
                std::strstr(result.errMessage, "Empty") != nullptr);
}

// Test: Multiple qualifiers - deleting one doesn't affect another
TEST_F(WXMPMetaDeleteQualifierTest_2018, DeleteOneQualifier_OtherRemains_2018) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");

    meta->SetProperty(kTestNS, kTestProp, "TestValue", 0);
    meta->SetQualifier(kTestNS, kTestProp, kQualNS, kQualName, "QualValue1", 0);
    meta->SetQualifier(kTestNS, kTestProp, kQualNS, "AnotherQual", "QualValue2", 0);

    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    EXPECT_FALSE(meta->DoesQualifierExist(kTestNS, kTestProp, kQualNS, kQualName));
    EXPECT_TRUE(meta->DoesQualifierExist(kTestNS, kTestProp, kQualNS, "AnotherQual"));
}

// Test: WXMP_Result is properly initialized when no error occurs
TEST_F(WXMPMetaDeleteQualifierTest_2018, ResultInitializedCorrectly_2018) {
    XMPMeta::RegisterNamespace(kTestNS, "test:");
    XMPMeta::RegisterNamespace(kQualNS, "qual:");

    meta->SetProperty(kTestNS, kTestProp, "TestValue", 0);

    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, kTestNS, kTestProp, kQualNS, kQualName, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: All four parameters empty - first check (schemaNS) should trigger
TEST_F(WXMPMetaDeleteQualifierTest_2018, AllParamsEmpty_FirstCheckTriggersError_2018) {
    WXMP_Result result;
    WXMPMeta_DeleteQualifier_1(xmpRef, "", "", "", "", &result);
    ASSERT_NE(result.errMessage, nullptr);
    // Should trigger the schemaNS check first (mentions schema)
    EXPECT_TRUE(std::strstr(result.errMessage, "schema") != nullptr ||
                std::strstr(result.errMessage, "Schema") != nullptr ||
                std::strstr(result.errMessage, "Empty") != nullptr);
}
