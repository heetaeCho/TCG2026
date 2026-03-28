#include <gtest/gtest.h>
#include <exiv2/cr2image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

class Cr2ImageTest_1740 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::Cr2Image> createCr2Image() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::Cr2Image>(std::move(io), true);
    }
};

// Test that mimeType returns the correct MIME type for CR2
TEST_F(Cr2ImageTest_1740, MimeTypeReturnsCr2_1740) {
    auto img = createCr2Image();
    EXPECT_EQ("image/x-canon-cr2", img->mimeType());
}

// Test that pixelWidth returns 0 when no EXIF data is present
TEST_F(Cr2ImageTest_1740, PixelWidthReturnsZeroWhenNoExifData_1740) {
    auto img = createCr2Image();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelHeight returns 0 when no EXIF data is present
TEST_F(Cr2ImageTest_1740, PixelHeightReturnsZeroWhenNoExifData_1740) {
    auto img = createCr2Image();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that pixelWidth returns the correct value when PixelXDimension is set
TEST_F(Cr2ImageTest_1740, PixelWidthReturnsCorrectValueWhenSet_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4000);
    EXPECT_EQ(4000u, img->pixelWidth());
}

// Test that pixelHeight returns the correct value when PixelYDimension is set
TEST_F(Cr2ImageTest_1740, PixelHeightReturnsCorrectValueWhenSet_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3000);
    EXPECT_EQ(3000u, img->pixelHeight());
}

// Test pixelWidth with a value of 1 (boundary)
TEST_F(Cr2ImageTest_1740, PixelWidthBoundaryValueOne_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelWidth());
}

// Test pixelHeight with a value of 1 (boundary)
TEST_F(Cr2ImageTest_1740, PixelHeightBoundaryValueOne_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelHeight());
}

// Test pixelWidth with max uint32 value
TEST_F(Cr2ImageTest_1740, PixelWidthMaxValue_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, img->pixelWidth());
}

// Test pixelHeight with max uint32 value
TEST_F(Cr2ImageTest_1740, PixelHeightMaxValue_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, img->pixelHeight());
}

// Test that setComment does not throw (CR2 typically doesn't support comments)
TEST_F(Cr2ImageTest_1740, SetCommentDoesNotThrow_1740) {
    auto img = createCr2Image();
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test that clearExifData resets pixelWidth to 0
TEST_F(Cr2ImageTest_1740, ClearExifDataResetsPixelWidth_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4000);
    EXPECT_EQ(4000u, img->pixelWidth());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that clearExifData resets pixelHeight to 0
TEST_F(Cr2ImageTest_1740, ClearExifDataResetsPixelHeight_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3000);
    EXPECT_EQ(3000u, img->pixelHeight());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that exifData returns a modifiable reference
TEST_F(Cr2ImageTest_1740, ExifDataIsModifiable_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    EXPECT_TRUE(exifData.empty());
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);
    EXPECT_FALSE(exifData.empty());
}

// Test that pixelWidth returns 0 when a different EXIF key is set (not PixelXDimension)
TEST_F(Cr2ImageTest_1740, PixelWidthZeroWithUnrelatedExifKey_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3000);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelHeight returns 0 when a different EXIF key is set (not PixelYDimension)
TEST_F(Cr2ImageTest_1740, PixelHeightZeroWithUnrelatedExifKey_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4000);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that both pixelWidth and pixelHeight can be set simultaneously
TEST_F(Cr2ImageTest_1740, BothDimensionsSetCorrectly_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(5472);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(3648);
    EXPECT_EQ(5472u, img->pixelWidth());
    EXPECT_EQ(3648u, img->pixelHeight());
}

// Test pixelWidth with value 0 explicitly set
TEST_F(Cr2ImageTest_1740, PixelWidthExplicitZero_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test pixelHeight with value 0 explicitly set
TEST_F(Cr2ImageTest_1740, PixelHeightExplicitZero_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test good() on a freshly created image with MemIo
TEST_F(Cr2ImageTest_1740, GoodReturnsTrueForMemIo_1740) {
    auto img = createCr2Image();
    EXPECT_TRUE(img->good());
}

// Test that updating pixelWidth multiple times yields the last value
TEST_F(Cr2ImageTest_1740, PixelWidthUpdateOverwrites_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);
    EXPECT_EQ(1920u, img->pixelWidth());
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(3840);
    EXPECT_EQ(3840u, img->pixelWidth());
}

// Test that setExifData replaces existing EXIF data
TEST_F(Cr2ImageTest_1740, SetExifDataReplacesData_1740) {
    auto img = createCr2Image();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);
    EXPECT_EQ(1920u, img->pixelWidth());

    Exiv2::ExifData newExifData;
    newExifData["Exif.Photo.PixelXDimension"] = uint32_t(7680);
    img->setExifData(newExifData);
    EXPECT_EQ(7680u, img->pixelWidth());
}

}  // namespace
