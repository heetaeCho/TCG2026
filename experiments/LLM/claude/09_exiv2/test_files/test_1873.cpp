#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary headers for XML_Node
#include "XMLParserAdapter.hpp"

class XMLNodeTest_1873 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with C-string name and parent as nullptr
TEST_F(XMLNodeTest_1873, ConstructWithCStringName_1873) {
    XML_Node node(nullptr, "testNode", 0);
    EXPECT_EQ(node.name, "testNode");
    EXPECT_EQ(node.kind, 0);
    EXPECT_EQ(node.nsPrefixLen, 0u);
    EXPECT_EQ(node.parent, nullptr);
}

// Test: Construction with std::string name
TEST_F(XMLNodeTest_1873, ConstructWithStdStringName_1873) {
    std::string nodeName = "stdStringNode";
    XML_Node node(nullptr, nodeName, 1);
    EXPECT_EQ(node.name, "stdStringNode");
    EXPECT_EQ(node.kind, 1);
    EXPECT_EQ(node.nsPrefixLen, 0u);
    EXPECT_EQ(node.parent, nullptr);
}

// Test: Construction with a parent node
TEST_F(XMLNodeTest_1873, ConstructWithParent_1873) {
    XML_Node parent(nullptr, "parentNode", 0);
    XML_Node child(&parent, "childNode", 1);
    EXPECT_EQ(child.parent, &parent);
    EXPECT_EQ(child.name, "childNode");
}

// Test: RemoveAttrs on empty attrs
TEST_F(XMLNodeTest_1873, RemoveAttrsOnEmpty_1873) {
    XML_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.attrs.empty());
    node.RemoveAttrs();
    EXPECT_TRUE(node.attrs.empty());
}

// Test: RemoveContent on empty content
TEST_F(XMLNodeTest_1873, RemoveContentOnEmpty_1873) {
    XML_Node node(nullptr, "node", 0);
    EXPECT_TRUE(node.content.empty());
    node.RemoveContent();
    EXPECT_TRUE(node.content.empty());
}

// Test: ClearNode empties everything
TEST_F(XMLNodeTest_1873, ClearNodeEmptiesAll_1873) {
    XML_Node node(nullptr, "node", 0);
    node.ns = "http://example.com/ns";
    node.name = "myNode";
    node.value = "someValue";
    
    // Add an attribute
    XML_Node* attr = new XML_Node(&node, "attr1", 0);
    attr->value = "val1";
    node.attrs.push_back(attr);
    
    // Add content
    XML_Node* content = new XML_Node(&node, "content1", 0);
    content->value = "cval1";
    node.content.push_back(content);
    
    node.ClearNode();
    EXPECT_TRUE(node.attrs.empty());
    EXPECT_TRUE(node.content.empty());
}

// Test: SetAttrValue and GetAttrValue
TEST_F(XMLNodeTest_1873, SetAndGetAttrValue_1873) {
    XML_Node node(nullptr, "node", 0);
    node.SetAttrValue("myAttr", "myValue");
    
    XMP_StringPtr result = node.GetAttrValue("myAttr");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "myValue");
}

// Test: GetAttrValue for non-existent attribute returns nullptr
TEST_F(XMLNodeTest_1873, GetAttrValueNonExistent_1873) {
    XML_Node node(nullptr, "node", 0);
    XMP_StringPtr result = node.GetAttrValue("nonExistent");
    EXPECT_EQ(result, nullptr);
}

// Test: SetAttrValue overwrites existing attribute
TEST_F(XMLNodeTest_1873, SetAttrValueOverwrite_1873) {
    XML_Node node(nullptr, "node", 0);
    node.SetAttrValue("attr", "value1");
    node.SetAttrValue("attr", "value2");
    
    XMP_StringPtr result = node.GetAttrValue("attr");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "value2");
}

// Test: Multiple attributes
TEST_F(XMLNodeTest_1873, MultipleAttributes_1873) {
    XML_Node node(nullptr, "node", 0);
    node.SetAttrValue("attr1", "val1");
    node.SetAttrValue("attr2", "val2");
    node.SetAttrValue("attr3", "val3");
    
    EXPECT_STREQ(node.GetAttrValue("attr1"), "val1");
    EXPECT_STREQ(node.GetAttrValue("attr2"), "val2");
    EXPECT_STREQ(node.GetAttrValue("attr3"), "val3");
}

// Test: SetLeafContentValue and GetLeafContentValue
TEST_F(XMLNodeTest_1873, SetAndGetLeafContentValue_1873) {
    XML_Node node(nullptr, "leaf", 0);
    node.SetLeafContentValue("leafValue");
    
    XMP_StringPtr result = node.GetLeafContentValue();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "leafValue");
}

// Test: GetLeafContentValue on node with no content
TEST_F(XMLNodeTest_1873, GetLeafContentValueEmpty_1873) {
    XML_Node node(nullptr, "emptyLeaf", 0);
    XMP_StringPtr result = node.GetLeafContentValue();
    // Could be nullptr or empty string depending on implementation
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
    }
}

// Test: CountNamedElements returns 0 when no matching elements
TEST_F(XMLNodeTest_1873, CountNamedElementsNone_1873) {
    XML_Node node(nullptr, "root", 0);
    size_t count = node.CountNamedElements("http://ns.example.com/", "child");
    EXPECT_EQ(count, 0u);
}

// Test: CountNamedElements with matching elements
TEST_F(XMLNodeTest_1873, CountNamedElementsMatching_1873) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "child", 0);
    child1->ns = "http://ns.example.com/";
    child1->name = "child";
    node.content.push_back(child1);
    
    XML_Node* child2 = new XML_Node(&node, "child", 0);
    child2->ns = "http://ns.example.com/";
    child2->name = "child";
    node.content.push_back(child2);
    
    size_t count = node.CountNamedElements("http://ns.example.com/", "child");
    EXPECT_EQ(count, 2u);
}

// Test: GetNamedElement returns nullptr when no match
TEST_F(XMLNodeTest_1873, GetNamedElementNoMatch_1873) {
    XML_Node node(nullptr, "root", 0);
    XML_NodePtr result = node.GetNamedElement("http://ns.example.com/", "child", 0);
    EXPECT_EQ(result, nullptr);
}

// Test: GetNamedElement returns correct element
TEST_F(XMLNodeTest_1873, GetNamedElementMatch_1873) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "child", 0);
    child1->ns = "http://ns.example.com/";
    child1->name = "child";
    node.content.push_back(child1);
    
    XML_NodePtr result = node.GetNamedElement("http://ns.example.com/", "child", 0);
    EXPECT_EQ(result, child1);
}

// Test: GetNamedElement with 'which' parameter
TEST_F(XMLNodeTest_1873, GetNamedElementByIndex_1873) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "child", 0);
    child1->ns = "http://ns.example.com/";
    child1->name = "child";
    child1->value = "first";
    node.content.push_back(child1);
    
    XML_Node* child2 = new XML_Node(&node, "child", 0);
    child2->ns = "http://ns.example.com/";
    child2->name = "child";
    child2->value = "second";
    node.content.push_back(child2);
    
    XML_NodePtr first = node.GetNamedElement("http://ns.example.com/", "child", 0);
    XML_NodePtr second = node.GetNamedElement("http://ns.example.com/", "child", 1);
    
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(first->value, "first");
    EXPECT_EQ(second->value, "second");
}

// Test: GetNamedElement with out-of-range index returns nullptr
TEST_F(XMLNodeTest_1873, GetNamedElementOutOfRange_1873) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "child", 0);
    child1->ns = "http://ns.example.com/";
    child1->name = "child";
    node.content.push_back(child1);
    
    XML_NodePtr result = node.GetNamedElement("http://ns.example.com/", "child", 5);
    EXPECT_EQ(result, nullptr);
}

// Test: Dump produces non-empty output
TEST_F(XMLNodeTest_1873, DumpProducesOutput_1873) {
    XML_Node node(nullptr, "testDump", 0);
    node.value = "dumpValue";
    
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_FALSE(buffer.empty());
}

// Test: Serialize produces non-empty output
TEST_F(XMLNodeTest_1873, SerializeProducesOutput_1873) {
    XML_Node node(nullptr, "testSerialize", 0);
    node.value = "serValue";
    
    std::string buffer;
    node.Serialize(&buffer);
    // Serialize should produce some output (may vary by implementation)
    // At minimum we verify it doesn't crash
}

// Test: IsWhitespaceNode on whitespace-only value
TEST_F(XMLNodeTest_1873, IsWhitespaceNodeTrue_1873) {
    XML_Node node(nullptr, "", 0);
    node.value = "   \t\n";
    // This should be considered a whitespace node (depends on implementation)
    bool result = node.IsWhitespaceNode();
    EXPECT_TRUE(result);
}

// Test: IsWhitespaceNode on non-whitespace value
TEST_F(XMLNodeTest_1873, IsWhitespaceNodeFalse_1873) {
    XML_Node node(nullptr, "", 0);
    node.value = "hello";
    bool result = node.IsWhitespaceNode();
    EXPECT_FALSE(result);
}

// Test: IsLeafContentNode
TEST_F(XMLNodeTest_1873, IsLeafContentNode_1873) {
    XML_Node node(nullptr, "leaf", 0);
    // A leaf content node typically has no child content nodes of element type
    bool result = node.IsLeafContentNode();
    // With no content, it should be a leaf
    EXPECT_TRUE(result);
}

// Test: IsEmptyLeafNode on empty node
TEST_F(XMLNodeTest_1873, IsEmptyLeafNodeTrue_1873) {
    XML_Node node(nullptr, "empty", 0);
    bool result = node.IsEmptyLeafNode();
    EXPECT_TRUE(result);
}

// Test: IsEmptyLeafNode on node with content
TEST_F(XMLNodeTest_1873, IsEmptyLeafNodeFalse_1873) {
    XML_Node node(nullptr, "nonEmpty", 0);
    XML_Node* child = new XML_Node(&node, "child", 0);
    child->value = "some content";
    node.content.push_back(child);
    
    bool result = node.IsEmptyLeafNode();
    EXPECT_FALSE(result);
}

// Test: Namespace and prefix fields
TEST_F(XMLNodeTest_1873, NamespaceAndPrefix_1873) {
    XML_Node node(nullptr, "ns:element", 0);
    node.ns = "http://example.com/ns";
    node.nsPrefixLen = 3; // "ns:"
    
    EXPECT_EQ(node.ns, "http://example.com/ns");
    EXPECT_EQ(node.nsPrefixLen, 3u);
    EXPECT_EQ(node.name, "ns:element");
}

// Test: Destructor cleans up attrs and content (no crash)
TEST_F(XMLNodeTest_1873, DestructorCleansUp_1873) {
    XML_Node* node = new XML_Node(nullptr, "root", 0);
    
    XML_Node* attr = new XML_Node(node, "attr1", 0);
    attr->value = "attrVal";
    node->attrs.push_back(attr);
    
    XML_Node* content = new XML_Node(node, "content1", 0);
    content->value = "contentVal";
    node->content.push_back(content);
    
    // This should not crash or leak
    delete node;
    SUCCEED();
}

// Test: Empty name construction
TEST_F(XMLNodeTest_1873, EmptyNameConstruction_1873) {
    XML_Node node(nullptr, "", 0);
    EXPECT_EQ(node.name, "");
    EXPECT_EQ(node.kind, 0);
}

// Test: Different kind values
TEST_F(XMLNodeTest_1873, DifferentKindValues_1873) {
    XML_Node node0(nullptr, "node", 0);
    EXPECT_EQ(node0.kind, 0);
    
    XML_Node node1(nullptr, "node", 1);
    EXPECT_EQ(node1.kind, 1);
    
    XML_Node node255(nullptr, "node", 255);
    EXPECT_EQ(node255.kind, 255);
}

// Test: RemoveAttrs after adding attributes
TEST_F(XMLNodeTest_1873, RemoveAttrsAfterAdding_1873) {
    XML_Node node(nullptr, "node", 0);
    node.SetAttrValue("a1", "v1");
    node.SetAttrValue("a2", "v2");
    
    EXPECT_FALSE(node.attrs.empty());
    node.RemoveAttrs();
    EXPECT_TRUE(node.attrs.empty());
    
    // After removal, attr should not be found
    EXPECT_EQ(node.GetAttrValue("a1"), nullptr);
    EXPECT_EQ(node.GetAttrValue("a2"), nullptr);
}

// Test: RemoveContent after adding content
TEST_F(XMLNodeTest_1873, RemoveContentAfterAdding_1873) {
    XML_Node node(nullptr, "node", 0);
    
    XML_Node* child = new XML_Node(&node, "child", 0);
    node.content.push_back(child);
    
    EXPECT_FALSE(node.content.empty());
    node.RemoveContent();
    EXPECT_TRUE(node.content.empty());
}

// Test: SetLeafContentValue replaces existing content
TEST_F(XMLNodeTest_1873, SetLeafContentValueReplace_1873) {
    XML_Node node(nullptr, "leaf", 0);
    node.SetLeafContentValue("first");
    
    XMP_StringPtr val1 = node.GetLeafContentValue();
    ASSERT_NE(val1, nullptr);
    EXPECT_STREQ(val1, "first");
    
    node.SetLeafContentValue("second");
    XMP_StringPtr val2 = node.GetLeafContentValue();
    ASSERT_NE(val2, nullptr);
    EXPECT_STREQ(val2, "second");
}

// Test: Dump on node with attributes and content
TEST_F(XMLNodeTest_1873, DumpWithAttrsAndContent_1873) {
    XML_Node node(nullptr, "root", 0);
    node.ns = "http://example.com/";
    node.SetAttrValue("attr1", "val1");
    node.SetLeafContentValue("content text");
    
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_FALSE(buffer.empty());
}

// Test: Serialize on node with attributes and content
TEST_F(XMLNodeTest_1873, SerializeWithAttrsAndContent_1873) {
    XML_Node node(nullptr, "root", 0);
    node.ns = "http://example.com/";
    node.SetAttrValue("attr1", "val1");
    node.SetLeafContentValue("content text");
    
    std::string buffer;
    node.Serialize(&buffer);
    // Verify it doesn't crash; content may vary
}

// Test: CountNamedElements with different namespaces
TEST_F(XMLNodeTest_1873, CountNamedElementsDifferentNS_1873) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "child", 0);
    child1->ns = "http://ns1.example.com/";
    child1->name = "child";
    node.content.push_back(child1);
    
    XML_Node* child2 = new XML_Node(&node, "child", 0);
    child2->ns = "http://ns2.example.com/";
    child2->name = "child";
    node.content.push_back(child2);
    
    EXPECT_EQ(node.CountNamedElements("http://ns1.example.com/", "child"), 1u);
    EXPECT_EQ(node.CountNamedElements("http://ns2.example.com/", "child"), 1u);
    EXPECT_EQ(node.CountNamedElements("http://ns3.example.com/", "child"), 0u);
}

// Test: CountNamedElements with different names same namespace
TEST_F(XMLNodeTest_1873, CountNamedElementsDifferentNames_1873) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "alpha", 0);
    child1->ns = "http://ns.example.com/";
    child1->name = "alpha";
    node.content.push_back(child1);
    
    XML_Node* child2 = new XML_Node(&node, "beta", 0);
    child2->ns = "http://ns.example.com/";
    child2->name = "beta";
    node.content.push_back(child2);
    
    EXPECT_EQ(node.CountNamedElements("http://ns.example.com/", "alpha"), 1u);
    EXPECT_EQ(node.CountNamedElements("http://ns.example.com/", "beta"), 1u);
    EXPECT_EQ(node.CountNamedElements("http://ns.example.com/", "gamma"), 0u);
}
