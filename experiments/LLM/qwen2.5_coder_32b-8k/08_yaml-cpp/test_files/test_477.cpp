#include <gtest/gtest.h>

#include "emitterstate.h"



class EmitterStateTest_477 : public ::testing::Test {

protected:

    YAML::EmitterState emitterState;

};



TEST_F(EmitterStateTest_477, StartedScalarClearsModifiedSettings_477) {

    // Assuming ClearModifiedSettings has some observable effect, which we need to verify.

    // Since the internal state is not accessible, we rely on any public method that might be affected by modified settings.

    emitterState.SetLocalValue(YAML::EMITTER_MANIP::Block);

    emitterState.StartedScalar();

    // We check if the local value was cleared as an indication that ClearModifiedSettings was called.

    EXPECT_NE(emitterState.GetStringFormat(), YAML::EMITTER_MANIP::Block);

}



TEST_F(EmitterStateTest_477, StartedScalarInvokesStartedNode_477) {

    // This test assumes that StartedNode has some observable effect, which we need to verify.

    // Since the internal state is not accessible, we rely on any public method that might be affected by StartedNode.

    emitterState.StartedScalar();

    // We check if HasBegunNode returns true as an indication that StartedNode was called.

    EXPECT_TRUE(emitterState.HasBegunNode());

}



TEST_F(EmitterStateTest_477, GoodAfterStartedScalar_477) {

    // Check if the state remains good after calling StartedScalar

    emitterState.StartedScalar();

    EXPECT_TRUE(emitterState.good());

}



TEST_F(EmitterStateTest_477, ErrorStatusUnchangedAfterStartedScalar_477) {

    // Set an error and check if it remains unchanged after calling StartedScalar

    emitterState.SetError("Initial Error");

    emitterState.StartedScalar();

    EXPECT_EQ(emitterState.GetLastError(), "Initial Error");

}
