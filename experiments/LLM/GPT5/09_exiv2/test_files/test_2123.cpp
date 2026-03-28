// =================================================================================================
// Unit tests for FixupQualifiedNode (ParseRDF.cpp)
// TEST_ID: 2123
//
// Notes:
// - We treat the implementation as a black box (no re-implementation of logic).
// - FixupQualifiedNode is a file-static function in ParseRDF.cpp. To test it, we include ParseRDF.cpp
//   directly into this test translation unit so the static symbol is visible.
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Include core XMP types used by ParseRDF.cpp.
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// IMPORTANT: Include the .cpp under test to access the file-static FixupQualifiedNode.
#include "ParseRDF.cpp"

namespace {

class FixupQualifiedNodeTest_2123 : public ::testing::Test {
protected:
  static XMP_Node* NewNode(XMP_Node* parent, const char* name, XMP_OptionBits options = 0) {
    return new XMP_Node(parent, name, options);
  }

  static XMP_Node* NewNodeWithValue(XMP_Node* parent,
                                   const char* name,
                                   const char* value,
                                   XMP_OptionBits options = 0) {
    return new XMP_Node(parent, name, value, options);
  }

  static void AddChild(XMP_Node* parent, XMP_Node* child) {
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(child, nullptr);
    child->parent = parent;
    parent->children.push_back(child);
  }

  static void AddQualifier(XMP_Node* parent, XMP_Node* qual) {
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(qual, nullptr);
    qual->parent = parent;
    parent->qualifiers.push_back(qual);
  }

  static XMP_Node* MakeQualifiedParentWithValueNode(XMP_OptionBits parentOptions,
                                                    XMP_Node** outValueNode) {
    // Parent must be a struct and have at least one child (rdf:value at [0]).
    auto* parent = NewNode(nullptr, "ex:Parent", parentOptions);
    auto* valueNode = NewNodeWithValue(parent, "rdf:value", "VALUE", 0);
    AddChild(parent, valueNode);
    if (outValueNode) *outValueNode = valueNode;
    return parent;
  }
};

TEST_F(FixupQualifiedNodeTest_2123, MovesXmlLangFromValueQualifierToParent_2123) {
  XMP_Node* valueNode = nullptr;
  XMP_Node* parent =
      MakeQualifiedParentWithValueNode(kXMP_PropValueIsStruct | kRDF_HasValueElem, &valueNode);
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(valueNode, nullptr);

  // Add xml:lang qualifier to rdf:value, marked as having lang.
  auto* langQual = NewNodeWithValue(valueNode, "xml:lang", "en-US", 0);
  AddQualifier(valueNode, langQual);
  valueNode->options |= kXMP_PropHasLang;

  // Add an additional qualifier to rdf:value (to ensure remaining qualifiers are copied too).
  auto* otherQual = NewNodeWithValue(valueNode, "ex:q1", "qv1", 0);
  AddQualifier(valueNode, otherQual);

  // Provide some valueNode children to verify they get swapped into parent children.
  auto* vnChild1 = NewNodeWithValue(valueNode, "ex:child1", "c1", 0);
  auto* vnChild2 = NewNodeWithValue(valueNode, "ex:child2", "c2", 0);
  AddChild(valueNode, vnChild1);
  AddChild(valueNode, vnChild2);

  // Precondition checks.
  ASSERT_EQ(parent->children.size(), 1U);
  ASSERT_EQ(parent->children[0]->name, "rdf:value");
  ASSERT_EQ(parent->qualifiers.size(), 0U);

  FixupQualifiedNode(parent);

  // Parent now should have taken rdf:value's value.
  EXPECT_EQ(parent->value, "VALUE");

  // Struct/value-elem flags should be cleared.
  EXPECT_EQ((parent->options & kXMP_PropValueIsStruct), 0U);
  EXPECT_EQ((parent->options & kRDF_HasValueElem), 0U);

  // xml:lang should be on the parent and first (if qualifiers exist).
  EXPECT_NE((parent->options & kXMP_PropHasLang), 0U);
  ASSERT_FALSE(parent->qualifiers.empty());
  EXPECT_EQ(parent->qualifiers[0]->name, "xml:lang");
  EXPECT_EQ(parent->qualifiers[0]->parent, parent);

  // The other qualifier should also have been moved to parent.
  bool foundQ1 = false;
  for (auto* q : parent->qualifiers) {
    if (q && q->name == "ex:q1") {
      foundQ1 = true;
      EXPECT_EQ(q->parent, parent);
      break;
    }
  }
  EXPECT_TRUE(foundQ1);

  // Parent should now have children from valueNode (not the original rdf:value wrapper).
  ASSERT_EQ(parent->children.size(), 2U);
  EXPECT_EQ(parent->children[0]->name, "ex:child1");
  EXPECT_EQ(parent->children[1]->name, "ex:child2");
  EXPECT_EQ(parent->children[0]->parent, parent);
  EXPECT_EQ(parent->children[1]->parent, parent);

  // Parent should indicate it has qualifiers.
  EXPECT_NE((parent->options & kXMP_PropHasQualifiers), 0U);

  delete parent;  // valueNode was deleted by FixupQualifiedNode.
}

TEST_F(FixupQualifiedNodeTest_2123, MovesExtraChildrenToQualifiersAndMarksQualifierBit_2123) {
  XMP_Node* valueNode = nullptr;
  XMP_Node* parent =
      MakeQualifiedParentWithValueNode(kXMP_PropValueIsStruct | kRDF_HasValueElem, &valueNode);
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(valueNode, nullptr);

  // Add extra children to parent; FixupQualifiedNode treats children[1..] as qualifiers.
  auto* qChild1 = NewNodeWithValue(parent, "ex:qualFromChild", "v", 0);
  auto* qChild2 = NewNodeWithValue(parent, "rdf:type", "T", 0);
  AddChild(parent, qChild1);
  AddChild(parent, qChild2);

  // Also give valueNode a child to ensure swap occurs.
  auto* vnChild = NewNodeWithValue(valueNode, "ex:child", "c", 0);
  AddChild(valueNode, vnChild);

  FixupQualifiedNode(parent);

  // Children should now be from valueNode, not the original list (which included extra "qual" children).
  ASSERT_EQ(parent->children.size(), 1U);
  EXPECT_EQ(parent->children[0]->name, "ex:child");
  EXPECT_EQ(parent->children[0]->parent, parent);

  // The two extra children should now be qualifiers on parent.
  bool foundFromChild = false;
  bool foundType = false;
  for (auto* q : parent->qualifiers) {
    if (!q) continue;
    if (q->name == "ex:qualFromChild") {
      foundFromChild = true;
      EXPECT_NE((q->options & kXMP_PropIsQualifier), 0U);
      EXPECT_EQ(q->parent, parent);
    } else if (q->name == "rdf:type") {
      foundType = true;
      EXPECT_NE((q->options & kXMP_PropIsQualifier), 0U);
      EXPECT_EQ(q->parent, parent);
    }
  }
  EXPECT_TRUE(foundFromChild);
  EXPECT_TRUE(foundType);

  // rdf:type should set the parent's has-type option.
  EXPECT_NE((parent->options & kXMP_PropHasType), 0U);

  delete parent;
}

TEST_F(FixupQualifiedNodeTest_2123, ThrowsIfParentAlreadyHasLangAndValueNodeHasLang_2123) {
  XMP_Node* valueNode = nullptr;
  XMP_Node* parent = MakeQualifiedParentWithValueNode(
      (kXMP_PropValueIsStruct | kRDF_HasValueElem | kXMP_PropHasLang), &valueNode);
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(valueNode, nullptr);

  // rdf:value has xml:lang.
  auto* langQual = NewNodeWithValue(valueNode, "xml:lang", "fr-FR", 0);
  AddQualifier(valueNode, langQual);
  valueNode->options |= kXMP_PropHasLang;

  EXPECT_ANY_THROW(FixupQualifiedNode(parent));

  // Cleanup: FixupQualifiedNode threw, so it should not have deleted valueNode.
  delete parent;  // XMP_Node destructor should clean up descendants in the real codebase.
}

TEST_F(FixupQualifiedNodeTest_2123, ThrowsIfDuplicateXmlLangInChildQualifiers_2123) {
  XMP_Node* valueNode = nullptr;
  XMP_Node* parent =
      MakeQualifiedParentWithValueNode(kXMP_PropValueIsStruct | kRDF_HasValueElem, &valueNode);
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(valueNode, nullptr);

  // Provide xml:lang as an extra child (will become a qualifier).
  auto* langFromChild = NewNodeWithValue(parent, "xml:lang", "en-US", 0);
  AddChild(parent, langFromChild);

  // And also ensure parent already has lang (or another xml:lang appears) => should throw.
  parent->options |= kXMP_PropHasLang;

  EXPECT_ANY_THROW(FixupQualifiedNode(parent));

  delete parent;
}

TEST_F(FixupQualifiedNodeTest_2123, ThrowsIfValueQualifierDuplicatesExistingChildNodeName_2123) {
  XMP_Node* valueNode = nullptr;
  XMP_Node* parent =
      MakeQualifiedParentWithValueNode(kXMP_PropValueIsStruct | kRDF_HasValueElem, &valueNode);
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(valueNode, nullptr);

  // Add a child (beyond rdf:value) whose name will match a qualifier on rdf:value.
  auto* dupChild = NewNodeWithValue(parent, "ex:dup", "childV", 0);
  AddChild(parent, dupChild);

  // Add a qualifier on rdf:value with the same name. The function checks for duplicates using
  // FindChildNode(xmpParent, currQual->name, kXMP_ExistingOnly) before moving qualifiers.
  auto* dupQual = NewNodeWithValue(valueNode, "ex:dup", "qualV", 0);
  AddQualifier(valueNode, dupQual);

  EXPECT_ANY_THROW(FixupQualifiedNode(parent));

  delete parent;
}

TEST_F(FixupQualifiedNodeTest_2123, PreservesExistingParentQualifiersAndAppendsNewOnes_2123) {
  XMP_Node* valueNode = nullptr;
  XMP_Node* parent =
      MakeQualifiedParentWithValueNode(kXMP_PropValueIsStruct | kRDF_HasValueElem, &valueNode);
  ASSERT_NE(parent, nullptr);
  ASSERT_NE(valueNode, nullptr);

  // Existing qualifier already on parent.
  auto* existing = NewNodeWithValue(parent, "ex:existing", "E", 0);
  AddQualifier(parent, existing);

  // rdf:value has a non-lang qualifier; should be moved and appended.
  auto* q1 = NewNodeWithValue(valueNode, "ex:q1", "Q1", 0);
  AddQualifier(valueNode, q1);

  // No children swap needed for this test; still give it one child so parent children changes.
  auto* vnChild = NewNodeWithValue(valueNode, "ex:c", "C", 0);
  AddChild(valueNode, vnChild);

  FixupQualifiedNode(parent);

  // Existing qualifier should still be present.
  bool foundExisting = false;
  bool foundQ1 = false;
  for (auto* q : parent->qualifiers) {
    if (!q) continue;
    if (q->name == "ex:existing") foundExisting = true;
    if (q->name == "ex:q1") foundQ1 = true;
  }
  EXPECT_TRUE(foundExisting);
  EXPECT_TRUE(foundQ1);

  delete parent;
}

}  // namespace