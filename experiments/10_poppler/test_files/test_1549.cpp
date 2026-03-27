#include <gtest/gtest.h>

#include "SplashClip.h"

#include "SplashPath.h"

#include "SplashBitmap.h"



// Test fixture for SplashClip

class SplashClipTest_1549 : public ::testing::Test {

protected:

    SplashCoord x0 = 0.0;

    SplashCoord y0 = 0.0;

    SplashCoord x1 = 100.0;

    SplashCoord y1 = 200.0;

    bool antialiasA = false;



    std::unique_ptr<SplashClip> clip;



    void SetUp() override {

        clip = std::make_unique<SplashClip>(x0, y0, x1, y1, antialiasA);

    }

};



// Test getYMax for normal operation

TEST_F(SplashClipTest_1549, GetYMax_ReturnsCorrectValue_1549) {

    EXPECT_EQ(clip->getYMax(), y1);

}



// Test getXMin for normal operation

TEST_F(SplashClipTest_1549, GetXMin_ReturnsCorrectValue_1549) {

    EXPECT_EQ(clip->getXMin(), x0);

}



// Test getXMax for normal operation

TEST_F(SplashClipTest_1549, GetXMax_ReturnsCorrectValue_1549) {

    EXPECT_EQ(clip->getXMax(), x1);

}



// Test getYMin for normal operation

TEST_F(SplashClipTest_1549, GetYMin_ReturnsCorrectValue_1549) {

    EXPECT_EQ(clip->getYMin(), y0);

}



// Test getXMinI for boundary condition

TEST_F(SplashClipTest_1549, GetXMinI_ReturnsFloorOfXMin_1549) {

    EXPECT_EQ(clip->getXMinI(), static_cast<int>(std::floor(x0)));

}



// Test getXMaxI for boundary condition

TEST_F(SplashClipTest_1549, GetXMaxI_ReturnsCeilOfXMax_1549) {

    EXPECT_EQ(clip->getXMaxI(), static_cast<int>(std::ceil(x1)));

}



// Test getYMinI for boundary condition

TEST_F(SplashClipTest_1549, GetYMinI_ReturnsFloorOfYMin_1549) {

    EXPECT_EQ(clip->getYMinI(), static_cast<int>(std::floor(y0)));

}



// Test getYMaxI for boundary condition

TEST_F(SplashClipTest_1549, GetYMaxI_ReturnsCeilOfYMax_1549) {

    EXPECT_EQ(clip->getYMaxI(), static_cast<int>(std::ceil(y1)));

}



// Test resetToRect with normal values

TEST_F(SplashClipTest_1549, ResetToRect_SetsCorrectValues_1549) {

    SplashCoord newX0 = 10.0;

    SplashCoord newY0 = 20.0;

    SplashCoord newX1 = 30.0;

    SplashCoord newY1 = 40.0;



    clip->resetToRect(newX0, newY0, newX1, newY1);



    EXPECT_EQ(clip->getXMin(), newX0);

    EXPECT_EQ(clip->getYMin(), newY0);

    EXPECT_EQ(clip->getXMax(), newX1);

    EXPECT_EQ(clip->getYMax(), newY1);

}



// Test clipToRect with normal values

TEST_F(SplashClipTest_1549, ClipToRect_ReturnsNoError_1549) {

    SplashCoord newX0 = 10.0;

    SplashCoord newY0 = 20.0;

    SplashCoord newX1 = 30.0;

    SplashCoord newY1 = 40.0;



    EXPECT_EQ(clip->clipToRect(newX0, newY0, newX1, newY1), splashOk);

}



// Test clipToPath with a simple path

TEST_F(SplashClipTest_1549, ClipToPath_ReturnsNoError_1549) {

    SplashPath path;

    std::array<SplashCoord, 6> matrix = {1, 0, 0, 1, 0, 0};

    SplashCoord flatness = 0.25;

    bool eo = false;



    path.moveTo(10.0, 10.0);

    path.lineTo(90.0, 10.0);

    path.lineTo(50.0, 80.0);

    path.close();



    EXPECT_EQ(clip->clipToPath(path, matrix, flatness, eo), splashOk);

}



// Test testRect with a rectangle fully inside the clip

TEST_F(SplashClipTest_1549, TestRect_ReturnsFullyInside_1549) {

    int rectXMin = 10;

    int rectYMin = 20;

    int rectXMax = 30;

    int rectYMax = 40;



    EXPECT_EQ(clip->testRect(rectXMin, rectYMin, rectXMax, rectYMax), splashClipAllInside);

}



// Test testSpan with a span fully inside the clip

TEST_F(SplashClipTest_1549, TestSpan_ReturnsFullyInside_1549) {

    int spanXMin = 10;

    int spanXMax = 30;

    int spanY = 20;



    EXPECT_EQ(clip->testSpan(spanXMin, spanXMax, spanY), splashClipAllInside);

}



// Test test with a point inside the clip

TEST_F(SplashClipTest_1549, Test_ReturnsTrueForPointInside_1549) {

    int x = 50;

    int y = 100;



    EXPECT_TRUE(clip->test(x, y));

}



// Test copy creates a new object with the same values

TEST_F(SplashClipTest_1549, Copy_ReturnsNewObjectWithSameValues_1549) {

    auto copiedClip = clip->copy();



    EXPECT_EQ(copiedClip->getXMin(), clip->getXMin());

    EXPECT_EQ(copiedClip->getYMin(), clip->getYMin());

    EXPECT_EQ(copiedClip->getXMax(), clip->getXMax());

    EXPECT_EQ(copiedClip->getYMax(), clip->getYMax());

}
