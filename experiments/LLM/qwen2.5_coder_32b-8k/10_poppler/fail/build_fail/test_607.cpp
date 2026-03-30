#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        gfxState = std::make_unique<GfxState>(72.0, 72.0, nullptr, 0, false);

    }

};



TEST_F(GfxStateTest_NormalOperation_607, GetTextMat_ReturnsValidMatrix_607) {

    const auto& textMat = gfxState->getTextMat();

    EXPECT_EQ(textMat.size(), 6);

}



TEST_F(GfxStateTest_BoundaryConditions_607, DefaultConstructedTextMat_IsIdentity_607) {

    const auto& textMat = gfxState->getTextMat();

    std::array<double, 6> identityMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(textMat, identityMatrix);

}



TEST_F(GfxStateTest_NormalOperation_607, SetTextMat_AffectsGetTextMat_607) {

    std::array<double, 6> customMatrix = {2.0, 0.5, -0.3, 1.2, 10.0, -5.0};

    gfxState->setTextMat(customMatrix[0], customMatrix[1], customMatrix[2],

                         customMatrix[3], customMatrix[4], customMatrix[5]);

    const auto& retrievedTextMat = gfxState->getTextMat();

    EXPECT_EQ(retrievedTextMat, customMatrix);

}



TEST_F(GfxStateTest_NormalOperation_607, TextTransform_AppliesTextMat_607) {

    std::array<double, 6> customMatrix = {2.0, 0.5, -0.3, 1.2, 10.0, -5.0};

    gfxState->setTextMat(customMatrix[0], customMatrix[1], customMatrix[2],

                         customMatrix[3], customMatrix[4], customMatrix[5]);

    

    double x = 1.0, y = 2.0;

    double transformedX = 0.0, transformedY = 0.0;

    gfxState->textTransform(x, y, &transformedX, &transformedY);

    

    // Calculated based on the custom matrix application: (x', y') = M * (x, y)

    double expectedX = customMatrix[0] * x + customMatrix[1] * y + customMatrix[4];

    double expectedY = customMatrix[2] * x + customMatrix[3] * y + customMatrix[5];

    

    EXPECT_DOUBLE_EQ(transformedX, expectedX);

    EXPECT_DOUBLE_EQ(transformedY, expectedY);

}



TEST_F(GfxStateTest_ExceptionalCases_607, TextTransform_DoesNotCrashWithZeroScale_607) {

    std::array<double, 6> customMatrix = {0.0, 0.0, 0.0, 0.0, 10.0, -5.0};

    gfxState->setTextMat(customMatrix[0], customMatrix[1], customMatrix[2],

                         customMatrix[3], customMatrix[4], customMatrix[5]);

    

    double x = 1.0, y = 2.0;

    double transformedX = 0.0, transformedY = 0.0;

    EXPECT_NO_THROW(gfxState->textTransform(x, y, &transformedX, &transformedY));

}



TEST_F(GfxStateTest_NormalOperation_607, SetTextMat_DoesNotAffectCTM_607) {

    std::array<double, 6> customMatrix = {2.0, 0.5, -0.3, 1.2, 10.0, -5.0};

    gfxState->setTextMat(customMatrix[0], customMatrix[1], customMatrix[2],

                         customMatrix[3], customMatrix[4], customMatrix[5]);

    

    const auto& ctm = gfxState->getCTM();

    std::array<double, 6> identityMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(ctm, identityMatrix);

}



TEST_F(GfxStateTest_NormalOperation_607, SetCTM_DoesNotAffectTextMat_607) {

    std::array<double, 6> customMatrix = {2.0, 0.5, -0.3, 1.2, 10.0, -5.0};

    gfxState->setCTM(customMatrix[0], customMatrix[1], customMatrix[2],

                     customMatrix[3], customMatrix[4], customMatrix[5]);

    

    const auto& textMat = gfxState->getTextMat();

    std::array<double, 6> identityMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(textMat, identityMatrix);

}
