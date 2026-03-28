#include <gtest/gtest.h>
#include <exiv2/mrwimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

class MrwImageTest_979 : public ::testing::Test {
protected:
    std::unique_ptr<MrwImage> createMrwImage() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<MrwImage>(std::move(io), true);
    }
};

// Test that mimeType returns the correct MIME type for MRW images
TEST_F(MrwImageTest_979, MimeType_ReturnsMrwMimeType_979) {
    auto image = createMrwImage();
    std::string mime = image->mimeType();
    EXPECT_EQ(mime, "image/x-minolta-mrw");
}

// Test pixelWidth returns 0 when no EXIF data is set
TEST_F(MrwImageTest_979, PixelWidth_NoExifData_ReturnsZero_979) {
    auto image = createMrwImage();
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test pixelHeight returns 0 when no EXIF data is set
TEST_F(MrwImageTest_979, PixelHeight_NoExifData_ReturnsZero_979) {
    auto image = createMrwImage();
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test pixelWidth returns the correct value when Exif.Image.ImageWidth is set
TEST_F(MrwImageTest_979, PixelWidth_WithExifImageWidth_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(1920);
    EXPECT_EQ(image->pixelWidth(), 1920u);
}

// Test pixelHeight returns the correct value when Exif.Image.ImageLength is set
TEST_F(MrwImageTest_979, PixelHeight_WithExifImageLength_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(1080);
    EXPECT_EQ(image->pixelHeight(), 1080u);
}

// Test pixelWidth with a small value
TEST_F(MrwImageTest_979, PixelWidth_SmallValue_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(1);
    EXPECT_EQ(image->pixelWidth(), 1u);
}

// Test pixelHeight with a small value
TEST_F(MrwImageTest_979, PixelHeight_SmallValue_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(1);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test pixelWidth with a large value
TEST_F(MrwImageTest_979, PixelWidth_LargeValue_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(65535);
    EXPECT_EQ(image->pixelWidth(), 65535u);
}

// Test pixelHeight with a large value
TEST_F(MrwImageTest_979, PixelHeight_LargeValue_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(65535);
    EXPECT_EQ(image->pixelHeight(), 65535u);
}

// Test that setExifData does not throw (MRW images don't support setting EXIF directly)
TEST_F(MrwImageTest_979, SetExifData_DoesNotThrow_979) {
    auto image = createMrwImage();
    ExifData exifData;
    EXPECT_NO_THROW(image->setExifData(exifData));
}

// Test that setIptcData does not throw (MRW images don't support setting IPTC directly)
TEST_F(MrwImageTest_979, SetIptcData_DoesNotThrow_979) {
    auto image = createMrwImage();
    IptcData iptcData;
    EXPECT_NO_THROW(image->setIptcData(iptcData));
}

// Test that setComment does not throw
TEST_F(MrwImageTest_979, SetComment_DoesNotThrow_979) {
    auto image = createMrwImage();
    EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test that clearExifData results in pixelWidth returning 0
TEST_F(MrwImageTest_979, ClearExifData_PixelWidthReturnsZero_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(1920);
    EXPECT_EQ(image->pixelWidth(), 1920u);
    image->clearExifData();
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test that clearExifData results in pixelHeight returning 0
TEST_F(MrwImageTest_979, ClearExifData_PixelHeightReturnsZero_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(1080);
    EXPECT_EQ(image->pixelHeight(), 1080u);
    image->clearExifData();
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test pixelWidth with zero value explicitly set
TEST_F(MrwImageTest_979, PixelWidth_ZeroValueSet_ReturnsZero_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(0);
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test pixelHeight with zero value explicitly set
TEST_F(MrwImageTest_979, PixelHeight_ZeroValueSet_ReturnsZero_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(0);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test that both width and height can be set simultaneously
TEST_F(MrwImageTest_979, PixelWidthAndHeight_BothSet_ReturnCorrectValues_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(3840);
    exifData["Exif.Image.ImageLength"] = uint32_t(2160);
    EXPECT_EQ(image->pixelWidth(), 3840u);
    EXPECT_EQ(image->pixelHeight(), 2160u);
}

// Test that good() returns true for a newly created MRW image with valid IO
TEST_F(MrwImageTest_979, Good_NewImage_ReturnsExpected_979) {
    auto image = createMrwImage();
    // MemIo should be valid
    EXPECT_TRUE(image->good());
}

// Test that exifData returns a reference that can be modified
TEST_F(MrwImageTest_979, ExifData_ModifiableReference_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    EXPECT_TRUE(exifData.empty());
    exifData["Exif.Image.ImageWidth"] = uint32_t(640);
    EXPECT_FALSE(exifData.empty());
}

// Test readMetadata with empty IO - should throw
TEST_F(MrwImageTest_979, ReadMetadata_EmptyIo_Throws_979) {
    auto image = createMrwImage();
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test writeMetadata with empty IO - should throw
TEST_F(MrwImageTest_979, WriteMetadata_EmptyIo_Throws_979) {
    auto image = createMrwImage();
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test pixelWidth with uint16_t value to check type conversion
TEST_F(MrwImageTest_979, PixelWidth_Uint16Value_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint16_t(800);
    EXPECT_EQ(image->pixelWidth(), 800u);
}

// Test pixelHeight with uint16_t value
TEST_F(MrwImageTest_979, PixelHeight_Uint16Value_ReturnsCorrectValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageLength"] = uint16_t(600);
    EXPECT_EQ(image->pixelHeight(), 600u);
}

// Test that updating pixelWidth reflects new value
TEST_F(MrwImageTest_979, PixelWidth_UpdateValue_ReturnsNewValue_979) {
    auto image = createMrwImage();
    ExifData& exifData = image->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(1024);
    EXPECT_EQ(image->pixelWidth(), 1024u);
    exifData["Exif.Image.ImageWidth"] = uint32_t(2048);
    EXPECT_EQ(image->pixelWidth(), 2048u);
}
