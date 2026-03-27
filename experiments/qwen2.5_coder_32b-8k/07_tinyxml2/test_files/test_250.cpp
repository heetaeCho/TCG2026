#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_250 : public ::testing::Test {

protected:

    XMLElement element;

};



TEST_F(XMLElementTest_250, QueryFloatText_SuccessfulConversion_250) {

    XMLText text("123.45");

    element.InsertEndChild(&text);



    float result = 0.0f;

    XMLError error = element.QueryFloatText(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_FLOAT_EQ(result, 123.45f);

}



TEST_F(XMLElementTest_250, QueryFloatText_InvalidConversion_250) {

    XMLText text("not_a_float");

    element.InsertEndChild(&text);



    float result = 0.0f;

    XMLError error = element.QueryFloatText(&result);

    EXPECT_EQ(error, XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_250, QueryFloatText_NoTextNode_250) {

    float result = 0.0f;

    XMLError error = element.QueryFloatText(&result);

    EXPECT_EQ(error, XML_NO_TEXT_NODE);

}



TEST_F(XMLElementTest_250, QueryFloatText_EmptyString_250) {

    XMLText text("");

    element.InsertEndChild(&text);



    float result = 0.0f;

    XMLError error = element.QueryFloatText(&result);

    EXPECT_EQ(error, XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_250, QueryFloatText_BoundaryPositiveMax_250) {

    XMLText text("3.402823466e+38");

    element.InsertEndChild(&text);



    float result = 0.0f;

    XMLError error = element.QueryFloatText(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::max());

}



TEST_F(XMLElementTest_250, QueryFloatText_BoundaryNegativeMax_250) {

    XMLText text("-3.402823466e+38");

    element.InsertEndChild(&text);



    float result = 0.0f;

    XMLError error = element.QueryFloatText(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::lowest());

}



TEST_F(XMLElementTest_250, QueryFloatText_ZeroValue_250) {

    XMLText text("0");

    element.InsertEndChild(&text);



    float result = 0.0f;

    XMLError error = element.QueryFloatText(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_FLOAT_EQ(result, 0.0f);

}
