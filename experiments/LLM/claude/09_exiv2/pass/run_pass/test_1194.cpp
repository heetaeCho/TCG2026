#include <gtest/gtest.h>
#include <exiv2/bmffimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

// Helper to create a BmffImage with a MemIo (in-memory I/O)
std::unique_ptr<Exiv2::BmffImage> createBmffImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::BmffImage>(std::move(io), true, 1000);
}

class BmffImagePixelWidthTest_1194 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::BmffImage> image;

    void SetUp() override {
        image = createBmffImage();
    }
};

// Test that pixelWidth returns 0 (default pixelWidth_) when no EXIF data is set
TEST_F(BmffImagePixelWidthTest_1194, ReturnsDefaultWhenNoExifData_1194) {
    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test that pixelWidth returns the EXIF PixelXDimension when it is set
TEST_F(BmffImagePixelWidthTest_1194, ReturnsExifPixelXDimensionWhenSet_1194) {
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);

    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 1920u);
}

// Test that pixelWidth returns EXIF value even if it differs from the internal pixelWidth_
TEST_F(BmffImagePixelWidthTest_1194, ExifValueOverridesInternalWidth_1194) {
    // The internal pixelWidth_ defaults to 0 (from Image base class)
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(3840);

    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 3840u);
}

// Test pixelWidth with a small value
TEST_F(BmffImagePixelWidthTest_1194, ReturnsSmallExifValue_1194) {
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1);

    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 1u);
}

// Test pixelWidth with maximum uint32_t value
TEST_F(BmffImagePixelWidthTest_1194, ReturnsMaxUint32ExifValue_1194) {
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0xFFFFFFFF);

    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 0xFFFFFFFFu);
}

// Test that clearing EXIF data causes pixelWidth to return default
TEST_F(BmffImagePixelWidthTest_1194, ReturnsDefaultAfterClearingExifData_1194) {
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);

    EXPECT_EQ(image->pixelWidth(), 1920u);

    image->clearExifData();

    // After clearing, should return default pixelWidth_ (0)
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test that pixelWidth returns EXIF value of 0 when EXIF is explicitly set to 0
TEST_F(BmffImagePixelWidthTest_1194, ReturnsZeroWhenExifSetToZero_1194) {
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0);

    uint32_t width = image->pixelWidth();
    // The EXIF key exists and count > 0, so toUint32() is called which returns 0
    EXPECT_EQ(width, 0u);
}

// Test pixelHeight similarly - returns default when no EXIF data
TEST_F(BmffImagePixelWidthTest_1194, PixelHeightReturnsDefaultWhenNoExifData_1194) {
    uint32_t height = image->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test that other EXIF keys don't affect pixelWidth
TEST_F(BmffImagePixelWidthTest_1194, OtherExifKeysDoNotAffectPixelWidth_1194) {
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1080);

    // PixelXDimension not set, so should return default
    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test that setting PixelXDimension multiple times returns the last value
TEST_F(BmffImagePixelWidthTest_1194, ReturnsLastSetExifValue_1194) {
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(800);
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1600);

    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 1600u);
}

// Test mimeType returns a non-empty string
TEST_F(BmffImagePixelWidthTest_1194, MimeTypeReturnsNonEmpty_1194) {
    std::string mime = image->mimeType();
    EXPECT_FALSE(mime.empty());
}

// Test that setComment doesn't throw (it's overridden in BmffImage)
TEST_F(BmffImagePixelWidthTest_1194, SetCommentDoesNotThrow_1194) {
    EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test that setExifData doesn't throw (overridden, likely no-op or throws)
TEST_F(BmffImagePixelWidthTest_1194, SetExifDataDoesNotCrash_1194) {
    Exiv2::ExifData exifData;
    // BmffImage::setExifData may throw or be a no-op; we just verify no crash
    try {
        image->setExifData(exifData);
    } catch (...) {
        // Expected - BmffImage may not support setting EXIF data
    }
}

}  // namespace
