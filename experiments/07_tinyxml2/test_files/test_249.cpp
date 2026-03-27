#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_249 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

    }



    void TearDown() override {

        if (element) {

            delete element;

        }

    }



    void SetText(const std::string& text) {

        if (!element->FirstChild()) {

            XMLText* textNode = doc.NewText(text.c_str());

            element->InsertEndChild(textNode);

        } else {

            static_cast<XMLText*>(element->FirstChild())->SetValue(text.c_str());

        }

    }

};



TEST_F(XMLElementTest_249, QueryDoubleText_ValidNumber_249) {

    double result;

    SetText("123.456");

    EXPECT_EQ(element->QueryDoubleText(&result), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(result, 123.456);

}



TEST_F(XMLElementTest_249, QueryDoubleText_ZeroValue_249) {

    double result;

    SetText("0.0");

    EXPECT_EQ(element->QueryDoubleText(&result), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(result, 0.0);

}



TEST_F(XMLElementTest_249, QueryDoubleText_IntegerValue_249) {

    double result;

    SetText("123");

    EXPECT_EQ(element->QueryDoubleText(&result), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(result, 123.0);

}



TEST_F(XMLElementTest_249, QueryDoubleText_NegativeNumber_249) {

    double result;

    SetText("-123.456");

    EXPECT_EQ(element->QueryDoubleText(&result), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(result, -123.456);

}



TEST_F(XMLElementTest_249, QueryDoubleText_ScientificNotation_249) {

    double result;

    SetText("1.23e-5");

    EXPECT_EQ(element->QueryDoubleText(&result), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(result, 0.0000123);

}



TEST_F(XMLElementTest_249, QueryDoubleText_NoTextNode_249) {

    double result;

    element->DeleteChildren();

    EXPECT_EQ(element->QueryDoubleText(&result), XML_NO_TEXT_NODE);

}



TEST_F(XMLElementTest_249, QueryDoubleText_CannotConvertText_249) {

    double result;

    SetText("not_a_number");

    EXPECT_EQ(element->QueryDoubleText(&result), XML_CAN_NOT_CONVERT_TEXT);

}
