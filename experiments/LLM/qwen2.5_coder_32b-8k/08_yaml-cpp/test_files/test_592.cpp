#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"



class IsNaNTest_592 : public ::testing::Test {};



TEST_F(IsNaNTest_592, ValidNaNString_ReturnsTrue_592) {

    EXPECT_TRUE(YAML::conversion::IsNaN(".nan"));

}



TEST_F(IsNaNTest_592, ValidNaNStringUpperCase_ReturnsTrue_592) {

    EXPECT_TRUE(YAML::conversion::IsNaN(".NaN"));

}



TEST_F(IsNaNTest_592, ValidNANStringUpperCase_ReturnsTrue_592) {

    EXPECT_TRUE(YAML::conversion::IsNaN(".NAN"));

}



TEST_F(IsNaNTest_592, InvalidString_ReturnsFalse_592) {

    EXPECT_FALSE(YAML::conversion::IsNaN("not_nan"));

}



TEST_F(IsNaNTest_592, EmptyString_ReturnsFalse_592) {

    EXPECT_FALSE(YAML::conversion::IsNaN(""));

}



TEST_F(IsNaNTest_592, ShorterThanFourCharacters_ReturnsFalse_592) {

    EXPECT_FALSE(YAML::conversion::IsNaN(".na"));

}



TEST_F(IsNaNTest_592, DifferentCaseCombination_ReturnsFalse_592) {

    EXPECT_FALSE(YAML::conversion::IsNaN(".nAn"));

}
