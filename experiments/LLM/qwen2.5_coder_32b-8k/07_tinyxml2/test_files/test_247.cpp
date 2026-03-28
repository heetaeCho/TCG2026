#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_247 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_247, QueryUnsigned64Text_SuccessfulConversion_247) {

    const char* textValue = "18446744073709551615"; // uint64_t max

    element->SetText(textValue);



    uint64_t result;

    XMLError error = element->QueryUnsigned64Text(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, 18446744073709551615u);

}



TEST_F(XMLElementTest_247, QueryUnsigned64Text_ZeroValue_247) {

    element->SetText("0");



    uint64_t result;

    XMLError error = element->QueryUnsigned64Text(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, 0u);

}



TEST_F(XMLElementTest_247, QueryUnsigned64Text_NoTextNode_247) {

    element->DeleteChild(element->FirstChild());



    uint64_t result;

    XMLError error = element->QueryUnsigned64Text(&result);

    EXPECT_EQ(error, XML_NO_TEXT_NODE);

}



TEST_F(XMLElementTest_247, QueryUnsigned64Text_CanNotConvertText_247) {

    element->SetText("not_a_number");



    uint64_t result;

    XMLError error = element->QueryUnsigned64Text(&result);

    EXPECT_EQ(error, XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_247, QueryUnsigned64Text_BoundaryConditionMax_247) {

    const char* textValue = "18446744073709551615"; // uint64_t max

    element->SetText(textValue);



    uint64_t result;

    XMLError error = element->QueryUnsigned64Text(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, 18446744073709551615u);

}



TEST_F(XMLElementTest_247, QueryUnsigned64Text_BoundaryConditionMin_247) {

    element->SetText("0");



    uint64_t result;

    XMLError error = element->QueryUnsigned64Text(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, 0u);

}
