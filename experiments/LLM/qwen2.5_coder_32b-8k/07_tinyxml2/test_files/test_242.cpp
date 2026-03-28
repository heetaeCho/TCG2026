#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_242 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        ASSERT_NE(element, nullptr);

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_242, SetTextFloatNormal_242) {

    float value = 123.456f;

    element->SetText(value);



    const char* text = element->GetText();

    ASSERT_STREQ(text, "123.456");

}



TEST_F(XMLElementTest_242, SetTextFloatBoundaryPositive_242) {

    float value = std::numeric_limits<float>::max();

    element->SetText(value);



    const char* text = element->GetText();

    ASSERT_STREQ(text, "3.40282e+38");

}



TEST_F(XMLElementTest_242, SetTextFloatBoundaryNegative_242) {

    float value = std::numeric_limits<float>::lowest();

    element->SetText(value);



    const char* text = element->GetText();

    ASSERT_STREQ(text, "-3.40282e+38");

}



TEST_F(XMLElementTest_242, SetTextFloatZero_242) {

    float value = 0.0f;

    element->SetText(value);



    const char* text = element->GetText();

    ASSERT_STREQ(text, "0");

}
