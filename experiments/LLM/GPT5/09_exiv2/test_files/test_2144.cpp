// ============================================================================
// Unit tests for CompareNodeLangs (TEST_ID = 2144)
// File under test: ./TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp (static function)
// ============================================================================

#include <gtest/gtest.h>

#include <string>

// Bring in XMP_Node and related types.
#include "xmpsdk/src/XMPCore_Impl.hpp"

// Include the .cpp to access the TU-local static function (black-box testing,
// no reimplementation of logic).
#include "xmpsdk/src/XMPMeta.cpp"

namespace {

// Helper: create an XMP_Node with optional first qualifier (name/value),
// and optional extra qualifier(s). Parent pointers are set so that if the
// XMP_Node destructor owns/removes qualifiers, ownership is consistent.
static XMP_Node* MakeNodeWithQualifiers(const char* nodeName,
                                       const char* nodeValue,
                                       const char* firstQualName,
                                       const char* firstQualValue,
                                       bool addSecondQualifier = false,
                                       const char* secondQualName = "q:other",
                                       const char* secondQualValue = "ignored") {
  XMP_Node* node = new XMP_Node(/*parent*/ nullptr, nodeName, nodeValue, /*options*/ 0);

  if (firstQualName != nullptr) {
    XMP_Node* q1 = new XMP_Node(/*parent*/ node, firstQualName, firstQualValue, /*options*/ 0);
    node->qualifiers.push_back(q1);
  }

  if (addSecondQualifier) {
    XMP_Node* q2 = new XMP_Node(/*parent*/ node, secondQualName, secondQualValue, /*options*/ 0);
    node->qualifiers.push_back(q2);
  }

  return node;
}

static XMP_Node* MakeNodeNoQualifiers(const char* nodeName, const char* nodeValue) {
  return new XMP_Node(/*parent*/ nullptr, nodeName, nodeValue, /*options*/ 0);
}

}  // namespace

TEST(CompareNodeLangsTest_2144, ReturnsFalseWhenLeftHasNoQualifiers_2144) {
  XMP_Node* left = MakeNodeNoQualifiers("left", "v");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "xml:lang", "en");

  EXPECT_FALSE(CompareNodeLangs(left, right));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, ReturnsFalseWhenRightHasNoQualifiers_2144) {
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "xml:lang", "en");
  XMP_Node* right = MakeNodeNoQualifiers("right", "v");

  EXPECT_FALSE(CompareNodeLangs(left, right));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, ReturnsFalseWhenLeftFirstQualifierIsNotXmlLang_2144) {
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "not:lang", "en");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "xml:lang", "en");

  EXPECT_FALSE(CompareNodeLangs(left, right));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, ReturnsFalseWhenRightFirstQualifierIsNotXmlLang_2144) {
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "xml:lang", "en");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "not:lang", "en");

  EXPECT_FALSE(CompareNodeLangs(left, right));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, LeftXDefaultWinsAgainstNonDefault_2144) {
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "xml:lang", "x-default");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "xml:lang", "en");

  EXPECT_TRUE(CompareNodeLangs(left, right));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, RightXDefaultBeatsNonDefaultSoCompareReturnsFalse_2144) {
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "xml:lang", "en");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "xml:lang", "x-default");

  EXPECT_FALSE(CompareNodeLangs(left, right));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, BothXDefaultReturnsTrueDueToLeftPriority_2144) {
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "xml:lang", "x-default");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "xml:lang", "x-default");

  EXPECT_TRUE(CompareNodeLangs(left, right));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, LexicographicCompareForNonDefaultLanguages_2144) {
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "xml:lang", "en");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "xml:lang", "fr");

  EXPECT_TRUE(CompareNodeLangs(left, right));
  EXPECT_FALSE(CompareNodeLangs(right, left));

  delete left;
  delete right;
}

TEST(CompareNodeLangsTest_2144, UsesOnlyFirstQualifierEvenIfMoreQualifiersExist_2144) {
  // Boundary-ish case: first qualifier drives behavior; additional qualifiers should not change it.
  XMP_Node* left = MakeNodeWithQualifiers("left", "v", "xml:lang", "en",
                                         /*addSecondQualifier*/ true, "xml:lang", "zz");
  XMP_Node* right = MakeNodeWithQualifiers("right", "v", "xml:lang", "fr",
                                          /*addSecondQualifier*/ true, "q:any", "anything");

  EXPECT_TRUE(CompareNodeLangs(left, right));
  EXPECT_FALSE(CompareNodeLangs(right, left));

  delete left;
  delete right;
}