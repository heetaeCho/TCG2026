#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_238 : public ::testing::Test {

protected:

    XMLDocument* doc;

    XMLElement* element;



    void SetUp() override {

        doc = new XMLDocument();

        element = doc->NewElement("TestElement");

        doc->LinkEndChild(element);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLElementTest_238, SetTextUnsignedNormalOperation_238) {

    unsigned value = 12345;

    element->SetText(value);



    const char* text = element->GetText();

    ASSERT_STREQ(text, "12345");

}



TEST_F(XMLElementTest_238, SetTextUnsignedBoundaryConditionZero_238) {

    unsigned value = 0;

    element->SetText(value);



    const char* text = element->GetText();

    ASSERT_STREQ(text, "0");

}



TEST_F(XMLElementTest_238, SetTextUnsignedBoundaryConditionMaxValue_238) {

    unsigned value = UINT_MAX;

    element->SetText(value);



    const char* text = element->GetText();

    std::string expected = std::to_string(UINT_MAX);

    ASSERT_STREQ(text, expected.c_str());

}
