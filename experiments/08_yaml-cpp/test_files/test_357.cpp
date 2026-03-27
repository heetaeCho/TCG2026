#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



class NearestToEvenPolicyTest_357 : public ::testing::Test {

protected:

    using SignedSignificandBits = int;

};



TEST_F(NearestToEvenPolicyTest_357, ShorterInterval_ReturnsEmptyInterval_NormalOperation_357) {

    auto result = nearest_to_even_t::shorter_interval(SignedSignificandBits{0});

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}



TEST_F(NearestToEvenPolicyTest_357, ShorterInterval_ReturnsEmptyInterval_BoundaryCondition_Zero_357) {

    auto result = nearest_to_even_t::shorter_interval(SignedSignificandBits{0});

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}



TEST_F(NearestToEvenPolicyTest_357, ShorterInterval_ReturnsEmptyInterval_BoundaryCondition_MaxPositive_357) {

    auto result = nearest_to_even_t::shorter_interval(std::numeric_limits<SignedSignificandBits>::max());

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}



TEST_F(NearestToEvenPolicyTest_357, ShorterInterval_ReturnsEmptyInterval_BoundaryCondition_MaxNegative_357) {

    auto result = nearest_to_even_t::shorter_interval(std::numeric_limits<SignedSignificandBits>::min());

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}



TEST_F(NearestToEvenPolicyTest_357, ShorterInterval_ReturnsEmptyInterval_ExceptionalCase_NegativeOne_357) {

    auto result = nearest_to_even_t::shorter_interval(SignedSignificandBits{-1});

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}
