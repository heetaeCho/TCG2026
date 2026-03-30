#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Initialize a default GfxState object with dummy values for the constructor parameters.

        state = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_587, GetFillPattern_ReturnsNullPtrInitially_587) {

    EXPECT_EQ(state->getFillPattern(), nullptr);

}



TEST_F(GfxStateTest_587, SetAndGetFillPattern_SetsAndReturnsCorrectPattern_587) {

    auto pattern = std::make_unique<GfxPattern>();

    GfxPattern* rawPattern = pattern.get();

    state->setFillPattern(std::move(pattern));

    EXPECT_EQ(state->getFillPattern(), rawPattern);

}



TEST_F(GfxStateTest_587, SetFillPatternTwice_SecondPatternReplacesFirst_587) {

    auto firstPattern = std::make_unique<GfxPattern>();

    state->setFillPattern(std::move(firstPattern));

    

    auto secondPattern = std::make_unique<GfxPattern>();

    GfxPattern* rawSecondPattern = secondPattern.get();

    state->setFillPattern(std::move(secondPattern));



    EXPECT_EQ(state->getFillPattern(), rawSecondPattern);

}
