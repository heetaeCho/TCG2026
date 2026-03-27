#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_471 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_471, SetNonContent_DefaultValue_471) {

    // Initially m_hasNonContent should be false by default.

    EXPECT_FALSE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_471, SetNonContent_ModifiesValue_471) {

    emitter_state.SetNonContent();

    EXPECT_TRUE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_471, SetNonContent_Idempotent_471) {

    emitter_state.SetNonContent();

    bool firstCall = emitter_state.HasBegunContent();

    emitter_state.SetNonContent();

    bool secondCall = emitter_state.HasBegunContent();

    EXPECT_EQ(firstCall, secondCall);

}



TEST_F(EmitterStateTest_471, SetNonContent_NoError_471) {

    emitter_state.SetNonContent();

    EXPECT_TRUE(emitter_state.good());

    EXPECT_EQ("", emitter_state.GetLastError());

}
