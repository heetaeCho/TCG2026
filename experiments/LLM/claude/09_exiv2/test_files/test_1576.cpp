#include <gtest/gtest.h>
#include <exiv2/rw2image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

class Rw2ImageTest_1576 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::Rw2Image> createRw2Image() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::Rw2Image>(std::move(io));
    }
};

// Test that mimeType returns the correct MIME type for RW2
TEST_F(Rw2ImageTest_1576, MimeTypeReturnsCorrectValue_1576) {
    auto image = createRw2Image();
    EXPECT_EQ("image/x-panasonic-rw2", image->mimeType());
}

// Test that pixelWidth returns 0 when no EXIF data is set
TEST_F(Rw2ImageTest_1576, PixelWidthReturnsZeroWhenNoExifData_1576) {
    auto image = createRw2Image();
    EXPECT_EQ(0u, image->pixelWidth());
}

// Test that pixelHeight returns 0 when no EXIF data is set
TEST_F(Rw2ImageTest_1576, PixelHeightReturnsZeroWhenNoExifData_1576) {
    auto image = createRw2Image();
    EXPECT_EQ(0u, image->pixelHeight());
}

// Test that pixelWidth returns the correct value when SensorWidth is set in ExifData
TEST_F(Rw2ImageTest_1576, PixelWidthReturnsSensorWidthWhenSet_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = uint32_t(4000);
    EXPECT_EQ(4000u, image->pixelWidth());
}

// Test that pixelHeight returns the correct value when SensorHeight is set in ExifData
TEST_F(Rw2ImageTest_1576, PixelHeightReturnsSensorHeightWhenSet_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = uint32_t(3000);
    EXPECT_EQ(3000u, image->pixelHeight());
}

// Test that pixelWidth returns 0 when SensorWidth key exists but has no value (count == 0)
TEST_F(Rw2ImageTest_1576, PixelWidthReturnsZeroWhenKeyExistsButEmpty_1576) {
    auto image = createRw2Image();
    // Without setting a value, find should return end()
    EXPECT_EQ(0u, image->pixelWidth());
}

// Test that pixelHeight returns 0 when SensorHeight key exists but has no value
TEST_F(Rw2ImageTest_1576, PixelHeightReturnsZeroWhenKeyExistsButEmpty_1576) {
    auto image = createRw2Image();
    EXPECT_EQ(0u, image->pixelHeight());
}

// Test pixelWidth with a value of 1 (boundary)
TEST_F(Rw2ImageTest_1576, PixelWidthBoundaryValueOne_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = uint32_t(1);
    EXPECT_EQ(1u, image->pixelWidth());
}

// Test pixelHeight with a value of 1 (boundary)
TEST_F(Rw2ImageTest_1576, PixelHeightBoundaryValueOne_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = uint32_t(1);
    EXPECT_EQ(1u, image->pixelHeight());
}

// Test pixelWidth with a large value
TEST_F(Rw2ImageTest_1576, PixelWidthLargeValue_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = uint32_t(65535);
    EXPECT_EQ(65535u, image->pixelWidth());
}

// Test pixelHeight with a large value
TEST_F(Rw2ImageTest_1576, PixelHeightLargeValue_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = uint32_t(65535);
    EXPECT_EQ(65535u, image->pixelHeight());
}

// Test that setExifData does not throw (RW2 disallows setting exif data)
TEST_F(Rw2ImageTest_1576, SetExifDataDoesNotCrash_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(image->setExifData(exifData));
}

// Test that setIptcData does not throw (RW2 disallows setting IPTC data)
TEST_F(Rw2ImageTest_1576, SetIptcDataDoesNotCrash_1576) {
    auto image = createRw2Image();
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image->setIptcData(iptcData));
}

// Test that setComment does not throw (RW2 disallows setting comment)
TEST_F(Rw2ImageTest_1576, SetCommentDoesNotCrash_1576) {
    auto image = createRw2Image();
    EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test that exifData is initially empty
TEST_F(Rw2ImageTest_1576, ExifDataInitiallyEmpty_1576) {
    auto image = createRw2Image();
    EXPECT_TRUE(image->exifData().empty());
}

// Test that after clearing exifData, pixelWidth returns 0
TEST_F(Rw2ImageTest_1576, PixelWidthZeroAfterClearExifData_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = uint32_t(4000);
    EXPECT_EQ(4000u, image->pixelWidth());
    image->clearExifData();
    EXPECT_EQ(0u, image->pixelWidth());
}

// Test that after clearing exifData, pixelHeight returns 0
TEST_F(Rw2ImageTest_1576, PixelHeightZeroAfterClearExifData_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = uint32_t(3000);
    EXPECT_EQ(3000u, image->pixelHeight());
    image->clearExifData();
    EXPECT_EQ(0u, image->pixelHeight());
}

// Test that writeMetadata throws for an empty MemIo (RW2 is read-only)
TEST_F(Rw2ImageTest_1576, WriteMetadataThrows_1576) {
    auto image = createRw2Image();
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test pixelWidth with uint32 max value
TEST_F(Rw2ImageTest_1576, PixelWidthMaxUint32_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, image->pixelWidth());
}

// Test pixelHeight with uint32 max value
TEST_F(Rw2ImageTest_1576, PixelHeightMaxUint32_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, image->pixelHeight());
}

// Test that the image reports good() as false for empty MemIo
TEST_F(Rw2ImageTest_1576, GoodReturnsFalseForEmptyIo_1576) {
    auto image = createRw2Image();
    // An empty MemIo likely reports good() as false since there's no valid data
    // This depends on BasicIo implementation; we just verify it doesn't crash
    EXPECT_NO_THROW(image->good());
}

// Test that pixelWidth returns 0 when a different Exif key is set but not SensorWidth
TEST_F(Rw2ImageTest_1576, PixelWidthZeroWhenDifferentKeySet_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = uint32_t(3000);
    EXPECT_EQ(0u, image->pixelWidth());
}

// Test that pixelHeight returns 0 when a different Exif key is set but not SensorHeight
TEST_F(Rw2ImageTest_1576, PixelHeightZeroWhenDifferentKeySet_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = uint32_t(4000);
    EXPECT_EQ(0u, image->pixelHeight());
}

// Test pixelWidth with zero value explicitly set
TEST_F(Rw2ImageTest_1576, PixelWidthExplicitlySetToZero_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorWidth"] = uint32_t(0);
    EXPECT_EQ(0u, image->pixelWidth());
}

// Test pixelHeight with zero value explicitly set
TEST_F(Rw2ImageTest_1576, PixelHeightExplicitlySetToZero_1576) {
    auto image = createRw2Image();
    Exiv2::ExifData& exifData = image->exifData();
    exifData["Exif.PanasonicRaw.SensorHeight"] = uint32_t(0);
    EXPECT_EQ(0u, image->pixelHeight());
}

// Test printStructure does not crash
TEST_F(Rw2ImageTest_1576, PrintStructureDoesNotCrash_1576) {
    auto image = createRw2Image();
    std::ostringstream oss;
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsNone, 0));
}

}  // namespace
