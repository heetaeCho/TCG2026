#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLE Document doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_241, SetTextBoolTrue_241) {

    element->SetText(true);

    EXPECT_STREQ(element->GetText(), "true");

}



TEST_F(XMLElementTest_241, SetTextBoolFalse_241) {

    element->SetText(false);

    EXPECT_STREQ(element->GetText(), "false");

}



TEST_F(XMLElementTest_241, GetTextDefaultAfterSet_241) {

    element->SetText(true);

    EXPECT_TRUE(element->BoolText(false));

    element->SetText(false);

    EXPECT_FALSE(element->BoolText(true));

}



TEST_F(XMLElementTest_241, SetTextBoundaryTrueFalse_241) {

    element->SetText(static_cast<bool>(0));

    EXPECT_STREQ(element->GetText(), "false");

    element->SetText(static_cast<bool>(1));

    EXPECT_STREQ(element->GetText(), "true");

}



TEST_F(XMLElementTest_241, QueryBoolTextSuccess_241) {

    bool value;

    element->SetText(true);

    EXPECT_EQ(element->QueryBoolText(&value), XML_SUCCESS);

    EXPECT_TRUE(value);

    element->SetText(false);

    EXPECT_EQ(element->QueryBoolText(&value), XML_SUCCESS);

    EXPECT_FALSE(value);

}



TEST_F(XMLElementTest_241, QueryBoolTextFailure_241) {

    bool value;

    element->SetText("not_a_bool");

    EXPECT_NE(element->QueryBoolText(&value), XML_SUCCESS);

}
