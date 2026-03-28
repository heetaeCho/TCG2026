#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Minimal mock XMLNode-derived objects for testing
class MockXMLNode : public XMLNode {};
class MockXMLElement : public XMLElement {};

class XMLHandleTest_119 : public ::testing::Test {
protected:
    MockXMLNode node;
    MockXMLElement element;
};

// Test the copy assignment operator
TEST_F(XMLHandleTest_119, CopyAssignment_119) {
    XMLHandle handle1(&node);
    XMLHandle handle2(nullptr);

    handle2 = handle1;  // Should copy _node
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test constructing from a pointer
TEST_F(XMLHandleTest_119, ConstructFromPointer_119) {
    XMLHandle handle(&node);
    EXPECT_EQ(handle.ToNode(), &node);
}

// Test constructing from a reference
TEST_F(XMLHandleTest_119, ConstructFromReference_119) {
    XMLHandle handle(node);
    EXPECT_EQ(handle.ToNode(), &node);
}

// Test copy constructor
TEST_F(XMLHandleTest_119, CopyConstructor_119) {
    XMLHandle handle1(&node);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test FirstChild when node is nullptr
TEST_F(XMLHandleTest_119, FirstChildReturnsEmpty_119) {
    XMLHandle handle(nullptr);
    EXPECT_EQ(handle.FirstChild().ToNode(), nullptr);
}

// Test FirstChildElement with nullptr and valid name
TEST_F(XMLHandleTest_119, FirstChildElementReturnsEmpty_119) {
    XMLHandle handle(nullptr);
    EXPECT_EQ(handle.FirstChildElement().ToNode(), nullptr);
    EXPECT_EQ(handle.FirstChildElement("NonExistent").ToNode(), nullptr);
}

// Test LastChild and LastChildElement on empty handle
TEST_F(XMLHandleTest_119, LastChildReturnsEmpty_119) {
    XMLHandle handle(nullptr);
    EXPECT_EQ(handle.LastChild().ToNode(), nullptr);
    EXPECT_EQ(handle.LastChildElement().ToNode(), nullptr);
}

// Test Sibling navigation on empty handle
TEST_F(XMLHandleTest_119, SiblingNavigationReturnsEmpty_119) {
    XMLHandle handle(nullptr);
    EXPECT_EQ(handle.PreviousSibling().ToNode(), nullptr);
    EXPECT_EQ(handle.PreviousSiblingElement().ToNode(), nullptr);
    EXPECT_EQ(handle.NextSibling().ToNode(), nullptr);
    EXPECT_EQ(handle.NextSiblingElement().ToNode(), nullptr);
}

// Test type conversion methods on empty handle
TEST_F(XMLHandleTest_119, TypeConversionsOnEmptyHandle_119) {
    XMLHandle handle(nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}
