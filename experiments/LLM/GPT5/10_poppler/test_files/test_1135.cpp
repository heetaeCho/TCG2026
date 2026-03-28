#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/FileSpec.h"
#include "./TestProjects/poppler/poppler/GooString.h"

// Mock class for external dependencies
class MockGooString : public GooString {
public:
    MOCK_CONST_METHOD0(get, const char*());
};

// Test case for `getFileName`
TEST_F(FileSpecTest_1135, getFileName_ReturnsCorrectFileName_1135) {
    // Arrange
    MockGooString mockGooString;
    EXPECT_CALL(mockGooString, get()).WillOnce(testing::Return("file_name"));

    FileSpec fileSpec(nullptr);
    fileSpec.setFileName(&mockGooString);

    // Act
    const GooString* result = fileSpec.getFileName();

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->get(), "file_name");
}

// Test case for `getFileNameForPlatform`
TEST_F(FileSpecTest_1136, getFileNameForPlatform_ReturnsPlatformFileName_1136) {
    // Arrange
    MockGooString mockGooString;
    EXPECT_CALL(mockGooString, get()).WillOnce(testing::Return("platform_file_name"));

    FileSpec fileSpec(nullptr);
    fileSpec.setPlatformFileName(&mockGooString);

    // Act
    GooString* result = fileSpec.getFileNameForPlatform();

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->get(), "platform_file_name");
}

// Test case for `getEmbeddedFile`
TEST_F(FileSpecTest_1137, getEmbeddedFile_ReturnsEmbeddedFile_1137) {
    // Arrange
    EmbFile* embFile = new EmbFile();
    FileSpec fileSpec(nullptr);
    fileSpec.setEmbeddedFile(embFile);

    // Act
    EmbFile* result = fileSpec.getEmbeddedFile();

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, embFile);
}

// Test case for `isOk` method
TEST_F(FileSpecTest_1138, isOk_ReturnsTrueWhenFileIsValid_1138) {
    // Arrange
    FileSpec fileSpec(nullptr);
    fileSpec.setFileName(new GooString("valid_file"));

    // Act
    bool result = fileSpec.isOk();

    // Assert
    EXPECT_TRUE(result);
}

// Test case for `getDescription`
TEST_F(FileSpecTest_1139, getDescription_ReturnsCorrectDescription_1139) {
    // Arrange
    MockGooString mockGooString;
    EXPECT_CALL(mockGooString, get()).WillOnce(testing::Return("file description"));

    FileSpec fileSpec(nullptr);
    fileSpec.setDescription(&mockGooString);

    // Act
    const GooString* result = fileSpec.getDescription();

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->get(), "file description");
}

// Test for `getFileName` when fileName is null
TEST_F(FileSpecTest_1140, getFileName_ReturnsNullWhenFileNameIsNull_1140) {
    // Arrange
    FileSpec fileSpec(nullptr);

    // Act
    const GooString* result = fileSpec.getFileName();

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Test for `getDescription` when description is null
TEST_F(FileSpecTest_1141, getDescription_ReturnsNullWhenDescriptionIsNull_1141) {
    // Arrange
    FileSpec fileSpec(nullptr);

    // Act
    const GooString* result = fileSpec.getDescription();

    // Assert
    EXPECT_EQ(result, nullptr);
}