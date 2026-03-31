#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Annot.h"

// Test fixture for DefaultAppearance
class DefaultAppearanceTest_756 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with fontName, fontPtSize, and unique_ptr<AnnotColor>
TEST_F(DefaultAppearanceTest_756, ConstructWithAnnotColor_756) {
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "Helv");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test construction with fontName, fontPtSize, and int fontColor
TEST_F(DefaultAppearanceTest_756, ConstructWithIntColor_756) {
    DefaultAppearance da("Courier", 10.0, 0xFF0000);
    
    EXPECT_EQ(da.getFontName(), "Courier");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 10.0);
}

// Test getFontName returns correct value
TEST_F(DefaultAppearanceTest_756, GetFontName_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("TimesRoman", 14.0, std::move(color));
    
    const std::string &name = da.getFontName();
    EXPECT_EQ(name, "TimesRoman");
}

// Test getFontPtSize returns correct value
TEST_F(DefaultAppearanceTest_756, GetFontPtSize_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 24.5, std::move(color));
    
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 24.5);
}

// Test setFontName changes font name
TEST_F(DefaultAppearanceTest_756, SetFontName_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontName("Courier");
    EXPECT_EQ(da.getFontName(), "Courier");
}

// Test setFontPtSize changes font size
TEST_F(DefaultAppearanceTest_756, SetFontPtSize_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontPtSize(20.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 20.0);
}

// Test setFontColor with unique_ptr<AnnotColor>
TEST_F(DefaultAppearanceTest_756, SetFontColorAnnotColor_756) {
    auto color1 = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color1));
    
    auto color2 = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    da.setFontColor(std::move(color2));
    
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test setFontName to empty string
TEST_F(DefaultAppearanceTest_756, SetFontNameEmpty_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontName("");
    EXPECT_EQ(da.getFontName(), "");
}

// Test setFontPtSize to zero
TEST_F(DefaultAppearanceTest_756, SetFontPtSizeZero_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontPtSize(0.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 0.0);
}

// Test setFontPtSize to negative value
TEST_F(DefaultAppearanceTest_756, SetFontPtSizeNegative_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontPtSize(-5.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), -5.0);
}

// Test toAppearanceString returns non-empty string
TEST_F(DefaultAppearanceTest_756, ToAppearanceString_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    const std::string result = da.toAppearanceString();
    EXPECT_FALSE(result.empty());
}

// Test toAppearanceString contains font name
TEST_F(DefaultAppearanceTest_756, ToAppearanceStringContainsFontName_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    const std::string result = da.toAppearanceString();
    EXPECT_NE(result.find("Helv"), std::string::npos);
}

// Test construction with nullptr AnnotColor
TEST_F(DefaultAppearanceTest_756, ConstructWithNullColor_756) {
    DefaultAppearance da("Helv", 12.0, nullptr);
    
    EXPECT_EQ(da.getFontName(), "Helv");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
    EXPECT_EQ(da.getFontColor(), nullptr);
}

// Test setFontColor with nullptr
TEST_F(DefaultAppearanceTest_756, SetFontColorNull_756) {
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontColor(nullptr);
    EXPECT_EQ(da.getFontColor(), nullptr);
}

// Test very large font size
TEST_F(DefaultAppearanceTest_756, VeryLargeFontSize_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 99999.99, std::move(color));
    
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 99999.99);
}

// Test very small positive font size
TEST_F(DefaultAppearanceTest_756, VerySmallFontSize_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 0.001, std::move(color));
    
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 0.001);
}

// Test setFontName multiple times
TEST_F(DefaultAppearanceTest_756, SetFontNameMultipleTimes_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontName("Courier");
    EXPECT_EQ(da.getFontName(), "Courier");
    
    da.setFontName("TimesRoman");
    EXPECT_EQ(da.getFontName(), "TimesRoman");
    
    da.setFontName("Helv");
    EXPECT_EQ(da.getFontName(), "Helv");
}

// Test construction from GooString (DA string parsing)
TEST_F(DefaultAppearanceTest_756, ConstructFromDAString_756) {
    GooString daStr("0 0 0 rg /Helv 12 Tf");
    DefaultAppearance da(&daStr);
    
    EXPECT_EQ(da.getFontName(), "Helv");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test construction from GooString with different font
TEST_F(DefaultAppearanceTest_756, ConstructFromDAStringDifferentFont_756) {
    GooString daStr("1 0 0 rg /Cour 10 Tf");
    DefaultAppearance da(&daStr);
    
    EXPECT_EQ(da.getFontName(), "Cour");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 10.0);
}

// Test toAppearanceString after modifications
TEST_F(DefaultAppearanceTest_756, ToAppearanceStringAfterModifications_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    da.setFontName("Courier");
    da.setFontPtSize(18.0);
    
    const std::string result = da.toAppearanceString();
    EXPECT_NE(result.find("Courier"), std::string::npos);
}

// Test getFontName returns reference that stays valid
TEST_F(DefaultAppearanceTest_756, GetFontNameReferenceValidity_756) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));
    
    const std::string &nameRef = da.getFontName();
    EXPECT_EQ(nameRef, "Helv");
    
    // After setting a new name, the old reference should reflect the new value
    da.setFontName("Courier");
    EXPECT_EQ(nameRef, "Courier");
}
