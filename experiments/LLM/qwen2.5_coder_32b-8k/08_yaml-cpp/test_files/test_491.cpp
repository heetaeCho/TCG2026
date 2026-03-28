#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest_491 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_491, SetBoolFormat_ValidValues_ReturnTrue_491) {

    EXPECT_TRUE(emitterState.SetBoolFormat(OnOffBool, FmtScope::Local));

    EXPECT_TRUE(emitterState.SetBoolFormat(TrueFalseBool, FmtScope::Global));

    EXPECT_TRUE(emitterState.SetBoolFormat(YesNoBool, FmtScope::BlockStyle));

}



TEST_F(EmitterStateTest_491, SetBoolFormat_InvalidValue_ReturnFalse_491) {

    EXPECT_FALSE(emitterState.SetBoolFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::Local));

    EXPECT_FALSE(emitterState.SetBoolFormat(static_cast<EMITTER_MANIP>(256), FmtScope::Global));

}



TEST_F(EmitterStateTest_491, SetBoolFormat_ScopeValues_ReturnTrue_491) {

    EXPECT_TRUE(emitterState.SetBoolFormat(OnOffBool, FmtScope::Local));

    EXPECT_TRUE(emitterState.SetBoolFormat(TrueFalseBool, FmtScope::Global));

    EXPECT_TRUE(emitterState.SetBoolFormat(YesNoBool, FmtScope::BlockStyle));

}



TEST_F(EmitterStateTest_491, SetBoolFormat_MultipleValidCalls_ReturnTrue_491) {

    EXPECT_TRUE(emitterState.SetBoolFormat(OnOffBool, FmtScope::Local));

    EXPECT_TRUE(emitterState.SetBoolFormat(TrueFalseBool, FmtScope::Global));

    EXPECT_TRUE(emitterState.SetBoolFormat(YesNoBool, FmtScope::BlockStyle));

}



TEST_F(EmitterStateTest_491, SetBoolFormat_DefaultBehavior_ReturnTrue_491) {

    EXPECT_TRUE(emitterState.SetBoolFormat(OnOffBool, FmtScope::Local));

}
