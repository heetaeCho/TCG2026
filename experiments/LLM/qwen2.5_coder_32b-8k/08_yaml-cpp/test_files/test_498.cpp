#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_498 : public ::testing::Test {

protected:

    EmitterState emitter_state_;

};



TEST_F(EmitterStateTest_498, SetPostCommentIndent_NormalOperation_498) {

    EXPECT_TRUE(emitter_state_.SetPostCommentIndent(2, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_498, SetPostCommentIndent_BoundaryCondition_ZeroValue_498) {

    EXPECT_FALSE(emitter_state_.SetPostCommentIndent(0, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_498, SetPostCommentIndent_VerifySettingChange_498) {

    emitter_state_.SetPostCommentIndent(2, FmtScope::GLOBAL);

    EXPECT_EQ(emitter_state_.GetPostCommentIndent(), 2);

}
