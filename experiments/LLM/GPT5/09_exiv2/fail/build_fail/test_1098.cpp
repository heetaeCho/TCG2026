#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/image.hpp"
#include "exiv2/imagefactory.hpp"

using namespace Exiv2;

class ImageTest_1098 : public testing::Test {
protected:
    ImageType testImageType = ImageType::Jpeg;  // Example image type
    uint16_t testSupportedMetadata = 0x0001;  // Example metadata ID
    std::unique_ptr<BasicIo> mockIo;

    void SetUp() override {
        mockIo = std::make_unique<BasicIo>(); // Create a mock Io
    }
};

TEST_F(ImageTest_1098, CheckMode_ValidMetadataId_1098) {
    Image image(testImageType, testSupportedMetadata, std::move(mockIo));
    MetadataId metadataId = MetadataId::Exif;  // Example metadata ID for Exif
    AccessMode result = image.checkMode(metadataId);

    // Verify if the result is correct for the given metadataId
    EXPECT_EQ(result, ImageFactory::checkMode(testImageType, metadataId));
}

TEST_F(ImageTest_1098, CheckMode_InvalidMetadataId_1098) {
    Image image(testImageType, testSupportedMetadata, std::move(mockIo));
    MetadataId invalidMetadataId = MetadataId::Iptc;  // Example invalid metadata ID
    AccessMode result = image.checkMode(invalidMetadataId);

    // Verify if the result is correct for an invalid metadataId
    EXPECT_EQ(result, ImageFactory::checkMode(testImageType, invalidMetadataId));
}

TEST_F(ImageTest_1098, CheckMode_UnsupportedMetadata_1098) {
    Image image(testImageType, 0, std::move(mockIo));  // Create image with no supported metadata
    MetadataId unsupportedMetadataId = MetadataId::Xmp;  // Example unsupported metadata ID
    AccessMode result = image.checkMode(unsupportedMetadataId);

    // Ensure the result is default or invalid for unsupported metadata
    EXPECT_EQ(result, ImageFactory::checkMode(testImageType, unsupportedMetadataId));
}

TEST_F(ImageTest_1098, CheckMode_ValidImage_1098) {
    Image image(testImageType, testSupportedMetadata, std::move(mockIo));
    MetadataId validMetadataId = MetadataId::Exif;  // A valid metadata ID
    AccessMode result = image.checkMode(validMetadataId);

    // Check that the mode is correctly set
    EXPECT_EQ(result, ImageFactory::checkMode(testImageType, validMetadataId));
}

TEST_F(ImageTest_1098, CheckMode_WithMockedIo_1098) {
    // Use a mock for BasicIo to simulate its behavior during the test
    MockBasicIo mockIo;
    EXPECT_CALL(mockIo, read())
        .WillOnce(testing::Return(true)); // Mock expected behavior

    Image image(testImageType, testSupportedMetadata, std::make_unique<MockBasicIo>(mockIo));
    MetadataId metadataId = MetadataId::Exif;
    AccessMode result = image.checkMode(metadataId);

    // Verify that the function interacts with Io as expected
    EXPECT_EQ(result, ImageFactory::checkMode(testImageType, metadataId));
}