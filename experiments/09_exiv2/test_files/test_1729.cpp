#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "exiv2/exif.hpp"

#include "exiv2/image.hpp"

#include "exiv2/tiffimage.hpp"



using namespace Exiv2;

using ::testing::Return;



class TiffImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock BasicIo object

        auto io = std::make_unique<BasicIo>();

        tiff_image_ = std::make_unique<TiffImage>(std::move(io), false);

    }



    std::unique_ptr<TiffImage> tiff_image_;

};



TEST_F(TiffImageTest, MimeTypeDefault_1729) {

    EXPECT_EQ(tiff_image_->mimeType(), "image/tiff");

}



TEST_F(TiffImageTest, MimeTypeWithCompression_1729) {

    Exifdatum exif_datum("Exif.PrimaryGroup.Compression", new UShort(65000));

    tiff_image_->exifData().add(exif_datum);



    EXPECT_EQ(tiff_image_->mimeType(), "image/x-kodak-dcr");

}



TEST_F(TiffImageTest, MimeTypeWithUnknownCompression_1729) {

    Exifdatum exif_datum("Exif.PrimaryGroup.Compression", new UShort(0));

    tiff_image_->exifData().add(exif_datum);



    EXPECT_EQ(tiff_image_->mimeType(), "image/tiff");

}



TEST_F(TiffImageTest, MimeTypeWithNonDefaultCompression_1729) {

    Exifdatum exif_datum("Exif.PrimaryGroup.Compression", new UShort(65535));

    tiff_image_->exifData().add(exif_datum);



    EXPECT_EQ(tiff_image_->mimeType(), "image/x-pentax-pef");

}



TEST_F(TiffImageTest, MimeTypeWithMissingCompression_1729) {

    // No compression tag added

    EXPECT_EQ(tiff_image_->mimeType(), "image/tiff");

}
