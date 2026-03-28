#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *state;



    void SetUp() override {

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_666, HasSavesInitiallyFalse_666) {

    EXPECT_FALSE(state->hasSaves());

}



TEST_F(GfxStateTest_666, SaveIncreasesHasSaves_666) {

    state->save();

    EXPECT_TRUE(state->hasSaves());

}



TEST_F(GfxStateTest_666, RestoreDecreasesHasSaves_666) {

    state->save();

    state->restore();

    EXPECT_FALSE(state->hasSaves());

}



TEST_F(GfxStateTest_666, MultipleSaveIncreaseHasSaves_666) {

    state->save();

    state->save();

    EXPECT_TRUE(state->hasSaves());

}



TEST_F(GfxStateTest_666, RestoreAllSaves_666) {

    state->save();

    state->save();

    state->restore();

    state->restore();

    EXPECT_FALSE(state->hasSaves());

}



TEST_F(GfxStateTest_666, SaveRestoreBalance_666) {

    state->save();

    state->restore();

    state->save();

    state->restore();

    EXPECT_FALSE(state->hasSaves());

}
