#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <vector>
#include <cstring>

using namespace Exiv2;

class ExifThumbTest_771 : public ::testing::Test {
protected:
    ExifData exifData_;
};

// Test that setJpegThumbnail with buffer, size, xres, yres, unit sets the resolution metadata
TEST_F(ExifThumbTest_771, SetJpegThumbnailWithResolution_SetsXResolution_771) {
    ExifThumb thumb(exifData_);
    
    // Minimal JPEG data (SOI marker)
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(72, 1);
    URational yres(72, 1);
    uint16_t unit = 2; // inches
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toRational(), Rational(72, 1));
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailWithResolution_SetsYResolution_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(300, 1);
    URational yres(300, 1);
    uint16_t unit = 2;
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.YResolution"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toRational(), Rational(300, 1));
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailWithResolution_SetsResolutionUnit_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(72, 1);
    URational yres(72, 1);
    uint16_t unit = 3; // centimeters
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.ResolutionUnit"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(), 3);
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailWithResolution_DifferentResolutions_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(150, 1);
    URational yres(200, 1);
    uint16_t unit = 2;
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    auto itX = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(itX, exifData_.end());
    EXPECT_EQ(itX->toRational(), Rational(150, 1));
    
    auto itY = exifData_.findKey(ExifKey("Exif.Thumbnail.YResolution"));
    ASSERT_NE(itY, exifData_.end());
    EXPECT_EQ(itY->toRational(), Rational(200, 1));
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailWithResolution_UnitInches_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(72, 1);
    URational yres(72, 1);
    uint16_t unit = 2; // inches
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.ResolutionUnit"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(), 2);
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailWithResolution_FractionalResolution_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(72, 10);
    URational yres(144, 10);
    uint16_t unit = 2;
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    auto itX = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(itX, exifData_.end());
    EXPECT_EQ(itX->toRational(), Rational(72, 10));
    
    auto itY = exifData_.findKey(ExifKey("Exif.Thumbnail.YResolution"));
    ASSERT_NE(itY, exifData_.end());
    EXPECT_EQ(itY->toRational(), Rational(144, 10));
}

// Test basic setJpegThumbnail (without resolution) and then erase
TEST_F(ExifThumbTest_771, SetJpegThumbnailBasic_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    
    // Should not throw
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData.data(), jpegData.size()));
}

TEST_F(ExifThumbTest_771, Erase_RemovesThumbnailData_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(72, 1);
    URational yres(72, 1);
    uint16_t unit = 2;
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    // Verify data was set
    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(it, exifData_.end());
    
    // Erase the thumbnail
    thumb.erase();
    
    // After erase, thumbnail-related entries should be removed
    it = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    EXPECT_EQ(it, exifData_.end());
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailOverwrite_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    
    // Set first time
    URational xres1(72, 1);
    URational yres1(72, 1);
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres1, yres1, 2);
    
    // Set second time with different values
    URational xres2(300, 1);
    URational yres2(300, 1);
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres2, yres2, 3);
    
    auto itX = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(itX, exifData_.end());
    EXPECT_EQ(itX->toRational(), Rational(300, 1));
    
    auto itUnit = exifData_.findKey(ExifKey("Exif.Thumbnail.ResolutionUnit"));
    ASSERT_NE(itUnit, exifData_.end());
    EXPECT_EQ(itUnit->toInt64(), 3);
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailWithResolution_ZeroResolution_771) {
    ExifThumb thumb(exifData_);
    
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(0, 1);
    URational yres(0, 1);
    uint16_t unit = 1; // no absolute unit
    
    thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit);
    
    auto itX = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(itX, exifData_.end());
    EXPECT_EQ(itX->toRational(), Rational(0, 1));
}

TEST_F(ExifThumbTest_771, SetJpegThumbnailWithLargerBuffer_771) {
    ExifThumb thumb(exifData_);
    
    // Create a larger buffer simulating a real JPEG thumbnail
    std::vector<byte> jpegData(1024, 0);
    jpegData[0] = 0xFF;
    jpegData[1] = 0xD8;
    jpegData[1022] = 0xFF;
    jpegData[1023] = 0xD9;
    
    URational xres(96, 1);
    URational yres(96, 1);
    uint16_t unit = 2;
    
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit));
    
    auto itX = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(itX, exifData_.end());
    EXPECT_EQ(itX->toRational(), Rational(96, 1));
}

// Test ExifData operator[] and basic operations
class ExifDataTest_771 : public ::testing::Test {
protected:
    ExifData exifData_;
};

TEST_F(ExifDataTest_771, OperatorBracket_CreatesEntry_771) {
    exifData_["Exif.Image.Make"] = "TestMake";
    
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestMake");
}

TEST_F(ExifDataTest_771, Empty_InitiallyTrue_771) {
    EXPECT_TRUE(exifData_.empty());
}

TEST_F(ExifDataTest_771, Empty_AfterAdd_771) {
    exifData_["Exif.Image.Make"] = "Test";
    EXPECT_FALSE(exifData_.empty());
}

TEST_F(ExifDataTest_771, Count_AfterMultipleAdds_771) {
    exifData_["Exif.Image.Make"] = "Test";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);
}

TEST_F(ExifDataTest_771, Clear_RemovesAllEntries_771) {
    exifData_["Exif.Image.Make"] = "Test";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

TEST_F(ExifDataTest_771, FindKey_NonExistent_771) {
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, exifData_.end());
}

TEST_F(ExifDataTest_771, Erase_SingleElement_771) {
    exifData_["Exif.Image.Make"] = "Test";
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    exifData_.erase(it);
    EXPECT_TRUE(exifData_.empty());
}

TEST_F(ExifDataTest_771, OperatorBracket_Uint16Assignment_771) {
    exifData_["Exif.Image.Orientation"] = static_cast<uint16_t>(1);
    auto it = exifData_.findKey(ExifKey("Exif.Image.Orientation"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(), 1);
}

TEST_F(ExifDataTest_771, OperatorBracket_URationalAssignment_771) {
    exifData_["Exif.Thumbnail.XResolution"] = URational(72, 1);
    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.XResolution"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toRational(), Rational(72, 1));
}
