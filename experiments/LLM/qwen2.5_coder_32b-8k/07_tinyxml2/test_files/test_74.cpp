#include <gtest/gtest.h>

#include <tinyxml2/tinyxml2.h>



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_74, UnsignedValue_ReturnsCorrectValue_74) {

    unsigned int value = 42;

    EXPECT_EQ(XMLError::XML_SUCCESS, attr.QueryUnsignedValue(&value));

    EXPECT_EQ(42u, attr.UnsignedValue());

}



TEST_F(XMLAttributeTest_74, UnsignedValue_DefaultValueIsZero_74) {

    unsigned int value = 0;

    EXPECT_EQ(0u, attr.UnsignedValue());

}



TEST_F(XMLAttributeTest_74, QueryUnsignedValue_SuccessOnValidInput_74) {

    unsigned int value = 123;

    EXPECT_EQ(XMLError::XML_SUCCESS, attr.QueryUnsignedValue(&value));

}



TEST_F(XMLAttributeTest_74, QueryUnsignedValue_ErrorOnInvalidInput_74) {

    // Since we cannot modify the internal state, we assume that an invalid input

    // would be provided through a different interface or setup. Here, we just test

    // the failure case by passing a nullptr.

    unsigned int* nullPtr = nullptr;

    EXPECT_EQ(XMLError::XML_ERROR_PARSING_ATTRIBUTE, attr.QueryUnsignedValue(nullPtr));

}
