#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/reporters/catch_reporter_helpers.hpp"



using namespace Catch;



TEST(getFormattedDuration_817, NormalOperation_PositiveValue_817) {

    double duration = 123.456;

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "123.456");

}



TEST(getFormattedDuration_817, NormalOperation_Zero_817) {

    double duration = 0.0;

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "0.000");

}



TEST(getFormattedDuration_817, NormalOperation_NegativeValue_817) {

    double duration = -987.654;

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "-987.654");

}



TEST(getFormattedDuration_817, BoundaryCondition_MaxDoubleValue_817) {

    double duration = DBL_MAX;

    std::string formattedDuration = getFormattedDuration(duration);

    size_t maxDoubleSize = DBL_MAX_10_EXP + 1 + 1 + 3 + 1;

    EXPECT_LE(formattedDuration.size(), maxDoubleSize);

}



TEST(getFormattedDuration_817, BoundaryCondition_MinDoubleValue_817) {

    double duration = DBL_MIN;

    std::string formattedDuration = getFormattedDuration(duration);

    size_t maxDoubleSize = DBL_MAX_10_EXP + 1 + 1 + 3 + 1;

    EXPECT_LE(formattedDuration.size(), maxDoubleSize);

}



TEST(getFormattedDuration_817, BoundaryCondition_LargePositiveValue_817) {

    double duration = 999999999.999;

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "1000000000.000");

}



TEST(getFormattedDuration_817, BoundaryCondition_LargeNegativeValue_817) {

    double duration = -999999999.999;

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "-1000000000.000");

}



TEST(getFormattedDuration_817, ExceptionalCase_NaN_817) {

    double duration = std::numeric_limits<double>::quiet_NaN();

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "nan"); // Note: Behavior might vary based on platform and compiler

}



TEST(getFormattedDuration_817, ExceptionalCase_Infinity_817) {

    double duration = std::numeric_limits<double>::infinity();

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "inf"); // Note: Behavior might vary based on platform and compiler

}



TEST(getFormattedDuration_817, ExceptionalCase_NegativeInfinity_817) {

    double duration = -std::numeric_limits<double>::infinity();

    std::string formattedDuration = getFormattedDuration(duration);

    EXPECT_EQ(formattedDuration, "-inf"); // Note: Behavior might vary based on platform and compiler

}
