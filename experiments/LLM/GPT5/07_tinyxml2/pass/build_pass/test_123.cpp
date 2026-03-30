#include "tinyxml2.h"
#include "gtest/gtest.h"

using namespace tinyxml2;

class XMLHandleTest_123 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root;

    void SetUp() override {
        root = doc.NewElement("Root");
        doc.InsertEndChild(root);
    }
};

// Test: LastChildElement returns an empty handle when XMLHandle is null
TEST_F(XMLHandleTest_123, LastChildElement_NullHandleReturnsNull_123) {
    XMLHandle nullHandle(nullptr);
    XMLHandle result = nullHandle.LastChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test: LastChildElement on node with no children returns null
TEST_F(XMLHandleTest_123, LastChildElement_NoChildrenReturnsNull_123) {
    XMLHandle handle(root);
    XMLHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test: LastChildElement returns the last child element when multiple children exist
TEST_F(XMLHandleTest_123, LastChildElement_MultipleChildrenReturnsLast_123) {
    XMLElement* child1 = doc.NewElement("Child1");
    XMLElement* child2 = doc.NewElement("Child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    XMLHandle handle(root);
    XMLHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToNode(), child2);
}

// Test: LastChildElement with a specific name returns the last matching child
TEST_F(XMLHandleTest_123, LastChildElement_WithNameReturnsLastMatching_123) {
    XMLElement* child1 = doc.NewElement("Target");
    XMLElement* child2 = doc.NewElement("Other");
    XMLElement* child3 = doc.NewElement("Target");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    XMLHandle handle(root);
    XMLHandle result = handle.LastChildElement("Target");
    EXPECT_EQ(result.ToNode(), child3);
}

// Test: LastChildElement with a name that does not exist returns null
TEST_F(XMLHandleTest_123, LastChildElement_WithNonexistentNameReturnsNull_123) {
    XMLElement* child1 = doc.NewElement("Child1");
    root->InsertEndChild(child1);

    XMLHandle handle(root);
    XMLHandle result = handle.LastChildElement("Missing");
    EXPECT_EQ(result.ToNode(), nullptr);
}
