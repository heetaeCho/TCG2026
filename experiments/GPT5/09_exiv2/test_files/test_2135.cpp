// =================================================================================================
// Unit tests for RDF_ParseTypeCollectionPropertyElement
// File: ./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Bring in the real implementation (function has internal linkage in the .cpp).
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"

namespace {

class ParseTypeCollectionPropertyElementTest_2135 : public ::testing::Test {
 protected:
  static XMP_Node MakeParentNode() {
    // Use a minimal, valid construction via the public constructors.
    return XMP_Node(/*_parent*/ nullptr, /*_name*/ "ns:Parent", /*_options*/ 0);
  }

  static XML_Node MakeXmlNode() {
    // Create a minimal XML_Node. The exact meaning of "kind" is not required for these tests.
    XML_NodePtr parent;  // null parent is acceptable for construction per interface.
    return XML_Node(parent, /*_name*/ "rdf:Description", /*_kind*/ static_cast<XMP_Uns8>(0));
  }
};

TEST_F(ParseTypeCollectionPropertyElementTest_2135, ThrowsOnTopLevelTrue_2135) {
  XMP_Node xmpParent = MakeParentNode();
  XML_Node xmlNode = MakeXmlNode();

  EXPECT_ANY_THROW(RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true));
}

TEST_F(ParseTypeCollectionPropertyElementTest_2135, ThrowsOnTopLevelFalse_2135) {
  XMP_Node xmpParent = MakeParentNode();
  XML_Node xmlNode = MakeXmlNode();

  EXPECT_ANY_THROW(RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ false));
}

TEST_F(ParseTypeCollectionPropertyElementTest_2135, ThrowsWithNullXmpParent_2135) {
  XML_Node xmlNode = MakeXmlNode();

  EXPECT_ANY_THROW(
      RDF_ParseTypeCollectionPropertyElement(/*xmpParent*/ nullptr, xmlNode, /*isTopLevel*/ true));
}

}  // namespace