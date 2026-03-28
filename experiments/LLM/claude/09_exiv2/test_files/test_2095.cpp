#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "xmpsdk/src/XMLParserAdapter.hpp"

// We need to include the ExpatAdapter header for the actual adapter class
// Based on the codebase structure, ExpatAdapter likely inherits from XMLParserAdapter
#include "xmpsdk/src/ExpatAdapter.hpp"

class ExpatAdapterTest_2095 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Parsing a simple well-formed XML document
TEST_F(ExpatAdapterTest_2095, ParseSimpleXML_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>Hello</root>";
    size_t len = strlen(xml);

    EXPECT_NO_THROW(adapter->ParseBuffer(xml, len, true));

    // The tree should have content after parsing
    EXPECT_GT(adapter->tree.content.size(), 0u);

    delete adapter;
}

// Test: Parsing XML with character data
TEST_F(ExpatAdapterTest_2095, ParseCharacterData_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>TestContent</root>";
    size_t len = strlen(xml);

    adapter->ParseBuffer(xml, len, true);

    // Check that tree has content
    ASSERT_GT(adapter->tree.content.size(), 0u);

    // The root element should exist
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);
    EXPECT_EQ(rootElem->kind, kElemNode);
    EXPECT_EQ(rootElem->name, "root");

    // The root element should have character data content
    ASSERT_GT(rootElem->content.size(), 0u);
    XML_Node* cdataNode = rootElem->content[0];
    ASSERT_NE(cdataNode, nullptr);
    EXPECT_EQ(cdataNode->kind, kCDataNode);
    EXPECT_EQ(cdataNode->value, "TestContent");

    delete adapter;
}

// Test: Parsing XML with empty element
TEST_F(ExpatAdapterTest_2095, ParseEmptyElement_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root/>";
    size_t len = strlen(xml);

    EXPECT_NO_THROW(adapter->ParseBuffer(xml, len, true));

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);
    EXPECT_EQ(rootElem->kind, kElemNode);
    EXPECT_EQ(rootElem->content.size(), 0u);

    delete adapter;
}

// Test: Parsing XML with nested elements
TEST_F(ExpatAdapterTest_2095, ParseNestedElements_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root><child>data</child></root>";
    size_t len = strlen(xml);

    adapter->ParseBuffer(xml, len, true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);
    EXPECT_EQ(rootElem->name, "root");

    // Root should have a child element
    ASSERT_GT(rootElem->content.size(), 0u);

    // Find the child element node
    XML_Node* childElem = nullptr;
    for (size_t i = 0; i < rootElem->content.size(); ++i) {
        if (rootElem->content[i]->kind == kElemNode) {
            childElem = rootElem->content[i];
            break;
        }
    }
    ASSERT_NE(childElem, nullptr);
    EXPECT_EQ(childElem->name, "child");

    // Child should have character data
    ASSERT_GT(childElem->content.size(), 0u);
    XML_Node* cdataNode = childElem->content[0];
    ASSERT_NE(cdataNode, nullptr);
    EXPECT_EQ(cdataNode->kind, kCDataNode);
    EXPECT_EQ(cdataNode->value, "data");

    delete adapter;
}

// Test: Parsing XML with attributes
TEST_F(ExpatAdapterTest_2095, ParseElementWithAttributes_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root attr1=\"value1\" attr2=\"value2\"/>";
    size_t len = strlen(xml);

    adapter->ParseBuffer(xml, len, true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);

    // Should have attributes
    EXPECT_GE(rootElem->attrs.size(), 2u);

    delete adapter;
}

// Test: Parsing XML with namespaces
TEST_F(ExpatAdapterTest_2095, ParseElementWithNamespace_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><ns:root xmlns:ns=\"http://example.com\">content</ns:root>";
    size_t len = strlen(xml);

    EXPECT_NO_THROW(adapter->ParseBuffer(xml, len, true));

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);
    EXPECT_EQ(rootElem->kind, kElemNode);

    delete adapter;
}

// Test: Parsing XML with multiple character data segments
TEST_F(ExpatAdapterTest_2095, ParseMultipleCharData_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>Hello<child/>World</root>";
    size_t len = strlen(xml);

    adapter->ParseBuffer(xml, len, true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);

    // Root should have multiple content nodes (cdata + elem + cdata)
    EXPECT_GE(rootElem->content.size(), 3u);

    delete adapter;
}

// Test: Parsing XML incrementally (not last buffer)
TEST_F(ExpatAdapterTest_2095, ParseIncrementalBuffer_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* part1 = "<?xml version=\"1.0\"?><root>";
    const char* part2 = "content</root>";

    EXPECT_NO_THROW(adapter->ParseBuffer(part1, strlen(part1), false));
    EXPECT_NO_THROW(adapter->ParseBuffer(part2, strlen(part2), true));

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);
    EXPECT_EQ(rootElem->name, "root");

    delete adapter;
}

// Test: Parsing empty buffer with last=true
TEST_F(ExpatAdapterTest_2095, ParseEmptyBufferLast_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    // Parse a complete document first, then an empty last buffer
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    adapter->ParseBuffer(xml, strlen(xml), false);
    EXPECT_NO_THROW(adapter->ParseBuffer("", 0, true));

    delete adapter;
}

// Test: Parsing malformed XML should throw or handle error
TEST_F(ExpatAdapterTest_2095, ParseMalformedXML_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root><unclosed>";
    size_t len = strlen(xml);

    // Malformed XML - unclosed tags should cause an error when finalized
    try {
        adapter->ParseBuffer(xml, len, true);
        // If no exception, we can't verify error - that's implementation dependent
    } catch (...) {
        // Expected - malformed XML should cause an error
    }

    delete adapter;
}

// Test: Character data node parent relationship
TEST_F(ExpatAdapterTest_2095, CDataNodeParentRelationship_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>TestData</root>";
    adapter->ParseBuffer(xml, strlen(xml), true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);
    ASSERT_GT(rootElem->content.size(), 0u);

    XML_Node* cdataNode = rootElem->content[0];
    ASSERT_NE(cdataNode, nullptr);
    EXPECT_EQ(cdataNode->kind, kCDataNode);
    EXPECT_EQ(cdataNode->parent, rootElem);

    delete adapter;
}

// Test: Character data node name should be empty
TEST_F(ExpatAdapterTest_2095, CDataNodeNameIsEmpty_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>SomeText</root>";
    adapter->ParseBuffer(xml, strlen(xml), true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);
    ASSERT_GT(rootElem->content.size(), 0u);

    XML_Node* cdataNode = rootElem->content[0];
    ASSERT_NE(cdataNode, nullptr);
    EXPECT_EQ(cdataNode->kind, kCDataNode);
    EXPECT_EQ(cdataNode->name, "");

    delete adapter;
}

// Test: Tree root node kind
TEST_F(ExpatAdapterTest_2095, TreeRootIsRootNode_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    EXPECT_EQ(adapter->tree.kind, kRootNode);
    EXPECT_EQ(adapter->tree.name, "");

    delete adapter;
}

// Test: Parsing XML with whitespace character data
TEST_F(ExpatAdapterTest_2095, ParseWhitespaceCharData_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>   </root>";
    adapter->ParseBuffer(xml, strlen(xml), true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);

    // Should have whitespace content
    ASSERT_GT(rootElem->content.size(), 0u);
    XML_Node* cdataNode = rootElem->content[0];
    ASSERT_NE(cdataNode, nullptr);
    EXPECT_EQ(cdataNode->kind, kCDataNode);
    EXPECT_EQ(cdataNode->value, "   ");

    delete adapter;
}

// Test: Parsing XML with special characters (entities)
TEST_F(ExpatAdapterTest_2095, ParseSpecialCharEntities_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root>&amp;&lt;&gt;</root>";
    adapter->ParseBuffer(xml, strlen(xml), true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);

    // Collect all cdata values
    std::string allCData;
    for (size_t i = 0; i < rootElem->content.size(); ++i) {
        if (rootElem->content[i]->kind == kCDataNode) {
            allCData += rootElem->content[i]->value;
        }
    }
    EXPECT_EQ(allCData, "&<>");

    delete adapter;
}

// Test: Parsing deeply nested XML
TEST_F(ExpatAdapterTest_2095, ParseDeeplyNestedXML_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><a><b><c><d>deep</d></c></b></a>";
    adapter->ParseBuffer(xml, strlen(xml), true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* a = adapter->tree.content[0];
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->name, "a");

    // Navigate down
    ASSERT_GT(a->content.size(), 0u);
    XML_Node* b = nullptr;
    for (auto* node : a->content) {
        if (node->kind == kElemNode) { b = node; break; }
    }
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(b->name, "b");

    XML_Node* c = nullptr;
    for (auto* node : b->content) {
        if (node->kind == kElemNode) { c = node; break; }
    }
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->name, "c");

    XML_Node* d = nullptr;
    for (auto* node : c->content) {
        if (node->kind == kElemNode) { d = node; break; }
    }
    ASSERT_NE(d, nullptr);
    EXPECT_EQ(d->name, "d");

    ASSERT_GT(d->content.size(), 0u);
    EXPECT_EQ(d->content[0]->kind, kCDataNode);
    EXPECT_EQ(d->content[0]->value, "deep");

    delete adapter;
}

// Test: Creating adapter with namespace awareness
TEST_F(ExpatAdapterTest_2095, CreateAdapterWithNamespaceAwareness_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(true);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root xmlns=\"http://example.com\">data</root>";
    EXPECT_NO_THROW(adapter->ParseBuffer(xml, strlen(xml), true));

    ASSERT_GT(adapter->tree.content.size(), 0u);

    delete adapter;
}

// Test: Multiple sibling elements
TEST_F(ExpatAdapterTest_2095, ParseMultipleSiblingElements_2095) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter(false);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?><root><a>1</a><b>2</b><c>3</c></root>";
    adapter->ParseBuffer(xml, strlen(xml), true);

    ASSERT_GT(adapter->tree.content.size(), 0u);
    XML_Node* rootElem = adapter->tree.content[0];
    ASSERT_NE(rootElem, nullptr);

    // Count element children
    int elemCount = 0;
    for (auto* node : rootElem->content) {
        if (node->kind == kElemNode) elemCount++;
    }
    EXPECT_EQ(elemCount, 3);

    delete adapter;
}
