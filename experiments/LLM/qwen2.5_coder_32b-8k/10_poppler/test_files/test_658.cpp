#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_658 : public ::testing::Test {

protected:

    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        gfxState = std::make_unique<GfxState>(72.0, 72.0, nullptr, 0, false);

    }

};



TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_ReturnsNewInstance_658) {

    auto copiedCS = gfxState->copyDefaultGrayColorSpace();

    EXPECT_NE(copiedCS.get(), nullptr);

}



TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_ReturnsDifferentInstances_658) {

    auto copiedCS1 = gfxState->copyDefaultGrayColorSpace();

    auto copiedCS2 = gfxState->copyDefaultGrayColorSpace();

    EXPECT_NE(copiedCS1.get(), copiedCS2.get());

}



TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_DoesNotModifyOriginal_658) {

    auto originalCS = gfxState->getDefaultGrayColorSpace().get();

    auto copiedCS = gfxState->copyDefaultGrayColorSpace();

    EXPECT_NE(copiedCS.get(), originalCS);

}



TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_DefaultToGfxDeviceGrayColorSpace_658) {

    auto copiedCS = gfxState->copyDefaultGrayColorSpace();

    EXPECT_EQ(typeid(*copiedCS), typeid(GfxDeviceGrayColorSpace));

}
