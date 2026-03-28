#include <gtest/gtest.h>
#include <exiv2/rafimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <memory>

namespace {

// Helper to create a RafImage with a MemIo (in-memory IO)
std::unique_ptr<Exiv2::RafImage> createRafImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::RafImage>(std::move(io), true);
}

class RafImagePixelHeightTest_219 : public ::testing::Test {
protected:
    void SetUp() override {
        rafImage_ = createRafImage();
    }

    std::unique_ptr<Exiv2::RafImage> rafImage_;
};

// Test that pixelHeight returns 0 when no pixelHeight_ is set and no EXIF data exists
TEST_F(RafImagePixelHeightTest_219, ReturnsZeroWhenNoHeightSetAndNoExifData_219) {
    uint32_t height = rafImage_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test that pixelHeight returns the EXIF value when Exif.Fujifilm.RawImageFullHeight is set
TEST_F(RafImagePixelHeightTest_219, ReturnsExifHeightWhenKeyExists_219) {
    Exiv2::ExifData& exifData = rafImage_->exifData();
    exifData["Exif.Fujifilm.RawImageFullHeight"] = static_cast<uint32_t>(4000);
    
    uint32_t height = rafImage_->pixelHeight();
    EXPECT_EQ(height, 4000u);
}

// Test that pixelHeight returns 0 when the EXIF key exists but has count 0
// This tests the count() == 0 branch
TEST_F(RafImagePixelHeightTest_219, ReturnsZeroWhenExifKeyHasZeroCount_219) {
    // Without setting a value for the key, or after clearing it,
    // we rely on the key not existing or having no value.
    // If we add a key with no value, count should be 0.
    Exiv2::ExifData& exifData = rafImage_->exifData();
    Exiv2::ExifKey key("Exif.Fujifilm.RawImageFullHeight");
    exifData.add(key, nullptr);
    
    uint32_t height = rafImage_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test that pixelHeight returns the correct value for a small height
TEST_F(RafImagePixelHeightTest_219, ReturnsSmallHeight_219) {
    Exiv2::ExifData& exifData = rafImage_->exifData();
    exifData["Exif.Fujifilm.RawImageFullHeight"] = static_cast<uint32_t>(1);
    
    uint32_t height = rafImage_->pixelHeight();
    EXPECT_EQ(height, 1u);
}

// Test that pixelHeight returns a large value
TEST_F(RafImagePixelHeightTest_219, ReturnsLargeHeight_219) {
    Exiv2::ExifData& exifData = rafImage_->exifData();
    exifData["Exif.Fujifilm.RawImageFullHeight"] = static_cast<uint32_t>(65535);
    
    uint32_t height = rafImage_->pixelHeight();
    EXPECT_EQ(height, 65535u);
}

// Test that pixelHeight returns 0 when exifData has other keys but not RawImageFullHeight
TEST_F(RafImagePixelHeightTest_219, ReturnsZeroWhenDifferentExifKeysExist_219) {
    Exiv2::ExifData& exifData = rafImage_->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = static_cast<uint32_t>(6000);
    
    uint32_t height = rafImage_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test mimeType returns the correct MIME type for RAF
TEST_F(RafImagePixelHeightTest_219, MimeTypeIsCorrect_219) {
    std::string mime = rafImage_->mimeType();
    EXPECT_EQ(mime, "image/x-fuji-raf");
}

// Test pixelWidth behavior similar to pixelHeight
class RafImagePixelWidthTest_219 : public ::testing::Test {
protected:
    void SetUp() override {
        rafImage_ = createRafImage();
    }

    std::unique_ptr<Exiv2::RafImage> rafImage_;
};

TEST_F(RafImagePixelWidthTest_219, ReturnsZeroWhenNoWidthSetAndNoExifData_219) {
    uint32_t width = rafImage_->pixelWidth();
    EXPECT_EQ(width, 0u);
}

TEST_F(RafImagePixelWidthTest_219, ReturnsExifWidthWhenKeyExists_219) {
    Exiv2::ExifData& exifData = rafImage_->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = static_cast<uint32_t>(6000);
    
    uint32_t width = rafImage_->pixelWidth();
    EXPECT_EQ(width, 6000u);
}

// Test setComment does not throw (it's documented as a no-op for RAF)
TEST_F(RafImagePixelHeightTest_219, SetCommentDoesNotThrow_219) {
    EXPECT_NO_THROW(rafImage_->setComment("test comment"));
}

// Test setExifData does not throw (documented behavior for RAF)
TEST_F(RafImagePixelHeightTest_219, SetExifDataDoesNotThrow_219) {
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(rafImage_->setExifData(exifData));
}

// Test setIptcData does not throw (documented behavior for RAF)
TEST_F(RafImagePixelHeightTest_219, SetIptcDataDoesNotThrow_219) {
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(rafImage_->setIptcData(iptcData));
}

// Test pixelHeight with max uint32 value
TEST_F(RafImagePixelHeightTest_219, ReturnsMaxUint32Height_219) {
    Exiv2::ExifData& exifData = rafImage_->exifData();
    exifData["Exif.Fujifilm.RawImageFullHeight"] = static_cast<uint32_t>(0xFFFFFFFF);
    
    uint32_t height = rafImage_->pixelHeight();
    EXPECT_EQ(height, 0xFFFFFFFF);
}

// Test that clearing exif data after setting it results in pixelHeight returning 0
TEST_F(RafImagePixelHeightTest_219, ReturnsZeroAfterClearingExifData_219) {
    Exiv2::ExifData& exifData = rafImage_->exifData();
    exifData["Exif.Fujifilm.RawImageFullHeight"] = static_cast<uint32_t>(4000);
    
    // Verify it's set
    EXPECT_EQ(rafImage_->pixelHeight(), 4000u);
    
    // Clear
    exifData.clear();
    
    EXPECT_EQ(rafImage_->pixelHeight(), 0u);
}

}  // namespace
