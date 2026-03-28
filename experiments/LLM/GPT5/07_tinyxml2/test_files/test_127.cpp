#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLHandle NextSiblingElement
class XMLHandleTest_127 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root;
    XMLElement* child1;
    XMLElement* child2;

    void SetUp() override {
        root = doc.NewElement("Root");
        doc.InsertEndChild(root);

        child1 = doc.NewElement("Child1");
        root->InsertEndChild(child1);

        child2 = doc.NewElement("Child2");
        root->InsertEndChild(child2);
    }
};

// Test normal operation: retrieving the next sibling without specifying a name
TEST_F(XMLHandleTest_127, NextSiblingElementWithoutName_127) {
    XMLHandle handle(child1);
    XMLHandle next = handle.NextSiblingElement();
    EXPECT_EQ(next.ToNode(), child2);
}

// Test normal operation: retrieving the next sibling by specifying the correct name
TEST_F(XMLHandleTest_127, NextSiblingElementWithMatchingName_127) {
    XMLHandle handle(child1);
    XMLHandle next = handle.NextSiblingElement("Child2");
    EXPECT_EQ(next.ToNode(), child2);
}

// Test boundary case: requesting a sibling with a non-existing name
TEST_F(XMLHandleTest_127, NextSiblingElementWithNonExistingName_127) {
    XMLHandle handle(child1);
    XMLHandle next = handle.NextSiblingElement("NonExistent");
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test boundary case: node has no next sibling
TEST_F(XMLHandleTest_127, NextSiblingElementAtLastChild_127) {
    XMLHandle handle(child2);
    XMLHandle next = handle.NextSiblingElement();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test error/edge case: handle constructed from nullptr
TEST_F(XMLHandleTest_127, NextSiblingElementFromNullHandle_127) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle next = handle.NextSiblingElement();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test name matching is strict
TEST_F(XMLHandleTest_127, NextSiblingElementNameMismatch_127) {
    XMLHandle handle(child1);
    XMLHandle next = handle.NextSiblingElement("child2"); // different case
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test chaining multiple calls
TEST_F(XMLHandleTest_127, NextSiblingElementChaining_127) {
    XMLHandle handle(child1);
    XMLHandle next1 = handle.NextSiblingElement();
    XMLHandle next2 = next1.NextSiblingElement();
    EXPECT_EQ(next1.ToNode(), child2);
    EXPECT_EQ(next2.ToNode(), nullptr);
}
