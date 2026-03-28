#include <gtest/gtest.h>
#include <memory>
#include <string>

#include <exiv2/tiffimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

namespace {

// Helper to create a TiffImage with a MemIo
std::unique_ptr<Exiv2::TiffImage> createTiffImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::TiffImage>(std::move(io), true);
}

class TiffImagePixelWidthTest_1730 : public ::testing::Test {
protected:
    void SetUp() override {
        tiffImage_ = createTiffImage();
    }

    std::unique_ptr<Exiv2::TiffImage> tiffImage_;
};

// Test that pixelWidth returns 0 when no exif data is set and no primary width cached
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthReturnsZeroWhenNoData_1730) {
    // No exif data set, so pixelWidth should return 0
    uint32_t width = tiffImage_->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test that pixelWidth returns the correct value when ImageWidth is set in exif data
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthReturnsValueFromExifData_1730) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    // Set ImageWidth in the Image group (common primary group for TIFF)
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1920);

    uint32_t width = tiffImage_->pixelWidth();
    EXPECT_EQ(width, 1920u);
}

// Test that pixelWidth caches the value and returns it on subsequent calls
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthCachesValue_1730) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(3840);

    uint32_t width1 = tiffImage_->pixelWidth();
    EXPECT_EQ(width1, 3840u);

    // Even if we clear exif data, cached value should persist
    exifData.clear();
    uint32_t width2 = tiffImage_->pixelWidth();
    EXPECT_EQ(width2, 3840u);
}

// Test that pixelHeight returns 0 when no exif data is set
TEST_F(TiffImagePixelWidthTest_1730, PixelHeightReturnsZeroWhenNoData_1730) {
    uint32_t height = tiffImage_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test that pixelHeight returns the correct value when ImageLength is set
TEST_F(TiffImagePixelWidthTest_1730, PixelHeightReturnsValueFromExifData_1730) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(1080);

    uint32_t height = tiffImage_->pixelHeight();
    EXPECT_EQ(height, 1080u);
}

// Test that mimeType returns the expected TIFF MIME type
TEST_F(TiffImagePixelWidthTest_1730, MimeTypeReturnsTiffMimeType_1730) {
    std::string mime = tiffImage_->mimeType();
    EXPECT_EQ(mime, "image/tiff");
}

// Test setComment throws or is a no-op for TIFF images
TEST_F(TiffImagePixelWidthTest_1730, SetCommentIsHandled_1730) {
    // According to the implementation, setComment for TIFF throws
    EXPECT_THROW(tiffImage_->setComment("test comment"), Exiv2::Error);
}

// Test pixelWidth with a width value of 1 (boundary)
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthBoundaryValueOne_1730) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1);

    uint32_t width = tiffImage_->pixelWidth();
    EXPECT_EQ(width, 1u);
}

// Test pixelWidth with maximum uint32 value
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthMaxValue_1730) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(0xFFFFFFFF);

    uint32_t width = tiffImage_->pixelWidth();
    EXPECT_EQ(width, 0xFFFFFFFFu);
}

// Test both pixelWidth and pixelHeight together
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthAndHeightTogether_1730) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(640);
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(480);

    EXPECT_EQ(tiffImage_->pixelWidth(), 640u);
    EXPECT_EQ(tiffImage_->pixelHeight(), 480u);
}

// Test that pixelWidth returns 0 when ImageWidth key exists but count is 0
// This tests the condition where the key is found but has no value
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthZeroWhenKeyExistsButEmpty_1730) {
    // Adding a key with no value - using add with nullptr
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    exifData.add(key, nullptr);

    uint32_t width = tiffImage_->pixelWidth();
    // If count() is 0, the width should remain 0
    EXPECT_EQ(width, 0u);
}

// Test pixelWidth consistency - calling multiple times returns same value
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthConsistentMultipleCalls_1730) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(2560);

    uint32_t w1 = tiffImage_->pixelWidth();
    uint32_t w2 = tiffImage_->pixelWidth();
    uint32_t w3 = tiffImage_->pixelWidth();

    EXPECT_EQ(w1, 2560u);
    EXPECT_EQ(w2, 2560u);
    EXPECT_EQ(w3, 2560u);
}

// Test that the base class pixelWidth_ does not interfere
TEST_F(TiffImagePixelWidthTest_1730, PixelWidthUsesOverride_1730) {
    // The TiffImage overrides pixelWidth, so it should use its own logic
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(800);

    // Cast to Image* and call pixelWidth - should still use TiffImage's override
    Exiv2::Image* img = tiffImage_.get();
    EXPECT_EQ(img->pixelWidth(), 800u);
}

}  // namespace
