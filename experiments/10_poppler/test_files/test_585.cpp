#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_585 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a GfxState object for testing

        state = std::make_unique<GfxState>(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        // Clean up after each test

        state.reset();

    }



    std::unique_ptr<GfxState> state;

};



TEST_F(GfxStateTest_585, GetFillColorSpace_ReturnsNullPointerInitially_585) {

    EXPECT_EQ(state->getFillColorSpace(), nullptr);

}



// Assuming we can set the fill color space and verify it

TEST_F(GfxStateTest_585, SetAndGetFillColorSpace_ValidColorSpace_585) {

    auto colorSpace = std::make_unique<GfxColorSpace>();

    GfxColorSpace* rawColorSpace = colorSpace.get();

    state->setFillColorSpace(std::move(colorSpace));

    EXPECT_EQ(state->getFillColorSpace(), rawColorSpace);

}



// Boundary conditions - check if setting null works

TEST_F(GfxStateTest_585, SetFillColorSpace_NullPointer_585) {

    state->setFillColorSpace(nullptr);

    EXPECT_EQ(state->getFillColorSpace(), nullptr);

}



// Assuming we can set the stroke color space and verify it

TEST_F(GfxStateTest_585, SetAndGetStrokeColorSpace_ValidColorSpace_585) {

    auto colorSpace = std::make_unique<GfxColorSpace>();

    GfxColorSpace* rawColorSpace = colorSpace.get();

    state->setStrokeColorSpace(std::move(colorSpace));

    EXPECT_EQ(state->getStrokeColorSpace(), rawColorSpace);

}



// Boundary conditions - check if setting null works

TEST_F(GfxStateTest_585, SetStrokeColorSpace_NullPointer_585) {

    state->setStrokeColorSpace(nullptr);

    EXPECT_EQ(state->getStrokeColorSpace(), nullptr);

}
