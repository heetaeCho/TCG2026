#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashClip.h"

#include "TestProjects/poppler/splash/SplashError.h"

#include "TestProjects/poppler/splash/SplashBitmap.h"

#include "TestProjects/poppler/splash/SplashPath.h"



class SplashClipTest_1546 : public ::testing::Test {

protected:

    void SetUp() override {

        clip = std::make_unique<SplashClip>(0.0, 0.0, 10.0, 10.0, false);

    }



    void TearDown() override {

        clip.reset();

    }



    std::unique_ptr<SplashClip> clip;

};



TEST_F(SplashClipTest_1546, GetXMin_ReturnsCorrectValue_1546) {

    EXPECT_EQ(clip->getXMin(), 0.0);

}



TEST_F(SplashClipTest_1546, GetXMax_ReturnsCorrectValue_1546) {

    EXPECT_EQ(clip->getXMax(), 10.0);

}



TEST_F(SplashClipTest_1546, GetYMin_ReturnsCorrectValue_1546) {

    EXPECT_EQ(clip->getYMin(), 0.0);

}



TEST_F(SplashClipTest_1546, GetYMax_ReturnsCorrectValue_1546) {

    EXPECT_EQ(clip->getYMax(), 10.0);

}



TEST_F(SplashClipTest_1546, GetXMinI_ReturnsIntegerPartOfXMin_1546) {

    EXPECT_EQ(clip->getXMinI(), static_cast<int>(clip->getXMin()));

}



TEST_F(SplashClipTest_1546, GetXMaxI_ReturnsIntegerPartOfXMax_1546) {

    EXPECT_EQ(clip->getXMaxI(), static_cast<int>(clip->getXMax()));

}



TEST_F(SplashClipTest_1546, GetYMinI_ReturnsIntegerPartOfYMin_1546) {

    EXPECT_EQ(clip->getYMinI(), static_cast<int>(clip->getYMin()));

}



TEST_F(SplashClipTest_1546, GetYMaxI_ReturnsIntegerPartOfYMax_1546) {

    EXPECT_EQ(clip->getYMaxI(), static_cast<int>(clip->getYMax()));

}



TEST_F(SplashClipTest_1546, ResetToRect_ChangesDimensionsCorrectly_1546) {

    clip->resetToRect(1.0, 2.0, 9.0, 8.0);

    EXPECT_EQ(clip->getXMin(), 1.0);

    EXPECT_EQ(clip->getYMin(), 2.0);

    EXPECT_EQ(clip->getXMax(), 9.0);

    EXPECT_EQ(clip->getYMax(), 8.0);

}



TEST_F(SplashClipTest_1546, ClipToRect_ReturnsNoErrorOnValidInput_1546) {

    EXPECT_EQ(clip->clipToRect(1.0, 2.0, 9.0, 8.0), splashOk);

}



TEST_F(SplashClipTest_1546, TestRect_ReturnsResultForContainedRectangle_1546) {

    EXPECT_EQ(clip->testRect(1, 2, 3, 4), splashClipAllInside);

}



TEST_F(SplashClipTest_1546, TestSpan_ReturnsResultForContainedSpan_1546) {

    EXPECT_EQ(clip->testSpan(1, 3, 2), splashClipAllInside);

}



TEST_F(SplashClipTest_1546, Copy_CreatesIdenticalInstance_1546) {

    auto copiedClip = clip->copy();

    EXPECT_EQ(copiedClip->getXMin(), clip->getXMin());

    EXPECT_EQ(copiedClip->getYMin(), clip->getYMin());

    EXPECT_EQ(copiedClip->getXMax(), clip->getXMax());

    EXPECT_EQ(copiedClip->getYMax(), clip->getYMax());

}



TEST_F(SplashClipTest_1546, Test_OutsidePoint_ReturnsFalse_1546) {

    EXPECT_FALSE(clip->test(-1, -1));

}



TEST_F(SplashClipTest_1546, Test_BoundaryPoint_ReturnsTrue_1546) {

    EXPECT_TRUE(clip->test(0, 0));

}



TEST_F(SplashClipTest_1546, GetNumPaths_ReturnsZeroForDefaultClip_1546) {

    EXPECT_EQ(clip->getNumPaths(), 0);

}
