#include <gtest/gtest.h>

#include "emitterstate.h"

#include "yaml-cpp/emittermanip.h"



class EmitterStateTest_494 : public ::testing::Test {

protected:

    YAML::EmitterState emitterState;

};



TEST_F(EmitterStateTest_494, SetNullFormat_LowerNull_GlobalScope_ReturnsTrue_494) {

    EXPECT_TRUE(emitterState.SetNullFormat(YAML::LowerNull, YAML::FmtScope::Global));

}



TEST_F(EmitterStateTest_494, SetNullFormat_UpperNull_LocalScope_ReturnsTrue_494) {

    EXPECT_TRUE(emitterState.SetNullFormat(YAML::UpperNull, YAML::FmtScope::Local));

}



TEST_F(EmitterStateTest_494, SetNullFormat_CamelNull_BlockScope_ReturnsTrue_494) {

    EXPECT_TRUE(emitterState.SetNullFormat(YAML::CamelNull, YAML::FmtScope::Block));

}



TEST_F(EmitterStateTest_494, SetNullFormat_TildeNull_GlobalScope_ReturnsTrue_494) {

    EXPECT_TRUE(emitterState.SetNullFormat(YAML::TildeNull, YAML::FmtScope::Global));

}



TEST_F(EmitterStateTest_494, SetNullFormat_InvalidValue_ReturnsFalse_494) {

    EXPECT_FALSE(emitterState.SetNullFormat(static_cast<YAML::EMITTER_MANIP>(-1), YAML::FmtScope::Local));

}



TEST_F(EmitterStateTest_494, SetNullFormat_DefaultConstructor_IsGood_ReturnsTrue_494) {

    EXPECT_TRUE(emitterState.good());

}
