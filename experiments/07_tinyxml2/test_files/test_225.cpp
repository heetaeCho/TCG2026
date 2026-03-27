#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_225 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_225, SetAttribute_Float_Normal_225) {

    float value = 123.456f;

    attr.SetAttribute(value);

    float retrievedValue = 0.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}



TEST_F(XMLAttributeTest_225, SetAttribute_Float_Zero_225) {

    float value = 0.0f;

    attr.SetAttribute(value);

    float retrievedValue = -1.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}



TEST_F(XMLAttributeTest_225, SetAttribute_Float_Negative_225) {

    float value = -123.456f;

    attr.SetAttribute(value);

    float retrievedValue = 0.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}



TEST_F(XMLAttributeTest_225, SetAttribute_Float_BoundaryMax_225) {

    float value = std::numeric_limits<float>::max();

    attr.SetAttribute(value);

    float retrievedValue = 0.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}



TEST_F(XMLAttributeTest_225, SetAttribute_Float_BoundaryMin_225) {

    float value = std::numeric_limits<float>::lowest();

    attr.SetAttribute(value);

    float retrievedValue = 0.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}



TEST_F(XMLAttributeTest_225, SetAttribute_Float_Epsilon_225) {

    float value = std::numeric_limits<float>::epsilon();

    attr.SetAttribute(value);

    float retrievedValue = 0.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}



TEST_F(XMLAttributeTest_225, SetAttribute_Float_SmallPositive_225) {

    float value = 1.0e-38f;

    attr.SetAttribute(value);

    float retrievedValue = 0.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}



TEST_F(XMLAttributeTest_225, SetAttribute_Float_SmallNegative_225) {

    float value = -1.0e-38f;

    attr.SetAttribute(value);

    float retrievedValue = 0.0f;

    XMLError err = attr.QueryFloatValue(&retrievedValue);

    EXPECT_EQ(err, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(retrievedValue, value);

}
