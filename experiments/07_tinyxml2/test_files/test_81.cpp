#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_81 : public ::testing::Test {

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



TEST_F(XMLElementTest_81, QueryIntAttribute_NormalOperation_81) {

    int value;

    element->SetAttribute("test", 42);

    EXPECT_EQ(XML_SUCCESS, element->QueryIntAttribute("test", &value));

    EXPECT_EQ(42, value);

}



TEST_F(XMLElementTest_81, QueryIntAttribute_NoAttribute_81) {

    int value = 0;

    EXPECT_EQ(XML_NO_ATTRIBUTE, element->QueryIntAttribute("nonexistent", &value));

    EXPECT_EQ(0, value); // Ensure the value is unchanged

}



TEST_F(XMLElementTest_81, QueryIntAttribute_WrongType_81) {

    int value = 0;

    element->SetAttribute("test", "not an integer");

    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, element->QueryIntAttribute("test", &value));

    EXPECT_EQ(0, value); // Ensure the value is unchanged

}



TEST_F(XMLElementTest_81, QueryIntAttribute_BoundaryCondition_Zero_81) {

    int value;

    element->SetAttribute("test", 0);

    EXPECT_EQ(XML_SUCCESS, element->QueryIntAttribute("test", &value));

    EXPECT_EQ(0, value);

}



TEST_F(XMLElementTest_81, QueryIntAttribute_BoundaryCondition_MaxInt_81) {

    int value;

    element->SetAttribute("test", INT_MAX);

    EXPECT_EQ(XML_SUCCESS, element->QueryIntAttribute("test", &value));

    EXPECT_EQ(INT_MAX, value);

}



TEST_F(XMLElementTest_81, QueryIntAttribute_BoundaryCondition_MinInt_81) {

    int value;

    element->SetAttribute("test", INT_MIN);

    EXPECT_EQ(XML_SUCCESS, element->QueryIntAttribute("test", &value));

    EXPECT_EQ(INT_MIN, value);

}
