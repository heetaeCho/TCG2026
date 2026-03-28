#include <gtest/gtest.h>
#include <exiv2/rw2image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

// Helper to create an Rw2Image with a MemIo (in-memory I/O)
std::unique_ptr<Exiv2::Rw2Image> createRw2Image() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::Rw2Image>(std::move(io));
}

class Rw2ImageTest_1577 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createRw2Image();
    }

    std::unique_ptr<Exiv2::Rw2Image> image_;
};

// Test that mimeType returns the expected MIME type for RW2
TEST_F(Rw2ImageTest_1577, MimeType_ReturnsCorrectType_1577) {
    std::string mime = image_->mimeType();
    EXPECT_EQ(mime, "image/x-panasonic-rw2");
}

// Test pixelWidth returns 0 when no EXIF data is set
TEST_F(Rw2ImageTest_1577, PixelWidth_NoExifData_ReturnsZero_1577) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

// Test pixelHeight returns 0 when no EXIF data is set
TEST_F(Rw2ImageTest_1577, PixelHeight_NoExifData_ReturnsZero_1577) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test pixelWidth when SensorWidth key is present in exifData
TEST_F(Rw2ImageTest_1577, PixelWidth_WithSensorWidth_ReturnsValue_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint16_t>(4000);
    EXPECT_EQ(image_->pixelWidth(), 4000u);
}

// Test pixelHeight when SensorHeight key is present in exifData
TEST_F(Rw2ImageTest_1577, PixelHeight_WithSensorHeight_ReturnsValue_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = static_cast<uint16_t>(3000);
    EXPECT_EQ(image_->pixelHeight(), 3000u);
}

// Test pixelWidth with a specific uint32 value
TEST_F(Rw2ImageTest_1577, PixelWidth_WithUint32Value_ReturnsValue_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint32_t>(5472);
    EXPECT_EQ(image_->pixelWidth(), 5472u);
}

// Test pixelHeight with a specific uint32 value
TEST_F(Rw2ImageTest_1577, PixelHeight_WithUint32Value_ReturnsValue_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = static_cast<uint32_t>(3648);
    EXPECT_EQ(image_->pixelHeight(), 3648u);
}

// Test that pixelWidth returns 0 when the key exists but has wrong key name
TEST_F(Rw2ImageTest_1577, PixelWidth_WrongKeyName_ReturnsZero_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelXDimension"] = static_cast<uint32_t>(1920);
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

// Test that pixelHeight returns 0 when the key exists but has wrong key name
TEST_F(Rw2ImageTest_1577, PixelHeight_WrongKeyName_ReturnsZero_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(1080);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test setExifData does not throw (RW2 images typically reject setExifData)
TEST_F(Rw2ImageTest_1577, SetExifData_DoesNotThrow_1577) {
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(image_->setExifData(exifData));
}

// Test setIptcData does not throw (RW2 images typically reject setIptcData)
TEST_F(Rw2ImageTest_1577, SetIptcData_DoesNotThrow_1577) {
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image_->setIptcData(iptcData));
}

// Test setComment does not throw
TEST_F(Rw2ImageTest_1577, SetComment_DoesNotThrow_1577) {
    EXPECT_NO_THROW(image_->setComment("test comment"));
}

// Test writeMetadata throws since RW2 writing is not supported
TEST_F(Rw2ImageTest_1577, WriteMetadata_ThrowsError_1577) {
    EXPECT_THROW(image_->writeMetadata(), Exiv2::Error);
}

// Test that pixelWidth with value of 0 set explicitly returns 0
TEST_F(Rw2ImageTest_1577, PixelWidth_ZeroValue_ReturnsZero_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint16_t>(0);
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

// Test that pixelHeight with value of 0 set explicitly returns 0
TEST_F(Rw2ImageTest_1577, PixelHeight_ZeroValue_ReturnsZero_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = static_cast<uint16_t>(0);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test pixelWidth with value 1 (boundary)
TEST_F(Rw2ImageTest_1577, PixelWidth_ValueOne_ReturnsOne_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint16_t>(1);
    EXPECT_EQ(image_->pixelWidth(), 1u);
}

// Test pixelHeight with value 1 (boundary)
TEST_F(Rw2ImageTest_1577, PixelHeight_ValueOne_ReturnsOne_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = static_cast<uint16_t>(1);
    EXPECT_EQ(image_->pixelHeight(), 1u);
}

// Test pixelWidth with large value
TEST_F(Rw2ImageTest_1577, PixelWidth_LargeValue_ReturnsCorrectly_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint32_t>(65535);
    EXPECT_EQ(image_->pixelWidth(), 65535u);
}

// Test pixelHeight with large value
TEST_F(Rw2ImageTest_1577, PixelHeight_LargeValue_ReturnsCorrectly_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = static_cast<uint32_t>(65535);
    EXPECT_EQ(image_->pixelHeight(), 65535u);
}

// Test that both pixelWidth and pixelHeight can be set simultaneously
TEST_F(Rw2ImageTest_1577, PixelDimensions_BothSet_ReturnCorrectValues_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint16_t>(4000);
    exifData["Exif.PanasonicRaw.SensorHeight"] = static_cast<uint16_t>(3000);
    EXPECT_EQ(image_->pixelWidth(), 4000u);
    EXPECT_EQ(image_->pixelHeight(), 3000u);
}

// Test that clearing exif data resets pixel dimensions to 0
TEST_F(Rw2ImageTest_1577, ClearExifData_ResetsPixelDimensions_1577) {
    Exiv2::ExifData& exifData = image_->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint16_t>(4000);
    exifData["Exif.PanasonicRaw.SensorHeight"] = static_cast<uint16_t>(3000);
    image_->clearExifData();
    EXPECT_EQ(image_->pixelWidth(), 0u);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test good() on a fresh image with MemIo
TEST_F(Rw2ImageTest_1577, Good_FreshImage_1577) {
    // MemIo with no data should still be valid in terms of I/O state
    // This tests the observable behavior of good()
    bool result = image_->good();
    // Just verify it doesn't crash; the exact value depends on BasicIo state
    (void)result;
}

// Test printStructure doesn't crash with default options
TEST_F(Rw2ImageTest_1577, PrintStructure_DoesNotCrash_1577) {
    std::ostringstream oss;
    // kpsNone should be safe
    EXPECT_NO_THROW(image_->printStructure(oss, Exiv2::kpsNone, 0));
}

}  // namespace
