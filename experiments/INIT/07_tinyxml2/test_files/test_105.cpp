#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Fixture for XMLElement tests
class XMLElementTest_105 : public ::testing::Test {
protected:
    void SetUp() override {
        // No internal state setup needed; treating as black box
    }

    void TearDown() override {
        // Cleanup if necessary
    }

    XMLElement element;
};

// Normal case: No attributes set
TEST_F(XMLElementTest_105, FirstAttributeReturnsNullWhenNoAttributes_105) {
    const XMLAttribute* attr = element.FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// Normal case: Add a single attribute and verify FirstAttribute returns non-null
TEST_F(XMLElementTest_105, FirstAttributeReturnsNonNullWhenAttributeExists_105) {
    element.SetAttribute("name", "value");
    const XMLAttribute* attr = element.FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "name");
    EXPECT_STREQ(attr->Value(), "value");
}

// Boundary case: Multiple attributes, verify FirstAttribute returns the first added
TEST_F(XMLElementTest_105, FirstAttributeReturnsFirstAddedAttribute_105) {
    element.SetAttribute("first", "1");
    element.SetAttribute("second", "2");

    const XMLAttribute* attr = element.FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    EXPECT_STREQ(attr->Value(), "1");
}

// Edge case: Deleting an attribute and checking FirstAttribute
TEST_F(XMLElementTest_105, FirstAttributeAfterDeleteAttribute_105) {
    element.SetAttribute("toDelete", "value");
    element.DeleteAttribute("toDelete");

    const XMLAttribute* attr = element.FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// Edge case: FirstAttribute on newly inserted child element
TEST_F(XMLElementTest_105, FirstAttributeOnNewChildElement_105) {
    XMLElement* child = element.InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    const XMLAttribute* attr = child->FirstAttribute();
    EXPECT_EQ(attr, nullptr);

    child->SetAttribute("childAttr", "val");
    attr = child->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "childAttr");
    EXPECT_STREQ(attr->Value(), "val");
}
