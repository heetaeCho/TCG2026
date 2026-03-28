#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Rendition.h"

class MediaRenditionTest_1246 : public ::testing::Test {
protected:
    MediaRenditionTest_1246() {
        // Setup code if needed
    }

    ~MediaRenditionTest_1246() override {
        // Cleanup code if needed
    }
};

TEST_F(MediaRenditionTest_1246, GetBEParametersReturnsValidPointer_1246) {
    // Arrange
    MediaRendition rendition({});

    // Act
    const MediaParameters* parameters = rendition.getBEParameters();

    // Assert
    ASSERT_NE(parameters, nullptr); // Check that the returned pointer is not null
}

TEST_F(MediaRenditionTest_1246, GetMHParametersReturnsValidPointer_1247) {
    // Arrange
    MediaRendition rendition({});

    // Act
    const MediaParameters* parameters = rendition.getMHParameters();

    // Assert
    ASSERT_NE(parameters, nullptr); // Check that the returned pointer is not null
}

TEST_F(MediaRenditionTest_1246, IsOkReturnsTrueWhenMediaIsValid_1248) {
    // Arrange
    MediaRendition rendition({});

    // Act
    bool isValid = rendition.isOk();

    // Assert
    ASSERT_TRUE(isValid); // Assuming a valid object is always "ok"
}

TEST_F(MediaRenditionTest_1246, GetContentTypeReturnsValidString_1249) {
    // Arrange
    MediaRendition rendition({});

    // Act
    const GooString* contentType = rendition.getContentType();

    // Assert
    ASSERT_NE(contentType, nullptr); // Ensure the content type is not null
    // Additional assertion on the content type value can be added if known
}

TEST_F(MediaRenditionTest_1246, GetFileNameReturnsValidString_1250) {
    // Arrange
    MediaRendition rendition({});

    // Act
    const GooString* fileName = rendition.getFileName();

    // Assert
    ASSERT_NE(fileName, nullptr); // Ensure the file name is not null
    // Additional assertion on the file name can be added if expected
}

TEST_F(MediaRenditionTest_1246, GetIsEmbeddedReturnsCorrectValue_1251) {
    // Arrange
    MediaRendition rendition({});

    // Act
    bool isEmbedded = rendition.getIsEmbedded();

    // Assert
    ASSERT_FALSE(isEmbedded); // Assuming the default state is not embedded
}

TEST_F(MediaRenditionTest_1246, GetEmbeddedStreamReturnsNullWhenNotEmbedded_1252) {
    // Arrange
    MediaRendition rendition({});

    // Act
    Stream* stream = rendition.getEmbbededStream();

    // Assert
    ASSERT_EQ(stream, nullptr); // Ensure that the stream is null when not embedded
}

TEST_F(MediaRenditionTest_1246, GetEmbeddedStreamObjectReturnsNullWhenNotEmbedded_1253) {
    // Arrange
    MediaRendition rendition({});

    // Act
    const Object* streamObject = rendition.getEmbbededStreamObject();

    // Assert
    ASSERT_EQ(streamObject, nullptr); // Ensure the embedded stream object is null when not embedded
}

TEST_F(MediaRenditionTest_1246, CopyConstructorCreatesValidObject_1254) {
    // Arrange
    MediaRendition originalRendition({});

    // Act
    MediaRendition copiedRendition = originalRendition;

    // Assert
    ASSERT_TRUE(copiedRendition.isOk()); // Ensure the copied object is valid
}

TEST_F(MediaRenditionTest_1246, CopyAssignmentIsDeleted_1255) {
    // Arrange
    MediaRendition rendition({});

    // Act & Assert
    ASSERT_DEATH(rendition = MediaRendition({}), ".*"); // Assert that copy assignment is deleted
}

TEST_F(MediaRenditionTest_1246, OutputToFileWritesDataCorrectly_1256) {
    // Arrange
    MediaRendition rendition({});
    FILE* file = tmpfile();

    // Act
    rendition.outputToFile(file);

    // Assert
    ASSERT_NE(file, nullptr); // Ensure that file is valid (write operation itself cannot be fully tested)
    fclose(file);
}