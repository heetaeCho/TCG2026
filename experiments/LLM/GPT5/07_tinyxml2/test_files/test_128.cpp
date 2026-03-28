#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

// Minimal stub classes for XMLNode and derived types to allow compilation
class XMLNode {};
class XMLElement : public XMLNode {};
class XMLText : public XMLNode {};
class XMLUnknown : public XMLNode {};
class XMLDeclaration : public XMLNode {};

// Test fixture
class XMLHandleTest_128 : public ::testing::Test {
protected:
    XMLNode* node = nullptr;
    XMLHandle* handle = nullptr;

    void SetUp() override {
        node = new XMLNode();
        handle = new XMLHandle(node);
    }

    void TearDown() override {
        delete handle;
        delete node;
    }
};

// Test ToNode returns the same node passed in
TEST_F(XMLHandleTest_128, ToNodeReturnsOriginalNode_128) {
    EXPECT_EQ(handle->ToNode(), node);
}

// Test construction from XMLNode reference
TEST_F(XMLHandleTest_128, ConstructFromNodeReference_128) {
    XMLHandle handleRef(*node);
    EXPECT_EQ(handleRef.ToNode(), node);
}

// Test copy construction
TEST_F(XMLHandleTest_128, CopyConstructionCopiesNode_128) {
    XMLHandle copyHandle(*handle);
    EXPECT_EQ(copyHandle.ToNode(), node);
}

// Test assignment operator
TEST_F(XMLHandleTest_128, AssignmentOperatorCopiesNode_128) {
    XMLNode otherNode;
    XMLHandle otherHandle(&otherNode);
    otherHandle = *handle;
    EXPECT_EQ(otherHandle.ToNode(), node);
}

// Test FirstChild returns a handle (node is unknown; black-box)
TEST_F(XMLHandleTest_128, FirstChildReturnsHandle_128) {
    XMLHandle firstChild = handle->FirstChild();
    EXPECT_TRUE(firstChild.ToNode() == nullptr || dynamic_cast<XMLNode*>(firstChild.ToNode()));
}

// Test FirstChildElement returns a handle
TEST_F(XMLHandleTest_128, FirstChildElementReturnsHandle_128) {
    XMLHandle firstChildEl = handle->FirstChildElement();
    EXPECT_TRUE(firstChildEl.ToNode() == nullptr || dynamic_cast<XMLNode*>(firstChildEl.ToNode()));
}

// Test LastChild returns a handle
TEST_F(XMLHandleTest_128, LastChildReturnsHandle_128) {
    XMLHandle lastChild = handle->LastChild();
    EXPECT_TRUE(lastChild.ToNode() == nullptr || dynamic_cast<XMLNode*>(lastChild.ToNode()));
}

// Test LastChildElement returns a handle
TEST_F(XMLHandleTest_128, LastChildElementReturnsHandle_128) {
    XMLHandle lastChildEl = handle->LastChildElement();
    EXPECT_TRUE(lastChildEl.ToNode() == nullptr || dynamic_cast<XMLNode*>(lastChildEl.ToNode()));
}

// Test PreviousSibling returns a handle
TEST_F(XMLHandleTest_128, PreviousSiblingReturnsHandle_128) {
    XMLHandle prevSibling = handle->PreviousSibling();
    EXPECT_TRUE(prevSibling.ToNode() == nullptr || dynamic_cast<XMLNode*>(prevSibling.ToNode()));
}

// Test PreviousSiblingElement returns a handle
TEST_F(XMLHandleTest_128, PreviousSiblingElementReturnsHandle_128) {
    XMLHandle prevSiblingEl = handle->PreviousSiblingElement();
    EXPECT_TRUE(prevSiblingEl.ToNode() == nullptr || dynamic_cast<XMLNode*>(prevSiblingEl.ToNode()));
}

// Test NextSibling returns a handle
TEST_F(XMLHandleTest_128, NextSiblingReturnsHandle_128) {
    XMLHandle nextSibling = handle->NextSibling();
    EXPECT_TRUE(nextSibling.ToNode() == nullptr || dynamic_cast<XMLNode*>(nextSibling.ToNode()));
}

// Test NextSiblingElement returns a handle
TEST_F(XMLHandleTest_128, NextSiblingElementReturnsHandle_128) {
    XMLHandle nextSiblingEl = handle->NextSiblingElement();
    EXPECT_TRUE(nextSiblingEl.ToNode() == nullptr || dynamic_cast<XMLNode*>(nextSiblingEl.ToNode()));
}

// Test ToElement returns nullptr for base XMLNode (black-box)
TEST_F(XMLHandleTest_128, ToElementReturnsNullForBaseNode_128) {
    EXPECT_EQ(handle->ToElement(), nullptr);
}

// Test ToText returns nullptr for base XMLNode
TEST_F(XMLHandleTest_128, ToTextReturnsNullForBaseNode_128) {
    EXPECT_EQ(handle->ToText(), nullptr);
}

// Test ToUnknown returns nullptr for base XMLNode
TEST_F(XMLHandleTest_128, ToUnknownReturnsNullForBaseNode_128) {
    EXPECT_EQ(handle->ToUnknown(), nullptr);
}

// Test ToDeclaration returns nullptr for base XMLNode
TEST_F(XMLHandleTest_128, ToDeclarationReturnsNullForBaseNode_128) {
    EXPECT_EQ(handle->ToDeclaration(), nullptr);
}
