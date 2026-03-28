#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Fixture for XMLConstHandle tests
class XMLConstHandleTest_133 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("Root");
        doc.InsertFirstChild(root);

        XMLElement* child1 = doc.NewElement("Child1");
        root->InsertEndChild(child1);

        XMLElement* child2 = doc.NewElement("Child2");
        root->InsertEndChild(child2);
    }
};

// Test assignment operator
TEST_F(XMLConstHandleTest_133, AssignmentOperator_133) {
    XMLConstHandle handle1(root);
    XMLConstHandle handle2 = handle1;

    // Observable behavior: ToNode() should return the same node
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test FirstChild
TEST_F(XMLConstHandleTest_133, FirstChildReturnsCorrectNode_133) {
    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();

    EXPECT_EQ(firstChild.ToNode()->Value(), std::string("Child1"));
}

// Test FirstChildElement
TEST_F(XMLConstHandleTest_133, FirstChildElementByName_133) {
    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement("Child2");

    EXPECT_EQ(child.ToNode()->Value(), std::string("Child2"));
}

// Test LastChild
TEST_F(XMLConstHandleTest_133, LastChildReturnsCorrectNode_133) {
    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();

    EXPECT_EQ(lastChild.ToNode()->Value(), std::string("Child2"));
}

// Test LastChildElement
TEST_F(XMLConstHandleTest_133, LastChildElementByName_133) {
    XMLConstHandle handle(root);
    XMLConstHandle child = handle.LastChildElement("Child1");

    EXPECT_EQ(child.ToNode()->Value(), std::string("Child1"));
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_133, PreviousSiblingReturnsCorrectNode_133) {
    XMLConstHandle handle(root->FirstChild());
    XMLConstHandle sibling = handle.NextSibling().PreviousSibling();

    EXPECT_EQ(sibling.ToNode()->Value(), std::string("Child1"));
}

// Test PreviousSiblingElement by name
TEST_F(XMLConstHandleTest_133, PreviousSiblingElementByName_133) {
    XMLConstHandle handle(root->LastChild());
    XMLConstHandle sibling = handle.PreviousSiblingElement("Child1");

    EXPECT_EQ(sibling.ToNode()->Value(), std::string("Child1"));
}

// Test NextSibling
TEST_F(XMLConstHandleTest_133, NextSiblingReturnsCorrectNode_133) {
    XMLConstHandle handle(root->FirstChild());
    XMLConstHandle next = handle.NextSibling();

    EXPECT_EQ(next.ToNode()->Value(), std::string("Child2"));
}

// Test NextSiblingElement by name
TEST_F(XMLConstHandleTest_133, NextSiblingElementByName_133) {
    XMLConstHandle handle(root->FirstChild());
    XMLConstHandle next = handle.NextSiblingElement("Child2");

    EXPECT_EQ(next.ToNode()->Value(), std::string("Child2"));
}

// Test ToNode returns the correct pointer
TEST_F(XMLConstHandleTest_133, ToNodeReturnsCorrectPointer_133) {
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToElement returns correct element
TEST_F(XMLConstHandleTest_133, ToElementReturnsCorrectElement_133) {
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToText returns nullptr for element
TEST_F(XMLConstHandleTest_133, ToTextReturnsNullForElement_133) {
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown returns nullptr for element
TEST_F(XMLConstHandleTest_133, ToUnknownReturnsNullForElement_133) {
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration returns nullptr for element
TEST_F(XMLConstHandleTest_133, ToDeclarationReturnsNullForElement_133) {
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}
