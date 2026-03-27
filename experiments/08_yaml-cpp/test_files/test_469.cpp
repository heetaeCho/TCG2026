#include <gtest/gtest.h>

#include "emitterstate.h"



namespace YAML {

    class EmitterStateTest : public ::testing::Test {

    protected:

        EmitterState state;

    };

}



TEST_F(EmitterStateTest_469, SetAlias_SetsHasAliasToTrue_469) {

    EXPECT_FALSE(state.HasAlias());

    state.SetAlias();

    EXPECT_TRUE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, HasAlias_ReturnsFalseInitially_469) {

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, SetAnchor_DoesNotAffectHasAlias_469) {

    state.SetAnchor();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, SetTag_DoesNotAffectHasAlias_469) {

    state.SetTag();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, SetNonContent_DoesNotAffectHasAlias_469) {

    state.SetNonContent();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, SetLongKey_DoesNotAffectHasAlias_469) {

    state.SetLongKey();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, ForceFlow_DoesNotAffectHasAlias_469) {

    state.ForceFlow();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, StartedDoc_DoesNotAffectHasAlias_469) {

    state.StartedDoc();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, EndedDoc_DoesNotAffectHasAlias_469) {

    state.EndedDoc();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, StartedScalar_DoesNotAffectHasAlias_469) {

    state.StartedScalar();

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, StartedGroup_DoesNotAffectHasAlias_469) {

    state.StartedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_FALSE(state.HasAlias());

}



TEST_F(EmitterStateTest_469, EndedGroup_DoesNotAffectHasAlias_469) {

    state.EndedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_FALSE(state.HasAlias());

}
