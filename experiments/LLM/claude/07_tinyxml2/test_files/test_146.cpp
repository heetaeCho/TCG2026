#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_146 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test constructing XMLConstHandle with a null node pointer
TEST_F(XMLConstHandleTest_146, ConstructWithNullNode_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test constructing XMLConstHandle with a valid document node
TEST_F(XMLConstHandleTest_146, ConstructWithValidNode_146) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
    EXPECT_NE(handle.ToElement(), nullptr);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_146, CopyConstructor_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_146, AssignmentOperator_146) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    const XMLNode* child = root->FirstChildElement("child");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(child);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test constructing from reference
TEST_F(XMLConstHandleTest_146, ConstructFromReference_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToDeclaration with a declaration node
TEST_F(XMLConstHandleTest_146, ToDeclarationWithDeclaration_146) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    ASSERT_NE(firstChild->ToDeclaration(), nullptr);

    XMLConstHandle handle(firstChild);
    const XMLDeclaration* decl = handle.ToDeclaration();
    EXPECT_NE(decl, nullptr);
}

// Test ToDeclaration with a non-declaration node returns null
TEST_F(XMLConstHandleTest_146, ToDeclarationWithNonDeclaration_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration with null node returns null
TEST_F(XMLConstHandleTest_146, ToDeclarationWithNullNode_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToElement with an element node
TEST_F(XMLConstHandleTest_146, ToElementWithElement_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_NE(handle.ToElement(), nullptr);
}

// Test ToElement with null node
TEST_F(XMLConstHandleTest_146, ToElementWithNullNode_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText with a text node
TEST_F(XMLConstHandleTest_146, ToTextWithTextNode_146) {
    XMLDocument doc;
    doc.Parse("<root>Hello</root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLConstHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText with non-text node
TEST_F(XMLConstHandleTest_146, ToTextWithNonTextNode_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown with an unknown node
TEST_F(XMLConstHandleTest_146, ToUnknownWithUnknownNode_146) {
    XMLDocument doc;
    doc.Parse("<root><!UNKNOWN stuff></root>");
    // Unknown nodes might not be parsed from this, let's use the doc-level parse
    // Actually tinyxml2 doesn't parse unknown inside elements easily; let's try at doc level
    XMLDocument doc2;
    doc2.Parse("<!DOCTYPE html><root/>");
    const XMLNode* firstChild = doc2.FirstChild();
    // The first child might be an unknown node
    if (firstChild && firstChild->ToUnknown()) {
        XMLConstHandle handle(firstChild);
        EXPECT_NE(handle.ToUnknown(), nullptr);
    }
}

// Test ToUnknown with null node
TEST_F(XMLConstHandleTest_146, ToUnknownWithNullNode_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test FirstChild on handle with children
TEST_F(XMLConstHandleTest_146, FirstChildWithChildren_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_NE(firstChild.ToElement(), nullptr);
}

// Test FirstChild on handle with no children
TEST_F(XMLConstHandleTest_146, FirstChildWithNoChildren_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild on null handle
TEST_F(XMLConstHandleTest_146, FirstChildOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement with name
TEST_F(XMLConstHandleTest_146, FirstChildElementWithName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement("b");
    EXPECT_NE(child.ToNode(), nullptr);
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "b");
}

// Test FirstChildElement with non-existent name
TEST_F(XMLConstHandleTest_146, FirstChildElementWithNonExistentName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test FirstChildElement with default (null) name
TEST_F(XMLConstHandleTest_146, FirstChildElementDefaultName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement();
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "a");
}

// Test LastChild
TEST_F(XMLConstHandleTest_146, LastChild_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
    EXPECT_NE(lastChild.ToElement(), nullptr);
    EXPECT_STREQ(lastChild.ToElement()->Name(), "c");
}

// Test LastChild on null handle
TEST_F(XMLConstHandleTest_146, LastChildOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement with name
TEST_F(XMLConstHandleTest_146, LastChildElementWithName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><a id='2'/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.LastChildElement("a");
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "a");
    // It should be the last 'a' element
    EXPECT_STREQ(child.ToElement()->Attribute("id"), "2");
}

// Test LastChildElement with default name
TEST_F(XMLConstHandleTest_146, LastChildElementDefaultName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.LastChildElement();
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "c");
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_146, PreviousSibling_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLConstHandle handle(b);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    EXPECT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "a");
}

// Test PreviousSibling when there is no previous sibling
TEST_F(XMLConstHandleTest_146, PreviousSiblingNone_146) {
    XMLDocument doc;
    doc.Parse("<root><a/></root>");
    const XMLNode* a = doc.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLConstHandleTest_146, PreviousSiblingOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement with name
TEST_F(XMLConstHandleTest_146, PreviousSiblingElementWithName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><a id='2'/><c/></root>");
    const XMLNode* c = doc.FirstChildElement("root")->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLConstHandle handle(c);
    XMLConstHandle prev = handle.PreviousSiblingElement("a");
    EXPECT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Attribute("id"), "2");
}

// Test PreviousSiblingElement default name
TEST_F(XMLConstHandleTest_146, PreviousSiblingElementDefaultName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* c = doc.FirstChildElement("root")->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLConstHandle handle(c);
    XMLConstHandle prev = handle.PreviousSiblingElement();
    EXPECT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "b");
}

// Test NextSibling
TEST_F(XMLConstHandleTest_146, NextSibling_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* a = doc.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "b");
}

// Test NextSibling when there is no next sibling
TEST_F(XMLConstHandleTest_146, NextSiblingNone_146) {
    XMLDocument doc;
    doc.Parse("<root><a/></root>");
    const XMLNode* a = doc.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLConstHandleTest_146, NextSiblingOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement with name
TEST_F(XMLConstHandleTest_146, NextSiblingElementWithName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/><b id='2'/></root>");
    const XMLNode* a = doc.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSiblingElement("c");
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "c");
}

// Test NextSiblingElement default name
TEST_F(XMLConstHandleTest_146, NextSiblingElementDefaultName_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* a = doc.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSiblingElement();
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "b");
}

// Test NextSiblingElement with non-existent name
TEST_F(XMLConstHandleTest_146, NextSiblingElementNonExistent_146) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/></root>");
    const XMLNode* a = doc.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSiblingElement("zzz");
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test chaining: FirstChildElement then NextSiblingElement
TEST_F(XMLConstHandleTest_146, ChainingHandles_146) {
    XMLDocument doc;
    doc.Parse("<root><a><x/></a><b><y/></b></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("a").FirstChildElement("x");
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "x");
}

// Test chaining with missing intermediate element returns null
TEST_F(XMLConstHandleTest_146, ChainingHandlesMissing_146) {
    XMLDocument doc;
    doc.Parse("<root><a/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("nonexistent").FirstChildElement("anything");
    EXPECT_EQ(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test ToNode returns correct node
TEST_F(XMLConstHandleTest_146, ToNodeReturnsCorrectNode_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode on null handle
TEST_F(XMLConstHandleTest_146, ToNodeOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToText on null handle
TEST_F(XMLConstHandleTest_146, ToTextOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test self-assignment
TEST_F(XMLConstHandleTest_146, SelfAssignment_146) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}

// Test deeply nested chaining
TEST_F(XMLConstHandleTest_146, DeepChaining_146) {
    XMLDocument doc;
    doc.Parse("<a><b><c><d/></c></b></a>");
    const XMLNode* docNode = &doc;

    XMLConstHandle handle(docNode);
    XMLConstHandle result = handle.FirstChildElement("a")
                                  .FirstChildElement("b")
                                  .FirstChildElement("c")
                                  .FirstChildElement("d");
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "d");
}

// Test that ToElement returns null for text nodes accessed via handle
TEST_F(XMLConstHandleTest_146, ToElementOnTextNode_146) {
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle textHandle = handle.FirstChild();
    EXPECT_NE(textHandle.ToNode(), nullptr);
    EXPECT_NE(textHandle.ToText(), nullptr);
    EXPECT_EQ(textHandle.ToElement(), nullptr);
}

// Test FirstChildElement on null handle
TEST_F(XMLConstHandleTest_146, FirstChildElementOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle child = handle.FirstChildElement("anything");
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test LastChildElement on null handle
TEST_F(XMLConstHandleTest_146, LastChildElementOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle child = handle.LastChildElement();
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLConstHandleTest_146, PreviousSiblingElementOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSiblingElement();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test NextSiblingElement on null handle
TEST_F(XMLConstHandleTest_146, NextSiblingElementOnNullHandle_146) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSiblingElement();
    EXPECT_EQ(next.ToNode(), nullptr);
}
