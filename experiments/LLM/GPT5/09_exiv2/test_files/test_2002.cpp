// =================================================================================================
// UNIT TESTS for WXMPMeta_RegisterAlias_1 (TEST_ID = 2002)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// These headers are part of the XMP SDK tree used by Exiv2.
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_RegisterAlias_1(XMP_StringPtr aliasNS,
                                        XMP_StringPtr aliasProp,
                                        XMP_StringPtr actualNS,
                                        XMP_StringPtr actualProp,
                                        XMP_OptionBits arrayForm,
                                        WXMP_Result* wResult);

namespace {

class WXMPMetaRegisterAlias1Test_2002 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // Many XMP SDK entry points require initialization. If Initialize returns false,
    // tests might still run in some builds, but this avoids undefined behavior where possible.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

protected:
  static void EnsureNamespaceRegistered(XMP_StringPtr nsURI, XMP_StringPtr prefix) {
    // RegisterNamespace may throw for invalid params; test inputs are well-formed.
    XMPMeta::RegisterNamespace(nsURI, prefix);
  }

  static void DeleteAliasNoThrow(XMP_StringPtr aliasNS, XMP_StringPtr aliasProp) {
    try {
      XMPMeta::DeleteAlias(aliasNS, aliasProp);
    } catch (...) {
      // Best-effort cleanup; tests must not depend on DeleteAlias behavior.
    }
  }

  static std::string ToStringWithSize(XMP_StringPtr s, XMP_StringLen n) {
    if (s == nullptr) return std::string();
    return std::string(s, static_cast<size_t>(n));
  }
};

// -------------------------------
// Error / exceptional cases
// -------------------------------

TEST_F(WXMPMetaRegisterAlias1Test_2002, NullAliasNamespaceSetsError_2002) {
  WXMP_Result r;
  const char* aliasProp = "prop";
  const char* actualNS = "http://ns.example.com/actual/2002/";
  const char* actualProp = "actualProp";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(nullptr, aliasProp, actualNS, actualProp, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);

  // Alias should not resolve if registration failed.
  XMP_StringPtr outNS = nullptr, outProp = nullptr;
  XMP_StringLen outNSSize = 0, outPropSize = 0;
  XMP_OptionBits outForm = 0;
  EXPECT_FALSE(XMPMeta::ResolveAlias(nullptr, aliasProp, &outNS, &outNSSize, &outProp, &outPropSize, &outForm));
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, EmptyAliasNamespaceSetsError_2002) {
  WXMP_Result r;
  const char* aliasNS = "";
  const char* aliasProp = "prop";
  const char* actualNS = "http://ns.example.com/actual/2002/";
  const char* actualProp = "actualProp";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, NullAliasPropertySetsError_2002) {
  WXMP_Result r;
  const char* aliasNS = "http://ns.example.com/alias/2002/";
  const char* actualNS = "http://ns.example.com/actual/2002/";
  const char* actualProp = "actualProp";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, nullptr, actualNS, actualProp, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, EmptyAliasPropertySetsError_2002) {
  WXMP_Result r;
  const char* aliasNS = "http://ns.example.com/alias/2002/";
  const char* aliasProp = "";
  const char* actualNS = "http://ns.example.com/actual/2002/";
  const char* actualProp = "actualProp";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, NullActualNamespaceSetsError_2002) {
  WXMP_Result r;
  const char* aliasNS = "http://ns.example.com/alias/2002/";
  const char* aliasProp = "prop";
  const char* actualProp = "actualProp";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, nullptr, actualProp, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, EmptyActualNamespaceSetsError_2002) {
  WXMP_Result r;
  const char* aliasNS = "http://ns.example.com/alias/2002/";
  const char* aliasProp = "prop";
  const char* actualNS = "";
  const char* actualProp = "actualProp";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, NullActualPropertySetsError_2002) {
  WXMP_Result r;
  const char* aliasNS = "http://ns.example.com/alias/2002/";
  const char* aliasProp = "prop";
  const char* actualNS = "http://ns.example.com/actual/2002/";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, nullptr, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, EmptyActualPropertySetsError_2002) {
  WXMP_Result r;
  const char* aliasNS = "http://ns.example.com/alias/2002/";
  const char* aliasProp = "prop";
  const char* actualNS = "http://ns.example.com/actual/2002/";
  const char* actualProp = "";

  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, 0, &r));
  EXPECT_NE(r.errMessage, nullptr);
}

// -------------------------------
// Normal operation + observable interactions via XMPMeta::ResolveAlias
// -------------------------------

TEST_F(WXMPMetaRegisterAlias1Test_2002, RegistersAliasAndResolvesToActual_2002) {
  const char* aliasNS = "http://ns.example.com/alias/2002/";
  const char* actualNS = "http://ns.example.com/actual/2002/";
  const char* aliasProp = "AliasProp2002";
  const char* actualProp = "ActualProp2002";
  const XMP_OptionBits form = 0;

  // Best-effort isolation.
  DeleteAliasNoThrow(aliasNS, aliasProp);

  // Ensure namespaces exist in the registry (avoids dependence on implicit registration).
  EnsureNamespaceRegistered(aliasNS, "al2002:");
  EnsureNamespaceRegistered(actualNS, "ac2002:");

  WXMP_Result r;
  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, form, &r));
  EXPECT_EQ(r.errMessage, nullptr);

  XMP_StringPtr outNS = nullptr, outProp = nullptr;
  XMP_StringLen outNSSize = 0, outPropSize = 0;
  XMP_OptionBits outForm = 0;

  EXPECT_TRUE(XMPMeta::ResolveAlias(aliasNS, aliasProp,
                                   &outNS, &outNSSize,
                                   &outProp, &outPropSize,
                                   &outForm));

  EXPECT_EQ(ToStringWithSize(outNS, outNSSize), std::string(actualNS));
  EXPECT_EQ(ToStringWithSize(outProp, outPropSize), std::string(actualProp));
  EXPECT_EQ(outForm, form);

  DeleteAliasNoThrow(aliasNS, aliasProp);
}

TEST_F(WXMPMetaRegisterAlias1Test_2002, ReRegisteringSameAliasUpdatesResolution_2002) {
  const char* aliasNS = "http://ns.example.com/alias/2002/reregister/";
  const char* actualNS = "http://ns.example.com/actual/2002/reregister/";
  const char* aliasProp = "AliasPropReReg2002";
  const char* actualProp1 = "ActualPropFirst2002";
  const char* actualProp2 = "ActualPropSecond2002";

  DeleteAliasNoThrow(aliasNS, aliasProp);
  EnsureNamespaceRegistered(aliasNS, "ar2002:");
  EnsureNamespaceRegistered(actualNS, "rr2002:");

  WXMP_Result r1;
  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp1, 0, &r1));
  EXPECT_EQ(r1.errMessage, nullptr);

  WXMP_Result r2;
  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp2, 0, &r2));
  EXPECT_EQ(r2.errMessage, nullptr);

  XMP_StringPtr outNS = nullptr, outProp = nullptr;
  XMP_StringLen outNSSize = 0, outPropSize = 0;
  XMP_OptionBits outForm = 0;

  EXPECT_TRUE(XMPMeta::ResolveAlias(aliasNS, aliasProp,
                                   &outNS, &outNSSize,
                                   &outProp, &outPropSize,
                                   &outForm));

  EXPECT_EQ(ToStringWithSize(outNS, outNSSize), std::string(actualNS));
  EXPECT_EQ(ToStringWithSize(outProp, outPropSize), std::string(actualProp2));

  DeleteAliasNoThrow(aliasNS, aliasProp);
}

// -------------------------------
// Boundary-ish inputs (observable success + resolution)
// -------------------------------

TEST_F(WXMPMetaRegisterAlias1Test_2002, LongPropertyNamesStillRegisterAndResolve_2002) {
  const char* aliasNS = "http://ns.example.com/alias/2002/long/";
  const char* actualNS = "http://ns.example.com/actual/2002/long/";

  // Create long but valid-ish names (no embedded NUL).
  std::string aliasProp(512, 'A');
  std::string actualProp(512, 'B');

  DeleteAliasNoThrow(aliasNS, aliasProp.c_str());
  EnsureNamespaceRegistered(aliasNS, "l2002a:");
  EnsureNamespaceRegistered(actualNS, "l2002b:");

  WXMP_Result r;
  EXPECT_NO_THROW(WXMPMeta_RegisterAlias_1(aliasNS, aliasProp.c_str(),
                                          actualNS, actualProp.c_str(),
                                          0, &r));
  EXPECT_EQ(r.errMessage, nullptr);

  XMP_StringPtr outNS = nullptr, outProp = nullptr;
  XMP_StringLen outNSSize = 0, outPropSize = 0;
  XMP_OptionBits outForm = 0;

  EXPECT_TRUE(XMPMeta::ResolveAlias(aliasNS, aliasProp.c_str(),
                                   &outNS, &outNSSize,
                                   &outProp, &outPropSize,
                                   &outForm));

  EXPECT_EQ(ToStringWithSize(outNS, outNSSize), std::string(actualNS));
  EXPECT_EQ(ToStringWithSize(outProp, outPropSize), actualProp);

  DeleteAliasNoThrow(aliasNS, aliasProp.c_str());
}

}  // namespace