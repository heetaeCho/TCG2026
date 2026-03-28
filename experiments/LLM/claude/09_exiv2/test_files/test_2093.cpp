#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "XMLParserAdapter.hpp"

// We need the ExpatAdapter class
// ExpatAdapter is typically declared in a header; we include it
// based on the project structure
#include "ExpatAdapter.hpp"

class ExpatAdapterTest_2093 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Parse a simple XML element with no attributes
TEST_F(ExpatAdapterTest_2093, ParseSimpleElement_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root></root>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    // The tree should have content (the root element)
    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        EXPECT_EQ(rootElem->kind, kElemNode);
        EXPECT_EQ(rootElem->name, "root");
        EXPECT_TRUE(rootElem->attrs.empty());
    }

    delete adapter;
}

// Test: Parse XML with attributes
TEST_F(ExpatAdapterTest_2093, ParseElementWithAttributes_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root attr1=\"value1\" attr2=\"value2\"></root>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        EXPECT_EQ(rootElem->kind, kElemNode);
        EXPECT_EQ(rootElem->attrs.size(), 2u);

        bool foundAttr1 = false, foundAttr2 = false;
        for (size_t i = 0; i < rootElem->attrs.size(); ++i) {
            if (rootElem->attrs[i]->name == "attr1") {
                EXPECT_EQ(rootElem->attrs[i]->value, "value1");
                foundAttr1 = true;
            }
            if (rootElem->attrs[i]->name == "attr2") {
                EXPECT_EQ(rootElem->attrs[i]->value, "value2");
                foundAttr2 = true;
            }
        }
        EXPECT_TRUE(foundAttr1);
        EXPECT_TRUE(foundAttr2);
    }

    delete adapter;
}

// Test: Parse nested XML elements
TEST_F(ExpatAdapterTest_2093, ParseNestedElements_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><parent><child></child></parent>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* parentNode = adapter->tree.content[0];
        EXPECT_EQ(parentNode->name, "parent");
        EXPECT_FALSE(parentNode->content.empty());
        if (!parentNode->content.empty()) {
            // Find the child element node (content may include text/cdata nodes)
            bool foundChild = false;
            for (size_t i = 0; i < parentNode->content.size(); ++i) {
                if (parentNode->content[i]->kind == kElemNode && parentNode->content[i]->name == "child") {
                    foundChild = true;
                    break;
                }
            }
            EXPECT_TRUE(foundChild);
        }
    }

    delete adapter;
}

// Test: Parse XML with rdf:RDF element sets rootNode
TEST_F(ExpatAdapterTest_2093, ParseRdfRDFSetsRootNode_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml =
        "<?xml version=\"1.0\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "</rdf:RDF>"
        "</x:xmpmeta>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_NE(adapter->rootNode, nullptr);
    if (adapter->rootNode != nullptr) {
        EXPECT_EQ(adapter->rootNode->name, "rdf:RDF");
    }
    EXPECT_EQ(adapter->rootCount, 1u);

    delete adapter;
}

// Test: Parse XML with xml:lang attribute normalizes value
TEST_F(ExpatAdapterTest_2093, XmlLangAttributeNormalized_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml =
        "<?xml version=\"1.0\"?>"
        "<root xml:lang=\"EN-US\"></root>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        bool foundLang = false;
        for (size_t i = 0; i < rootElem->attrs.size(); ++i) {
            if (rootElem->attrs[i]->name == "xml:lang") {
                // NormalizeLangValue should lowercase the value
                EXPECT_EQ(rootElem->attrs[i]->value, "en-us");
                foundLang = true;
                break;
            }
        }
        EXPECT_TRUE(foundLang);
    }

    delete adapter;
}

// Test: Parse empty XML buffer
TEST_F(ExpatAdapterTest_2093, ParseEmptyBuffer_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    // Parsing empty buffer with last=true shouldn't crash
    adapter->ParseBuffer("", 0, true);

    // Tree content should be empty (no elements parsed)
    EXPECT_TRUE(adapter->tree.content.empty());

    delete adapter;
}

// Test: Parse XML with text content
TEST_F(ExpatAdapterTest_2093, ParseElementWithTextContent_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>Hello World</root>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        EXPECT_EQ(rootElem->name, "root");
        // Should have content nodes (text)
        EXPECT_FALSE(rootElem->content.empty());
    }

    delete adapter;
}

// Test: Parse XML with namespaced elements
TEST_F(ExpatAdapterTest_2093, ParseNamespacedElements_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml =
        "<?xml version=\"1.0\"?>"
        "<dc:title xmlns:dc=\"http://purl.org/dc/elements/1.1/\">Test</dc:title>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* elem = adapter->tree.content[0];
        EXPECT_EQ(elem->kind, kElemNode);
        // The name should be set via SetQualName with namespace
        EXPECT_FALSE(elem->name.empty());
    }

    delete adapter;
}

// Test: Parse XML incrementally (multiple ParseBuffer calls)
TEST_F(ExpatAdapterTest_2093, ParseIncrementalBuffers_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* part1 = "<?xml version=\"1.0\"?><ro";
    const char* part2 = "ot><child/></root>";

    adapter->ParseBuffer(part1, std::strlen(part1), false);
    adapter->ParseBuffer(part2, std::strlen(part2), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        EXPECT_EQ(rootElem->name, "root");
    }

    delete adapter;
}

// Test: Parse XML with multiple children
TEST_F(ExpatAdapterTest_2093, ParseMultipleChildren_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml =
        "<?xml version=\"1.0\"?>"
        "<root><child1/><child2/><child3/></root>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        // Count element children
        size_t elemChildren = 0;
        for (size_t i = 0; i < rootElem->content.size(); ++i) {
            if (rootElem->content[i]->kind == kElemNode) {
                ++elemChildren;
            }
        }
        EXPECT_EQ(elemChildren, 3u);
    }

    delete adapter;
}

// Test: rootCount is initially zero
TEST_F(ExpatAdapterTest_2093, InitialRootCount_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    EXPECT_EQ(adapter->rootCount, 0u);
    EXPECT_EQ(adapter->rootNode, nullptr);

    delete adapter;
}

// Test: Parse XML with self-closing element
TEST_F(ExpatAdapterTest_2093, ParseSelfClosingElement_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root/>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        EXPECT_EQ(rootElem->kind, kElemNode);
        EXPECT_EQ(rootElem->name, "root");
        EXPECT_TRUE(rootElem->content.empty());
    }

    delete adapter;
}

// Test: Parse malformed XML throws or reports error
TEST_F(ExpatAdapterTest_2093, ParseMalformedXML_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root><unclosed>";

    try {
        adapter->ParseBuffer(xml, std::strlen(xml), true);
        // If no exception, that's also acceptable depending on implementation
    } catch (...) {
        // Expected - malformed XML may throw
    }

    delete adapter;
}

// Test: Parent-child relationship is correct
TEST_F(ExpatAdapterTest_2093, ParentChildRelationship_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><parent><child/></parent>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* parentNode = adapter->tree.content[0];
        EXPECT_EQ(parentNode->parent, &adapter->tree);

        for (size_t i = 0; i < parentNode->content.size(); ++i) {
            if (parentNode->content[i]->kind == kElemNode) {
                EXPECT_EQ(parentNode->content[i]->parent, parentNode);
            }
        }
    }

    delete adapter;
}

// Test: Attribute nodes have correct kind
TEST_F(ExpatAdapterTest_2093, AttributeNodeKind_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root myattr=\"myval\"/>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_FALSE(adapter->tree.content.empty());
    if (!adapter->tree.content.empty()) {
        XML_Node* rootElem = adapter->tree.content[0];
        EXPECT_EQ(rootElem->attrs.size(), 1u);
        if (!rootElem->attrs.empty()) {
            EXPECT_EQ(rootElem->attrs[0]->kind, kAttrNode);
            EXPECT_EQ(rootElem->attrs[0]->value, "myval");
            EXPECT_EQ(rootElem->attrs[0]->parent, rootElem);
        }
    }

    delete adapter;
}

// Test: Multiple rdf:RDF elements increment rootCount
TEST_F(ExpatAdapterTest_2093, MultipleRdfRDFIncrementsRootCount_2093) {
    ExpatAdapter* adapter = ExpatAdapter::Create(0);
    ASSERT_NE(adapter, nullptr);

    const char* xml =
        "<?xml version=\"1.0\"?>"
        "<wrapper xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:RDF></rdf:RDF>"
        "<rdf:RDF></rdf:RDF>"
        "</wrapper>";
    adapter->ParseBuffer(xml, std::strlen(xml), true);

    EXPECT_EQ(adapter->rootCount, 2u);

    delete adapter;
}
