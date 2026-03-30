#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest_492 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_492, SetBoolLengthFormat_LongBool_GlobalScope_ReturnsTrue_492) {

    EXPECT_TRUE(emitterState.SetBoolLengthFormat(LongBool, FmtScope::global));

}



TEST_F(EmitterStateTest_492, SetBoolLengthFormat_ShortBool_LocalScope_ReturnsTrue_492) {

    EXPECT_TRUE(emitterState.SetBoolLengthFormat(ShortBool, FmtScope::local));

}



TEST_F(EmitterStateTest_492, SetBoolLengthFormat_DefaultCase_ReturnsFalse_492) {

    EMITTER_MANIP invalidValue = static_cast<EMITTER_MANIP>(-1);

    EXPECT_FALSE(emitterState.SetBoolLengthFormat(invalidValue, FmtScope::local));

}



TEST_F(EmitterStateTest_492, SetBoolLengthFormat_DefaultCase_GlobalScope_ReturnsFalse_492) {

    EMITTER_MANIP invalidValue = static_cast<EMITTER_MANIP>(-1);

    EXPECT_FALSE(emitterState.SetBoolLengthFormat(invalidValue, FmtScope::global));

}
