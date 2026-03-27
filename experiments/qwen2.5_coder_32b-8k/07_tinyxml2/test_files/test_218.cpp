#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_218, SetAttributeString_NormalOperation_218) {

    const char* testValue = "testValue";

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeInt_NormalOperation_218) {

    int testValue = 42;

    attr.SetAttribute(testValue);

    EXPECT_EQ(attr.IntValue(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeUnsignedInt_NormalOperation_218) {

    unsigned int testValue = 42u;

    attr.SetAttribute(testValue);

    EXPECT_EQ(attr.UnsignedValue(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeInt64_NormalOperation_218) {

    int64_t testValue = 42LL;

    attr.SetAttribute(testValue);

    EXPECT_EQ(attr.Int64Value(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeUnsigned64_NormalOperation_218) {

    uint64_t testValue = 42uLL;

    attr.SetAttribute(testValue);

    EXPECT_EQ(attr.Unsigned64Value(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeBool_NormalOperation_218) {

    bool testValue = true;

    attr.SetAttribute(testValue);

    EXPECT_EQ(attr.BoolValue(), testValue);



    testValue = false;

    attr.SetAttribute(testValue);

    EXPECT_EQ(attr.BoolValue(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeDouble_NormalOperation_218) {

    double testValue = 3.14;

    attr.SetAttribute(testValue);

    EXPECT_DOUBLE_EQ(attr.DoubleValue(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeFloat_NormalOperation_218) {

    float testValue = 3.14f;

    attr.SetAttribute(testValue);

    EXPECT_FLOAT_EQ(attr.FloatValue(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeString_EmptyString_218) {

    const char* testValue = "";

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), testValue);

}



TEST_F(XMLAttributeTest_218, SetAttributeString_NullPointer_218) {

    const char* testValue = nullptr;

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), "");

}
