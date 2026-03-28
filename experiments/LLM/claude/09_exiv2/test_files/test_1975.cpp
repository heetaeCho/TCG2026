#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "XMLParserAdapter.hpp"

class XMLNodeTest_1975 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(XMLNodeTest_1975, ConstructorWithCStringInitializesFields_1975) {
    XML_Node node(nullptr, "testNode", kElemNode);
    EXPECT_EQ(node.kind, kElemNode);
    EXPECT_EQ(node.name, "testNode");
    EXPECT_EQ(node.nsPrefixLen, 0u);
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_TRUE(node.attrs.empty());
    EXPECT_TRUE(node.content.empty());
}

TEST_F(XMLNodeTest_1975, ConstructorWithStdStringInitializesFields_1975) {
    std::string name = "myElement";
    XML_Node node(nullptr, name, kCDataNode);
    EXPECT_EQ(node.kind, kCDataNode);
    EXPECT_EQ(node.name, "myElement");
    EXPECT_EQ(node.nsPrefixLen, 0u);
    EXPECT_EQ(node.parent, nullptr);
}

TEST_F(XMLNodeTest_1975, ConstructorWithParentPointer_1975) {
    XML_Node parent(nullptr, "parent", kElemNode);
    XML_Node child(&parent, "child", kElemNode);
    EXPECT_EQ(child.parent, &parent);
}

// ==================== Serialize Tests ====================

TEST_F(XMLNodeTest_1975, SerializeEmptyElement_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<root/>");
}

TEST_F(XMLNodeTest_1975, SerializeElementWithContent_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* child = new XML_Node(&node, "child", kElemNode);
    node.content.push_back(child);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<root><child/></root>");
}

TEST_F(XMLNodeTest_1975, SerializeElementWithTextContent_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* text = new XML_Node(&node, "", kCDataNode);
    text->value = "Hello World";
    node.content.push_back(text);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<root>Hello World</root>");
}

TEST_F(XMLNodeTest_1975, SerializeElementWithAttribute_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* attr = new XML_Node(&node, "id", kAttrNode);
    attr->value = "123";
    node.attrs.push_back(attr);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<root id=\"123\"/>");
}

TEST_F(XMLNodeTest_1975, SerializeElementWithAttributeAndContent_1975) {
    XML_Node node(nullptr, "div", kElemNode);
    XML_Node* attr = new XML_Node(&node, "class", kAttrNode);
    attr->value = "main";
    node.attrs.push_back(attr);
    XML_Node* text = new XML_Node(&node, "", kCDataNode);
    text->value = "content";
    node.content.push_back(text);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<div class=\"main\">content</div>");
}

TEST_F(XMLNodeTest_1975, SerializeElementWithMultipleAttributes_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    XML_Node* attr1 = new XML_Node(&node, "a", kAttrNode);
    attr1->value = "1";
    node.attrs.push_back(attr1);
    XML_Node* attr2 = new XML_Node(&node, "b", kAttrNode);
    attr2->value = "2";
    node.attrs.push_back(attr2);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<elem a=\"1\" b=\"2\"/>");
}

TEST_F(XMLNodeTest_1975, SerializeCDataNode_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "some text data";
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "some text data");
}

TEST_F(XMLNodeTest_1975, SerializePINode_1975) {
    XML_Node node(nullptr, "", kPINode);
    node.value = "<?xml version=\"1.0\"?>";
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<?xml version=\"1.0\"?>");
}

TEST_F(XMLNodeTest_1975, SerializeNestedElements_1975) {
    XML_Node root(nullptr, "a", kElemNode);
    XML_Node* b = new XML_Node(&root, "b", kElemNode);
    XML_Node* c = new XML_Node(b, "c", kElemNode);
    b->content.push_back(c);
    root.content.push_back(b);
    std::string buffer;
    root.Serialize(&buffer);
    EXPECT_EQ(buffer, "<a><b><c/></b></a>");
}

TEST_F(XMLNodeTest_1975, SerializeDefaultNamespaceHack_1975) {
    XML_Node node(nullptr, "_dflt_:element", kElemNode);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<element/>");
}

TEST_F(XMLNodeTest_1975, SerializeDefaultNamespaceHackWithContent_1975) {
    XML_Node node(nullptr, "_dflt_:root", kElemNode);
    XML_Node* text = new XML_Node(&node, "", kCDataNode);
    text->value = "data";
    node.content.push_back(text);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "<root>data</root>");
}

// ==================== IsWhitespaceNode Tests ====================

TEST_F(XMLNodeTest_1975, IsWhitespaceNodeWithSpaces_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "   ";
    EXPECT_TRUE(node.IsWhitespaceNode());
}

TEST_F(XMLNodeTest_1975, IsWhitespaceNodeWithTabs_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "\t\t";
    EXPECT_TRUE(node.IsWhitespaceNode());
}

TEST_F(XMLNodeTest_1975, IsWhitespaceNodeWithNewlines_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "\n\n";
    EXPECT_TRUE(node.IsWhitespaceNode());
}

TEST_F(XMLNodeTest_1975, IsWhitespaceNodeWithText_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "hello";
    EXPECT_FALSE(node.IsWhitespaceNode());
}

TEST_F(XMLNodeTest_1975, IsWhitespaceNodeEmpty_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "";
    EXPECT_TRUE(node.IsWhitespaceNode());
}

// ==================== IsLeafContentNode Tests ====================

TEST_F(XMLNodeTest_1975, IsLeafContentNodeCData_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "text";
    EXPECT_TRUE(node.IsLeafContentNode());
}

TEST_F(XMLNodeTest_1975, IsLeafContentNodeElement_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    EXPECT_FALSE(node.IsLeafContentNode());
}

// ==================== IsEmptyLeafNode Tests ====================

TEST_F(XMLNodeTest_1975, IsEmptyLeafNodeEmpty_1975) {
    XML_Node node(nullptr, "leaf", kElemNode);
    EXPECT_TRUE(node.IsEmptyLeafNode());
}

TEST_F(XMLNodeTest_1975, IsEmptyLeafNodeWithContent_1975) {
    XML_Node node(nullptr, "leaf", kElemNode);
    XML_Node* child = new XML_Node(&node, "", kCDataNode);
    child->value = "text";
    node.content.push_back(child);
    EXPECT_FALSE(node.IsEmptyLeafNode());
}

// ==================== GetAttrValue / SetAttrValue Tests ====================

TEST_F(XMLNodeTest_1975, SetAndGetAttrValue_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    node.SetAttrValue("myattr", "myvalue");
    XMP_StringPtr val = node.GetAttrValue("myattr");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "myvalue");
}

TEST_F(XMLNodeTest_1975, GetAttrValueNonExistent_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    XMP_StringPtr val = node.GetAttrValue("nonexistent");
    EXPECT_EQ(val, nullptr);
}

TEST_F(XMLNodeTest_1975, SetAttrValueOverwrite_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    node.SetAttrValue("key", "value1");
    node.SetAttrValue("key", "value2");
    XMP_StringPtr val = node.GetAttrValue("key");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "value2");
}

TEST_F(XMLNodeTest_1975, SetMultipleAttributes_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    node.SetAttrValue("a", "1");
    node.SetAttrValue("b", "2");
    node.SetAttrValue("c", "3");
    EXPECT_STREQ(node.GetAttrValue("a"), "1");
    EXPECT_STREQ(node.GetAttrValue("b"), "2");
    EXPECT_STREQ(node.GetAttrValue("c"), "3");
}

// ==================== GetLeafContentValue / SetLeafContentValue Tests ====================

TEST_F(XMLNodeTest_1975, SetAndGetLeafContentValue_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    node.SetLeafContentValue("leaf value");
    XMP_StringPtr val = node.GetLeafContentValue();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "leaf value");
}

TEST_F(XMLNodeTest_1975, GetLeafContentValueEmpty_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    XMP_StringPtr val = node.GetLeafContentValue();
    // Could be nullptr or empty string for empty element
    if (val != nullptr) {
        EXPECT_STREQ(val, "");
    }
}

TEST_F(XMLNodeTest_1975, SetLeafContentValueOverwrite_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    node.SetLeafContentValue("first");
    node.SetLeafContentValue("second");
    XMP_StringPtr val = node.GetLeafContentValue();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "second");
}

// ==================== CountNamedElements Tests ====================

TEST_F(XMLNodeTest_1975, CountNamedElementsNone_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    EXPECT_EQ(node.CountNamedElements("http://ns", "child"), 0u);
}

TEST_F(XMLNodeTest_1975, CountNamedElementsOne_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* child = new XML_Node(&node, "child", kElemNode);
    child->ns = "http://ns";
    child->name = "child";
    node.content.push_back(child);
    EXPECT_EQ(node.CountNamedElements("http://ns", "child"), 1u);
}

TEST_F(XMLNodeTest_1975, CountNamedElementsMultiple_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    for (int i = 0; i < 3; i++) {
        XML_Node* child = new XML_Node(&node, "child", kElemNode);
        child->ns = "http://ns";
        child->name = "child";
        node.content.push_back(child);
    }
    EXPECT_EQ(node.CountNamedElements("http://ns", "child"), 3u);
}

// ==================== GetNamedElement Tests ====================

TEST_F(XMLNodeTest_1975, GetNamedElementExists_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* child = new XML_Node(&node, "child", kElemNode);
    child->ns = "http://ns";
    child->name = "child";
    node.content.push_back(child);
    XML_Node* result = node.GetNamedElement("http://ns", "child", 0);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, child);
}

TEST_F(XMLNodeTest_1975, GetNamedElementNotExists_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* result = node.GetNamedElement("http://ns", "nonexistent", 0);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLNodeTest_1975, GetNamedElementByIndex_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* child1 = new XML_Node(&node, "child", kElemNode);
    child1->ns = "http://ns";
    child1->name = "child";
    child1->value = "first";
    node.content.push_back(child1);

    XML_Node* child2 = new XML_Node(&node, "child", kElemNode);
    child2->ns = "http://ns";
    child2->name = "child";
    child2->value = "second";
    node.content.push_back(child2);

    XML_Node* result0 = node.GetNamedElement("http://ns", "child", 0);
    EXPECT_EQ(result0, child1);

    XML_Node* result1 = node.GetNamedElement("http://ns", "child", 1);
    EXPECT_EQ(result1, child2);
}

// ==================== RemoveAttrs Tests ====================

TEST_F(XMLNodeTest_1975, RemoveAttrs_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    node.SetAttrValue("a", "1");
    node.SetAttrValue("b", "2");
    EXPECT_FALSE(node.attrs.empty());
    node.RemoveAttrs();
    EXPECT_TRUE(node.attrs.empty());
}

TEST_F(XMLNodeTest_1975, RemoveAttrsOnEmpty_1975) {
    XML_Node node(nullptr, "elem", kElemNode);
    EXPECT_TRUE(node.attrs.empty());
    node.RemoveAttrs();
    EXPECT_TRUE(node.attrs.empty());
}

// ==================== RemoveContent Tests ====================

TEST_F(XMLNodeTest_1975, RemoveContent_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* child = new XML_Node(&node, "child", kElemNode);
    node.content.push_back(child);
    EXPECT_FALSE(node.content.empty());
    node.RemoveContent();
    EXPECT_TRUE(node.content.empty());
}

TEST_F(XMLNodeTest_1975, RemoveContentOnEmpty_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    EXPECT_TRUE(node.content.empty());
    node.RemoveContent();
    EXPECT_TRUE(node.content.empty());
}

// ==================== ClearNode Tests ====================

TEST_F(XMLNodeTest_1975, ClearNodeRemovesEverything_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    node.SetAttrValue("attr", "val");
    XML_Node* child = new XML_Node(&node, "child", kElemNode);
    node.content.push_back(child);
    node.ns = "http://ns";
    node.value = "some value";

    node.ClearNode();

    EXPECT_TRUE(node.attrs.empty());
    EXPECT_TRUE(node.content.empty());
}

// ==================== Dump Tests ====================

TEST_F(XMLNodeTest_1975, DumpProducesOutput_1975) {
    XML_Node node(nullptr, "root", kElemNode);
    XML_Node* child = new XML_Node(&node, "child", kElemNode);
    node.content.push_back(child);
    std::string buffer;
    node.Dump(&buffer);
    EXPECT_FALSE(buffer.empty());
}

// ==================== Complex Serialize Tests ====================

TEST_F(XMLNodeTest_1975, SerializeComplexTree_1975) {
    XML_Node root(nullptr, "html", kElemNode);

    XML_Node* body = new XML_Node(&root, "body", kElemNode);
    root.content.push_back(body);

    XML_Node* bodyAttr = new XML_Node(body, "class", kAttrNode);
    bodyAttr->value = "main";
    body->attrs.push_back(bodyAttr);

    XML_Node* p = new XML_Node(body, "p", kElemNode);
    body->content.push_back(p);

    XML_Node* text = new XML_Node(p, "", kCDataNode);
    text->value = "Hello";
    p->content.push_back(text);

    std::string buffer;
    root.Serialize(&buffer);
    EXPECT_EQ(buffer, "<html><body class=\"main\"><p>Hello</p></body></html>");
}

TEST_F(XMLNodeTest_1975, SerializeMultipleChildElements_1975) {
    XML_Node root(nullptr, "ul", kElemNode);

    for (int i = 0; i < 3; i++) {
        XML_Node* li = new XML_Node(&root, "li", kElemNode);
        XML_Node* text = new XML_Node(li, "", kCDataNode);
        text->value = "item";
        li->content.push_back(text);
        root.content.push_back(li);
    }

    std::string buffer;
    root.Serialize(&buffer);
    EXPECT_EQ(buffer, "<ul><li>item</li><li>item</li><li>item</li></ul>");
}

TEST_F(XMLNodeTest_1975, SerializeAttrNodeAlone_1975) {
    XML_Node attr(nullptr, "href", kAttrNode);
    attr.value = "http://example.com";
    std::string buffer;
    attr.Serialize(&buffer);
    EXPECT_EQ(buffer, " href=\"http://example.com\"");
}

TEST_F(XMLNodeTest_1975, SerializeEmptyValueCData_1975) {
    XML_Node node(nullptr, "", kCDataNode);
    node.value = "";
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "");
}

TEST_F(XMLNodeTest_1975, SerializeDefaultNamespaceAttr_1975) {
    XML_Node attr(nullptr, "_dflt_:myattr", kAttrNode);
    attr.value = "val";
    std::string buffer;
    attr.Serialize(&buffer);
    EXPECT_EQ(buffer, " myattr=\"val\"");
}

// ==================== Destructor Test ====================

TEST_F(XMLNodeTest_1975, DestructorDoesNotCrash_1975) {
    XML_Node* node = new XML_Node(nullptr, "root", kElemNode);
    XML_Node* child = new XML_Node(node, "child", kElemNode);
    node->content.push_back(child);
    XML_Node* attr = new XML_Node(node, "attr", kAttrNode);
    attr->value = "val";
    node->attrs.push_back(attr);
    EXPECT_NO_THROW(delete node);
}

// ==================== Edge Cases ====================

TEST_F(XMLNodeTest_1975, SerializeElementWithEmptyName_1975) {
    XML_Node node(nullptr, "", kElemNode);
    std::string buffer;
    node.Serialize(&buffer);
    EXPECT_EQ(buffer, "</>");
}

TEST_F(XMLNodeTest_1975, SerializeMixedContent_1975) {
    XML_Node root(nullptr, "p", kElemNode);

    XML_Node* text1 = new XML_Node(&root, "", kCDataNode);
    text1->value = "Hello ";
    root.content.push_back(text1);

    XML_Node* bold = new XML_Node(&root, "b", kElemNode);
    XML_Node* boldText = new XML_Node(bold, "", kCDataNode);
    boldText->value = "world";
    bold->content.push_back(boldText);
    root.content.push_back(bold);

    XML_Node* text2 = new XML_Node(&root, "", kCDataNode);
    text2->value = "!";
    root.content.push_back(text2);

    std::string buffer;
    root.Serialize(&buffer);
    EXPECT_EQ(buffer, "<p>Hello <b>world</b>!</p>");
}
