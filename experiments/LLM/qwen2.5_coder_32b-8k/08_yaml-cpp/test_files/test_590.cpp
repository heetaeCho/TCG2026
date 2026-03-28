#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"



using namespace YAML::conversion;



TEST(IsInfinityTest_590, PositiveInfinityWithDotInf_590) {

    EXPECT_TRUE(IsInfinity(".inf"));

}



TEST(IsInfinityTest_590, PositiveInfinityWithCapitalizedDotInf_590) {

    EXPECT_TRUE(IsInfinity(".Inf"));

}



TEST(IsInfinityTest_590, PositiveInfinityWithUpperCaseDotINF_590) {

    EXPECT_TRUE(IsInfinity(".INF"));

}



TEST(IsInfinityTest_590, PositiveInfinityWithPlusAndDotInf_590) {

    EXPECT_TRUE(IsInfinity("+.inf"));

}



TEST(IsInfinityTest_590, PositiveInfinityWithPlusAndCapitalizedDotInf_590) {

    EXPECT_TRUE(IsInfinity("+.Inf"));

}



TEST(IsInfinityTest_590, PositiveInfinityWithPlusAndUpperCaseDotINF_590) {

    EXPECT_TRUE(IsInfinity("+.INF"));

}



TEST(IsInfinityTest_590, NegativeInfinity_ShouldReturnFalse_590) {

    EXPECT_FALSE(IsInfinity("-.inf"));

}



TEST(IsInfinityTest_590, NonInfinityString_ShouldReturnFalse_590) {

    EXPECT_FALSE(IsInfinity("not_infinity"));

}



TEST(IsInfinityTest_590, EmptyString_ShouldReturnFalse_590) {

    EXPECT_FALSE(IsInfinity(""));

}



TEST(IsInfinityTest_590, InfinityWithSpaces_ShouldReturnFalse_590) {

    EXPECT_FALSE(IsInfinity(".inf "));

    EXPECT_FALSE(IsInfinity(" .inf"));

}



TEST(IsInfinityTest_590, MixedCaseNonStandardFormat_ShouldReturnFalse_590) {

    EXPECT_FALSE(IsInfinity("+.InF"));

}
