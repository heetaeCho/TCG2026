#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



using namespace YAML;



class EmitterStateTest_450 : public ::testing::Test {

protected:

    EmitterState emitter_state_;

};



TEST_F(EmitterStateTest_450, HasTagInitiallyFalse_450) {

    EXPECT_FALSE(emitter_state_.HasTag());

}



TEST_F(EmitterStateTest_450, SetTagChangesHasTagToTrue_450) {

    emitter_state_.SetTag();

    EXPECT_TRUE(emitter_state_.HasTag());

}



TEST_F(EmitterStateTest_450, HasTagReturnsFalseAfterResetting_450) {

    emitter_state_.SetTag();

    emitter_state_.EndedDoc();  // Assuming EndedDoc resets the state

    EXPECT_FALSE(emitter_state_.HasTag());

}
