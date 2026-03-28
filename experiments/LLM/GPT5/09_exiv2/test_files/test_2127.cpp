// =================================================================================================
// TEST_ID: 2127
// Unit tests for RDF_NodeElement (./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// Pull in the real implementation (RDF_NodeElement is static in ParseRDF.cpp).
// These tests treat the implementation as a black box and only validate observable behavior
// (throws / no-throws) through the public-callable test TU that includes the .cpp.
#include "./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

// Minimal includes for constructing inputs (these headers are referenced by the prompt).
#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "./TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"

namespace {

// NOTE: XML_Node::kind is used by the parser; for this test, we only need a consistent value.
// If the codebase defines named constants, they will still work with this simple value.
constexpr XMP_Uns8 kElementKind = 1;

class RDF_NodeElementTest_2127 : public ::testing::Test {
protected:
  XMP_Node MakeParentNode() {
    // Using a simple root node; options value is not part of this test’s assertions.
    return XMP_Node(/*_parent*/ nullptr, /*_name*/ "root", /*_options*/ 0);
  }

  XML_Node MakeElementNode(const std::string& qname) {
    return XML_Node(/*_parent*/ nullptr, /*_name*/ qname, /*_kind*/ kElementKind);
  }
};

}  // namespace

// --- Normal operation ---

TEST_F(RDF_NodeElementTest_2127, AllowsTopLevelRdfDescription_2127) {
  XMP_Node xmpParent = MakeParentNode();
  XML_Node xmlNode = MakeElementNode("rdf:Description");

  EXPECT_NO_THROW(RDF_NodeElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
}

TEST_F(RDF_NodeElementTest_2127, AllowsNonTopLevelTypedNode_2127) {
  XMP_Node xmpParent = MakeParentNode();
  // A QName that is commonly treated as a typed node (non-rdf:Description).
  XML_Node xmlNode = MakeElementNode("ex:MyTypedNode");

  EXPECT_NO_THROW(RDF_NodeElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
}

// --- Boundary conditions ---

TEST_F(RDF_NodeElementTest_2127, EmptyElementNameIsRejectedOrThrows_2127) {
  XMP_Node xmpParent = MakeParentNode();
  XML_Node xmlNode = MakeElementNode("");

  // Observable behavior: must not silently succeed for an ill-formed node name.
  EXPECT_ANY_THROW(RDF_NodeElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
}

TEST_F(RDF_NodeElementTest_2127, NonTopLevelRdfDescriptionDoesNotThrow_2127) {
  XMP_Node xmpParent = MakeParentNode();
  XML_Node xmlNode = MakeElementNode("rdf:Description");

  EXPECT_NO_THROW(RDF_NodeElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
}

// --- Exceptional / error cases (observable via thrown exceptions) ---

TEST_F(RDF_NodeElementTest_2127, RejectsNonDescriptionAndNonTypedNode_2127) {
  XMP_Node xmpParent = MakeParentNode();
  // A QName that is typically an RDF term but not rdf:Description or a typed node.
  // The function under test requires Description or typedNode; others must throw.
  XML_Node xmlNode = MakeElementNode("rdf:Bag");

  EXPECT_ANY_THROW(RDF_NodeElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
}

TEST_F(RDF_NodeElementTest_2127, RejectsTopLevelTypedNode_2127) {
  XMP_Node xmpParent = MakeParentNode();
  XML_Node xmlNode = MakeElementNode("ex:MyTypedNode");

  EXPECT_ANY_THROW(RDF_NodeElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
}