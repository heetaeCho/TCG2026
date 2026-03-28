#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



namespace {



class ExifThumbTest_771 : public ::testing::Test {

protected:

    Exiv2::ExifData exif_data_;

    Exiv2::ExifThumb exif_thumb_{exif_data_};



    const byte jpeg_buffer_[6] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};

    const size_t jpeg_size_ = sizeof(jpeg_buffer_);

    const Exiv2::URational xres_{72, 1};

    const Exiv2::URational yres_{72, 1};

    const uint16_t unit_ = 2; // Inch

};



TEST_F(ExifThumbTest_771, SetJpegThumbnail_NormalOperation_771) {

    exif_thumb_.setJpegThumbnail(jpeg_buffer_, jpeg_size_, xres_, yres_, unit_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.XResolution"].toRational(), xres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.YResolution"].toRational(), yres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.ResolutionUnit"].toInt64(), unit_);

}



TEST_F(ExifThumbTest_771, SetJpegThumbnail_ZeroSize_771) {

    exif_thumb_.setJpegThumbnail(jpeg_buffer_, 0, xres_, yres_, unit_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.XResolution"].toRational(), xres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.YResolution"].toRational(), yres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.ResolutionUnit"].toInt64(), unit_);

}



TEST_F(ExifThumbTest_771, SetJpegThumbnail_NullBuffer_771) {

    exif_thumb_.setJpegThumbnail(nullptr, jpeg_size_, xres_, yres_, unit_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.XResolution"].toRational(), xres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.YResolution"].toRational(), yres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.ResolutionUnit"].toInt64(), unit_);

}



TEST_F(ExifThumbTest_771, SetJpegThumbnail_UnitBoundary_771) {

    exif_thumb_.setJpegThumbnail(jpeg_buffer_, jpeg_size_, xres_, yres_, 0);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.XResolution"].toRational(), xres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.YResolution"].toRational(), yres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.ResolutionUnit"].toInt64(), 0);

}



TEST_F(ExifThumbTest_771, SetJpegThumbnail_UnitBoundaryMax_771) {

    exif_thumb_.setJpegThumbnail(jpeg_buffer_, jpeg_size_, xres_, yres_, std::numeric_limits<uint16_t>::max());

    EXPECT_EQ(exif_data_["Exif.Thumbnail.XResolution"].toRational(), xres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.YResolution"].toRational(), yres_);

    EXPECT_EQ(exif_data_["Exif.Thumbnail.ResolutionUnit"].toInt64(), std::numeric_limits<uint16_t>::max());

}



}  // namespace
