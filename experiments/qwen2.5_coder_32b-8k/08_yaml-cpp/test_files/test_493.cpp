#include <gtest/gtest.h>

#include "emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_SetBoolCaseFormat_493, ValidUpperCase_493) {

    EXPECT_TRUE(emitterState.SetBoolCaseFormat(UpperCase, FmtScope::value::GLOBAL));

}



TEST_F(EmitterStateTest_SetBoolCaseFormat_493, ValidLowerCase_493) {

    EXPECT_TRUE(emitterState.SetBoolCaseFormat(LowerCase, FmtScope::value::BLOCK));

}



TEST_F(EmitterStateTest_SetBoolCaseFormat_493, ValidCamelCase_493) {

    EXPECT_TRUE(emitterState.SetBoolCaseFormat(CamelCase, FmtScope::value::LOCAL));

}



TEST_F(EmitterStateTest_SetBoolCaseFormat_493, InvalidValue_493) {

    EXPECT_FALSE(emitterState.SetBoolCaseFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::value::GLOBAL));

}



TEST_F(EmitterStateTest_SetBoolCaseFormat_493, InvalidScope_493) {

    EXPECT_FALSE(emitterState.SetBoolCaseFormat(UpperCase, static_cast<FmtScope::value>(-1)));

}
