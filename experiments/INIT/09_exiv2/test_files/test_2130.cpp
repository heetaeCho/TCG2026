// =================================================================================================
// UNIT TESTS for RDF_PropertyElement (ParseRDF.cpp)
// TEST_ID: 2130
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

// Pull in the real SDK types/constants used by ParseRDF.cpp.
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// IMPORTANT:
// RDF_PropertyElement is a static function in ParseRDF.cpp. To test it as a black box without
// re-implementing internals, we compile the production .cpp directly into this test TU.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

class RDFPropertyElementTest_2130 : public ::testing::Test {
protected:
  // Own all XML nodes we create so pointers placed into attrs/content remain valid.
  std::vector<std::unique_ptr<XML_Node>> ownedXml_;

  XML_Node* NewXMLNode(XML_Node* parent, const std::string& name, XMP_Uns8 kind) {
    ownedXml_.push_back(std::make_unique<XML_Node>(parent, name, kind));
    return ownedXml_.back().get();
  }

  XML_Node* NewAttr(const std::string& name, const std::string& value) {
    XML_Node* a = NewXMLNode(/*parent*/ nullptr, name, kAttrNode);
    a->name = name;
    a->value = value;
    return a;
  }

  XML_Node* NewCData(const std::string& value) {
    XML_Node* c = NewXMLNode(/*parent*/ nullptr, "", kCDataNode);
    c->value = value;
    return c;
  }

  XML_Node* NewElem(const std::string& name) {
    XML_Node* e = NewXMLNode(/*parent*/ nullptr, name, kElemNode);
    e->name = name;
    return e;
  }
};

// --- Exceptional / error case ------------------------------------------------------------

TEST_F(RDFPropertyElementTest_2130, InvalidPropertyElementNameThrowsBadRDF_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "rdf:RDF", kElemNode); // commonly a non-property element
  xmlNode.name = "rdf:RDF";

  try {
    RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true);
    FAIL() << "Expected an exception for invalid property element name.";
  } catch (const XMP_Error& err) {
    EXPECT_EQ(err.GetID(), kXMPErr_BadRDF);
  } catch (...) {
    FAIL() << "Expected XMP_Error (kXMPErr_BadRDF).";
  }
}

// --- Normal / branching coverage ---------------------------------------------------------

TEST_F(RDFPropertyElementTest_2130, AttrCountGreaterThan3DoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  // >3 attrs triggers the empty-property-element path in RDF_PropertyElement.
  xmlNode.attrs.push_back(NewAttr("xml:lang", "en"));
  xmlNode.attrs.push_back(NewAttr("rdf:ID", "id1"));
  xmlNode.attrs.push_back(NewAttr("ex:a", "1"));
  xmlNode.attrs.push_back(NewAttr("ex:b", "2"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
  EXPECT_GT(xmpParent.children.size(), before);
}

TEST_F(RDFPropertyElementTest_2130, DatatypeAttributeDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  // Ensure the first non-(xml:lang,rdf:ID) attribute encountered is rdf:datatype.
  xmlNode.attrs.push_back(NewAttr("xml:lang", "en"));
  xmlNode.attrs.push_back(NewAttr("rdf:datatype", "http://www.w3.org/2001/XMLSchema#string"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
  EXPECT_GT(xmpParent.children.size(), before);
}

TEST_F(RDFPropertyElementTest_2130, ParseTypeLiteralDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  xmlNode.attrs.push_back(NewAttr("rdf:parseType", "Literal"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
  EXPECT_GT(xmpParent.children.size(), before);
}

TEST_F(RDFPropertyElementTest_2130, ParseTypeResourceDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  xmlNode.attrs.push_back(NewAttr("rdf:parseType", "Resource"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
  EXPECT_GT(xmpParent.children.size(), before);
}

TEST_F(RDFPropertyElementTest_2130, ParseTypeCollectionDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  xmlNode.attrs.push_back(NewAttr("rdf:parseType", "Collection"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
  EXPECT_GT(xmpParent.children.size(), before);
}

TEST_F(RDFPropertyElementTest_2130, ParseTypeOtherDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  xmlNode.attrs.push_back(NewAttr("rdf:parseType", "SomethingElse"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
  EXPECT_GT(xmpParent.children.size(), before);
}

// --- Boundary conditions: attribute scanning + content classification --------------------

TEST_F(RDFPropertyElementTest_2130, OnlyLangAndIDWithEmptyContentDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  // Only the special attrs; the function should treat as "no other attrs".
  xmlNode.attrs.push_back(NewAttr("xml:lang", "en"));
  xmlNode.attrs.push_back(NewAttr("rdf:ID", "id1"));

  // Empty content.
  ASSERT_TRUE(xmlNode.content.empty());

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
  EXPECT_GT(xmpParent.children.size(), before);
}

TEST_F(RDFPropertyElementTest_2130, OnlyCDataChildrenDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  // No attrs.
  ASSERT_TRUE(xmlNode.attrs.empty());

  // Content: all CData nodes (boundary: loop scans all children and reaches end).
  xmlNode.content.push_back(NewCData("hello"));
  xmlNode.content.push_back(NewCData("world"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
  EXPECT_GT(xmpParent.children.size(), before);
}

TEST_F(RDFPropertyElementTest_2130, MixedContentWithNonCDataChildDoesNotThrowAndAddsChild_2130) {
  XMP_Node xmpParent(/*parent*/ nullptr, "xmp:Parent", /*options*/ 0);

  XML_Node xmlNode(/*parent*/ nullptr, "ex:prop", kElemNode);
  xmlNode.name = "ex:prop";

  // No attrs.
  ASSERT_TRUE(xmlNode.attrs.empty());

  // Content: first CData, then an element node (boundary: breaks early on non-CData).
  xmlNode.content.push_back(NewCData("prefix"));
  xmlNode.content.push_back(NewElem("ex:child"));

  const size_t before = xmpParent.children.size();
  EXPECT_NO_THROW(RDF_PropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
  EXPECT_GT(xmpParent.children.size(), before);
}

} // namespace