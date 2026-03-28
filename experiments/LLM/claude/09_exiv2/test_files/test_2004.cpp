#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_DeleteAlias_1(XMP_StringPtr aliasNS, XMP_StringPtr aliasProp, WXMP_Result* wResult);

// We need XMPMeta to be initialized
#include "XMPMeta.hpp"

class WXMPMetaDeleteAliasTest_2004 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMPMeta so the SDK is ready
        XMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        XMPMeta::Terminate();
    }

    void SetUp() override {
        memset(&result, 0, sizeof(result));
        result.errMessage = nullptr;
    }

    WXMP_Result result;
};

// Test: Null aliasNS should produce an error (kXMPErr_BadSchema)
TEST_F(WXMPMetaDeleteAliasTest_2004, NullAliasNS_ProducesError_2004) {
    WXMPMeta_DeleteAlias_1(nullptr, "someProp", &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias namespace URI") != nullptr);
    }
}

// Test: Empty string aliasNS should produce an error (kXMPErr_BadSchema)
TEST_F(WXMPMetaDeleteAliasTest_2004, EmptyAliasNS_ProducesError_2004) {
    WXMPMeta_DeleteAlias_1("", "someProp", &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias namespace URI") != nullptr);
    }
}

// Test: Null aliasProp should produce an error (kXMPErr_BadXPath)
TEST_F(WXMPMetaDeleteAliasTest_2004, NullAliasProp_ProducesError_2004) {
    WXMPMeta_DeleteAlias_1("http://ns.example.com/", nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias property name") != nullptr);
    }
}

// Test: Empty string aliasProp should produce an error (kXMPErr_BadXPath)
TEST_F(WXMPMetaDeleteAliasTest_2004, EmptyAliasProp_ProducesError_2004) {
    WXMPMeta_DeleteAlias_1("http://ns.example.com/", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias property name") != nullptr);
    }
}

// Test: Both aliasNS and aliasProp null - should fail on aliasNS check first
TEST_F(WXMPMetaDeleteAliasTest_2004, BothNull_ProducesSchemaError_2004) {
    WXMPMeta_DeleteAlias_1(nullptr, nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias namespace URI") != nullptr);
    }
}

// Test: Both aliasNS and aliasProp empty strings - should fail on aliasNS check first
TEST_F(WXMPMetaDeleteAliasTest_2004, BothEmpty_ProducesSchemaError_2004) {
    WXMPMeta_DeleteAlias_1("", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias namespace URI") != nullptr);
    }
}

// Test: Valid namespace and property that is not an alias - should not produce validation error
// (DeleteAlias on non-existent alias may or may not produce an error from XMPMeta::DeleteAlias,
// but the parameter validation should pass)
TEST_F(WXMPMetaDeleteAliasTest_2004, ValidParamsNonExistentAlias_NoParamError_2004) {
    WXMPMeta_DeleteAlias_1("http://ns.nonexistent.com/", "nonExistentProp", &result);
    // The function may or may not set an error for a non-existent alias,
    // but it should NOT be the parameter validation errors
    if (result.errMessage != nullptr) {
        EXPECT_EQ(std::strstr(result.errMessage, "Empty alias namespace URI"), nullptr);
        EXPECT_EQ(std::strstr(result.errMessage, "Empty alias property name"), nullptr);
    }
}

// Test: WXMP_Result is properly initialized with no error before call
TEST_F(WXMPMetaDeleteAliasTest_2004, ResultInitialization_2004) {
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, 0u);
    EXPECT_EQ(result.int64Result, 0u);
}

// Test: Register an alias then delete it - should succeed with no error
TEST_F(WXMPMetaDeleteAliasTest_2004, RegisterThenDeleteAlias_Succeeds_2004) {
    // First register the namespaces
    XMPMeta::RegisterNamespace("http://ns.test.deletealiasA/", "testDelA:");
    XMPMeta::RegisterNamespace("http://ns.test.deletealiasB/", "testDelB:");

    // Register an alias
    XMPMeta::RegisterAlias("http://ns.test.deletealiasA/", "testDelA:aliased",
                           "http://ns.test.deletealiasB/", "testDelB:actual", 0);

    // Now delete the alias via the wrapper
    WXMPMeta_DeleteAlias_1("http://ns.test.deletealiasA/", "testDelA:aliased", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: aliasNS is valid but aliasProp is null - should get BadXPath error
TEST_F(WXMPMetaDeleteAliasTest_2004, ValidNS_NullProp_ProducesBadXPath_2004) {
    WXMPMeta_DeleteAlias_1("http://valid.ns.com/", nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: aliasNS is valid but aliasProp is empty - should get BadXPath error
TEST_F(WXMPMetaDeleteAliasTest_2004, ValidNS_EmptyProp_ProducesBadXPath_2004) {
    WXMPMeta_DeleteAlias_1("http://valid.ns.com/", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}
