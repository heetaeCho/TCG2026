#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_77, FloatValue_ReturnsDefaultValue_77) {

    float result = attr.FloatValue();

    EXPECT_EQ(result, 0.0f);

}



TEST_F(XMLAttributeTest_77, QueryFloatValue_Success_77) {

    float value = 3.14f;

    XMLError error = attr.QueryFloatValue(&value);

    EXPECT_EQ(error, XML_NO_ERROR);

    EXPECT_EQ(value, 0.0f); // Assuming default value remains unchanged

}



TEST_F(XMLAttributeTest_77, QueryFloatValue_NullPointer_77) {

    float* nullPtr = nullptr;

    XMLError error = attr.QueryFloatValue(nullPtr);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}
