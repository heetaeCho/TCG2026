#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// A minimal fixture for XMLHandle tests
class XMLHandleTest_120 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLNode* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("Root");
        doc.InsertFirstChild(root);
    }
};

// Test constructing XMLHandle from XMLNode pointer
TEST_F(XMLHandleTest_120, ConstructFromNodePtr_120) {
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLHandle from XMLNode reference
TEST_F(XMLHandleTest_120, ConstructFromNodeRef_120) {
    XMLHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLHandleTest_120, CopyConstructor_120) {
    XMLHandle original(root);
    XMLHandle copy(original);
    EXPECT_EQ(copy.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLHandleTest_120, AssignmentOperator_120) {
    XMLHandle h1(root);
    XMLHandle h2(nullptr);
    h2 = h1;
    EXPECT_EQ(h2.ToNode(), root);
}

// Test FirstChild returns XMLHandle with first child or null
TEST_F(XMLHandleTest_120, FirstChild_ReturnsCorrectHandle_120) {
    XMLNode* child = doc.NewElement("Child");
    root->InsertEndChild(child);

    XMLHandle handle(root);
    XMLHandle firstChildHandle = handle.FirstChild();
    EXPECT_EQ(firstChildHandle.ToNode(), child);
}

// Test FirstChild returns null handle when no children
TEST_F(XMLHandleTest_120, FirstChild_NoChildrenReturnsNull_120) {
    XMLHandle handle(root);
    XMLHandle firstChildHandle = handle.FirstChild();
    EXPECT_EQ(firstChildHandle.ToNode(), nullptr);
}

// Test ToElement returns XMLElement if node is an element
TEST_F(XMLHandleTest_120, ToElement_ReturnsXMLElement_120) {
    XMLHandle handle(root);
    XMLElement* elem = handle.ToElement();
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Value(), "Root");
}

// Test ToNode returns nullptr for empty handle
TEST_F(XMLHandleTest_120, ToNode_NullHandle_120) {
    XMLHandle emptyHandle(nullptr);
    EXPECT_EQ(emptyHandle.ToNode(), nullptr);
}

// Test chaining FirstChild on handle
TEST_F(XMLHandleTest_120, ChainedFirstChild_120) {
    XMLElement* child = doc.NewElement("Child");
    root->InsertEndChild(child);
    XMLElement* grandchild = doc.NewElement("Grandchild");
    child->InsertEndChild(grandchild);

    XMLHandle handle(root);
    XMLHandle chainHandle = handle.FirstChild().FirstChild();
    EXPECT_EQ(chainHandle.ToNode(), grandchild);
}

// Test FirstChildElement returns handle to first child element with optional name
TEST_F(XMLHandleTest_120, FirstChildElement_WithName_120) {
    XMLElement* child1 = doc.NewElement("Child1");
    XMLElement* child2 = doc.NewElement("Child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement("Child2");
    EXPECT_EQ(result.ToNode(), child2);
}

// Test FirstChildElement returns nullptr handle if no matching element
TEST_F(XMLHandleTest_120, FirstChildElement_NoMatch_120) {
    XMLElement* child = doc.NewElement("Child");
    root->InsertEndChild(child);

    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement("Nonexistent");
    EXPECT_EQ(result.ToNode(), nullptr);
}
