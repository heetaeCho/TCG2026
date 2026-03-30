#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_458 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_458, GetNullFormat_DefaultValue_458) {

    EXPECT_EQ(emitter_state.GetNullFormat(), EMITTER_MANIP()); // Assuming EMITTER_MANIP() is the default value

}



TEST_F(EmitterStateTest_458, SetNullFormat_Success_458) {

    ASSERT_TRUE(emitter_state.SetNullFormat(EMITTER_MANIP::VALUE, FmtScope::BLOCK));

    EXPECT_EQ(emitter_state.GetNullFormat(), EMITTER_MANIP::VALUE);

}



TEST_F(EmitterStateTest_458, SetNullFormat_ScopeLocal_458) {

    emitter_state.SetLocalValue(EMITTER_MANIP::OTHER_VALUE);

    ASSERT_TRUE(emitter_state.SetNullFormat(EMITTER_MANIP::VALUE, FmtScope::LOCAL));

    EXPECT_EQ(emitter_state.GetNullFormat(), EMITTER_MANIP::VALUE);

}



TEST_F(EmitterStateTest_458, SetNullFormat_ScopeGlobal_458) {

    emitter_state.SetLocalValue(EMITTER_MANIP::OTHER_VALUE);

    ASSERT_TRUE(emitter_state.SetNullFormat(EMITTER_MANIP::VALUE, FmtScope::GLOBAL));

    EXPECT_EQ(emitter_state.GetNullFormat(), EMITTER_MANIP::VALUE);

}



TEST_F(EmitterStateTest_458, SetNullFormat_InvalidScope_458) {

    // Assuming there is an invalid scope value defined in FmtScope

    EXPECT_FALSE(emitter_state.SetNullFormat(EMITTER_MANIP::VALUE, static_cast<FmtScope::value>(999)));

}



TEST_F(EmitterStateTest_458, SetNullFormat_ErrorHandling_458) {

    // Assuming there is a way to trigger an error in setting the null format

    // This would depend on the internal implementation details which we cannot infer,

    // but if there's any condition that could lead to failure, it should be tested.

    // For this example, let's assume setting an invalid value always fails:

    EXPECT_FALSE(emitter_state.SetNullFormat(static_cast<EMITTER_MANIP>(999), FmtScope::BLOCK));

}
