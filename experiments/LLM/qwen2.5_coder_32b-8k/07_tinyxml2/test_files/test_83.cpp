#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_83 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_83, QueryInt64Attribute_AttributeExistsAndValid_83) {

    int64_t value;

    element->SetAttribute("testAttr", static_cast<int64_t>(12345));

    XMLError result = element->QueryInt64Attribute("testAttr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 12345);

}



TEST_F(XMLElementTest_83, QueryInt64Attribute_AttributeDoesNotExist_83) {

    int64_t value;

    XMLError result = element->QueryInt64Attribute("nonExistentAttr", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_83, QueryInt64Attribute_AttributeExistsButInvalidType_83) {

    int64_t value;

    element->SetAttribute("testAttr", "notAnInteger");

    XMLError result = element->QueryInt64Attribute("testAttr", &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_83, QueryInt64Attribute_AttributeValueIsMinInt64_83) {

    int64_t value;

    element->SetAttribute("testAttr", static_cast<int64_t>(INT64_MIN));

    XMLError result = element->QueryInt64Attribute("testAttr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, INT64_MIN);

}



TEST_F(XMLElementTest_83, QueryInt64Attribute_AttributeValueIsMaxInt64_83) {

    int64_t value;

    element->SetAttribute("testAttr", static_cast<int64_t>(INT64_MAX));

    XMLError result = element->QueryInt64Attribute("testAttr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, INT64_MAX);

}
