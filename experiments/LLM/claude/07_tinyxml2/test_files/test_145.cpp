#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_145 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test constructing XMLConstHandle from a null node pointer
TEST_F(XMLConstHandleTest_145, ConstructFromNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test constructing XMLConstHandle from a valid node pointer
TEST_F(XMLConstHandleTest_145, ConstructFromValidNode_145) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLConstHandle from a node reference
TEST_F(XMLConstHandleTest_145, ConstructFromNodeReference_145) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_145, CopyConstructor_145) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_145, AssignmentOperator_145) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->RootElement();
    const XMLElement* child = root->FirstChildElement();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(child);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test ToUnknown with null node returns null
TEST_F(XMLConstHandleTest_145, ToUnknownWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToUnknown with non-unknown node returns null
TEST_F(XMLConstHandleTest_145, ToUnknownWithNonUnknownNode_145) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToElement with a valid element
TEST_F(XMLConstHandleTest_145, ToElementWithValidElement_145) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement with null node
TEST_F(XMLConstHandleTest_145, ToElementWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText with null node
TEST_F(XMLConstHandleTest_145, ToTextWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText with a text node
TEST_F(XMLConstHandleTest_145, ToTextWithTextNode_145) {
    doc->Parse("<root>Hello</root>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLConstHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToDeclaration with null node
TEST_F(XMLConstHandleTest_145, ToDeclarationWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration with a declaration node
TEST_F(XMLConstHandleTest_145, ToDeclarationWithDeclarationNode_145) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLConstHandle handle(firstChild);
    const XMLDeclaration* decl = handle.ToDeclaration();
    EXPECT_NE(decl, nullptr);
}

// Test FirstChild on handle with valid node that has children
TEST_F(XMLConstHandleTest_145, FirstChildWithChildren_145) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_EQ(firstChild.ToNode(), root->FirstChild());
}

// Test FirstChild on handle with null node
TEST_F(XMLConstHandleTest_145, FirstChildWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild on handle with node that has no children
TEST_F(XMLConstHandleTest_145, FirstChildWithNoChildren_145) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement with name
TEST_F(XMLConstHandleTest_145, FirstChildElementWithName_145) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement("beta");
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "beta");
}

// Test FirstChildElement with no name (default)
TEST_F(XMLConstHandleTest_145, FirstChildElementDefault_145) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement();
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "alpha");
}

// Test FirstChildElement with non-existent name
TEST_F(XMLConstHandleTest_145, FirstChildElementNonExistent_145) {
    doc->Parse("<root><alpha/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement("gamma");
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test LastChild on handle with valid node
TEST_F(XMLConstHandleTest_145, LastChildWithChildren_145) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
    EXPECT_EQ(lastChild.ToNode(), root->LastChild());
}

// Test LastChild on null handle
TEST_F(XMLConstHandleTest_145, LastChildWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement with name
TEST_F(XMLConstHandleTest_145, LastChildElementWithName_145) {
    doc->Parse("<root><alpha/><beta/><alpha/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.LastChildElement("alpha");
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "alpha");
    // Should be the last "alpha" element
    EXPECT_EQ(child.ToNode(), root->LastChildElement("alpha"));
}

// Test LastChildElement with no name
TEST_F(XMLConstHandleTest_145, LastChildElementDefault_145) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.LastChildElement();
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "beta");
}

// Test PreviousSibling on handle
TEST_F(XMLConstHandleTest_145, PreviousSibling_145) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* child2 = root->LastChild();
    ASSERT_NE(child2, nullptr);

    XMLConstHandle handle(child2);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    EXPECT_EQ(prev.ToNode(), root->FirstChild());
}

// Test PreviousSibling on null handle
TEST_F(XMLConstHandleTest_145, PreviousSiblingWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on first child (no previous sibling)
TEST_F(XMLConstHandleTest_145, PreviousSiblingOnFirstChild_145) {
    doc->Parse("<root><child1/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* child1 = root->FirstChild();
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement with name
TEST_F(XMLConstHandleTest_145, PreviousSiblingElementWithName_145) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLElement* gamma = root->LastChildElement("gamma");
    ASSERT_NE(gamma, nullptr);

    XMLConstHandle handle(gamma);
    XMLConstHandle prev = handle.PreviousSiblingElement("alpha");
    EXPECT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "alpha");
}

// Test PreviousSiblingElement default
TEST_F(XMLConstHandleTest_145, PreviousSiblingElementDefault_145) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLElement* gamma = root->LastChildElement("gamma");
    ASSERT_NE(gamma, nullptr);

    XMLConstHandle handle(gamma);
    XMLConstHandle prev = handle.PreviousSiblingElement();
    EXPECT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "beta");
}

// Test NextSibling on handle
TEST_F(XMLConstHandleTest_145, NextSibling_145) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* child1 = root->FirstChild();
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
    EXPECT_EQ(next.ToNode(), root->LastChild());
}

// Test NextSibling on null handle
TEST_F(XMLConstHandleTest_145, NextSiblingWithNullNode_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling on last child (no next sibling)
TEST_F(XMLConstHandleTest_145, NextSiblingOnLastChild_145) {
    doc->Parse("<root><child1/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* child1 = root->LastChild();
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement with name
TEST_F(XMLConstHandleTest_145, NextSiblingElementWithName_145) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLElement* alpha = root->FirstChildElement("alpha");
    ASSERT_NE(alpha, nullptr);

    XMLConstHandle handle(alpha);
    XMLConstHandle next = handle.NextSiblingElement("gamma");
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "gamma");
}

// Test NextSiblingElement default
TEST_F(XMLConstHandleTest_145, NextSiblingElementDefault_145) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLElement* alpha = root->FirstChildElement("alpha");
    ASSERT_NE(alpha, nullptr);

    XMLConstHandle handle(alpha);
    XMLConstHandle next = handle.NextSiblingElement();
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "beta");
}

// Test ToNode on null handle
TEST_F(XMLConstHandleTest_145, ToNodeWithNullHandle_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToNode on valid handle
TEST_F(XMLConstHandleTest_145, ToNodeWithValidHandle_145) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test chaining: FirstChildElement then NextSiblingElement
TEST_F(XMLConstHandleTest_145, ChainingNavigation_145) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("a");
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "a");

    result = result.NextSiblingElement();
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "b");

    result = result.NextSiblingElement();
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "c");

    result = result.NextSiblingElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test chaining from null propagates null
TEST_F(XMLConstHandleTest_145, ChainingFromNullPropagatesNull_145) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChild();
    EXPECT_EQ(result.ToNode(), nullptr);

    result = result.FirstChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);

    result = result.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);

    result = result.NextSiblingElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test ToElement on non-element node returns null
TEST_F(XMLConstHandleTest_145, ToElementOnNonElementNode_145) {
    doc->Parse("<root>Hello</root>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLConstHandle handle(textNode);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText on non-text node returns null
TEST_F(XMLConstHandleTest_145, ToTextOnNonTextNode_145) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test deep navigation: root > child > grandchild
TEST_F(XMLConstHandleTest_145, DeepNavigation_145) {
    doc->Parse("<root><child><grandchild/></child></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle grandchild = handle.FirstChildElement("child").FirstChildElement("grandchild");
    EXPECT_NE(grandchild.ToElement(), nullptr);
    EXPECT_STREQ(grandchild.ToElement()->Name(), "grandchild");
}

// Test deep navigation with missing intermediate returns null
TEST_F(XMLConstHandleTest_145, DeepNavigationMissingIntermediate_145) {
    doc->Parse("<root><child/></root>");
    const XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("nonexistent").FirstChildElement("grandchild");
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test handle constructed from XMLDocument node
TEST_F(XMLConstHandleTest_145, HandleFromDocument_145) {
    doc->Parse("<root/>");
    const XMLNode* docNode = static_cast<const XMLNode*>(doc);

    XMLConstHandle handle(docNode);
    EXPECT_EQ(handle.ToNode(), docNode);

    XMLConstHandle rootHandle = handle.FirstChildElement("root");
    EXPECT_NE(rootHandle.ToElement(), nullptr);
    EXPECT_STREQ(rootHandle.ToElement()->Name(), "root");
}

// Test self-assignment
TEST_F(XMLConstHandleTest_145, SelfAssignment_145) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}
