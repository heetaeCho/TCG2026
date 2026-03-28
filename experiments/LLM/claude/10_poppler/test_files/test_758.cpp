#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Annot.h"

// Test fixture for DefaultAppearance tests
class DefaultAppearanceTest_758 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with font name, size, and AnnotColor
TEST_F(DefaultAppearanceTest_758, ConstructWithFontNameSizeAndColor_758) {
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "Helvetica");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test construction with nullptr color
TEST_F(DefaultAppearanceTest_758, ConstructWithNullColor_758) {
    std::unique_ptr<AnnotColor> nullColor = nullptr;
    DefaultAppearance da("Courier", 10.0, std::move(nullColor));
    
    EXPECT_EQ(da.getFontName(), "Courier");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 10.0);
    EXPECT_EQ(da.getFontColor(), nullptr);
}

// Test getFontName returns correct name
TEST_F(DefaultAppearanceTest_758, GetFontNameReturnsCorrectValue_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Times-Roman", 14.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "Times-Roman");
}

// Test getFontPtSize returns correct size
TEST_F(DefaultAppearanceTest_758, GetFontPtSizeReturnsCorrectValue_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 24.5, std::move(color));
    
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 24.5);
}

// Test setFontName changes the font name
TEST_F(DefaultAppearanceTest_758, SetFontNameChangesName_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    da.setFontName("Courier");
    EXPECT_EQ(da.getFontName(), "Courier");
}

// Test setFontPtSize changes the font size
TEST_F(DefaultAppearanceTest_758, SetFontPtSizeChangesSize_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    da.setFontPtSize(20.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 20.0);
}

// Test setFontColor changes the color
TEST_F(DefaultAppearanceTest_758, SetFontColorChangesColor_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    auto newColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    da.setFontColor(std::move(newColor));
    
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test setFontColor with nullptr
TEST_F(DefaultAppearanceTest_758, SetFontColorToNull_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    da.setFontColor(std::unique_ptr<AnnotColor>(nullptr));
    EXPECT_EQ(da.getFontColor(), nullptr);
}

// Test toAppearanceString returns non-empty string
TEST_F(DefaultAppearanceTest_758, ToAppearanceStringReturnsNonEmpty_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    std::string result = da.toAppearanceString();
    EXPECT_FALSE(result.empty());
}

// Test boundary: zero font size
TEST_F(DefaultAppearanceTest_758, ZeroFontSize_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 0.0, std::move(color));
    
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 0.0);
}

// Test boundary: very large font size
TEST_F(DefaultAppearanceTest_758, VeryLargeFontSize_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 99999.0, std::move(color));
    
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 99999.0);
}

// Test boundary: empty font name
TEST_F(DefaultAppearanceTest_758, EmptyFontName_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("", 12.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "");
}

// Test setFontName to empty string
TEST_F(DefaultAppearanceTest_758, SetFontNameToEmpty_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    da.setFontName("");
    EXPECT_EQ(da.getFontName(), "");
}

// Test negative font size
TEST_F(DefaultAppearanceTest_758, NegativeFontSize_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", -5.0, std::move(color));
    
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), -5.0);
}

// Test multiple set operations
TEST_F(DefaultAppearanceTest_758, MultipleSetOperations_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    da.setFontName("Courier");
    da.setFontPtSize(18.0);
    auto newColor = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    da.setFontColor(std::move(newColor));
    
    EXPECT_EQ(da.getFontName(), "Courier");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 18.0);
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test with RGB color values
TEST_F(DefaultAppearanceTest_758, ConstructWithRGBColor_758) {
    auto color = std::make_unique<AnnotColor>(0.5, 0.3, 0.7);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    const AnnotColor *fc = da.getFontColor();
    EXPECT_NE(fc, nullptr);
}

// Test toAppearanceString after modifications
TEST_F(DefaultAppearanceTest_758, ToAppearanceStringAfterModification_758) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontName("Cour");
    da.setFontPtSize(16.0);
    
    std::string result = da.toAppearanceString();
    EXPECT_FALSE(result.empty());
}

// Test construction with GooString (DA string parsing)
TEST_F(DefaultAppearanceTest_758, ConstructFromDAString_758) {
    GooString daStr("0 0 0 rg /Helv 12 Tf");
    DefaultAppearance da(&daStr);
    
    // The parsed values should be accessible
    EXPECT_FALSE(da.getFontName().empty());
    EXPECT_GT(da.getFontPtSize(), 0.0);
}

// Test construction from empty DA string
TEST_F(DefaultAppearanceTest_758, ConstructFromEmptyDAString_758) {
    GooString daStr("");
    DefaultAppearance da(&daStr);
    
    // Should handle empty string gracefully
    // Values may be default/zero
    EXPECT_GE(da.getFontPtSize(), 0.0);
}
