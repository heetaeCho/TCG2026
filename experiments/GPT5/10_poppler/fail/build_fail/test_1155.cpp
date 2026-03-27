#include <gtest/gtest.h>
#include <memory>
#include "GfxFont.h"

// Mocking external dependencies if needed
// Example: Google Mock could be used here if any dependencies need to be mocked

class GfxFontTest_1155 : public ::testing::Test {
protected:
    // You can add setup/teardown logic here if needed

    std::unique_ptr<GfxFont> font;
    
    // Set up the test environment, creating a font object for testing
    void SetUp() override {
        font = std::make_unique<GfxFont>("font_tag", Ref(0), std::optional<std::string>("Helvetica"), GfxFontType::Type1, Ref(1));
    }

    // Clean up after tests
    void TearDown() override {
        font.reset();
    }
};

// Test for normal operation: Checking if `isBold` method works correctly
TEST_F(GfxFontTest_1155, isBold_True_1155) {
    // Setting up a font with bold flag
    font->setFlags(font->getFlags() | fontBold); // Assuming setter or flag manipulation is available for the test
    
    EXPECT_TRUE(font->isBold());
}

TEST_F(GfxFontTest_1155, isBold_False_1155) {
    // Setting up a font without bold flag
    font->setFlags(font->getFlags() & ~fontBold); // Assuming setter or flag manipulation is available for the test
    
    EXPECT_FALSE(font->isBold());
}

// Test for boundary conditions: Checking if `getFontMatrix` and `getFontBBox` return valid results
TEST_F(GfxFontTest_1155, getFontMatrix_Valid_1155) {
    const auto& matrix = font->getFontMatrix();
    
    EXPECT_EQ(matrix.size(), 6); // The matrix should have 6 elements
    EXPECT_DOUBLE_EQ(matrix[0], 1.0); // Checking a specific value, for example
}

TEST_F(GfxFontTest_1155, getFontBBox_Valid_1155) {
    const auto& bbox = font->getFontBBox();
    
    EXPECT_EQ(bbox.size(), 4); // The BBox should have 4 elements
    EXPECT_DOUBLE_EQ(bbox[1], 0.0); // Checking a specific value, for example
}

// Exceptional or error case: Checking if `getTag` returns a valid tag
TEST_F(GfxFontTest_1155, getTag_ValidTag_1155) {
    const std::string& tag = font->getTag();
    
    EXPECT_FALSE(tag.empty()); // Ensure the tag is not empty
    EXPECT_EQ(tag, "font_tag"); // Assuming the tag provided is "font_tag"
}

// Test for external interaction: Verifying `isBold` flag modification (interaction with font flags)
TEST_F(GfxFontTest_1155, setBoldFlag_ModifiesFlags_1155) {
    int initialFlags = font->getFlags();
    
    // Simulate changing bold flag
    font->setFlags(initialFlags | fontBold);
    EXPECT_TRUE(font->isBold());
    
    // Resetting bold flag
    font->setFlags(initialFlags & ~fontBold);
    EXPECT_FALSE(font->isBold());
}

// Test for boundary conditions: Checking `getAscent` and `getDescent` return values
TEST_F(GfxFontTest_1155, getAscent_Valid_1155) {
    double ascent = font->getAscent();
    
    EXPECT_GE(ascent, 0.0); // Ascent should be non-negative
}

TEST_F(GfxFontTest_1155, getDescent_Valid_1155) {
    double descent = font->getDescent();
    
    EXPECT_LE(descent, 0.0); // Descent should be non-positive
}

// Test exceptional case: Checking `getFamily` for null family
TEST_F(GfxFontTest_1155, getFamily_NullFamily_1155) {
    font->setFamily(nullptr); // Assuming setFamily is available for test
    
    EXPECT_EQ(font->getFamily(), nullptr); // Should return null if no family is set
}

// Test: Check if the font is considered valid (e.g., if it's ok)
TEST_F(GfxFontTest_1155, isOk_True_1155) {
    EXPECT_TRUE(font->isOk()); // Assuming the font should be considered valid by default
}

TEST_F(GfxFontTest_1155, isOk_False_1155) {
    // Simulating an invalid font (example, actual invalidation logic depends on implementation)
    font->invalidateEmbeddedFont(); // Assuming a method to invalidate the font
    
    EXPECT_FALSE(font->isOk()); // It should now return false
}