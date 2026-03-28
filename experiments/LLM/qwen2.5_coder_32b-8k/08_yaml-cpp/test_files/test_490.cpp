#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_490, SetStringFormat_ValidValues_GlobalScope_ReturnsTrue_490) {

    EXPECT_TRUE(emitter_state.SetStringFormat(Auto, FmtScope::Global));

    EXPECT_TRUE(emitter_state.SetStringFormat(SingleQuoted, FmtScope::Global));

    EXPECT_TRUE(emitter_state.SetStringFormat(DoubleQuoted, FmtScope::Global));

    EXPECT_TRUE(emitter_state.SetStringFormat(Literal, FmtScope::Global));

}



TEST_F(EmitterStateTest_490, SetStringFormat_ValidValues_LocalScope_ReturnsTrue_490) {

    EXPECT_TRUE(emitter_state.SetStringFormat(Auto, FmtScope::Local));

    EXPECT_TRUE(emitter_state.SetStringFormat(SingleQuoted, FmtScope::Local));

    EXPECT_TRUE(emitter_state.SetStringFormat(DoubleQuoted, FmtScope::Local));

    EXPECT_TRUE(emitter_state.SetStringFormat(Literal, FmtScope::Local));

}



TEST_F(EmitterStateTest_490, SetStringFormat_InvalidValue_GlobalScope_ReturnsFalse_490) {

    EXPECT_FALSE(emitter_state.SetStringFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::Global));

    EXPECT_FALSE(emitter_state.SetStringFormat(static_cast<EMITTER_MANIP>(35), FmtScope::Global));

}



TEST_F(EmitterStateTest_490, SetStringFormat_InvalidValue_LocalScope_ReturnsFalse_490) {

    EXPECT_FALSE(emitter_state.SetStringFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::Local));

    EXPECT_FALSE(emitter_state.SetStringFormat(static_cast<EMITTER_MANIP>(35), FmtScope::Local));

}
