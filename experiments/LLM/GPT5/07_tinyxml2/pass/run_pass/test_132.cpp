#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock XMLDeclaration creation is not needed since ToDeclaration() just returns a pointer.
// We'll use minimal XMLDocument and XMLDeclaration instances for testing.

class XMLHandleTest_132 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLDeclaration* decl = nullptr;
    XMLNode* node = nullptr;

    void SetUp() override {
        // Create an XMLDeclaration node and attach it to the document
        decl = doc.NewDeclaration("xml version='1.0'");
        ASSERT_NE(decl, nullptr);  // Ensure creation succeeded
        node = decl;               // Use the declaration as the node for XMLHandle
    }
};

// Test normal operation: _node points to an XMLDeclaration
TEST_F(XMLHandleTest_132, ToDeclarationReturnsDeclaration_132) {
    XMLHandle handle(node);
    XMLDeclaration* result = handle.ToDeclaration();
    EXPECT_EQ(result, decl);
}

// Test boundary condition: _node is nullptr
TEST_F(XMLHandleTest_132, ToDeclarationWithNullNodeReturnsNull_132) {
    XMLHandle handle(nullptr);
    XMLDeclaration* result = handle.ToDeclaration();
    EXPECT_EQ(result, nullptr);
}

// Test copy constructor preserves ToDeclaration behavior
TEST_F(XMLHandleTest_132, CopyConstructedHandleReturnsDeclaration_132) {
    XMLHandle handle(node);
    XMLHandle copy(handle);
    EXPECT_EQ(copy.ToDeclaration(), decl);
}

// Test assignment operator preserves ToDeclaration behavior
TEST_F(XMLHandleTest_132, AssignedHandleReturnsDeclaration_132) {
    XMLHandle handle1(node);
    XMLHandle handle2(nullptr);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToDeclaration(), decl);
}

// Test ToDeclaration on a node that is not a declaration
TEST_F(XMLHandleTest_132, ToDeclarationOnNonDeclarationNodeReturnsNull_132) {
    // Create a normal element node
    XMLElement* elem = doc.NewElement("TestElement");
    ASSERT_NE(elem, nullptr);

    XMLHandle handle(elem);
    XMLDeclaration* result = handle.ToDeclaration();
    EXPECT_EQ(result, nullptr);
}
