#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_132 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test ToDeclaration with a valid declaration node
TEST_F(XMLHandleTest_132, ToDeclaration_WithDeclarationNode_ReturnsDeclaration_132) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    ASSERT_NE(declNode->ToDeclaration(), nullptr);
    
    XMLHandle handle(declNode);
    XMLDeclaration* decl = handle.ToDeclaration();
    ASSERT_NE(decl, nullptr);
    EXPECT_EQ(decl, declNode->ToDeclaration());
}

// Test ToDeclaration with a null node
TEST_F(XMLHandleTest_132, ToDeclaration_WithNullNode_ReturnsNull_132) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLDeclaration* decl = handle.ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test ToDeclaration with non-declaration node (element)
TEST_F(XMLHandleTest_132, ToDeclaration_WithElementNode_ReturnsNull_132) {
    const char* xml = "<root><child/></root>";
    doc->Parse(xml);
    
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLHandle handle(root);
    XMLDeclaration* decl = handle.ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test ToDeclaration with comment node
TEST_F(XMLHandleTest_132, ToDeclaration_WithCommentNode_ReturnsNull_132) {
    const char* xml = "<!-- comment --><root/>";
    doc->Parse(xml);
    
    XMLNode* commentNode = doc->FirstChild();
    ASSERT_NE(commentNode, nullptr);
    ASSERT_NE(commentNode->ToComment(), nullptr);
    
    XMLHandle handle(commentNode);
    XMLDeclaration* decl = handle.ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test ToDeclaration with text node
TEST_F(XMLHandleTest_132, ToDeclaration_WithTextNode_ReturnsNull_132) {
    const char* xml = "<root>Hello</root>";
    doc->Parse(xml);
    
    XMLNode* textNode = doc->RootElement()->FirstChild();
    ASSERT_NE(textNode, nullptr);
    ASSERT_NE(textNode->ToText(), nullptr);
    
    XMLHandle handle(textNode);
    XMLDeclaration* decl = handle.ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test XMLHandle constructed from reference
TEST_F(XMLHandleTest_132, ToDeclaration_ConstructedFromReference_WithDeclaration_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    ASSERT_NE(declNode->ToDeclaration(), nullptr);
    
    XMLHandle handle(*declNode);
    XMLDeclaration* decl = handle.ToDeclaration();
    ASSERT_NE(decl, nullptr);
    EXPECT_EQ(decl, declNode->ToDeclaration());
}

// Test XMLHandle copy constructor preserves ToDeclaration behavior
TEST_F(XMLHandleTest_132, ToDeclaration_CopyConstructor_PreservesBehavior_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    
    XMLHandle handle1(declNode);
    XMLHandle handle2(handle1);
    
    EXPECT_EQ(handle1.ToDeclaration(), handle2.ToDeclaration());
}

// Test XMLHandle assignment operator preserves ToDeclaration behavior
TEST_F(XMLHandleTest_132, ToDeclaration_AssignmentOperator_PreservesBehavior_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    
    XMLHandle handle1(declNode);
    XMLHandle handle2(static_cast<XMLNode*>(nullptr));
    handle2 = handle1;
    
    EXPECT_EQ(handle1.ToDeclaration(), handle2.ToDeclaration());
}

// Test XMLHandle FirstChild chained with ToDeclaration
TEST_F(XMLHandleTest_132, FirstChild_ThenToDeclaration_ReturnsNullForElement_132) {
    const char* xml = "<root><child/></root>";
    doc->Parse(xml);
    
    XMLHandle handle(doc->RootElement());
    XMLDeclaration* decl = handle.FirstChild().ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test XMLHandle with document node - ToDeclaration returns null
TEST_F(XMLHandleTest_132, ToDeclaration_WithDocumentNode_ReturnsNull_132) {
    const char* xml = "<root/>";
    doc->Parse(xml);
    
    XMLHandle handle(static_cast<XMLNode*>(doc));
    XMLDeclaration* decl = handle.ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test ToNode on declaration handle returns the same node
TEST_F(XMLHandleTest_132, ToNode_WithDeclarationNode_ReturnsNode_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    
    XMLHandle handle(declNode);
    EXPECT_EQ(handle.ToNode(), declNode);
    EXPECT_NE(handle.ToDeclaration(), nullptr);
}

// Test ToElement on declaration handle returns null
TEST_F(XMLHandleTest_132, ToElement_WithDeclarationNode_ReturnsNull_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    ASSERT_NE(declNode->ToDeclaration(), nullptr);
    
    XMLHandle handle(declNode);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_NE(handle.ToDeclaration(), nullptr);
}

// Test ToText on declaration handle returns null
TEST_F(XMLHandleTest_132, ToText_WithDeclarationNode_ReturnsNull_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    
    XMLHandle handle(declNode);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_NE(handle.ToDeclaration(), nullptr);
}

// Test ToUnknown on declaration handle returns null
TEST_F(XMLHandleTest_132, ToUnknown_WithDeclarationNode_ReturnsNull_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* declNode = doc->FirstChild();
    ASSERT_NE(declNode, nullptr);
    
    XMLHandle handle(declNode);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_NE(handle.ToDeclaration(), nullptr);
}

// Test chaining - navigate to declaration via handle navigation
TEST_F(XMLHandleTest_132, NavigateToDeclaration_ViaFirstChild_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLHandle docHandle(static_cast<XMLNode*>(doc));
    XMLHandle firstChildHandle = docHandle.FirstChild();
    
    XMLDeclaration* decl = firstChildHandle.ToDeclaration();
    ASSERT_NE(decl, nullptr);
}

// Test NextSibling from declaration to element
TEST_F(XMLHandleTest_132, NextSibling_FromDeclaration_ReturnsElement_132) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLHandle docHandle(static_cast<XMLNode*>(doc));
    XMLHandle declHandle = docHandle.FirstChild();
    ASSERT_NE(declHandle.ToDeclaration(), nullptr);
    
    XMLHandle nextHandle = declHandle.NextSibling();
    EXPECT_EQ(nextHandle.ToDeclaration(), nullptr);
    EXPECT_NE(nextHandle.ToElement(), nullptr);
}

// Test null handle from failed navigation still returns null ToDeclaration
TEST_F(XMLHandleTest_132, FailedNavigation_ToDeclaration_ReturnsNull_132) {
    const char* xml = "<root/>";
    doc->Parse(xml);
    
    XMLHandle handle(doc->RootElement());
    // root has no children, so FirstChild returns null handle
    XMLHandle nullHandle = handle.FirstChild();
    EXPECT_EQ(nullHandle.ToDeclaration(), nullptr);
    EXPECT_EQ(nullHandle.ToNode(), nullptr);
}

// Test with unknown node - ToDeclaration returns null
TEST_F(XMLHandleTest_132, ToDeclaration_WithUnknownNode_ReturnsNull_132) {
    const char* xml = "<!DOCTYPE foo><root/>";
    doc->Parse(xml);
    
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    
    // If it's an unknown node, ToDeclaration should be null
    if (firstChild->ToUnknown() != nullptr) {
        XMLHandle handle(firstChild);
        EXPECT_EQ(handle.ToDeclaration(), nullptr);
    }
}
