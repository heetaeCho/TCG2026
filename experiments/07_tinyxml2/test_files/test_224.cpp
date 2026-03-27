#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_224 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_224, SetDoubleValue_Positive_224) {

    double value = 123.456;

    attr.SetAttribute(value);

    EXPECT_STREQ(attr.Value(), "123.456");

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_Negative_224) {

    double value = -987.654;

    attr.SetAttribute(value);

    EXPECT_STREQ(attr.Value(), "-987.654");

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_Zero_224) {

    double value = 0.0;

    attr.SetAttribute(value);

    EXPECT_STREQ(attr.Value(), "0");

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_LargePositive_224) {

    double value = 1e20;

    attr.SetAttribute(value);

    // The exact string representation may vary, but it should be a valid large number string

    EXPECT_TRUE(std::string(attr.Value()).find("e") != std::string::npos || 

                std::string(attr.Value()).find("E") != std::string::npos);

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_LargeNegative_224) {

    double value = -1e20;

    attr.SetAttribute(value);

    // The exact string representation may vary, but it should be a valid large number string with negative sign

    EXPECT_TRUE(std::string(attr.Value()).find("-") != std::string::npos &&

                (std::string(attr.Value()).find("e") != std::string::npos || 

                 std::string(attr.Value()).find("E") != std::string::npos));

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_MaxBoundary_224) {

    double value = DBL_MAX;

    attr.SetAttribute(value);

    // The exact string representation may vary, but it should be a valid large number string

    EXPECT_TRUE(std::string(attr.Value()).find("e") != std::string::npos || 

                std::string(attr.Value()).find("E") != std::string::npos);

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_MinBoundary_224) {

    double value = DBL_MIN;

    attr.SetAttribute(value);

    // The exact string representation may vary, but it should be a valid small number string

    EXPECT_TRUE(std::string(attr.Value()).find("e") != std::string::npos || 

                std::string(attr.Value()).find("E") != std::string::npos);

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_NaN_224) {

    double value = std::numeric_limits<double>::quiet_NaN();

    attr.SetAttribute(value);

    // The exact string representation of NaN can vary, but it should not be a normal number

    EXPECT_FALSE(std::string(attr.Value()).find("e") != std::string::npos || 

                 std::string(attr.Value()).find("E") != std::string::npos ||

                 std::string(attr.Value()) == "0");

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_Infinity_224) {

    double value = std::numeric_limits<double>::infinity();

    attr.SetAttribute(value);

    // The exact string representation of infinity can vary

    EXPECT_TRUE(std::string(attr.Value()).find("inf") != std::string::npos ||

                std::string(attr.Value()).find("INF") != std::string::npos);

}



TEST_F(XMLAttributeTest_224, SetDoubleValue_NegativeInfinity_224) {

    double value = -std::numeric_limits<double>::infinity();

    attr.SetAttribute(value);

    // The exact string representation of negative infinity can vary

    EXPECT_TRUE(std::string(attr.Value()).find("-inf") != std::string::npos ||

                std::string(attr.Value()).find("-INF") != std::string::npos);

}
