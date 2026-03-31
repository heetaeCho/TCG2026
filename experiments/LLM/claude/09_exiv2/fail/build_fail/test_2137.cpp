#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdexcept>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// We need access to the static function. Since it's static in the .cpp,
// we include it to get access. This also brings in helper functions.
#include "ParseRDF.cpp"

class RDFEmptyPropertyElementTest_2137 : public ::testing::Test {
protected:
    void SetUp() override {
        xmpParent = new XMP_Node(nullptr, "xmpParent", 0);
    }

    void TearDown() override {
        delete xmpParent;
        // Clean up any XML nodes we created
        for (auto* node : allocatedNodes) {
            delete node;
        }
        allocatedNodes.clear();
    }

    XMP_Node* xmpParent;
    std::vector<XML_Node*> allocatedNodes;

    XML_Node* makeXMLNode(XML_Node* parent, const std::string& name, XMP_Uns8 kind = kElemNode) {
        XML_Node* node = new XML_Node(parent, name, kind);
        allocatedNodes.push_back(node);
        return node;
    }

    XML_Node* makeAttrNode(XML_Node* parent, const std::string& name, const std::string& value) {
        XML_Node* node = new XML_Node(parent, name, kAttrNode);
        node->value = value;
        allocatedNodes.push_back(node);
        return node;
    }
};

// Test: Nested content causes an exception
TEST_F(RDFEmptyPropertyElementTest_2137, NestedContentThrows_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    XML_Node* contentChild = makeXMLNode(&xmlNode, "child", kElemNode);
    xmlNode.content.push_back(contentChild);

    EXPECT_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test: rdf:resource and rdf:nodeID together throws
TEST_F(RDFEmptyPropertyElementTest_2137, ResourceAndNodeIDThrows_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    
    XML_Node* resourceAttr = makeAttrNode(&xmlNode, "rdf:resource", "http://example.com");
    XML_Node* nodeIDAttr = makeAttrNode(&xmlNode, "rdf:nodeID", "node1");
    
    xmlNode.attrs.push_back(resourceAttr);
    xmlNode.attrs.push_back(nodeIDAttr);

    EXPECT_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test: rdf:nodeID and rdf:resource (reverse order) throws
TEST_F(RDFEmptyPropertyElementTest_2137, NodeIDThenResourceThrows_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    
    XML_Node* nodeIDAttr = makeAttrNode(&xmlNode, "rdf:nodeID", "node1");
    XML_Node* resourceAttr = makeAttrNode(&xmlNode, "rdf:resource", "http://example.com");
    
    xmlNode.attrs.push_back(nodeIDAttr);
    xmlNode.attrs.push_back(resourceAttr);

    EXPECT_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test: rdf:value and rdf:resource together throws
TEST_F(RDFEmptyPropertyElementTest_2137, ValueAndResourceThrows_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    
    XML_Node* valueAttr = makeAttrNode(&xmlNode, "rdf:value", "somevalue");
    XML_Node* resourceAttr = makeAttrNode(&xmlNode, "rdf:resource", "http://example.com");
    
    xmlNode.attrs.push_back(valueAttr);
    xmlNode.attrs.push_back(resourceAttr);

    EXPECT_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test: rdf:resource then rdf:value throws
TEST_F(RDFEmptyPropertyElementTest_2137, ResourceThenValueThrows_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    
    XML_Node* resourceAttr = makeAttrNode(&xmlNode, "rdf:resource", "http://example.com");
    XML_Node* valueAttr = makeAttrNode(&xmlNode, "rdf:value", "somevalue");
    
    xmlNode.attrs.push_back(resourceAttr);
    xmlNode.attrs.push_back(valueAttr);

    EXPECT_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test: Empty element with no attributes creates a child node
TEST_F(RDFEmptyPropertyElementTest_2137, EmptyElementNoAttrs_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    EXPECT_FALSE(xmpParent->children.empty());
}

// Test: Element with rdf:resource sets URI option
TEST_F(RDFEmptyPropertyElementTest_2137, ResourceSetsURIOption_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* resourceAttr = makeAttrNode(&xmlNode, "rdf:resource", "http://example.com");
    xmlNode.attrs.push_back(resourceAttr);

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    ASSERT_FALSE(xmpParent->children.empty());
    XMP_Node* child = xmpParent->children[0];
    EXPECT_EQ(child->value, "http://example.com");
    EXPECT_TRUE((child->options & kXMP_PropValueIsURI) != 0);
}

// Test: Element with rdf:value uses value attribute
TEST_F(RDFEmptyPropertyElementTest_2137, ValueAttrUsed_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* valueAttr = makeAttrNode(&xmlNode, "rdf:value", "hello world");
    xmlNode.attrs.push_back(valueAttr);

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    ASSERT_FALSE(xmpParent->children.empty());
    XMP_Node* child = xmpParent->children[0];
    EXPECT_EQ(child->value, "hello world");
    EXPECT_FALSE((child->options & kXMP_PropValueIsURI) != 0);
}

// Test: Property attributes make struct
TEST_F(RDFEmptyPropertyElementTest_2137, PropertyAttrsCreateStruct_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    // A non-rdf, non-xml:lang attribute counts as a property attribute
    XML_Node* propAttr = makeAttrNode(&xmlNode, "test:attr1", "val1");
    propAttr->ns = "test:";
    propAttr->nsPrefixLen = 5;
    xmlNode.attrs.push_back(propAttr);

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    ASSERT_FALSE(xmpParent->children.empty());
    XMP_Node* child = xmpParent->children[0];
    EXPECT_TRUE((child->options & kXMP_PropValueIsStruct) != 0);
}

// Test: xml:lang is treated as qualifier, not property attr
TEST_F(RDFEmptyPropertyElementTest_2137, XmlLangIsQualifier_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* langAttr = makeAttrNode(&xmlNode, "xml:lang", "en");
    xmlNode.attrs.push_back(langAttr);

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    ASSERT_FALSE(xmpParent->children.empty());
    XMP_Node* child = xmpParent->children[0];
    // xml:lang should not cause struct, and should be added as qualifier
    EXPECT_FALSE((child->options & kXMP_PropValueIsStruct) != 0);
}

// Test: rdf:ID is ignored and doesn't cause exceptions
TEST_F(RDFEmptyPropertyElementTest_2137, RdfIDIgnored_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* idAttr = makeAttrNode(&xmlNode, "rdf:ID", "myid");
    xmlNode.attrs.push_back(idAttr);

    EXPECT_NO_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false)
    );
    EXPECT_FALSE(xmpParent->children.empty());
}

// Test: Unrecognized rdf: attribute throws
TEST_F(RDFEmptyPropertyElementTest_2137, UnrecognizedRDFAttrThrows_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    // rdf:li or another reserved RDF term that falls into default case
    XML_Node* badAttr = makeAttrNode(&xmlNode, "rdf:li", "val");
    xmlNode.attrs.push_back(badAttr);

    EXPECT_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test: Multiple property attributes in struct mode add as children
TEST_F(RDFEmptyPropertyElementTest_2137, MultiplePropertyAttrsAsChildren_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* attr1 = makeAttrNode(&xmlNode, "test:a", "val1");
    attr1->ns = "test:";
    attr1->nsPrefixLen = 5;
    XML_Node* attr2 = makeAttrNode(&xmlNode, "test:b", "val2");
    attr2->ns = "test:";
    attr2->nsPrefixLen = 5;
    xmlNode.attrs.push_back(attr1);
    xmlNode.attrs.push_back(attr2);

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    ASSERT_FALSE(xmpParent->children.empty());
    XMP_Node* child = xmpParent->children[0];
    EXPECT_TRUE((child->options & kXMP_PropValueIsStruct) != 0);
    // Both property attrs should become children of the struct
    EXPECT_EQ(child->children.size(), 2u);
}

// Test: rdf:resource with xml:lang - resource is value, lang is qualifier
TEST_F(RDFEmptyPropertyElementTest_2137, ResourceWithLang_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* resourceAttr = makeAttrNode(&xmlNode, "rdf:resource", "http://example.com");
    XML_Node* langAttr = makeAttrNode(&xmlNode, "xml:lang", "en");
    xmlNode.attrs.push_back(resourceAttr);
    xmlNode.attrs.push_back(langAttr);

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    ASSERT_FALSE(xmpParent->children.empty());
    XMP_Node* child = xmpParent->children[0];
    EXPECT_EQ(child->value, "http://example.com");
    EXPECT_TRUE((child->options & kXMP_PropValueIsURI) != 0);
}

// Test: rdf:value with additional property attr - value is value, attr is qualifier
TEST_F(RDFEmptyPropertyElementTest_2137, ValueWithPropertyAttr_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* valueAttr = makeAttrNode(&xmlNode, "rdf:value", "myval");
    XML_Node* otherAttr = makeAttrNode(&xmlNode, "test:q", "qval");
    otherAttr->ns = "test:";
    otherAttr->nsPrefixLen = 5;
    xmlNode.attrs.push_back(valueAttr);
    xmlNode.attrs.push_back(otherAttr);

    RDF_EmptyPropertyElement(xmpParent, xmlNode, false);

    ASSERT_FALSE(xmpParent->children.empty());
    XMP_Node* child = xmpParent->children[0];
    EXPECT_EQ(child->value, "myval");
    // The other attr should be a qualifier since hasValueAttr is true and it's not struct
    EXPECT_FALSE((child->options & kXMP_PropValueIsStruct) != 0);
}

// Test: rdf:nodeID alone doesn't throw
TEST_F(RDFEmptyPropertyElementTest_2137, NodeIDAloneNoThrow_2137) {
    XML_Node xmlNode(nullptr, "test:prop", kElemNode);
    xmlNode.ns = "test:";
    xmlNode.name = "test:prop";
    xmlNode.nsPrefixLen = 5;
    
    XML_Node* nodeIDAttr = makeAttrNode(&xmlNode, "rdf:nodeID", "node1");
    xmlNode.attrs.push_back(nodeIDAttr);

    EXPECT_NO_THROW(
        RDF_EmptyPropertyElement(xmpParent, xmlNode, false)
    );
    EXPECT_FALSE(xmpParent->children.empty());
}
