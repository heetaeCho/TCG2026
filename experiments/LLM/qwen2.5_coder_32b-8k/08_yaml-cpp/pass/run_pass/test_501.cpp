#include <gtest/gtest.h>

#include "emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest_501 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_501, SetMapKeyFormat_Auto_GlobalScope_Success_501) {

    EXPECT_TRUE(emitter_state.SetMapKeyFormat(Auto, FmtScope::Global));

}



TEST_F(EmitterStateTest_501, SetMapKeyFormat_LongKey_LocalScope_Success_501) {

    EXPECT_TRUE(emitter_state.SetMapKeyFormat(LongKey, FmtScope::Local));

}



TEST_F(EmitterStateTest_501, SetMapKeyFormat_Default_GlobalScope_Failure_501) {

    EXPECT_FALSE(emitter_state.SetMapKeyFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::Global));

}



TEST_F(EmitterStateTest_501, SetMapKeyFormat_Default_LocalScope_Failure_501) {

    EXPECT_FALSE(emitter_state.SetMapKeyFormat(static_cast<EMITTER_MANIP>(42), FmtScope::Local));

}
