#include <gtest/gtest.h>

#include "SplashClip.h"

#include <memory>



class SplashClipTest_1547 : public ::testing::Test {

protected:

    std::unique_ptr<SplashClip> clip;



    void SetUp() override {

        clip = std::make_unique<SplashClip>(0, 0, 100, 100, true);

    }

};



TEST_F(SplashClipTest_1547, GetXMax_ReturnsCorrectValue_1547) {

    EXPECT_EQ(clip->getXMax(), 100);

}



TEST_F(SplashClipTest_1547, ResetToRect_ChangesXMax_1547) {

    clip->resetToRect(10, 10, 200, 200);

    EXPECT_EQ(clip->getXMax(), 200);

}



TEST_F(SplashClipTest_1547, ClipToRect_OutOfBounds_ReturnsError_1547) {

    EXPECT_EQ(clip->clipToRect(-10, -10, -1, -1), splashErrRange);

}



TEST_F(SplashClipTest_1547, Copy_ProducesEqualXMax_1547) {

    auto copiedClip = clip->copy();

    EXPECT_EQ(copiedClip->getXMax(), clip->getXMax());

}



TEST_F(SplashClipTest_1547, GetXMin_ReturnsCorrectValue_1547) {

    EXPECT_EQ(clip->getXMin(), 0);

}



TEST_F(SplashClipTest_1547, GetYMin_ReturnsCorrectValue_1547) {

    EXPECT_EQ(clip->getYMin(), 0);

}



TEST_F(SplashClipTest_1547, GetXMaxI_ReturnsCorrectIntegerValue_1547) {

    EXPECT_EQ(clip->getXMaxI(), 100);

}



TEST_F(SplashClipTest_1547, GetYMax_ReturnsCorrectValue_1547) {

    EXPECT_EQ(clip->getYMax(), 100);

}



TEST_F(SplashClipTest_1547, GetYMaxI_ReturnsCorrectIntegerValue_1547) {

    EXPECT_EQ(clip->getYMaxI(), 100);

}



TEST_F(SplashClipTest_1547, TestRect_OutOfBounds_ReturnsFalse_1547) {

    EXPECT_FALSE(clip->testRect(-10, -10, -1, -1));

}



TEST_F(SplashClipTest_1547, TestSpan_OutOfBounds_ReturnsFalse_1547) {

    EXPECT_FALSE(clip->testSpan(-10, -1, 0));

}
