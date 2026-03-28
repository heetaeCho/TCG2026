#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



using namespace YAML;



class EmitterStateTest_455 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_455, GetBoolFormat_DefaultValue_455) {

    EXPECT_EQ(emitterState.GetBoolFormat(), EMITTER_MANIP_DEFAULT);

}



TEST_F(EmitterStateTest_455, SetBoolFormat_Success_455) {

    ASSERT_TRUE(emitterState.SetBoolFormat(EMITTER_MANIP_TRUE_LC, FmtScope::BLOCK));

    EXPECT_EQ(emitterState.GetBoolFormat(), EMITTER_MANIP_TRUE_LC);

}



TEST_F(EmitterStateTest_455, SetBoolFormat_InvalidValue_455) {

    ASSERT_FALSE(emitterState.SetBoolFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::BLOCK));

    EXPECT_EQ(emitterState.GetBoolFormat(), EMITTER_MANIP_DEFAULT);

}



TEST_F(EmitterStateTest_455, SetBoolFormat_GlobalScope_455) {

    emitterState.SetBoolFormat(EMITTER_MANIP_TRUE_LC, FmtScope::GLOBAL);

    EmitterState anotherEmitter;

    EXPECT_EQ(anotherEmitter.GetBoolFormat(), EMITTER_MANIP_TRUE_LC);

}



TEST_F(EmitterStateTest_455, SetBoolFormat_BlockScope_455) {

    emitterState.SetBoolFormat(EMITTER_MANIP_TRUE_LC, FmtScope::BLOCK);

    EmitterState anotherEmitter;

    EXPECT_EQ(anotherEmitter.GetBoolFormat(), EMITTER_MANIP_DEFAULT);

}



TEST_F(EmitterStateTest_455, SetBoolFormat_LocalValueOverride_455) {

    emitterState.SetBoolFormat(EMITTER_MANIP_TRUE_LC, FmtScope::BLOCK);

    emitterState.SetLocalValue(EMITTER_MANIP_TRUE_UC);

    EXPECT_EQ(emitterState.GetBoolFormat(), EMITTER_MANIP_TRUE_UC);

}



TEST_F(EmitterStateTest_455, SetBoolFormat_RestoreGlobalModifiedSettings_455) {

    emitterState.SetBoolFormat(EMITTER_MANIP_TRUE_LC, FmtScope::GLOBAL);

    EmitterState anotherEmitter;

    anotherEmitter.SetLocalValue(EMITTER_MANIP_TRUE_UC);

    anotherEmitter.RestoreGlobalModifiedSettings();

    EXPECT_EQ(anotherEmitter.GetBoolFormat(), EMITTER_MANIP_TRUE_LC);

}
