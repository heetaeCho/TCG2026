#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute* attr;



    void SetUp() override {

        attr = new XMLAttribute();

    }



    void TearDown() override {

        delete attr;

    }

};



TEST_F(XMLAttributeTest_76, DoubleValue_DefaultIsZero_76) {

    EXPECT_EQ(attr->DoubleValue(), 0.0);

}



TEST_F(XMLAttributeTest_76, QueryDoubleValue_ValidNumber_ReturnsSuccess_76) {

    double value = 3.14;

    attr->SetAttribute(value);

    double result;

    EXPECT_EQ(attr->QueryDoubleValue(&result), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(result, value);

}



TEST_F(XMLAttributeTest_76, QueryDoubleValue_InvalidNumber_ReturnsFail_76) {

    attr->SetAttribute("not_a_number");

    double result;

    EXPECT_NE(attr->QueryDoubleValue(&result), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_76, SetAttribute_Double_SetsCorrectly_76) {

    double value = 2.718;

    attr->SetAttribute(value);

    EXPECT_DOUBLE_EQ(attr->DoubleValue(), value);

}



TEST_F(XMLAttributeTest_76, QueryDoubleValue_NullPointer_ReturnsFail_76) {

    EXPECT_NE(attr->QueryDoubleValue(nullptr), XML_SUCCESS);

}
