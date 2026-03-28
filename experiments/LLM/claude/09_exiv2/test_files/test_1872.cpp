#include <gtest/gtest.h>
#include <string>

// Include necessary headers from the project
#include "XMPCore_Impl.hpp"

class XMP_AutoNodeTest_1872 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor initializes nodePtr to null
TEST_F(XMP_AutoNodeTest_1872, DefaultConstructor_NodePtrIsNull_1872) {
    XMP_AutoNode autoNode;
    EXPECT_EQ(autoNode.nodePtr, nullptr);
}

// Test constructor with parent, name (XMP_StringPtr), and options
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithStringPtrName_CreatesNode_1872) {
    XMP_AutoNode autoNode(nullptr, "testName", 0);
    EXPECT_NE(autoNode.nodePtr, nullptr);
}

// Test constructor with parent, name (VarString), and options
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithVarStringName_CreatesNode_1872) {
    XMP_VarString name("testName");
    XMP_AutoNode autoNode(nullptr, name, 0);
    EXPECT_NE(autoNode.nodePtr, nullptr);
}

// Test constructor with parent, name (StringPtr), value (StringPtr), and options
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithStringPtrNameAndValue_CreatesNode_1872) {
    XMP_AutoNode autoNode(nullptr, "testName", "testValue", 0);
    EXPECT_NE(autoNode.nodePtr, nullptr);
}

// Test constructor with parent, name (VarString), value (VarString), and options
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithVarStringNameAndValue_CreatesNode_1872) {
    XMP_VarString name("testName");
    XMP_VarString value("testValue");
    XMP_AutoNode autoNode(nullptr, name, value, 0);
    EXPECT_NE(autoNode.nodePtr, nullptr);
}

// Test that destructor sets nodePtr to 0 (verified indirectly by no crash/leak)
TEST_F(XMP_AutoNodeTest_1872, DestructorDeletesNode_NoDoubleFree_1872) {
    {
        XMP_AutoNode autoNode(nullptr, "testName", 0);
        EXPECT_NE(autoNode.nodePtr, nullptr);
        // autoNode goes out of scope, destructor should clean up without issues
    }
    SUCCEED();
}

// Test destructor with default-constructed (null) nodePtr doesn't crash
TEST_F(XMP_AutoNodeTest_1872, DestructorWithNullNodePtr_NoCrash_1872) {
    {
        XMP_AutoNode autoNode;
        EXPECT_EQ(autoNode.nodePtr, nullptr);
        // destructor called on null nodePtr should be safe
    }
    SUCCEED();
}

// Test that nodePtr is publicly accessible and can be modified
TEST_F(XMP_AutoNodeTest_1872, NodePtrIsPublicAndModifiable_1872) {
    XMP_AutoNode autoNode;
    EXPECT_EQ(autoNode.nodePtr, nullptr);
    
    // Assign a new node manually
    autoNode.nodePtr = new XMP_Node(nullptr, "manualNode", 0);
    EXPECT_NE(autoNode.nodePtr, nullptr);
    // Destructor will clean it up
}

// Test releasing ownership by setting nodePtr to null before destruction
TEST_F(XMP_AutoNodeTest_1872, ReleaseOwnership_SetNullBeforeDestruction_1872) {
    XMP_AutoNode autoNode(nullptr, "testName", 0);
    XMP_Node* rawPtr = autoNode.nodePtr;
    EXPECT_NE(rawPtr, nullptr);
    
    // Release ownership
    autoNode.nodePtr = nullptr;
    EXPECT_EQ(autoNode.nodePtr, nullptr);
    
    // Manual cleanup since we took ownership
    delete rawPtr;
}

// Test with non-zero options
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithNonZeroOptions_CreatesNode_1872) {
    XMP_AutoNode autoNode(nullptr, "testName", 0x01);
    EXPECT_NE(autoNode.nodePtr, nullptr);
}

// Test constructor with empty name string
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithEmptyName_CreatesNode_1872) {
    XMP_AutoNode autoNode(nullptr, "", 0);
    EXPECT_NE(autoNode.nodePtr, nullptr);
}

// Test constructor with empty name and value strings
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithEmptyNameAndValue_CreatesNode_1872) {
    XMP_AutoNode autoNode(nullptr, "", "", 0);
    EXPECT_NE(autoNode.nodePtr, nullptr);
}

// Test with a parent node
TEST_F(XMP_AutoNodeTest_1872, ConstructorWithParentNode_CreatesNode_1872) {
    XMP_AutoNode parent(nullptr, "parent", 0);
    ASSERT_NE(parent.nodePtr, nullptr);
    
    XMP_AutoNode child(parent.nodePtr, "child", 0);
    EXPECT_NE(child.nodePtr, nullptr);
}
