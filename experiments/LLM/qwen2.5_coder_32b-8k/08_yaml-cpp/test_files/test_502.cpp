#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_502 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_502, SetFloatPrecision_ValidValue_ReturnsTrue_502) {

    EXPECT_TRUE(emitterState.SetFloatPrecision(7, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_502, SetFloatPrecision_MaxDigits10_ReturnsTrue_502) {

    EXPECT_TRUE(emitterState.SetFloatPrecision(std::numeric_limits<float>::max_digits10, FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_502, SetFloatPrecision_ValueGreaterThanMaxDigits10_ReturnsFalse_502) {

    EXPECT_FALSE(emitterState.SetFloatPrecision(std::numeric_limits<float>::max_digits10 + 1, FmtScope::BLOCK));

}



TEST_F(EmitterStateTest_502, SetFloatPrecision_ZeroValue_ReturnsTrue_502) {

    EXPECT_TRUE(emitterState.SetFloatPrecision(0, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_502, SetFloatPrecision_BoundaryValue_ReturnsTrue_502) {

    EXPECT_TRUE(emitterState.SetFloatPrecision(1, FmtScope::BLOCK));

}
