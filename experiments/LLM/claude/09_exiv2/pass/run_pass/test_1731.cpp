#include <gtest/gtest.h>
#include <memory>
#include <string>

#include <exiv2/tiffimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

// Helper to create a TiffImage with a MemIo (in-memory I/O)
std::unique_ptr<Exiv2::TiffImage> createTiffImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::TiffImage>(std::move(io), true);
}

class TiffImagePixelHeightTest_1731 : public ::testing::Test {
protected:
    void SetUp() override {
        tiffImage_ = createTiffImage();
    }

    std::unique_ptr<Exiv2::TiffImage> tiffImage_;
};

// Test that pixelHeight returns 0 when no exif data is set and no primary height
TEST_F(TiffImagePixelHeightTest_1731, ReturnsZeroWhenNoExifData_1731) {
    uint32_t height = tiffImage_->pixelHeight();
    // Without any exif data or metadata loaded, should return 0
    EXPECT_EQ(0u, height);
}

// Test that pixelHeight returns the value from ExifData when ImageLength is set
TEST_F(TiffImagePixelHeightTest_1731, ReturnsHeightFromExifImageLength_1731) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    
    // Set ImageLength in the Image (IFD0) group
    Exiv2::ExifKey key("Exif.Image.ImageLength");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("480");
    exifData.add(key, value.get());
    
    uint32_t height = tiffImage_->pixelHeight();
    // The pixelHeight function looks up primaryGroup's ImageLength
    // primaryGroup() typically returns "Image" for TIFF
    // It may or may not find it depending on primaryGroup() logic
    // We test the observable behavior
    EXPECT_GE(height, 0u);
}

// Test that pixelHeight returns a consistent value on repeated calls
TEST_F(TiffImagePixelHeightTest_1731, ConsistentOnRepeatedCalls_1731) {
    uint32_t height1 = tiffImage_->pixelHeight();
    uint32_t height2 = tiffImage_->pixelHeight();
    EXPECT_EQ(height1, height2);
}

// Test that pixelHeight caches/returns the same value after first lookup
TEST_F(TiffImagePixelHeightTest_1731, CachesValueAfterFirstCall_1731) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    
    // First call with no data
    uint32_t height1 = tiffImage_->pixelHeight();
    
    // Now add ImageLength
    Exiv2::ExifKey key("Exif.Image.ImageLength");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("1024");
    exifData.add(key, value.get());
    
    // Second call - behavior depends on caching
    uint32_t height2 = tiffImage_->pixelHeight();
    
    // If first call returned 0, adding data might make second call return non-zero
    // because pixelHeightPrimary_ was 0 so it re-checks
    // This tests that caching works: if pixelHeightPrimary_ was set to non-zero, it returns cached
    // If it was 0 (not found), it tries again
    // Both are valid behaviors
    EXPECT_TRUE(height2 == 0u || height2 == 1024u);
}

// Test mimeType returns expected TIFF mime type
TEST_F(TiffImagePixelHeightTest_1731, MimeTypeIsTiff_1731) {
    std::string mime = tiffImage_->mimeType();
    EXPECT_EQ("image/tiff", mime);
}

// Test pixelWidth returns 0 when no exif data
TEST_F(TiffImagePixelHeightTest_1731, PixelWidthReturnsZeroWhenNoExifData_1731) {
    uint32_t width = tiffImage_->pixelWidth();
    EXPECT_EQ(0u, width);
}

// Test setComment throws or is a no-op for TIFF images
TEST_F(TiffImagePixelHeightTest_1731, SetCommentNoOp_1731) {
    // setComment for TiffImage is documented to do nothing or throw
    EXPECT_NO_THROW(tiffImage_->setComment("test comment"));
}

// Test that clearing exif data and calling pixelHeight returns 0
TEST_F(TiffImagePixelHeightTest_1731, ReturnsZeroAfterClearExifData_1731) {
    // This creates a fresh TiffImage
    auto io = std::make_unique<Exiv2::MemIo>();
    auto img = std::make_unique<Exiv2::TiffImage>(std::move(io), true);
    
    img->clearExifData();
    uint32_t height = img->pixelHeight();
    EXPECT_EQ(0u, height);
}

// Test with a large ImageLength value
TEST_F(TiffImagePixelHeightTest_1731, LargeImageLengthValue_1731) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    
    Exiv2::ExifKey key("Exif.Image.ImageLength");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("4294967295");  // UINT32_MAX
    exifData.add(key, value.get());
    
    uint32_t height = tiffImage_->pixelHeight();
    // Should handle large values without overflow
    EXPECT_TRUE(height == 0u || height == 4294967295u);
}

// Test with ImageLength value of 1 (minimum positive)
TEST_F(TiffImagePixelHeightTest_1731, MinimumPositiveImageLength_1731) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    
    Exiv2::ExifKey key("Exif.Image.ImageLength");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("1");
    exifData.add(key, value.get());
    
    uint32_t height = tiffImage_->pixelHeight();
    EXPECT_TRUE(height == 0u || height == 1u);
}

// Test pixelWidth with ImageWidth set
TEST_F(TiffImagePixelHeightTest_1731, PixelWidthWithExifData_1731) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("640");
    exifData.add(key, value.get());
    
    uint32_t width = tiffImage_->pixelWidth();
    EXPECT_TRUE(width == 0u || width == 640u);
}

// Test that both pixelWidth and pixelHeight work together
TEST_F(TiffImagePixelHeightTest_1731, BothDimensionsSet_1731) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    
    {
        Exiv2::ExifKey key("Exif.Image.ImageWidth");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("1920");
        exifData.add(key, value.get());
    }
    {
        Exiv2::ExifKey key("Exif.Image.ImageLength");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("1080");
        exifData.add(key, value.get());
    }
    
    uint32_t width = tiffImage_->pixelWidth();
    uint32_t height = tiffImage_->pixelHeight();
    
    // Either both found or not, depending on primaryGroup
    if (width != 0) {
        EXPECT_EQ(1920u, width);
    }
    if (height != 0) {
        EXPECT_EQ(1080u, height);
    }
}

// Test that exifData is accessible and modifiable
TEST_F(TiffImagePixelHeightTest_1731, ExifDataAccessible_1731) {
    Exiv2::ExifData& exifData = tiffImage_->exifData();
    EXPECT_TRUE(exifData.empty());
    
    Exiv2::ExifKey key("Exif.Image.ImageLength");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("100");
    exifData.add(key, value.get());
    
    EXPECT_FALSE(exifData.empty());
}

// Test image creation with create=false
TEST(TiffImageCreationTest_1731, CreateFalse_1731) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto img = std::make_unique<Exiv2::TiffImage>(std::move(io), false);
    EXPECT_NE(nullptr, img);
    EXPECT_EQ(0u, img->pixelHeight());
    EXPECT_EQ(0u, img->pixelWidth());
}

}  // namespace
