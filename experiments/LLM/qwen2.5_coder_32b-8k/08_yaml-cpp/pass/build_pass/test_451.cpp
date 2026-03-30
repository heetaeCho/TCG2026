#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_451 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_451, HasBegunNode_InitiallyFalse_451) {

    EXPECT_FALSE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_451, HasBegunNode_AfterSetAnchor_ReturnsTrue_451) {

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_451, HasBegunNode_AfterSetAlias_ReturnsFalse_451) {

    emitter_state.SetAlias();

    EXPECT_FALSE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_451, HasBegunNode_AfterSetTag_ReturnsTrue_451) {

    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_451, HasBegunNode_AfterSetNonContent_ReturnsTrue_451) {

    emitter_state.SetNonContent();

    EXPECT_TRUE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_451, HasBegunNode_MultipleCallsConsistent_451) {

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasBegunNode());

    EXPECT_TRUE(emitter_state.HasBegunNode());



    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_451, HasBegunNode_ResetAfterClearModifiedSettings_451) {

    emitter_state.SetAnchor();

    emitter_state.ClearModifiedSettings();

    EXPECT_FALSE(emitter_state.HasBegunNode());

}
