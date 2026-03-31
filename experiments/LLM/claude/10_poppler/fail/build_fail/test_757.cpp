#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Annot.h"

// Test fixture for DefaultAppearance tests
class DefaultAppearanceTest_757 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with font name, size, and AnnotColor
TEST_F(DefaultAppearanceTest_757, ConstructWithAnnotColor_757)
{
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    EXPECT_EQ(da.getFontName(), "Helvetica");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test construction with font name, size, and int color
TEST_F(DefaultAppearanceTest_757, ConstructWithIntColor_757)
{
    DefaultAppearance da("Courier", 10.5, 0xFF0000);

    EXPECT_EQ(da.getFontName(), "Courier");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 10.5);
}

// Test getFontName returns correct name
TEST_F(DefaultAppearanceTest_757, GetFontNameReturnsCorrectValue_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("TimesRoman", 14.0, std::move(color));

    EXPECT_EQ(da.getFontName(), "TimesRoman");
}

// Test getFontPtSize returns correct size
TEST_F(DefaultAppearanceTest_757, GetFontPtSizeReturnsCorrectValue_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 24.0, std::move(color));

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 24.0);
}

// Test getFontColor returns non-null when color is set
TEST_F(DefaultAppearanceTest_757, GetFontColorReturnsNonNull_757)
{
    auto color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    const AnnotColor *fc = da.getFontColor();
    EXPECT_NE(fc, nullptr);
}

// Test setFontName changes the font name
TEST_F(DefaultAppearanceTest_757, SetFontNameChangesName_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    da.setFontName("Courier");
    EXPECT_EQ(da.getFontName(), "Courier");
}

// Test setFontPtSize changes the font size
TEST_F(DefaultAppearanceTest_757, SetFontPtSizeChangesSize_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    da.setFontPtSize(18.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 18.0);
}

// Test setFontColor with AnnotColor changes the color
TEST_F(DefaultAppearanceTest_757, SetFontColorWithAnnotColor_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    auto newColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    da.setFontColor(std::move(newColor));

    const AnnotColor *fc = da.getFontColor();
    EXPECT_NE(fc, nullptr);
}

// Test setFontColor with int changes the color
TEST_F(DefaultAppearanceTest_757, SetFontColorWithInt_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    da.setFontColor(0x00FF00);
    // After setting int color, we verify it doesn't crash and the object is still usable
    EXPECT_EQ(da.getFontName(), "Helvetica");
}

// Test toAppearanceString returns a non-empty string
TEST_F(DefaultAppearanceTest_757, ToAppearanceStringNotEmpty_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));

    const std::string result = da.toAppearanceString();
    EXPECT_FALSE(result.empty());
}

// Test boundary: zero font size
TEST_F(DefaultAppearanceTest_757, ZeroFontSize_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 0.0, std::move(color));

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 0.0);
}

// Test boundary: very large font size
TEST_F(DefaultAppearanceTest_757, VeryLargeFontSize_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 99999.0, std::move(color));

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 99999.0);
}

// Test boundary: negative font size
TEST_F(DefaultAppearanceTest_757, NegativeFontSize_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", -5.0, std::move(color));

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), -5.0);
}

// Test boundary: empty font name
TEST_F(DefaultAppearanceTest_757, EmptyFontName_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("", 12.0, std::move(color));

    EXPECT_EQ(da.getFontName(), "");
}

// Test setFontName to empty string
TEST_F(DefaultAppearanceTest_757, SetFontNameToEmpty_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    da.setFontName("");
    EXPECT_EQ(da.getFontName(), "");
}

// Test setFontColor with nullptr
TEST_F(DefaultAppearanceTest_757, SetFontColorWithNullptr_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    da.setFontColor(std::unique_ptr<AnnotColor>(nullptr));
    EXPECT_EQ(da.getFontColor(), nullptr);
}

// Test construction with nullptr AnnotColor
TEST_F(DefaultAppearanceTest_757, ConstructWithNullAnnotColor_757)
{
    DefaultAppearance da("Helvetica", 12.0, std::unique_ptr<AnnotColor>(nullptr));

    EXPECT_EQ(da.getFontName(), "Helvetica");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
    EXPECT_EQ(da.getFontColor(), nullptr);
}

// Test toAppearanceString contains font name info
TEST_F(DefaultAppearanceTest_757, ToAppearanceStringContainsFontInfo_757)
{
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    DefaultAppearance da("Helv", 12.0, std::move(color));

    const std::string result = da.toAppearanceString();
    // The appearance string should contain the font name reference
    EXPECT_NE(result.find("Helv"), std::string::npos);
}

// Test multiple setFontPtSize calls
TEST_F(DefaultAppearanceTest_757, MultipleSetFontPtSizeCalls_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    da.setFontPtSize(14.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 14.0);

    da.setFontPtSize(16.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 16.0);

    da.setFontPtSize(8.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 8.0);
}

// Test multiple setFontName calls
TEST_F(DefaultAppearanceTest_757, MultipleSetFontNameCalls_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));

    da.setFontName("Courier");
    EXPECT_EQ(da.getFontName(), "Courier");

    da.setFontName("TimesRoman");
    EXPECT_EQ(da.getFontName(), "TimesRoman");
}

// Test construction from GooString (DA string parsing)
TEST_F(DefaultAppearanceTest_757, ConstructFromDAString_757)
{
    GooString daStr("/Helv 12 Tf 0 g");
    DefaultAppearance da(&daStr);

    // After parsing, we should be able to get font information
    EXPECT_FALSE(da.getFontName().empty());
    EXPECT_GT(da.getFontPtSize(), 0.0);
}

// Test fractional font size
TEST_F(DefaultAppearanceTest_757, FractionalFontSize_757)
{
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 10.5, std::move(color));

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 10.5);
}
