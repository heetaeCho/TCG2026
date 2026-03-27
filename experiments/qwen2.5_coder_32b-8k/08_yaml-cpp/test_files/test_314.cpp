#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



class CountFactorsTest_314 : public ::testing::Test {

protected:

    // No additional setup or teardown needed for this simple function.

};



TEST_F(CountFactorsTest_314, NormalOperation_PowerOfTwo_314) {

    EXPECT_EQ(count_factors<2, unsigned int>(8), 3);  // 2^3 = 8

}



TEST_F(CountFactorsTest_314, NormalOperation_MixedFactors_314) {

    EXPECT_EQ(count_factors<3, unsigned int>(18), 2);  // 3^2 * 2 = 18

}



TEST_F(CountFactorsTest_314, BoundaryCondition_ZeroInput_314) {

    EXPECT_EQ(count_factors<5, unsigned int>(0), 0);  // By convention, 0 has no factors.

}



TEST_F(CountFactorsTest_314, BoundaryCondition_OneInput_314) {

    EXPECT_EQ(count_factors<7, unsigned int>(1), 0);  // 1 is not divisible by any prime number.

}



TEST_F(CountFactorsTest_314, ExceptionalCase_PrimeNumber_314) {

    EXPECT_EQ(count_factors<11, unsigned int>(11), 1);  // 11 is a prime number itself.

}



TEST_F(CountFactorsTest_314, ExceptionalCase_NoFactor_314) {

    EXPECT_EQ(count_factors<2, unsigned int>(5), 0);  // 5 is not divisible by 2.

}



} } } }
