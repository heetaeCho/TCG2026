// =================================================================================================
// TEST_ID: 2093
// Unit tests for ExpatAdapter StartElement handling via public ParseBuffer behavior.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// These headers are part of the XMP SDK sources inside Exiv2's xmpsdk.
#include "XMLParserAdapter.hpp"
#include "ExpatAdapter.hpp"

// If your build needs different include paths, adjust accordingly, e.g.:
// #include "xmpsdk/src/XMLParserAdapter.hpp"
// #include "xmpsdk/src/ExpatAdapter.hpp"

namespace {

static XML_Node* FirstChild(XML_Node& node) {
  if (node.content.empty()) return nullptr;
  return node.content[0];
}

static XML_Node* NthChild(XML_Node& node, size_t i) {
  if (i >= node.content.size()) return nullptr;
  return node.content[i];
}

static XML_Node* FindAttr(XML_Node* elem, const char* attrName) {
  if (elem == nullptr) return nullptr;
  for (auto* a : elem->attrs) {
    if (a != nullptr && a->name == attrName) return a;
  }
  return nullptr;
}

class ExpatAdapterTest_2093 : public ::testing::Test {
 protected:
  ExpatAdapter adapter;
};

}  // namespace

TEST_F(ExpatAdapterTest_2093, ParseSimpleElementNoAttrs_2093) {
  const std::string xml = "<root/>";

  ASSERT_NO_THROW(adapter.ParseBuffer(xml.data(), xml.size(), /*last=*/true));

  // The root "tree" node should have exactly one element child named "root".
  ASSERT_EQ(adapter.tree.kind, kRootNode);
  ASSERT_EQ(adapter.tree.content.size(), 1u);

  XML_Node* rootElem = FirstChild(adapter.tree);
  ASSERT_NE(rootElem, nullptr);
  EXPECT_EQ(rootElem->kind, kElemNode);
  EXPECT_EQ(rootElem->name, "root");
  EXPECT_TRUE(rootElem->attrs.empty());
}

TEST_F(ExpatAdapterTest_2093, ParseElementWithMultipleAttributes_2093) {
  const std::string xml = "<root a='1' b=\"two\"/>";

  ASSERT_NO_THROW(adapter.ParseBuffer(xml.data(), xml.size(), /*last=*/true));

  XML_Node* rootElem = FirstChild(adapter.tree);
  ASSERT_NE(rootElem, nullptr);
  ASSERT_EQ(rootElem->name, "root");

  // Attributes should be present as name/value pairs.
  ASSERT_EQ(rootElem->attrs.size(), 2u);

  XML_Node* a = FindAttr(rootElem, "a");
  XML_Node* b = FindAttr(rootElem, "b");
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_EQ(a->kind, kAttrNode);
  EXPECT_EQ(b->kind, kAttrNode);
  EXPECT_EQ(a->value, "1");
  EXPECT_EQ(b->value, "two");
}

TEST_F(ExpatAdapterTest_2093, ParseNestedElementsPreservesChildOrder_2093) {
  const std::string xml = "<root><child/><child2/></root>";

  ASSERT_NO_THROW(adapter.ParseBuffer(xml.data(), xml.size(), /*last=*/true));

  XML_Node* rootElem = FirstChild(adapter.tree);
  ASSERT_NE(rootElem, nullptr);
  ASSERT_EQ(rootElem->name, "root");

  ASSERT_EQ(rootElem->content.size(), 2u);

  XML_Node* child1 = NthChild(*rootElem, 0);
  XML_Node* child2 = NthChild(*rootElem, 1);
  ASSERT_NE(child1, nullptr);
  ASSERT_NE(child2, nullptr);

  EXPECT_EQ(child1->kind, kElemNode);
  EXPECT_EQ(child2->kind, kElemNode);
  EXPECT_EQ(child1->name, "child");
  EXPECT_EQ(child2->name, "child2");
}

TEST_F(ExpatAdapterTest_2093, ParsingRdfRdfSetsRootNodeAndIncrementsRootCount_2093) {
  // The StartElement handler checks for elemNode->name == "rdf:RDF".
  const std::string xml =
      "<wrapper>"
      "  <rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'/>"
      "</wrapper>";

  ASSERT_NO_THROW(adapter.ParseBuffer(xml.data(), xml.size(), /*last=*/true));

  EXPECT_EQ(adapter.rootCount, 1u);
  ASSERT_NE(adapter.rootNode, nullptr);
  EXPECT_EQ(adapter.rootNode->name, "rdf:RDF");

  // Also verify the rdf:RDF node is actually present in the parsed tree.
  XML_Node* wrapper = FirstChild(adapter.tree);
  ASSERT_NE(wrapper, nullptr);
  ASSERT_EQ(wrapper->name, "wrapper");
  ASSERT_FALSE(wrapper->content.empty());
  EXPECT_EQ(wrapper->content[0], adapter.rootNode);
}

TEST_F(ExpatAdapterTest_2093, MalformedXmlCausesObservableFailure_2093) {
  // We don't assume a specific exception type; only that parsing fails observably.
  const std::string badXml = "<root><unclosed></root>";
  EXPECT_ANY_THROW(adapter.ParseBuffer(badXml.data(), badXml.size(), /*last=*/true));
}