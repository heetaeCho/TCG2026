#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_248 : public ::testing::Test {

protected:

    XMLElement* xmlElement;

    XMLDocument* doc;



    void SetUp() override {

        doc = new XMLDocument();

        xmlElement = new XMLElement(doc);

    }



    void TearDown() override {

        delete xmlElement;

        delete doc;

    }

};



TEST_F(XMLElementTest_248, QueryBoolText_NormalOperation_True_248) {

    bool result;

    xmlElement->SetText("true");

    EXPECT_EQ(xmlElement->QueryBoolText(&result), XML_SUCCESS);

    EXPECT_TRUE(result);

}



TEST_F(XMLElementTest_248, QueryBoolText_NormalOperation_False_248) {

    bool result;

    xmlElement->SetText("false");

    EXPECT_EQ(xmlElement->QueryBoolText(&result), XML_SUCCESS);

    EXPECT_FALSE(result);

}



TEST_F(XMLElementTest_248, QueryBoolText_BoundaryCondition_EmptyString_248) {

    bool result;

    xmlElement->SetText("");

    EXPECT_EQ(xmlElement->QueryBoolText(&result), XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_248, QueryBoolText_ErrorCase_NonBooleanString_248) {

    bool result;

    xmlElement->SetText("not_a_boolean");

    EXPECT_EQ(xmlElement->QueryBoolText(&result), XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_248, QueryBoolText_ErrorCase_NoTextNode_248) {

    bool result;

    xmlElement->DeleteChildren();

    EXPECT_EQ(xmlElement->QueryBoolText(&result), XML_NO_TEXT_NODE);

}
