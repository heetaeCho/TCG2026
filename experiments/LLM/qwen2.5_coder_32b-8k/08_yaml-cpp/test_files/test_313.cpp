#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML {

namespace jkj {

namespace dragonbox {

namespace detail {



using namespace testing;



TEST(compute_power_Test_313, PowerOfZero_313) {

    EXPECT_EQ(compute_power<0, int>(2), 1);

}



TEST(compute_power_Test_313, PowerOfOne_313) {

    EXPECT_EQ(compute_power<1, int>(2), 2);

}



TEST(compute_power_Test_313, PowerOfTwo_313) {

    EXPECT_EQ(compute_power<2, int>(2), 4);

}



TEST(compute_power_Test_313, PowerOfThree_313) {

    EXPECT_EQ(compute_power<3, int>(2), 8);

}



TEST(compute_power_Test_313, LargePower_313) {

    EXPECT_EQ(compute_power<10, int>(2), 1024);

}



TEST(compute_power_Test_313, PowerOfZeroWithNonTrivialBase_313) {

    EXPECT_EQ(compute_power<0, int>(5), 1);

}



TEST(compute_power_Test_313, NegativeBaseEvenPower_313) {

    EXPECT_EQ(compute_power<2, int>(-3), 9);

}



TEST(compute_power_Test_313, NegativeBaseOddPower_313) {

    EXPECT_EQ(compute_power<3, int>(-3), -27);

}



} // namespace detail

} // namespace dragonbox

} // namespace jkj

} // namespace YAML
