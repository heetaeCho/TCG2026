#include <gtest/gtest.h>
#include <exiv2/crwimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

class CrwImageTest_1813 : public ::testing::Test {
protected:
    std::unique_ptr<CrwImage> createCrwImage() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<CrwImage>(std::move(io), true);
    }
};

// Test that mimeType returns the correct MIME type for CRW images
TEST_F(CrwImageTest_1813, MimeTypeReturnsCrwMimeType_1813) {
    auto img = createCrwImage();
    EXPECT_EQ("image/x-canon-crw", img->mimeType());
}

// Test that pixelWidth returns 0 when no EXIF data is set
TEST_F(CrwImageTest_1813, PixelWidthReturnsZeroWhenNoExifData_1813) {
    auto img = createCrwImage();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelHeight returns 0 when no EXIF data is set
TEST_F(CrwImageTest_1813, PixelHeightReturnsZeroWhenNoExifData_1813) {
    auto img = createCrwImage();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that pixelWidth returns the correct value when Exif.Photo.PixelXDimension is set
TEST_F(CrwImageTest_1813, PixelWidthReturnsCorrectValueWhenSet_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);
    EXPECT_EQ(1920u, img->pixelWidth());
}

// Test that pixelHeight returns the correct value when Exif.Photo.PixelYDimension is set
TEST_F(CrwImageTest_1813, PixelHeightReturnsCorrectValueWhenSet_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1080);
    EXPECT_EQ(1080u, img->pixelHeight());
}

// Test that pixelWidth returns correct value for large dimensions
TEST_F(CrwImageTest_1813, PixelWidthLargeValue_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4294967295u);
    EXPECT_EQ(4294967295u, img->pixelWidth());
}

// Test that pixelHeight returns correct value for large dimensions
TEST_F(CrwImageTest_1813, PixelHeightLargeValue_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(4294967295u);
    EXPECT_EQ(4294967295u, img->pixelHeight());
}

// Test that pixelWidth and pixelHeight can be set independently
TEST_F(CrwImageTest_1813, PixelDimensionsIndependent_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(800);
    // Only width set, height should still be 0
    EXPECT_EQ(800u, img->pixelWidth());
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that setting PixelYDimension without PixelXDimension works
TEST_F(CrwImageTest_1813, PixelHeightSetWithoutWidth_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(600);
    EXPECT_EQ(0u, img->pixelWidth());
    EXPECT_EQ(600u, img->pixelHeight());
}

// Test that both dimensions can be set together
TEST_F(CrwImageTest_1813, BothDimensionsSet_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(3000);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(2000);
    EXPECT_EQ(3000u, img->pixelWidth());
    EXPECT_EQ(2000u, img->pixelHeight());
}

// Test that setIptcData does not throw (CRW does not support IPTC, should be no-op)
TEST_F(CrwImageTest_1813, SetIptcDataNoOp_1813) {
    auto img = createCrwImage();
    IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test clearing exif data resets pixel dimensions
TEST_F(CrwImageTest_1813, ClearExifDataResetsPixelDimensions_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1024);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(768);
    EXPECT_EQ(1024u, img->pixelWidth());
    EXPECT_EQ(768u, img->pixelHeight());

    img->clearExifData();
    EXPECT_EQ(0u, img->pixelWidth());
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelWidth with zero value set explicitly
TEST_F(CrwImageTest_1813, PixelWidthZeroExplicit_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test pixelHeight with zero value set explicitly
TEST_F(CrwImageTest_1813, PixelHeightZeroExplicit_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that pixelWidth with value 1 (minimum non-zero)
TEST_F(CrwImageTest_1813, PixelWidthMinNonZero_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelWidth());
}

// Test that pixelHeight with value 1 (minimum non-zero)
TEST_F(CrwImageTest_1813, PixelHeightMinNonZero_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelHeight());
}

// Test that exifData returns a modifiable reference
TEST_F(CrwImageTest_1813, ExifDataIsModifiable_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    EXPECT_TRUE(exifData.empty());
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(640);
    EXPECT_FALSE(exifData.empty());
}

// Test good() on a newly created CrwImage with MemIo
TEST_F(CrwImageTest_1813, GoodOnNewImage_1813) {
    auto img = createCrwImage();
    // MemIo should be in a good state
    EXPECT_TRUE(img->good());
}

// Test that setting exifData via setExifData works for pixel dimensions
TEST_F(CrwImageTest_1813, SetExifDataAffectsPixelDimensions_1813) {
    auto img = createCrwImage();
    ExifData exifData;
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(2560);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1440);
    img->setExifData(exifData);
    EXPECT_EQ(2560u, img->pixelWidth());
    EXPECT_EQ(1440u, img->pixelHeight());
}

// Test updating pixel dimensions after initial set
TEST_F(CrwImageTest_1813, UpdatePixelDimensions_1813) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(100);
    EXPECT_EQ(100u, img->pixelWidth());

    exifData["Exif.Photo.PixelXDimension"] = uint32_t(200);
    EXPECT_EQ(200u, img->pixelWidth());
}
