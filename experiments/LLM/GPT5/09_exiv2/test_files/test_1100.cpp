#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "image.hpp"
#include "error.hpp"
#include "types.hpp"

using namespace Exiv2;

// Mock for Registry to control behavior in the test cases.
class MockRegistry {
public:
    MOCK_METHOD(AccessMode, exifSupport, (), ());
    MOCK_METHOD(AccessMode, iptcSupport, (), ());
    MOCK_METHOD(AccessMode, xmpSupport, (), ());
    MOCK_METHOD(AccessMode, commentSupport, (), ());
};

class ImageFactoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any initial configurations if needed.
    }

    void TearDown() override {
        // Clean up any resources if needed.
    }

    ImageFactory imageFactory;
};

TEST_F(ImageFactoryTest, CheckModeReturnsExifSupport_WhenMetadataIsExif) {
    // Arrange
    MockRegistry mockRegistry;
    ImageType type = ImageType::jpeg;
    MetadataId metadataId = mdExif;

    // Expectation
    EXPECT_CALL(mockRegistry, exifSupport()).WillOnce(testing::Return(amReadWrite));

    // Act
    AccessMode result = imageFactory.checkMode(type, metadataId);

    // Assert
    EXPECT_EQ(result, amReadWrite);
}

TEST_F(ImageFactoryTest, CheckModeReturnsIptcSupport_WhenMetadataIsIptc) {
    // Arrange
    MockRegistry mockRegistry;
    ImageType type = ImageType::jpeg;
    MetadataId metadataId = mdIptc;

    // Expectation
    EXPECT_CALL(mockRegistry, iptcSupport()).WillOnce(testing::Return(amRead));

    // Act
    AccessMode result = imageFactory.checkMode(type, metadataId);

    // Assert
    EXPECT_EQ(result, amRead);
}

TEST_F(ImageFactoryTest, CheckModeReturnsXmpSupport_WhenMetadataIsXmp) {
    // Arrange
    MockRegistry mockRegistry;
    ImageType type = ImageType::jpeg;
    MetadataId metadataId = mdXmp;

    // Expectation
    EXPECT_CALL(mockRegistry, xmpSupport()).WillOnce(testing::Return(amReadWrite));

    // Act
    AccessMode result = imageFactory.checkMode(type, metadataId);

    // Assert
    EXPECT_EQ(result, amReadWrite);
}

TEST_F(ImageFactoryTest, CheckModeReturnsCommentSupport_WhenMetadataIsComment) {
    // Arrange
    MockRegistry mockRegistry;
    ImageType type = ImageType::jpeg;
    MetadataId metadataId = mdComment;

    // Expectation
    EXPECT_CALL(mockRegistry, commentSupport()).WillOnce(testing::Return(amRead));

    // Act
    AccessMode result = imageFactory.checkMode(type, metadataId);

    // Assert
    EXPECT_EQ(result, amRead);
}

TEST_F(ImageFactoryTest, CheckModeThrowsError_WhenUnsupportedMetadataIsProvided) {
    // Arrange
    MockRegistry mockRegistry;
    ImageType type = ImageType::jpeg;
    MetadataId metadataId = mdNone;

    // Act & Assert
    EXPECT_THROW(imageFactory.checkMode(type, metadataId), Error);
}

TEST_F(ImageFactoryTest, CheckModeThrowsError_WhenUnsupportedImageTypeIsProvided) {
    // Arrange
    MockRegistry mockRegistry;
    ImageType type = static_cast<ImageType>(100);  // Invalid ImageType
    MetadataId metadataId = mdExif;

    // Act & Assert
    EXPECT_THROW(imageFactory.checkMode(type, metadataId), Error);
}