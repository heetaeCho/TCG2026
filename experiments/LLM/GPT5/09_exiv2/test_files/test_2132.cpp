// =================================================================================================
// TEST_ID: 2132
// Unit tests for RDF_LiteralPropertyElement (ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

// Pull in the real types.
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"
#include "XMP_Const.h"

// Include the implementation file to access the TU-local static function under test.
// This is a common technique to test file-local (static) functions without altering production code.
#include "ParseRDF.cpp"

namespace {

// Helper: create XML_NodePtr regardless of whether XML_NodePtr is a raw pointer or a smart pointer.
template <typename... Args>
XML_NodePtr MakeXMLNode(Args&&... args) {
  if constexpr (std::is_pointer_v<XML_NodePtr>) {
    return new XML_Node(std::forward<Args>(args)...);
  } else {
    return std::make_shared<XML_Node>(std::forward<Args>(args)...);
  }
}

template <typename TPtr>
XML_Node* GetRawXML(TPtr& p) {
  if constexpr (std::is_pointer_v<TPtr>) {
    return p;
  } else {
    return p.get();
  }
}

template <typename TPtr>
const XML_Node* GetRawXML(const TPtr& p) {
  if constexpr (std::is_pointer_v<TPtr>) {
    return p;
  } else {
    return p.get();
  }
}

void DeleteIfRaw(XML_NodePtr p) {
  if constexpr (std::is_pointer_v<XML_NodePtr>) {
    delete p;
  } else {
    (void)p;
  }
}

// Helper RAII holder for XML nodes if XML_NodePtr is raw-pointer based.
struct XMLNodeArena {
  std::vector<XML_NodePtr> owned;
  ~XMLNodeArena() {
    for (auto& p : owned) DeleteIfRaw(p);
  }

  template <typename... Args>
  XML_NodePtr New(Args&&... args) {
    XML_NodePtr p = MakeXMLNode(std::forward<Args>(args)...);
    owned.push_back(p);
    return p;
  }
};

class RDFLiteralPropertyElementTest_2132 : public ::testing::Test {
 protected:
  // Prefer heap allocation for XMP_Node in case destructor manages offspring.
  std::unique_ptr<XMP_Node> xmpParent;

  void SetUp() override {
    xmpParent.reset(new XMP_Node(/*parent*/ nullptr, "parent", /*options*/ 0));
  }

  static XML_Node MakeElementNodeStack() {
    // xmlNode itself is passed by const reference; we can keep it on the stack.
    // Parent pointer for xml tree is not relevant to this function.
    return XML_Node(/*parent*/ nullptr, "ex:prop", kElemNode);
  }
};

}  // namespace

TEST_F(RDFLiteralPropertyElementTest_2132, ConcatenatesCDataChildrenIntoNewChildValue_2132) {
  XMLNodeArena arena;
  XML_Node xmlNode = MakeElementNodeStack();

  // Two CDATA children: "A" and "B"
  XML_NodePtr c1 = arena.New(/*parent*/ nullptr, "", kCDataNode);
  GetRawXML(c1)->value = "A";
  XML_NodePtr c2 = arena.New(/*parent*/ nullptr, "", kCDataNode);
  GetRawXML(c2)->value = "B";

  xmlNode.content.push_back(c1);
  xmlNode.content.push_back(c2);

  ASSERT_NO_THROW(RDF_LiteralPropertyElement(xmpParent.get(), xmlNode, /*isTopLevel*/ true));

  ASSERT_EQ(xmpParent->children.size(), 1u);
  ASSERT_NE(xmpParent->children[0], nullptr);
  EXPECT_EQ(xmpParent->children[0]->value, "AB");
}

TEST_F(RDFLiteralPropertyElementTest_2132, AcceptsXmlLangAsQualifier_2132) {
  XMLNodeArena arena;
  XML_Node xmlNode = MakeElementNodeStack();

  // xml:lang attribute
  XML_NodePtr langAttr = arena.New(/*parent*/ nullptr, "xml:lang", kAttrNode);
  GetRawXML(langAttr)->value = "en-US";
  xmlNode.attrs.push_back(langAttr);

  // One CDATA child
  XML_NodePtr c1 = arena.New(/*parent*/ nullptr, "", kCDataNode);
  GetRawXML(c1)->value = "Hello";
  xmlNode.content.push_back(c1);

  ASSERT_NO_THROW(RDF_LiteralPropertyElement(xmpParent.get(), xmlNode, /*isTopLevel*/ false));

  ASSERT_EQ(xmpParent->children.size(), 1u);
  XMP_Node* child = xmpParent->children[0];
  ASSERT_NE(child, nullptr);
  EXPECT_EQ(child->value, "Hello");

  // Observable external interaction: a qualifier should be added for xml:lang.
  ASSERT_GE(child->qualifiers.size(), 1u);

  bool found = false;
  for (auto* q : child->qualifiers) {
    ASSERT_NE(q, nullptr);
    if (q->name == "xml:lang") {
      found = true;
      EXPECT_EQ(q->value, "en-US");
    }
  }
  EXPECT_TRUE(found);
}

TEST_F(RDFLiteralPropertyElementTest_2132, IgnoresRdfIDAndRdfDatatypeAttributes_2132) {
  XMLNodeArena arena;
  XML_Node xmlNode = MakeElementNodeStack();

  XML_NodePtr idAttr = arena.New(/*parent*/ nullptr, "rdf:ID", kAttrNode);
  GetRawXML(idAttr)->value = "someId";
  XML_NodePtr dtAttr = arena.New(/*parent*/ nullptr, "rdf:datatype", kAttrNode);
  GetRawXML(dtAttr)->value = "http://www.w3.org/2001/XMLSchema#string";

  xmlNode.attrs.push_back(idAttr);
  xmlNode.attrs.push_back(dtAttr);

  XML_NodePtr c1 = arena.New(/*parent*/ nullptr, "", kCDataNode);
  GetRawXML(c1)->value = "v";
  xmlNode.content.push_back(c1);

  ASSERT_NO_THROW(RDF_LiteralPropertyElement(xmpParent.get(), xmlNode, /*isTopLevel*/ true));

  ASSERT_EQ(xmpParent->children.size(), 1u);
  EXPECT_EQ(xmpParent->children[0]->value, "v");
}

TEST_F(RDFLiteralPropertyElementTest_2132, ThrowsOnInvalidAttribute_2132) {
  XMLNodeArena arena;
  XML_Node xmlNode = MakeElementNodeStack();

  XML_NodePtr badAttr = arena.New(/*parent*/ nullptr, "not-allowed", kAttrNode);
  GetRawXML(badAttr)->value = "x";
  xmlNode.attrs.push_back(badAttr);

  XML_NodePtr c1 = arena.New(/*parent*/ nullptr, "", kCDataNode);
  GetRawXML(c1)->value = "text";
  xmlNode.content.push_back(c1);

  try {
    RDF_LiteralPropertyElement(xmpParent.get(), xmlNode, /*isTopLevel*/ true);
    FAIL() << "Expected an exception for invalid attribute";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(e.GetID(), kXMPErr_BadRDF);
  } catch (...) {
    FAIL() << "Expected XMP_Error";
  }
}

TEST_F(RDFLiteralPropertyElementTest_2132, ThrowsOnNonCDataChildNode_2132) {
  XMLNodeArena arena;
  XML_Node xmlNode = MakeElementNodeStack();

  // Child kind not kCDataNode
  XML_NodePtr elemChild = arena.New(/*parent*/ nullptr, "ex:child", kElemNode);
  xmlNode.content.push_back(elemChild);

  try {
    RDF_LiteralPropertyElement(xmpParent.get(), xmlNode, /*isTopLevel*/ false);
    FAIL() << "Expected an exception for invalid child node kind";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(e.GetID(), kXMPErr_BadRDF);
  } catch (...) {
    FAIL() << "Expected XMP_Error";
  }
}

TEST_F(RDFLiteralPropertyElementTest_2132, AllowsEmptyContentProducesEmptyValue_2132) {
  XML_Node xmlNode = MakeElementNodeStack();
  ASSERT_TRUE(xmlNode.content.empty());

  ASSERT_NO_THROW(RDF_LiteralPropertyElement(xmpParent.get(), xmlNode, /*isTopLevel*/ true));

  ASSERT_EQ(xmpParent->children.size(), 1u);
  ASSERT_NE(xmpParent->children[0], nullptr);
  EXPECT_TRUE(xmpParent->children[0]->value.empty());
}

TEST_F(RDFLiteralPropertyElementTest_2132, ConcatenatesManyCDataNodesInOrder_2132) {
  XMLNodeArena arena;
  XML_Node xmlNode = MakeElementNodeStack();

  std::string expected;
  for (int i = 0; i < 50; ++i) {
    XML_NodePtr c = arena.New(/*parent*/ nullptr, "", kCDataNode);
    const std::string chunk = "x" + std::to_string(i) + ";";
    GetRawXML(c)->value = chunk;
    expected += chunk;
    xmlNode.content.push_back(c);
  }

  ASSERT_NO_THROW(RDF_LiteralPropertyElement(xmpParent.get(), xmlNode, /*isTopLevel*/ false));

  ASSERT_EQ(xmpParent->children.size(), 1u);
  ASSERT_NE(xmpParent->children[0], nullptr);
  EXPECT_EQ(xmpParent->children[0]->value, expected);
}