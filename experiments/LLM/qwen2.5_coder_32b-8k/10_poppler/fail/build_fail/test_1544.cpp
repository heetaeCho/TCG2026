#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "SplashClip.h"



using ::testing::Eq;

using ::testing::Return;



class SplashClipTest_1544 : public ::testing::Test {

protected:

    SplashCoord x0 = 0.0, y0 = 0.0, x1 = 100.0, y1 = 100.0;

    bool antialias = true;

    std::unique_ptr<SplashClip> clip;



    void SetUp() override {

        clip = std::make_unique<SplashClip>(x0, y0, x1, y1, antialias);

    }

};



TEST_F(SplashClipTest_1544, ResetToRect_ChangesBounds_1544) {

    SplashCoord newX0 = 10.0, newY0 = 10.0, newX1 = 90.0, newY1 = 90.0;

    clip->resetToRect(newX0, newY0, newX1, newY1);

    EXPECT_EQ(clip->getXMin(), newX0);

    EXPECT_EQ(clip->getYMin(), newY0);

    EXPECT_EQ(clip->getXMax(), newX1);

    EXPECT_EQ(clip->getYMax(), newY1);

}



TEST_F(SplashClipTest_1544, Copy_CreatesNewInstanceWithSameBounds_1544) {

    auto newClip = clip->copy();

    EXPECT_EQ(newClip->getXMin(), clip->getXMin());

    EXPECT_EQ(newClip->getYMin(), clip->getYMin());

    EXPECT_EQ(newClip->getXMax(), clip->getXMax());

    EXPECT_EQ(newClip->getYMax(), clip->getYMax());

}



TEST_F(SplashClipTest_1544, ClipToRect_ReturnsNoErrorOnValidInput_1544) {

    SplashCoord newX0 = 20.0, newY0 = 20.0, newX1 = 80.0, newY1 = 80.0;

    EXPECT_EQ(clip->clipToRect(newX0, newY0, newX1, newY1), splashOk);

}



TEST_F(SplashClipTest_1544, ClipToRect_ReturnsErrorOnInvalidInput_1544) {

    SplashCoord newX0 = 120.0, newY0 = 120.0, newX1 = 180.0, newY1 = 180.0;

    EXPECT_EQ(clip->clipToRect(newX0, newY0, newX1, newY1), splashErr);

}



TEST_F(SplashClipTest_1544, TestRect_ReturnsInsideForValidPoint_1544) {

    int rectXMin = 20, rectYMin = 20, rectXMax = 80, rectYMax = 80;

    EXPECT_EQ(clip->testRect(rectXMin, rectYMin, rectXMax, rectYMax), splashClipAllInside);

}



TEST_F(SplashClipTest_1544, TestSpan_ReturnsInsideForValidPoint_1544) {

    int spanXMin = 20, spanXMax = 80, spanY = 50;

    EXPECT_EQ(clip->testSpan(spanXMin, spanXMax, spanY), splashClipAllInside);

}



TEST_F(SplashClipTest_1544, GetBounds_ReturnsInitialValues_1544) {

    EXPECT_EQ(clip->getXMin(), x0);

    EXPECT_EQ(clip->getYMin(), y0);

    EXPECT_EQ(clip->getXMax(), x1);

    EXPECT_EQ(clip->getYMax(), y1);

}



TEST_F(SplashClipTest_1544, GetIntegerBounds_ReturnsCorrectValues_1544) {

    int xMinI = static_cast<int>(x0), yMinI = static_cast<int>(y0),

        xMaxI = static_cast<int>(x1), yMaxI = static_cast<int>(y1);

    EXPECT_EQ(clip->getXMinI(), xMinI);

    EXPECT_EQ(clip->getYMinI(), yMinI);

    EXPECT_EQ(clip->getXMaxI(), xMaxI);

    EXPECT_EQ(clip->getYMaxI(), yMaxI);

}



TEST_F(SplashClipTest_1544, Test_ReturnsTrueForPointInsideBounds_1544) {

    int x = 50, y = 50;

    EXPECT_TRUE(clip->test(x, y));

}



TEST_F(SplashClipTest_1544, Test_ReturnsFalseForPointOutsideBounds_1544) {

    int x = 200, y = 200;

    EXPECT_FALSE(clip->test(x, y));

}
