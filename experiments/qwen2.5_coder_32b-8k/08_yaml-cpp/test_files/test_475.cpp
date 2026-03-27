#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_475 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_475, StartedDocResetsFlags_475) {

    // Arrange

    emitter_state.SetAnchor();

    emitter_state.SetTag();

    emitter_state.SetNonContent();



    // Act

    emitter_state.StartedDoc();



    // Assert

    EXPECT_FALSE(emitter_state.HasAnchor());

    EXPECT_FALSE(emitter_state.HasTag());

    EXPECT_FALSE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_475, StartedDocInitiallyFalseFlags_475) {

    // Arrange



    // Act

    emitter_state.StartedDoc();



    // Assert

    EXPECT_FALSE(emitter_state.HasAnchor());

    EXPECT_FALSE(emitter_state.HasTag());

    EXPECT_FALSE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_475, SetAndGetFlagsConsistency_475) {

    // Arrange



    // Act & Assert for Anchor

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasAnchor());



    // Act & Assert for Tag

    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasTag());



    // Act & Assert for NonContent

    emitter_state.SetNonContent();

    EXPECT_TRUE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_475, DefaultGoodState_475) {

    // Arrange



    // Act



    // Assert

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_475, SetErrorChangesGoodState_475) {

    // Arrange



    // Act

    emitter_state.SetError("Test Error");



    // Assert

    EXPECT_FALSE(emitter_state.good());

    EXPECT_EQ(emitter_state.GetLastError(), "Test Error");

}



TEST_F(EmitterStateTest_475, ClearModifiedSettingsNoChange_475) {

    // Arrange



    // Act

    emitter_state.ClearModifiedSettings();



    // Assert - No observable behavior to assert directly, but ensure no crash or error occurs

}



TEST_F(EmitterStateTest_475, RestoreGlobalModifiedSettingsNoChange_475) {

    // Arrange



    // Act

    emitter_state.RestoreGlobalModifiedSettings();



    // Assert - No observable behavior to assert directly, but ensure no crash or error occurs

}
