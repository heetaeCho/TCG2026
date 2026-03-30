#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

class XMLHandleTest_130 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLNode* root = nullptr;
    XMLNode* textNode = nullptr;

    void SetUp() override {
        root = doc.NewElement("Root");
        doc.InsertFirstChild(root);

        textNode = doc.NewText("Hello");
        root->InsertEndChild(textNode);
    }
};

// Test construction from XMLNode*
TEST_F(XMLHandleTest_130, ConstructFromNodePtr_130) {
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test construction from XMLNode&
TEST_F(XMLHandleTest_130, ConstructFromNodeRef_130) {
    XMLHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLHandleTest_130, CopyConstructor_130) {
    XMLHandle handle1(root);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLHandleTest_130, AssignmentOperator_130) {
    XMLHandle handle1(root);
    XMLHandle handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);

    XMLHandle handle3(nullptr);
    handle3 = handle1;
    EXPECT_EQ(handle3.ToNode(), root);
}

// Test FirstChild()
TEST_F(XMLHandleTest_130, FirstChildReturnsCorrectHandle_130) {
    XMLHandle handle(root);
    XMLHandle childHandle = handle.FirstChild();
    EXPECT_EQ(childHandle.ToNode(), textNode);
}

// Test FirstChildElement() with matching name
TEST_F(XMLHandleTest_130, FirstChildElementByName_130) {
    XMLElement* elem = doc.NewElement("Child");
    root->InsertEndChild(elem);

    XMLHandle handle(root);
    XMLHandle childElemHandle = handle.FirstChildElement("Child");
    EXPECT_EQ(childElemHandle.ToElement(), elem);
}

// Test FirstChildElement() with non-existent name returns null
TEST_F(XMLHandleTest_130, FirstChildElementNonExistent_130) {
    XMLHandle handle(root);
    XMLHandle childElemHandle = handle.FirstChildElement("NonExistent");
    EXPECT_EQ(childElemHandle.ToElement(), nullptr);
}

// Test ToText() returns correct XMLText pointer
TEST_F(XMLHandleTest_130, ToTextReturnsCorrectNode_130) {
    XMLHandle handle(textNode);
    XMLText* txt = handle.ToText();
    ASSERT_NE(txt, nullptr);
    EXPECT_STREQ(txt->Value(), "Hello");
}

// Test ToText() on non-text node returns nullptr
TEST_F(XMLHandleTest_130, ToTextOnNonTextNodeReturnsNull_130) {
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test behavior when handle is initialized with nullptr
TEST_F(XMLHandleTest_130, HandleWithNullNode_130) {
    XMLHandle handle(nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.FirstChild().ToNode(), nullptr);
    EXPECT_EQ(handle.FirstChildElement().ToNode(), nullptr);
}

// Test NextSibling() and PreviousSibling() for boundary (no sibling)
TEST_F(XMLHandleTest_130, NoSiblingReturnsNullHandle_130) {
    XMLHandle handle(root);
    EXPECT_EQ(handle.NextSibling().ToNode(), nullptr);
    EXPECT_EQ(handle.PreviousSibling().ToNode(), nullptr);
}

// Test NextSiblingElement() and PreviousSiblingElement() with no match
TEST_F(XMLHandleTest_130, SiblingElementNoMatchReturnsNull_130) {
    XMLHandle handle(root);
    EXPECT_EQ(handle.NextSiblingElement("NonExistent").ToNode(), nullptr);
    EXPECT_EQ(handle.PreviousSiblingElement("NonExistent").ToNode(), nullptr);
}
