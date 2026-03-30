#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <memory>
#include "GfxFont.h"

class GfxFontTest_1144 : public ::testing::Test {
protected:
    std::optional<std::string> testFontName = "TestFont";
    std::optional<std::string> emptyFontName = {};

    // Mock XRef, Dict, PSOutputDev for external interactions if necessary
    XRef *mockXRef;
    Dict *mockDict;
    PSOutputDev *mockPSOutputDev;
};

TEST_F(GfxFontTest_1144, GetName_ReturnsCorrectFontName_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    ASSERT_TRUE(font.getName().has_value());
    EXPECT_EQ(*font.getName(), "TestFont");
}

TEST_F(GfxFontTest_1144, GetName_ReturnsEmptyWhenNotSet_1144) {
    GfxFont font("tag", Ref(), std::nullopt, GfxFontType::typeA, Ref());
    ASSERT_FALSE(font.getName().has_value());
}

TEST_F(GfxFontTest_1144, IsSubset_ReturnsCorrectBool_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    // Assuming 'isSubset()' returns false for this example
    EXPECT_FALSE(font.isSubset());
}

TEST_F(GfxFontTest_1144, GetNameWithoutSubsetTag_ReturnsCorrectString_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont-Subset"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getNameWithoutSubsetTag(), "TestFont");
}

TEST_F(GfxFontTest_1144, GetTag_ReturnsCorrectTag_1144) {
    GfxFont font("TestTag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getTag(), "TestTag");
}

TEST_F(GfxFontTest_1144, GetID_ReturnsCorrectID_1144) {
    Ref ref; // Assume Ref is a valid object
    GfxFont font("TestTag", ref, std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getID(), &ref);
}

TEST_F(GfxFontTest_1144, IsFixedWidth_ReturnsTrueForFixedWidthFont_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("FixedWidthFont"), GfxFontType::typeA, Ref());
    // Assuming 'isFixedWidth()' would return true for fixed-width fonts
    EXPECT_TRUE(font.isFixedWidth());
}

TEST_F(GfxFontTest_1144, IsFixedWidth_ReturnsFalseForNonFixedWidthFont_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("NonFixedWidthFont"), GfxFontType::typeA, Ref());
    EXPECT_FALSE(font.isFixedWidth());
}

TEST_F(GfxFontTest_1144, GetFamily_ReturnsCorrectFamily_1144) {
    std::unique_ptr<GooString> family = std::make_unique<GooString>("Arial");
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(*font.getFamily(), "Arial");
}

TEST_F(GfxFontTest_1144, GetFamily_ReturnsNullIfNotSet_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getFamily(), nullptr);
}

TEST_F(GfxFontTest_1144, GetFontMatrix_ReturnsCorrectMatrix_1144) {
    std::array<double, 6> expectedMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getFontMatrix(), expectedMatrix);
}

TEST_F(GfxFontTest_1144, GetFontBBox_ReturnsCorrectBBox_1144) {
    std::array<double, 4> expectedBBox = {0.0, 0.0, 100.0, 100.0};
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getFontBBox(), expectedBBox);
}

TEST_F(GfxFontTest_1144, GetAscent_ReturnsCorrectAscent_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getAscent(), 0.0); // Assume default ascent value for test
}

TEST_F(GfxFontTest_1144, GetDescent_ReturnsCorrectDescent_1144) {
    GfxFont font("tag", Ref(), std::make_optional<std::string>("TestFont"), GfxFontType::typeA, Ref());
    EXPECT_EQ(font.getDescent(), 0.0); // Assume default descent value for test
}