#include <gtest/gtest.h>

#include "SplashClip.h"



class SplashClipTest : public ::testing::Test {

protected:

    std::unique_ptr<SplashClip> clip;



    void SetUp() override {

        // Initialize a default splash clip with some arbitrary values.

        clip = std::make_unique<SplashClip>(0.0, 0.0, 100.0, 100.0, true);

    }

};



TEST_F(SplashClipTest_1550, GetXMinI_ReturnsCorrectValue_1550) {

    // Assuming the constructor sets xMinI correctly, we test if getXMinI returns it.

    EXPECT_EQ(clip->getXMinI(), 0);

}



TEST_F(SplashClipTest_1550, ResetToRect_AffectsGetXMinI_1550) {

    clip->resetToRect(10.0, 20.0, 30.0, 40.0);

    EXPECT_EQ(clip->getXMinI(), 10);

}



TEST_F(SplashClipTest_1550, ClipToRect_OutOfBounds_ReturnsError_1550) {

    // Assuming clipToRect returns an error when the rectangle is out of bounds.

    SplashError result = clip->clipToRect(-1.0, -1.0, -2.0, -2.0);

    EXPECT_NE(result, splashOk);

}



TEST_F(SplashClipTest_1550, ClipToPath_ValidPath_ReturnsSuccess_1550) {

    // Mocking a path and matrix for testing purposes.

    SplashPath path;

    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    SplashError result = clip->clipToPath(path, matrix, 0.5, false);

    EXPECT_EQ(result, splashOk);

}



TEST_F(SplashClipTest_1550, TestRect_OutOfBounds_ReturnsOutside_1550) {

    // Assuming testRect returns outside when the rectangle is out of bounds.

    SplashClipResult result = clip->testRect(-10, -10, -5, -5);

    EXPECT_EQ(result, splashClipAllOutside);

}



TEST_F(SplashClipTest_1550, TestSpan_OutOfBounds_ReturnsOutside_1550) {

    // Assuming testSpan returns outside when the span is out of bounds.

    SplashClipResult result = clip->testSpan(-10, -5, -7);

    EXPECT_EQ(result, splashClipAllOutside);

}



TEST_F(SplashClipTest_1550, Copy_ReturnsValidObject_1550) {

    auto copiedClip = clip->copy();

    EXPECT_NE(copiedClip.get(), nullptr);

}
