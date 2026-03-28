// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::MrwImage::pixelHeight()
// File: test_mrwimage_pixelheight_980.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/mrwimage.hpp>

namespace {

class MrwImageTest_980 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::MrwImage> MakeMrwImage() {
    // Use an in-memory IO to avoid filesystem dependencies.
    Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
    return std::unique_ptr<Exiv2::MrwImage>(new Exiv2::MrwImage(std::move(io), /*create=*/false));
  }
};

TEST_F(MrwImageTest_980, PixelHeightReturnsZeroWhenExifTagMissing_980) {
  auto img = MakeMrwImage();

  // No Exif.Image.ImageLength set.
  EXPECT_EQ(img->pixelHeight(), 0u);
}

TEST_F(MrwImageTest_980, PixelHeightReturnsValueWhenExifImageLengthPresent_980) {
  auto img = MakeMrwImage();

  // Set the tag via the public ExifData accessor.
  img->exifData()["Exif.Image.ImageLength"] = static_cast<uint32_t>(1234);

  EXPECT_EQ(img->pixelHeight(), 1234u);
}

TEST_F(MrwImageTest_980, PixelHeightReturnsZeroWhenExifImageLengthIsZero_980) {
  auto img = MakeMrwImage();

  img->exifData()["Exif.Image.ImageLength"] = static_cast<uint32_t>(0);

  EXPECT_EQ(img->pixelHeight(), 0u);
}

TEST_F(MrwImageTest_980, PixelHeightReturnsZeroWhenExifTagPresentButHasNoValue_980) {
  auto img = MakeMrwImage();

  // Boundary case: tag exists but has no value (if supported by implementation).
  // We do NOT infer internal behavior; we only verify observable outcome and that it doesn't crash.
  img->exifData().add(Exiv2::ExifKey("Exif.Image.ImageLength"), /*pValue=*/nullptr);

  EXPECT_EQ(img->pixelHeight(), 0u);
}

TEST_F(MrwImageTest_980, PixelHeightUnaffectedByOtherExifTags_980) {
  auto img = MakeMrwImage();

  // Set some other common tag; pixelHeight should still be 0 without ImageLength.
  img->exifData()["Exif.Image.ImageWidth"] = static_cast<uint32_t>(999);

  EXPECT_EQ(img->pixelHeight(), 0u);
}

}  // namespace