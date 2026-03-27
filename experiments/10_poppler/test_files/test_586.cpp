#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



class GfxStateTest_586 : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_586, GetStrokeColorSpace_ReturnsNullByDefault_586) {

    EXPECT_EQ(gfxState->getStrokeColorSpace(), nullptr);

}



TEST_F(GfxStateTest_586, SetAndGetStrokeColorSpace_UpdatesCorrectly_586) {

    auto colorSpace = std::make_unique<GfxColorSpace>();

    gfxState->setStrokeColorSpace(std::move(colorSpace));

    EXPECT_NE(gfxState->getStrokeColorSpace(), nullptr);

}



TEST_F(GfxStateTest_586, SetStrokeColorSpaceTwice_SecondCallUpdatesCorrectly_586) {

    auto colorSpace1 = std::make_unique<GfxColorSpace>();

    gfxState->setStrokeColorSpace(std::move(colorSpace1));

    auto colorSpace2 = std::make_unique<GfxColorSpace>();

    gfxState->setStrokeColorSpace(std::move(colorSpace2));

    EXPECT_NE(gfxState->getStrokeColorSpace(), nullptr);

}



TEST_F(GfxStateTest_586, SetStrokeColorSpaceWithNull_DoesNotThrow_586) {

    auto colorSpace = std::make_unique<GfxColorSpace>();

    gfxState->setStrokeColorSpace(std::move(colorSpace));

    gfxState->setStrokeColorSpace(nullptr);

    EXPECT_EQ(gfxState->getStrokeColorSpace(), nullptr);

}
