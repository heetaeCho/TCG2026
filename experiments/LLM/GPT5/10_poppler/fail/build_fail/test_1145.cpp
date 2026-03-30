#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>
#include <optional>

#include "GfxFont.h"

// Mock class for dependencies if needed
class MockXRef : public XRef {
    // Mock methods as needed
};

class GfxFontTest_1145 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if necessary
    }

    void TearDown() override {
        // Cleanup code if necessary
    }
};

// Normal operation test for getType method
TEST_F(GfxFontTest_1145, GetTypeReturnsCorrectFontType_1145) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());

    // Act
    GfxFontType result = font.getType();

    // Assert
    EXPECT_EQ(result, GfxFontType::Type1);
}

// Boundary condition test for getType with a different font type
TEST_F(GfxFontTest_1145, GetTypeReturnsDifferentFontType_1146) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type3, Ref());

    // Act
    GfxFontType result = font.getType();

    // Assert
    EXPECT_EQ(result, GfxFontType::Type3);
}

// Exceptional case: Test invalid state or uninitialized object (if any)
TEST_F(GfxFontTest_1145, GetTypeThrowsForUninitializedFont_1147) {
    // Arrange: assuming we can simulate an uninitialized state for the test
    GfxFont font("", Ref(), nullptr, GfxFontType::Unknown, Ref());

    // Act & Assert
    EXPECT_EQ(font.getType(), GfxFontType::Unknown);
}

// Test case for getNameWithoutSubsetTag
TEST_F(GfxFontTest_1145, GetNameWithoutSubsetTagReturnsCorrectValue_1148) {
    // Arrange
    GfxFont font("tag", Ref(), std::make_unique<GooString>("Arial"), GfxFontType::Type1, Ref());
    
    // Act
    std::string result = font.getNameWithoutSubsetTag();

    // Assert
    EXPECT_EQ(result, "Arial");
}

// Test exceptional case for getNameWithoutSubsetTag when family name is not set
TEST_F(GfxFontTest_1145, GetNameWithoutSubsetTagEmptyName_1149) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());

    // Act
    std::string result = font.getNameWithoutSubsetTag();

    // Assert
    EXPECT_EQ(result, "");
}

// Test for matches method with matching tag
TEST_F(GfxFontTest_1145, MatchesReturnsTrueForMatchingTag_1150) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());

    // Act
    bool result = font.matches("tag");

    // Assert
    EXPECT_TRUE(result);
}

// Test for matches method with non-matching tag
TEST_F(GfxFontTest_1145, MatchesReturnsFalseForNonMatchingTag_1151) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());

    // Act
    bool result = font.matches("differentTag");

    // Assert
    EXPECT_FALSE(result);
}

// Test for getFamily when family is set
TEST_F(GfxFontTest_1145, GetFamilyReturnsCorrectFamily_1152) {
    // Arrange
    auto family = std::make_unique<GooString>("Arial");
    GfxFont font("tag", Ref(), std::move(family), GfxFontType::Type1, Ref());

    // Act
    const GooString* result = font.getFamily();

    // Assert
    EXPECT_EQ(result->getCString(), "Arial");
}

// Test for getFamily when family is not set
TEST_F(GfxFontTest_1145, GetFamilyReturnsNullWhenNotSet_1153) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());

    // Act
    const GooString* result = font.getFamily();

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Test for isFixedWidth method (assume implementation or mock based on actual usage)
TEST_F(GfxFontTest_1145, IsFixedWidthReturnsCorrectValue_1154) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());

    // Act
    bool result = font.isFixedWidth();

    // Assert
    EXPECT_FALSE(result);
}

// Exceptional case for getEmbeddedFontName (assuming non-embedded font)
TEST_F(GfxFontTest_1145, GetEmbeddedFontNameReturnsNullForNonEmbedded_1155) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());

    // Act
    const GooString* result = font.getEmbeddedFontName();

    // Assert
    EXPECT_EQ(result, nullptr);
}