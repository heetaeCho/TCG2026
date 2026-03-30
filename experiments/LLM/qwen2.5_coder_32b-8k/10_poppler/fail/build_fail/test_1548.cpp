#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashClip.h"

#include <memory>



using namespace ::testing;



class SplashClipTest : public Test {

protected:

    std::unique_ptr<SplashClip> clip;



    void SetUp() override {

        clip = std::make_unique<SplashClip>(0, 0, 100, 100, false);

    }

};



TEST_F(SplashClipTest_1548, GetYMin_ReturnsInitializedValue_1548) {

    EXPECT_EQ(clip->getYMin(), 0);

}



TEST_F(SplashClipTest_1548, ResetToRect_ChangesBounds_1548) {

    clip->resetToRect(10, 20, 30, 40);

    EXPECT_EQ(clip->getXMin(), 10);

    EXPECT_EQ(clip->getYMin(), 20);

    EXPECT_EQ(clip->getXMax(), 30);

    EXPECT_EQ(clip->getYMax(), 40);

}



TEST_F(SplashClipTest_1548, ClipToRect_OutsideBounds_ReturnsError_1548) {

    EXPECT_EQ(clip->clipToRect(-10, -20, -5, -10), splashErrRange);

}



TEST_F(SplashClipTest_1548, TestRect_FullyInside_ReturnsFullCoverage_1548) {

    EXPECT_EQ(clip->testRect(10, 10, 90, 90), splashClipAllInside);

}



TEST_F(SplashClipTest_1548, TestRect_Outside_ReturnsNoCoverage_1548) {

    EXPECT_EQ(clip->testRect(-10, -20, -5, -10), splashClipAllOutside);

}



TEST_F(SplashClipTest_1548, TestSpan_FullyInside_ReturnsTrue_1548) {

    EXPECT_TRUE(clip->testSpan(10, 90, 50));

}



TEST_F(SplashClipTest_1548, TestSpan_Outside_ReturnsFalse_1548) {

    EXPECT_FALSE(clip->testSpan(-10, -5, -20));

}



TEST_F(SplashClipTest_1548, Copy_CreatesNewInstanceWithSameBounds_1548) {

    auto newClip = clip->copy();

    EXPECT_EQ(newClip->getXMin(), 0);

    EXPECT_EQ(newClip->getYMin(), 0);

    EXPECT_EQ(newClip->getXMax(), 100);

    EXPECT_EQ(newClip->getYMax(), 100);

}



TEST_F(SplashClipTest_1548, Test_PointInside_ReturnsTrue_1548) {

    EXPECT_TRUE(clip->test(50, 50));

}



TEST_F(SplashClipTest_1548, Test_PointOutside_ReturnsFalse_1548) {

    EXPECT_FALSE(clip->test(-10, -20));

}



TEST_F(SplashClipTest_1548, GetBoundaryCoordinates_ReturnCorrectValues_1548) {

    EXPECT_EQ(clip->getXMin(), 0);

    EXPECT_EQ(clip->getYMin(), 0);

    EXPECT_EQ(clip->getXMax(), 100);

    EXPECT_EQ(clip->getYMax(), 100);



    EXPECT_EQ(clip->getXMinI(), 0);

    EXPECT_EQ(clip->getYMinI(), 0);

    EXPECT_EQ(clip->getXMaxI(), 100);

    EXPECT_EQ(clip->getYMaxI(), 100);

}



TEST_F(SplashClipTest_1548, GetNumPaths_DefaultInitialization_ReturnsZero_1548) {

    EXPECT_EQ(clip->getNumPaths(), 0);

}
