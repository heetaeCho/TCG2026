#include <gtest/gtest.h>
#include <exiv2/orfimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

namespace {

class OrfImageTest_1548 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::OrfImage> createOrfImage() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::OrfImage>(std::move(io), true);
    }
};

// Test that pixelWidth returns 0 when no Exif.Image.ImageWidth is set
TEST_F(OrfImageTest_1548, PixelWidthReturnsZeroWhenNoExifData_1548) {
    auto img = createOrfImage();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that pixelHeight returns 0 when no Exif.Image.ImageLength is set
TEST_F(OrfImageTest_1548, PixelHeightReturnsZeroWhenNoExifData_1548) {
    auto img = createOrfImage();
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test that pixelWidth returns the correct value when Exif.Image.ImageWidth is set
TEST_F(OrfImageTest_1548, PixelWidthReturnsCorrectValueWhenSet_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1920);
    EXPECT_EQ(1920u, img->pixelWidth());
}

// Test that pixelHeight returns the correct value when Exif.Image.ImageLength is set
TEST_F(OrfImageTest_1548, PixelHeightReturnsCorrectValueWhenSet_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(1080);
    EXPECT_EQ(1080u, img->pixelHeight());
}

// Test pixelWidth with a value of 0
TEST_F(OrfImageTest_1548, PixelWidthReturnsZeroWhenSetToZero_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(0);
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test pixelHeight with a value of 0
TEST_F(OrfImageTest_1548, PixelHeightReturnsZeroWhenSetToZero_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(0);
    EXPECT_EQ(0u, img->pixelHeight());
}

// Test pixelWidth with a large value
TEST_F(OrfImageTest_1548, PixelWidthLargeValue_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(4294967295u);
    EXPECT_EQ(4294967295u, img->pixelWidth());
}

// Test pixelHeight with a large value
TEST_F(OrfImageTest_1548, PixelHeightLargeValue_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(4294967295u);
    EXPECT_EQ(4294967295u, img->pixelHeight());
}

// Test mimeType returns the expected ORF mime type
TEST_F(OrfImageTest_1548, MimeTypeReturnsOrfType_1548) {
    auto img = createOrfImage();
    std::string mime = img->mimeType();
    EXPECT_FALSE(mime.empty());
    // ORF images typically have image/x-olympus-orf mime type
    EXPECT_EQ("image/x-olympus-orf", mime);
}

// Test setComment does not crash (ORF doesn't support comments typically)
TEST_F(OrfImageTest_1548, SetCommentDoesNotCrash_1548) {
    auto img = createOrfImage();
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test that exifData can be set and cleared
TEST_F(OrfImageTest_1548, ExifDataCanBeSetAndCleared_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(640);
    EXPECT_EQ(640u, img->pixelWidth());

    img->clearExifData();
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test pixelWidth after updating the value
TEST_F(OrfImageTest_1548, PixelWidthUpdatedValue_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(800);
    EXPECT_EQ(800u, img->pixelWidth());

    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1024);
    EXPECT_EQ(1024u, img->pixelWidth());
}

// Test pixelHeight after updating the value
TEST_F(OrfImageTest_1548, PixelHeightUpdatedValue_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(600);
    EXPECT_EQ(600u, img->pixelHeight());

    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(768);
    EXPECT_EQ(768u, img->pixelHeight());
}

// Test that both width and height can be set simultaneously
TEST_F(OrfImageTest_1548, BothWidthAndHeightSet_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(3840);
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(2160);
    EXPECT_EQ(3840u, img->pixelWidth());
    EXPECT_EQ(2160u, img->pixelHeight());
}

// Test pixelWidth with value of 1 (boundary)
TEST_F(OrfImageTest_1548, PixelWidthBoundaryOne_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1);
    EXPECT_EQ(1u, img->pixelWidth());
}

// Test pixelHeight with value of 1 (boundary)
TEST_F(OrfImageTest_1548, PixelHeightBoundaryOne_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.ImageLength"] = static_cast<uint32_t>(1);
    EXPECT_EQ(1u, img->pixelHeight());
}

// Test that setting unrelated exif data doesn't affect pixelWidth
TEST_F(OrfImageTest_1548, UnrelatedExifDoesNotAffectPixelWidth_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.Make"] = "Olympus";
    EXPECT_EQ(0u, img->pixelWidth());
}

// Test that setting unrelated exif data doesn't affect pixelHeight
TEST_F(OrfImageTest_1548, UnrelatedExifDoesNotAffectPixelHeight_1548) {
    auto img = createOrfImage();
    Exiv2::ExifData& exifData = img->exifData();
    exifData["Exif.Image.Make"] = "Olympus";
    EXPECT_EQ(0u, img->pixelHeight());
}

}  // namespace
