#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashClip.h"

#include <memory>



// Mocking external collaborators if needed (None in this case)



class SplashClipTest : public ::testing::Test {

protected:

    std::unique_ptr<SplashClip> clip;



    void SetUp() override {

        // Initialize with a default rectangle and antialias set to false

        clip = std::make_unique<SplashClip>(0.0, 0.0, 100.0, 100.0, false);

    }

};



TEST_F(SplashClipTest_1551, GetXMaxI_ReturnsCorrectValue_1551) {

    EXPECT_EQ(clip->getXMaxI(), 100);

}



TEST_F(SplashClipTest_1551, ResetToRect_ChangesXMaxI_1551) {

    clip->resetToRect(0.0, 0.0, 200.0, 200.0);

    EXPECT_EQ(clip->getXMaxI(), 200);

}



TEST_F(SplashClipTest_1551, ClipToRect_Successful_ReturnsNoError_1551) {

    SplashError error = clip->clipToRect(10.0, 10.0, 90.0, 90.0);

    EXPECT_EQ(error, splashOk);

}



TEST_F(SplashClipTest_1551, ClipToRect_OutOfBounds_ReturnsError_1551) {

    SplashError error = clip->clipToRect(-10.0, -10.0, 110.0, 110.0);

    EXPECT_NE(error, splashOk); // Assuming out of bounds returns an error

}



TEST_F(SplashClipTest_1551, TestRect_Inside_ReturnsPositiveResult_1551) {

    SplashClipResult result = clip->testRect(10, 10, 90, 90);

    EXPECT_TRUE(result == splashClipAll || result == splashClipPartial);

}



TEST_F(SplashClipTest_1551, TestRect_Outside_ReturnsNegativeResult_1551) {

    SplashClipResult result = clip->testRect(-10, -10, 10, 10);

    EXPECT_EQ(result, splashClipNone);

}



TEST_F(SplashClipTest_1551, TestSpan_Inside_ReturnsPositiveResult_1551) {

    bool result = clip->testSpan(10, 90, 50);

    EXPECT_TRUE(result);

}



TEST_F(SplashClipTest_1551, TestSpan_Outside_ReturnsNegativeResult_1551) {

    bool result = clip->testSpan(-10, 10, -5);

    EXPECT_FALSE(result);

}



TEST_F(SplashClipTest_1551, Copy_ReturnsNewInstance_1551) {

    auto newClip = clip->copy();

    EXPECT_NE(newClip.get(), nullptr);

    EXPECT_EQ(newClip->getXMaxI(), 100);

}



TEST_F(SplashClipTest_1551, TestPoint_Outside_ReturnsFalse_1551) {

    bool result = clip->test(-10, -10);

    EXPECT_FALSE(result);

}



TEST_F(SplashClipTest_1551, TestPoint_Inside_ReturnsTrue_1551) {

    bool result = clip->test(50, 50);

    EXPECT_TRUE(result);

}
