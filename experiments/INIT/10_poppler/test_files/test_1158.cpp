#include <gtest/gtest.h>
#include <memory>
#include <string>

// Assuming the necessary headers are included
#include "./TestProjects/poppler/poppler/GfxFont.h"

// Test class for GfxFont
class GfxFontTest_1158 : public ::testing::Test {
protected:
    std::unique_ptr<GfxFont> font;

    void SetUp() override {
        // Setup logic here if necessary, e.g., initializing GfxFont
        font = std::make_unique<GfxFont>("tagA", 1, "Arial", GfxFontType::Type1, 1);
    }

    void TearDown() override {
        // Any necessary cleanup logic here
    }
};

// Normal operation test for getAscent method
TEST_F(GfxFontTest_1158, GetAscent_1158) {
    // Test the getAscent method
    EXPECT_EQ(font->getAscent(), font->ascent);
}

// Boundary conditions for getAscent method when font is uninitialized
TEST_F(GfxFontTest_1158, GetAscent_Uninitialized_1158) {
    // Create an uninitialized font
    std::unique_ptr<GfxFont> uninitializedFont;
    EXPECT_EQ(uninitializedFont->getAscent(), 0);  // Assuming 0 as default for boundary condition
}

// Exceptional cases: Verify the behavior of a missing font type
TEST_F(GfxFontTest_1158, GetAscent_MissingFontType_1158) {
    // Assuming the font type is required for valid ascent, and checking for missing font type behavior
    std::unique_ptr<GfxFont> missingFontType = std::make_unique<GfxFont>("tagA", 1, "", GfxFontType::Unknown, 1);
    EXPECT_EQ(missingFontType->getAscent(), 0);  // Assuming a default value
}

// Mock test case for external interaction with locateFont method
TEST_F(GfxFontTest_1158, LocateFont_ExternalInteraction_1158) {
    // Assuming we mock XRef and PSOutputDev for external interaction tests
    XRef mockXRef;
    PSOutputDev mockPsDev;
    GooString mockSubstituteFontName;

    EXPECT_CALL(mockPsDev, someExpectedFunction()).Times(1);  // Example mock for interaction
    auto result = font->locateFont(&mockXRef, &mockPsDev, &mockSubstituteFontName);
    EXPECT_TRUE(result.has_value());
}

// Test case for font attributes such as weight, stretch
TEST_F(GfxFontTest_1158, FontAttributes_1158) {
    EXPECT_EQ(font->getWeight(), Weight::Regular);
    EXPECT_EQ(font->getStretch(), Stretch::Normal);
}

// Test for font bounding box (fontBBox)
TEST_F(GfxFontTest_1158, FontBBox_1158) {
    const auto& bbox = font->getFontBBox();
    EXPECT_EQ(bbox.size(), 4);  // Assuming the fontBBox array has 4 elements
    EXPECT_EQ(bbox[0], 0);  // Boundary condition check
}