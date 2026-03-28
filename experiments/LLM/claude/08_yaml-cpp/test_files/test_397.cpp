#include <gtest/gtest.h>
#include <cstdint>
#include <cmath>
#include <limits>
#include <string>
#include <sstream>

// Include the dragonbox header
#include "contrib/dragonbox.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/emitter.h"

// The dragonbox implementation is used internally for float-to-string conversion.
// We test it through observable behavior: converting floating point values to 
// their string representations via YAML emission or through the dragonbox 
// to_decimal interface if available.

class DragonboxTest_397 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal double values through YAML emission
TEST_F(DragonboxTest_397, NormalDoubleEmission_397) {
    YAML::Emitter emitter;
    emitter << 3.14;
    std::string result = emitter.c_str();
    // The emitted value should parse back to the same double
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 3.14);
}

TEST_F(DragonboxTest_397, ZeroDoubleEmission_397) {
    YAML::Emitter emitter;
    emitter << 0.0;
    std::string result = emitter.c_str();
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 0.0);
}

TEST_F(DragonboxTest_397, NegativeDoubleEmission_397) {
    YAML::Emitter emitter;
    emitter << -2.718281828;
    std::string result = emitter.c_str();
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -2.718281828);
}

TEST_F(DragonboxTest_397, SmallDoubleEmission_397) {
    YAML::Emitter emitter;
    double val = 1e-10;
    emitter << val;
    std::string result = emitter.c_str();
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, val);
}

TEST_F(DragonboxTest_397, LargeDoubleEmission_397) {
    YAML::Emitter emitter;
    double val = 1e+15;
    emitter << val;
    std::string result = emitter.c_str();
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, val);
}

TEST_F(DragonboxTest_397, FloatEmission_397) {
    YAML::Emitter emitter;
    emitter << 1.5f;
    std::string result = emitter.c_str();
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 1.5f);
}

TEST_F(DragonboxTest_397, OnePointZeroEmission_397) {
    YAML::Emitter emitter;
    emitter << 1.0;
    std::string result = emitter.c_str();
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1.0);
}

TEST_F(DragonboxTest_397, VerySmallSubnormalLikeValue_397) {
    YAML::Emitter emitter;
    double val = 5e-324; // smallest positive double (subnormal)
    emitter << val;
    std::string result = emitter.c_str();
    // Should at least produce a valid string
    EXPECT_FALSE(result.empty());
}

TEST_F(DragonboxTest_397, MaxDoubleEmission_397) {
    YAML::Emitter emitter;
    double val = std::numeric_limits<double>::max();
    emitter << val;
    std::string result = emitter.c_str();
    EXPECT_FALSE(result.empty());
}

TEST_F(DragonboxTest_397, MinPositiveDoubleEmission_397) {
    YAML::Emitter emitter;
    double val = std::numeric_limits<double>::min();
    emitter << val;
    std::string result = emitter.c_str();
    EXPECT_FALSE(result.empty());
}

TEST_F(DragonboxTest_397, RoundTripMultipleValues_397) {
    double values[] = {0.1, 0.2, 0.3, 1.0/3.0, 2.0/3.0, 
                       1e-5, 1e5, 1e-20, 1e20, 
                       123456789.0, 0.123456789};
    for (double val : values) {
        YAML::Emitter emitter;
        emitter << val;
        std::string result = emitter.c_str();
        double parsed = std::stod(result);
        EXPECT_DOUBLE_EQ(parsed, val) << "Failed for value: " << val;
    }
}

TEST_F(DragonboxTest_397, NegativeZeroEmission_397) {
    YAML::Emitter emitter;
    emitter << -0.0;
    std::string result = emitter.c_str();
    EXPECT_FALSE(result.empty());
}

TEST_F(DragonboxTest_397, InfinityEmission_397) {
    YAML::Emitter emitter;
    double val = std::numeric_limits<double>::infinity();
    emitter << val;
    std::string result = emitter.c_str();
    EXPECT_FALSE(result.empty());
}

TEST_F(DragonboxTest_397, NaNEmission_397) {
    YAML::Emitter emitter;
    double val = std::numeric_limits<double>::quiet_NaN();
    emitter << val;
    std::string result = emitter.c_str();
    EXPECT_FALSE(result.empty());
}

TEST_F(DragonboxTest_397, NegativeInfinityEmission_397) {
    YAML::Emitter emitter;
    double val = -std::numeric_limits<double>::infinity();
    emitter << val;
    std::string result = emitter.c_str();
    EXPECT_FALSE(result.empty());
}

TEST_F(DragonboxTest_397, PowersOfTwo_397) {
    for (int exp = -50; exp <= 50; ++exp) {
        double val = std::ldexp(1.0, exp);
        YAML::Emitter emitter;
        emitter << val;
        std::string result = emitter.c_str();
        double parsed = std::stod(result);
        EXPECT_DOUBLE_EQ(parsed, val) << "Failed for 2^" << exp;
    }
}

TEST_F(DragonboxTest_397, FloatRoundTrip_397) {
    float values[] = {0.1f, 0.5f, 1.0f, 3.14f, -2.5f, 1e10f, 1e-10f};
    for (float val : values) {
        YAML::Emitter emitter;
        emitter << val;
        std::string result = emitter.c_str();
        float parsed = std::stof(result);
        EXPECT_FLOAT_EQ(parsed, val) << "Failed for float value: " << val;
    }
}
