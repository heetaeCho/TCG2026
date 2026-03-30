#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* gfxState;



    void SetUp() override {

        gfxState = new GfxState(300, 300, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_589, GetBlendMode_DefaultValue_589) {

    EXPECT_EQ(gfxState->getBlendMode(), GfxBlendMode::Normal);

}



TEST_F(GfxStateTest_589, SetBlendMode_ChangesBlendMode_589) {

    gfxState->setBlendMode(GfxBlendMode::Multiply);

    EXPECT_EQ(gfxState->getBlendMode(), GfxBlendMode::Multiply);

}



TEST_F(GfxStateTest_589, GetHDPI_ReturnsCorrectValue_589) {

    EXPECT_DOUBLE_EQ(gfxState->getHDPI(), 300.0);

}



TEST_F(GfxStateTest_589, GetVDPI_ReturnsCorrectValue_589) {

    EXPECT_DOUBLE_EQ(gfxState->getVDPI(), 300.0);

}



TEST_F(GfxStateTest_589, GetCTM_ReturnsDefaultMatrix_589) {

    std::array<double, 6> expected = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(gfxState->getCTM(), expected);

}



TEST_F(GfxStateTest_589, SetCTM_ChangesMatrix_589) {

    gfxState->setCTM(2.0, 0.0, 0.0, 3.0, 4.0, 5.0);

    std::array<double, 6> expected = {2.0, 0.0, 0.0, 3.0, 4.0, 5.0};

    EXPECT_EQ(gfxState->getCTM(), expected);

}



TEST_F(GfxStateTest_589, ConcatCTM_MultipliesMatrices_589) {

    gfxState->setCTM(2.0, 0.0, 0.0, 3.0, 4.0, 5.0);

    gfxState->concatCTM(1.0, 0.0, 0.0, 2.0, 1.0, 1.0);

    std::array<double, 6> expected = {2.0, 0.0, 0.0, 6.0, 5.0, 11.0};

    EXPECT_EQ(gfxState->getCTM(), expected);

}



TEST_F(GfxStateTest_589, Save_RestoresState_589) {

    gfxState->setBlendMode(GfxBlendMode::Multiply);

    GfxState* savedState = gfxState->save();

    gfxState->setBlendMode(GfxBlendMode::Screen);

    EXPECT_EQ(gfxState->getBlendMode(), GfxBlendMode::Screen);



    gfxState->restore();

    EXPECT_EQ(gfxState->getBlendMode(), GfxBlendMode::Multiply);

    delete savedState;

}



TEST_F(GfxStateTest_589, Save_RestoresMultipleStates_589) {

    gfxState->setBlendMode(GfxBlendMode::Multiply);

    GfxState* savedState1 = gfxState->save();

    gfxState->setBlendMode(GfxBlendMode::Screen);

    GfxState* savedState2 = gfxState->save();

    gfxState->setBlendMode(GfxBlendMode::Overlay);



    EXPECT_EQ(gfxState->getBlendMode(), GfxBlendMode::Overlay);

    gfxState->restore();

    EXPECT_EQ(gfxState->getBlendMode(), GfxBlendMode::Screen);

    gfxState->restore();

    EXPECT_EQ(gfxState->getBlendMode(), GfxBlendMode::Multiply);



    delete savedState1;

    delete savedState2;

}



TEST_F(GfxStateTest_589, SetFont_SetsFontAndSize_589) {

    auto font = std::make_shared<GfxFont>();

    gfxState->setFont(font, 12.0);

    EXPECT_EQ(gfxState->getFont(), font);

    EXPECT_DOUBLE_EQ(gfxState->getFontSize(), 12.0);

}



TEST_F(GfxStateTest_589, SetLineColor_SetsColor_589) {

    GfxRGB color = {0.5, 0.5, 0.5};

    gfxState->setStrokeColor(&color);

    EXPECT_EQ(*gfxState->getStrokeColor(), color);

}



TEST_F(GfxStateTest_589, SetFillColor_SetsColor_589) {

    GfxRGB color = {1.0, 0.0, 0.0};

    gfxState->setFillColor(&color);

    EXPECT_EQ(*gfxState->getFillColor(), color);

}



TEST_F(GfxStateTest_589, SetLineWidth_SetsLineWidth_589) {

    gfxState->setLineWidth(2.5);

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 2.5);

}



TEST_F(GfxStateTest_589, SetLineDash_SetsDashPattern_589) {

    std::vector<double> dash = {4.0, 2.0};

    gfxState->setLineDash(std::move(dash), 0.0);

    double start;

    EXPECT_EQ(gfxState->getLineDash(&start), std::vector<double>({4.0, 2.0}));

    EXPECT_DOUBLE_EQ(start, 0.0);

}
