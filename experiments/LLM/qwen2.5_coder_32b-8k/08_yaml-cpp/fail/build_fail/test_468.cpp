#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_468 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_468, HasAnchorInitiallyFalse_468) {

    EXPECT_FALSE(emitter_state.HasAnchor());

}



TEST_F(EmitterStateTest_468, SetAnchorChangesHasAnchorToTrue_468) {

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasAnchor());

}



TEST_F(EmitterStateTest_468, SetAnchorMultipleTimesRemainsTrue_468) {

    emitter_state.SetAnchor();

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasAnchor());

}



TEST_F(EmitterStateTest_468, GoodInitiallyTrue_468) {

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_468, GetLastErrorInitiallyEmpty_468) {

    EXPECT_EQ(emitter_state.GetLastError(), "");

}



TEST_F(EmitterStateTest_468, SetErrorChangesLastError_468) {

    const std::string error_message = "An error occurred";

    emitter_state.SetError(error_message);

    EXPECT_EQ(emitter_state.GetLastError(), error_message);

}



TEST_F(EmitterStateTest_468, SetErrorTwiceUpdatesLastError_468) {

    const std::string first_error = "First error";

    const std::string second_error = "Second error";

    emitter_state.SetError(first_error);

    emitter_state.SetError(second_error);

    EXPECT_EQ(emitter_state.GetLastError(), second_error);

}



TEST_F(EmitterStateTest_468, CurIndentInitiallyZero_468) {

    EXPECT_EQ(emitter_state.CurIndent(), 0);

}



TEST_F(EmitterStateTest_468, HasAliasInitiallyFalse_468) {

    EXPECT_FALSE(emitter_state.HasAlias());

}



TEST_F(EmitterStateTest_468, SetAliasChangesHasAliasToTrue_468) {

    emitter_state.SetAlias();

    EXPECT_TRUE(emitter_state.HasAlias());

}



TEST_F(EmitterStateTest_468, HasTagInitiallyFalse_468) {

    EXPECT_FALSE(emitter_state.HasTag());

}



TEST_F(EmitterStateTest_468, SetTagChangesHasTagToTrue_468) {

    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasTag());

}



TEST_F(EmitterStateTest_468, HasBegunNodeInitiallyFalse_468) {

    EXPECT_FALSE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_468, StartedNodeChangesHasBegunNodeToTrue_468) {

    emitter_state.StartedNode();

    EXPECT_TRUE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_468, HasBegunContentInitiallyFalse_468) {

    EXPECT_FALSE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_468, SetNonContentChangesHasBegunContentToTrue_468) {

    emitter_state.SetNonContent();

    EXPECT_TRUE(emitter_state.HasBegunContent());

}
