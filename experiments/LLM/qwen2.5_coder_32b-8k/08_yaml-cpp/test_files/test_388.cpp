#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace binary_to_decimal_rounding {



class DragonboxTest_388 : public ::testing::Test {

protected:

    using CarrierUInt = unsigned long long; // Assuming a common type for testing

};



TEST_F(DragonboxTest_388, PreferRoundDown_ReturnsFalseForNonZeroValue_388) {

    CarrierUInt value = 1;

    EXPECT_FALSE(away_from_zero::prefer_round_down(value));

}



TEST_F(DragonboxTest_388, PreferRoundDown_ReturnsFalseForMaxValue_388) {

    CarrierUInt value = std::numeric_limits<CarrierUInt>::max();

    EXPECT_FALSE(away_from_zero::prefer_round_down(value));

}



TEST_F(DragonboxTest_388, PreferRoundDown_ReturnsFalseForMinValue_388) {

    CarrierUInt value = std::numeric_limits<CarrierUInt>::min();

    EXPECT_FALSE(away_from_zero::prefer_round_down(value));

}



TEST_F(DragonboxTest_388, PreferRoundDown_ReturnsFalseForZeroValue_388) {

    CarrierUInt value = 0;

    EXPECT_FALSE(away_from_zero::prefer_round_down(value));

}



} } } } }
