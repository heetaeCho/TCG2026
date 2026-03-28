#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_216 : public ::testing::Test {

protected:

    float result;

    XMLError error;

    XMLAttribute xmlAttribute;



    void SetUp() override {

        result = 0.0f;

        error = XML_SUCCESS;

    }

};



TEST_F(XMLAttributeTest_216, QueryFloatValue_ValidInput_ReturnsSuccessAndCorrectValue_216) {

    const char* validValue = "3.14";

    xmlAttribute.SetAttribute(validValue);



    error = xmlAttribute.QueryFloatValue(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_FLOAT_EQ(result, 3.14f);

}



TEST_F(XMLAttributeTest_216, QueryFloatValue_EmptyString_ReturnsWrongAttributeType_216) {

    const char* emptyValue = "";

    xmlAttribute.SetAttribute(emptyValue);



    error = xmlAttribute.QueryFloatValue(&result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_216, QueryFloatValue_NonNumericString_ReturnsWrongAttributeType_216) {

    const char* nonNumericValue = "abc";

    xmlAttribute.SetAttribute(nonNumericValue);



    error = xmlAttribute.QueryFloatValue(&result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_216, QueryFloatValue_LargeNumber_ReturnsSuccessAndCorrectValue_216) {

    const char* largeValue = "3.402823e+38";

    xmlAttribute.SetAttribute(largeValue);



    error = xmlAttribute.QueryFloatValue(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    // The actual value might not be exactly the same due to precision limits of float

    EXPECT_FLOAT_EQ(result, 3.402823e+38f);

}



TEST_F(XMLAttributeTest_216, QueryFloatValue_SmallNumber_ReturnsSuccessAndCorrectValue_216) {

    const char* smallValue = "1.175494e-38";

    xmlAttribute.SetAttribute(smallValue);



    error = xmlAttribute.QueryFloatValue(&result);

    EXPECT_EQ(error, XML_SUCCESS);

    // The actual value might not be exactly the same due to precision limits of float

    EXPECT_FLOAT_EQ(result, 1.175494e-38f);

}
