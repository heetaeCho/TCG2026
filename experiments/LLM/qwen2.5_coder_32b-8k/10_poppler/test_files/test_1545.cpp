#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashClip.h"



class SplashClipTest_1545 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a SplashClip object with known coordinates and antialiasing setting.

        clip = std::make_unique<SplashClip>(0.0, 0.0, 10.0, 10.0, true);

    }



    std::unique_ptr<SplashClip> clip;

};



TEST_F(SplashClipTest_1545, TestWithinBounds_1545) {

    EXPECT_TRUE(clip->test(5, 5));

}



TEST_F(SplashClipTest_1545, TestOnBoundary_1545) {

    EXPECT_TRUE(clip->test(0, 0));

    EXPECT_TRUE(clip->test(10, 10));

}



TEST_F(SplashClipTest_1545, TestOutsideBounds_1545) {

    EXPECT_FALSE(clip->test(-1, -1));

    EXPECT_FALSE(clip->test(11, 11));

    EXPECT_FALSE(clip->test(10, -1));

    EXPECT_FALSE(clip->test(-1, 10));

}



TEST_F(SplashClipTest_1545, TestGetXMin_1545) {

    EXPECT_EQ(0.0, clip->getXMin());

}



TEST_F(SplashClipTest_1545, TestGetXMax_1545) {

    EXPECT_EQ(10.0, clip->getXMax());

}



TEST_F(SplashClipTest_1545, TestGetYMin_1545) {

    EXPECT_EQ(0.0, clip->getYMin());

}



TEST_F(SplashClipTest_1545, TestGetYMax_1545) {

    EXPECT_EQ(10.0, clip->getYMax());

}



TEST_F(SplashClipTest_1545, TestGetXMinI_1545) {

    EXPECT_EQ(0, clip->getXMinI());

}



TEST_F(SplashClipTest_1545, TestGetXMaxI_1545) {

    EXPECT_EQ(10, clip->getXMaxI());

}



TEST_F(SplashClipTest_1545, TestGetYMinI_1545) {

    EXPECT_EQ(0, clip->getYMinI());

}



TEST_F(SplashClipTest_1545, TestGetYMaxI_1545) {

    EXPECT_EQ(10, clip->getYMaxI());

}
