#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

#include <limits>



using namespace YAML::jkj::dragonbox;



// Test fixture for dragonbox tests

class DragonboxTest_429 : public ::testing::Test {

protected:

    // Common setup code can be placed here if needed

};



TEST_F(DragonboxTest_429, NormalOperation_PositiveValue_429) {

    double value = 123.456;

    auto result = to_decimal(value);

    EXPECT_TRUE(result.success());

}



TEST_F(DragonboxTest_429, NormalOperation_NegativeValue_429) {

    double value = -123.456;

    auto result = to_decimal(value);

    EXPECT_TRUE(result.success());

}



TEST_F(DragonboxTest_429, BoundaryCondition_Zero_429) {

    double value = 0.0;

    auto result = to_decimal(value);

    // Assuming zero is not considered finite and non-zero based on assert(br.is_finite() && br.is_nonzero())

    EXPECT_FALSE(result.success());

}



TEST_F(DragonboxTest_429, BoundaryCondition_MaxDouble_429) {

    double value = std::numeric_limits<double>::max();

    auto result = to_decimal(value);

    EXPECT_TRUE(result.success());

}



TEST_F(DragonboxTest_429, BoundaryCondition_MinDouble_429) {

    double value = std::numeric_limits<double>::min();

    auto result = to_decimal(value);

    EXPECT_TRUE(result.success());

}



TEST_F(DragonboxTest_429, ExceptionalCase_NaN_429) {

    double value = std::numeric_limits<double>::quiet_NaN();

    auto result = to_decimal(value);

    // Assuming NaN is not considered finite and non-zero based on assert(br.is_finite() && br.is_nonzero())

    EXPECT_FALSE(result.success());

}



TEST_F(DragonboxTest_429, ExceptionalCase_Infinity_429) {

    double value = std::numeric_limits<double>::infinity();

    auto result = to_decimal(value);

    // Assuming infinity is not considered finite and non-zero based on assert(br.is_finite() && br.is_nonzero())

    EXPECT_FALSE(result.success());

}



TEST_F(DragonboxTest_429, ExceptionalCase_NegativeInfinity_429) {

    double value = -std::numeric_limits<double>::infinity();

    auto result = to_decimal(value);

    // Assuming negative infinity is not considered finite and non-zero based on assert(br.is_finite() && br.is_nonzero())

    EXPECT_FALSE(result.success());

}
