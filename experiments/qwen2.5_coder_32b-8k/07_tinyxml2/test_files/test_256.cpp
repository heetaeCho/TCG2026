#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLElement* element;



    void SetUp() override {

        XMLDocument doc;

        element = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_256, DoubleText_DefaultValue_ReturnedWhenNoText_256) {

    double result = element->DoubleText(42.0);

    EXPECT_DOUBLE_EQ(result, 42.0);

}



TEST_F(XMLElementTest_256, DoubleText_ValidNumber_ReturnedCorrectly_256) {

    element->SetText("123.45");

    double result = element->DoubleText(42.0);

    EXPECT_DOUBLE_EQ(result, 123.45);

}



TEST_F(XMLElementTest_256, DoubleText_InvalidNumber_ReturnsDefaultValue_256) {

    element->SetText("abc");

    double result = element->DoubleText(42.0);

    EXPECT_DOUBLE_EQ(result, 42.0);

}



TEST_F(XMLElementTest_256, DoubleText_EmptyString_ReturnsDefaultValue_256) {

    element->SetText("");

    double result = element->DoubleText(42.0);

    EXPECT_DOUBLE_EQ(result, 42.0);

}



TEST_F(XMLElementTest_256, DoubleText_Zero_ReturnedCorrectly_256) {

    element->SetText("0");

    double result = element->DoubleText(42.0);

    EXPECT_DOUBLE_EQ(result, 0.0);

}
