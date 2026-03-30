#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FoFiIdentifier.h"
#include "FoFiTrueType.h"
#include "Error.h"

// Mocking the dependencies for testing
class MockFoFiIdentifier {
public:
    MOCK_METHOD(FoFiIdentifierType, identifyFile, (const char*), (const));
};

class MockFoFiTrueType {
public:
    MOCK_METHOD(std::unique_ptr<FoFiTrueType>, load, (const char*, int), (const));
    MOCK_METHOD(int, findCmap, (int, int), (const));
    MOCK_METHOD(int, mapCodeToGID, (int, Unicode), (const));
};

TEST_F(EmbeddedFontTest_1902, SupportedFontForEmbedding_WithValidTrueTypeFont_ReturnsTrue) {
    // Arrange
    const char* validFilepath = "valid_font.ttf";
    int validFaceIndex = 0;
    Unicode testChar = 65; // 'A' character

    // Mock the behavior of identifyFile
    EXPECT_CALL(mockFoFiIdentifier, identifyFile(validFilepath))
        .WillOnce(testing::Return(fofiIdTrueType));

    // Mock the behavior of FoFiTrueType::load
    auto mockFoFiTrueType = std::make_unique<MockFoFiTrueType>();
    EXPECT_CALL(*mockFoFiTrueType, findCmap(0, 3)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockFoFiTrueType, mapCodeToGID(0, testChar)).WillOnce(testing::Return(1));

    // Act
    bool result = supportedFontForEmbedding(testChar, validFilepath, validFaceIndex);

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(EmbeddedFontTest_1902, SupportedFontForEmbedding_WithInvalidFontFileExtension_ReturnsFalse) {
    // Arrange
    const char* invalidFilepath = "invalid_font.bmp";
    int validFaceIndex = 0;
    Unicode testChar = 65; // 'A' character

    // Act
    bool result = supportedFontForEmbedding(testChar, invalidFilepath, validFaceIndex);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(EmbeddedFontTest_1902, SupportedFontForEmbedding_WithInvalidFontType_ReturnsFalse) {
    // Arrange
    const char* validFilepath = "valid_font.otf";
    int validFaceIndex = 0;
    Unicode testChar = 65; // 'A' character

    // Mock the behavior of identifyFile
    EXPECT_CALL(mockFoFiIdentifier, identifyFile(validFilepath))
        .WillOnce(testing::Return(fofiIdUnknown));

    // Act
    bool result = supportedFontForEmbedding(testChar, validFilepath, validFaceIndex);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(EmbeddedFontTest_1902, SupportedFontForEmbedding_WithFontLoadFailure_ReturnsFalse) {
    // Arrange
    const char* validFilepath = "valid_font.ttf";
    int validFaceIndex = 0;
    Unicode testChar = 65; // 'A' character

    // Mock the behavior of identifyFile
    EXPECT_CALL(mockFoFiIdentifier, identifyFile(validFilepath))
        .WillOnce(testing::Return(fofiIdTrueType));

    // Mock the behavior of FoFiTrueType::load failure
    EXPECT_CALL(mockFoFiTrueType, load(validFilepath, validFaceIndex))
        .WillOnce(testing::Return(nullptr));

    // Act
    bool result = supportedFontForEmbedding(testChar, validFilepath, validFaceIndex);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(EmbeddedFontTest_1902, SupportedFontForEmbedding_WithNoUnicodeMap_ReturnsFalse) {
    // Arrange
    const char* validFilepath = "valid_font.ttf";
    int validFaceIndex = 0;
    Unicode testChar = 65; // 'A' character

    // Mock the behavior of identifyFile
    EXPECT_CALL(mockFoFiIdentifier, identifyFile(validFilepath))
        .WillOnce(testing::Return(fofiIdTrueType));

    // Mock the behavior of FoFiTrueType::load and findCmap returning negative value
    auto mockFoFiTrueType = std::make_unique<MockFoFiTrueType>();
    EXPECT_CALL(*mockFoFiTrueType, findCmap(0, 3)).WillOnce(testing::Return(-1));

    // Act
    bool result = supportedFontForEmbedding(testChar, validFilepath, validFaceIndex);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(EmbeddedFontTest_1902, SupportedFontForEmbedding_WithGlyphMappingFailure_ReturnsFalse) {
    // Arrange
    const char* validFilepath = "valid_font.ttf";
    int validFaceIndex = 0;
    Unicode testChar = 65; // 'A' character

    // Mock the behavior of identifyFile
    EXPECT_CALL(mockFoFiIdentifier, identifyFile(validFilepath))
        .WillOnce(testing::Return(fofiIdTrueType));

    // Mock the behavior of FoFiTrueType::load and findCmap returning valid value but mapCodeToGID failing
    auto mockFoFiTrueType = std::make_unique<MockFoFiTrueType>();
    EXPECT_CALL(*mockFoFiTrueType, findCmap(0, 3)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockFoFiTrueType, mapCodeToGID(0, testChar)).WillOnce(testing::Return(0));

    // Act
    bool result = supportedFontForEmbedding(testChar, validFilepath, validFaceIndex);

    // Assert
    EXPECT_FALSE(result);
}