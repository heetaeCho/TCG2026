// ============================================================================
// TEST_ID: 2134
// Unit tests for RDF_ParseTypeResourcePropertyElement (ParseRDF.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

// These are internal XMP SDK headers in exiv2/xmpsdk. Adjust include paths as needed
// for your build/test environment.
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"

// IMPORTANT:
// RDF_ParseTypeResourcePropertyElement is a file-static function in ParseRDF.cpp.
// A common way to test such functions is to include the .cpp into the test TU.
// Ensure your build does NOT also compile/link ParseRDF.cpp into this test binary,
// otherwise you may get duplicate symbol errors.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

// Helper to build an attribute XML_Node and append to xmlNode.attrs.
static void AddAttr(XML_Node& xmlNode, const std::string& name, const std::string& value) {
  // XML_NodePtr is defined by XMLParserAdapter.hpp (typically a shared_ptr).
  XML_NodePtr attr = std::make_shared<XML_Node>(XML_NodePtr(), name.c_str(), /*kind*/ 0);
  attr->name = name;
  attr->value = value;
  xmlNode.attrs.push_back(attr);
}

class RDF_ParseTypeResourcePropertyElementTest_2134 : public ::testing::Test {
 protected:
  RDF_ParseTypeResourcePropertyElementTest_2134()
      : xmpRoot_(nullptr, "root", /*options*/ 0),
        xmlProp_(XML_NodePtr(), "ex:prop", /*kind*/ 0) {}

  XMP_Node xmpRoot_;
  XML_Node xmlProp_;
};

TEST_F(RDF_ParseTypeResourcePropertyElementTest_2134, CreatesChildStructOnValidParseTypeResource_2134) {
  AddAttr(xmlProp_, "rdf:parseType", "Resource");

  ASSERT_NO_THROW(RDF_ParseTypeResourcePropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ true));

  ASSERT_EQ(xmpRoot_.children.size(), 1u);
  ASSERT_NE(xmpRoot_.children[0], nullptr);

  const XMP_Node* child = xmpRoot_.children[0];
  EXPECT_NE((child->options & kXMP_PropValueIsStruct), 0u);
}

TEST_F(RDF_ParseTypeResourcePropertyElementTest_2134, AddsXmlLangAsQualifier_2134) {
  AddAttr(xmlProp_, "rdf:parseType", "Resource");
  AddAttr(xmlProp_, "xml:lang", "en-US");

  ASSERT_NO_THROW(RDF_ParseTypeResourcePropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ false));

  ASSERT_EQ(xmpRoot_.children.size(), 1u);
  const XMP_Node* child = xmpRoot_.children[0];

  // Observable behavior: xml:lang should become a qualifier node.
  ASSERT_GE(child->qualifiers.size(), 1u);

  bool foundLang = false;
  for (const XMP_Node* q : child->qualifiers) {
    if (q == nullptr) continue;
    if (q->name == "xml:lang") {
      foundLang = true;
      EXPECT_EQ(q->value, "en-US");
      break;
    }
  }
  EXPECT_TRUE(foundLang);
}

TEST_F(RDF_ParseTypeResourcePropertyElementTest_2134, IgnoresRdfIDAttribute_2134) {
  AddAttr(xmlProp_, "rdf:parseType", "Resource");
  AddAttr(xmlProp_, "rdf:ID", "ignored-id");

  ASSERT_NO_THROW(RDF_ParseTypeResourcePropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ true));

  ASSERT_EQ(xmpRoot_.children.size(), 1u);
  const XMP_Node* child = xmpRoot_.children[0];

  // rdf:ID is ignored, so it should not appear as a qualifier.
  for (const XMP_Node* q : child->qualifiers) {
    ASSERT_NE(q, nullptr);
    EXPECT_NE(q->name, "rdf:ID");
  }
}

TEST_F(RDF_ParseTypeResourcePropertyElementTest_2134, SupportsCombinationOfAllowedAttributes_2134) {
  AddAttr(xmlProp_, "rdf:parseType", "Resource");
  AddAttr(xmlProp_, "xml:lang", "fr");
  AddAttr(xmlProp_, "rdf:ID", "ignore-me");

  ASSERT_NO_THROW(RDF_ParseTypeResourcePropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ false));

  ASSERT_EQ(xmpRoot_.children.size(), 1u);
  const XMP_Node* child = xmpRoot_.children[0];

  // Must still be a struct.
  EXPECT_NE((child->options & kXMP_PropValueIsStruct), 0u);

  // Must contain xml:lang qualifier; rdf:ID must not.
  bool foundLang = false;
  bool foundRdfId = false;
  for (const XMP_Node* q : child->qualifiers) {
    if (q == nullptr) continue;
    if (q->name == "xml:lang") foundLang = true;
    if (q->name == "rdf:ID") foundRdfId = true;
  }
  EXPECT_TRUE(foundLang);
  EXPECT_FALSE(foundRdfId);
}

TEST_F(RDF_ParseTypeResourcePropertyElementTest_2134, ThrowsOnInvalidAttributeName_2134) {
  AddAttr(xmlProp_, "rdf:parseType", "Resource");
  AddAttr(xmlProp_, "rdf:about", "not-allowed-here");  // invalid for parseType="Resource" property element

  EXPECT_ANY_THROW(RDF_ParseTypeResourcePropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ true));
}

TEST_F(RDF_ParseTypeResourcePropertyElementTest_2134, ThrowsOnUnknownAttribute_2134) {
  AddAttr(xmlProp_, "rdf:parseType", "Resource");
  AddAttr(xmlProp_, "ex:customAttr", "x");  // unknown/invalid

  EXPECT_ANY_THROW(RDF_ParseTypeResourcePropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ false));
}

TEST_F(RDF_ParseTypeResourcePropertyElementTest_2134, BoundaryNoAttributesStillCreatesStructChild_2134) {
  // Boundary: empty attribute list (even though real callers may enforce rdf:parseType="Resource").
  // Observable: function should still create a struct child before processing attributes.
  ASSERT_NO_THROW(RDF_ParseTypeResourcePropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ true));

  ASSERT_EQ(xmpRoot_.children.size(), 1u);
  const XMP_Node* child = xmpRoot_.children[0];
  ASSERT_NE(child, nullptr);
  EXPECT_NE((child->options & kXMP_PropValueIsStruct), 0u);
}

}  // namespace