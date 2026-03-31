#include <gtest/gtest.h>
#include <exiv2/crwimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

// Helper to create a CrwImage with a MemIo (in-memory I/O)
class CrwImageTest_1812 : public ::testing::Test {
protected:
    std::unique_ptr<CrwImage> createCrwImage() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<CrwImage>(std::move(io), true);
    }
};

// Test: pixelWidth returns 0 when no EXIF data is set
TEST_F(CrwImageTest_1812, PixelWidthReturnsZeroWhenNoExifData_1812) {
    auto img = createCrwImage();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test: pixelHeight returns 0 when no EXIF data is set
TEST_F(CrwImageTest_1812, PixelHeightReturnsZeroWhenNoExifData_1812) {
    auto img = createCrwImage();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test: pixelWidth returns correct value when Exif.Photo.PixelXDimension is set
TEST_F(CrwImageTest_1812, PixelWidthReturnsValueWhenExifDataSet_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);
    EXPECT_EQ(1920u, img->pixelWidth());
}

// Test: pixelHeight returns correct value when Exif.Photo.PixelYDimension is set
TEST_F(CrwImageTest_1812, PixelHeightReturnsValueWhenExifDataSet_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1080);
    EXPECT_EQ(1080u, img->pixelHeight());
}

// Test: mimeType returns the correct MIME type for CRW images
TEST_F(CrwImageTest_1812, MimeTypeReturnsCrwMimeType_1812) {
    auto img = createCrwImage();
    EXPECT_EQ("image/x-canon-crw", img->mimeType());
}

// Test: setIptcData does not throw (CRW doesn't support IPTC, it's a no-op)
TEST_F(CrwImageTest_1812, SetIptcDataDoesNotThrow_1812) {
    auto img = createCrwImage();
    IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test: pixelWidth with a large value
TEST_F(CrwImageTest_1812, PixelWidthLargeValue_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(4294967295u);
    EXPECT_EQ(4294967295u, img->pixelWidth());
}

// Test: pixelHeight with a large value
TEST_F(CrwImageTest_1812, PixelHeightLargeValue_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(4294967295u);
    EXPECT_EQ(4294967295u, img->pixelHeight());
}

// Test: pixelWidth returns 0 when value is set to 0
TEST_F(CrwImageTest_1812, PixelWidthReturnsZeroWhenSetToZero_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test: pixelHeight returns 0 when value is set to 0
TEST_F(CrwImageTest_1812, PixelHeightReturnsZeroWhenSetToZero_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(0);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test: pixelWidth with value 1 (boundary)
TEST_F(CrwImageTest_1812, PixelWidthBoundaryOne_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelWidth());
}

// Test: pixelHeight with value 1 (boundary)
TEST_F(CrwImageTest_1812, PixelHeightBoundaryOne_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1);
    EXPECT_EQ(1u, img->pixelHeight());
}

// Test: clearExifData resets pixelWidth to 0
TEST_F(CrwImageTest_1812, ClearExifDataResetsPixelWidth_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(800);
    EXPECT_EQ(800u, img->pixelWidth());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test: clearExifData resets pixelHeight to 0
TEST_F(CrwImageTest_1812, ClearExifDataResetsPixelHeight_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(600);
    EXPECT_EQ(600u, img->pixelHeight());
    img->clearExifData();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test: Setting pixelWidth via exifData and then updating it
TEST_F(CrwImageTest_1812, PixelWidthUpdatedAfterChange_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(640);
    EXPECT_EQ(640u, img->pixelWidth());
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1280);
    EXPECT_EQ(1280u, img->pixelWidth());
}

// Test: Setting pixelHeight via exifData and then updating it
TEST_F(CrwImageTest_1812, PixelHeightUpdatedAfterChange_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(480);
    EXPECT_EQ(480u, img->pixelHeight());
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(960);
    EXPECT_EQ(960u, img->pixelHeight());
}

// Test: pixelWidth doesn't return other EXIF fields' values
TEST_F(CrwImageTest_1812, PixelWidthNotAffectedByOtherExifKeys_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(1080);
    // PixelXDimension not set, should return 0
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test: pixelHeight doesn't return other EXIF fields' values
TEST_F(CrwImageTest_1812, PixelHeightNotAffectedByOtherExifKeys_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(1920);
    // PixelYDimension not set, should return 0
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test: Both pixelWidth and pixelHeight can be set independently
TEST_F(CrwImageTest_1812, BothDimensionsSetIndependently_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(3840);
    exifData["Exif.Photo.PixelYDimension"] = uint32_t(2160);
    EXPECT_EQ(3840u, img->pixelWidth());
    EXPECT_EQ(2160u, img->pixelHeight());
}

// Test: good() returns true for a valid MemIo-backed image
TEST_F(CrwImageTest_1812, GoodReturnsTrueForMemIo_1812) {
    auto img = createCrwImage();
    EXPECT_TRUE(img->good());
}

// Test: exifData returns a reference that can be manipulated
TEST_F(CrwImageTest_1812, ExifDataReturnsManipulableReference_1812) {
    auto img = createCrwImage();
    ExifData& exifData = img->exifData();
    EXPECT_TRUE(exifData.empty());
    exifData["Exif.Photo.PixelXDimension"] = uint32_t(100);
    EXPECT_FALSE(exifData.empty());
}

// Test: setExifData replaces existing EXIF data
TEST_F(CrwImageTest_1812, SetExifDataReplacesExistingData_1812) {
    auto img = createCrwImage();
    img->exifData()["Exif.Photo.PixelXDimension"] = uint32_t(500);
    EXPECT_EQ(500u, img->pixelWidth());

    ExifData newExifData;
    newExifData["Exif.Photo.PixelXDimension"] = uint32_t(999);
    img->setExifData(newExifData);
    EXPECT_EQ(999u, img->pixelWidth());
}
