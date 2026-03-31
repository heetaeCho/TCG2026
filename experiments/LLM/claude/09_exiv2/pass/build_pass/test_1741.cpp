#include <gtest/gtest.h>
#include <exiv2/cr2image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

class Cr2ImageTest_1741 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::Cr2Image> createCr2Image() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::Cr2Image>(std::move(io), true);
    }
};

// Test that mimeType returns the correct MIME type for CR2 images
TEST_F(Cr2ImageTest_1741, MimeTypeReturnsCr2_1741) {
    auto img = createCr2Image();
    EXPECT_EQ("image/x-canon-cr2", img->mimeType());
}

// Test that pixelWidth returns 0 when no EXIF data is present
TEST_F(Cr2ImageTest_1741, PixelWidthReturnsZeroWhenNoExifData_1741) {
    auto img = createCr2Image();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelHeight returns 0 when no EXIF data is present
TEST_F(Cr2ImageTest_1741, PixelHeightReturnsZeroWhenNoExifData_1741) {
    auto img = createCr2Image();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that pixelWidth returns correct value when Exif.Photo.PixelXDimension is set
TEST_F(Cr2ImageTest_1741, PixelWidthReturnsCorrectValueWhenSet_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4000);
    EXPECT_EQ(4000u, img->pixelWidth());
}

// Test that pixelHeight returns correct value when Exif.Photo.PixelYDimension is set
TEST_F(Cr2ImageTest_1741, PixelHeightReturnsCorrectValueWhenSet_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3000);
    EXPECT_EQ(3000u, img->pixelHeight());
}

// Test pixelWidth with a value of 0
TEST_F(Cr2ImageTest_1741, PixelWidthReturnsZeroWhenSetToZero_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test pixelHeight with a value of 0
TEST_F(Cr2ImageTest_1741, PixelHeightReturnsZeroWhenSetToZero_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelWidth with a large value
TEST_F(Cr2ImageTest_1741, PixelWidthLargeValue_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(65535);
    EXPECT_EQ(65535u, img->pixelWidth());
}

// Test pixelHeight with a large value
TEST_F(Cr2ImageTest_1741, PixelHeightLargeValue_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(65535);
    EXPECT_EQ(65535u, img->pixelHeight());
}

// Test that setComment does not throw (CR2 typically ignores comments)
TEST_F(Cr2ImageTest_1741, SetCommentDoesNotThrow_1741) {
    auto img = createCr2Image();
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test that good() returns true for a freshly created image with MemIo
TEST_F(Cr2ImageTest_1741, GoodReturnsTrueForMemIo_1741) {
    auto img = createCr2Image();
    // MemIo should be valid
    EXPECT_TRUE(img->good());
}

// Test that exifData can be cleared and pixelWidth returns 0
TEST_F(Cr2ImageTest_1741, ClearExifDataResetsPixelWidth_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4000);
    EXPECT_EQ(4000u, img->pixelWidth());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that exifData can be cleared and pixelHeight returns 0
TEST_F(Cr2ImageTest_1741, ClearExifDataResetsPixelHeight_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3000);
    EXPECT_EQ(3000u, img->pixelHeight());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test setting both width and height
TEST_F(Cr2ImageTest_1741, BothPixelDimensionsSet_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(5472);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3648);
    EXPECT_EQ(5472u, img->pixelWidth());
    EXPECT_EQ(3648u, img->pixelHeight());
}

// Test that pixelWidth returns 0 when only PixelYDimension is set
TEST_F(Cr2ImageTest_1741, PixelWidthZeroWhenOnlyHeightSet_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3000);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelHeight returns 0 when only PixelXDimension is set
TEST_F(Cr2ImageTest_1741, PixelHeightZeroWhenOnlyWidthSet_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4000);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelWidth with value 1 (boundary)
TEST_F(Cr2ImageTest_1741, PixelWidthBoundaryOne_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelWidth());
}

// Test pixelHeight with value 1 (boundary)
TEST_F(Cr2ImageTest_1741, PixelHeightBoundaryOne_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelHeight());
}

// Test that imageType is cr2
TEST_F(Cr2ImageTest_1741, ImageTypeIsCr2_1741) {
    auto img = createCr2Image();
    EXPECT_EQ(Exiv2::ImageType::cr2, img->imageType());
}

// Test pixelWidth with max uint32_t value
TEST_F(Cr2ImageTest_1741, PixelWidthMaxUint32_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, img->pixelWidth());
}

// Test pixelHeight with max uint32_t value
TEST_F(Cr2ImageTest_1741, PixelHeightMaxUint32_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, img->pixelHeight());
}

// Test that setting exifData with unrelated keys doesn't affect pixel dimensions
TEST_F(Cr2ImageTest_1741, UnrelatedExifKeysDoNotAffectDimensions_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS 5D Mark IV";
    EXPECT_EQ(0u, img->pixelWidth());
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test overwriting pixel dimensions
TEST_F(Cr2ImageTest_1741, OverwritePixelDimensions_1741) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4000);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3000);
    EXPECT_EQ(4000u, img->pixelWidth());
    EXPECT_EQ(3000u, img->pixelHeight());
    
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(8000);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(6000);
    EXPECT_EQ(8000u, img->pixelWidth());
    EXPECT_EQ(6000u, img->pixelHeight());
}

}  // namespace
