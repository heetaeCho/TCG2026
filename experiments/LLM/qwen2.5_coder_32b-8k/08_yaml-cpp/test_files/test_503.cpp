#include <gtest/gtest.h>

#include "emitterstate.h"



class EmitterStateTest_503 : public ::testing::Test {

protected:

    YAML::EmitterState emitter_state;

};



TEST_F(EmitterStateTest_503, SetDoublePrecision_NormalValue_ReturnsTrue_503) {

    EXPECT_TRUE(emitter_state.SetDoublePrecision(15, YAML::FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_503, SetDoublePrecision_MaxDigits10_ReturnsTrue_503) {

    EXPECT_TRUE(emitter_state.SetDoublePrecision(std::numeric_limits<double>::max_digits10, YAML::FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_503, SetDoublePrecision_ValueExceedingMaxDigits10_ReturnsFalse_503) {

    EXPECT_FALSE(emitter_state.SetDoublePrecision(std::numeric_limits<double>::max_digits10 + 1, YAML::FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_503, SetDoublePrecision_ZeroValue_ReturnsTrue_503) {

    EXPECT_TRUE(emitter_state.SetDoublePrecision(0, YAML::FmtScope::BLOCK));

}
