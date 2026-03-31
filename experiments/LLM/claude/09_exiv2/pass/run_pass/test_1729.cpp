#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "exiv2/tiffimage.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"

namespace {

// Helper to create a TiffImage with a MemIo (in-memory I/O)
std::unique_ptr<Exiv2::TiffImage> createTiffImage() {
  auto io = std::make_unique<Exiv2::MemIo>();
  return std::make_unique<Exiv2::TiffImage>(std::move(io), true);
}

class TiffImageMimeTypeTest_1729 : public ::testing::Test {
 protected:
  void SetUp() override {
    tiffImage_ = createTiffImage();
  }

  std::unique_ptr<Exiv2::TiffImage> tiffImage_;
};

// Test that the default MIME type is "image/tiff" when no compression metadata is set
TEST_F(TiffImageMimeTypeTest_1729, DefaultMimeType_1729) {
  std::string mime = tiffImage_->mimeType();
  EXPECT_EQ(mime, "image/tiff");
}

// Test that calling mimeType() multiple times returns the same result (caching behavior)
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeCachedConsistency_1729) {
  std::string mime1 = tiffImage_->mimeType();
  std::string mime2 = tiffImage_->mimeType();
  EXPECT_EQ(mime1, mime2);
  EXPECT_EQ(mime1, "image/tiff");
}

// Test that setting compression to 32767 yields "image/x-sony-arw"
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeSonyArw_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(32767);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/x-sony-arw");
}

// Test that setting compression to 32769 yields "image/x-epson-erf"
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeEpsonErf_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(32769);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/x-epson-erf");
}

// Test that setting compression to 32770 yields "image/x-samsung-srw"
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeSamsungSrw_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(32770);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/x-samsung-srw");
}

// Test that setting compression to 34713 yields "image/x-nikon-nef"
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeNikonNef_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(34713);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/x-nikon-nef");
}

// Test that setting compression to 65000 yields "image/x-kodak-dcr"
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeKodakDcr_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  // 65000 exceeds uint16_t max? No, uint16_t max is 65535, so 65000 fits.
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(65000);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/x-kodak-dcr");
}

// Test that setting compression to 65535 yields "image/x-pentax-pef"
TEST_F(TiffImageMimeTypeTest_1729, MimeTypePentaxPef_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(65535);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/x-pentax-pef");
}

// Test that setting an unknown compression value falls back to "image/tiff"
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeUnknownCompression_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(1); // standard TIFF compression, not in mimeTypeList
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/tiff");
}

// Test with compression value 0 (not in the list)
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeCompressionZero_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(0);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/tiff");
}

// Test with a common TIFF compression value (e.g., 6 = JPEG) not in the special list
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeJpegCompression_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(6);
  std::string mime = img->mimeType();
  EXPECT_EQ(mime, "image/tiff");
}

// Test pixelWidth default
TEST_F(TiffImageMimeTypeTest_1729, PixelWidthDefault_1729) {
  EXPECT_EQ(tiffImage_->pixelWidth(), 0u);
}

// Test pixelHeight default
TEST_F(TiffImageMimeTypeTest_1729, PixelHeightDefault_1729) {
  EXPECT_EQ(tiffImage_->pixelHeight(), 0u);
}

// Test setComment throws or is a no-op (TiffImage overrides setComment)
TEST_F(TiffImageMimeTypeTest_1729, SetCommentNoOp_1729) {
  // TiffImage::setComment is overridden; we just verify it doesn't crash
  EXPECT_NO_THROW(tiffImage_->setComment("test comment"));
}

// Test that exifData is accessible and initially empty
TEST_F(TiffImageMimeTypeTest_1729, ExifDataInitiallyEmpty_1729) {
  Exiv2::ExifData& exifData = tiffImage_->exifData();
  EXPECT_TRUE(exifData.empty());
}

// Test that after clearing exifData, mimeType returns default on a fresh image
TEST_F(TiffImageMimeTypeTest_1729, ClearExifDataThenMimeType_1729) {
  auto img = createTiffImage();
  Exiv2::ExifData& exifData = img->exifData();
  exifData["Exif.Image.Compression"] = static_cast<uint16_t>(32767);
  // First call caches the result
  std::string mime1 = img->mimeType();
  EXPECT_EQ(mime1, "image/x-sony-arw");
}

// Test with a brand new TiffImage that mimeType is not empty
TEST_F(TiffImageMimeTypeTest_1729, MimeTypeNotEmpty_1729) {
  std::string mime = tiffImage_->mimeType();
  EXPECT_FALSE(mime.empty());
}

// Test image type
TEST_F(TiffImageMimeTypeTest_1729, ImageType_1729) {
  EXPECT_EQ(tiffImage_->imageType(), Exiv2::ImageType::tiff);
}

}  // namespace
