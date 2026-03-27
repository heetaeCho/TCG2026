#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace detail {



class NearestPolicyTest_375 : public ::testing::Test {

protected:

    using SignedSignificandBits = int;

};



TEST_F(NearestPolicyTest_375, NormalInterval_ReturnsDefaultConstructedInterval_375) {

    auto interval = nearest::normal_interval(SignedSignificandBits{0});

    EXPECT_EQ(interval, interval_type::open{});

}



TEST_F(NearestPolicyTest_375, NormalInterval_BoundaryCondition_Zero_375) {

    auto interval = nearest::normal_interval(SignedSignificandBits{0});

    EXPECT_EQ(interval, interval_type::open{});

}



TEST_F(NearestPolicyTest_375, NormalInterval_NegativeValue_ReturnsDefaultConstructedInterval_375) {

    auto interval = nearest::normal_interval(SignedSignificandBits{-1});

    EXPECT_EQ(interval, interval_type::open{});

}



TEST_F(NearestPolicyTest_375, NormalInterval_PositiveValue_ReturnsDefaultConstructedInterval_375) {

    auto interval = nearest::normal_interval(SignedSignificandBits{1});

    EXPECT_EQ(interval, interval_type::open{});

}



}}}}}}


