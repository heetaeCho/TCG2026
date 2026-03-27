#include <gtest/gtest.h>

#include "emitterstate.h"



class EmitterStateTest_449 : public ::testing::Test {

protected:

    YAML::EmitterState emitterState;

};



TEST_F(EmitterStateTest_449, HasAliasInitiallyFalse_449) {

    EXPECT_FALSE(emitterState.HasAlias());

}



TEST_F(EmitterStateTest_449, SetAliasChangesHasAliasToTrue_449) {

    emitterState.SetAlias();

    EXPECT_TRUE(emitterState.HasAlias());

}



TEST_F(EmitterStateTest_449, HasAliasRemainsTrueAfterMultipleSetAliasCalls_449) {

    emitterState.SetAlias();

    emitterState.SetAlias();

    EXPECT_TRUE(emitterState.HasAlias());

}
