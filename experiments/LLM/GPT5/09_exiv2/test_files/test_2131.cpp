// =================================================================================================
// UNIT TESTS for RDF_ResourcePropertyElement (ParseRDF.cpp)
// TEST_ID = 2131
//
// Notes:
// - The function under test has internal linkage (static) in ParseRDF.cpp.
// - These tests include the .cpp directly to access the symbol in this TU.
// - Tests treat implementation as a black box and assert only observable effects:
//   * thrown XMP_Error IDs
//   * changes visible via public XMP_Node fields (children/qualifiers/options)
//
// =================================================================================================

#include <gtest/gtest.h>

#include <functional>
#include <memory>
#include <string>

// Exiv2/XMP SDK headers (as provided / typical for this codebase)
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"

// Include the implementation TU to access the static function under test.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

// Small helper to assert XMP_Error with a specific ID.
void ExpectXMPErrorId(const std::function<void()>& fn, XMP_Int32 expectedId) {
  try {
    fn();
    FAIL() << "Expected XMP_Error exception";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(e.GetID(), expectedId);
  } catch (...) {
    FAIL() << "Expected XMP_Error, but caught a different exception type";
  }
}

// Helpers to build XML nodes.
// NOTE: We only set fields that are observable/required by the interface usage here.
static XML_NodePtr MakeXMLNode(XML_NodePtr parent, const std::string& name, XMP_Uns8 kind) {
  return std::make_shared<XML_Node>(parent, name, kind);
}

static void AddAttr(XML_Node& elem, const std::string& name, const std::string& value) {
  XML_NodePtr attr = MakeXMLNode(elem.parent, name, kAttrNode);
  attr->name = name;
  attr->value = value;
  elem.attrs.push_back(attr);
}

static void AddWhitespace(XML_Node& elem, const std::string& ws = " \n\t") {
  XML_NodePtr wsNode = MakeXMLNode(elem.parent, "", kCDataNode);
  wsNode->value = ws;
  elem.content.push_back(wsNode);
}

static XML_NodePtr AddChildElem(XML_Node& parent, const std::string& name, const std::string& ns = "") {
  XML_NodePtr child = MakeXMLNode(parent.parent, name, kElemNode);
  child->name = name;
  child->ns = ns;
  parent.content.push_back(child);
  return child;
}

// Find a qualifier by name on an XMP_Node.
static const XMP_Node* FindQualifier(const XMP_Node& node, const std::string& qName) {
  for (const auto* q : node.qualifiers) {
    if (q && q->name == qName) return q;
  }
  return nullptr;
}

class RDF_ResourcePropertyElementTest_2131 : public ::testing::Test {
 protected:
  // A root XMP node to attach parsed results.
  XMP_Node xmpRoot_{nullptr, "xmp:Root", (XMP_OptionBits)0};
};

TEST_F(RDF_ResourcePropertyElementTest_2131, TopLevelChangesNodeIsIgnored_2131) {
  XML_Node xml(nullptr, "iX:changes", kElemNode);
  xml.name = "iX:changes";

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ true);

  EXPECT_EQ(xmpRoot_.children.size(), beforeChildren) << "Top-level iX:changes must be ignored";
}

TEST_F(RDF_ResourcePropertyElementTest_2131, AddsChildAndLangQualifierWhenXmlLangPresent_2131) {
  XML_Node xml(nullptr, "dc:title", kElemNode);
  xml.name = "dc:title";

  AddAttr(xml, "xml:lang", "en-US");
  // Minimal valid child: rdf:Description
  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Description", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false);

  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1u);
  XMP_Node* newCompound = xmpRoot_.children.back();
  ASSERT_NE(newCompound, nullptr);

  // Observable: a qualifier should have been added for xml:lang.
  // We don't assume qualifier node structure beyond presence of "xml:lang" name.
  EXPECT_NE(FindQualifier(*newCompound, "xml:lang"), nullptr);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, IgnoresRdfIdAttribute_2131) {
  XML_Node xml(nullptr, "dc:creator", kElemNode);
  xml.name = "dc:creator";

  AddAttr(xml, "rdf:ID", "someId");  // must be ignored
  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Description", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false);

  EXPECT_EQ(xmpRoot_.children.size(), beforeChildren + 1u);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, ThrowsOnInvalidAttribute_2131) {
  XML_Node xml(nullptr, "dc:subject", kElemNode);
  xml.name = "dc:subject";

  AddAttr(xml, "foo:bar", "nope");  // invalid here
  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Description", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  ExpectXMPErrorId([&]() { RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false); },
                   kXMPErr_BadRDF);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, ThrowsWhenMissingChildElement_2131) {
  XML_Node xml(nullptr, "dc:subject", kElemNode);
  xml.name = "dc:subject";
  // Only whitespace children -> should be treated as missing child
  AddWhitespace(xml);
  AddWhitespace(xml, "  ");

  ExpectXMPErrorId([&]() { RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false); },
                   kXMPErr_BadRDF);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, ThrowsWhenFirstNonWhitespaceChildIsNotElement_2131) {
  XML_Node xml(nullptr, "dc:subject", kElemNode);
  xml.name = "dc:subject";

  AddWhitespace(xml);
  // Non-whitespace, non-element node (CDATA with actual content)
  XML_NodePtr cdata = MakeXMLNode(xml.parent, "", kCDataNode);
  cdata->value = "not-whitespace";
  xml.content.push_back(cdata);

  ExpectXMPErrorId([&]() { RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false); },
                   kXMPErr_BadRDF);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, SetsArrayOptionsForRdfBag_2131) {
  XML_Node xml(nullptr, "dc:subject", kElemNode);
  xml.name = "dc:subject";

  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Bag", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false);

  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1u);
  XMP_Node* newCompound = xmpRoot_.children.back();
  ASSERT_NE(newCompound, nullptr);

  EXPECT_NE((newCompound->options & kXMP_PropValueIsArray), 0u);
  EXPECT_EQ((newCompound->options & kXMP_PropArrayIsOrdered), 0u);
  EXPECT_EQ((newCompound->options & kXMP_PropArrayIsAlternate), 0u);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, SetsArrayOptionsForRdfSeq_2131) {
  XML_Node xml(nullptr, "dc:subject", kElemNode);
  xml.name = "dc:subject";

  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Seq", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false);

  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1u);
  XMP_Node* newCompound = xmpRoot_.children.back();
  ASSERT_NE(newCompound, nullptr);

  EXPECT_NE((newCompound->options & kXMP_PropValueIsArray), 0u);
  EXPECT_NE((newCompound->options & kXMP_PropArrayIsOrdered), 0u);
  EXPECT_EQ((newCompound->options & kXMP_PropArrayIsAlternate), 0u);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, SetsArrayOptionsForRdfAlt_2131) {
  XML_Node xml(nullptr, "dc:title", kElemNode);
  xml.name = "dc:title";

  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Alt", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false);

  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1u);
  XMP_Node* newCompound = xmpRoot_.children.back();
  ASSERT_NE(newCompound, nullptr);

  EXPECT_NE((newCompound->options & kXMP_PropValueIsArray), 0u);
  EXPECT_NE((newCompound->options & kXMP_PropArrayIsOrdered), 0u);
  EXPECT_NE((newCompound->options & kXMP_PropArrayIsAlternate), 0u);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, SetsStructOptionForNonArrayChild_2131) {
  XML_Node xml(nullptr, "dc:creator", kElemNode);
  xml.name = "dc:creator";

  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Description", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false);

  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1u);
  XMP_Node* newCompound = xmpRoot_.children.back();
  ASSERT_NE(newCompound, nullptr);

  EXPECT_NE((newCompound->options & kXMP_PropValueIsStruct), 0u);
  EXPECT_EQ((newCompound->options & kXMP_PropValueIsArray), 0u);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, AddsRdfTypeQualifierForNonDescriptionChildWithNamespace_2131) {
  XML_Node xml(nullptr, "ex:prop", kElemNode);
  xml.name = "ex:prop";

  AddWhitespace(xml);
  // Child element that is not rdf:Description triggers rdf:type qualifier addition.
  XML_NodePtr child = AddChildElem(xml, "ex:Thing", "http://example.com/ns/");
  (void)child;

  const size_t beforeChildren = xmpRoot_.children.size();
  RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false);

  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1u);
  XMP_Node* newCompound = xmpRoot_.children.back();
  ASSERT_NE(newCompound, nullptr);

  // Observable: rdf:type qualifier exists.
  EXPECT_NE(FindQualifier(*newCompound, "rdf:type"), nullptr);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, ThrowsBadXMPWhenNonDescriptionChildHasNoColonInName_2131) {
  XML_Node xml(nullptr, "ex:prop", kElemNode);
  xml.name = "ex:prop";

  AddWhitespace(xml);
  // Name without ':' should trigger "All XML elements must be in a namespace" -> kXMPErr_BadXMP
  AddChildElem(xml, "NoPrefixName", "http://example.com/ns/");

  ExpectXMPErrorId([&]() { RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false); },
                   kXMPErr_BadXMP);
}

TEST_F(RDF_ResourcePropertyElementTest_2131, ThrowsWhenNonWhitespaceAppearsAfterPrimaryChild_2131) {
  XML_Node xml(nullptr, "dc:subject", kElemNode);
  xml.name = "dc:subject";

  AddWhitespace(xml);
  AddChildElem(xml, "rdf:Bag", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  // Trailing non-whitespace content after the primary child must trigger error.
  XML_NodePtr trailing = MakeXMLNode(xml.parent, "", kCDataNode);
  trailing->value = "not-whitespace";
  xml.content.push_back(trailing);

  ExpectXMPErrorId([&]() { RDF_ResourcePropertyElement(&xmpRoot_, xml, /*isTopLevel*/ false); },
                   kXMPErr_BadRDF);
}

}  // namespace