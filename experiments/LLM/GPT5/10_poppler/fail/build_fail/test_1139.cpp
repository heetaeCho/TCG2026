#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"

using namespace testing;

class GfxFontTest_1139 : public ::testing::Test {
protected:
    GfxFontTest_1139() {
        // Set up code if necessary
    }
    
    // You can add helper functions or mock objects if needed
};

TEST_F(GfxFontTest_1139, GetIDReturnsCorrectID_1139) {
    // Arrange
    Ref expectedID; // Create a reference to the expected ID (fill as needed)
    GfxFont font("tag", expectedID, nullptr, GfxFontType::SomeType, expectedID);

    // Act
    const Ref* actualID = font.getID();

    // Assert
    EXPECT_EQ(actualID, &expectedID);
}

TEST_F(GfxFontTest_1139, GetTagReturnsCorrectTag_1139) {
    // Arrange
    const std::string expectedTag = "testTag";
    GfxFont font(expectedTag.c_str(), Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    const std::string& actualTag = font.getTag();

    // Assert
    EXPECT_EQ(actualTag, expectedTag);
}

TEST_F(GfxFontTest_1139, IsSubsetReturnsCorrectValue_1139) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    bool isSubset = font.isSubset();

    // Assert
    EXPECT_FALSE(isSubset); // Assuming default behavior is not a subset
}

TEST_F(GfxFontTest_1139, GetNameWithoutSubsetTagReturnsCorrectName_1139) {
    // Arrange
    const std::string expectedName = "FontName";
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());
    
    // Act
    std::string name = font.getNameWithoutSubsetTag();

    // Assert
    EXPECT_EQ(name, expectedName);
}

TEST_F(GfxFontTest_1139, GetFamilyReturnsCorrectFamily_1139) {
    // Arrange
    const GooString expectedFamily("FontFamily");
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    const GooString* family = font.getFamily();

    // Assert
    EXPECT_EQ(family->getCString(), expectedFamily.getCString());
}

TEST_F(GfxFontTest_1139, GetWeightReturnsCorrectWeight_1139) {
    // Arrange
    Weight expectedWeight = Weight::Bold;
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    Weight weight = font.getWeight();

    // Assert
    EXPECT_EQ(weight, expectedWeight);
}

TEST_F(GfxFontTest_1139, IsOkReturnsTrue_1139) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    bool isOk = font.isOk();

    // Assert
    EXPECT_TRUE(isOk); // Assuming this font is ok by default
}

TEST_F(GfxFontTest_1139, MatchesReturnsTrueForMatchingTag_1139) {
    // Arrange
    const std::string tagToMatch = "testTag";
    GfxFont font(tagToMatch.c_str(), Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    bool matches = font.matches(tagToMatch.c_str());

    // Assert
    EXPECT_TRUE(matches);
}

TEST_F(GfxFontTest_1139, GetFontMatrixReturnsCorrectMatrix_1139) {
    // Arrange
    std::array<double, 6> expectedMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    const std::array<double, 6>& matrix = font.getFontMatrix();

    // Assert
    EXPECT_EQ(matrix, expectedMatrix);
}

TEST_F(GfxFontTest_1139, GetAscentReturnsCorrectAscent_1139) {
    // Arrange
    double expectedAscent = 10.0;
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    double ascent = font.getAscent();

    // Assert
    EXPECT_EQ(ascent, expectedAscent);
}

TEST_F(GfxFontTest_1139, GetDescentReturnsCorrectDescent_1139) {
    // Arrange
    double expectedDescent = -2.0;
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    double descent = font.getDescent();

    // Assert
    EXPECT_EQ(descent, expectedDescent);
}

TEST_F(GfxFontTest_1139, IsCIDFontReturnsCorrectValue_1139) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    bool isCIDFont = font.isCIDFont();

    // Assert
    EXPECT_FALSE(isCIDFont); // Assuming the default value is false
}

TEST_F(GfxFontTest_1139, HasToUnicodeCMapReturnsTrue_1139) {
    // Arrange
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    bool hasCMap = font.hasToUnicodeCMap();

    // Assert
    EXPECT_TRUE(hasCMap); // Assuming default behavior
}

TEST_F(GfxFontTest_1139, GetEncodingNameReturnsCorrectName_1139) {
    // Arrange
    const std::string expectedEncodingName = "WinAnsiEncoding";
    GfxFont font("tag", Ref(), nullptr, GfxFontType::SomeType, Ref());

    // Act
    const std::string& encodingName = font.getEncodingName();

    // Assert
    EXPECT_EQ(encodingName, expectedEncodingName);
}