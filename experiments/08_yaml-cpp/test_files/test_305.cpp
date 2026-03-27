#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::wuint;



TEST_F(uint128Test_305, DefaultConstructorInitializesToZero_305) {

    uint128 num;

    EXPECT_EQ(num.high(), 0);

    EXPECT_EQ(num.low(), 0);

}



TEST_F(uint128Test_305, ParameterizedConstructorSetsValuesCorrectly_305) {

    uint128 num(0x123456789ABCDEF0, 0xFEDCBA9876543210);

    EXPECT_EQ(num.high(), 0x123456789ABCDEF0);

    EXPECT_EQ(num.low(), 0xFEDCBA9876543210);

}



TEST_F(uint128Test_305, OperatorPlusEqualAddsCorrectlyWithinBounds_305) {

    uint128 num(0x0, 0xFFFFFFFFFFFFFFFF);

    num += 1;

    EXPECT_EQ(num.high(), 1);

    EXPECT_EQ(num.low(), 0);

}



TEST_F(uint128Test_305, OperatorPlusEqualHandlesLargeAdditionWithoutOverflow_305) {

    uint128 num(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);

    num += 1;

    EXPECT_EQ(num.high(), 0);

    EXPECT_EQ(num.low(), 0);

}



TEST_F(uint128Test_305, OperatorPlusEqualHandlesZeroAdditionCorrectly_305) {

    uint128 num(0xABCDEF1234567890, 0xFEDCBA0987654321);

    num += 0;

    EXPECT_EQ(num.high(), 0xABCDEF1234567890);

    EXPECT_EQ(num.low(), 0xFEDCBA0987654321);

}



TEST_F(uint128Test_305, OperatorPlusEqualHandlesBoundaryConditionCorrectly_305) {

    uint128 num(0xFFFFFFFFFFFFFFFF, 0x0);

    num += 1;

    EXPECT_EQ(num.high(), 1);

    EXPECT_EQ(num.low(), 0);

}
