#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <limits>
#include <string>

// Include the header under test
#include "yaml-cpp/node/convert.h"

// Test fixture for inner_encode
class InnerEncodeTest_604 : public ::testing::Test {
protected:
    std::stringstream stream;
};

// ==================== float tests ====================

TEST_F(InnerEncodeTest_604, FloatNaN_604) {
    float val = std::numeric_limits<float>::quiet_NaN();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".nan");
}

TEST_F(InnerEncodeTest_604, FloatPositiveInfinity_604) {
    float val = std::numeric_limits<float>::infinity();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".inf");
}

TEST_F(InnerEncodeTest_604, FloatNegativeInfinity_604) {
    float val = -std::numeric_limits<float>::infinity();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), "-.inf");
}

TEST_F(InnerEncodeTest_604, FloatZero_604) {
    float val = 0.0f;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    // The result should represent zero
    EXPECT_DOUBLE_EQ(std::stof(result), 0.0f);
}

TEST_F(InnerEncodeTest_604, FloatNegativeZero_604) {
    float val = -0.0f;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(InnerEncodeTest_604, FloatPositiveValue_604) {
    float val = 3.14f;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, 3.14f, 0.01f);
}

TEST_F(InnerEncodeTest_604, FloatNegativeValue_604) {
    float val = -2.718f;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, -2.718f, 0.01f);
}

TEST_F(InnerEncodeTest_604, FloatSmallValue_604) {
    float val = std::numeric_limits<float>::min();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, FloatMaxValue_604) {
    float val = std::numeric_limits<float>::max();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, FloatLowestValue_604) {
    float val = std::numeric_limits<float>::lowest();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, FloatSignalingNaN_604) {
    float val = std::numeric_limits<float>::signaling_NaN();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".nan");
}

// ==================== double tests ====================

TEST_F(InnerEncodeTest_604, DoubleNaN_604) {
    double val = std::numeric_limits<double>::quiet_NaN();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".nan");
}

TEST_F(InnerEncodeTest_604, DoublePositiveInfinity_604) {
    double val = std::numeric_limits<double>::infinity();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".inf");
}

TEST_F(InnerEncodeTest_604, DoubleNegativeInfinity_604) {
    double val = -std::numeric_limits<double>::infinity();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), "-.inf");
}

TEST_F(InnerEncodeTest_604, DoubleZero_604) {
    double val = 0.0;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_DOUBLE_EQ(std::stod(result), 0.0);
}

TEST_F(InnerEncodeTest_604, DoublePositiveValue_604) {
    double val = 3.141592653589793;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.141592653589793, 1e-6);
}

TEST_F(InnerEncodeTest_604, DoubleNegativeValue_604) {
    double val = -2.718281828459045;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, -2.718281828459045, 1e-6);
}

TEST_F(InnerEncodeTest_604, DoubleMaxValue_604) {
    double val = std::numeric_limits<double>::max();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, DoubleLowestValue_604) {
    double val = std::numeric_limits<double>::lowest();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, DoubleSmallValue_604) {
    double val = std::numeric_limits<double>::min();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, DoubleDenormMin_604) {
    double val = std::numeric_limits<double>::denorm_min();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, DoubleSignalingNaN_604) {
    double val = std::numeric_limits<double>::signaling_NaN();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".nan");
}

TEST_F(InnerEncodeTest_604, DoubleOne_604) {
    double val = 1.0;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_DOUBLE_EQ(std::stod(result), 1.0);
}

TEST_F(InnerEncodeTest_604, DoubleNegativeOne_604) {
    double val = -1.0;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_DOUBLE_EQ(std::stod(result), -1.0);
}

// ==================== long double tests ====================

TEST_F(InnerEncodeTest_604, LongDoubleNaN_604) {
    long double val = std::numeric_limits<long double>::quiet_NaN();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".nan");
}

TEST_F(InnerEncodeTest_604, LongDoublePositiveInfinity_604) {
    long double val = std::numeric_limits<long double>::infinity();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), ".inf");
}

TEST_F(InnerEncodeTest_604, LongDoubleNegativeInfinity_604) {
    long double val = -std::numeric_limits<long double>::infinity();
    YAML::conversion::inner_encode(val, stream);
    EXPECT_EQ(stream.str(), "-.inf");
}

TEST_F(InnerEncodeTest_604, LongDoublePositiveValue_604) {
    long double val = 1.23456789L;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

// ==================== Precision tests ====================

TEST_F(InnerEncodeTest_604, DoublePrecisionRespected_604) {
    stream.precision(15);
    double val = 1.0 / 3.0;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1.0 / 3.0, 1e-14);
}

TEST_F(InnerEncodeTest_604, FloatEpsilon_604) {
    float val = std::numeric_limits<float>::epsilon();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, DoubleEpsilon_604) {
    double val = std::numeric_limits<double>::epsilon();
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

// ==================== Integer-like float values ====================

TEST_F(InnerEncodeTest_604, DoubleIntegerValue_604) {
    double val = 42.0;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 42.0);
}

TEST_F(InnerEncodeTest_604, FloatIntegerValue_604) {
    float val = 100.0f;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 100.0f);
}

// ==================== Multiple writes to stream ====================

TEST_F(InnerEncodeTest_604, MultipleEncodesAppendToStream_604) {
    double val1 = std::numeric_limits<double>::quiet_NaN();
    YAML::conversion::inner_encode(val1, stream);
    std::string first = stream.str();
    EXPECT_EQ(first, ".nan");

    // Reset stream for second write
    std::stringstream stream2;
    double val2 = std::numeric_limits<double>::infinity();
    YAML::conversion::inner_encode(val2, stream2);
    EXPECT_EQ(stream2.str(), ".inf");
}

TEST_F(InnerEncodeTest_604, DoubleNegativeZero_604) {
    double val = -0.0;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(InnerEncodeTest_604, FloatVeryLargeValue_604) {
    float val = 1.0e38f;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}

TEST_F(InnerEncodeTest_604, DoubleVerySmallNegative_604) {
    double val = -1.0e-300;
    YAML::conversion::inner_encode(val, stream);
    std::string result = stream.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, ".nan");
    EXPECT_NE(result, ".inf");
    EXPECT_NE(result, "-.inf");
}
