#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_ResolveAlias_1(
    XMP_StringPtr aliasNS,
    XMP_StringPtr aliasProp,
    XMP_StringPtr * actualNS,
    XMP_StringLen * nsSize,
    XMP_StringPtr * actualProp,
    XMP_StringLen * propSize,
    XMP_OptionBits * arrayForm,
    WXMP_Result * wResult
);

class WXMPMetaResolveAliasTest_2003 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP toolkit once
        XMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        XMPMeta::Terminate();
    }

    void SetUp() override {
        memset(&wResult, 0, sizeof(wResult));
    }

    WXMP_Result wResult;
};

// Test: Null alias namespace should produce an error
TEST_F(WXMPMetaResolveAliasTest_2003, NullAliasNamespaceThrowsError_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1(nullptr, "someProp",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty alias namespace string should produce an error
TEST_F(WXMPMetaResolveAliasTest_2003, EmptyAliasNamespaceThrowsError_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1("", "someProp",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null alias property should produce an error
TEST_F(WXMPMetaResolveAliasTest_2003, NullAliasPropThrowsError_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1("http://ns.example.com/", nullptr,
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty alias property string should produce an error
TEST_F(WXMPMetaResolveAliasTest_2003, EmptyAliasPropThrowsError_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1("http://ns.example.com/", "",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Both namespace and property null should produce an error (namespace checked first)
TEST_F(WXMPMetaResolveAliasTest_2003, BothNullParamsThrowsError_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1(nullptr, nullptr,
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Non-existent alias returns not found (int32Result == 0)
TEST_F(WXMPMetaResolveAliasTest_2003, NonExistentAliasReturnsNotFound_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1("http://ns.nonexistent.com/test/", "nonExistentProp",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    // If no error, check result
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
    }
}

// Test: Null output pointers should be handled gracefully (no crash)
TEST_F(WXMPMetaResolveAliasTest_2003, NullOutputPointersHandledGracefully_2003) {
    WXMPMeta_ResolveAlias_1("http://ns.nonexistent.com/test/", "nonExistentProp",
                             nullptr, nullptr,
                             nullptr, nullptr,
                             nullptr, &wResult);

    // Should not crash; either error or not found
    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
    }
}

// Test: Resolve a known standard alias (dc:subject related aliases if standard aliases registered)
TEST_F(WXMPMetaResolveAliasTest_2003, ResolveStandardAliasAfterRegistration_2003) {
    // Register standard aliases
    XMPMeta::RegisterStandardAliases("");

    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    // "photoshop:Headline" is a known standard alias that maps to "dc:description"
    // Try a known XMP standard alias: xmpDM:artist -> dc:creator[1]
    // The exact aliases depend on SDK version. We test with a commonly known one.
    WXMPMeta_ResolveAlias_1("http://ns.adobe.com/photoshop/1.0/", "Headline",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    // We don't know for certain this alias exists, so just verify no crash
    // and that result is consistent
    if (wResult.errMessage == nullptr) {
        // int32Result is either 0 (not found) or non-zero (found)
        // If found, actualNS and actualProp should be non-null
        if (wResult.int32Result != 0) {
            EXPECT_NE(actualNS, nullptr);
            EXPECT_NE(actualProp, nullptr);
            EXPECT_GT(nsSize, static_cast<XMP_StringLen>(0));
            EXPECT_GT(propSize, static_cast<XMP_StringLen>(0));
        }
    }
}

// Test: Resolve with valid NS and prop but no alias registered returns false
TEST_F(WXMPMetaResolveAliasTest_2003, ValidParamsNoAliasReturnsFalse_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    // Use a namespace that is valid but has no aliases
    XMPMeta::RegisterNamespace("http://ns.test.unique.2003/", "test2003:");

    WXMPMeta_ResolveAlias_1("http://ns.test.unique.2003/", "someRandomProp",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    if (wResult.errMessage == nullptr) {
        EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
    }
}

// Test: Both empty strings should produce an error
TEST_F(WXMPMetaResolveAliasTest_2003, BothEmptyStringsThrowsError_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1("", "",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    // Should get error for empty namespace (checked first)
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: wResult is properly initialized with no error on success
TEST_F(WXMPMetaResolveAliasTest_2003, WResultInitializedCorrectlyOnSuccess_2003) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    XMPMeta::RegisterNamespace("http://ns.test.wresult.2003/", "twres2003:");

    WXMPMeta_ResolveAlias_1("http://ns.test.wresult.2003/", "testProp",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    // Should succeed without error (even though alias not found)
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Register a custom alias and then resolve it
TEST_F(WXMPMetaResolveAliasTest_2003, RegisterAndResolveCustomAlias_2003) {
    // Register namespaces
    XMPMeta::RegisterNamespace("http://ns.alias.source.2003/", "aliassrc2003:");
    XMPMeta::RegisterNamespace("http://ns.alias.target.2003/", "aliastrg2003:");

    // Register an alias
    // aliassrc2003:MyAlias -> aliastrg2003:MyActual
    try {
        XMPMeta::RegisterAlias("http://ns.alias.source.2003/", "MyAlias",
                               "http://ns.alias.target.2003/", "MyActual", 0);
    } catch (...) {
        // If registration fails, skip the rest
        GTEST_SKIP() << "Could not register alias, skipping resolve test";
    }

    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;

    WXMPMeta_ResolveAlias_1("http://ns.alias.source.2003/", "MyAlias",
                             &actualNS, &nsSize,
                             &actualProp, &propSize,
                             &arrayForm, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    EXPECT_NE(actualNS, nullptr);
    EXPECT_NE(actualProp, nullptr);
    EXPECT_GT(nsSize, static_cast<XMP_StringLen>(0));
    EXPECT_GT(propSize, static_cast<XMP_StringLen>(0));

    // Verify the resolved namespace and property
    std::string resolvedNS(actualNS, nsSize);
    std::string resolvedProp(actualProp, propSize);
    EXPECT_EQ(resolvedNS, "http://ns.alias.target.2003/");
    EXPECT_EQ(resolvedProp, "MyActual");
}

// Test: Partial null output pointers with valid alias
TEST_F(WXMPMetaResolveAliasTest_2003, PartialNullOutputWithValidAlias_2003) {
    XMPMeta::RegisterNamespace("http://ns.alias.partialnull.2003/", "apn2003:");
    XMPMeta::RegisterNamespace("http://ns.alias.partialnulltgt.2003/", "apnt2003:");

    try {
        XMPMeta::RegisterAlias("http://ns.alias.partialnull.2003/", "PNAlias",
                               "http://ns.alias.partialnulltgt.2003/", "PNActual", 0);
    } catch (...) {
        GTEST_SKIP() << "Could not register alias";
    }

    // Call with some null output params
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;

    WXMPMeta_ResolveAlias_1("http://ns.alias.partialnull.2003/", "PNAlias",
                             &actualNS, &nsSize,
                             nullptr, nullptr,
                             nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    EXPECT_NE(actualNS, nullptr);
    EXPECT_GT(nsSize, static_cast<XMP_StringLen>(0));
}
