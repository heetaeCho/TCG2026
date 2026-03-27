#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



using namespace YAML;



class EmitterStateTest_459 : public ::testing::Test {

protected:

    EmitterState state;

};



TEST_F(EmitterStateTest_459, GetIntFormat_DefaultValue_459) {

    EXPECT_EQ(state.GetIntFormat(), EMITTER_MANIP_DEFAULT);

}



TEST_F(EmitterStateTest_459, SetIntFormat_NormalOperation_459) {

    ASSERT_TRUE(state.SetIntFormat(EMITTER_MANIP_DECIMAL, FmtScope::BLOCK));

    EXPECT_EQ(state.GetIntFormat(), EMITTER_MANIP_DECIMAL);

}



TEST_F(EmitterStateTest_459, SetIntFormat_BoundaryCondition_459) {

    // Assuming valid range for EMITTER_MANIP includes DECIMAL and HEXADECIMAL

    ASSERT_TRUE(state.SetIntFormat(EMITTER_MANIP_HEXADECIMAL, FmtScope::BLOCK));

    EXPECT_EQ(state.GetIntFormat(), EMITTER_MANIP_HEXADECIMAL);

}



TEST_F(EmitterStateTest_459, SetIntFormat_ErrorCase_459) {

    // Assuming invalid value for EMITTER_MANIP is outside of defined values

    EXPECT_FALSE(state.SetIntFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::BLOCK));

}
