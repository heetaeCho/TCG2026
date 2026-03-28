#include <gtest/gtest.h>

#include "emitterstate.h"



class EmitterStateTest_470 : public ::testing::Test {

protected:

    YAML::EmitterState emitterState;

};



TEST_F(EmitterStateTest_470, SetTagSetsHasTagToTrue_470) {

    EXPECT_FALSE(emitterState.HasTag());

    emitterState.SetTag();

    EXPECT_TRUE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, HasTagReturnsFalseInitially_470) {

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, SetAnchorDoesNotAffectHasTag_470) {

    emitterState.SetAnchor();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, SetAliasDoesNotAffectHasTag_470) {

    emitterState.SetAlias();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, SetNonContentDoesNotAffectHasTag_470) {

    emitterState.SetNonContent();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, SetLongKeyDoesNotAffectHasTag_470) {

    emitterState.SetLongKey();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, ForceFlowDoesNotAffectHasTag_470) {

    emitterState.ForceFlow();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, StartedDocDoesNotAffectHasTag_470) {

    emitterState.StartedDoc();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, EndedDocDoesNotAffectHasTag_470) {

    emitterState.EndedDoc();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, StartedScalarDoesNotAffectHasTag_470) {

    emitterState.StartedScalar();

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, StartedGroupDoesNotAffectHasTag_470) {

    emitterState.StartedGroup(YAML::GroupType::value::BLOCK_SEQUENCE);

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, EndedGroupDoesNotAffectHasTag_470) {

    emitterState.EndedGroup(YAML::GroupType::value::BLOCK_SEQUENCE);

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, ClearModifiedSettingsDoesNotAffectHasTag_470) {

    emitterState.SetTag();

    emitterState.ClearModifiedSettings();

    EXPECT_TRUE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_470, RestoreGlobalModifiedSettingsDoesNotAffectHasTag_470) {

    emitterState.SetTag();

    emitterState.RestoreGlobalModifiedSettings();

    EXPECT_TRUE(emitterState.HasTag());

}
