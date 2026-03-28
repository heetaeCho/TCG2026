#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashClip.h"



// Mocking dependencies if needed (not required for this class)

// using ::testing::Mock;



class SplashClipTest_1552 : public ::testing::Test {

protected:

    SplashClip* clip;



    void SetUp() override {

        // Initialize with some default values

        clip = new SplashClip(0.0, 0.0, 100.0, 100.0, false);

    }



    void TearDown() override {

        delete clip;

    }

};



TEST_F(SplashClipTest_1552, GetYMinI_NormalOperation_1552) {

    EXPECT_EQ(clip->getYMinI(), 0); // Assuming default yMinI is set to 0

}



TEST_F(SplashClipTest_1552, ResetToRect_YMinIUpdate_1552) {

    clip->resetToRect(10.0, 15.0, 90.0, 85.0);

    EXPECT_EQ(clip->getYMinI(), 15); // Assuming yMinI is set to the integer part of y0

}



TEST_F(SplashClipTest_1552, ClipToRect_YMinIUpdate_1552) {

    clip->clipToRect(10.0, 15.0, 90.0, 85.0);

    EXPECT_EQ(clip->getYMinI(), 15); // Assuming yMinI is set to the integer part of y0

}



TEST_F(SplashClipTest_1552, ClipToPath_YMinIUnchangedIfNoIntersection_1552) {

    SplashPath path; // Assuming an empty path does not change the clip region

    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    clip->clipToPath(path, matrix, 1.0, false);

    EXPECT_EQ(clip->getYMinI(), 0); // Assuming default yMinI remains unchanged

}



TEST_F(SplashClipTest_1552, TestRect_YMinIBoundaryCondition_1552) {

    SplashClipResult result = clip->testRect(-1, -1, 99, 99);

    EXPECT_EQ(clip->getYMinI(), 0); // Assuming yMinI remains unchanged

}



TEST_F(SplashClipTest_1552, TestSpan_YMinIBoundaryCondition_1552) {

    SplashClipResult result = clip->testSpan(-1, 99, -1);

    EXPECT_EQ(clip->getYMinI(), 0); // Assuming yMinI remains unchanged

}



TEST_F(SplashClipTest_1552, GetYMinI_AfterCopy_1552) {

    std::unique_ptr<SplashClip> clipCopy = clip->copy();

    EXPECT_EQ(clipCopy->getYMinI(), clip->getYMinI()); // Assuming copy retains yMinI

}



TEST_F(SplashClipTest_1552, GetYMinI_AfterMoveConstructor_1552) {

    SplashClip movedClip(clip);

    EXPECT_EQ(movedClip.getYMinI(), clip->getYMinI()); // Assuming move constructor retains yMinI

}
