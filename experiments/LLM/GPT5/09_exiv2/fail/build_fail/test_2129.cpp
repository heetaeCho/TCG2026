// =================================================================================================
// TEST_ID: 2129
// Unit tests for static function RDF_PropertyElementList (ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Pull in the real types used by the implementation.
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// NOTE: RDF_PropertyElementList is a static function in ParseRDF.cpp (internal linkage).
// To test it as a black box without re-implementing logic, we include the .cpp into this
// test translation unit so the symbol is visible here.
#include "ParseRDF.cpp"

namespace {

// Helper: create an XML node (shared_ptr/raw pointer type depends on SDK typedefs).
static XML_NodePtr MakeXMLNode(XML_NodePtr parent, const std::string& name, XMP_Uns8 kind) {
  return XML_NodePtr(new XML_Node(parent, name, kind));
}

class ParseRDF_PropertyElementListTest_2129 : public ::testing::Test {
 protected:
  XMP_Node xmpParent_{nullptr, "xmpParent", 0};
  XML_NodePtr xmlParent_{MakeXMLNode(XML_NodePtr(), "xmlParent", kElemNode)};
};

TEST_F(ParseRDF_PropertyElementListTest_2129, EmptyContentDoesNothing_2129) {
  ASSERT_TRUE(xmlParent_->content.empty());
  EXPECT_NO_THROW(RDF_PropertyElementList(&xmpParent_, *xmlParent_, /*isTopLevel=*/true));
}

TEST_F(ParseRDF_PropertyElementListTest_2129, WhitespaceChildrenAreIgnored_2129) {
  XML_NodePtr ws = MakeXMLNode(xmlParent_, "ws", kCDataNode);
  ws->value = " \n\t  ";  // typical whitespace
  xmlParent_->content.push_back(ws);

  EXPECT_NO_THROW(RDF_PropertyElementList(&xmpParent_, *xmlParent_, /*isTopLevel=*/false));
}

TEST_F(ParseRDF_PropertyElementListTest_2129, NonElementNonWhitespaceThrowsBadRDF_2129) {
  // A non-element node that is not whitespace should cause an observable error.
  XML_NodePtr text = MakeXMLNode(xmlParent_, "text", kCDataNode);
  text->value = "not-whitespace";
  xmlParent_->content.push_back(text);

  try {
    RDF_PropertyElementList(&xmpParent_, *xmlParent_, /*isTopLevel=*/true);
    FAIL() << "Expected XMP_Error to be thrown";
  } catch (const XMP_Error& err) {
    EXPECT_EQ(err.GetID(), kXMPErr_BadRDF);
  }
}

TEST_F(ParseRDF_PropertyElementListTest_2129, WhitespaceBeforeBadNodeStillThrowsBadRDF_2129) {
  // Boundary-ish: ensure leading whitespace nodes are skipped and do not affect the error outcome.
  XML_NodePtr ws = MakeXMLNode(xmlParent_, "ws", kCDataNode);
  ws->value = "   ";
  xmlParent_->content.push_back(ws);

  XML_NodePtr bad = MakeXMLNode(xmlParent_, "bad", kAttrNode);
  bad->value = "x";
  xmlParent_->content.push_back(bad);

  EXPECT_THROW(RDF_PropertyElementList(&xmpParent_, *xmlParent_, /*isTopLevel=*/false), XMP_Error);
}

TEST_F(ParseRDF_PropertyElementListTest_2129, ManyWhitespaceNodesDoNotThrow_2129) {
  // Boundary: large-ish list of ignorable nodes should not throw.
  for (int i = 0; i < 200; ++i) {
    XML_NodePtr ws = MakeXMLNode(xmlParent_, "ws", kCDataNode);
    ws->value = "\n";
    xmlParent_->content.push_back(ws);
  }

  EXPECT_NO_THROW(RDF_PropertyElementList(&xmpParent_, *xmlParent_, /*isTopLevel=*/true));
}

}  // namespace