#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "GfxColorSpace.h"



using namespace testing;



class GfxStateTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxState> gfxState;

    std::unique_ptr<GfxColorSpace> mockDefaultRGBColorSpace;



    void SetUp() override {

        gfxState = std::make_unique<GfxState>(100.0, 100.0, nullptr, 0, false);

        mockDefaultRGBColorSpace = std::make_unique<GfxDeviceRGBColorSpace>();

        gfxState->setDefaultRGBColorSpace(std::move(mockDefaultRGBColorSpace));

    }

};



TEST_F(GfxStateTest_659, CopyDefaultRGBColorSpace_ReturnsNewInstance_659) {

    auto copiedColorSpace = gfxState->copyDefaultRGBColorSpace();

    EXPECT_NE(copiedColorSpace.get(), nullptr);

}



TEST_F(GfxStateTest_659, CopyDefaultRGBColorSpace_DifferentInstances_659) {

    auto firstCopy = gfxState->copyDefaultRGBColorSpace();

    auto secondCopy = gfxState->copyDefaultRGBColorSpace();

    EXPECT_NE(firstCopy.get(), secondCopy.get());

}



TEST_F(GfxStateTest_659, CopyDefaultRGBColorSpace_DefaultBehaviorWhenNull_659) {

    gfxState->setDefaultRGBColorSpace(nullptr);

    auto copiedColorSpace = gfxState->copyDefaultRGBColorSpace();

    EXPECT_NE(copiedColorSpace.get(), nullptr);

}
