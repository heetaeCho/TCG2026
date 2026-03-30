#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest_575 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColor> initialFillColor = std::make_unique<GfxColor>();

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(300, 300, nullptr, 0, false);

        gfxState->setFillColor(initialFillColor.get());

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_575, GetFillColor_ReturnsInitialColor_575) {

    const GfxColor *fillColor = gfxState->getFillColor();

    EXPECT_EQ(fillColor, initialFillColor.get());

}



TEST_F(GfxStateTest_575, SetAndGetFillColor_ChangesColorCorrectly_575) {

    std::unique_ptr<GfxColor> newColor = std::make_unique<GfxColor>();

    gfxState->setFillColor(newColor.get());



    const GfxColor *fillColor = gfxState->getFillColor();

    EXPECT_EQ(fillColor, newColor.get());

}



TEST_F(GfxStateTest_575, GetStrokeColor_ReturnsNullptrByDefault_575) {

    const GfxColor *strokeColor = gfxState->getStrokeColor();

    EXPECT_EQ(strokeColor, nullptr);

}
