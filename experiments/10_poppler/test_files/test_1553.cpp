#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashClip.h"



class SplashClipTest : public ::testing::Test {

protected:

    SplashClip* clip;



    void SetUp() override {

        // Initialize with a default rectangle and antialiasing disabled

        clip = new SplashClip(0, 0, 100, 100, false);

    }



    void TearDown() override {

        delete clip;

    }

};



TEST_F(SplashClipTest_1553, ConstructorInitializesCoordinates_1553) {

    EXPECT_EQ(clip->getXMin(), 0.0f);

    EXPECT_EQ(clip->getYMin(), 0.0f);

    EXPECT_EQ(clip->getXMax(), 100.0f);

    EXPECT_EQ(clip->getYMax(), 100.0f);

}



TEST_F(SplashClipTest_1553, ConstructorInitializesIntegerCoordinates_1553) {

    EXPECT_EQ(clip->getXMinI(), 0);

    EXPECT_EQ(clip->getYMinI(), 0);

    EXPECT_EQ(clip->getXMaxI(), 100);

    EXPECT_EQ(clip->getYMaxI(), 100);

}



TEST_F(SplashClipTest_1553, ResetToRectUpdatesCoordinates_1553) {

    clip->resetToRect(10, 20, 90, 80);

    EXPECT_EQ(clip->getXMin(), 10.0f);

    EXPECT_EQ(clip->getYMin(), 20.0f);

    EXPECT_EQ(clip->getXMax(), 90.0f);

    EXPECT_EQ(clip->getYMax(), 80.0f);

}



TEST_F(SplashClipTest_1553, ResetToRectUpdatesIntegerCoordinates_1553) {

    clip->resetToRect(10, 20, 90, 80);

    EXPECT_EQ(clip->getXMinI(), 10);

    EXPECT_EQ(clip->getYMinI(), 20);

    EXPECT_EQ(clip->getXMaxI(), 90);

    EXPECT_EQ(clip->getYMaxI(), 80);

}



TEST_F(SplashClipTest_1553, ClipToRectWithNoOverlapReturnsError_1553) {

    EXPECT_EQ(clip->clipToRect(-10, -10, -5, -5), splashErrInvalidArgument);

}



TEST_F(SplashClipTest_1553, ClipToRectUpdatesCoordinates_1553) {

    EXPECT_EQ(clip->clipToRect(20, 30, 80, 70), splashOk);

    EXPECT_EQ(clip->getXMin(), 20.0f);

    EXPECT_EQ(clip->getYMin(), 30.0f);

    EXPECT_EQ(clip->getXMax(), 80.0f);

    EXPECT_EQ(clip->getYMax(), 70.0f);

}



TEST_F(SplashClipTest_1553, ClipToRectUpdatesIntegerCoordinates_1553) {

    EXPECT_EQ(clip->clipToRect(20, 30, 80, 70), splashOk);

    EXPECT_EQ(clip->getXMinI(), 20);

    EXPECT_EQ(clip->getYMinI(), 30);

    EXPECT_EQ(clip->getXMaxI(), 80);

    EXPECT_EQ(clip->getYMaxI(), 70);

}



TEST_F(SplashClipTest_1553, TestRectWithinBoundsReturnsTrue_1553) {

    EXPECT_TRUE(clip->testRect(10, 10, 90, 90));

}



TEST_F(SplashClipTest_1553, TestRectOutsideBoundsReturnsFalse_1553) {

    EXPECT_FALSE(clip->testRect(-10, -10, -5, -5));

}



TEST_F(SplashClipTest_1553, TestSpanWithinBoundsReturnsTrue_1553) {

    EXPECT_TRUE(clip->testSpan(10, 90, 50));

}



TEST_F(SplashClipTest_1553, TestSpanOutsideBoundsReturnsFalse_1553) {

    EXPECT_FALSE(clip->testSpan(-10, -5, -20));

}



TEST_F(SplashClipTest_1553, CopyCreatesIdenticalClip_1553) {

    std::unique_ptr<SplashClip> copiedClip = clip->copy();

    EXPECT_EQ(copiedClip->getXMin(), 0.0f);

    EXPECT_EQ(copiedClip->getYMin(), 0.0f);

    EXPECT_EQ(copiedClip->getXMax(), 100.0f);

    EXPECT_EQ(copiedClip->getYMax(), 100.0f);

}



TEST_F(SplashClipTest_1553, TestPointWithinBoundsReturnsTrue_1553) {

    EXPECT_TRUE(clip->test(50, 50));

}



TEST_F(SplashClipTest_1553, TestPointOutsideBoundsReturnsFalse_1553) {

    EXPECT_FALSE(clip->test(-10, -10));

}
