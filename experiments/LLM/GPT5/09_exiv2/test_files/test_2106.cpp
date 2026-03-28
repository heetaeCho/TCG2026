// =================================================================================================
// TEST_ID 2106
// Unit tests for static DeclareUsedNamespaces in XMPMeta-Serialize.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Pull in the real XMP types used by the implementation.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// -------------------------------------------------------------------------------------------------
// Test doubles for external collaborators called by DeclareUsedNamespaces.
// We redirect calls inside the included .cpp via preprocessor remapping.
// -------------------------------------------------------------------------------------------------

struct NSCall_2106 {
  enum Kind { kOne, kElem } kind;
  std::string a;  // nsURI or elemName
  std::string b;  // prefix (only for DeclareOneNamespace)
  std::string newline;
  std::string indentStr;
  XMP_Index indent = 0;
};

static std::vector<NSCall_2106> g_calls_2106;

static std::string SafeStr_2106(XMP_StringPtr s) {
  return (s == nullptr) ? std::string("<null>") : std::string(s);
}

// These signatures must match the ones used by XMPMeta-Serialize.cpp.
// They intentionally do NOT try to emulate behavior; they only record calls.
static void Test_DeclareOneNamespace_2106(XMP_StringPtr nsURI,
                                         XMP_StringPtr prefix,
                                         XMP_VarString& /*usedNS*/,
                                         XMP_VarString& /*outputStr*/,
                                         XMP_StringPtr newline,
                                         XMP_StringPtr indentStr,
                                         XMP_Index indent) {
  NSCall_2106 rec;
  rec.kind = NSCall_2106::kOne;
  rec.a = SafeStr_2106(nsURI);
  rec.b = SafeStr_2106(prefix);
  rec.newline = SafeStr_2106(newline);
  rec.indentStr = SafeStr_2106(indentStr);
  rec.indent = indent;
  g_calls_2106.push_back(rec);
}

static void Test_DeclareElemNamespace_2106(XMP_StringPtr elemName,
                                          XMP_VarString& /*usedNS*/,
                                          XMP_VarString& /*outputStr*/,
                                          XMP_StringPtr newline,
                                          XMP_StringPtr indentStr,
                                          XMP_Index indent) {
  NSCall_2106 rec;
  rec.kind = NSCall_2106::kElem;
  rec.a = SafeStr_2106(elemName);
  rec.newline = SafeStr_2106(newline);
  rec.indentStr = SafeStr_2106(indentStr);
  rec.indent = indent;
  g_calls_2106.push_back(rec);
}

// Remap collaborator names in the .cpp under test to our test doubles.
#define DeclareOneNamespace Test_DeclareOneNamespace_2106
#define DeclareElemNamespace Test_DeclareElemNamespace_2106

// Include the implementation so the file-static function is in this test TU.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

#undef DeclareOneNamespace
#undef DeclareElemNamespace

// -------------------------------------------------------------------------------------------------

class DeclareUsedNamespacesTest_2106 : public ::testing::Test {
 protected:
  std::vector<XMP_Node*> owned_;

  void SetUp() override { g_calls_2106.clear(); }

  void TearDown() override {
    for (XMP_Node* p : owned_) delete p;
    owned_.clear();
    g_calls_2106.clear();
  }

  XMP_Node* NewNode(XMP_Node* parent, XMP_StringPtr name, XMP_OptionBits options) {
    XMP_Node* n = new XMP_Node(parent, name, options);
    owned_.push_back(n);
    return n;
  }

  XMP_Node* NewNodeWithValue(XMP_Node* parent, XMP_StringPtr name, XMP_StringPtr value, XMP_OptionBits options) {
    XMP_Node* n = new XMP_Node(parent, name, value, options);
    owned_.push_back(n);
    return n;
  }
};

// -------------------------------------------------------------------------------------------------
// Tests
// -------------------------------------------------------------------------------------------------

TEST_F(DeclareUsedNamespacesTest_2106, NoSchemaNoStructNoChildrenNoQualifiers_DoesNotCallDeclHelpers_2106) {
  XMP_Node* root = NewNode(/*parent*/ nullptr, "root", /*options*/ 0);

  XMP_VarString usedNS("USED");
  XMP_VarString outputStr("OUT");
  const char* newline = "\n";
  const char* indentStr = "  ";
  const XMP_Index indent = 3;

  DeclareUsedNamespaces(root, usedNS, outputStr, newline, indentStr, indent);

  EXPECT_TRUE(g_calls_2106.empty());
  EXPECT_EQ(usedNS, "USED");
  EXPECT_EQ(outputStr, "OUT");
}

TEST_F(DeclareUsedNamespacesTest_2106, SchemaNode_CallsDeclareOneNamespaceOnceWithPassThroughArgs_2106) {
  XMP_Node* schema = NewNodeWithValue(/*parent*/ nullptr,
                                      /*name*/ "ns:prefix",
                                      /*value*/ "http://example.com/ns/",
                                      /*options*/ kXMP_SchemaNode);

  XMP_VarString usedNS;
  XMP_VarString outputStr;
  const char* newline = "\r\n";
  const char* indentStr = "\t";
  const XMP_Index indent = 7;

  DeclareUsedNamespaces(schema, usedNS, outputStr, newline, indentStr, indent);

  ASSERT_EQ(g_calls_2106.size(), 1u);
  EXPECT_EQ(g_calls_2106[0].kind, NSCall_2106::kOne);
  EXPECT_EQ(g_calls_2106[0].a, "http://example.com/ns/");  // nsURI
  EXPECT_EQ(g_calls_2106[0].b, "ns:prefix");               // prefix/name
  EXPECT_EQ(g_calls_2106[0].newline, "\r\n");
  EXPECT_EQ(g_calls_2106[0].indentStr, "\t");
  EXPECT_EQ(g_calls_2106[0].indent, indent);
}

TEST_F(DeclareUsedNamespacesTest_2106, StructNode_DeclaresElemNamespaceForEachDirectChildField_2106) {
  XMP_Node* st = NewNode(/*parent*/ nullptr, "st", kXMP_PropValueIsStruct);

  XMP_Node* f1 = NewNode(st, "a:field1", /*options*/ 0);
  XMP_Node* f2 = NewNode(st, "b:field2", /*options*/ 0);
  st->children.push_back(f1);
  st->children.push_back(f2);

  XMP_VarString usedNS;
  XMP_VarString outputStr;
  const char* newline = "\n";
  const char* indentStr = " ";
  const XMP_Index indent = 0;

  DeclareUsedNamespaces(st, usedNS, outputStr, newline, indentStr, indent);

  ASSERT_EQ(g_calls_2106.size(), 2u);
  EXPECT_EQ(g_calls_2106[0].kind, NSCall_2106::kElem);
  EXPECT_EQ(g_calls_2106[0].a, "a:field1");
  EXPECT_EQ(g_calls_2106[1].kind, NSCall_2106::kElem);
  EXPECT_EQ(g_calls_2106[1].a, "b:field2");
}

TEST_F(DeclareUsedNamespacesTest_2106, RecursesIntoChildren_DeclaresFromNestedSchemaNode_2106) {
  XMP_Node* root = NewNode(/*parent*/ nullptr, "root", /*options*/ 0);

  XMP_Node* childSchema = NewNodeWithValue(root, "c:pref", "http://child/ns/", kXMP_SchemaNode);
  root->children.push_back(childSchema);

  XMP_VarString usedNS;
  XMP_VarString outputStr;
  const char* newline = "\n";
  const char* indentStr = "  ";
  const XMP_Index indent = 1;

  DeclareUsedNamespaces(root, usedNS, outputStr, newline, indentStr, indent);

  ASSERT_EQ(g_calls_2106.size(), 1u);
  EXPECT_EQ(g_calls_2106[0].kind, NSCall_2106::kOne);
  EXPECT_EQ(g_calls_2106[0].a, "http://child/ns/");
  EXPECT_EQ(g_calls_2106[0].b, "c:pref");
}

TEST_F(DeclareUsedNamespacesTest_2106, Qualifier_DeclaresElemNamespaceAndRecursesIntoQualifierSubtree_2106) {
  XMP_Node* root = NewNode(/*parent*/ nullptr, "root", /*options*/ 0);

  // Qualifier itself: should cause DeclareElemNamespace(qual->name, ...)
  XMP_Node* qual = NewNode(root, "q:qual", /*options*/ 0);
  root->qualifiers.push_back(qual);

  // Nested under qualifier: schema node, should cause DeclareOneNamespace
  XMP_Node* nestedSchema = NewNodeWithValue(qual, "q:pref", "http://qual/ns/", kXMP_SchemaNode);
  qual->children.push_back(nestedSchema);

  XMP_VarString usedNS;
  XMP_VarString outputStr;
  const char* newline = "\n";
  const char* indentStr = "    ";
  const XMP_Index indent = 4;

  DeclareUsedNamespaces(root, usedNS, outputStr, newline, indentStr, indent);

  ASSERT_EQ(g_calls_2106.size(), 2u);

  EXPECT_EQ(g_calls_2106[0].kind, NSCall_2106::kElem);
  EXPECT_EQ(g_calls_2106[0].a, "q:qual");

  EXPECT_EQ(g_calls_2106[1].kind, NSCall_2106::kOne);
  EXPECT_EQ(g_calls_2106[1].a, "http://qual/ns/");
  EXPECT_EQ(g_calls_2106[1].b, "q:pref");
}

TEST_F(DeclareUsedNamespacesTest_2106, Boundary_EmptyNamesStillForwardedToHelperCalls_2106) {
  // Struct node with a child having empty name: should still invoke DeclareElemNamespace once.
  XMP_Node* st = NewNode(/*parent*/ nullptr, "st", kXMP_PropValueIsStruct);
  XMP_Node* emptyField = NewNode(st, "", /*options*/ 0);
  st->children.push_back(emptyField);

  XMP_VarString usedNS("u");
  XMP_VarString outputStr("o");
  DeclareUsedNamespaces(st, usedNS, outputStr, "\n", " ", 2);

  ASSERT_EQ(g_calls_2106.size(), 1u);
  EXPECT_EQ(g_calls_2106[0].kind, NSCall_2106::kElem);
  EXPECT_EQ(g_calls_2106[0].a, "");  // empty elemName forwarded
}