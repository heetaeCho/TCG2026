#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "GfxFont.h"  // Assuming GfxFont.h is included as part of the project

// Test class for GfxFont
class GfxFontTest_1154 : public ::testing::Test {
protected:
    // You may need to mock or set up any necessary dependencies here
    std::unique_ptr<GfxFont> font;
    
    void SetUp() override {
        // Example setup, adjusting this as per the actual implementation needs
        font = std::make_unique<GfxFont>("tag", Ref{}, nullptr, GfxFontType::Type1, Ref{});
    }

    void TearDown() override {
        // Clean up, if needed
    }
};

// Test: Verifying that isItalic returns the correct result
TEST_F(GfxFontTest_1154, IsItalic_ReturnsCorrectValue_1154) {
    // Setting up the flags to test the `isItalic` function
    font->flags = fontItalic; // Assuming fontItalic is defined as part of the class
    
    EXPECT_TRUE(font->isItalic());
    
    font->flags = 0;
    EXPECT_FALSE(font->isItalic());
}

// Test: Verifying behavior when getting font family
TEST_F(GfxFontTest_1154, GetFamily_ReturnsExpectedValue_1154) {
    // Assuming the family is set in the setup
    auto family = font->getFamily();
    ASSERT_NE(family, nullptr);  // Make sure it's not null
    EXPECT_EQ(family->getCString(), "ExpectedFamilyName"); // Replace with actual expected family name
}

// Test: Boundary case for checking the descent of a font
TEST_F(GfxFontTest_1154, GetDescent_ReturnsCorrectValue_1154) {
    // Assuming descent has a valid value
    double descent = font->getDescent();
    EXPECT_GE(descent, 0);  // Descent should be a non-negative value
}

// Test: Verifying the 'isBold' function works as expected
TEST_F(GfxFontTest_1154, IsBold_ReturnsCorrectValue_1154) {
    font->flags = fontBold;  // Assuming fontBold is a predefined constant
    
    EXPECT_TRUE(font->isBold());
    
    font->flags = 0;
    EXPECT_FALSE(font->isBold());
}

// Test: Exceptional case for font initialization (e.g., null font object)
TEST_F(GfxFontTest_1154, NullFontObject_ThrowsException_1154) {
    std::unique_ptr<GfxFont> nullFont;
    
    ASSERT_THROW({
        nullFont->isItalic();  // Attempting to access a method of a null object
    }, std::exception);
}

// Test: Boundary condition for checking 'getFontMatrix'
TEST_F(GfxFontTest_1154, GetFontMatrix_ReturnsValidMatrix_1154) {
    const auto& matrix = font->getFontMatrix();
    
    ASSERT_EQ(matrix.size(), 6);  // Ensuring the font matrix has exactly 6 elements
    EXPECT_NE(matrix[0], 0);  // Example assertion, adjust to actual behavior
}

// Test: Verifying external interaction for getting the tag
TEST_F(GfxFontTest_1154, GetTag_ReturnsCorrectValue_1154) {
    const std::string& tag = font->getTag();
    
    EXPECT_EQ(tag, "ExpectedTag");  // Replace with actual expected tag
}

// Test: Boundary case for checking 'getType' method
TEST_F(GfxFontTest_1154, GetType_ReturnsValidType_1154) {
    GfxFontType type = font->getType();
    
    EXPECT_EQ(type, GfxFontType::Type1);  // Assuming Type1 is one of the defined types
}

// Test: Verifying 'isSubset' function
TEST_F(GfxFontTest_1154, IsSubset_ReturnsCorrectValue_1154) {
    // Assuming the font is subset or not based on specific logic
    EXPECT_TRUE(font->isSubset());
    
    // Adjust based on your implementation and requirements
}

// Test: Verifying external interaction with `locateFont` method
TEST_F(GfxFontTest_1154, LocateFont_ReturnsExpectedFontLoc_1154) {
    XRef* xref = nullptr;  // Example dependency, mock or set accordingly
    PSOutputDev* ps = nullptr;
    GooString* substituteFontName = nullptr;

    auto fontLoc = font->locateFont(xref, ps, substituteFontName);
    
    ASSERT_TRUE(fontLoc.has_value());
    // Add more specific assertions depending on the expected behavior
}