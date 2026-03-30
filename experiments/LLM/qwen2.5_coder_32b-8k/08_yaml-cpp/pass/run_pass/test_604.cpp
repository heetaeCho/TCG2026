#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/node/convert.h>

#include <sstream>

#include <cmath>



using namespace YAML::conversion;



class YamlConversionTest_604 : public ::testing::Test {

protected:

    std::stringstream stream;

};



TEST_F(YamlConversionTest_604, FloatNormalOperation_604) {

    float value = 123.456f;

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), "123.456");

}



TEST_F(YamlConversionTest_604, DoubleNormalOperation_604) {

    double value = 789.012;

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), "789.012");

}



TEST_F(YamlConversionTest_604, FloatBoundaryZero_604) {

    float value = 0.0f;

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), "0");

}



TEST_F(YamlConversionTest_604, DoubleBoundaryZero_604) {

    double value = 0.0;

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), "0");

}



TEST_F(YamlConversionTest_604, FloatNanValue_604) {

    float value = std::nanf("");

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), ".nan");

}



TEST_F(YamlConversionTest_604, DoubleNanValue_604) {

    double value = std::nan("");

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), ".nan");

}



TEST_F(YamlConversionTest_604, FloatPositiveInfinity_604) {

    float value = std::numeric_limits<float>::infinity();

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), ".inf");

}



TEST_F(YamlConversionTest_604, DoublePositiveInfinity_604) {

    double value = std::numeric_limits<double>::infinity();

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), ".inf");

}



TEST_F(YamlConversionTest_604, FloatNegativeInfinity_604) {

    float value = -std::numeric_limits<float>::infinity();

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), "-.inf");

}



TEST_F(YamlConversionTest_604, DoubleNegativeInfinity_604) {

    double value = -std::numeric_limits<double>::infinity();

    inner_encode(value, stream);

    EXPECT_EQ(stream.str(), "-.inf");

}
