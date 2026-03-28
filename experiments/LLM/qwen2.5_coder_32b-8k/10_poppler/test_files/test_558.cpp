#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxXYZ2DisplayTransformsTest_558 : public ::testing::Test {

protected:

    std::shared_ptr<GfxLCMSProfile> dummyProfile;

    GfxXYZ2DisplayTransforms* transforms;



    void SetUp() override {

        dummyProfile = std::make_shared<GfxLCMSProfile>();

        transforms = new GfxXYZ2DisplayTransforms(dummyProfile);

    }



    void TearDown() override {

        delete transforms;

    }

};



TEST_F(GfxXYZ2DisplayTransformsTest_558, GetDisplayProfile_ReturnsCorrectProfile_558) {

    EXPECT_EQ(transforms->getDisplayProfile(), dummyProfile);

}



TEST_F(GfxXYZ2DisplayTransformsTest_558, GetRelCol_ReturnsNonNullPointer_558) {

    EXPECT_NE(transforms->getRelCol(), nullptr);

}



TEST_F(GfxXYZ2DisplayTransformsTest_558, GetAbsCol_ReturnsNonNullPointer_558) {

    EXPECT_NE(transforms->getAbsCol(), nullptr);

}



TEST_F(GfxXYZ2DisplayTransformsTest_558, GetSat_ReturnsNonNullPointer_558) {

    EXPECT_NE(transforms->getSat(), nullptr);

}



TEST_F(GfxXYZ2DisplayTransformsTest_558, GetPerc_ReturnsNonNullPointer_558) {

    EXPECT_NE(transforms->getPerc(), nullptr);

}
