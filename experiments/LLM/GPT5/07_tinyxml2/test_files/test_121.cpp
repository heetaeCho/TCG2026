#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_121 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("Root");
        doc.InsertFirstChild(root);
    }
};

// Normal operation: retrieve the first child element without specifying a name
TEST_F(XMLHandleTest_121, FirstChildElementReturnsFirstChildWithoutName_121) {
    XMLElement* child1 = doc.NewElement("Child1");
    XMLElement* child2 = doc.NewElement("Child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement();

    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "Child1");
}

// Normal operation: retrieve the first child element by specifying an existing name
TEST_F(XMLHandleTest_121, FirstChildElementReturnsFirstMatchingName_121) {
    XMLElement* child1 = doc.NewElement("Child1");
    XMLElement* child2 = doc.NewElement("Child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement("Child2");

    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "Child2");
}

// Boundary case: handle points to nullptr, should return XMLHandle with nullptr node
TEST_F(XMLHandleTest_121, FirstChildElementOnNullNodeReturnsNullHandle_121) {
    XMLHandle handle(nullptr);
    XMLHandle result = handle.FirstChildElement();

    EXPECT_EQ(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Boundary case: child with given name does not exist
TEST_F(XMLHandleTest_121, FirstChildElementNonexistentNameReturnsNull_121) {
    XMLElement* child1 = doc.NewElement("Child1");
    root->InsertEndChild(child1);

    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement("NoSuchChild");

    EXPECT_EQ(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Boundary case: root element has no children
TEST_F(XMLHandleTest_121, FirstChildElementEmptyParentReturnsNull_121) {
    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement();

    EXPECT_EQ(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Normal operation: multiple children with same name, should return the first
TEST_F(XMLHandleTest_121, FirstChildElementMultipleSameNameReturnsFirst_121) {
    XMLElement* child1 = doc.NewElement("Child");
    XMLElement* child2 = doc.NewElement("Child");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement("Child");

    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToElement(), child1);
}
