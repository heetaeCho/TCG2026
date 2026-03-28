#include <gtest/gtest.h>

#include "emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest_495 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_495, SetIntFormat_Dec_Global_495) {

    EXPECT_TRUE(emitter_state.SetIntFormat(Dec, FmtScope::value::Global));

}



TEST_F(EmitterStateTest_495, SetIntFormat_Hex_Local_495) {

    EXPECT_TRUE(emitter_state.SetIntFormat(Hex, FmtScope::value::Local));

}



TEST_F(EmitterStateTest_495, SetIntFormat_Oct_Global_495) {

    EXPECT_TRUE(emitter_state.SetIntFormat(Oct, FmtScope::value::Global));

}



TEST_F(EmitterStateTest_495, SetIntFormat_InvalidValue_ReturnsFalse_495) {

    EXPECT_FALSE(emitter_state.SetIntFormat(static_cast<EMITTER_MANIP>(255), FmtScope::value::Local));

}



TEST_F(EmitterStateTest_495, SetIntFormat_BoundaryCondition_Dec_Local_495) {

    EXPECT_TRUE(emitter_state.SetIntFormat(Dec, FmtScope::value::Local));

}
