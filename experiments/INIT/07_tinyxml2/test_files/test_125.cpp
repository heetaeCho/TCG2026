#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock helper not needed here since PreviousSiblingElement has no external dependencies
// We'll just use real XMLDocument/XMLNode objects to observe behavior

class XMLHandleTest_125 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* parent = nullptr;
    XMLElement* child1 = nullptr;
    XMLElement* child2 = nullptr;
    XMLElement* child3 = nullptr;

    void SetUp() override {
        parent = doc.NewElement("parent");
        doc.InsertEndChild(parent);

        child1 = doc.NewElement("child");
        child2 = doc.NewElement("child");
        child3 = doc.NewElement("child2");

        parent->InsertEndChild(child1);
        parent->InsertEndChild(child2);
        parent->InsertEndChild(child3);
    }
};

// Test normal behavior: find previous sibling by name
TEST_F(XMLHandleTest_125, PreviousSiblingElementByName_ReturnsCorrectSibling_125) {
    XMLHandle handle(child2);
    XMLHandle prev = handle.PreviousSiblingElement("child");

    ASSERT_TRUE(prev.ToElement() != nullptr);
    EXPECT_EQ(prev.ToElement(), child1);
}

// Test behavior when name does not match any previous sibling
TEST_F(XMLHandleTest_125, PreviousSiblingElementByName_NoMatch_ReturnsNull_125) {
    XMLHandle handle(child1);
    XMLHandle prev = handle.PreviousSiblingElement("nonexistent");

    EXPECT_EQ(prev.ToElement(), nullptr);
}

// Test behavior when called on first child
TEST_F(XMLHandleTest_125, PreviousSiblingElement_FirstChild_ReturnsNull_125) {
    XMLHandle handle(child1);
    XMLHandle prev = handle.PreviousSiblingElement();

    EXPECT_EQ(prev.ToElement(), nullptr);
}

// Test behavior without specifying a name (should return immediate previous sibling)
TEST_F(XMLHandleTest_125, PreviousSiblingElement_NoName_ReturnsImmediatePrevious_125) {
    XMLHandle handle(child3);
    XMLHandle prev = handle.PreviousSiblingElement();

    ASSERT_TRUE(prev.ToElement() != nullptr);
    EXPECT_EQ(prev.ToElement(), child2);
}

// Test behavior when the node itself is null
TEST_F(XMLHandleTest_125, PreviousSiblingElement_NullNode_ReturnsNull_125) {
    XMLHandle handle(nullptr);
    XMLHandle prev = handle.PreviousSiblingElement();

    EXPECT_EQ(prev.ToElement(), nullptr);
}

// Test behavior with a single node (no siblings)
TEST_F(XMLHandleTest_125, PreviousSiblingElement_SingleNode_ReturnsNull_125) {
    XMLDocument singleDoc;
    XMLElement* solo = singleDoc.NewElement("solo");
    singleDoc.InsertEndChild(solo);

    XMLHandle handle(solo);
    XMLHandle prev = handle.PreviousSiblingElement();

    EXPECT_EQ(prev.ToElement(), nullptr);
}
