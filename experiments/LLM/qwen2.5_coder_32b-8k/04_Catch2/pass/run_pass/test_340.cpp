#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_random_floating_point_helpers.hpp"



using namespace Catch::Detail;



TEST(count_equidistant_floats_340, NormalOperation_PositiveValues_340) {

    float a = 1.0f;

    float b = 5.0f;

    float distance = 1.0f;

    EXPECT_EQ(count_equidistant_floats(a, b, distance), 5);

}



TEST(count_equidistant_floats_340, NormalOperation_NegativeValues_340) {

    float a = -5.0f;

    float b = -1.0f;

    float distance = 1.0f;

    EXPECT_EQ(count_equidistant_floats(a, b, distance), 5);

}



TEST(count_equidistant_floats_340, NormalOperation_MixedValues_340) {

    float a = -2.0f;

    float b = 2.0f;

    float distance = 1.0f;

    EXPECT_EQ(count_equidistant_floats(a, b, distance), 5);

}



TEST(count_equidistant_floats_340, BoundaryCondition_ZeroDistance_340) {

    float a = 1.0f;

    float b = 5.0f;

    float distance = 0.0f;

    EXPECT_THROW(count_equidistant_floats(a, b, distance), std::exception);

}



TEST(count_equidistant_floats_340, BoundaryCondition_EqualEndpoints_340) {

    float a = 1.0f;

    float b = 1.0f;

    float distance = 1.0f;

    EXPECT_EQ(count_equidistant_floats(a, b, distance), 1);

}



TEST(count_equidistant_floats_340, BoundaryCondition_SmallDistance_340) {

    float a = 1.0f;

    float b = 5.0f;

    float distance = 0.1f;

    EXPECT_EQ(count_equidistant_floats(a, b, distance), 41);

}



TEST(count_equidistant_floats_340, ExceptionalCase_AGreaterThanB_340) {

    float a = 5.0f;

    float b = 1.0f;

    float distance = 1.0f;

    EXPECT_DEATH_IF_SUPPORTED(count_equidistant_floats(a, b, distance), ".*");

}
