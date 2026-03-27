#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    uint16_t supportedMetadata = 0x3; // Example value where EXIF and IPTC are supported

    ImageType imageType = ImageType::jpeg;



    void SetUp() override {

        io = std::make_unique<BasicIo>();

        image.reset(new Image(imageType, supportedMetadata, std::move(io)));

    }



    std::unique_ptr<Image> image;

};



TEST_F(ImageTest_1097, SupportsExifMetadata_1097) {

    MetadataId metadataId = MetadataId::exif;

    EXPECT_TRUE(image->supportsMetadata(metadataId));

}



TEST_F(ImageTest_1097, SupportsIptcMetadata_1097) {

    MetadataId metadataId = MetadataId::iptc;

    EXPECT_TRUE(image->supportsMetadata(metadataId));

}



TEST_F(ImageTest_1097, DoesNotSupportXmpMetadata_1097) {

    MetadataId metadataId = MetadataId::xmp;

    EXPECT_FALSE(image->supportsMetadata(metadataId));

}



TEST_F(ImageTest_1097, SupportsMultipleMetadataTypes_1097) {

    supportedMetadata = 0x7; // Example value where EXIF, IPTC, and XMP are supported

    image.reset(new Image(imageType, supportedMetadata, std::move(io)));

    EXPECT_TRUE(image->supportsMetadata(MetadataId::exif));

    EXPECT_TRUE(image->supportsMetadata(MetadataId::iptc));

    EXPECT_TRUE(image->supportsMetadata(MetadataId::xmp));

}



TEST_F(ImageTest_1097, SupportsNoMetadataTypes_1097) {

    supportedMetadata = 0x0; // Example value where no metadata types are supported

    image.reset(new Image(imageType, supportedMetadata, std::move(io)));

    EXPECT_FALSE(image->supportsMetadata(MetadataId::exif));

    EXPECT_FALSE(image->supportsMetadata(MetadataId::iptc));

    EXPECT_FALSE(image->supportsMetadata(MetadataId::xmp));

}
