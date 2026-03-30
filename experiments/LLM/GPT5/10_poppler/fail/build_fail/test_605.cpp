#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/GfxState.h"

class GfxStateTest : public testing::Test {
protected:
    // You can set up necessary state here
    GfxStateTest() {
        // Setup if needed
    }

    ~GfxStateTest() override {
        // Cleanup if needed
    }
};

TEST_F(GfxStateTest, GetFontReturnsFont_605) {
    // Test for normal operation of getFont()
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    auto font = gfxState.getFont();
    EXPECT_NE(font, nullptr);  // Assuming font is initialized in constructor or elsewhere
}

TEST_F(GfxStateTest, GetFontReturnsCorrectFont_605) {
    // Test that the correct font is returned
    std::shared_ptr<GfxFont> expectedFont = std::make_shared<GfxFont>();
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    gfxState.setFont(expectedFont, 12.0);
    auto font = gfxState.getFont();
    EXPECT_EQ(font, expectedFont);  // Verify the font is the one set
}

TEST_F(GfxStateTest, GetFontReturnsNullWhenNotSet_605) {
    // Test that nullptr is returned when no font is set
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    auto font = gfxState.getFont();
    EXPECT_EQ(font, nullptr);  // Ensure nullptr is returned if font is not set
}

TEST_F(GfxStateTest, SetFontChangesFont_605) {
    // Test that calling setFont modifies the font
    std::shared_ptr<GfxFont> newFont = std::make_shared<GfxFont>();
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    gfxState.setFont(newFont, 12.0);
    auto font = gfxState.getFont();
    EXPECT_EQ(font, newFont);  // Ensure the font was correctly updated
}

TEST_F(GfxStateTest, SetFontWithInvalidFontSize_605) {
    // Test that the font size doesn't set properly when invalid size is given (e.g., 0)
    std::shared_ptr<GfxFont> newFont = std::make_shared<GfxFont>();
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    gfxState.setFont(newFont, 0.0);  // Invalid font size
    auto font = gfxState.getFont();
    EXPECT_EQ(font, newFont);  // Ensure the font is still the same, even with invalid size
}

TEST_F(GfxStateTest, GetFontWithNullPointer_605) {
    // Test for handling null pointer for font
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    std::shared_ptr<GfxFont> nullFont = nullptr;
    gfxState.setFont(nullFont, 12.0);
    auto font = gfxState.getFont();
    EXPECT_EQ(font, nullFont);  // Ensure it handles null pointer
}

TEST_F(GfxStateTest, SetFontUpdatesFontSize_605) {
    // Test that font size is properly updated with setFont
    std::shared_ptr<GfxFont> newFont = std::make_shared<GfxFont>();
    double newSize = 14.0;
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    gfxState.setFont(newFont, newSize);
    EXPECT_EQ(gfxState.getFontSize(), newSize);  // Verify the font size update
}