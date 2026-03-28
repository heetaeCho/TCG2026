#include <gtest/gtest.h>
#include <exiv2/rafimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <memory>

using namespace Exiv2;

class RafImagePixelWidthTest_218 : public ::testing::Test {
protected:
    std::unique_ptr<RafImage> createRafImage() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<RafImage>(std::move(io), true);
    }
};

// Test that pixelWidth returns 0 when pixelWidth_ is 0 and no exif data is set
TEST_F(RafImagePixelWidthTest_218, ReturnsZeroWhenNoPixelWidthAndNoExifData_218) {
    auto img = createRafImage();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelWidth returns the value from exif data when key exists and has count > 0
TEST_F(RafImagePixelWidthTest_218, ReturnsExifValueWhenKeyExistsWithCount_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = uint32_t(4000);
    EXPECT_EQ(4000u, img->pixelWidth());
}

// Test that pixelWidth returns 0 when the exif key does not exist
TEST_F(RafImagePixelWidthTest_218, ReturnsZeroWhenExifKeyNotFound_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    // Add a different key, not the one we're looking for
    exifData["Exif.Fujifilm.RawImageFullHeight"] = uint32_t(3000);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelWidth returns various uint32 values correctly
TEST_F(RafImagePixelWidthTest_218, ReturnsCorrectValueForVariousWidths_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    
    exifData["Exif.Fujifilm.RawImageFullWidth"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelWidth());
}

// Test with a large width value
TEST_F(RafImagePixelWidthTest_218, ReturnsLargeWidthValue_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = uint32_t(65535);
    EXPECT_EQ(65535u, img->pixelWidth());
}

// Test that mimeType returns expected value for RAF images
TEST_F(RafImagePixelWidthTest_218, MimeTypeReturnsExpectedValue_218) {
    auto img = createRafImage();
    EXPECT_EQ("image/x-fuji-raf", img->mimeType());
}

// Test pixelHeight returns 0 when no data set
TEST_F(RafImagePixelWidthTest_218, PixelHeightReturnsZeroWhenNoData_218) {
    auto img = createRafImage();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelHeight returns value from exif when key exists
TEST_F(RafImagePixelWidthTest_218, PixelHeightReturnsExifValueWhenKeyExists_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Fujifilm.RawImageFullHeight"] = uint32_t(3000);
    EXPECT_EQ(3000u, img->pixelHeight());
}

// Test that clearing exif data makes pixelWidth return 0 again
TEST_F(RafImagePixelWidthTest_218, ReturnsZeroAfterClearingExifData_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = uint32_t(4000);
    EXPECT_EQ(4000u, img->pixelWidth());
    
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test with zero value in exif data
TEST_F(RafImagePixelWidthTest_218, ReturnsZeroWhenExifValueIsZero_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = uint32_t(0);
    // The exif key exists with count > 0, toUint32() returns 0
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that setExifData doesn't throw (RAF images may not support writing EXIF)
TEST_F(RafImagePixelWidthTest_218, SetExifDataDoesNotThrow_218) {
    auto img = createRafImage();
    ExifData exifData;
    EXPECT_NO_THROW(img->setExifData(exifData));
}

// Test that setIptcData doesn't throw
TEST_F(RafImagePixelWidthTest_218, SetIptcDataDoesNotThrow_218) {
    auto img = createRafImage();
    IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test that setComment doesn't throw
TEST_F(RafImagePixelWidthTest_218, SetCommentDoesNotThrow_218) {
    auto img = createRafImage();
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test with maximum uint32 value
TEST_F(RafImagePixelWidthTest_218, ReturnsMaxUint32Value_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, img->pixelWidth());
}

// Test that both width and height can be retrieved independently
TEST_F(RafImagePixelWidthTest_218, WidthAndHeightIndependent_218) {
    auto img = createRafImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Fujifilm.RawImageFullWidth"] = uint32_t(4000);
    exifData["Exif.Fujifilm.RawImageFullHeight"] = uint32_t(3000);
    EXPECT_EQ(4000u, img->pixelWidth());
    EXPECT_EQ(3000u, img->pixelHeight());
}
