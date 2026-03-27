#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include <memory>



using namespace testing;



class GfxStateTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> createMockGfxColorSpace() {

        return std::make_unique<GfxColorSpace>();

    }



    GfxState* state;

    void SetUp() override {

        state = new GfxState(100, 100, nullptr, 0, false);

    }

    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_655, SetDefaultGrayColorSpace_NormalOperation_655) {

    auto colorSpace = createMockGfxColorSpace();

    EXPECT_NO_THROW(state->setDefaultGrayColorSpace(std::move(colorSpace)));

}



TEST_F(GfxStateTest_655, SetDefaultGrayColorSpace_Nullptr_655) {

    std::unique_ptr<GfxColorSpace> colorSpace;

    EXPECT_NO_THROW(state->setDefaultGrayColorSpace(std::move(colorSpace)));

}
