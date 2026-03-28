#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SplashFont.h"

// Test fixture for SplashFont
class SplashFontTest_1554 : public ::testing::Test {
protected:
    SplashFont font;
};

// Test that getGlyphAdvance returns -1 for a typical character code
TEST_F(SplashFontTest_1554, GetGlyphAdvanceReturnsNegativeOneForTypicalChar_1554) {
    double result = font.getGlyphAdvance(65); // 'A'
    EXPECT_DOUBLE_EQ(-1.0, result);
}

// Test that getGlyphAdvance returns -1 for character code 0
TEST_F(SplashFontTest_1554, GetGlyphAdvanceReturnsNegativeOneForZero_1554) {
    double result = font.getGlyphAdvance(0);
    EXPECT_DOUBLE_EQ(-1.0, result);
}

// Test that getGlyphAdvance returns -1 for negative character code
TEST_F(SplashFontTest_1554, GetGlyphAdvanceReturnsNegativeOneForNegativeChar_1554) {
    double result = font.getGlyphAdvance(-1);
    EXPECT_DOUBLE_EQ(-1.0, result);
}

// Test that getGlyphAdvance returns -1 for large character code
TEST_F(SplashFontTest_1554, GetGlyphAdvanceReturnsNegativeOneForLargeChar_1554) {
    double result = font.getGlyphAdvance(100000);
    EXPECT_DOUBLE_EQ(-1.0, result);
}

// Test that getGlyphAdvance returns -1 for INT_MAX
TEST_F(SplashFontTest_1554, GetGlyphAdvanceReturnsNegativeOneForIntMax_1554) {
    double result = font.getGlyphAdvance(INT_MAX);
    EXPECT_DOUBLE_EQ(-1.0, result);
}

// Test that getGlyphAdvance returns -1 for INT_MIN
TEST_F(SplashFontTest_1554, GetGlyphAdvanceReturnsNegativeOneForIntMin_1554) {
    double result = font.getGlyphAdvance(INT_MIN);
    EXPECT_DOUBLE_EQ(-1.0, result);
}

// Test that multiple calls return consistent results
TEST_F(SplashFontTest_1554, GetGlyphAdvanceConsistentAcrossMultipleCalls_1554) {
    EXPECT_DOUBLE_EQ(font.getGlyphAdvance(42), font.getGlyphAdvance(42));
    EXPECT_DOUBLE_EQ(font.getGlyphAdvance(0), font.getGlyphAdvance(100));
}

// Test that a derived class can override getGlyphAdvance (virtual function behavior)
class MockSplashFont : public SplashFont {
public:
    MOCK_METHOD(double, getGlyphAdvance, (int c), (override));
};

TEST_F(SplashFontTest_1554, DerivedClassCanOverrideGetGlyphAdvance_1554) {
    MockSplashFont mockFont;
    EXPECT_CALL(mockFont, getGlyphAdvance(65)).WillOnce(::testing::Return(10.5));
    
    SplashFont* basePtr = &mockFont;
    double result = basePtr->getGlyphAdvance(65);
    EXPECT_DOUBLE_EQ(10.5, result);
}

// Test that base class default returns -1 through pointer
TEST_F(SplashFontTest_1554, BaseClassVirtualReturnsNegativeOneThroughPointer_1554) {
    SplashFont* basePtr = &font;
    double result = basePtr->getGlyphAdvance(32);
    EXPECT_DOUBLE_EQ(-1.0, result);
}

// Test with character code 1 (boundary near zero)
TEST_F(SplashFontTest_1554, GetGlyphAdvanceReturnsNegativeOneForOne_1554) {
    double result = font.getGlyphAdvance(1);
    EXPECT_DOUBLE_EQ(-1.0, result);
}
