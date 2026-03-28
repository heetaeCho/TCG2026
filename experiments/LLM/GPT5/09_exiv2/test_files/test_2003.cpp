// =================================================================================================
// Copyright ...
// Unit tests for WXMPMeta_ResolveAlias_1
// TEST_ID: 2003
// =================================================================================================

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper function lives in WXMPMeta.cpp. Declare it here to avoid relying on a specific header.
extern "C" void WXMPMeta_ResolveAlias_1(XMP_StringPtr  aliasNS,
                                       XMP_StringPtr  aliasProp,
                                       XMP_StringPtr* actualNS,
                                       XMP_StringLen* nsSize,
                                       XMP_StringPtr* actualProp,
                                       XMP_StringLen* propSize,
                                       XMP_OptionBits* arrayForm,
                                       WXMP_Result*   wResult);

namespace {

class WXMPMetaResolveAlias1Test_2003 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // Initialize once for all tests in this suite. Safe even if already initialized in the process.
    XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

protected:
  void SetUp() override {
    // Best-effort cleanup of any aliases we might register (ignore failures/throws).
    try {
      XMPMeta::DeleteAlias(kAliasNS, kAliasProp);
    } catch (...) {
    }
    try {
      XMPMeta::DeleteAlias(kAliasNS, kAliasPropLong);
    } catch (...) {
    }
  }

  void TearDown() override {
    try {
      XMPMeta::DeleteAlias(kAliasNS, kAliasProp);
    } catch (...) {
    }
    try {
      XMPMeta::DeleteAlias(kAliasNS, kAliasPropLong);
    } catch (...) {
    }
  }

  static constexpr XMP_StringPtr kAliasNS = "http://example.com/xmp/alias/1.0/";
  static constexpr XMP_StringPtr kActualNS = "http://example.com/xmp/actual/1.0/";
  static constexpr XMP_StringPtr kAliasProp = "AliasProp";
  static constexpr XMP_StringPtr kActualProp = "ActualProp";
  static constexpr XMP_StringPtr kAliasPropLong =
      "AliasProp_"
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
};

TEST_F(WXMPMetaResolveAlias1Test_2003, EmptyAliasNamespace_Nullptr_2003) {
  WXMP_Result wr;
  XMP_StringPtr outNS = nullptr;
  XMP_StringLen outNSLen = 0;
  XMP_StringPtr outProp = nullptr;
  XMP_StringLen outPropLen = 0;
  XMP_OptionBits outForm = 0;

  WXMPMeta_ResolveAlias_1(nullptr, "SomeProp", &outNS, &outNSLen, &outProp, &outPropLen, &outForm, &wr);

  // Observable error reporting through WXMP_Result::errMessage should be present for bad params.
  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaResolveAlias1Test_2003, EmptyAliasNamespace_EmptyString_2003) {
  WXMP_Result wr;
  XMP_StringPtr outNS = nullptr;
  XMP_StringLen outNSLen = 0;
  XMP_StringPtr outProp = nullptr;
  XMP_StringLen outPropLen = 0;
  XMP_OptionBits outForm = 0;

  WXMPMeta_ResolveAlias_1("", "SomeProp", &outNS, &outNSLen, &outProp, &outPropLen, &outForm, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaResolveAlias1Test_2003, EmptyAliasProperty_Nullptr_2003) {
  WXMP_Result wr;
  XMP_StringPtr outNS = nullptr;
  XMP_StringLen outNSLen = 0;
  XMP_StringPtr outProp = nullptr;
  XMP_StringLen outPropLen = 0;
  XMP_OptionBits outForm = 0;

  WXMPMeta_ResolveAlias_1("http://example.com/ns/", nullptr, &outNS, &outNSLen, &outProp, &outPropLen, &outForm, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaResolveAlias1Test_2003, EmptyAliasProperty_EmptyString_2003) {
  WXMP_Result wr;
  XMP_StringPtr outNS = nullptr;
  XMP_StringLen outNSLen = 0;
  XMP_StringPtr outProp = nullptr;
  XMP_StringLen outPropLen = 0;
  XMP_OptionBits outForm = 0;

  WXMPMeta_ResolveAlias_1("http://example.com/ns/", "", &outNS, &outNSLen, &outProp, &outPropLen, &outForm, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaResolveAlias1Test_2003, NotFound_ReturnsFalse_NoError_2003) {
  WXMP_Result wr;
  XMP_StringPtr outNS = nullptr;
  XMP_StringLen outNSLen = 123;     // sentinel
  XMP_StringPtr outProp = nullptr;
  XMP_StringLen outPropLen = 456;   // sentinel
  XMP_OptionBits outForm = 0xFFFFFFFFu;

  WXMPMeta_ResolveAlias_1("http://example.com/xmp/unknown/1.0/",
                         "NoSuchAlias",
                         &outNS,
                         &outNSLen,
                         &outProp,
                         &outPropLen,
                         &outForm,
                         &wr);

  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_EQ(wr.int32Result, 0u);
}

TEST_F(WXMPMetaResolveAlias1Test_2003, ResolveAlias_Success_PopulatesOutputs_2003) {
  // Register namespaces (idempotent in typical XMP toolkits; treated as black box here).
  XMPMeta::RegisterNamespace(kAliasNS, "al");
  XMPMeta::RegisterNamespace(kActualNS, "ac");

  // Register an alias mapping.
  const XMP_OptionBits kArrayForm = 0; // simplest form; we only verify round-tripped observables.
  XMPMeta::RegisterAlias(kAliasNS, kAliasProp, kActualNS, kActualProp, kArrayForm);

  WXMP_Result wr;
  XMP_StringPtr outNS = nullptr;
  XMP_StringLen outNSLen = 0;
  XMP_StringPtr outProp = nullptr;
  XMP_StringLen outPropLen = 0;
  XMP_OptionBits outForm = 0xDEADBEEFu; // sentinel

  WXMPMeta_ResolveAlias_1(kAliasNS, kAliasProp, &outNS, &outNSLen, &outProp, &outPropLen, &outForm, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_EQ(wr.int32Result, 1u);

  // Output pointers/sizes should be meaningful when found is true.
  ASSERT_NE(outNS, nullptr);
  ASSERT_NE(outProp, nullptr);
  EXPECT_GT(outNSLen, 0u);
  EXPECT_GT(outPropLen, 0u);

  // The outputs should match the alias registration (observable contract of ResolveAlias).
  EXPECT_STREQ(outNS, kActualNS);
  EXPECT_STREQ(outProp, kActualProp);
  EXPECT_EQ(outForm, kArrayForm);
}

TEST_F(WXMPMetaResolveAlias1Test_2003, NullOutParams_AreAllowed_StillResolves_2003) {
  XMPMeta::RegisterNamespace(kAliasNS, "al");
  XMPMeta::RegisterNamespace(kActualNS, "ac");
  XMPMeta::RegisterAlias(kAliasNS, kAliasProp, kActualNS, kActualProp, 0);

  WXMP_Result wr;

  // All out-params null (except wResult), wrapper should supply internal defaults and not crash.
  WXMPMeta_ResolveAlias_1(kAliasNS, kAliasProp,
                         /*actualNS*/ nullptr,
                         /*nsSize*/ nullptr,
                         /*actualProp*/ nullptr,
                         /*propSize*/ nullptr,
                         /*arrayForm*/ nullptr,
                         &wr);

  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_EQ(wr.int32Result, 1u);
}

TEST_F(WXMPMetaResolveAlias1Test_2003, Boundary_LongPropertyName_AliasRegistrationAndResolution_2003) {
  XMPMeta::RegisterNamespace(kAliasNS, "al");
  XMPMeta::RegisterNamespace(kActualNS, "ac");

  // Use a long alias property name to exercise boundary conditions around name length handling.
  XMPMeta::RegisterAlias(kAliasNS, kAliasPropLong, kActualNS, kActualProp, 0);

  WXMP_Result wr;
  XMP_StringPtr outNS = nullptr;
  XMP_StringLen outNSLen = 0;
  XMP_StringPtr outProp = nullptr;
  XMP_StringLen outPropLen = 0;
  XMP_OptionBits outForm = 0;

  WXMPMeta_ResolveAlias_1(kAliasNS, kAliasPropLong, &outNS, &outNSLen, &outProp, &outPropLen, &outForm, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_EQ(wr.int32Result, 1u);

  ASSERT_NE(outNS, nullptr);
  ASSERT_NE(outProp, nullptr);
  EXPECT_STREQ(outNS, kActualNS);
  EXPECT_STREQ(outProp, kActualProp);
}

}  // namespace