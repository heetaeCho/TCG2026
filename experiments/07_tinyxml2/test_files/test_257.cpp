#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLElement* element;



    void SetUp() override {

        XMLDocument doc;

        element = new XMLElement(&doc);

        element->SetText("1.5");

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_257, FloatText_ReturnsParsedValue_257) {

    float result = element->FloatText(0.0f);

    EXPECT_FLOAT_EQ(result, 1.5f);

}



TEST_F(XMLElementTest_257, FloatText_ReturnsDefaultValueWhenTextIsNotAFloat_257) {

    element->SetText("invalid_float");

    float result = element->FloatText(3.0f);

    EXPECT_FLOAT_EQ(result, 3.0f);

}



TEST_F(XMLElementTest_257, FloatText_ReturnsDefaultValueWhenTextIsEmpty_257) {

    element->SetText("");

    float result = element->FloatText(4.5f);

    EXPECT_FLOAT_EQ(result, 4.5f);

}



TEST_F(XMLElementTest_257, FloatText_HandlesBoundaryValues_257) {

    element->SetText("3.4028234e+38"); // Max float value

    float result = element->FloatText(0.0f);

    EXPECT_FLOAT_EQ(result, 3.4028234e+38);



    element->SetText("-3.4028234e+38"); // Min float value

    result = element->FloatText(0.0f);

    EXPECT_FLOAT_EQ(result, -3.4028234e+38);

}



TEST_F(XMLElementTest_257, FloatText_ReturnsDefaultValueWhenTextIsTooLarge_257) {

    element->SetText("1e+40"); // Larger than max float value

    float result = element->FloatText(6.0f);

    EXPECT_FLOAT_EQ(result, 6.0f);



    element->SetText("-1e+40"); // Smaller than min float value

    result = element->FloatText(7.0f);

    EXPECT_FLOAT_EQ(result, 7.0f);

}
