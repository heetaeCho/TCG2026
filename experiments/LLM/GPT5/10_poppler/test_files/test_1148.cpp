#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/GfxFont.h"
#include "./TestProjects/poppler/poppler/Ref.h"

class GfxFontTest_1148 : public testing::Test {
protected:
    GfxFontTest_1148() = default;
    ~GfxFontTest_1148() override = default;
};

// Mock external dependencies if needed
// Example: Mock XRef, GooString, etc., if required for external interaction verification

TEST_F(GfxFontTest_1148, InvalidateEmbeddedFont_ValidFontID_ReturnsTrue_1148) {
    // Arrange: Create a GfxFont instance with a valid embedded font ID
    Ref validRef{1, 1};  // Example valid Ref ID
    GfxFont font("TestTag", validRef, nullptr, GfxFontType::typeA, validRef);

    // Act: Call invalidateEmbeddedFont
    bool result = font.invalidateEmbeddedFont();

    // Assert: The embedded font ID is invalidated, and the function returns true
    EXPECT_TRUE(result);
    EXPECT_EQ(validRef.num, Ref::INVALID().num);
    EXPECT_EQ(validRef.gen, Ref::INVALID().gen);
}

TEST_F(GfxFontTest_1148, InvalidateEmbeddedFont_InvalidFontID_ReturnsFalse_1148) {
    // Arrange: Create a GfxFont instance with an invalid embedded font ID
    Ref invalidRef = Ref::INVALID();
    GfxFont font("TestTag", invalidRef, nullptr, GfxFontType::typeA, invalidRef);

    // Act: Call invalidateEmbeddedFont
    bool result = font.invalidateEmbeddedFont();

    // Assert: The embedded font ID was already invalid, and the function returns false
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1148, GetEmbeddedFontID_ReturnsCorrectID_1148) {
    // Arrange: Create a GfxFont instance with a known embedded font ID
    Ref knownRef{1, 2};
    GfxFont font("TestTag", knownRef, nullptr, GfxFontType::typeA, knownRef);

    // Act: Get the embedded font ID
    Ref returnedRef;
    bool result = font.getEmbeddedFontID(&returnedRef);

    // Assert: The returned embedded font ID matches the one set in the font
    EXPECT_TRUE(result);
    EXPECT_EQ(returnedRef.num, knownRef.num);
    EXPECT_EQ(returnedRef.gen, knownRef.gen);
}

TEST_F(GfxFontTest_1148, GetFontMatrix_ReturnsValidMatrix_1148) {
    // Arrange: Create a GfxFont instance with a predefined font matrix
    std::array<double, 6> expectedMatrix{1.0, 0.0, 0.0, 1.0, 0.0, 0.0};  // Example matrix
    GfxFont font("TestTag", Ref::INVALID(), nullptr, GfxFontType::typeA, Ref::INVALID());

    // Act: Get the font matrix
    const std::array<double, 6>& matrix = font.getFontMatrix();

    // Assert: The returned matrix matches the expected one
    EXPECT_EQ(matrix, expectedMatrix);
}

TEST_F(GfxFontTest_1148, IsBase14Font_ValidFamilyAndStyle_ReturnsTrue_1148) {
    // Arrange: Valid base 14 font family and style
    std::string_view family = "Times";
    std::string_view style = "Roman";

    // Act: Check if the font is a base 14 font
    bool result = GfxFont::isBase14Font(family, style);

    // Assert: It should return true for base 14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1148, GetNameWithoutSubsetTag_ReturnsCorrectName_1148) {
    // Arrange: Create a GfxFont instance with a name that contains a subset tag
    std::string fontName = "MyFont-Subset";
    GfxFont font("TestTag", Ref::INVALID(), std::make_optional(fontName), GfxFontType::typeA, Ref::INVALID());

    // Act: Get the name without the subset tag
    std::string result = font.getNameWithoutSubsetTag();

    // Assert: The result should remove the "-Subset" part
    EXPECT_EQ(result, "MyFont");
}

TEST_F(GfxFontTest_1148, GetFontBBox_ReturnsValidBoundingBox_1148) {
    // Arrange: Create a GfxFont instance with a predefined font bounding box
    std::array<double, 4> expectedBBox{0.0, 0.0, 100.0, 200.0};  // Example bounding box
    GfxFont font("TestTag", Ref::INVALID(), nullptr, GfxFontType::typeA, Ref::INVALID());

    // Act: Get the font bounding box
    const std::array<double, 4>& bbox = font.getFontBBox();

    // Assert: The returned bounding box matches the expected one
    EXPECT_EQ(bbox, expectedBBox);
}

TEST_F(GfxFontTest_1148, IsSerif_ReturnsTrueForSerifFont_1148) {
    // Arrange: Create a GfxFont instance with a serif font
    GfxFont font("TestTag", Ref::INVALID(), nullptr, GfxFontType::typeA, Ref::INVALID());

    // Act: Check if the font is serif
    bool result = font.isSerif();

    // Assert: The font should be identified as serif
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1148, IsFixedWidth_ReturnsFalseForNonFixedWidthFont_1148) {
    // Arrange: Create a GfxFont instance that is not fixed-width
    GfxFont font("TestTag", Ref::INVALID(), nullptr, GfxFontType::typeA, Ref::INVALID());

    // Act: Check if the font is fixed-width
    bool result = font.isFixedWidth();

    // Assert: The font should not be fixed-width
    EXPECT_FALSE(result);
}