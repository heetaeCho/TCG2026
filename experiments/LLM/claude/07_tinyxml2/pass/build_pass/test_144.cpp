#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_144 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
        // Build a small document tree for testing
        // <root><child1>text1</child1><child2/><child3/></root>
        doc.Parse("<root><child1>text1</child1><child2/><child3/></root>");
    }
};

// Test construction from null node pointer
TEST_F(XMLConstHandleTest_144, ConstructFromNullPointer_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToNode());
    EXPECT_EQ(nullptr, handle.ToElement());
    EXPECT_EQ(nullptr, handle.ToText());
    EXPECT_EQ(nullptr, handle.ToUnknown());
    EXPECT_EQ(nullptr, handle.ToDeclaration());
}

// Test construction from valid node pointer
TEST_F(XMLConstHandleTest_144, ConstructFromValidPointer_144) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(root, handle.ToNode());
}

// Test construction from node reference
TEST_F(XMLConstHandleTest_144, ConstructFromReference_144) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle(*root);
    EXPECT_EQ(root, handle.ToNode());
}

// Test copy constructor
TEST_F(XMLConstHandleTest_144, CopyConstructor_144) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test assignment operator
TEST_F(XMLConstHandleTest_144, AssignmentOperator_144) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(static_cast<const XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(root, handle2.ToNode());
}

// Test ToElement on element node
TEST_F(XMLConstHandleTest_144, ToElementOnElementNode_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_NE(nullptr, handle.ToElement());
    EXPECT_STREQ("root", handle.ToElement()->Name());
}

// Test ToElement on null handle
TEST_F(XMLConstHandleTest_144, ToElementOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToElement());
}

// Test ToText on text node
TEST_F(XMLConstHandleTest_144, ToTextOnTextNode_144) {
    const XMLElement* child1 = doc.RootElement()->FirstChildElement("child1");
    ASSERT_NE(nullptr, child1);
    const XMLNode* textNode = child1->FirstChild();
    ASSERT_NE(nullptr, textNode);
    XMLConstHandle handle(textNode);
    EXPECT_NE(nullptr, handle.ToText());
}

// Test ToText on non-text node returns null
TEST_F(XMLConstHandleTest_144, ToTextOnNonTextNode_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(nullptr, handle.ToText());
}

// Test ToText on null handle returns null
TEST_F(XMLConstHandleTest_144, ToTextOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToText());
}

// Test FirstChild
TEST_F(XMLConstHandleTest_144, FirstChild_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(nullptr, firstChild.ToNode());
    EXPECT_NE(nullptr, firstChild.ToElement());
    EXPECT_STREQ("child1", firstChild.ToElement()->Name());
}

// Test FirstChild on null handle
TEST_F(XMLConstHandleTest_144, FirstChildOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(nullptr, firstChild.ToNode());
}

// Test FirstChildElement with no name filter
TEST_F(XMLConstHandleTest_144, FirstChildElementNoFilter_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement();
    EXPECT_NE(nullptr, firstElem.ToElement());
    EXPECT_STREQ("child1", firstElem.ToElement()->Name());
}

// Test FirstChildElement with name filter
TEST_F(XMLConstHandleTest_144, FirstChildElementWithName_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle child2 = handle.FirstChildElement("child2");
    EXPECT_NE(nullptr, child2.ToElement());
    EXPECT_STREQ("child2", child2.ToElement()->Name());
}

// Test FirstChildElement with non-existing name
TEST_F(XMLConstHandleTest_144, FirstChildElementNonExistingName_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle noChild = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(nullptr, noChild.ToNode());
}

// Test FirstChildElement on null handle
TEST_F(XMLConstHandleTest_144, FirstChildElementOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChildElement();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test LastChild
TEST_F(XMLConstHandleTest_144, LastChild_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(nullptr, lastChild.ToNode());
    EXPECT_NE(nullptr, lastChild.ToElement());
    EXPECT_STREQ("child3", lastChild.ToElement()->Name());
}

// Test LastChild on null handle
TEST_F(XMLConstHandleTest_144, LastChildOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(nullptr, lastChild.ToNode());
}

// Test LastChildElement with no filter
TEST_F(XMLConstHandleTest_144, LastChildElementNoFilter_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement();
    EXPECT_NE(nullptr, lastElem.ToElement());
    EXPECT_STREQ("child3", lastElem.ToElement()->Name());
}

// Test LastChildElement with name filter
TEST_F(XMLConstHandleTest_144, LastChildElementWithName_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle child1 = handle.LastChildElement("child1");
    EXPECT_NE(nullptr, child1.ToElement());
    EXPECT_STREQ("child1", child1.ToElement()->Name());
}

// Test LastChildElement on null handle
TEST_F(XMLConstHandleTest_144, LastChildElementOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test NextSibling
TEST_F(XMLConstHandleTest_144, NextSibling_144) {
    const XMLElement* child1 = doc.RootElement()->FirstChildElement("child1");
    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_NE(nullptr, next.ToNode());
    EXPECT_NE(nullptr, next.ToElement());
    EXPECT_STREQ("child2", next.ToElement()->Name());
}

// Test NextSibling on last child returns null
TEST_F(XMLConstHandleTest_144, NextSiblingOnLastChild_144) {
    const XMLElement* child3 = doc.RootElement()->LastChildElement("child3");
    XMLConstHandle handle(child3);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(nullptr, next.ToNode());
}

// Test NextSibling on null handle
TEST_F(XMLConstHandleTest_144, NextSiblingOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(nullptr, next.ToNode());
}

// Test NextSiblingElement with no filter
TEST_F(XMLConstHandleTest_144, NextSiblingElementNoFilter_144) {
    const XMLElement* child1 = doc.RootElement()->FirstChildElement("child1");
    XMLConstHandle handle(child1);
    XMLConstHandle nextElem = handle.NextSiblingElement();
    EXPECT_NE(nullptr, nextElem.ToElement());
    EXPECT_STREQ("child2", nextElem.ToElement()->Name());
}

// Test NextSiblingElement with name
TEST_F(XMLConstHandleTest_144, NextSiblingElementWithName_144) {
    const XMLElement* child1 = doc.RootElement()->FirstChildElement("child1");
    XMLConstHandle handle(child1);
    XMLConstHandle child3 = handle.NextSiblingElement("child3");
    EXPECT_NE(nullptr, child3.ToElement());
    EXPECT_STREQ("child3", child3.ToElement()->Name());
}

// Test NextSiblingElement on null handle
TEST_F(XMLConstHandleTest_144, NextSiblingElementOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSiblingElement();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_144, PreviousSibling_144) {
    const XMLElement* child2 = doc.RootElement()->FirstChildElement("child2");
    XMLConstHandle handle(child2);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(nullptr, prev.ToNode());
    EXPECT_NE(nullptr, prev.ToElement());
    EXPECT_STREQ("child1", prev.ToElement()->Name());
}

// Test PreviousSibling on first child returns null
TEST_F(XMLConstHandleTest_144, PreviousSiblingOnFirstChild_144) {
    const XMLElement* child1 = doc.RootElement()->FirstChildElement("child1");
    XMLConstHandle handle(child1);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(nullptr, prev.ToNode());
}

// Test PreviousSibling on null handle
TEST_F(XMLConstHandleTest_144, PreviousSiblingOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(nullptr, prev.ToNode());
}

// Test PreviousSiblingElement with no filter
TEST_F(XMLConstHandleTest_144, PreviousSiblingElementNoFilter_144) {
    const XMLElement* child3 = doc.RootElement()->LastChildElement("child3");
    XMLConstHandle handle(child3);
    XMLConstHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_NE(nullptr, prevElem.ToElement());
    EXPECT_STREQ("child2", prevElem.ToElement()->Name());
}

// Test PreviousSiblingElement with name
TEST_F(XMLConstHandleTest_144, PreviousSiblingElementWithName_144) {
    const XMLElement* child3 = doc.RootElement()->LastChildElement("child3");
    XMLConstHandle handle(child3);
    XMLConstHandle child1 = handle.PreviousSiblingElement("child1");
    EXPECT_NE(nullptr, child1.ToElement());
    EXPECT_STREQ("child1", child1.ToElement()->Name());
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLConstHandleTest_144, PreviousSiblingElementOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test ToNode on valid handle
TEST_F(XMLConstHandleTest_144, ToNodeOnValidHandle_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(static_cast<const XMLNode*>(root), handle.ToNode());
}

// Test ToNode on null handle
TEST_F(XMLConstHandleTest_144, ToNodeOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToNode());
}

// Test ToUnknown on null handle
TEST_F(XMLConstHandleTest_144, ToUnknownOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToUnknown());
}

// Test ToUnknown on element node returns null
TEST_F(XMLConstHandleTest_144, ToUnknownOnElementNode_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(nullptr, handle.ToUnknown());
}

// Test ToDeclaration on null handle
TEST_F(XMLConstHandleTest_144, ToDeclarationOnNullHandle_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToDeclaration());
}

// Test ToDeclaration with a document that has a declaration
TEST_F(XMLConstHandleTest_144, ToDeclarationOnDeclarationNode_144) {
    XMLDocument docWithDecl;
    docWithDecl.Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* firstChild = docWithDecl.FirstChild();
    ASSERT_NE(nullptr, firstChild);
    XMLConstHandle handle(firstChild);
    EXPECT_NE(nullptr, handle.ToDeclaration());
}

// Test ToDeclaration on element node returns null
TEST_F(XMLConstHandleTest_144, ToDeclarationOnElementNode_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(nullptr, handle.ToDeclaration());
}

// Test chaining: FirstChildElement then NextSiblingElement
TEST_F(XMLConstHandleTest_144, ChainingFirstChildThenNextSibling_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle child2 = handle.FirstChildElement().NextSiblingElement();
    EXPECT_NE(nullptr, child2.ToElement());
    EXPECT_STREQ("child2", child2.ToElement()->Name());
}

// Test chaining: LastChildElement then PreviousSiblingElement
TEST_F(XMLConstHandleTest_144, ChainingLastChildThenPreviousSibling_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle child2 = handle.LastChildElement().PreviousSiblingElement();
    EXPECT_NE(nullptr, child2.ToElement());
    EXPECT_STREQ("child2", child2.ToElement()->Name());
}

// Test chaining through null gracefully
TEST_F(XMLConstHandleTest_144, ChainingThroughNull_144) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChildElement().NextSiblingElement().LastChild();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test handle with leaf node (no children)
TEST_F(XMLConstHandleTest_144, FirstChildOnLeafNode_144) {
    const XMLElement* child2 = doc.RootElement()->FirstChildElement("child2");
    XMLConstHandle handle(child2);
    XMLConstHandle result = handle.FirstChild();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test handle with leaf node FirstChildElement
TEST_F(XMLConstHandleTest_144, FirstChildElementOnLeafNode_144) {
    const XMLElement* child2 = doc.RootElement()->FirstChildElement("child2");
    XMLConstHandle handle(child2);
    XMLConstHandle result = handle.FirstChildElement();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test ToUnknown with actual unknown node
TEST_F(XMLConstHandleTest_144, ToUnknownOnUnknownNode_144) {
    XMLDocument docWithUnknown;
    docWithUnknown.Parse("<root><!unknown stuff></root>");
    const XMLNode* root = docWithUnknown.RootElement();
    ASSERT_NE(nullptr, root);
    const XMLNode* unknownNode = root->FirstChild();
    if (unknownNode != nullptr) {
        XMLConstHandle handle(unknownNode);
        // If tinyxml2 parsed it as unknown, ToUnknown should be non-null
        // Otherwise this is just an informational test
        if (unknownNode->ToUnknown()) {
            EXPECT_NE(nullptr, handle.ToUnknown());
        }
    }
}

// Test self-assignment
TEST_F(XMLConstHandleTest_144, SelfAssignment_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    handle = handle;
    EXPECT_EQ(root, handle.ToNode());
}

// Test deep chaining to text node
TEST_F(XMLConstHandleTest_144, DeepChainingToText_144) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    // root -> FirstChildElement("child1") -> FirstChild() should be text "text1"
    XMLConstHandle textHandle = handle.FirstChildElement("child1").FirstChild();
    EXPECT_NE(nullptr, textHandle.ToNode());
    EXPECT_NE(nullptr, textHandle.ToText());
}
