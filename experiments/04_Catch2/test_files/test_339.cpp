#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_random_floating_point_helpers.hpp"



using namespace Catch::Detail;



TEST(gamma_Function_339, ReturnsCorrectGammaForFloat_339) {

    float a = 1.0f;

    float b = 2.0f;

    float result = gamma<float>(a, b);

    EXPECT_FLOAT_EQ(result, std::nextafter(b, -std::numeric_limits<float>::infinity()) - b);

}



TEST(gamma_Function_339, ReturnsCorrectGammaForDouble_339) {

    double a = 1.0;

    double b = 2.0;

    double result = gamma<double>(a, b);

    EXPECT_DOUBLE_EQ(result, std::nextafter(b, -std::numeric_limits<double>::infinity()) - b);

}



TEST(gamma_Function_339, GammaUpLessThanGammaDown_339) {

    float a = 1.0f;

    float b = 2.0f;

    float gamma_up = std::nextafter(a, std::numeric_limits<float>::infinity()) - a;

    float gamma_down = b - std::nextafter(b, -std::numeric_limits<float>::infinity());

    if (gamma_up < gamma_down) {

        EXPECT_FLOAT_EQ(gamma<float>(a, b), gamma_down);

    }

}



TEST(gamma_Function_339, GammaUpGreaterThanGammaDown_339) {

    float a = 1.0f;

    float b = std::nextafter(1.5f, std::numeric_limits<float>::infinity());

    float gamma_up = std::nextafter(a, std::numeric_limits<float>::infinity()) - a;

    float gamma_down = b - std::nextafter(b, -std::numeric_limits<float>::infinity());

    if (gamma_up > gamma_down) {

        EXPECT_FLOAT_EQ(gamma<float>(a, b), gamma_up);

    }

}



TEST(gamma_Function_339, BoundaryConditionEqualValues_339) {

    float a = 1.0f;

    float b = 1.0f;

    float result = gamma<float>(a, b);

    EXPECT_FLOAT_EQ(result, std::nextafter(b, -std::numeric_limits<float>::infinity()) - b);

}



TEST(gamma_Function_339, BoundaryConditionMinFloatValues_339) {

    float a = std::numeric_limits<float>::min();

    float b = std::nextafter(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());

    float result = gamma<float>(a, b);

    EXPECT_FLOAT_EQ(result, b - a);

}



TEST(gamma_Function_339, BoundaryConditionMaxFloatValues_339) {

    float a = std::nextafter(std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest());

    float b = std::numeric_limits<float>::max();

    float result = gamma<float>(a, b);

    EXPECT_FLOAT_EQ(result, b - a);

}



TEST(gamma_Function_339, BoundaryConditionEqualValuesDouble_339) {

    double a = 1.0;

    double b = 1.0;

    double result = gamma<double>(a, b);

    EXPECT_DOUBLE_EQ(result, std::nextafter(b, -std::numeric_limits<double>::infinity()) - b);

}



TEST(gamma_Function_339, BoundaryConditionMinDoubleValues_339) {

    double a = std::numeric_limits<double>::min();

    double b = std::nextafter(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

    double result = gamma<double>(a, b);

    EXPECT_DOUBLE_EQ(result, b - a);

}



TEST(gamma_Function_339, BoundaryConditionMaxDoubleValues_339) {

    double a = std::nextafter(std::numeric_limits<double>::max(), std::numeric_limits<double>::lowest());

    double b = std::numeric_limits<double>::max();

    double result = gamma<double>(a, b);

    EXPECT_DOUBLE_EQ(result, b - a);

}
