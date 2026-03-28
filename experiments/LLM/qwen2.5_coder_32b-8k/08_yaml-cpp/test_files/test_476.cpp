#include <gtest/gtest.h>

#include "emitterstate.h"



class EmitterStateTest : public ::testing::Test {

protected:

    YAML::EmitterState emitter_state;

};



TEST_F(EmitterStateTest_476, EndedDocResetsAnchor_476) {

    emitter_state.SetAnchor();

    EXPECT_TRUE(emitter_state.HasAnchor());

    emitter_state.EndedDoc();

    EXPECT_FALSE(emitter_state.HasAnchor());

}



TEST_F(EmitterStateTest_476, EndedDocResetsTag_476) {

    emitter_state.SetTag();

    EXPECT_TRUE(emitter_state.HasTag());

    emitter_state.EndedDoc();

    EXPECT_FALSE(emitter_state.HasTag());

}



TEST_F(EmitterStateTest_476, EndedDocResetsNonContent_476) {

    emitter_state.SetNonContent();

    EXPECT_TRUE(emitter_state.HasBegunNode());

    emitter_state.EndedDoc();

    EXPECT_FALSE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_476, EndedDocIdempotent_476) {

    emitter_state.SetAnchor();

    emitter_state.SetTag();

    emitter_state.SetNonContent();



    emitter_state.EndedDoc();

    EXPECT_FALSE(emitter_state.HasAnchor());

    EXPECT_FALSE(emitter_state.HasTag());

    EXPECT_FALSE(emitter_state.HasBegunNode());



    emitter_state.EndedDoc(); // Should have no effect

    EXPECT_FALSE(emitter_state.HasAnchor());

    EXPECT_FALSE(emitter_state.HasTag());

    EXPECT_FALSE(emitter_state.HasBegunNode());

}



TEST_F(EmitterStateTest_476, GoodInitiallyTrue_476) {

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_476, GetLastErrorInitiallyEmpty_476) {

    EXPECT_EQ(emitter_state.GetLastError(), "");

}



TEST_F(EmitterStateTest_476, SetErrorChangesGoodToFalse_476) {

    emitter_state.SetError("Test error");

    EXPECT_FALSE(emitter_state.good());

}



TEST_F(EmitterStateTest_476, GetLastErrorReturnsSetError_476) {

    const std::string test_error = "Another test error";

    emitter_state.SetError(test_error);

    EXPECT_EQ(emitter_state.GetLastError(), test_error);

}
