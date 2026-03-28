// =================================================================================================
// TEST_ID: 2004
// Unit tests for WXMPMeta_DeleteAlias_1
// File: test_wxmpmeta_deletealias_1_2004.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "xmpsdk/src/XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test is implemented in:
//   ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
//
// If there is an official header declaring this wrapper in your tree, prefer including it.
// For this black-box test, we forward-declare the C wrapper.
extern "C" {
void WXMPMeta_DeleteAlias_1(XMP_StringPtr aliasNS, XMP_StringPtr aliasProp, WXMP_Result* wResult);
}

namespace {

static const char* kTestAliasNS   = "http://example.com/ns/alias/2004/";
static const char* kTestActualNS  = "http://example.com/ns/actual/2004/";
static const char* kTestAliasProp = "AliasProp2004";
static const char* kTestActualProp = "ActualProp2004";

class WXMPMeta_DeleteAlias_1_Test_2004 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // XMPMeta requires global initialization in many builds.
    // Treat as black-box; if already initialized, Initialize() should be safe or return true.
    (void)XMPMeta::Initialize();

    // Register test namespaces (ignore if duplicates exist).
    // XMPMeta::RegisterNamespace returns void; errors (if any) would be via exceptions internally.
    XMPMeta::RegisterNamespace(kTestAliasNS, "al2004");
    XMPMeta::RegisterNamespace(kTestActualNS, "ac2004");
  }

  static void TearDownTestSuite() {
    // Balance Initialize; if the library tolerates repeated init/term across tests, this is fine.
    XMPMeta::Terminate();
  }

  void SetUp() override {
    // Ensure a clean slate for each test: attempt to delete alias if present.
    // We intentionally do not assert on this cleanup behavior.
    WXMP_Result cleanup;
    WXMPMeta_DeleteAlias_1(kTestAliasNS, kTestAliasProp, &cleanup);
  }

  static bool ResolveAliasExists(XMP_StringPtr aliasNS, XMP_StringPtr aliasProp) {
    XMP_StringPtr actualNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr actualProp = nullptr;
    XMP_StringLen propSize = 0;
    XMP_OptionBits arrayForm = 0;
    return XMPMeta::ResolveAlias(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, &propSize, &arrayForm);
  }

  static void RegisterTestAlias() {
    // RegisterAlias is part of the public interface; we use it to create observable state.
    XMPMeta::RegisterAlias(kTestAliasNS, kTestAliasProp, kTestActualNS, kTestActualProp, /*arrayForm*/ 0);
  }
};

TEST_F(WXMPMeta_DeleteAlias_1_Test_2004, DeletesExistingAliasAndClearsResolution_2004) {
  // Arrange
  RegisterTestAlias();
  ASSERT_TRUE(ResolveAliasExists(kTestAliasNS, kTestAliasProp));

  WXMP_Result r;

  // Act
  WXMPMeta_DeleteAlias_1(kTestAliasNS, kTestAliasProp, &r);

  // Assert (observable behavior only)
  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_FALSE(ResolveAliasExists(kTestAliasNS, kTestAliasProp));
}

TEST_F(WXMPMeta_DeleteAlias_1_Test_2004, NullAliasNamespaceReportsBadSchema_2004) {
  // Arrange
  WXMP_Result r;

  // Act
  WXMPMeta_DeleteAlias_1(/*aliasNS*/ nullptr, kTestAliasProp, &r);

  // Assert
  // Observable error reporting: wrapper is expected to surface an error via WXMP_Result.
  EXPECT_NE(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, static_cast<XMP_Uns32>(kXMPErr_BadSchema));
}

TEST_F(WXMPMeta_DeleteAlias_1_Test_2004, EmptyAliasNamespaceReportsBadSchema_2004) {
  // Arrange
  WXMP_Result r;

  // Act
  WXMPMeta_DeleteAlias_1(/*aliasNS*/ "", kTestAliasProp, &r);

  // Assert
  EXPECT_NE(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, static_cast<XMP_Uns32>(kXMPErr_BadSchema));
}

TEST_F(WXMPMeta_DeleteAlias_1_Test_2004, NullAliasPropertyReportsBadXPath_2004) {
  // Arrange
  WXMP_Result r;

  // Act
  WXMPMeta_DeleteAlias_1(kTestAliasNS, /*aliasProp*/ nullptr, &r);

  // Assert
  EXPECT_NE(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, static_cast<XMP_Uns32>(kXMPErr_BadXPath));
}

TEST_F(WXMPMeta_DeleteAlias_1_Test_2004, EmptyAliasPropertyReportsBadXPath_2004) {
  // Arrange
  WXMP_Result r;

  // Act
  WXMPMeta_DeleteAlias_1(kTestAliasNS, /*aliasProp*/ "", &r);

  // Assert
  EXPECT_NE(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, static_cast<XMP_Uns32>(kXMPErr_BadXPath));
}

TEST_F(WXMPMeta_DeleteAlias_1_Test_2004, DeletingNonexistentAliasDoesNotCreateAlias_2004) {
  // Arrange
  // Ensure it does not exist before we begin.
  ASSERT_FALSE(ResolveAliasExists(kTestAliasNS, kTestAliasProp));

  WXMP_Result r;

  // Act
  WXMPMeta_DeleteAlias_1(kTestAliasNS, kTestAliasProp, &r);

  // Assert (black-box friendly):
  // - Regardless of whether deletion reports an error or not, it must not create an alias.
  EXPECT_FALSE(ResolveAliasExists(kTestAliasNS, kTestAliasProp));

  // If the wrapper treats "not found" as non-error, errMessage should remain null.
  // If it reports an error, this expectation can be relaxed in your environment.
  // Keeping it strict here because DeleteAlias commonly behaves as "no-op if missing".
  EXPECT_EQ(r.errMessage, nullptr);
}

}  // namespace