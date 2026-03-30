#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_91 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        if (element) {

            doc.InsertFirstChild(element);

        }

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_91, QueryAttribute_NormalOperation_Int64_91) {

    int64_t value = 0;

    element->SetAttribute("testAttr", static_cast<int64_t>(123456789));

    XMLError result = element->QueryAttribute("testAttr", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_EQ(value, 123456789);

}



TEST_F(XMLElementTest_91, QueryAttribute_BoundaryCondition_EmptyString_91) {

    int64_t value = 0;

    XMLError result = element->QueryAttribute("", &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_91, QueryAttribute_ErrorCase_AttributeNotFound_91) {

    int64_t value = 0;

    XMLError result = element->QueryAttribute("nonExistentAttr", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_91, QueryAttribute_ErrorCase_WrongType_91) {

    element->SetAttribute("testAttr", "notAnInt");

    int64_t value = 0;

    XMLError result = element->QueryAttribute("testAttr", &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
