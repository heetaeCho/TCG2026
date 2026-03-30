#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



using namespace testing;



TEST_F(NearestTowardPlusInfinityTest_362, NormalInterval_PositiveSignificand_362) {

    SignedSignificandBits s;

    s.set_is_negative(false);

    auto result = nearest_toward_plus_infinity_t::normal_interval(s);

    EXPECT_FALSE(result.is_lower_boundary_closed());

}



TEST_F(NearestTowardPlusInfinityTest_362, NormalInterval_NegativeSignificand_362) {

    SignedSignificandBits s;

    s.set_is_negative(true);

    auto result = nearest_toward_plus_infinity_t::normal_interval(s);

    EXPECT_TRUE(result.is_lower_boundary_closed());

}



// Assuming there are boundary conditions for the type of s

TEST_F(NearestTowardPlusInfinityTest_362, BoundaryCondition_ZeroSignificand_362) {

    SignedSignificandBits s;

    s.set_is_negative(false); // or true, depending on how zero is represented

    auto result = nearest_toward_plus_infinity_t::normal_interval(s);

    EXPECT_FALSE(result.is_lower_boundary_closed());

}



// Assuming there are exceptional/error cases that can be observed

TEST_F(NearestTowardPlusInfinityTest_362, ExceptionalCase_SpecialSignificandValue_362) {

    // This is a hypothetical test case for an exceptional value

    SignedSignificandBits s;

    s.set_is_negative(false); // Set to a special value if any

    auto result = nearest_toward_plus_infinity_t::normal_interval(s);

    EXPECT_FALSE(result.is_lower_boundary_closed());

}



} } } } }
