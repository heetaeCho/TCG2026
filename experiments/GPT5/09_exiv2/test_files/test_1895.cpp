#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.cpp"
#include "./TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// Mock classes if necessary for external collaborators (none provided in the prompt)
class MockXMP_Node : public XMP_Node {
public:
    MockXMP_Node(XMP_Node * _parent, XMP_StringPtr _name, XMP_OptionBits _options) 
        : XMP_Node(_parent, _name, _options) {}
    MockXMP_Node(XMP_Node * _parent, const XMP_VarString & _name, XMP_OptionBits _options) 
        : XMP_Node(_parent, _name, _options) {}
};

// Test class for FindChildNode
class XMPNodeTest : public ::testing::Test {
protected:
    XMP_Node *parentNode;
    XMP_StringPtr validChildName = "validChild";
    XMP_StringPtr invalidChildName = "invalidChild";

    void SetUp() override {
        // Setup parent node with a name and options
        parentNode = new XMP_Node(nullptr, "parentNode", kXMP_PropValueIsStruct);
    }

    void TearDown() override {
        delete parentNode;
    }
};

// Normal operation: valid child node is found
TEST_F(XMPNodeTest, FindChildNode_ValidChild_Found) {
    XMP_Node *childNode = new XMP_Node(parentNode, "validChild", kXMP_PropValueIsStruct);
    parentNode->children.push_back(childNode);

    XMP_NodePtrPos ptrPos;
    XMP_Node *result = FindChildNode(parentNode, validChildName, false, &ptrPos);
    
    ASSERT_EQ(result, childNode);
    ASSERT_EQ(*ptrPos, parentNode->children.begin() + 0);
}

// Boundary condition: parent node has no children
TEST_F(XMPNodeTest, FindChildNode_NoChildren_CreatesNode) {
    XMP_NodePtrPos ptrPos;
    XMP_Node *result = FindChildNode(parentNode, validChildName, true, &ptrPos);
    
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->name, validChildName);
    ASSERT_EQ(parentNode->children.size(), 1);
}

// Error case: parent node does not allow creation of new children
TEST_F(XMPNodeTest, FindChildNode_NoCreateNodes_Throws) {
    XMP_Throw = [](const char* message, int errorCode) { 
        ASSERT_STREQ(message, "Parent is new implicit node, but createNodes is false");
        ASSERT_EQ(errorCode, kXMPErr_InternalFailure);
    };
    
    EXPECT_THROW({
        FindChildNode(parentNode, validChildName, false, nullptr);
    }, std::exception);
}

// Error case: named children not allowed for arrays
TEST_F(XMPNodeTest, FindChildNode_NamedChildrenNotAllowedForArrays_Throws) {
    parentNode->options |= kXMP_PropValueIsArray;
    
    EXPECT_THROW({
        FindChildNode(parentNode, validChildName, false, nullptr);
    }, std::exception);
}

// Boundary condition: parent node with existing child and createNodes=false
TEST_F(XMPNodeTest, FindChildNode_ExistingChild_NotCreatedAgain) {
    XMP_Node *childNode = new XMP_Node(parentNode, "validChild", kXMP_PropValueIsStruct);
    parentNode->children.push_back(childNode);
    
    XMP_NodePtrPos ptrPos;
    XMP_Node *result = FindChildNode(parentNode, validChildName, false, &ptrPos);
    
    ASSERT_EQ(result, childNode);
    ASSERT_EQ(parentNode->children.size(), 1);
}

// Boundary condition: createNodes=true and child node not found
TEST_F(XMPNodeTest, FindChildNode_ChildNotFound_CreatesNewChild) {
    XMP_NodePtrPos ptrPos;
    XMP_Node *result = FindChildNode(parentNode, invalidChildName, true, &ptrPos);
    
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->name, invalidChildName);
    ASSERT_EQ(parentNode->children.size(), 1);
}

// Exceptional case: named children not allowed for schemas
TEST_F(XMPNodeTest, FindChildNode_NamedChildrenNotAllowedForSchemas_Throws) {
    parentNode->options |= kXMP_SchemaNode;
    
    EXPECT_THROW({
        FindChildNode(parentNode, validChildName, false, nullptr);
    }, std::exception);
}