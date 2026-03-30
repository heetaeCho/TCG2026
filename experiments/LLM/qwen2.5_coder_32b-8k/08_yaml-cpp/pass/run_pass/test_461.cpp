#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



using namespace YAML;



class EmitterStateTest_461 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_461, GetPreCommentIndent_DefaultValue_461) {

    EXPECT_EQ(emitter_state.GetPreCommentIndent(), 0);

}



TEST_F(EmitterStateTest_461, SetPreCommentIndent_NormalOperation_461) {

    ASSERT_TRUE(emitter_state.SetPreCommentIndent(2, FmtScope::value()));

    EXPECT_EQ(emitter_state.GetPreCommentIndent(), 2);

}



TEST_F(EmitterStateTest_461, SetPreCommentIndent_ZeroValue_461) {

    ASSERT_TRUE(emitter_state.SetPreCommentIndent(0, FmtScope::value()));

    EXPECT_EQ(emitter_state.GetPreCommentIndent(), 0);

}



TEST_F(EmitterStateTest_461, SetPreCommentIndent_LargeValue_461) {

    std::size_t large_value = std::numeric_limits<std::size_t>::max();

    ASSERT_TRUE(emitter_state.SetPreCommentIndent(large_value, FmtScope::value()));

    EXPECT_EQ(emitter_state.GetPreCommentIndent(), large_value);

}



TEST_F(EmitterStateTest_461, SetPreCommentIndent_ReturnsTrueOnSuccess_461) {

    EXPECT_TRUE(emitter_state.SetPreCommentIndent(5, FmtScope::value()));

}



TEST_F(EmitterStateTest_461, SetPreCommentIndent_Idempotent_461) {

    ASSERT_TRUE(emitter_state.SetPreCommentIndent(3, FmtScope::value()));

    ASSERT_TRUE(emitter_state.SetPreCommentIndent(3, FmtScope::value()));

    EXPECT_EQ(emitter_state.GetPreCommentIndent(), 3);

}
