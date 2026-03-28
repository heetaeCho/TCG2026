#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace log {



// Test fixture for floor_log5_pow2_minus_log5_3 function

class FloorLog5Pow2MinusLog53Test : public ::testing::Test {

protected:

    using Int = stdr::int_least32_t;

};



TEST_F(FloorLog5Pow2MinusLog53Test, NormalOperation_PositiveExponent_324) {

    EXPECT_EQ(floor_log5_pow2_minus_log5_3<Int>(10), 6);

}



TEST_F(FloorLog5Pow2MinusLog53Test, NormalOperation_NegativeExponent_324) {

    EXPECT_EQ(floor_log5_pow2_minus_log5_3<Int>(-10), -7);

}



TEST_F(FloorLog5Pow2MinusLog53Test, BoundaryCondition_MinExponent_324) {

    EXPECT_EQ(floor_log5_pow2_minus_log5_3<Int>(-3543), -8169);

}



TEST_F(FloorLog5Pow2MinusLog53Test, BoundaryCondition_MaxExponent_324) {

    EXPECT_EQ(floor_log5_pow2_minus_log5_3<Int>(2427), 5340);

}



TEST_F(FloorLog5Pow2MinusLog53Test, EdgeCase_ZeroExponent_324) {

    EXPECT_EQ(floor_log5_pow2_minus_log5_3<Int>(0), 0);

}



// Assuming that the function is noexcept and does not throw exceptions for any input within its range

// Therefore, no exceptional or error cases are expected to be observable through the interface



} } } } }
