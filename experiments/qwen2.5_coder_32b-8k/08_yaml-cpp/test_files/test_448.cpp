#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_448 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_448, HasAnchorInitiallyFalse_448) {

    EXPECT_FALSE(emitter_state.HasAnchor());

}



TEST_F(EmitterStateTest_448, SetAnchorChangesHasAnchorToTrue_448) {

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasAnchor());

}



TEST_F(EmitterStateTest_448, HasAliasInitiallyFalse_448) {

    EXPECT_FALSE(emitter_state.HasAlias());

}



TEST_F(EmitterStateTest_448, SetAliasChangesHasAliasToTrue_448) {

    emitter_state.SetAlias();

    EXPECT_TRUE(emitter_state.HasAlias());

}



TEST_F(EmitterStateTest_448, HasTagInitiallyFalse_448) {

    EXPECT_FALSE(emitter_state.HasTag());

}



TEST_F(EmitterStateTest_448, SetTagChangesHasTagToTrue_448) {

    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasTag());

}



TEST_F(EmitterStateTest_448, HasBegunNodeInitiallyFalse_448) {

    EXPECT_FALSE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_448, StartedScalarChangesHasBegunNodeToTrue_448) {

    emitter_state.StartedScalar();

    EXPECT_TRUE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_448, HasBegunContentInitiallyFalse_448) {

    EXPECT_FALSE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_448, SetNonContentChangesHasBegunContentToTrue_448) {

    emitter_state.SetNonContent();

    EXPECT_TRUE(emitter_state.HasBegunContent());

}



TEST_F(EmitterStateTest_448, CurIndentInitiallyZero_448) {

    EXPECT_EQ(0, emitter_state.CurIndent());

}



TEST_F(EmitterStateTest_448, SetIndentChangesCurIndent_448) {

    emitter_state.SetIndent(2, FmtScope::BLOCK);

    EXPECT_EQ(2, emitter_state.CurIndent());

}



TEST_F(EmitterStateTest_448, GoodInitiallyTrue_448) {

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_448, SetErrorChangesGoodToFalse_448) {

    emitter_state.SetError("An error occurred");

    EXPECT_FALSE(emitter_state.good());

}



TEST_F(EmitterStateTest_448, GetLastErrorInitiallyEmpty_448) {

    EXPECT_TRUE(emitter_state.GetLastError().empty());

}



TEST_F(EmitterStateTest_448, SetErrorChangesLastError_448) {

    const std::string error_message = "An error occurred";

    emitter_state.SetError(error_message);

    EXPECT_EQ(error_message, emitter_state.GetLastError());

}
