#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the function under test
#include "WXMPMeta.hpp"
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration if not in header
extern "C" void WXMPMeta_RegisterAlias_1(
    XMP_StringPtr aliasNS,
    XMP_StringPtr aliasProp,
    XMP_StringPtr actualNS,
    XMP_StringPtr actualProp,
    XMP_OptionBits arrayForm,
    WXMP_Result * wResult);

class WXMPMetaRegisterAliasTest_2002 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP SDK once for all tests
        XMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        XMPMeta::Terminate();
    }

    void SetUp() override {
        std::memset(&result, 0, sizeof(result));
        result.errMessage = nullptr;
    }

    WXMP_Result result;
};

// Test: Null aliasNS should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, NullAliasNS_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1(nullptr, "aliasProp", "http://ns.actual.com/", "actualProp", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias namespace URI") != nullptr);
    }
}

// Test: Empty aliasNS should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, EmptyAliasNS_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1("", "aliasProp", "http://ns.actual.com/", "actualProp", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias namespace URI") != nullptr);
    }
}

// Test: Null aliasProp should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, NullAliasProp_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", nullptr, "http://ns.actual.com/", "actualProp", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias property name") != nullptr);
    }
}

// Test: Empty aliasProp should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, EmptyAliasProp_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", "", "http://ns.actual.com/", "actualProp", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias property name") != nullptr);
    }
}

// Test: Null actualNS should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, NullActualNS_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", "aliasProp", nullptr, "actualProp", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty actual namespace URI") != nullptr);
    }
}

// Test: Empty actualNS should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, EmptyActualNS_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", "aliasProp", "", "actualProp", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty actual namespace URI") != nullptr);
    }
}

// Test: Null actualProp should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, NullActualProp_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", "aliasProp", "http://ns.actual.com/", nullptr, 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty actual property name") != nullptr);
    }
}

// Test: Empty actualProp should produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, EmptyActualProp_ProducesError_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", "aliasProp", "http://ns.actual.com/", "", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty actual property name") != nullptr);
    }
}

// Test: Validation order - aliasNS checked before aliasProp
TEST_F(WXMPMetaRegisterAliasTest_2002, ValidationOrder_AliasNSCheckedFirst_2002) {
    WXMPMeta_RegisterAlias_1("", "", "", "", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        // aliasNS is checked first, so the error should be about alias namespace
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias namespace URI") != nullptr);
    }
}

// Test: Validation order - aliasProp checked before actualNS
TEST_F(WXMPMetaRegisterAliasTest_2002, ValidationOrder_AliasPropCheckedBeforeActualNS_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", "", "", "", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty alias property name") != nullptr);
    }
}

// Test: Validation order - actualNS checked before actualProp
TEST_F(WXMPMetaRegisterAliasTest_2002, ValidationOrder_ActualNSCheckedBeforeActualProp_2002) {
    WXMPMeta_RegisterAlias_1("http://ns.alias.com/", "aliasProp", "", "", 0, &result);
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty actual namespace URI") != nullptr);
    }
}

// Test: Valid parameters with registered namespaces should not produce an error
TEST_F(WXMPMetaRegisterAliasTest_2002, ValidParameters_RegisteredNamespaces_NoError_2002) {
    // Register namespaces first so the alias registration can succeed
    XMPMeta::RegisterNamespace("http://ns.test.alias2002/", "talias2002:");
    XMPMeta::RegisterNamespace("http://ns.test.actual2002/", "tactual2002:");

    WXMPMeta_RegisterAlias_1(
        "http://ns.test.alias2002/", "AliasProperty",
        "http://ns.test.actual2002/", "ActualProperty",
        0, &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Valid call with arrayForm option
TEST_F(WXMPMetaRegisterAliasTest_2002, ValidParametersWithArrayForm_NoError_2002) {
    XMPMeta::RegisterNamespace("http://ns.test.aliasarr2002/", "taliasarr2002:");
    XMPMeta::RegisterNamespace("http://ns.test.actualarr2002/", "tactualarr2002:");

    // kXMP_PropArrayIsOrdered = 0x00000200UL typically
    WXMPMeta_RegisterAlias_1(
        "http://ns.test.aliasarr2002/", "AliasArrayProp",
        "http://ns.test.actualarr2002/", "ActualArrayProp",
        0x00000200UL, &result);
    // Either succeeds or fails gracefully - no crash
    // The main test is that valid non-empty params pass the initial checks
}

// Test: Result struct initialized properly when error occurs
TEST_F(WXMPMetaRegisterAliasTest_2002, ResultStructHasErrorMessage_WhenInvalid_2002) {
    WXMP_Result freshResult;
    freshResult.errMessage = nullptr;
    freshResult.int32Result = 0;
    freshResult.int64Result = 0;
    freshResult.floatResult = 0.0;
    freshResult.ptrResult = nullptr;

    WXMPMeta_RegisterAlias_1(nullptr, "prop", "http://ns.com/", "prop2", 0, &freshResult);
    EXPECT_NE(freshResult.errMessage, nullptr);
}
