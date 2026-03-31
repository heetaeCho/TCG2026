#include <gtest/gtest.h>
#include <exiv2/orfimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

// Helper to create an OrfImage with a MemIo (in-memory I/O)
std::unique_ptr<Exiv2::OrfImage> createOrfImage(bool create = true) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::OrfImage>(std::move(io), create);
}

class OrfImageTest_1549 : public ::testing::Test {
protected:
    void SetUp() override {
        orfImage_ = createOrfImage(true);
    }

    std::unique_ptr<Exiv2::OrfImage> orfImage_;
};

// Test that mimeType returns the expected MIME type for ORF images
TEST_F(OrfImageTest_1549, MimeType_ReturnsCorrectType_1549) {
    std::string mime = orfImage_->mimeType();
    EXPECT_EQ(mime, "image/x-olympus-orf");
}

// Test pixelWidth when no EXIF data is set (should return 0)
TEST_F(OrfImageTest_1549, PixelWidth_NoExifData_ReturnsZero_1549) {
    uint32_t width = orfImage_->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test pixelHeight when no EXIF data is set (should return 0)
TEST_F(OrfImageTest_1549, PixelHeight_NoExifData_ReturnsZero_1549) {
    uint32_t height = orfImage_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test pixelWidth when Exif.Image.ImageWidth is set
TEST_F(OrfImageTest_1549, PixelWidth_WithExifImageWidth_ReturnsValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(4000);
    uint32_t width = orfImage_->pixelWidth();
    EXPECT_EQ(width, 4000u);
}

// Test pixelHeight when Exif.Image.ImageLength is set
TEST_F(OrfImageTest_1549, PixelHeight_WithExifImageLength_ReturnsValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(3000);
    uint32_t height = orfImage_->pixelHeight();
    EXPECT_EQ(height, 3000u);
}

// Test pixelWidth with a value of 0
TEST_F(OrfImageTest_1549, PixelWidth_WithZeroValue_ReturnsZero_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(0);
    uint32_t width = orfImage_->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test pixelHeight with a value of 0
TEST_F(OrfImageTest_1549, PixelHeight_WithZeroValue_ReturnsZero_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(0);
    uint32_t height = orfImage_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test pixelWidth with a large value
TEST_F(OrfImageTest_1549, PixelWidth_LargeValue_ReturnsCorrectValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(65535);
    uint32_t width = orfImage_->pixelWidth();
    EXPECT_EQ(width, 65535u);
}

// Test pixelHeight with a large value
TEST_F(OrfImageTest_1549, PixelHeight_LargeValue_ReturnsCorrectValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(65535);
    uint32_t height = orfImage_->pixelHeight();
    EXPECT_EQ(height, 65535u);
}

// Test setComment does not throw (ORF images may not support comments)
TEST_F(OrfImageTest_1549, SetComment_DoesNotThrow_1549) {
    EXPECT_NO_THROW(orfImage_->setComment("test comment"));
}

// Test that clearing exif data makes pixelWidth return 0
TEST_F(OrfImageTest_1549, PixelWidth_AfterClearExifData_ReturnsZero_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1920);
    EXPECT_EQ(orfImage_->pixelWidth(), 1920u);
    orfImage_->clearExifData();
    EXPECT_EQ(orfImage_->pixelWidth(), 0u);
}

// Test that clearing exif data makes pixelHeight return 0
TEST_F(OrfImageTest_1549, PixelHeight_AfterClearExifData_ReturnsZero_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(1080);
    EXPECT_EQ(orfImage_->pixelHeight(), 1080u);
    orfImage_->clearExifData();
    EXPECT_EQ(orfImage_->pixelHeight(), 0u);
}

// Test pixelWidth and pixelHeight both set simultaneously
TEST_F(OrfImageTest_1549, PixelDimensions_BothSet_ReturnCorrectValues_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(5184);
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(3456);
    EXPECT_EQ(orfImage_->pixelWidth(), 5184u);
    EXPECT_EQ(orfImage_->pixelHeight(), 3456u);
}

// Test pixelWidth with uint16_t value (should still work via conversion)
TEST_F(OrfImageTest_1549, PixelWidth_WithUint16Value_ReturnsValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint16_t>(800);
    uint32_t width = orfImage_->pixelWidth();
    EXPECT_EQ(width, 800u);
}

// Test pixelHeight with uint16_t value (should still work via conversion)
TEST_F(OrfImageTest_1549, PixelHeight_WithUint16Value_ReturnsValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint16_t>(600);
    uint32_t height = orfImage_->pixelHeight();
    EXPECT_EQ(height, 600u);
}

// Test that updating the exif data reflects new pixel dimensions
TEST_F(OrfImageTest_1549, PixelWidth_UpdateValue_ReturnsUpdatedValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1024);
    EXPECT_EQ(orfImage_->pixelWidth(), 1024u);
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(2048);
    EXPECT_EQ(orfImage_->pixelWidth(), 2048u);
}

// Test that updating the exif data reflects new pixel height
TEST_F(OrfImageTest_1549, PixelHeight_UpdateValue_ReturnsUpdatedValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(768);
    EXPECT_EQ(orfImage_->pixelHeight(), 768u);
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(1536);
    EXPECT_EQ(orfImage_->pixelHeight(), 1536u);
}

// Test maximum uint32_t value for dimensions
TEST_F(OrfImageTest_1549, PixelWidth_MaxUint32_ReturnsMaxValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(0xFFFFFFFF);
    uint32_t width = orfImage_->pixelWidth();
    EXPECT_EQ(width, 0xFFFFFFFFu);
}

TEST_F(OrfImageTest_1549, PixelHeight_MaxUint32_ReturnsMaxValue_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(0xFFFFFFFF);
    uint32_t height = orfImage_->pixelHeight();
    EXPECT_EQ(height, 0xFFFFFFFFu);
}

// Test pixelWidth with value of 1 (boundary)
TEST_F(OrfImageTest_1549, PixelWidth_ValueOne_ReturnsOne_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1);
    EXPECT_EQ(orfImage_->pixelWidth(), 1u);
}

// Test pixelHeight with value of 1 (boundary)
TEST_F(OrfImageTest_1549, PixelHeight_ValueOne_ReturnsOne_1549) {
    Exiv2::ExifData& exifData = orfImage_->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(1);
    EXPECT_EQ(orfImage_->pixelHeight(), 1u);
}

}  // namespace
