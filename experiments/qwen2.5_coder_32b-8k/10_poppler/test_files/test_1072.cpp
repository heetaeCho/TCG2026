#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OutputDev.h"

#include "GfxState.h"  // Assuming GfxState and GfxRadialShading are defined in these headers

#include "GfxRadialShading.h"



class MockGfxState : public GfxState {

    // If needed, mock any methods from GfxState here.

};



class MockGfxRadialShading : public GfxRadialShading {

    // If needed, mock any methods from GfxRadialShading here.

};



class OutputDevTest_1072 : public ::testing::Test {

protected:

    OutputDev outputDev;

    std::unique_ptr<MockGfxState> state;

    std::unique_ptr<MockGfxRadialShading> shading;



    void SetUp() override {

        state = std::make_unique<MockGfxState>();

        shading = std::make_unique<MockGfxRadialShading>();

    }

};



TEST_F(OutputDevTest_1072, RadialShadedSupportExtend_ReturnsFalse_1072) {

    EXPECT_FALSE(outputDev.radialShadedSupportExtend(state.get(), shading.get()));

}
