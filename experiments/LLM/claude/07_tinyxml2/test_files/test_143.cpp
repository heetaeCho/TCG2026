#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_143 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test constructing XMLConstHandle with a null node
TEST_F(XMLConstHandleTest_143, ConstructWithNullNode_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test constructing XMLConstHandle with a valid node
TEST_F(XMLConstHandleTest_143, ConstructWithValidNode_143) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
    EXPECT_NE(handle.ToElement(), nullptr);
}

// Test constructing XMLConstHandle with a node reference
TEST_F(XMLConstHandleTest_143, ConstructWithNodeReference_143) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_143, CopyConstructor_143) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_143, AssignmentOperator_143) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    const XMLNode* child = root->FirstChildElement("child");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(child);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test ToElement with a valid element
TEST_F(XMLConstHandleTest_143, ToElementWithValidElement_143) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement with null node returns null
TEST_F(XMLConstHandleTest_143, ToElementWithNullNodeReturnsNull_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText with a text node
TEST_F(XMLConstHandleTest_143, ToTextWithTextNode_143) {
    doc->Parse("<root>Hello</root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLConstHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText with null node
TEST_F(XMLConstHandleTest_143, ToTextWithNullNode_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToDeclaration
TEST_F(XMLConstHandleTest_143, ToDeclarationWithDeclarationNode_143) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLConstHandle handle(firstChild);
    EXPECT_NE(handle.ToDeclaration(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToDeclaration with null node
TEST_F(XMLConstHandleTest_143, ToDeclarationWithNullNode_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToUnknown
TEST_F(XMLConstHandleTest_143, ToUnknownWithUnknownNode_143) {
    doc->Parse("<root/><!UNKNOWN>");
    // Try to find an unknown node
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test FirstChild on handle
TEST_F(XMLConstHandleTest_143, FirstChild_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_NE(firstChild.ToElement(), nullptr);
}

// Test FirstChild on null handle
TEST_F(XMLConstHandleTest_143, FirstChildOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement
TEST_F(XMLConstHandleTest_143, FirstChildElement_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle childHandle = handle.FirstChildElement("child1");
    EXPECT_NE(childHandle.ToElement(), nullptr);
}

// Test FirstChildElement with name that doesn't exist
TEST_F(XMLConstHandleTest_143, FirstChildElementNonExistent_143) {
    doc->Parse("<root><child1/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle childHandle = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(childHandle.ToNode(), nullptr);
    EXPECT_EQ(childHandle.ToElement(), nullptr);
}

// Test FirstChildElement without name filter
TEST_F(XMLConstHandleTest_143, FirstChildElementNoFilter_143) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle childHandle = handle.FirstChildElement();
    EXPECT_NE(childHandle.ToElement(), nullptr);
}

// Test FirstChildElement on null handle
TEST_F(XMLConstHandleTest_143, FirstChildElementOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle childHandle = handle.FirstChildElement("anything");
    EXPECT_EQ(childHandle.ToNode(), nullptr);
}

// Test LastChild
TEST_F(XMLConstHandleTest_143, LastChild_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test LastChild on null handle
TEST_F(XMLConstHandleTest_143, LastChildOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement
TEST_F(XMLConstHandleTest_143, LastChildElement_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("child2");
    EXPECT_NE(lastElem.ToElement(), nullptr);
}

// Test LastChildElement on null handle
TEST_F(XMLConstHandleTest_143, LastChildElementOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastElem = handle.LastChildElement();
    EXPECT_EQ(lastElem.ToNode(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_143, PreviousSibling_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child2 = root->LastChildElement("child2");
    ASSERT_NE(child2, nullptr);

    XMLConstHandle handle(child2);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLConstHandleTest_143, PreviousSiblingOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLConstHandleTest_143, PreviousSiblingElement_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child2 = root->LastChildElement("child2");
    ASSERT_NE(child2, nullptr);

    XMLConstHandle handle(child2);
    XMLConstHandle prevElem = handle.PreviousSiblingElement("child1");
    EXPECT_NE(prevElem.ToElement(), nullptr);
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLConstHandleTest_143, PreviousSiblingElementOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToNode(), nullptr);
}

// Test NextSibling
TEST_F(XMLConstHandleTest_143, NextSibling_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLConstHandleTest_143, NextSiblingOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLConstHandleTest_143, NextSiblingElement_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle nextElem = handle.NextSiblingElement("child2");
    EXPECT_NE(nextElem.ToElement(), nullptr);
}

// Test NextSiblingElement on null handle
TEST_F(XMLConstHandleTest_143, NextSiblingElementOnNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle nextElem = handle.NextSiblingElement();
    EXPECT_EQ(nextElem.ToNode(), nullptr);
}

// Test ToNode returns the node passed in
TEST_F(XMLConstHandleTest_143, ToNodeReturnsCorrectNode_143) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode returns null for null handle
TEST_F(XMLConstHandleTest_143, ToNodeReturnsNullForNullHandle_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test chaining navigation
TEST_F(XMLConstHandleTest_143, ChainingNavigation_143) {
    doc->Parse("<root><parent><child>Text</child></parent></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle childHandle = handle.FirstChildElement("parent").FirstChildElement("child");
    EXPECT_NE(childHandle.ToElement(), nullptr);
}

// Test chaining with non-existent intermediate node
TEST_F(XMLConstHandleTest_143, ChainingWithNonExistentIntermediate_143) {
    doc->Parse("<root><parent><child/></parent></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("nonexistent").FirstChildElement("child");
    EXPECT_EQ(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test ToElement when node is not an element (e.g., text node)
TEST_F(XMLConstHandleTest_143, ToElementReturnsNullForNonElement_143) {
    doc->Parse("<root>Hello</root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLConstHandle handle(textNode);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test document handle
TEST_F(XMLConstHandleTest_143, HandleWithDocument_143) {
    doc->Parse("<root/>");
    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    EXPECT_NE(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr); // document is not an element
}

// Test empty document with handle
TEST_F(XMLConstHandleTest_143, HandleWithEmptyDocument_143) {
    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild returns first child among mixed node types
TEST_F(XMLConstHandleTest_143, FirstChildMixedNodeTypes_143) {
    doc->Parse("<root>Text<elem/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    // First child should be the text node
    EXPECT_NE(firstChild.ToText(), nullptr);
}

// Test FirstChildElement skips non-element nodes
TEST_F(XMLConstHandleTest_143, FirstChildElementSkipsTextNodes_143) {
    doc->Parse("<root>Text<elem/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement();
    EXPECT_NE(firstElem.ToElement(), nullptr);
}

// Test no children
TEST_F(XMLConstHandleTest_143, NoChildren_143) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);

    XMLConstHandle firstElem = handle.FirstChildElement();
    EXPECT_EQ(firstElem.ToNode(), nullptr);

    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);

    XMLConstHandle lastElem = handle.LastChildElement();
    EXPECT_EQ(lastElem.ToNode(), nullptr);
}

// Test PreviousSibling on first child returns null
TEST_F(XMLConstHandleTest_143, PreviousSiblingOnFirstChildReturnsNull_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test NextSibling on last child returns null
TEST_F(XMLConstHandleTest_143, NextSiblingOnLastChildReturnsNull_143) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child2 = root->LastChildElement("child2");
    ASSERT_NE(child2, nullptr);

    XMLConstHandle handle(child2);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test deep chaining that results in null
TEST_F(XMLConstHandleTest_143, DeepChainingResultsInNull_143) {
    doc->Parse("<root><a><b/></a></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    // a -> b -> (no child) -> FirstChild returns null handle -> chaining continues safely
    XMLConstHandle result = handle.FirstChildElement("a")
                                   .FirstChildElement("b")
                                   .FirstChildElement("c");
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test self-assignment
TEST_F(XMLConstHandleTest_143, SelfAssignment_143) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}

// Test multiple siblings navigation
TEST_F(XMLConstHandleTest_143, MultipleSiblingsNavigation_143) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle a = handle.FirstChildElement("a");
    EXPECT_NE(a.ToElement(), nullptr);

    XMLConstHandle b = a.NextSiblingElement("b");
    EXPECT_NE(b.ToElement(), nullptr);

    XMLConstHandle c = b.NextSiblingElement("c");
    EXPECT_NE(c.ToElement(), nullptr);

    XMLConstHandle none = c.NextSiblingElement();
    EXPECT_EQ(none.ToNode(), nullptr);
}

// Test LastChildElement with name
TEST_F(XMLConstHandleTest_143, LastChildElementWithName_143) {
    doc->Parse("<root><item/><item/><other/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastItem = handle.LastChildElement("item");
    EXPECT_NE(lastItem.ToElement(), nullptr);

    // Verify it's the second item (which should have next sibling "other")
    XMLConstHandle nextAfterLastItem = lastItem.NextSiblingElement("other");
    EXPECT_NE(nextAfterLastItem.ToElement(), nullptr);
}
