// =================================================================================================
// TEST_ID: 2104
// Unit tests for internal helper: EstimateRDFSize (XMPMeta-Serialize.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

// Pull in the core types used by the function under test.
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"

// NOTE:
// EstimateRDFSize is a `static` function in XMPMeta-Serialize.cpp (internal linkage).
// To test it as provided (without re-implementing), we include the translation unit here.
// This keeps the test black-box with respect to logic, while making the symbol available.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

class EstimateRDFSizeTest_2104 : public ::testing::Test {
 protected:
  // Own nodes so we can safely wire raw pointers into children/qualifiers.
  std::vector<std::unique_ptr<XMP_Node>> owned_;

  XMP_Node* MakeNode(XMP_Node* parent,
                    const std::string& name,
                    const std::string& value,
                    XMP_OptionBits options) {
    owned_.push_back(std::make_unique<XMP_Node>(parent, name, value, options));
    return owned_.back().get();
  }

  XMP_Node* MakeNode(XMP_Node* parent, const std::string& name, XMP_OptionBits options) {
    owned_.push_back(std::make_unique<XMP_Node>(parent, name, options));
    return owned_.back().get();
  }
};

TEST_F(EstimateRDFSizeTest_2104, LeafValueLengthIncreaseIncreasesOrKeepsSize_2104) {
  XMP_Node* n1 = MakeNode(nullptr, "ns:prop", "a", 0);
  XMP_Node* n2 = MakeNode(nullptr, "ns:prop", "aaaaaaaaaa", 0);

  const size_t s1 = EstimateRDFSize(n1, /*indent*/ 0, /*indentLen*/ 2);
  const size_t s2 = EstimateRDFSize(n2, /*indent*/ 0, /*indentLen*/ 2);

  EXPECT_GE(s2, s1);
  EXPECT_GT(s1, 0u);
  EXPECT_GT(s2, 0u);
}

TEST_F(EstimateRDFSizeTest_2104, AddingChildIncreasesSize_2104) {
  XMP_Node* parent = MakeNode(nullptr, "ns:parent", "v", 0);
  const size_t base = EstimateRDFSize(parent, 0, 2);

  XMP_Node* child = MakeNode(parent, "ns:child", "cv", 0);
  parent->children.push_back(child);

  const size_t withChild = EstimateRDFSize(parent, 0, 2);
  EXPECT_GT(withChild, base);
}

TEST_F(EstimateRDFSizeTest_2104, AddingQualifierIncreasesSize_2104) {
  XMP_Node* node = MakeNode(nullptr, "ns:prop", "v", 0);
  const size_t base = EstimateRDFSize(node, 1, 2);

  XMP_Node* qual = MakeNode(node, "xml:lang", "en-US", kXMP_PropIsQualifier);
  node->qualifiers.push_back(qual);

  const size_t withQual = EstimateRDFSize(node, 1, 2);
  EXPECT_GT(withQual, base);
}

TEST_F(EstimateRDFSizeTest_2104, NestedQualifiersAreCountedRecursively_2104) {
  XMP_Node* node = MakeNode(nullptr, "ns:prop", "v", 0);
  XMP_Node* qual = MakeNode(node, "q:name", "qv", kXMP_PropIsQualifier);
  node->qualifiers.push_back(qual);

  const size_t oneLevel = EstimateRDFSize(node, 0, 2);

  // Add a qualifier to the qualifier.
  XMP_Node* qual2 = MakeNode(qual, "q2:name", "q2v", kXMP_PropIsQualifier);
  qual->qualifiers.push_back(qual2);

  const size_t twoLevel = EstimateRDFSize(node, 0, 2);
  EXPECT_GT(twoLevel, oneLevel);
}

TEST_F(EstimateRDFSizeTest_2104, ArrayChildrenCountAffectsSize_2104) {
  XMP_Node* arr = MakeNode(nullptr, "ns:arr", /*value*/ "", kXMP_PropValueIsArray);
  const size_t base = EstimateRDFSize(arr, 0, 2);

  XMP_Node* li1 = MakeNode(arr, "rdf:li", "v1", 0);
  arr->children.push_back(li1);
  const size_t one = EstimateRDFSize(arr, 0, 2);

  XMP_Node* li2 = MakeNode(arr, "rdf:li", "v2", 0);
  arr->children.push_back(li2);
  const size_t two = EstimateRDFSize(arr, 0, 2);

  EXPECT_GE(one, base);
  EXPECT_GT(two, one);
}

TEST_F(EstimateRDFSizeTest_2104, StructWithChildIncreasesSize_2104) {
  XMP_Node* st = MakeNode(nullptr, "ns:struct", /*value*/ "", kXMP_PropValueIsStruct);
  const size_t base = EstimateRDFSize(st, 0, 2);

  XMP_Node* field = MakeNode(st, "ns:field", "fv", 0);
  st->children.push_back(field);

  const size_t withChild = EstimateRDFSize(st, 0, 2);
  EXPECT_GT(withChild, base);
}

TEST_F(EstimateRDFSizeTest_2104, IndentationParametersAffectOrPreserveNonDecreasingSize_2104) {
  XMP_Node* node = MakeNode(nullptr, "ns:prop", "value", 0);

  const size_t sIndent0 = EstimateRDFSize(node, /*indent*/ 0, /*indentLen*/ 2);
  const size_t sIndent3 = EstimateRDFSize(node, /*indent*/ 3, /*indentLen*/ 2);

  // Without assuming exact formatting rules, higher indentation should not make the estimate smaller.
  EXPECT_GE(sIndent3, sIndent0);

  const size_t sLen0 = EstimateRDFSize(node, /*indent*/ 3, /*indentLen*/ 0);
  const size_t sLen4 = EstimateRDFSize(node, /*indent*/ 3, /*indentLen*/ 4);
  EXPECT_GE(sLen4, sLen0);
}

TEST_F(EstimateRDFSizeTest_2104, HandlesEmptyNameAndValue_2104) {
  XMP_Node* node = MakeNode(nullptr, "", "", 0);

  const size_t s = EstimateRDFSize(node, /*indent*/ 0, /*indentLen*/ 0);
  EXPECT_GT(s, 0u);

  // Also verify it remains well-defined with non-zero indent/indentLen.
  const size_t s2 = EstimateRDFSize(node, /*indent*/ 2, /*indentLen*/ 3);
  EXPECT_GT(s2, 0u);
  EXPECT_GE(s2, s);
}

}  // namespace