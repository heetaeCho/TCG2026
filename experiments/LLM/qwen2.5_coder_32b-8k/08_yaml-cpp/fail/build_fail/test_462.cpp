#include <gtest/gtest.h>

#include "emitterstate.h"



class EmitterStateTest_462 : public ::testing::Test {

protected:

    YAML::EmitterState emitterState;

};



TEST_F(EmitterStateTest_462, GetPostCommentIndent_DefaultValue_462) {

    EXPECT_EQ(emitterState.GetPostCommentIndent(), 0);

}



TEST_F(EmitterStateTest_462, SetPostCommentIndent_ValidValue_462) {

    emitterState.SetPostCommentIndent(5);

    EXPECT_EQ(emitterState.GetPostCommentIndent(), 5);

}



TEST_F(EmitterStateTest_462, SetPostCommentIndent_ZeroValue_462) {

    emitterState.SetPostCommentIndent(0);

    EXPECT_EQ(emitterState.GetPostCommentIndent(), 0);

}



TEST_F(EmitterStateTest_462, SetPostCommentIndent_LargeValue_462) {

    emitterState.SetPostCommentIndent(1000);

    EXPECT_EQ(emitterState.GetPostCommentIndent(), 1000);

}
