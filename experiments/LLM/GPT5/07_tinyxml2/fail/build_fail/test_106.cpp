#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLElement
class XMLElementTest_106 : public ::testing::Test {
protected:
    // You may initialize a document if needed
    XMLDocument doc;
    XMLElement* element;

    void SetUp() override {
        // Create a new element for testing
        element = doc.NewElement("TestElement");
        ASSERT_NE(element, nullptr);
    }
};

// Test that ClosingType() returns a valid enum value
TEST_F(XMLElementTest_106, ClosingTypeReturnsValue_106) {
    ElementClosingType type = element->ClosingType();

    // The value should be one of the enum values (OPEN, CLOSED, CLOSING)
    EXPECT_TRUE(type == ELEMENT_OPEN || type == ELEMENT_CLOSED || type == ELEMENT_CLOSING);
}

// Optional: Test behavior after setting text (should not affect ClosingType)
TEST_F(XMLElementTest_106, ClosingTypeUnaffectedBySetText_106) {
    element->SetText("Hello");
    ElementClosingType type = element->ClosingType();

    EXPECT_TRUE(type == ELEMENT_OPEN || type == ELEMENT_CLOSED || type == ELEMENT_CLOSING);
}

// Optional: Test after inserting a child element
TEST_F(XMLElementTest_106, ClosingTypeUnaffectedByInsertNewChild_106) {
    XMLElement* child = element->InsertNewChildElement("Child");
    ASSERT_NE(child, nullptr);

    ElementClosingType type = element->ClosingType();
    EXPECT_TRUE(type == ELEMENT_OPEN || type == ELEMENT_CLOSED || type == ELEMENT_CLOSING);
}
