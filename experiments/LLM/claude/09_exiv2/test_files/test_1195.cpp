#include <gtest/gtest.h>
#include <exiv2/bmffimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

// Helper to create a BmffImage with a MemIo (empty, not a valid BMFF file)
std::unique_ptr<Exiv2::BmffImage> createBmffImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
}

class BmffImagePixelHeightTest_1195 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::BmffImage> image_;

    void SetUp() override {
        image_ = createBmffImage();
    }
};

// Test that pixelHeight returns 0 (default pixelHeight_) when no EXIF data is present
TEST_F(BmffImagePixelHeightTest_1195, ReturnsDefaultWhenNoExifData_1195) {
    uint32_t height = image_->pixelHeight();
    // Default pixelHeight_ is 0 (from Image base class initialization)
    EXPECT_EQ(0u, height);
}

// Test that pixelHeight returns the EXIF value when Exif.Photo.PixelYDimension is set
TEST_F(BmffImagePixelHeightTest_1195, ReturnsExifValueWhenSet_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(1080);

    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(1080u, height);
}

// Test that pixelHeight returns EXIF value even when it's a small value (1)
TEST_F(BmffImagePixelHeightTest_1195, ReturnsExifValueSmall_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(1);

    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(1u, height);
}

// Test that pixelHeight returns EXIF value for a large value
TEST_F(BmffImagePixelHeightTest_1195, ReturnsExifValueLarge_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(4320);

    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(4320u, height);
}

// Test that pixelHeight returns EXIF value for max uint32
TEST_F(BmffImagePixelHeightTest_1195, ReturnsExifValueMaxUint32_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(0xFFFFFFFF);

    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(0xFFFFFFFFu, height);
}

// Test that pixelHeight returns EXIF value of zero when EXIF is set to 0
TEST_F(BmffImagePixelHeightTest_1195, ReturnsExifValueZero_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(0);

    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(0u, height);
}

// Test pixelWidth similarly to confirm BmffImage overrides work
class BmffImagePixelWidthTest_1195 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::BmffImage> image_;

    void SetUp() override {
        image_ = createBmffImage();
    }
};

// Test that pixelWidth returns 0 (default) when no EXIF data is present
TEST_F(BmffImagePixelWidthTest_1195, ReturnsDefaultWhenNoExifData_1195) {
    uint32_t width = image_->pixelWidth();
    EXPECT_EQ(0u, width);
}

// Test BmffImage construction and basic properties
class BmffImageBasicTest_1195 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::BmffImage> image_;

    void SetUp() override {
        image_ = createBmffImage();
    }
};

// Test that mimeType returns a valid string
TEST_F(BmffImageBasicTest_1195, MimeTypeNotEmpty_1195) {
    std::string mime = image_->mimeType();
    // BmffImage should return some mime type string
    EXPECT_FALSE(mime.empty());
}

// Test that imageType is bmff
TEST_F(BmffImageBasicTest_1195, ImageTypeIsBmff_1195) {
    EXPECT_EQ(Exiv2::ImageType::bmff, image_->imageType());
}

// Test that exifData is initially empty
TEST_F(BmffImageBasicTest_1195, ExifDataInitiallyEmpty_1195) {
    EXPECT_TRUE(image_->exifData().empty());
}

// Test setComment (should not throw, as it's overridden but may be no-op for BMFF)
TEST_F(BmffImageBasicTest_1195, SetCommentDoesNotThrow_1195) {
    EXPECT_NO_THROW(image_->setComment("test comment"));
}

// Test setExifData (overridden in BmffImage)
TEST_F(BmffImageBasicTest_1195, SetExifDataDoesNotThrow_1195) {
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(image_->setExifData(exifData));
}

// Test setIptcData (overridden in BmffImage)
TEST_F(BmffImageBasicTest_1195, SetIptcDataDoesNotThrow_1195) {
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image_->setIptcData(iptcData));
}

// Test setXmpData (overridden in BmffImage)
TEST_F(BmffImageBasicTest_1195, SetXmpDataDoesNotThrow_1195) {
    Exiv2::XmpData xmpData;
    EXPECT_NO_THROW(image_->setXmpData(xmpData));
}

// Test that after setting and clearing EXIF data, pixelHeight returns default
TEST_F(BmffImageBasicTest_1195, PixelHeightAfterClearExifData_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(720);
    EXPECT_EQ(720u, image_->pixelHeight());

    image_->clearExifData();
    EXPECT_EQ(0u, image_->pixelHeight());
}

// Test that pixelHeight with uint16_t EXIF value also works
TEST_F(BmffImagePixelHeightTest_1195, ReturnsExifValueFromUint16_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint16_t>(480);

    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(480u, height);
}

// Test that multiple updates to EXIF PixelYDimension are reflected
TEST_F(BmffImagePixelHeightTest_1195, ReflectsUpdatedExifValue_1195) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(1080);
    EXPECT_EQ(1080u, image_->pixelHeight());

    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(2160);
    EXPECT_EQ(2160u, image_->pixelHeight());
}

}  // namespace
