// =================================================================================================
// TEST_ID: 2120
// Unit tests for AddChildNode (ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"

// Include the .cpp to access the internal static function AddChildNode.
// This is a common unit-testing technique for file-local functions.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

// --- Helper: extract XMP error ID in a way that works with multiple XMP_Error shapes.

template <typename T, typename = void>
struct HasGetID : std::false_type {};
template <typename T>
struct HasGetID<T, std::void_t<decltype(std::declval<const T&>().GetID())>> : std::true_type {};

template <typename T, typename = void>
struct HasIdMember : std::false_type {};
template <typename T>
struct HasIdMember<T, std::void_t<decltype(std::declval<const T&>().id)>> : std::true_type {};

static XMP_Int32 GetXmpErrorId(const XMP_Error& err) {
  if constexpr (HasGetID<XMP_Error>::value) {
    return static_cast<XMP_Int32>(err.GetID());
  } else if constexpr (HasIdMember<XMP_Error>::value) {
    return static_cast<XMP_Int32>(err.id);
  } else {
    // If the SDK shape changes, we still keep the tests compiling.
    return static_cast<XMP_Int32>(kXMPErr_Unknown);
  }
}

static XML_Node MakeElemNode(const std::string& nsURI, const std::string& qname) {
  XML_Node node(/*_parent*/ nullptr, qname, /*_kind*/ 0);
  node.ns = nsURI;
  node.name = qname;
  return node;
}

class AddChildNodeTest_2120 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure the global alias map doesn't dangle if a test changes it.
    // (Most tests avoid the top-level path that touches this.)
  }
};

}  // namespace

TEST_F(AddChildNodeTest_2120, ThrowsBadRDFWhenXmlNamespaceMissing_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "root", /*_options*/ 0);
  XML_Node xmlNode(/*_parent*/ nullptr, "dc:title", /*_kind*/ 0);
  xmlNode.ns.clear();  // Missing namespace must be rejected.

  try {
    (void)AddChildNode(&parent, xmlNode, "v", /*isTopLevel*/ false);
    FAIL() << "Expected XMP_Error to be thrown";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(kXMPErr_BadRDF, GetXmpErrorId(e));
  }
}

TEST_F(AddChildNodeTest_2120, AddsNormalChildToParentAndPreservesNameValue_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "root", /*_options*/ 0);
  XML_Node xmlNode = MakeElemNode("http://purl.org/dc/elements/1.1/", "dc:title");

  XMP_Node* child = nullptr;
  ASSERT_NO_THROW(child = AddChildNode(&parent, xmlNode, "Hello", /*isTopLevel*/ false));
  ASSERT_NE(child, nullptr);

  EXPECT_EQ(child->parent, &parent);
  EXPECT_EQ(child->name, "dc:title");
  EXPECT_EQ(child->value, "Hello");
  ASSERT_EQ(parent.children.size(), 1u);
  EXPECT_EQ(parent.children[0], child);
}

TEST_F(AddChildNodeTest_2120, ThrowsBadXMPOnDuplicateNonSpecialChildName_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "root", /*_options*/ 0);

  // Pre-seed an existing child with the same name.
  XMP_Node* existing = new XMP_Node(&parent, "dc:title", "old", /*_options*/ 0);
  parent.children.push_back(existing);

  XML_Node xmlNode = MakeElemNode("http://purl.org/dc/elements/1.1/", "dc:title");

  try {
    (void)AddChildNode(&parent, xmlNode, "new", /*isTopLevel*/ false);
    FAIL() << "Expected XMP_Error to be thrown for duplicate property";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(kXMPErr_BadXMP, GetXmpErrorId(e));
  }
}

TEST_F(AddChildNodeTest_2120, AllowsMultipleRdfLiArrayItemsAndRenamesToArrayItemName_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "arr", /*_options*/ kXMP_PropValueIsArray);
  XML_Node liNode = MakeElemNode("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf:li");

  XMP_Node* item1 = nullptr;
  XMP_Node* item2 = nullptr;

  ASSERT_NO_THROW(item1 = AddChildNode(&parent, liNode, "one", /*isTopLevel*/ false));
  ASSERT_NO_THROW(item2 = AddChildNode(&parent, liNode, "two", /*isTopLevel*/ false));

  ASSERT_NE(item1, nullptr);
  ASSERT_NE(item2, nullptr);
  ASSERT_EQ(parent.children.size(), 2u);

  // Observable behavior: rdf:li nodes are renamed to the array item name constant.
  EXPECT_EQ(item1->name, kXMP_ArrayItemName);
  EXPECT_EQ(item2->name, kXMP_ArrayItemName);
  EXPECT_EQ(item1->value, "one");
  EXPECT_EQ(item2->value, "two");
}

TEST_F(AddChildNodeTest_2120, ThrowsBadRDFWhenRdfLiIsMisplacedOnNonArrayParent_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "notArray", /*_options*/ 0);
  XML_Node liNode = MakeElemNode("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf:li");

  try {
    (void)AddChildNode(&parent, liNode, "x", /*isTopLevel*/ false);
    FAIL() << "Expected XMP_Error to be thrown for misplaced rdf:li";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(kXMPErr_BadRDF, GetXmpErrorId(e));
  }
}

TEST_F(AddChildNodeTest_2120, ThrowsBadRDFWhenRdfValueUsedOnNonStructParent_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "notStruct", /*_options*/ 0);
  XML_Node valueNode = MakeElemNode("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf:value");

  try {
    (void)AddChildNode(&parent, valueNode, "v", /*isTopLevel*/ false);
    FAIL() << "Expected XMP_Error to be thrown for misplaced rdf:value";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(kXMPErr_BadRDF, GetXmpErrorId(e));
  }
}

TEST_F(AddChildNodeTest_2120, InsertsRdfValueBeforeOtherChildrenWhenParentHasChildren_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "struct", /*_options*/ kXMP_PropValueIsStruct);

  // Add a pre-existing child so rdf:value should be inserted at the front.
  XML_Node otherNode = MakeElemNode("http://purl.org/dc/elements/1.1/", "dc:creator");
  XMP_Node* otherChild = nullptr;
  ASSERT_NO_THROW(otherChild = AddChildNode(&parent, otherNode, "Someone", /*isTopLevel*/ false));
  ASSERT_NE(otherChild, nullptr);
  ASSERT_EQ(parent.children.size(), 1u);

  XML_Node valueNode = MakeElemNode("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf:value");
  XMP_Node* valueChild = nullptr;
  ASSERT_NO_THROW(valueChild = AddChildNode(&parent, valueNode, "Primary", /*isTopLevel*/ false));
  ASSERT_NE(valueChild, nullptr);

  ASSERT_EQ(parent.children.size(), 2u);
  EXPECT_EQ(parent.children[0], valueChild);   // Inserted at beginning.
  EXPECT_EQ(parent.children[1], otherChild);   // Existing child shifted right.
  EXPECT_EQ(valueChild->name, "rdf:value");
  EXPECT_EQ(valueChild->value, "Primary");

  // Observable effect: rdf:value should mark the parent with kRDF_HasValueElem.
  EXPECT_NE(0u, (parent.options & kRDF_HasValueElem));
}

TEST_F(AddChildNodeTest_2120, AddsRdfValueAsOnlyChildWhenParentHasNoChildren_2120) {
  XMP_Node parent(/*_parent*/ nullptr, "struct", /*_options*/ kXMP_PropValueIsStruct);
  XML_Node valueNode = MakeElemNode("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf:value");

  XMP_Node* valueChild = nullptr;
  ASSERT_NO_THROW(valueChild = AddChildNode(&parent, valueNode, "Only", /*isTopLevel*/ false));
  ASSERT_NE(valueChild, nullptr);

  ASSERT_EQ(parent.children.size(), 1u);
  EXPECT_EQ(parent.children[0], valueChild);
  EXPECT_EQ(valueChild->name, "rdf:value");
  EXPECT_EQ(valueChild->value, "Only");
  EXPECT_NE(0u, (parent.options & kRDF_HasValueElem));
}