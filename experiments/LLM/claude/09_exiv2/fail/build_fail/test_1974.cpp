#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMLParserAdapter.hpp"

// Test fixture for XML_Node tests
class XMLNodeTest_1974 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(XMLNodeTest_1974, ConstructorWithCStringName_1974) {
    XML_Node node(nullptr, "testNode", 1);
    EXPECT_EQ(node.name, "testNode");
    EXPECT_EQ(node.kind, 1);
    EXPECT_EQ(node.nsPrefixLen, 0u);
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_TRUE(node.ns.empty());
    EXPECT_TRUE(node.value.empty());
    EXPECT_TRUE(node.attrs.empty());
    EXPECT_TRUE(node.content.empty());
}

TEST_F(XMLNodeTest_1974, ConstructorWithStringName_1974) {
    std::string name = "testNode";
    XML_Node node(nullptr, name, 2);
    EXPECT_EQ(node.name, "testNode");
    EXPECT_EQ(node.kind, 2);
    EXPECT_EQ(node.nsPrefixLen, 0u);
    EXPECT_EQ(node.parent, nullptr);
}

TEST_F(XMLNodeTest_1974, ConstructorWithParent_1974) {
    XML_Node parent(nullptr, "parent", 0);
    XML_Node child(&parent, "child", 1);
    EXPECT_EQ(child.parent, &parent);
    EXPECT_EQ(child.name, "child");
}

TEST_F(XMLNodeTest_1974, ConstructorWithEmptyName_1974) {
    XML_Node node(nullptr, "", 0);
    EXPECT_TRUE(node.name.empty());
    EXPECT_EQ(node.kind, 0);
}

// ============================================================
// IsWhitespaceNode Tests
// ============================================================

TEST_F(XMLNodeTest_1974, IsWhitespaceNodeWithWhitespaceValue_1974) {
    XML_Node node(nullptr, "", 3); // cdata kind
    node.value = "   \t\n";
    // Whitespace node behavior depends on kind and value content
    // We just call and verify it doesn't crash; actual logic is implementation-defined
    bool result = node.IsWhitespaceNode();
    // Just check it returns a boolean without crash
    (void)result;
}

TEST_F(XMLNodeTest_1974, IsWhitespaceNodeWithNonWhitespaceValue_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.value = "hello";
    bool result = node.IsWhitespaceNode();
    EXPECT_FALSE(result);
}

// ============================================================
// IsLeafContentNode Tests
// ============================================================

TEST_F(XMLNodeTest_1974, IsLeafContentNodeOnEmptyElement_1974) {
    XML_Node node(nullptr, "leaf", 1);
    bool result = node.IsLeafContentNode();
    (void)result; // observable behavior
}

TEST_F(XMLNodeTest_1974, IsLeafContentNodeWithContent_1974) {
    XML_Node node(nullptr, "parent", 1);
    XML_Node* child = new XML_Node(&node, "child", 3);
    child->value = "text";
    node.content.push_back(child);
    bool result = node.IsLeafContentNode();
    (void)result;
}

// ============================================================
// IsEmptyLeafNode Tests
// ============================================================

TEST_F(XMLNodeTest_1974, IsEmptyLeafNodeOnEmptyNode_1974) {
    XML_Node node(nullptr, "empty", 1);
    bool result = node.IsEmptyLeafNode();
    EXPECT_TRUE(result);
}

TEST_F(XMLNodeTest_1974, IsEmptyLeafNodeWithContent_1974) {
    XML_Node node(nullptr, "nonEmpty", 1);
    XML_Node* child = new XML_Node(&node, "child", 1);
    node.content.push_back(child);
    bool result = node.IsEmptyLeafNode();
    EXPECT_FALSE(result);
}

// ============================================================
// GetAttrValue / SetAttrValue Tests
// ============================================================

TEST_F(XMLNodeTest_1974, SetAndGetAttrValue_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.SetAttrValue("myAttr", "myValue");
    
    const char* val = node.GetAttrValue("myAttr");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "myValue");
}

TEST_F(XMLNodeTest_1974, GetAttrValueNonExistent_1974) {
    XML_Node node(nullptr, "elem", 1);
    const char* val = node.GetAttrValue("nonexistent");
    EXPECT_EQ(val, nullptr);
}

TEST_F(XMLNodeTest_1974, SetAttrValueOverwrite_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.SetAttrValue("attr", "value1");
    node.SetAttrValue("attr", "value2");
    
    const char* val = node.GetAttrValue("attr");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "value2");
}

TEST_F(XMLNodeTest_1974, SetMultipleAttributes_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.SetAttrValue("attr1", "val1");
    node.SetAttrValue("attr2", "val2");
    node.SetAttrValue("attr3", "val3");
    
    EXPECT_STREQ(node.GetAttrValue("attr1"), "val1");
    EXPECT_STREQ(node.GetAttrValue("attr2"), "val2");
    EXPECT_STREQ(node.GetAttrValue("attr3"), "val3");
}

TEST_F(XMLNodeTest_1974, SetAttrValueEmptyValue_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.SetAttrValue("attr", "");
    
    const char* val = node.GetAttrValue("attr");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "");
}

// ============================================================
// GetLeafContentValue / SetLeafContentValue Tests
// ============================================================

TEST_F(XMLNodeTest_1974, SetAndGetLeafContentValue_1974) {
    XML_Node node(nullptr, "leaf", 1);
    node.SetLeafContentValue("leafValue");
    
    const char* val = node.GetLeafContentValue();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "leafValue");
}

TEST_F(XMLNodeTest_1974, GetLeafContentValueOnEmptyNode_1974) {
    XML_Node node(nullptr, "leaf", 1);
    const char* val = node.GetLeafContentValue();
    // Could be nullptr or empty string
    (void)val;
}

TEST_F(XMLNodeTest_1974, SetLeafContentValueEmptyString_1974) {
    XML_Node node(nullptr, "leaf", 1);
    node.SetLeafContentValue("");
    const char* val = node.GetLeafContentValue();
    // Behavior depends on implementation
    (void)val;
}

TEST_F(XMLNodeTest_1974, SetLeafContentValueOverwrite_1974) {
    XML_Node node(nullptr, "leaf", 1);
    node.SetLeafContentValue("first");
    node.SetLeafContentValue("second");
    
    const char* val = node.GetLeafContentValue();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "second");
}

// ============================================================
// CountNamedElements Tests
// ============================================================

TEST_F(XMLNodeTest_1974, CountNamedElementsEmpty_1974) {
    XML_Node node(nullptr, "root", 0);
    size_t count = node.CountNamedElements("http://ns.example.com", "child");
    EXPECT_EQ(count, 0u);
}

TEST_F(XMLNodeTest_1974, CountNamedElementsWithMatching_1974) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "child", 1);
    child1->ns = "http://ns.example.com";
    node.content.push_back(child1);
    
    XML_Node* child2 = new XML_Node(&node, "child", 1);
    child2->ns = "http://ns.example.com";
    node.content.push_back(child2);
    
    XML_Node* child3 = new XML_Node(&node, "other", 1);
    child3->ns = "http://ns.example.com";
    node.content.push_back(child3);
    
    size_t count = node.CountNamedElements("http://ns.example.com", "child");
    EXPECT_EQ(count, 2u);
}

TEST_F(XMLNodeTest_1974, CountNamedElementsWrongNS_1974) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child = new XML_Node(&node, "child", 1);
    child->ns = "http://ns.example.com";
    node.content.push_back(child);
    
    size_t count = node.CountNamedElements("http://other.ns.com", "child");
    EXPECT_EQ(count, 0u);
}

// ============================================================
// GetNamedElement Tests
// ============================================================

TEST_F(XMLNodeTest_1974, GetNamedElementFound_1974) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child = new XML_Node(&node, "child", 1);
    child->ns = "http://ns.example.com";
    node.content.push_back(child);
    
    XML_Node* result = node.GetNamedElement("http://ns.example.com", "child", 0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "child");
}

TEST_F(XMLNodeTest_1974, GetNamedElementNotFound_1974) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* result = node.GetNamedElement("http://ns.example.com", "nonexistent", 0);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLNodeTest_1974, GetNamedElementByIndex_1974) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child1 = new XML_Node(&node, "child", 1);
    child1->ns = "http://ns.example.com";
    child1->value = "first";
    node.content.push_back(child1);
    
    XML_Node* child2 = new XML_Node(&node, "child", 1);
    child2->ns = "http://ns.example.com";
    child2->value = "second";
    node.content.push_back(child2);
    
    XML_Node* result0 = node.GetNamedElement("http://ns.example.com", "child", 0);
    ASSERT_NE(result0, nullptr);
    EXPECT_EQ(result0->value, "first");
    
    XML_Node* result1 = node.GetNamedElement("http://ns.example.com", "child", 1);
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->value, "second");
}

TEST_F(XMLNodeTest_1974, GetNamedElementOutOfRange_1974) {
    XML_Node node(nullptr, "root", 0);
    
    XML_Node* child = new XML_Node(&node, "child", 1);
    child->ns = "http://ns.example.com";
    node.content.push_back(child);
    
    XML_Node* result = node.GetNamedElement("http://ns.example.com", "child", 5);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// Dump Tests
// ============================================================

TEST_F(XMLNodeTest_1974, DumpEmptyNode_1974) {
    XML_Node node(nullptr, "root", 0);
    std::string buffer;
    node.Dump(&buffer);
    // Should produce some output
    EXPECT_FALSE(buffer.empty());
}

TEST_F(XMLNodeTest_1974, DumpNodeWithValue_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.value = "testValue";
    std::string buffer;
    node.Dump(&buffer);
    // Should contain the name and value
    EXPECT_NE(buffer.find("elem"), std::string::npos);
    EXPECT_NE(buffer.find("testValue"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeWithNamespace_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.ns = "http://example.com/ns";
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("http://example.com/ns"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeWithPrefixLen_1974) {
    XML_Node node(nullptr, "ns:elem", 1);
    node.nsPrefixLen = 3;
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("prefixLen="), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeWithAttrs_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.SetAttrValue("testAttr", "attrValue");
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("attrs"), std::string::npos);
    EXPECT_NE(buffer.find("testAttr"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeWithContent_1974) {
    XML_Node node(nullptr, "parent", 1);
    XML_Node* child = new XML_Node(&node, "child", 1);
    child->value = "childValue";
    node.content.push_back(child);
    
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("child"), std::string::npos);
    EXPECT_NE(buffer.find("childValue"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeKindRoot_1974) {
    XML_Node node(nullptr, "root", 0);
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("root"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeKindElem_1974) {
    XML_Node node(nullptr, "myElem", 1);
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("elem"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeKindAttr_1974) {
    XML_Node node(nullptr, "myAttr", 2);
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("attr"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeKindCdata_1974) {
    XML_Node node(nullptr, "myCdata", 3);
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("cdata"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DumpNodeKindPI_1974) {
    XML_Node node(nullptr, "myPI", 4);
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find("pi"), std::string::npos);
}

// ============================================================
// Serialize Tests
// ============================================================

TEST_F(XMLNodeTest_1974, SerializeEmptyNode_1974) {
    XML_Node node(nullptr, "root", 0);
    std::string buffer;
    node.Serialize(&buffer);
    // Should produce some output
    (void)buffer;
}

TEST_F(XMLNodeTest_1974, SerializeElementWithContent_1974) {
    XML_Node node(nullptr, "elem", 1);
    XML_Node* text = new XML_Node(&node, "", 3);
    text->value = "hello";
    node.content.push_back(text);
    
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_NE(buffer.find("elem"), std::string::npos);
    EXPECT_NE(buffer.find("hello"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, SerializeElementWithAttributes_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.SetAttrValue("attr1", "val1");
    
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_NE(buffer.find("attr1"), std::string::npos);
    EXPECT_NE(buffer.find("val1"), std::string::npos);
}

// ============================================================
// RemoveAttrs Tests
// ============================================================

TEST_F(XMLNodeTest_1974, RemoveAttrsFromNode_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.SetAttrValue("attr1", "val1");
    node.SetAttrValue("attr2", "val2");
    
    EXPECT_FALSE(node.attrs.empty());
    
    node.RemoveAttrs();
    EXPECT_TRUE(node.attrs.empty());
    EXPECT_EQ(node.GetAttrValue("attr1"), nullptr);
    EXPECT_EQ(node.GetAttrValue("attr2"), nullptr);
}

TEST_F(XMLNodeTest_1974, RemoveAttrsFromEmptyNode_1974) {
    XML_Node node(nullptr, "elem", 1);
    EXPECT_TRUE(node.attrs.empty());
    node.RemoveAttrs(); // Should not crash
    EXPECT_TRUE(node.attrs.empty());
}

// ============================================================
// RemoveContent Tests
// ============================================================

TEST_F(XMLNodeTest_1974, RemoveContentFromNode_1974) {
    XML_Node node(nullptr, "parent", 1);
    XML_Node* child = new XML_Node(&node, "child", 1);
    node.content.push_back(child);
    
    EXPECT_FALSE(node.content.empty());
    
    node.RemoveContent();
    EXPECT_TRUE(node.content.empty());
}

TEST_F(XMLNodeTest_1974, RemoveContentFromEmptyNode_1974) {
    XML_Node node(nullptr, "parent", 1);
    EXPECT_TRUE(node.content.empty());
    node.RemoveContent(); // Should not crash
    EXPECT_TRUE(node.content.empty());
}

// ============================================================
// ClearNode Tests
// ============================================================

TEST_F(XMLNodeTest_1974, ClearNodeRemovesEverything_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.ns = "http://example.com";
    node.value = "someValue";
    node.nsPrefixLen = 5;
    node.SetAttrValue("attr", "val");
    XML_Node* child = new XML_Node(&node, "child", 1);
    node.content.push_back(child);
    
    node.ClearNode();
    
    EXPECT_TRUE(node.ns.empty());
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
    EXPECT_TRUE(node.attrs.empty());
    EXPECT_TRUE(node.content.empty());
}

TEST_F(XMLNodeTest_1974, ClearNodeOnAlreadyClearNode_1974) {
    XML_Node node(nullptr, "", 0);
    node.ClearNode(); // Should not crash
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
}

// ============================================================
// Destructor Tests
// ============================================================

TEST_F(XMLNodeTest_1974, DestructorCleansUpChildren_1974) {
    // Just verify no memory leaks or crashes with nested nodes
    XML_Node* root = new XML_Node(nullptr, "root", 0);
    XML_Node* child = new XML_Node(root, "child", 1);
    XML_Node* grandchild = new XML_Node(child, "grandchild", 1);
    child->content.push_back(grandchild);
    root->content.push_back(child);
    
    // Destructor should handle cleanup
    delete root;
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST_F(XMLNodeTest_1974, NodeWithLongName_1974) {
    std::string longName(10000, 'a');
    XML_Node node(nullptr, longName, 1);
    EXPECT_EQ(node.name, longName);
    
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_NE(buffer.find(longName), std::string::npos);
}

TEST_F(XMLNodeTest_1974, NodeWithSpecialCharactersInValue_1974) {
    XML_Node node(nullptr, "elem", 1);
    node.value = "<>&\"'";
    
    std::string buffer;
    node.Dump(&buffer);
    // Value should appear in dump
    EXPECT_NE(buffer.find(node.value), std::string::npos);
}

TEST_F(XMLNodeTest_1974, DeeplyNestedNodes_1974) {
    XML_Node root(nullptr, "root", 0);
    XML_Node* current = &root;
    
    std::vector<XML_Node*> nodes;
    for (int i = 0; i < 50; ++i) {
        std::string name = "level" + std::to_string(i);
        XML_Node* child = new XML_Node(current, name, 1);
        current->content.push_back(child);
        nodes.push_back(child);
        current = child;
    }
    
    std::string buffer;
    root.Dump(&buffer);
    EXPECT_NE(buffer.find("level49"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, MultipleChildrenSameName_1974) {
    XML_Node node(nullptr, "root", 0);
    
    for (int i = 0; i < 10; ++i) {
        XML_Node* child = new XML_Node(&node, "item", 1);
        child->ns = "http://example.com";
        child->value = std::to_string(i);
        node.content.push_back(child);
    }
    
    EXPECT_EQ(node.CountNamedElements("http://example.com", "item"), 10u);
    
    for (size_t i = 0; i < 10; ++i) {
        XML_Node* elem = node.GetNamedElement("http://example.com", "item", i);
        ASSERT_NE(elem, nullptr);
        EXPECT_EQ(elem->value, std::to_string(i));
    }
}

TEST_F(XMLNodeTest_1974, WhitespaceOnlyCDataNode_1974) {
    XML_Node node(nullptr, "", 3);
    node.value = "   \t\n\r  ";
    EXPECT_TRUE(node.IsWhitespaceNode());
}

TEST_F(XMLNodeTest_1974, NonWhitespaceCDataNode_1974) {
    XML_Node node(nullptr, "", 3);
    node.value = "  hello  ";
    EXPECT_FALSE(node.IsWhitespaceNode());
}

TEST_F(XMLNodeTest_1974, DumpWhitespaceNode_1974) {
    XML_Node root(nullptr, "root", 0);
    XML_Node* ws = new XML_Node(&root, "", 3);
    ws->value = "   ";
    root.content.push_back(ws);
    
    std::string buffer;
    root.Dump(&buffer);
    EXPECT_NE(buffer.find("whitespace"), std::string::npos);
}

TEST_F(XMLNodeTest_1974, CountNamedElementsEmptyNS_1974) {
    XML_Node node(nullptr, "root", 0);
    XML_Node* child = new XML_Node(&node, "child", 1);
    child->ns = "";
    node.content.push_back(child);
    
    size_t count = node.CountNamedElements("", "child");
    EXPECT_EQ(count, 1u);
}

TEST_F(XMLNodeTest_1974, SetLeafContentValueOnNodeWithExistingContent_1974) {
    XML_Node node(nullptr, "elem", 1);
    XML_Node* text = new XML_Node(&node, "", 3);
    text->value = "old";
    node.content.push_back(text);
    
    node.SetLeafContentValue("new");
    const char* val = node.GetLeafContentValue();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "new");
}
