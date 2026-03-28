#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::log;



TEST_F(DragonboxFloorLog5Pow2Test_323, NormalOperation_PositiveExponent_323) {

    EXPECT_EQ(floor_log5_pow2(10), 6);

}



TEST_F(DragonboxFloorLog5Pow2Test_323, NormalOperation_NegativeExponent_323) {

    EXPECT_EQ(floor_log5_pow2(-10), -7);

}



TEST_F(DragonboxFloorLog5Pow2Test_323, BoundaryCondition_MinExponent_323) {

    EXPECT_EQ(floor_log5_pow2(-1831), -4096);

}



TEST_F(DragonboxFloorLog5Pow2Test_323, BoundaryCondition_MaxExponent_323) {

    EXPECT_EQ(floor_log5_pow2(1831), 3979);

}



TEST_F(DragonboxFloorLog5Pow2Test_323, EdgeCase_ZeroExponent_323) {

    EXPECT_EQ(floor_log5_pow2(0), 0);

}



// Assuming that the function handles large values gracefully within its constraints

TEST_F(DragonboxFloorLog5Pow2Test_323, LargeValue_Exponent_323) {

    EXPECT_EQ(floor_log5_pow2(1000000), 430676);

}



// Assuming that the function handles small values gracefully within its constraints

TEST_F(DragonboxFloorLog5Pow2Test_323, SmallValue_Exponent_323) {

    EXPECT_EQ(floor_log5_pow2(-1000000), -430677);

}

```


