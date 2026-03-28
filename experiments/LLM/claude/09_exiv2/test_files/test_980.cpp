#include <gtest/gtest.h>
#include <exiv2/mrwimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

class MrwImageTest_980 : public ::testing::Test {
protected:
    std::unique_ptr<MrwImage> createMrwImage() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<MrwImage>(std::move(io), true);
    }
};

// Test that mimeType returns the correct MIME type for MRW images
TEST_F(MrwImageTest_980, MimeType_ReturnsCorrectType_980) {
    auto img = createMrwImage();
    EXPECT_EQ("image/x-minolta-mrw", img->mimeType());
}

// Test pixelWidth returns 0 when no exif data is set
TEST_F(MrwImageTest_980, PixelWidth_NoExifData_ReturnsZero_980) {
    auto img = createMrwImage();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test pixelHeight returns 0 when no exif data is set
TEST_F(MrwImageTest_980, PixelHeight_NoExifData_ReturnsZero_980) {
    auto img = createMrwImage();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelWidth returns correct value when Exif.Image.ImageWidth is set
TEST_F(MrwImageTest_980, PixelWidth_WithExifData_ReturnsCorrectValue_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(1920);
    EXPECT_EQ(1920u, img->pixelWidth());
}

// Test pixelHeight returns correct value when Exif.Image.ImageLength is set
TEST_F(MrwImageTest_980, PixelHeight_WithExifData_ReturnsCorrectValue_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(1080);
    EXPECT_EQ(1080u, img->pixelHeight());
}

// Test pixelWidth with a boundary value of 0
TEST_F(MrwImageTest_980, PixelWidth_ZeroValue_ReturnsZero_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test pixelHeight with a boundary value of 0
TEST_F(MrwImageTest_980, PixelHeight_ZeroValue_ReturnsZero_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelWidth with a large value
TEST_F(MrwImageTest_980, PixelWidth_LargeValue_ReturnsCorrectValue_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(65535);
    EXPECT_EQ(65535u, img->pixelWidth());
}

// Test pixelHeight with a large value
TEST_F(MrwImageTest_980, PixelHeight_LargeValue_ReturnsCorrectValue_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(65535);
    EXPECT_EQ(65535u, img->pixelHeight());
}

// Test that setExifData does not throw (MRW is read-only for exif set)
TEST_F(MrwImageTest_980, SetExifData_DoesNotThrow_980) {
    auto img = createMrwImage();
    ExifData exifData;
    EXPECT_NO_THROW(img->setExifData(exifData));
}

// Test that setIptcData does not throw (MRW is read-only for iptc set)
TEST_F(MrwImageTest_980, SetIptcData_DoesNotThrow_980) {
    auto img = createMrwImage();
    IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test that setComment does not throw
TEST_F(MrwImageTest_980, SetComment_DoesNotThrow_980) {
    auto img = createMrwImage();
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test that readMetadata on empty io throws
TEST_F(MrwImageTest_980, ReadMetadata_EmptyIo_Throws_980) {
    auto img = createMrwImage();
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that writeMetadata throws (MRW writing is not supported)
TEST_F(MrwImageTest_980, WriteMetadata_Throws_980) {
    auto img = createMrwImage();
    EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

// Test that good() returns true on a fresh image with valid io
TEST_F(MrwImageTest_980, Good_FreshImage_980) {
    auto img = createMrwImage();
    // MemIo is valid, so good() should reflect io state
    // The exact behavior depends on BasicIo state
    // Just verify it doesn't crash
    img->good();
}

// Test that clearing exif data results in pixelWidth returning 0
TEST_F(MrwImageTest_980, ClearExifData_PixelWidthReturnsZero_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(1920);
    EXPECT_EQ(1920u, img->pixelWidth());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that clearing exif data results in pixelHeight returning 0
TEST_F(MrwImageTest_980, ClearExifData_PixelHeightReturnsZero_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(1080);
    EXPECT_EQ(1080u, img->pixelHeight());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelWidth with max uint32_t value
TEST_F(MrwImageTest_980, PixelWidth_MaxUint32_ReturnsCorrectValue_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, img->pixelWidth());
}

// Test pixelHeight with max uint32_t value
TEST_F(MrwImageTest_980, PixelHeight_MaxUint32_ReturnsCorrectValue_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, img->pixelHeight());
}

// Test that both width and height can be set simultaneously
TEST_F(MrwImageTest_980, PixelDimensions_BothSet_ReturnsCorrectValues_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(3840);
    exifData["Exif.Image.ImageLength"] = uint32_t(2160);
    EXPECT_EQ(3840u, img->pixelWidth());
    EXPECT_EQ(2160u, img->pixelHeight());
}

// Test that only width is set, height should be 0
TEST_F(MrwImageTest_980, OnlyWidthSet_HeightReturnsZero_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(1024);
    EXPECT_EQ(1024u, img->pixelWidth());
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that only height is set, width should be 0
TEST_F(MrwImageTest_980, OnlyHeightSet_WidthReturnsZero_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = uint32_t(768);
    EXPECT_EQ(0u, img->pixelWidth());
    EXPECT_EQ(768u, img->pixelHeight());
}

// Test overwriting pixel dimensions
TEST_F(MrwImageTest_980, PixelDimensions_Overwrite_980) {
    auto img = createMrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = uint32_t(640);
    EXPECT_EQ(640u, img->pixelWidth());
    exifData["Exif.Image.ImageWidth"] = uint32_t(1280);
    EXPECT_EQ(1280u, img->pixelWidth());
}
