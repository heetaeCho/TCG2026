// File: test_xmpmeta_sort_within_offspring_2145.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

// Bring in the SDK node types / option bits used by SortWithinOffspring.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// Include the implementation file to access the TU-local (static) function under test.
// NOTE: This is intentional so the test can call SortWithinOffspring directly.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp"

namespace {

// Simple arena to own raw XMP_Node pointers referenced by children/qualifiers vectors.
class NodeArena_2145 {
 public:
  XMP_Node* New(XMP_Node* parent,
               const std::string& name,
               const std::string& value,
               XMP_OptionBits options) {
    nodes_.push_back(std::make_unique<XMP_Node>(parent, name.c_str(), value.c_str(), options));
    return nodes_.back().get();
  }

  XMP_Node* New(XMP_Node* parent, const std::string& name, XMP_OptionBits options) {
    nodes_.push_back(std::make_unique<XMP_Node>(parent, name.c_str(), options));
    return nodes_.back().get();
  }

 private:
  std::vector<std::unique_ptr<XMP_Node>> nodes_;
};

class SortWithinOffspringTest_2145 : public ::testing::Test {
 protected:
  NodeArena_2145 arena_;
};

static std::vector<XMP_Node*> SnapshotPtrs_2145(const XMP_NodeOffspring& vec) {
  return std::vector<XMP_Node*>(vec.begin(), vec.end());
}

}  // namespace

TEST_F(SortWithinOffspringTest_2145, HandlesEmptyVector_2145) {
  XMP_NodeOffspring vec;
  EXPECT_NO_THROW(SortWithinOffspring(vec));
  EXPECT_TRUE(vec.empty());
}

TEST_F(SortWithinOffspringTest_2145, SortsQualifiersByNameAndRecurses_2145) {
  // Parent node with qualifiers out of order by name.
  XMP_Node* parent = arena_.New(nullptr, "p", /*options=*/0);
  XMP_Node* qB = arena_.New(parent, "bQual", /*options=*/kXMP_PropIsQualifier);
  XMP_Node* qA = arena_.New(parent, "aQual", /*options=*/kXMP_PropIsQualifier);

  // Give one qualifier nested qualifiers out of order (to test recursion).
  XMP_Node* qB_child2 = arena_.New(qB, "zInner", /*options=*/kXMP_PropIsQualifier);
  XMP_Node* qB_child1 = arena_.New(qB, "aInner", /*options=*/kXMP_PropIsQualifier);
  qB->qualifiers.push_back(qB_child2);
  qB->qualifiers.push_back(qB_child1);

  parent->qualifiers.push_back(qB);
  parent->qualifiers.push_back(qA);

  XMP_NodeOffspring top;
  top.push_back(parent);

  SortWithinOffspring(top);

  ASSERT_EQ(parent->qualifiers.size(), 2u);
  EXPECT_EQ(parent->qualifiers[0]->name, "aQual");
  EXPECT_EQ(parent->qualifiers[1]->name, "bQual");

  ASSERT_EQ(qB->qualifiers.size(), 2u);
  EXPECT_EQ(qB->qualifiers[0]->name, "aInner");
  EXPECT_EQ(qB->qualifiers[1]->name, "zInner");
}

TEST_F(SortWithinOffspringTest_2145, SortsStructChildrenByName_2145) {
  XMP_Node* parent = arena_.New(nullptr, "structParent", /*options=*/kXMP_PropValueIsStruct);

  XMP_Node* c2 = arena_.New(parent, "bChild", /*options=*/0);
  XMP_Node* c1 = arena_.New(parent, "aChild", /*options=*/0);
  parent->children.push_back(c2);
  parent->children.push_back(c1);

  XMP_NodeOffspring top;
  top.push_back(parent);

  SortWithinOffspring(top);

  ASSERT_EQ(parent->children.size(), 2u);
  EXPECT_EQ(parent->children[0]->name, "aChild");
  EXPECT_EQ(parent->children[1]->name, "bChild");
}

TEST_F(SortWithinOffspringTest_2145, SortsUnorderedArrayChildrenByValue_2145) {
  // Unordered array: uses stable_sort with CompareNodeValues.
  XMP_Node* arr = arena_.New(nullptr, "arr", /*options=*/kXMP_PropValueIsArray | kXMP_PropArrayIsUnordered);

  XMP_Node* v2 = arena_.New(arr, "item2", "2", /*options=*/0);
  XMP_Node* v1 = arena_.New(arr, "item1", "1", /*options=*/0);
  arr->children.push_back(v2);
  arr->children.push_back(v1);

  XMP_NodeOffspring top;
  top.push_back(arr);

  SortWithinOffspring(top);

  ASSERT_EQ(arr->children.size(), 2u);
  EXPECT_EQ(arr->children[0]->value, "1");
  EXPECT_EQ(arr->children[1]->value, "2");
}

TEST_F(SortWithinOffspringTest_2145, SortsAltTextArrayChildrenByLang_2145) {
  // AltText array: uses sort with CompareNodeLangs.
  XMP_Node* alt =
      arena_.New(nullptr, "alt", /*options=*/kXMP_PropValueIsArray | kXMP_PropArrayIsAltText);

  // Create two array items with xml:lang qualifiers.
  XMP_Node* itemFR = arena_.New(alt, "[]", "Bonjour", /*options=*/0);
  XMP_Node* itemEN = arena_.New(alt, "[]", "Hello", /*options=*/0);

  // The usual XMP convention is qualifier name "xml:lang".
  XMP_Node* qLangFR = arena_.New(itemFR, "xml:lang", "fr", /*options=*/kXMP_PropIsQualifier);
  XMP_Node* qLangEN = arena_.New(itemEN, "xml:lang", "en", /*options=*/kXMP_PropIsQualifier);
  itemFR->qualifiers.push_back(qLangFR);
  itemEN->qualifiers.push_back(qLangEN);

  alt->children.push_back(itemFR);
  alt->children.push_back(itemEN);

  XMP_NodeOffspring top;
  top.push_back(alt);

  SortWithinOffspring(top);

  ASSERT_EQ(alt->children.size(), 2u);
  // Expect "en" item to sort before "fr" item.
  EXPECT_EQ(alt->children[0]->value, "Hello");
  EXPECT_EQ(alt->children[1]->value, "Bonjour");
}

TEST_F(SortWithinOffspringTest_2145, IsIdempotentOnAlreadySortedTrees_2145) {
  XMP_Node* parent = arena_.New(nullptr, "p", /*options=*/kXMP_PropValueIsStruct);

  // Already sorted names.
  XMP_Node* a = arena_.New(parent, "a", /*options=*/0);
  XMP_Node* b = arena_.New(parent, "b", /*options=*/0);
  parent->children.push_back(a);
  parent->children.push_back(b);

  // Qualifiers already sorted.
  XMP_Node* q1 = arena_.New(parent, "aQual", /*options=*/kXMP_PropIsQualifier);
  XMP_Node* q2 = arena_.New(parent, "bQual", /*options=*/kXMP_PropIsQualifier);
  parent->qualifiers.push_back(q1);
  parent->qualifiers.push_back(q2);

  XMP_NodeOffspring top;
  top.push_back(parent);

  SortWithinOffspring(top);
  auto childrenAfter1 = SnapshotPtrs_2145(parent->children);
  auto qualsAfter1 = SnapshotPtrs_2145(parent->qualifiers);

  SortWithinOffspring(top);
  auto childrenAfter2 = SnapshotPtrs_2145(parent->children);
  auto qualsAfter2 = SnapshotPtrs_2145(parent->qualifiers);

  EXPECT_EQ(childrenAfter1, childrenAfter2);
  EXPECT_EQ(qualsAfter1, qualsAfter2);
}

TEST_F(SortWithinOffspringTest_2145, RecursesIntoNestedChildren_2145) {
  // Top-level node doesn't need special options to recurse into children,
  // but nested node is struct so its children are name-sorted.
  XMP_Node* topNode = arena_.New(nullptr, "top", /*options=*/0);

  XMP_Node* nestedStruct = arena_.New(topNode, "nested", /*options=*/kXMP_PropValueIsStruct);
  topNode->children.push_back(nestedStruct);

  XMP_Node* n2 = arena_.New(nestedStruct, "b", /*options=*/0);
  XMP_Node* n1 = arena_.New(nestedStruct, "a", /*options=*/0);
  nestedStruct->children.push_back(n2);
  nestedStruct->children.push_back(n1);

  XMP_NodeOffspring top;
  top.push_back(topNode);

  SortWithinOffspring(top);

  ASSERT_EQ(nestedStruct->children.size(), 2u);
  EXPECT_EQ(nestedStruct->children[0]->name, "a");
  EXPECT_EQ(nestedStruct->children[1]->name, "b");
}