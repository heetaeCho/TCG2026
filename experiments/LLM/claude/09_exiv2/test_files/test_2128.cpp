#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <stdexcept>

// Include necessary headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// We need to access the static function RDF_NodeElementAttrs.
// Since it's static in ParseRDF.cpp, we include it (with necessary prerequisites).
// This is a testing workaround for static functions.

#define XMP_INCLUDE_XMPFILES 0

// Forward declarations and includes needed by ParseRDF.cpp
#include "XMP_Environment.h"
#include "XMPCore_Impl.hpp"

// Include the source to get access to the static function
#include "ParseRDF.cpp"

class RDFNodeElementAttrsTest_2128 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
    
    // Helper to create an XML_Node with attributes
    XML_Node* createXMLNode(const std::string& name) {
        XML_Node* node = new XML_Node(nullptr, name.c_str(), 0);
        return node;
    }
    
    // Helper to add an attribute to an XML_Node
    void addAttr(XML_Node* node, const std::string& attrName, const std::string& attrValue) {
        XML_Node* attr = new XML_Node(node, attrName.c_str(), 0);
        attr->value = attrValue;
        node->attrs.push_back(attr);
    }
    
    void cleanupXMLNode(XML_Node* node) {
        for (auto* attr : node->attrs) {
            delete attr;
        }
        node->attrs.clear();
        delete node;
    }
};

// Test: Top-level rdf:about sets xmpParent name when name is empty
TEST_F(RDFNodeElementAttrsTest_2128, AboutSetsNameWhenEmpty_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);  // parent is null (tree root)
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/test");
    
    try {
        RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true);
        EXPECT_EQ(xmpRoot.name, "http://example.com/test");
    } catch (...) {
        FAIL() << "Should not throw for valid rdf:about attribute";
    }
    
    cleanupXMLNode(xmlNode);
}

// Test: Top-level rdf:about with matching name does not throw
TEST_F(RDFNodeElementAttrsTest_2128, AboutMatchingNameNoThrow_2128) {
    XMP_Node xmpRoot(nullptr, "http://example.com/test", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/test");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    EXPECT_EQ(xmpRoot.name, "http://example.com/test");
    
    cleanupXMLNode(xmlNode);
}

// Test: Top-level rdf:about with mismatched name throws kXMPErr_BadXMP
TEST_F(RDFNodeElementAttrsTest_2128, AboutMismatchedNameThrows_2128) {
    XMP_Node xmpRoot(nullptr, "http://example.com/one", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/two");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: Top-level rdf:about with empty value does not change existing name
TEST_F(RDFNodeElementAttrsTest_2128, AboutEmptyValueKeepsExistingName_2128) {
    XMP_Node xmpRoot(nullptr, "http://example.com/existing", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    EXPECT_EQ(xmpRoot.name, "http://example.com/existing");
    
    cleanupXMLNode(xmlNode);
}

// Test: Mutually exclusive attributes - rdf:about and rdf:ID together throw
TEST_F(RDFNodeElementAttrsTest_2128, MutuallyExclusiveAboutAndIDThrows_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/test");
    addAttr(xmlNode, "rdf:ID", "someID");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: Mutually exclusive attributes - rdf:about and rdf:nodeID together throw
TEST_F(RDFNodeElementAttrsTest_2128, MutuallyExclusiveAboutAndNodeIDThrows_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/test");
    addAttr(xmlNode, "rdf:nodeID", "someNodeID");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: Mutually exclusive attributes - rdf:ID and rdf:nodeID together throw
TEST_F(RDFNodeElementAttrsTest_2128, MutuallyExclusiveIDAndNodeIDThrows_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:ID", "id1");
    addAttr(xmlNode, "rdf:nodeID", "nodeId1");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: No attributes - no throw, name remains unchanged
TEST_F(RDFNodeElementAttrsTest_2128, NoAttributesNoThrow_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    EXPECT_TRUE(xmpRoot.name.empty());
    
    cleanupXMLNode(xmlNode);
}

// Test: Single rdf:ID attribute does not throw
TEST_F(RDFNodeElementAttrsTest_2128, SingleIDNoThrow_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:ID", "myID");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    
    cleanupXMLNode(xmlNode);
}

// Test: Single rdf:nodeID attribute does not throw
TEST_F(RDFNodeElementAttrsTest_2128, SingleNodeIDNoThrow_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:nodeID", "myNodeID");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    
    cleanupXMLNode(xmlNode);
}

// Test: Invalid RDF attribute (e.g., rdf:li) throws kXMPErr_BadRDF
TEST_F(RDFNodeElementAttrsTest_2128, InvalidRDFAttributeThrows_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:li", "value");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: rdf:Description as attribute throws (invalid nodeElement attribute)
TEST_F(RDFNodeElementAttrsTest_2128, RDFDescriptionAttrThrows_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:Description", "value");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: Non-RDF "Other" attribute adds child node
TEST_F(RDFNodeElementAttrsTest_2128, OtherAttributeAddsChild_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "dc:creator", "John Doe");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    // The child should have been added
    EXPECT_FALSE(xmpRoot.children.empty());
    
    cleanupXMLNode(xmlNode);
    xmpRoot.RemoveChildren();
}

// Test: Non-top-level rdf:about does not set xmpParent name
TEST_F(RDFNodeElementAttrsTest_2128, NonTopLevelAboutDoesNotSetName_2128) {
    XMP_Node parentNode(nullptr, "parent", 0);
    XMP_Node xmpChild(&parentNode, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/test");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpChild, *xmlNode, false));
    // Name should remain empty since isTopLevel is false
    EXPECT_TRUE(xmpChild.name.empty());
    
    cleanupXMLNode(xmlNode);
}

// Test: All three mutually exclusive attributes throw
TEST_F(RDFNodeElementAttrsTest_2128, AllThreeExclusiveAttrsThrow_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/test");
    addAttr(xmlNode, "rdf:ID", "myID");
    addAttr(xmlNode, "rdf:nodeID", "myNodeID");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: Multiple "Other" attributes add multiple children
TEST_F(RDFNodeElementAttrsTest_2128, MultipleOtherAttrsAddMultipleChildren_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "dc:title", "My Title");
    addAttr(xmlNode, "dc:creator", "Author");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    EXPECT_GE(xmpRoot.children.size(), 2u);
    
    cleanupXMLNode(xmlNode);
    xmpRoot.RemoveChildren();
}

// Test: rdf:about with other non-RDF attributes works together
TEST_F(RDFNodeElementAttrsTest_2128, AboutWithOtherAttrsWorks_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:about", "http://example.com/test");
    addAttr(xmlNode, "dc:title", "My Title");
    
    EXPECT_NO_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true));
    EXPECT_EQ(xmpRoot.name, "http://example.com/test");
    EXPECT_FALSE(xmpRoot.children.empty());
    
    cleanupXMLNode(xmlNode);
    xmpRoot.RemoveChildren();
}

// Test: rdf:resource as attribute should throw (invalid nodeElement attribute)
TEST_F(RDFNodeElementAttrsTest_2128, RDFResourceAttrThrows_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:resource", "http://example.com");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}

// Test: rdf:parseType as attribute should throw (invalid nodeElement attribute)
TEST_F(RDFNodeElementAttrsTest_2128, RDFParseTypeAttrThrows_2128) {
    XMP_Node xmpRoot(nullptr, "", 0);
    XML_Node* xmlNode = createXMLNode("rdf:Description");
    addAttr(xmlNode, "rdf:parseType", "Literal");
    
    EXPECT_THROW(RDF_NodeElementAttrs(&xmpRoot, *xmlNode, true), XMP_Error);
    
    cleanupXMLNode(xmlNode);
}
