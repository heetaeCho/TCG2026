#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_223 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_223, SetBooleanTrue_223) {

    attr.SetAttribute(true);

    EXPECT_STREQ(attr.Value(), "true");

}



TEST_F(XMLAttributeTest_223, SetBooleanFalse_223) {

    attr.SetAttribute(false);

    EXPECT_STREQ(attr.Value(), "false");

}



TEST_F(XMLAttributeTest_223, DefaultConstructorValue_223) {

    EXPECT_STREQ(attr.Value(), "");

}



// Since the buffer size is 200, we can test a boundary condition with a string of length 199

TEST_F(XMLAttributeTest_223, LargeStringValue_223) {

    std::string largeString(199, 'a');

    attr.SetAttribute(largeString.c_str());

    EXPECT_STREQ(attr.Value(), largeString.c_str());

}



// Test to ensure that a string of length 200 (one character less than the buffer size) is handled correctly

TEST_F(XMLAttributeTest_223, MaxLengthStringValue_223) {

    std::string maxLengthString(199, 'a'); // One character less than BUF_SIZE to avoid null termination issues in test comparison

    maxLengthString += '\0'; // Manually add the null terminator

    attr.SetAttribute(maxLengthString.c_str());

    EXPECT_STREQ(attr.Value(), maxLengthString.c_str());

}



// Test to ensure that a string of length 201 (one character more than the buffer size) is handled correctly

TEST_F(XMLAttributeTest_223, OverflowStringValue_223) {

    std::string overflowString(201, 'a');

    attr.SetAttribute(overflowString.c_str());

    // The behavior here is undefined as per the current implementation, but we can check if it doesn't crash and behaves reasonably

    EXPECT_TRUE(attr.Value()[0] != '\0'); // Ensure that something was set

}
