#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_136 : public ::testing::Test {
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
TEST_F(XMLConstHandleTest_136, ConstructWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test constructing XMLConstHandle with a valid node
TEST_F(XMLConstHandleTest_136, ConstructWithValidNode_136) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLConstHandle with a node reference
TEST_F(XMLConstHandleTest_136, ConstructWithNodeReference_136) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_136, CopyConstructor_136) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_136, AssignmentOperator_136) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(static_cast<const XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test LastChild with null node
TEST_F(XMLConstHandleTest_136, LastChildWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChild with node that has no children
TEST_F(XMLConstHandleTest_136, LastChildWithNoChildren_136) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChild with node that has one child
TEST_F(XMLConstHandleTest_136, LastChildWithOneChild_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child = doc->NewElement("child");
    root->InsertEndChild(child);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
    EXPECT_EQ(lastChild.ToNode(), constRoot->LastChild());
}

// Test LastChild with node that has multiple children
TEST_F(XMLConstHandleTest_136, LastChildWithMultipleChildren_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    XMLElement* child3 = doc->NewElement("child3");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
    EXPECT_EQ(lastChild.ToElement()->Name(), std::string("child3"));
}

// Test FirstChild with null node
TEST_F(XMLConstHandleTest_136, FirstChildWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild with valid node
TEST_F(XMLConstHandleTest_136, FirstChildWithValidNode_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_EQ(firstChild.ToElement()->Name(), std::string("child1"));
}

// Test FirstChildElement with null node
TEST_F(XMLConstHandleTest_136, FirstChildElementWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstElem = handle.FirstChildElement();
    EXPECT_EQ(firstElem.ToNode(), nullptr);
}

// Test FirstChildElement with name filter
TEST_F(XMLConstHandleTest_136, FirstChildElementWithNameFilter_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle elem = handle.FirstChildElement("beta");
    EXPECT_NE(elem.ToNode(), nullptr);
    EXPECT_EQ(elem.ToElement()->Name(), std::string("beta"));
}

// Test FirstChildElement with non-matching name
TEST_F(XMLConstHandleTest_136, FirstChildElementWithNonMatchingName_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    root->InsertEndChild(child1);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle elem = handle.FirstChildElement("gamma");
    EXPECT_EQ(elem.ToNode(), nullptr);
}

// Test LastChildElement with null node
TEST_F(XMLConstHandleTest_136, LastChildElementWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastElem = handle.LastChildElement();
    EXPECT_EQ(lastElem.ToNode(), nullptr);
}

// Test LastChildElement with name filter
TEST_F(XMLConstHandleTest_136, LastChildElementWithNameFilter_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    XMLElement* child3 = doc->NewElement("alpha");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle elem = handle.LastChildElement("alpha");
    EXPECT_NE(elem.ToNode(), nullptr);
    // Should be the last "alpha" which is child3
    EXPECT_EQ(elem.ToNode(), static_cast<const XMLNode*>(child3));
}

// Test PreviousSibling with null node
TEST_F(XMLConstHandleTest_136, PreviousSiblingWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling with valid node
TEST_F(XMLConstHandleTest_136, PreviousSiblingWithValidNode_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    const XMLNode* constChild2 = root->LastChild();
    XMLConstHandle handle(constChild2);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    EXPECT_EQ(prev.ToElement()->Name(), std::string("child1"));
}

// Test PreviousSibling when there is no previous sibling
TEST_F(XMLConstHandleTest_136, PreviousSiblingWhenFirst_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    root->InsertEndChild(child1);

    const XMLNode* constChild1 = root->FirstChild();
    XMLConstHandle handle(constChild1);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement with null node
TEST_F(XMLConstHandleTest_136, PreviousSiblingElementWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToNode(), nullptr);
}

// Test NextSibling with null node
TEST_F(XMLConstHandleTest_136, NextSiblingWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling with valid node
TEST_F(XMLConstHandleTest_136, NextSiblingWithValidNode_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    const XMLNode* constChild1 = root->FirstChild();
    XMLConstHandle handle(constChild1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
    EXPECT_EQ(next.ToElement()->Name(), std::string("child2"));
}

// Test NextSibling when there is no next sibling
TEST_F(XMLConstHandleTest_136, NextSiblingWhenLast_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    root->InsertEndChild(child1);

    const XMLNode* constChild1 = root->LastChild();
    XMLConstHandle handle(constChild1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement with null node
TEST_F(XMLConstHandleTest_136, NextSiblingElementWithNullNode_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle nextElem = handle.NextSiblingElement();
    EXPECT_EQ(nextElem.ToNode(), nullptr);
}

// Test NextSiblingElement with name filter
TEST_F(XMLConstHandleTest_136, NextSiblingElementWithNameFilter_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    XMLElement* child3 = doc->NewElement("gamma");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    const XMLNode* constChild1 = root->FirstChild();
    XMLConstHandle handle(constChild1);
    XMLConstHandle nextElem = handle.NextSiblingElement("gamma");
    EXPECT_NE(nextElem.ToNode(), nullptr);
    EXPECT_EQ(nextElem.ToElement()->Name(), std::string("gamma"));
}

// Test ToNode with null
TEST_F(XMLConstHandleTest_136, ToNodeWithNull_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToNode with valid node
TEST_F(XMLConstHandleTest_136, ToNodeWithValidNode_136) {
    doc->InsertEndChild(doc->NewElement("root"));
    const XMLNode* root = doc->FirstChild();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToElement with null node
TEST_F(XMLConstHandleTest_136, ToElementWithNull_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToElement with element node
TEST_F(XMLConstHandleTest_136, ToElementWithElementNode_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    EXPECT_NE(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToElement()->Name(), std::string("root"));
}

// Test ToText with null node
TEST_F(XMLConstHandleTest_136, ToTextWithNull_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText with a text node
TEST_F(XMLConstHandleTest_136, ToTextWithTextNode_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLText* text = doc->NewText("hello");
    root->InsertEndChild(text);

    const XMLNode* constText = root->FirstChild();
    XMLConstHandle handle(constText);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText with non-text node
TEST_F(XMLConstHandleTest_136, ToTextWithNonTextNode_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown with null node
TEST_F(XMLConstHandleTest_136, ToUnknownWithNull_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration with null node
TEST_F(XMLConstHandleTest_136, ToDeclarationWithNull_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration with declaration node
TEST_F(XMLConstHandleTest_136, ToDeclarationWithDeclNode_136) {
    XMLDeclaration* decl = doc->NewDeclaration();
    doc->InsertFirstChild(decl);

    const XMLNode* constDecl = doc->FirstChild();
    XMLConstHandle handle(constDecl);
    EXPECT_NE(handle.ToDeclaration(), nullptr);
}

// Test chaining: FirstChild().LastChild()
TEST_F(XMLConstHandleTest_136, ChainingFirstChildLastChild_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    root->InsertEndChild(child1);
    XMLElement* grandchild1 = doc->NewElement("gc1");
    XMLElement* grandchild2 = doc->NewElement("gc2");
    child1->InsertEndChild(grandchild1);
    child1->InsertEndChild(grandchild2);

    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle result = handle.FirstChild().FirstChild().LastChild();
    EXPECT_NE(result.ToNode(), nullptr);
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToElement()->Name(), std::string("gc2"));
}

// Test chaining through null returns null
TEST_F(XMLConstHandleTest_136, ChainingThroughNullReturnsNull_136) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChild().LastChild().NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChild chained from LastChild
TEST_F(XMLConstHandleTest_136, LastChildChainedFromLastChild_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLElement* gc = doc->NewElement("gc");
    child2->InsertEndChild(gc);

    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle result = handle.FirstChild().LastChild().LastChild();
    EXPECT_NE(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement()->Name(), std::string("gc"));
}

// Test document handle - document as a node
TEST_F(XMLConstHandleTest_136, DocumentAsNode_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    EXPECT_NE(handle.ToNode(), nullptr);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_NE(firstChild.ToElement(), nullptr);
    EXPECT_EQ(firstChild.ToElement()->Name(), std::string("root"));
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLConstHandleTest_136, PreviousSiblingElementWithNameFilter_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    XMLElement* child3 = doc->NewElement("gamma");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    const XMLNode* constChild3 = root->LastChild();
    XMLConstHandle handle(constChild3);
    XMLConstHandle prevElem = handle.PreviousSiblingElement("alpha");
    EXPECT_NE(prevElem.ToNode(), nullptr);
    EXPECT_EQ(prevElem.ToElement()->Name(), std::string("alpha"));
}

// Test that ToElement returns null for non-element node
TEST_F(XMLConstHandleTest_136, ToElementReturnsNullForComment_136) {
    XMLComment* comment = doc->NewComment("a comment");
    doc->InsertEndChild(comment);

    const XMLNode* constComment = doc->FirstChild();
    XMLConstHandle handle(constComment);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_NE(handle.ToNode(), nullptr);
}

// Test FirstChildElement with no name (default param)
TEST_F(XMLConstHandleTest_136, FirstChildElementDefaultParam_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLComment* comment = doc->NewComment("comment");
    root->InsertEndChild(comment);
    XMLElement* child1 = doc->NewElement("child1");
    root->InsertEndChild(child1);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle firstElem = handle.FirstChildElement();
    EXPECT_NE(firstElem.ToNode(), nullptr);
    EXPECT_EQ(firstElem.ToElement()->Name(), std::string("child1"));
}

// Test LastChildElement with no name (default param)
TEST_F(XMLConstHandleTest_136, LastChildElementDefaultParam_136) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    XMLComment* comment = doc->NewComment("tail comment");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(comment);

    const XMLNode* constRoot = doc->FirstChild();
    XMLConstHandle handle(constRoot);
    XMLConstHandle lastElem = handle.LastChildElement();
    EXPECT_NE(lastElem.ToNode(), nullptr);
    EXPECT_EQ(lastElem.ToElement()->Name(), std::string("child2"));
}
