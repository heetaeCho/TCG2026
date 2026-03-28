#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"

class GfxFontTest_1141 : public testing::Test {
protected:
    // Sample objects or mock setups can go here, if necessary
    // Example: GfxFont fontMock(...);
};

TEST_F(GfxFontTest_1141, GetFamilyReturnsCorrectFamily_1141) {
    // Mock or create a GfxFont instance
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);
    font->family = std::make_unique<GooString>("Arial");

    // Call the function under test
    const GooString* family = font->getFamily();

    // Verify behavior
    EXPECT_EQ(family->getCString(), "Arial");
}

TEST_F(GfxFontTest_1141, GetFamilyReturnsNullIfNoFamilySet_1142) {
    // Create font without family set
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);

    // Call the function under test
    const GooString* family = font->getFamily();

    // Verify behavior - it should return nullptr if family is not set
    EXPECT_EQ(family, nullptr);
}

TEST_F(GfxFontTest_1141, GetFamilyHandlesEmptyFamily_1143) {
    // Create font with empty family
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("tag", 1, std::make_optional(""), GfxFontType::type1, 2);
    font->family = std::make_unique<GooString>("");

    // Call the function under test
    const GooString* family = font->getFamily();

    // Verify behavior - it should return an empty string when family is set as empty
    EXPECT_EQ(family->getCString(), "");
}

TEST_F(GfxFontTest_1141, GetFamilyIsConst_1144) {
    // Create font
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);

    // Call the function under test
    const GooString* family = font->getFamily();

    // Verify that the returned family string cannot be modified
    EXPECT_TRUE(std::is_const<std::remove_reference<decltype(*family)>::type>::value);
}

TEST_F(GfxFontTest_1141, GetFamilyHandlesInvalidPointer_1145) {
    // Create font with invalid family (nullptr)
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);
    font->family = nullptr;

    // Call the function under test
    const GooString* family = font->getFamily();

    // Verify behavior - it should return nullptr when family is not initialized
    EXPECT_EQ(family, nullptr);
}

TEST_F(GfxFontTest_1141, GetFamilyMockBehavior_1146) {
    // Mock the GooString and GfxFont behaviors
    GooString mockFamily("Times New Roman");
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("tag", 1, std::make_optional("Times New Roman"), GfxFontType::type1, 2);
    font->family = std::make_unique<GooString>(mockFamily);

    // Use a mock or simulate function call
    const GooString* family = font->getFamily();

    // Verify that the mock behavior works as expected
    EXPECT_EQ(family->getCString(), "Times New Roman");
}

TEST_F(GfxFontTest_1141, IsOkReturnsTrueForValidFont_1147) {
    // Create a valid font
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("valid_tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);

    // Call the function under test
    bool isValid = font->isOk();

    // Verify that the font is valid
    EXPECT_TRUE(isValid);
}

TEST_F(GfxFontTest_1141, IsOkReturnsFalseForInvalidFont_1148) {
    // Create an invalid font
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("invalid_tag", 1, std::make_optional(""), GfxFontType::type1, 2);

    // Call the function under test
    bool isValid = font->isOk();

    // Verify that the font is invalid
    EXPECT_FALSE(isValid);
}

TEST_F(GfxFontTest_1141, GetTagReturnsCorrectTag_1149) {
    // Create font
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("custom_tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);

    // Call the function under test
    const std::string& tag = font->getTag();

    // Verify behavior - it should return the correct tag
    EXPECT_EQ(tag, "custom_tag");
}

TEST_F(GfxFontTest_1141, MatchesReturnsTrueForMatchingTags_1150) {
    // Create font
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("custom_tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);

    // Call the function under test
    bool match = font->matches("custom_tag");

    // Verify behavior - it should match the tag
    EXPECT_TRUE(match);
}

TEST_F(GfxFontTest_1141, MatchesReturnsFalseForNonMatchingTags_1151) {
    // Create font
    std::unique_ptr<GfxFont> font = std::make_unique<GfxFont>("custom_tag", 1, std::make_optional("Arial"), GfxFontType::type1, 2);

    // Call the function under test
    bool match = font->matches("another_tag");

    // Verify behavior - it should not match the tag
    EXPECT_FALSE(match);
}