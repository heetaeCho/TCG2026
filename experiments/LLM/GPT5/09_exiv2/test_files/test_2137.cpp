// =================================================================================================
// UNIT TESTS for RDF_EmptyPropertyElement (ParseRDF.cpp)
// TEST_ID: 2137
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

// Pull in the real implementation (static function) into this translation unit.
// This is intentional so we can call RDF_EmptyPropertyElement without changing production code.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// Some builds define XML_NodePtr / XML_NodeVector in XMLParserAdapter.hpp.
// If your build uses different aliases, adjust the helper types below accordingly.
namespace {

static XML_NodePtr MakeXMLAttr(XML_NodePtr parent, const char* name, const char* value) {
  // The kind value is not relied on by these tests; we only need name/value to be observed
  // via the public interface and used by the production code.
  XML_NodePtr attr = new XML_Node(parent, name, /*kind*/ 0);
  attr->name = name;
  attr->value = value ? value : "";
  return attr;
}

static XML_NodePtr MakeXMLElement(XML_NodePtr parent, const char* name) {
  XML_NodePtr elem = new XML_Node(parent, name, /*kind*/ 0);
  elem->name = name;
  return elem;
}

static void DeleteXMLTreeShallow(XML_Node& node) {
  // The XML_Node destructor may or may not own children in this codebase.
  // These tests allocate nodes for attrs/content; to avoid leaks we delete
  // only what we allocated explicitly.
  for (auto* a : node.attrs) delete a;
  node.attrs.clear();
  for (auto* c : node.content) delete c;
  node.content.clear();
}

static int GetXMPErrorID(const XMP_Error& e) {
  // XMP_Error in the XMP SDK typically exposes GetID(). If not, adapt here.
  return e.GetID();
}

}  // namespace

class RDFEmptyPropertyElementTest_2137 : public ::testing::Test {
 protected:
  RDFEmptyPropertyElementTest_2137()
      : xmpRoot_(nullptr, "xmp:root", 0), xmlProp_(nullptr, "ns:prop", /*kind*/ 0) {}

  void TearDown() override { DeleteXMLTreeShallow(xmlProp_); }

  XMP_Node xmpRoot_;
  XML_Node xmlProp_;
};

TEST_F(RDFEmptyPropertyElementTest_2137, ThrowsWhenNestedContentPresent_2137) {
  // Arrange: empty property element with nested content (not allowed)
  xmlProp_.content.push_back(MakeXMLElement(&xmlProp_, "ns:child"));

  // Act / Assert
  try {
    RDF_EmptyPropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ true);
    FAIL() << "Expected XMP_Error to be thrown";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(GetXMPErrorID(e), kXMPErr_BadRDF);
  } catch (...) {
    FAIL() << "Expected XMP_Error";
  }
}

TEST_F(RDFEmptyPropertyElementTest_2137, ThrowsWhenBothResourceAndNodeID_2137) {
  // Arrange: rdf:resource and rdf:nodeID together is invalid
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "rdf:resource", "http://example.com/res"));
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "rdf:nodeID", "N1"));

  // Act / Assert
  try {
    RDF_EmptyPropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ false);
    FAIL() << "Expected XMP_Error to be thrown";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(GetXMPErrorID(e), kXMPErr_BadRDF);
  } catch (...) {
    FAIL() << "Expected XMP_Error";
  }
}

TEST_F(RDFEmptyPropertyElementTest_2137, ThrowsWhenBothRdfValueAndResource_2137) {
  // Arrange: rdf:value and rdf:resource together is invalid (observable via thrown error)
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "rdf:value", "v1"));
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "rdf:resource", "http://example.com/res"));

  // Act / Assert
  try {
    RDF_EmptyPropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ false);
    FAIL() << "Expected XMP_Error to be thrown";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(GetXMPErrorID(e), kXMPErr_BadXMP);
  } catch (...) {
    FAIL() << "Expected XMP_Error";
  }
}

TEST_F(RDFEmptyPropertyElementTest_2137, CreatesChildWithURIValueFromRdfResource_2137) {
  // Arrange
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "rdf:resource", "http://example.com/res"));

  const size_t beforeChildren = xmpRoot_.children.size();

  // Act
  ASSERT_NO_THROW(RDF_EmptyPropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ true));

  // Assert: a child was added
  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1);
  XMP_Node* child = xmpRoot_.children.back();
  ASSERT_NE(child, nullptr);

  EXPECT_EQ(child->value, "http://example.com/res");
  EXPECT_NE((child->options & kXMP_PropValueIsURI), 0u);

  // For rdf:resource value, the attribute holding the value is skipped as a qualifier.
  EXPECT_TRUE(child->qualifiers.empty());
}

TEST_F(RDFEmptyPropertyElementTest_2137, CreatesChildWithLiteralValueFromRdfValue_2137) {
  // Arrange
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "rdf:value", "literal"));

  const size_t beforeChildren = xmpRoot_.children.size();

  // Act
  ASSERT_NO_THROW(RDF_EmptyPropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ true));

  // Assert
  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1);
  XMP_Node* child = xmpRoot_.children.back();
  ASSERT_NE(child, nullptr);

  EXPECT_EQ(child->value, "literal");
  EXPECT_EQ((child->options & kXMP_PropValueIsURI), 0u);
  EXPECT_TRUE(child->qualifiers.empty());
}

TEST_F(RDFEmptyPropertyElementTest_2137, TreatsNonRdfNonLangAttributesAsStructFields_2137) {
  // Arrange: a non-rdf, non-xml:lang attribute should cause struct behavior (observable via options)
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "ex:field", "value1"));

  const size_t beforeChildren = xmpRoot_.children.size();

  // Act
  ASSERT_NO_THROW(RDF_EmptyPropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ false));

  // Assert: child added and marked as struct
  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1);
  XMP_Node* child = xmpRoot_.children.back();
  ASSERT_NE(child, nullptr);

  EXPECT_NE((child->options & kXMP_PropValueIsStruct), 0u);

  // Observable effect: attribute becomes a child field when struct mode is used.
  ASSERT_FALSE(child->children.empty());
  XMP_Node* field = child->children.front();
  ASSERT_NE(field, nullptr);
  EXPECT_EQ(field->value, "value1");
}

TEST_F(RDFEmptyPropertyElementTest_2137, XmlLangBecomesQualifierAndDoesNotForceStruct_2137) {
  // Arrange: xml:lang alone should be treated as a qualifier, not a struct field
  xmlProp_.attrs.push_back(MakeXMLAttr(&xmlProp_, "xml:lang", "en-US"));

  const size_t beforeChildren = xmpRoot_.children.size();

  // Act
  ASSERT_NO_THROW(RDF_EmptyPropertyElement(&xmpRoot_, xmlProp_, /*isTopLevel*/ false));

  // Assert
  ASSERT_EQ(xmpRoot_.children.size(), beforeChildren + 1);
  XMP_Node* child = xmpRoot_.children.back();
  ASSERT_NE(child, nullptr);

  EXPECT_EQ((child->options & kXMP_PropValueIsStruct), 0u);
  EXPECT_TRUE(child->children.empty());

  ASSERT_FALSE(child->qualifiers.empty());
  // Qualifier value should match the attribute value (observable through public fields).
  XMP_Node* qual = child->qualifiers.front();
  ASSERT_NE(qual, nullptr);
  EXPECT_EQ(qual->value, "en-US");
}