// ============================================================================
// TEST_ID 2098
// Unit tests for static AddSchemaAliases (XMPIterator.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// The function under test has internal linkage (static in XMPIterator.cpp).
// To test it via its provided signature/observable behavior, we include the .cpp
// into this test translation unit.
#include "TestProjects/exiv2/xmpsdk/src/XMPIterator.cpp"

#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// If your build provides XMP_Error in a different header, adjust include(s) as needed.
// In Adobe XMP toolkit, XMP_Error is commonly declared in XMP.hpp / XMPCommon.hpp.
#include "TestProjects/exiv2/xmpsdk/include/XMP.hpp"

namespace {

// Helper to register a namespace with a unique URI and prefix.
static void RegisterNsOrDie(const std::string& uri, const std::string& prefix) {
  // RegisterNamespace is void; it may throw on invalid input. We keep tests strict.
  XMPMeta::RegisterNamespace(uri.c_str(), prefix.c_str());
}

// Helper to delete namespace (best-effort; API is void).
static void DeleteNsBestEffort(const std::string& uri) {
  try {
    XMPMeta::DeleteNamespace(uri.c_str());
  } catch (...) {
    // best-effort cleanup
  }
}

// Helper to delete alias (best-effort; API is void).
static void DeleteAliasBestEffort(const std::string& aliasNS, const std::string& aliasProp) {
  try {
    XMPMeta::DeleteAlias(aliasNS.c_str(), aliasProp.c_str());
  } catch (...) {
    // best-effort cleanup
  }
}

class XMPIterator_AddSchemaAliasesTest_2098 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Ensure global tables (namespaces/aliases) are ready.
    ASSERT_TRUE(XMPMeta::Initialize());
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

  void SetUp() override { xmp_.Erase(); }

  XMPMeta xmp_;
};

}  // namespace

// ----------------------------------------------------------------------------
// Normal / error behavior
// ----------------------------------------------------------------------------

TEST_F(XMPIterator_AddSchemaAliasesTest_2098, UnknownSchemaNamespaceThrows_2098) {
  IterInfo info(/*options*/ 0, &xmp_);
  IterNode iterSchema;
  const char* unknownSchemaURI = "http://ns.example.com/test2098/unknown/";

  EXPECT_THROW(AddSchemaAliases(info, iterSchema, unknownSchemaURI), XMP_Error);
}

TEST_F(XMPIterator_AddSchemaAliasesTest_2098, NoAliasesRegisteredKeepsChildrenEmpty_2098) {
  const std::string aliasNS = "http://ns.example.com/test2098/ns1/";
  const std::string aliasPrefix = "t2098_1:";

  RegisterNsOrDie(aliasNS, aliasPrefix);

  IterInfo info(/*options*/ 0, &xmp_);
  IterNode iterSchema;

  ASSERT_TRUE(iterSchema.children.empty());
  EXPECT_NO_THROW(AddSchemaAliases(info, iterSchema, aliasNS.c_str()));
  EXPECT_TRUE(iterSchema.children.empty());

  DeleteNsBestEffort(aliasNS);
}

TEST_F(XMPIterator_AddSchemaAliasesTest_2098, AliasWithExistingActualPropertyAddsChild_2098) {
  const std::string aliasNS = "http://ns.example.com/test2098/ns2/alias/";
  const std::string aliasPrefix = "t2098_2:";

  const std::string actualNS = "http://ns.example.com/test2098/ns2/actual/";
  const std::string actualPrefix = "t2098_2a:";

  RegisterNsOrDie(aliasNS, aliasPrefix);
  RegisterNsOrDie(actualNS, actualPrefix);

  // Create actual property in the XMP tree via public API.
  xmp_.SetProperty(actualNS.c_str(), "ActualProp", "value", /*options*/ 0);

  // Register alias: aliasNS:AliasProp -> actualNS:ActualProp
  XMPMeta::RegisterAlias(aliasNS.c_str(), "AliasProp", actualNS.c_str(), "ActualProp", /*arrayForm*/ 0);

  IterInfo info(/*options*/ 0, &xmp_);
  IterNode iterSchema;

  EXPECT_NO_THROW(AddSchemaAliases(info, iterSchema, aliasNS.c_str()));

  ASSERT_EQ(iterSchema.children.size(), 1u);
  EXPECT_EQ(iterSchema.children[0].fullPath, (aliasPrefix + "AliasProp"));
  EXPECT_NE((iterSchema.children[0].options & kXMP_PropIsAlias), 0u);

  DeleteAliasBestEffort(aliasNS, "AliasProp");
  DeleteNsBestEffort(aliasNS);
  DeleteNsBestEffort(actualNS);
}

TEST_F(XMPIterator_AddSchemaAliasesTest_2098, AliasWithoutActualPropertyDoesNotAddChild_2098) {
  const std::string aliasNS = "http://ns.example.com/test2098/ns3/alias/";
  const std::string aliasPrefix = "t2098_3:";

  const std::string actualNS = "http://ns.example.com/test2098/ns3/actual/";
  const std::string actualPrefix = "t2098_3a:";

  RegisterNsOrDie(aliasNS, aliasPrefix);
  RegisterNsOrDie(actualNS, actualPrefix);

  // Register alias, but DO NOT create actual property in xmp_.
  XMPMeta::RegisterAlias(aliasNS.c_str(), "AliasProp", actualNS.c_str(), "MissingActualProp", /*arrayForm*/ 0);

  IterInfo info(/*options*/ 0, &xmp_);
  IterNode iterSchema;

  EXPECT_NO_THROW(AddSchemaAliases(info, iterSchema, aliasNS.c_str()));
  EXPECT_TRUE(iterSchema.children.empty());

  DeleteAliasBestEffort(aliasNS, "AliasProp");
  DeleteNsBestEffort(aliasNS);
  DeleteNsBestEffort(actualNS);
}

TEST_F(XMPIterator_AddSchemaAliasesTest_2098, OnlyAliasesMatchingSchemaPrefixAreAdded_2098) {
  const std::string aliasNS1 = "http://ns.example.com/test2098/ns4/alias1/";
  const std::string aliasPrefix1 = "t2098_4:";

  const std::string aliasNS2 = "http://ns.example.com/test2098/ns4/alias2/";
  const std::string aliasPrefix2 = "t2098_4b:";

  const std::string actualNS = "http://ns.example.com/test2098/ns4/actual/";
  const std::string actualPrefix = "t2098_4a:";

  RegisterNsOrDie(aliasNS1, aliasPrefix1);
  RegisterNsOrDie(aliasNS2, aliasPrefix2);
  RegisterNsOrDie(actualNS, actualPrefix);

  // Actual properties exist for both alias registrations.
  xmp_.SetProperty(actualNS.c_str(), "ActualProp1", "v1", 0);
  xmp_.SetProperty(actualNS.c_str(), "ActualProp2", "v2", 0);

  XMPMeta::RegisterAlias(aliasNS1.c_str(), "AliasProp1", actualNS.c_str(), "ActualProp1", 0);
  XMPMeta::RegisterAlias(aliasNS2.c_str(), "AliasProp2", actualNS.c_str(), "ActualProp2", 0);

  IterInfo info(/*options*/ 0, &xmp_);
  IterNode iterSchema;

  // Call using aliasNS1: should only add alias keys with prefix aliasPrefix1.
  EXPECT_NO_THROW(AddSchemaAliases(info, iterSchema, aliasNS1.c_str()));

  ASSERT_EQ(iterSchema.children.size(), 1u);
  EXPECT_EQ(iterSchema.children[0].fullPath, (aliasPrefix1 + "AliasProp1"));
  EXPECT_NE((iterSchema.children[0].options & kXMP_PropIsAlias), 0u);

  DeleteAliasBestEffort(aliasNS1, "AliasProp1");
  DeleteAliasBestEffort(aliasNS2, "AliasProp2");
  DeleteNsBestEffort(aliasNS1);
  DeleteNsBestEffort(aliasNS2);
  DeleteNsBestEffort(actualNS);
}

// ----------------------------------------------------------------------------
// Boundary / behavioral details observable via public members
// ----------------------------------------------------------------------------

TEST_F(XMPIterator_AddSchemaAliasesTest_2098, AppendsToExistingChildrenDoesNotClear_2098) {
  const std::string aliasNS = "http://ns.example.com/test2098/ns5/alias/";
  const std::string aliasPrefix = "t2098_5:";

  const std::string actualNS = "http://ns.example.com/test2098/ns5/actual/";
  const std::string actualPrefix = "t2098_5a:";

  RegisterNsOrDie(aliasNS, aliasPrefix);
  RegisterNsOrDie(actualNS, actualPrefix);

  xmp_.SetProperty(actualNS.c_str(), "ActualProp", "value", 0);
  XMPMeta::RegisterAlias(aliasNS.c_str(), "AliasProp", actualNS.c_str(), "ActualProp", 0);

  IterInfo info(/*options*/ 0, &xmp_);
  IterNode iterSchema;

  // Pre-populate children with a sentinel node.
  iterSchema.children.push_back(IterNode(/*options*/ 0, "sentinel:path", /*leafOffset*/ 0));
  const size_t before = iterSchema.children.size();
  ASSERT_EQ(before, 1u);

  EXPECT_NO_THROW(AddSchemaAliases(info, iterSchema, aliasNS.c_str()));

  ASSERT_EQ(iterSchema.children.size(), before + 1);
  EXPECT_EQ(iterSchema.children[0].fullPath, "sentinel:path");
  EXPECT_EQ(iterSchema.children[1].fullPath, (aliasPrefix + "AliasProp"));
  EXPECT_NE((iterSchema.children[1].options & kXMP_PropIsAlias), 0u);

  DeleteAliasBestEffort(aliasNS, "AliasProp");
  DeleteNsBestEffort(aliasNS);
  DeleteNsBestEffort(actualNS);
}