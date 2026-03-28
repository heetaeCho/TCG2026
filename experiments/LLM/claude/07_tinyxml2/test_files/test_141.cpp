#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_141 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test constructing XMLConstHandle with a null node
TEST_F(XMLConstHandleTest_141, ConstructWithNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test constructing XMLConstHandle with a valid node
TEST_F(XMLConstHandleTest_141, ConstructWithValidNode_141) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLConstHandle with a node reference
TEST_F(XMLConstHandleTest_141, ConstructWithNodeReference_141) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_141, CopyConstructor_141) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_141, AssignmentOperator_141) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(static_cast<const XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test NextSiblingElement with null internal node
TEST_F(XMLConstHandleTest_141, NextSiblingElementWithNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSiblingElement with no next sibling
TEST_F(XMLConstHandleTest_141, NextSiblingElementNoSibling_141) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle(root);
    XMLConstHandle result = handle.NextSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSiblingElement with a valid next sibling element
TEST_F(XMLConstHandleTest_141, NextSiblingElementWithValidSibling_141) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    const XMLNode* first = doc->FirstChild();
    XMLConstHandle handle(first);
    XMLConstHandle result = handle.NextSiblingElement();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "second");
}

// Test NextSiblingElement with name filter - matching
TEST_F(XMLConstHandleTest_141, NextSiblingElementWithNameMatch_141) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    doc->InsertEndChild(doc->NewElement("third"));
    const XMLNode* first = doc->FirstChild();
    XMLConstHandle handle(first);
    XMLConstHandle result = handle.NextSiblingElement("third");
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "third");
}

// Test NextSiblingElement with name filter - no match
TEST_F(XMLConstHandleTest_141, NextSiblingElementWithNameNoMatch_141) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    const XMLNode* first = doc->FirstChild();
    XMLConstHandle handle(first);
    XMLConstHandle result = handle.NextSiblingElement("nonexistent");
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test FirstChild with null node
TEST_F(XMLConstHandleTest_141, FirstChildNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test FirstChild with valid node that has children
TEST_F(XMLConstHandleTest_141, FirstChildWithChildren_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.FirstChild();
    ASSERT_NE(result.ToNode(), nullptr);
}

// Test FirstChild with valid node that has no children
TEST_F(XMLConstHandleTest_141, FirstChildNoChildren_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.FirstChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test FirstChildElement with no name
TEST_F(XMLConstHandleTest_141, FirstChildElementNoName_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.FirstChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "child1");
}

// Test FirstChildElement with name filter
TEST_F(XMLConstHandleTest_141, FirstChildElementWithName_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.FirstChildElement("child2");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "child2");
}

// Test FirstChildElement with null internal node
TEST_F(XMLConstHandleTest_141, FirstChildElementNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test LastChild with null node
TEST_F(XMLConstHandleTest_141, LastChildNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChild with children
TEST_F(XMLConstHandleTest_141, LastChildWithChildren_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
}

// Test LastChildElement with null node
TEST_F(XMLConstHandleTest_141, LastChildElementNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test LastChildElement with children
TEST_F(XMLConstHandleTest_141, LastChildElementWithChildren_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "child2");
}

// Test LastChildElement with name
TEST_F(XMLConstHandleTest_141, LastChildElementWithName_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));
    root->InsertEndChild(doc->NewElement("child1"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.LastChildElement("child1");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "child1");
}

// Test PreviousSibling with null node
TEST_F(XMLConstHandleTest_141, PreviousSiblingNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling with valid previous sibling
TEST_F(XMLConstHandleTest_141, PreviousSiblingValid_141) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    const XMLNode* second = doc->FirstChild()->NextSibling();
    XMLConstHandle handle(second);
    XMLConstHandle result = handle.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);
}

// Test PreviousSiblingElement with null node
TEST_F(XMLConstHandleTest_141, PreviousSiblingElementNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test PreviousSiblingElement with valid previous sibling
TEST_F(XMLConstHandleTest_141, PreviousSiblingElementValid_141) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    const XMLNode* second = doc->FirstChild()->NextSibling();
    XMLConstHandle handle(second);
    XMLConstHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "first");
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLConstHandleTest_141, PreviousSiblingElementWithName_141) {
    doc->InsertEndChild(doc->NewElement("alpha"));
    doc->InsertEndChild(doc->NewElement("beta"));
    doc->InsertEndChild(doc->NewElement("gamma"));
    const XMLNode* gamma = doc->LastChild();
    XMLConstHandle handle(gamma);
    XMLConstHandle result = handle.PreviousSiblingElement("alpha");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "alpha");
}

// Test NextSibling with null node
TEST_F(XMLConstHandleTest_141, NextSiblingNullNode_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSibling with valid next sibling
TEST_F(XMLConstHandleTest_141, NextSiblingValid_141) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    const XMLNode* first = doc->FirstChild();
    XMLConstHandle handle(first);
    XMLConstHandle result = handle.NextSibling();
    ASSERT_NE(result.ToNode(), nullptr);
}

// Test ToNode returns correct node
TEST_F(XMLConstHandleTest_141, ToNodeReturnsCorrectNode_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    const XMLNode* node = root;
    XMLConstHandle handle(node);
    EXPECT_EQ(handle.ToNode(), node);
}

// Test ToNode returns nullptr for null handle
TEST_F(XMLConstHandleTest_141, ToNodeReturnsNullForNullHandle_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToElement returns element for element node
TEST_F(XMLConstHandleTest_141, ToElementReturnsElement_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    EXPECT_NE(handle.ToElement(), nullptr);
}

// Test ToElement returns nullptr for null handle
TEST_F(XMLConstHandleTest_141, ToElementReturnsNullForNullHandle_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText returns nullptr for non-text node
TEST_F(XMLConstHandleTest_141, ToTextReturnsNullForNonTextNode_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText returns nullptr for null handle
TEST_F(XMLConstHandleTest_141, ToTextReturnsNullForNullHandle_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText returns text for text node
TEST_F(XMLConstHandleTest_141, ToTextReturnsTextNode_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLText* text = doc->NewText("hello");
    root->InsertEndChild(text);
    XMLConstHandle handle(static_cast<const XMLNode*>(text));
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToUnknown returns nullptr for null handle
TEST_F(XMLConstHandleTest_141, ToUnknownReturnsNullForNullHandle_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration returns nullptr for null handle
TEST_F(XMLConstHandleTest_141, ToDeclarationReturnsNullForNullHandle_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test chaining: FirstChildElement then NextSiblingElement
TEST_F(XMLConstHandleTest_141, ChainingFirstChildThenNextSibling_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("a"));
    root->InsertEndChild(doc->NewElement("b"));
    root->InsertEndChild(doc->NewElement("c"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle result = handle.FirstChildElement().NextSiblingElement().NextSiblingElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "c");
}

// Test chaining with null propagation
TEST_F(XMLConstHandleTest_141, ChainingWithNullPropagation_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("a"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    // a has no next sibling element, so this should propagate null
    XMLConstHandle result = handle.FirstChildElement().NextSiblingElement().NextSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSiblingElement called on null handle with name
TEST_F(XMLConstHandleTest_141, NextSiblingElementNullNodeWithName_141) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSiblingElement("something");
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test multiple siblings with same name, NextSiblingElement finds next
TEST_F(XMLConstHandleTest_141, NextSiblingElementMultipleSameName_141) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("item"));
    root->InsertEndChild(doc->NewElement("item"));
    root->InsertEndChild(doc->NewElement("item"));
    
    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    XMLConstHandle first = handle.FirstChildElement("item");
    ASSERT_NE(first.ToElement(), nullptr);
    
    XMLConstHandle second = first.NextSiblingElement("item");
    ASSERT_NE(second.ToElement(), nullptr);
    EXPECT_NE(second.ToNode(), first.ToNode());
    
    XMLConstHandle third = second.NextSiblingElement("item");
    ASSERT_NE(third.ToElement(), nullptr);
    EXPECT_NE(third.ToNode(), second.ToNode());
    
    XMLConstHandle fourth = third.NextSiblingElement("item");
    EXPECT_EQ(fourth.ToNode(), nullptr);
}

// Test document as root handle
TEST_F(XMLConstHandleTest_141, DocumentAsHandle_141) {
    doc->InsertEndChild(doc->NewElement("root"));
    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle result = handle.FirstChildElement("root");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "root");
}

// Test ToDeclaration with actual declaration
TEST_F(XMLConstHandleTest_141, ToDeclarationWithDeclaration_141) {
    XMLDeclaration* decl = doc->NewDeclaration();
    doc->InsertFirstChild(decl);
    XMLConstHandle handle(static_cast<const XMLNode*>(decl));
    EXPECT_NE(handle.ToDeclaration(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
}
