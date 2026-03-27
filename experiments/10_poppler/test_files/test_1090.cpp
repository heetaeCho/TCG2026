#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



using namespace testing;



class MockGfxFunctionShading : public GfxFunctionShading {

public:

    MOCK_METHOD(int, getNumInputs, (), (const override));

    MOCK_METHOD(int, getNumOutputs, (), (const override));

};



class SplashFunctionPatternTest_1090 : public ::testing::Test {

protected:

    std::unique_ptr<GfxState> state;

    std::unique_ptr<MockGfxFunctionShading> shading;

    std::unique_ptr<SplashFunctionPattern> pattern;



    void SetUp() override {

        state = std::make_unique<GfxState>();

        shading = std::make_unique<MockGfxFunctionShading>();

        pattern = std::make_unique<SplashFunctionPattern>(splashModeRGB8, state.get(), shading.get());

    }

};



TEST_F(SplashFunctionPatternTest_1090, GetShadingReturnsCorrectShading_1090) {

    EXPECT_EQ(pattern->getShading(), shading.get());

}



TEST_F(SplashFunctionPatternTest_1090, IsStaticReturnsFalse_1090) {

    EXPECT_FALSE(pattern->isStatic());

}



TEST_F(SplashFunctionPatternTest_1090, CopyCreatesNewInstance_1090) {

    auto copiedPattern = pattern->copy();

    EXPECT_NE(copiedPattern, nullptr);

    EXPECT_EQ(dynamic_cast<SplashFunctionPattern*>(copiedPattern)->getShading(), shading.get());

}



TEST_F(SplashFunctionPatternTest_1090, TestPositionAlwaysReturnsTrue_1090) {

    EXPECT_TRUE(pattern->testPosition(0, 0));

}



TEST_F(SplashFunctionPatternTest_1090, IsCMYKBasedOnShadingType_1090) {

    EXPECT_CALL(*shading, getNumOutputs()).WillOnce(Return(4)); // Assuming CMYK has 4 outputs

    EXPECT_TRUE(pattern->isCMYK());



    EXPECT_CALL(*shading, getNumOutputs()).WillOnce(Return(3)); // Non-CMYK case

    EXPECT_FALSE(pattern->isCMYK());

}
