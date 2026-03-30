#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest_592 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mock setup is not needed for the test

        // Since the actual constructor requires parameters, we cannot directly instantiate here.

        // We would need a factory method or mocking if available. For this example, we assume a valid instance.

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_592, GetFillOverprint_DefaultValue_592) {

    EXPECT_FALSE(state->getFillOverprint());

}



TEST_F(GfxStateTest_592, SetAndGetFillOverprint_592) {

    state->setFillOverprint(true);

    EXPECT_TRUE(state->getFillOverprint());



    state->setFillOverprint(false);

    EXPECT_FALSE(state->getFillOverprint());

}



TEST_F(GfxStateTest_592, GetStrokeOverprint_DefaultValue_592) {

    EXPECT_FALSE(state->getStrokeOverprint());

}



TEST_F(GfxStateTest_592, SetAndGetStrokeOverprint_592) {

    state->setStrokeOverprint(true);

    EXPECT_TRUE(state->getStrokeOverprint());



    state->setStrokeOverprint(false);

    EXPECT_FALSE(state->getStrokeOverprint());

}



TEST_F(GfxStateTest_592, GetBlendMode_DefaultValue_592) {

    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);

}



TEST_F(GfxStateTest_592, SetAndGetBlendMode_592) {

    state->setBlendMode(gfxBlendMultiply);

    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);



    state->setBlendMode(gfxBlendNormal);

    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);

}



TEST_F(GfxStateTest_592, GetFillOpacity_DefaultValue_592) {

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);

}



TEST_F(GfxStateTest_592, SetAndGetFillOpacity_592) {

    state->setFillOpacity(0.5);

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);



    state->setFillOpacity(1.0);

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);

}



TEST_F(GfxStateTest_592, GetStrokeOpacity_DefaultValue_592) {

    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);

}



TEST_F(GfxStateTest_592, SetAndGetStrokeOpacity_592) {

    state->setStrokeOpacity(0.75);

    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);



    state->setStrokeOpacity(1.0);

    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);

}



TEST_F(GfxStateTest_592, GetLineWidth_DefaultValue_592) {

    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);

}



TEST_F(GfxStateTest_592, SetAndGetLineWidth_592) {

    state->setLineWidth(2.0);

    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.0);



    state->setLineWidth(1.0);

    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);

}



TEST_F(GfxStateTest_592, GetFlatness_DefaultValue_592) {

    EXPECT_EQ(state->getFlatness(), 4);

}



TEST_F(GfxStateTest_592, SetAndGetFlatness_592) {

    state->setFlatness(8);

    EXPECT_EQ(state->getFlatness(), 8);



    state->setFlatness(4);

    EXPECT_EQ(state->getFlatness(), 4);

}
