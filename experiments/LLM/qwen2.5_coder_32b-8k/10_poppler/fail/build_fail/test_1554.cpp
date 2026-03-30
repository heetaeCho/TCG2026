#include <gtest/gtest.h>

#include "SplashFont.h"



// Mock class for testing SplashFont interface

class MockSplashFont : public SplashFont {

public:

    MOCK_METHOD(double, getGlyphAdvance, (int c), (override));

};



// Test fixture for SplashFont tests

class SplashFontTest_1554 : public ::testing::Test {

protected:

    std::unique_ptr<SplashFont> font;



    void SetUp() override {

        font = std::make_unique<MockSplashFont>();

    }

};



TEST_F(SplashFontTest_1554, GetGlyphAdvance_NormalOperation_1554) {

    EXPECT_CALL(*static_cast<MockSplashFont*>(font.get()), getGlyphAdvance(65)).WillOnce(::testing::Return(0.8));

    double advance = font->getGlyphAdvance(65);

    EXPECT_EQ(advance, 0.8);

}



TEST_F(SplashFontTest_1554, GetGlyphAdvance_BoundaryCondition_MinValue_1554) {

    EXPECT_CALL(*static_cast<MockSplashFont*>(font.get()), getGlyphAdvance(std::numeric_limits<int>::min())).WillOnce(::testing::Return(-1));

    double advance = font->getGlyphAdvance(std::numeric_limits<int>::min());

    EXPECT_EQ(advance, -1);

}



TEST_F(SplashFontTest_1554, GetGlyphAdvance_BoundaryCondition_MaxValue_1554) {

    EXPECT_CALL(*static_cast<MockSplashFont*>(font.get()), getGlyphAdvance(std::numeric_limits<int>::max())).WillOnce(::testing::Return(-1));

    double advance = font->getGlyphAdvance(std::numeric_limits<int>::max());

    EXPECT_EQ(advance, -1);

}



TEST_F(SplashFontTest_1554, GetGlyphAdvance_ExceptionalCase_DefaultBehavior_1554) {

    int invalidChar = -1;

    double advance = font->getGlyphAdvance(invalidChar);

    EXPECT_EQ(advance, -1);

}
