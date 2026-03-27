#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



using namespace YAML;



class EmitterStateTest_452 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_452, HasBegunContent_InitialValue_452) {

    EXPECT_FALSE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_452, HasBegunContent_SetAnchor_452) {

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_452, HasBegunContent_SetAlias_452) {

    emitter_state.SetAlias();

    EXPECT_FALSE(emitter_state.HasBegunContent()); // Alias does not set content

}



TEST_F(EmitterStateTest_452, HasBegunContent_SetTag_452) {

    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_452, HasBegunContent_MultipleSets_452) {

    emitter_state.SetAnchor();

    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasBegunContent());



    emitter_state.SetAlias();

    EXPECT_TRUE(emitter_state.HasBegunContent()); // Content already set

}



TEST_F(EmitterStateTest_452, HasBegunContent_ResetAfterSet_452) {

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasBegunContent());



    // No reset method provided in the interface to clear m_hasAnchor or m_hasTag

    // Assuming that HasBegunContent only resets if all content indicators are cleared,

    // which is not possible with current public methods.

}



TEST_F(EmitterStateTest_452, HasBegunContent_NoContentSet_452) {

    emitter_state.SetNonContent();

    EXPECT_FALSE(emitter_state.HasBegunContent()); // Non-content does not set content

}
