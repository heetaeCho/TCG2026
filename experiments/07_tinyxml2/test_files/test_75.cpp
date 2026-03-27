#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLAttributeTest_75 : public ::testing::Test {

protected:

    XMLAttribute attribute;

};



TEST_F(XMLAttributeTest_75, BoolValue_ReturnsFalseByDefault_75) {

    EXPECT_FALSE(attribute.BoolValue());

}



// Assuming QueryBoolValue modifies the value when successful

TEST_F(XMLAttributeTest_75, BoolValue_ReturnsTrueAfterSettingTrue_75) {

    bool value = true;

    attribute.QueryBoolValue(&value);

    EXPECT_TRUE(attribute.BoolValue());

}



TEST_F(XMLAttributeTest_75, BoolValue_ReturnsFalseAfterSettingFalse_75) {

    bool value = false;

    attribute.QueryBoolValue(&value);

    EXPECT_FALSE(attribute.BoolValue());

}



// Test boundary conditions and exceptional cases

TEST_F(XMLAttributeTest_75, QueryBoolValue_SuccessWithTrue_75) {

    bool value = true;

    XMLError result = attribute.QueryBoolValue(&value);

    EXPECT_EQ(result, XML_NO_ERROR);

}



TEST_F(XMLAttributeTest_75, QueryBoolValue_SuccessWithFalse_75) {

    bool value = false;

    XMLError result = attribute.QueryBoolValue(&value);

    EXPECT_EQ(result, XML_NO_ERROR);

}



// Assuming an invalid state or input could cause a specific error

// This is speculative and based on typical behavior; if the implementation never returns errors, this can be omitted.

// TEST_F(XMLAttributeTest_75, QueryBoolValue_ErrorHandling_75) {

//     bool value = false;

//     XMLError result = attribute.QueryBoolValue(nullptr);

//     EXPECT_EQ(result, XML_ERROR_PARSING_ATTRIBUTE);

// }



TEST_F(XMLAttributeTest_75, SetAttribute_BoolTrue_AffectsBoolValue_75) {

    attribute.SetAttribute(true);

    EXPECT_TRUE(attribute.BoolValue());

}



TEST_F(XMLAttributeTest_75, SetAttribute_BoolFalse_AffectsBoolValue_75) {

    attribute.SetAttribute(false);

    EXPECT_FALSE(attribute.BoolValue());

}
