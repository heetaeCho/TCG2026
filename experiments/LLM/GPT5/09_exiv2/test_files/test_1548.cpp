// File: test_orfimage_pixelwidth_1548.cpp

#include <gtest/gtest.h>

#include <exiv2/orfimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>

#include <cstdint>
#include <limits>
#include <memory>

namespace {

class OrfImagePixelWidthTest_1548 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::OrfImage> MakeOrfImage() {
    // pixelWidth() only consults ExifData; IO contents should not matter here.
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::OrfImage>(std::move(io), /*create=*/false);
  }
};

TEST_F(OrfImagePixelWidthTest_1548, ReturnsZeroWhenExifKeyMissing_1548) {
  auto img = MakeOrfImage();

  // No Exif.Image.ImageWidth set.
  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(OrfImagePixelWidthTest_1548, ReturnsValueWhenExifKeyPresent_1548) {
  auto img = MakeOrfImage();

  img->exifData()["Exif.Image.ImageWidth"] = static_cast<uint32_t>(123u);

  EXPECT_EQ(img->pixelWidth(), 123u);
}

TEST_F(OrfImagePixelWidthTest_1548, ReturnsZeroWhenExifKeyPresentButValueIsZero_1548) {
  auto img = MakeOrfImage();

  img->exifData()["Exif.Image.ImageWidth"] = static_cast<uint32_t>(0u);

  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(OrfImagePixelWidthTest_1548, ReturnsMaxWhenExifKeyPresentWithMaxUint32_1548) {
  auto img = MakeOrfImage();

  const uint32_t kMax = std::numeric_limits<uint32_t>::max();
  img->exifData()["Exif.Image.ImageWidth"] = kMax;

  EXPECT_EQ(img->pixelWidth(), kMax);
}

TEST_F(OrfImagePixelWidthTest_1548, UsesUpdatedExifValueAfterOverwrite_1548) {
  auto img = MakeOrfImage();

  img->exifData()["Exif.Image.ImageWidth"] = static_cast<uint32_t>(10u);
  EXPECT_EQ(img->pixelWidth(), 10u);

  // Overwrite via the public ExifData interface.
  img->exifData()["Exif.Image.ImageWidth"] = static_cast<uint32_t>(999u);
  EXPECT_EQ(img->pixelWidth(), 999u);
}

}  // namespace