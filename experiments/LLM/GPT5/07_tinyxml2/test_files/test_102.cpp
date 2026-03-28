#include "tinyxml2.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace tinyxml2;

// Mock visitor to verify external interactions if needed
class MockVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (XMLElement*, const XMLAttribute*), (override));
    MOCK_METHOD(bool, VisitExit, (XMLElement*), (override));
};

// Test fixture for XMLElement tests
class XMLElementTest_102 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
        element = doc->NewElement("TestElement");
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
    XMLElement* element;
};

// Test normal operation: setting a boolean attribute
TEST_F(XMLElementTest_102, SetBooleanAttribute_Normal_102) {
    element->SetAttribute("enabled", true);
    bool value = false;
    XMLError err = element->QueryBoolAttribute("enabled", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);

    element->SetAttribute("enabled", false);
    value = true;
    err = element->QueryBoolAttribute("enabled", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test boundary: attribute name is an empty string
TEST_F(XMLElementTest_102, SetBooleanAttribute_EmptyName_102) {
    element->SetAttribute("", true);
    bool value = false;
    XMLError err = element->QueryBoolAttribute("", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test boundary: attribute name is very long
TEST_F(XMLElementTest_102, SetBooleanAttribute_LongName_102) {
    std::string longName(1024, 'a'); // 1024 chars
    element->SetAttribute(longName.c_str(), true);
    bool value = false;
    XMLError err = element->QueryBoolAttribute(longName.c_str(), &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test overwriting an existing attribute
TEST_F(XMLElementTest_102, SetBooleanAttribute_Overwrite_102) {
    element->SetAttribute("flag", true);
    element->SetAttribute("flag", false); // overwrite
    bool value = true;
    XMLError err = element->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test multiple boolean attributes coexist
TEST_F(XMLElementTest_102, SetBooleanAttribute_MultipleAttributes_102) {
    element->SetAttribute("attr1", true);
    element->SetAttribute("attr2", false);

    bool value1 = false;
    bool value2 = true;

    EXPECT_EQ(element->QueryBoolAttribute("attr1", &value1), XML_SUCCESS);
    EXPECT_TRUE(value1);

    EXPECT_EQ(element->QueryBoolAttribute("attr2", &value2), XML_SUCCESS);
    EXPECT_FALSE(value2);
}

// Optional: test interaction with a visitor (mocked)
TEST_F(XMLElementTest_102, AcceptVisitor_AttributeSet_102) {
    MockVisitor visitor;
    element->SetAttribute("visited", true);

    // Expect VisitEnter to be called once
    EXPECT_CALL(visitor, VisitEnter(element, testing::_)).Times(1);

    element->Accept(&visitor);
}
