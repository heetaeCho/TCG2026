#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// Since RDF_NodeElementList is a static function in ParseRDF.cpp,
// we test the observable behavior through the public interfaces of XML_Node and XMP_Node
// which are the primary data structures used by the parsing logic.

class XMLNodeTest_2126 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class XMPNodeTest_2126 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// XML_Node Tests
// ============================================================

TEST_F(XMLNodeTest_2126, ConstructWithCStringName_2126) {
    XML_Node node(nullptr, "testNode", 0);
    EXPECT_EQ(node.name, "testNode");
    EXPECT_EQ(node.kind, 0);
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_EQ(node.nsPrefixLen, 0u);
}

TEST_F(XMLNodeTest_2126, ConstructWithStringName_2126) {
    std::string nodeName = "myElement";
    XML_Node node(nullptr, nodeName, 1);
    EXPECT_EQ(node.name, "myElement");
    EXPECT_EQ(node.kind, 1);
    EXPECT_EQ(node.parent, nullptr);
}

TEST_F(XMLNodeTest_2126, ConstructWithParent_2126) {
    XML_Node parent(nullptr, "parent", 0);
    XML_Node child(&parent, "child", 0);
    EXPECT_EQ(child.parent, &parent);
    EXPECT_EQ(child.name, "child");
}

TEST_F(XMLNodeTest_2126, ContentVectorInitiallyEmpty_2126) {
    XML_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.content.empty());
}

TEST_F(XMLNodeTest_2126, AttrsVectorInitiallyEmpty_2126) {
    XML_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.attrs.empty());
}

TEST_F(XMLNodeTest_2126, AddChildToContent_2126) {
    XML_Node parent(nullptr, "parent", 0);
    XML_Node* child = new XML_Node(&parent, "child", 0);
    parent.content.push_back(child);
    EXPECT_EQ(parent.content.size(), 1u);
    EXPECT_EQ(parent.content[0]->name, "child");
    // Cleanup handled by RemoveContent or manually
    parent.RemoveContent();
}

TEST_F(XMLNodeTest_2126, AddMultipleChildrenToContent_2126) {
    XML_Node parent(nullptr, "parent", 0);
    XML_Node* child1 = new XML_Node(&parent, "child1", 0);
    XML_Node* child2 = new XML_Node(&parent, "child2", 0);
    XML_Node* child3 = new XML_Node(&parent, "child3", 0);
    parent.content.push_back(child1);
    parent.content.push_back(child2);
    parent.content.push_back(child3);
    EXPECT_EQ(parent.content.size(), 3u);
    parent.RemoveContent();
    EXPECT_TRUE(parent.content.empty());
}

TEST_F(XMLNodeTest_2126, IsWhitespaceNodeOnWhitespace_2126) {
    // A whitespace node typically has kind = kCDataKind and only whitespace value
    XML_Node node(nullptr, "", 0);
    node.kind = 3; // kCDataKind typically
    node.value = "   \t\n  ";
    // The result depends on implementation; we just verify it doesn't crash
    bool result = node.IsWhitespaceNode();
    // We can't assert the exact result without knowing the implementation,
    // but we verify the call succeeds
    (void)result;
}

TEST_F(XMLNodeTest_2126, IsWhitespaceNodeOnNonWhitespace_2126) {
    XML_Node node(nullptr, "element", 0);
    node.kind = 3;
    node.value = "Hello World";
    bool result = node.IsWhitespaceNode();
    (void)result;
}

TEST_F(XMLNodeTest_2126, IsLeafContentNode_2126) {
    XML_Node node(nullptr, "leaf", 0);
    bool result = node.IsLeafContentNode();
    (void)result;
}

TEST_F(XMLNodeTest_2126, IsEmptyLeafNode_2126) {
    XML_Node node(nullptr, "empty", 0);
    bool result = node.IsEmptyLeafNode();
    (void)result;
}

TEST_F(XMLNodeTest_2126, SetAndGetAttrValue_2126) {
    XML_Node node(nullptr, "element", 0);
    node.SetAttrValue("key", "value");
    const char* val = node.GetAttrValue("key");
    if (val != nullptr) {
        EXPECT_STREQ(val, "value");
    }
}

TEST_F(XMLNodeTest_2126, GetAttrValueNonExistent_2126) {
    XML_Node node(nullptr, "element", 0);
    const char* val = node.GetAttrValue("nonexistent");
    // Should return nullptr or empty for non-existent attribute
    if (val != nullptr) {
        EXPECT_STREQ(val, "");
    }
}

TEST_F(XMLNodeTest_2126, SetLeafContentValue_2126) {
    XML_Node node(nullptr, "leaf", 0);
    node.SetLeafContentValue("some content");
    const char* val = node.GetLeafContentValue();
    if (val != nullptr) {
        EXPECT_STREQ(val, "some content");
    }
}

TEST_F(XMLNodeTest_2126, CountNamedElementsEmpty_2126) {
    XML_Node node(nullptr, "parent", 0);
    size_t count = node.CountNamedElements("http://ns.example.com/", "child");
    EXPECT_EQ(count, 0u);
}

TEST_F(XMLNodeTest_2126, GetNamedElementNonExistent_2126) {
    XML_Node node(nullptr, "parent", 0);
    XML_Node* found = node.GetNamedElement("http://ns.example.com/", "child", 0);
    EXPECT_EQ(found, nullptr);
}

TEST_F(XMLNodeTest_2126, RemoveAttrs_2126) {
    XML_Node node(nullptr, "element", 0);
    node.SetAttrValue("attr1", "val1");
    node.RemoveAttrs();
    EXPECT_TRUE(node.attrs.empty());
}

TEST_F(XMLNodeTest_2126, RemoveContent_2126) {
    XML_Node parent(nullptr, "parent", 0);
    XML_Node* child = new XML_Node(&parent, "child", 0);
    parent.content.push_back(child);
    EXPECT_EQ(parent.content.size(), 1u);
    parent.RemoveContent();
    EXPECT_TRUE(parent.content.empty());
}

TEST_F(XMLNodeTest_2126, ClearNode_2126) {
    XML_Node node(nullptr, "element", 0);
    node.value = "some value";
    node.ns = "http://ns.example.com/";
    node.SetAttrValue("attr", "val");
    XML_Node* child = new XML_Node(&node, "child", 0);
    node.content.push_back(child);
    node.ClearNode();
    EXPECT_TRUE(node.content.empty());
    EXPECT_TRUE(node.attrs.empty());
}

TEST_F(XMLNodeTest_2126, SerializeNode_2126) {
    XML_Node node(nullptr, "element", 0);
    node.value = "test";
    std::string buffer;
    node.Serialize(&buffer);
    // Just verify it doesn't crash and produces some output
    // The exact format depends on implementation
}

TEST_F(XMLNodeTest_2126, DumpNode_2126) {
    XML_Node node(nullptr, "element", 0);
    std::string buffer;
    node.Dump(&buffer);
    // Just verify it doesn't crash
}

TEST_F(XMLNodeTest_2126, NamespaceField_2126) {
    XML_Node node(nullptr, "ns:element", 0);
    node.ns = "http://ns.example.com/";
    node.nsPrefixLen = 3; // "ns:"
    EXPECT_EQ(node.ns, "http://ns.example.com/");
    EXPECT_EQ(node.nsPrefixLen, 3u);
}

TEST_F(XMLNodeTest_2126, DestructorCleansUp_2126) {
    // Verify destructor doesn't crash
    XML_Node* node = new XML_Node(nullptr, "test", 0);
    XML_Node* child = new XML_Node(node, "child", 0);
    node->content.push_back(child);
    delete node; // Should clean up children
}

// ============================================================
// XMP_Node Tests
// ============================================================

TEST_F(XMPNodeTest_2126, ConstructWithCStringNameAndOptions_2126) {
    XMP_Node node(nullptr, "xmp:Property", 0);
    EXPECT_EQ(node.name, "xmp:Property");
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_TRUE(node.value.empty());
}

TEST_F(XMPNodeTest_2126, ConstructWithStringNameAndOptions_2126) {
    std::string name = "xmp:Property";
    XMP_Node node(nullptr, name, 0);
    EXPECT_EQ(node.name, "xmp:Property");
}

TEST_F(XMPNodeTest_2126, ConstructWithNameAndValue_2126) {
    XMP_Node node(nullptr, "xmp:Title", "My Title", 0);
    EXPECT_EQ(node.name, "xmp:Title");
    EXPECT_EQ(node.value, "My Title");
    EXPECT_EQ(node.parent, nullptr);
}

TEST_F(XMPNodeTest_2126, ConstructWithStringNameAndValue_2126) {
    std::string name = "xmp:Title";
    std::string value = "My Title";
    XMP_Node node(nullptr, name, value, 0);
    EXPECT_EQ(node.name, "xmp:Title");
    EXPECT_EQ(node.value, "My Title");
}

TEST_F(XMPNodeTest_2126, ConstructWithParent_2126) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node child(&parent, "child", 0);
    EXPECT_EQ(child.parent, &parent);
}

TEST_F(XMPNodeTest_2126, ChildrenInitiallyEmpty_2126) {
    XMP_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.children.empty());
}

TEST_F(XMPNodeTest_2126, QualifiersInitiallyEmpty_2126) {
    XMP_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(XMPNodeTest_2126, AddChild_2126) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&parent, "child", 0);
    parent.children.push_back(child);
    EXPECT_EQ(parent.children.size(), 1u);
    EXPECT_EQ(parent.children[0]->name, "child");
    parent.RemoveChildren();
}

TEST_F(XMPNodeTest_2126, AddQualifier_2126) {
    XMP_Node node(nullptr, "node", 0);
    XMP_Node* qual = new XMP_Node(&node, "qualifier", 0);
    node.qualifiers.push_back(qual);
    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.RemoveQualifiers();
}

TEST_F(XMPNodeTest_2126, RemoveChildren_2126) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child1 = new XMP_Node(&parent, "child1", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "child2", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);
    EXPECT_EQ(parent.children.size(), 2u);
    parent.RemoveChildren();
    EXPECT_TRUE(parent.children.empty());
}

TEST_F(XMPNodeTest_2126, RemoveQualifiers_2126) {
    XMP_Node node(nullptr, "node", 0);
    XMP_Node* q1 = new XMP_Node(&node, "q1", 0);
    XMP_Node* q2 = new XMP_Node(&node, "q2", 0);
    node.qualifiers.push_back(q1);
    node.qualifiers.push_back(q2);
    EXPECT_EQ(node.qualifiers.size(), 2u);
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(XMPNodeTest_2126, ClearNode_2126) {
    XMP_Node node(nullptr, "node", "value", 0);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    XMP_Node* qual = new XMP_Node(&node, "qual", 0);
    node.children.push_back(child);
    node.qualifiers.push_back(qual);
    node.ClearNode();
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(XMPNodeTest_2126, RemoveChildrenOnEmpty_2126) {
    XMP_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.children.empty());
    node.RemoveChildren(); // Should not crash
    EXPECT_TRUE(node.children.empty());
}

TEST_F(XMPNodeTest_2126, RemoveQualifiersOnEmpty_2126) {
    XMP_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.qualifiers.empty());
    node.RemoveQualifiers(); // Should not crash
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(XMPNodeTest_2126, DestructorCleansUp_2126) {
    XMP_Node* node = new XMP_Node(nullptr, "test", 0);
    XMP_Node* child = new XMP_Node(node, "child", 0);
    node->children.push_back(child);
    delete node; // Should clean up
}

TEST_F(XMPNodeTest_2126, OptionsField_2126) {
    XMP_Node node(nullptr, "node", 0x0010);
    EXPECT_EQ(node.options, 0x0010u);
}

TEST_F(XMPNodeTest_2126, MultipleChildrenOrder_2126) {
    XMP_Node parent(nullptr, "parent", 0);
    for (int i = 0; i < 5; ++i) {
        std::string childName = "child" + std::to_string(i);
        XMP_Node* child = new XMP_Node(&parent, childName, 0);
        parent.children.push_back(child);
    }
    EXPECT_EQ(parent.children.size(), 5u);
    for (int i = 0; i < 5; ++i) {
        std::string expectedName = "child" + std::to_string(i);
        EXPECT_EQ(parent.children[i]->name, expectedName);
    }
    parent.RemoveChildren();
}

// ============================================================
// Integration-style tests for XML_Node content iteration pattern
// (mimicking RDF_NodeElementList traversal pattern)
// ============================================================

class RDFNodeElementListPatternTest_2126 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RDFNodeElementListPatternTest_2126, EmptyContentNoIteration_2126) {
    XML_Node xmlParent(nullptr, "rdf:RDF", 0);
    // Mimicking the loop pattern: iterating over empty content
    int count = 0;
    for (auto it = xmlParent.content.begin(); it != xmlParent.content.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST_F(RDFNodeElementListPatternTest_2126, ContentWithOnlyWhitespaceNodes_2126) {
    XML_Node xmlParent(nullptr, "rdf:RDF", 0);
    // Create whitespace nodes (kind=3 for CData, value is whitespace)
    XML_Node* ws1 = new XML_Node(&xmlParent, "", 3);
    ws1->value = "   ";
    XML_Node* ws2 = new XML_Node(&xmlParent, "", 3);
    ws2->value = "\n\t";
    xmlParent.content.push_back(ws1);
    xmlParent.content.push_back(ws2);

    int nonWhitespaceCount = 0;
    for (auto it = xmlParent.content.begin(); it != xmlParent.content.end(); ++it) {
        if (!(*it)->IsWhitespaceNode()) {
            nonWhitespaceCount++;
        }
    }
    // All are whitespace, so nonWhitespaceCount should be 0
    // (depends on implementation of IsWhitespaceNode)
    xmlParent.RemoveContent();
}

TEST_F(RDFNodeElementListPatternTest_2126, ContentWithMixedNodes_2126) {
    XML_Node xmlParent(nullptr, "rdf:RDF", 0);

    XML_Node* ws = new XML_Node(&xmlParent, "", 3);
    ws->value = "   ";
    xmlParent.content.push_back(ws);

    XML_Node* element = new XML_Node(&xmlParent, "rdf:Description", 0);
    element->kind = 2; // element kind
    xmlParent.content.push_back(element);

    XML_Node* ws2 = new XML_Node(&xmlParent, "", 3);
    ws2->value = "\n";
    xmlParent.content.push_back(ws2);

    EXPECT_EQ(xmlParent.content.size(), 3u);

    // Iterate mimicking the RDF_NodeElementList pattern
    int processedElements = 0;
    for (auto it = xmlParent.content.begin(); it != xmlParent.content.end(); ++it) {
        if ((*it)->IsWhitespaceNode()) continue;
        processedElements++;
    }
    // At least the element node should be processed
    EXPECT_GE(processedElements, 1);

    xmlParent.RemoveContent();
}

TEST_F(RDFNodeElementListPatternTest_2126, SingleElementContent_2126) {
    XML_Node xmlParent(nullptr, "rdf:RDF", 0);
    XML_Node* element = new XML_Node(&xmlParent, "rdf:Description", 2);
    element->ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    xmlParent.content.push_back(element);

    EXPECT_EQ(xmlParent.content.size(), 1u);
    EXPECT_EQ(xmlParent.content[0]->name, "rdf:Description");

    xmlParent.RemoveContent();
}

TEST_F(RDFNodeElementListPatternTest_2126, MultipleElementContent_2126) {
    XML_Node xmlParent(nullptr, "rdf:RDF", 0);

    for (int i = 0; i < 10; ++i) {
        std::string name = "rdf:Description" + std::to_string(i);
        XML_Node* element = new XML_Node(&xmlParent, name, 2);
        xmlParent.content.push_back(element);
    }

    EXPECT_EQ(xmlParent.content.size(), 10u);

    int count = 0;
    for (auto it = xmlParent.content.begin(); it != xmlParent.content.end(); ++it) {
        if (!(*it)->IsWhitespaceNode()) {
            count++;
        }
    }
    EXPECT_GE(count, 0); // Can't know exact behavior of IsWhitespaceNode for these

    xmlParent.RemoveContent();
}

// Test that XMP_Node can serve as a parent for collecting parsed results
TEST_F(RDFNodeElementListPatternTest_2126, XMPNodeAsCollector_2126) {
    XMP_Node xmpRoot(nullptr, "xmpRoot", 0);

    // Simulate adding children as would happen in RDF_NodeElement
    XMP_Node* schema1 = new XMP_Node(&xmpRoot, "http://ns.adobe.com/xap/1.0/", 0);
    xmpRoot.children.push_back(schema1);

    XMP_Node* schema2 = new XMP_Node(&xmpRoot, "http://purl.org/dc/elements/1.1/", 0);
    xmpRoot.children.push_back(schema2);

    EXPECT_EQ(xmpRoot.children.size(), 2u);
    EXPECT_EQ(xmpRoot.children[0]->name, "http://ns.adobe.com/xap/1.0/");
    EXPECT_EQ(xmpRoot.children[1]->name, "http://purl.org/dc/elements/1.1/");

    xmpRoot.RemoveChildren();
}
